#ifndef __TOWERMANAGER_HPP
#define __TOWERMANAGER_HPP

#include<SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>
#include "tower.hpp"
#include "tileMap.hpp"
#include "utils.hpp"


class TowerManager {
  
    public : 
    TowerManager(tileMap& map): map_(map) {}

    inline bool inBound(int grid_x ,int grid_y) const ; 
    bool buildable(sf::Vector2u grisPos) const;
    bool isOccupied(sf::Vector2u gridPos) const;
    bool inGround(sf::Vector2u gridPos) const;
    bool addTower(sf::RenderTarget& window, sf::Vector2i pixel); 
    void draw(sf::RenderTarget& window) const ;
    std::vector<Tower> getTowers() const { return towers_ ;}

    void Ghost();
    void updateGhost(sf::RenderWindow& window, sf::Vector2i pixel);
    void drawGhost(sf::RenderTarget& window) const;

    

    private :

   static uint64_t key(sf::Vector2u gridPos) { return (uint64_t(gridPos.x) << 32) ^ gridPos.y; }

   private : 

   tileMap& map_ ;
   std::unordered_set<uint64_t> occupied_ ;
   std::vector<Tower> towers_ ;
   sf::RectangleShape ghost_;
   sf::Vector2i ghostGridPos_ =  {-1, -1};
   








};
#endif 