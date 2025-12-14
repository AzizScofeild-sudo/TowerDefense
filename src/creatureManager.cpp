/* #include <algorithm>
#include "creatureManager.hpp"
#include "mapManager.hpp"







CreatureManager::CreatureManager(tileMap& map, gameEconomy& economy)
    : map_(map), economy_(economy)
{
    // ajouter un controlle sur le bon calcule du path avec une sorte de 
    // if(path.empty()) std::cout<<"aucun chemin trouve...."<<std::endl ;  
    //path_ = mapManager::extractPathTiles(map_);
    //if (path_.empty()) {
    //    std::cout << "[CreatureManager] Aucun chemin trouvé, les créatures ne pourront pas bouger" <<std::endl;
    //}
    spawnTimer_.restart();
}


void CreatureManager::spawn()
{
    if(path_.empty()) return ; 
    if(spawnTimer_.getElapsedTime().asSeconds() >= spawnInterval_)
    {
        creatures_.push_back(std::make_shared<Creature>(path_.front().x, path_.front().y, map_, 70, 100.f, 10));
        std::cout<<"une nouvelle creature a etait cree !"<<std::endl;
        spawnTimer_.restart();
    } 
}

void CreatureManager::update() 
{
    float dt = frameClock_.restart().asSeconds();
    spawn();
    for (auto& c : creatures_){c->move(path_, dt);}

    // supprimer les créatures mortes (qui ont fini le chemin ou sont "tuées")
    //std::cout<<"la taille du creatures 2 :"<<creatures_.size()<<std::endl;
    creatures_.erase(
        std::remove_if(creatures_.begin(), creatures_.end(),
            [this](const std::shared_ptr<Creature>& c) {
                if (!c->isAlive()) {
                    return true;
                }
                return false;
            }),
        creatures_.end()
    );
    //std::cout<<"la taille du creatures 3 :"<<creatures_.size()<<std::endl;
}

void CreatureManager::draw(sf::RenderTarget& rt)
{
    for (auto& c : creatures_) c->draw(rt);

}



void CreatureManager::buildPath()
{
    path_ = mapManager::extractPathTiles(map_);
    //petit test de bof : 
    std::cout<<"la taille du paff 1 :" << path_.size() <<std::endl; 
    if (path_.empty()) {
        std::cout << "Aucun chemin trouvé, les créatures ne pourront pas bouger" <<std::endl;
    }

    
   
} */

#include <algorithm>
#include <iostream>

#include "creatureManager.hpp"
#include "creature.hpp"
#include "mapManager.hpp"
#include "gameEconomy.hpp" 

CreatureManager::CreatureManager(tileMap& map, gameEconomy& economy)
    : map_(map), economy_(economy)
{
    spawnTimer_.restart();

    waves_ = {
        // creatureCount, spawned, health, speed, reward, spawnInterval

        {15,  0,  50,  80.f,  5,  1.5f}, // vague 1
        {20,  0,  80, 110.f,  8,  1.2f}, // vague 2
        {25, 0, 120, 150.f, 12, 0.8f}  // vague 3
    };
}

void CreatureManager::buildPath()
{
    path_ = mapManager::extractPathTiles(map_);

    if (path_.empty())
    {
        std::cout << "[CreatureManager] Aucun chemin trouvé" << std::endl;
    }
}

void CreatureManager::spawn()
{
    if (path_.empty()) return;
    if (currentWave_ >= waves_.size()) return;

    Wave& wave = waves_[currentWave_];

    // >>> MODIF : si la vague est complète, on ne spawn plus
    if (wave.spawned >= wave.creatureCount)
        return;

    if (spawnTimer_.getElapsedTime().asSeconds() >= wave.spawnInterval)
    {
        creatures_.push_back(std::make_shared<Creature>(
            path_.front().x,
            path_.front().y,
            map_,
            wave.health,
            wave.speed,
            wave.reward
        ));

        wave.spawned++;
        spawnTimer_.restart();

        std::cout << "Spawn creature ("
                  << wave.spawned << "/"
                  << wave.creatureCount
                  << ") vague " << currentWave_ + 1 << std::endl;
    }
}

void CreatureManager::update()
{
    float dt = frameClock_.restart().asSeconds();

    spawn();

    for (auto& c : creatures_)
        c->move(path_, dt);

    // suppression des créatures mortes
    creatures_.erase(
        std::remove_if(creatures_.begin(), creatures_.end(),
            [this](const std::shared_ptr<Creature>& c)
            {
                if (!c->isAlive()) {
                    if (c->wasKilledByPlayer())
                        economy_.earn(c->getReward());
                    return true; // retire la créature morte ou arrivée au goal
                }
                return false;
            }),
        creatures_.end()
    );



    // >>> MODIF : passer à la vague suivante
    if (creatures_.empty() &&
        currentWave_ < waves_.size() &&
        waves_[currentWave_].spawned >= waves_[currentWave_].creatureCount)
    {
        startNextWave();
    }
}

void CreatureManager::startNextWave()
{
    currentWave_++;

    if (currentWave_ < waves_.size())
    {
        std::cout << "===== VAGUE "
                  << currentWave_ + 1
                  << " =====" << std::endl;

        spawnTimer_.restart();
    }
    else
    {
        std::cout << "===== FIN DES VAGUES =====" << std::endl;
    }
}

void CreatureManager::draw(sf::RenderTarget& rt)
{
    for (auto& c : creatures_)
        c->draw(rt);
}

const std::vector<std::shared_ptr<Creature>>& CreatureManager::getCreatures() const
{
    return creatures_;
}
