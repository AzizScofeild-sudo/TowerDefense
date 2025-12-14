/* #ifndef CREATUREMANAGER_HPP
#define CREATUREMANAGER_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "creature.hpp"
#include "tileMap.hpp"




class CreatureManager {

public:
CreatureManager(tileMap& map, gameEconomy& economy);

void spawn();
void update();
void draw(sf::RenderTarget& rt);
void buildPath(); 
const std::vector<std::shared_ptr<Creature>>& getCreatures() const {
    return creatures_;
}

private:

tileMap& map_ ; 
sf::Clock spawnTimer_ ;
sf::Clock frameClock_;
const float spawnInterval_ = 1.0 ;// en seconde (4 secondes)
std::vector<std::shared_ptr<Creature>> creatures_ ; 
std::vector<sf::Vector2i> path_ ;

gameEconomy& economy_;

};

#endif */

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class tileMap;
class Creature;
class gameEconomy;

// >>> MODIF : structure Wave
struct Wave
{
    int creatureCount;
    int spawned;
    int health;
    float speed;
    int reward;
    float spawnInterval;
};

class CreatureManager
{
public:
    CreatureManager(tileMap& map, gameEconomy& economy);

    void update();
    void draw(sf::RenderTarget& rt);
    void buildPath();
    const std::vector<std::shared_ptr<Creature>>& getCreatures() const;


private:
    void spawn();
    void startNextWave();   // >>> MODIF

    tileMap& map_;
    gameEconomy& economy_;

    std::vector<std::shared_ptr<Creature>> creatures_;
    std::vector<sf::Vector2i> path_;

    sf::Clock spawnTimer_;
    sf::Clock frameClock_;

    // >>> MODIF : système de vagues
    std::vector<Wave> waves_;
    int currentWave_ = 0;
};
