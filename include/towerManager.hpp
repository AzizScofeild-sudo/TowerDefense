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
    bool addTower(sf::Vector2i cell_pos); 
    void draw(sf::RenderTarget& window) ; // jai enelever const
    // std::vector<Tower> getTowers() const { return towers_ ;}

    void Ghost();
    void updateGhost(sf::Vector2i cell_pos);
    void drawGhost(sf::RenderTarget& window) const;

    void Update(const std::vector<std::shared_ptr<Creature>>& creatures);
    

    private :

   static uint64_t key(sf::Vector2u gridPos) { return (uint64_t(gridPos.x) << 32) ^ gridPos.y; }

   private : 

   tileMap& map_ ;
   std::unordered_set<uint64_t> occupied_ ;
    std::vector<std::unique_ptr<Tower>> towers_;
    sf::RectangleShape ghost_;
   sf::Vector2i ghostGridPos_ =  {-1, -1};


   
   sf::Clock deltaClock_; ///








};
#endif 