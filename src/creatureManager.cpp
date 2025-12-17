
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

        {20,  0,  50,  80.f,  12,  1.5f}, // vague 1
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

int CreatureManager::update(float dt)
{
    if (dt <= 0.f) return 0;
    if (dt > 0.1f) dt = 0.1f;
    if (path_.empty())
        return 0;

    // 1) spawn
    spawn();

    // 2) move
    for (auto& c : creatures_)
        c->move(path_, dt);

    // 3) collect + erase
    int leaked = 0;

    creatures_.erase(
        std::remove_if(creatures_.begin(), creatures_.end(),
            [this, &leaked](const std::shared_ptr<Creature>& c)
            {
                if (c->isAlive())
                    return false;

                if (c->wasKilledByPlayer())
                {
                    economy_.earn(c->getReward());
                }
                else if (c->reachedGoal())
                {
                    leaked += 1;
                }

                return true;
            }),
        creatures_.end()
    );

    // 4) next wave
    if (currentWave_ < waves_.size())
    {
        Wave& wave = waves_[currentWave_];
        const bool waveCompleted = (wave.spawned >= wave.creatureCount);
        const bool noCreatureLeft = creatures_.empty();

        if (waveCompleted && noCreatureLeft)
            startNextWave();
    }

    return leaked;
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
