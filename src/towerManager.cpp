#include "towerManager.hpp"
#include <iostream>






bool TowerManager::isOccupied(sf::Vector2u gridPos) const
{
    return occupied_.count(key(gridPos)) > 0;
}


bool TowerManager::buildable(sf::Vector2u gridPos) const
{
   if(map_.accessTile(gridPos.x, gridPos.y).getType() == tileType::ground)
   {
    if(!isOccupied(gridPos))
     {
        return true;
     }  
     else return false;  
  
   }
    else return false;
}


bool TowerManager::addTower(sf::Vector2u gridPos)
{
    if(!buildable(gridPos)) return false ; 
    towers_.emplace_back(gridPos , map_) ;
    occupied_.insert(key(gridPos));
    return true ;
}

void TowerManager::draw(sf::RenderWindow& window) const  {
    for (std::size_t i = 0; i < towers_.size(); ++i)
        const_cast<Tower&>(towers_[i]).draw(window);
}
