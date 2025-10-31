#include "towerManager.hpp"
#include <iostream>






bool TowerManager::isOccupied(sf::Vector2u gridPos) const
{ 


    for(int dx = -1 ; dx <= 1 ; ++dx)
    {
        for(int dy = -1 ; dy <=1 ; ++dy)
        {
            if( occupied_.count( key( { gridPos.x + dx , gridPos.y + dy } ) ) > 0)
            {
                return true ;
            }
        }
    }
    return false;
}

bool TowerManager::inGround(sf::Vector2u gridPos) const
{
    for(int dx = -1 ; dx <= 1 ; ++dx)
    {
        for(int dy = -1 ; dy <=1 ; ++dy)
        {
            if( map_.accessTile( gridPos.x + dx , gridPos.y + dy ).getType() != tileType::ground)
            {
                return false ;
            }
        }
    }
    return true ;


}


bool TowerManager::buildable(sf::Vector2u gridPos) const
{
   if(inGround(gridPos))
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
    for(int dx = -1 ; dx <= 1 ; ++dx)
    {
        for(int dy = -1 ; dy <=1 ; ++dy)
        {
            occupied_.insert( key( { gridPos.x + dx , gridPos.y + dy } ) ) ;
        }
    }
    return true ;
}

void TowerManager::draw(sf::RenderWindow& window) const  {
    for (std::size_t i = 0; i < towers_.size(); ++i)
        const_cast<Tower&>(towers_[i]).draw(window);
}
