#include <algorithm>
#include "creatureManager.hpp"
#include "mapManager.hpp"







CreatureManager::CreatureManager(tileMap& map) : 
map_(map)
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
        creatures_.push_back(std::make_shared<Creature>(path_.front().x, path_.front().y, map_, 70, 100.f));
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
        [](const std::shared_ptr<Creature>& c){ return !c->isAlive(); }),
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

    
   
}