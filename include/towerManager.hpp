#ifndef __TOWERMANAGER_HPP
#define __TOWERMANAGER_HPP


#include <vector>
#include <unordered_set>
#include "tower.hpp"
#include "tileMap.hpp"


class TowerManager {
  
    public : 
    TowerManager(tileMap& map): map_(map) {}

    bool buildable(sf::Vector2u grisPos) const;
    bool isOccupied(sf::Vector2u gridPos) const;
    bool addTower(sf::Vector2u gridPos); 
    void draw(sf::RenderWindow& window) const ;
    std::vector <Tower> getTowers() const { return towers_ ;}

    private :

   static uint64_t key(sf::Vector2u gridPos) { return (uint64_t(gridPos.x) << 32) ^ gridPos.y; }

   private : 

   tileMap& map_ ;
   std::unordered_set<uint64_t> occupied_ ;
   std::vector<Tower> towers_ ;









};
#endif 