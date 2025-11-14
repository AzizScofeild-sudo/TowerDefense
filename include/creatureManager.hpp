#ifndef CREATUREMANAGER_HPP
#define CREATUREMANAGER_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "creature.hpp"
#include "tileMap.hpp"




class CreatureManager {

public:
CreatureManager(tileMap& map) ;

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


};

#endif