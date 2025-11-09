#include "towerManager.hpp"
#include <iostream>




inline bool TowerManager::inBound(int  grid_x, int grid_y) const  
{
    return (grid_x>=0 && grid_y>=0 && static_cast<unsigned>(grid_x)< map_.getWidth() && static_cast<unsigned>(grid_y)<map_.getHeight() );
}



bool TowerManager::isOccupied(sf::Vector2u gridPos) const
{ 


    for(int dx = -1 ; dx <= 1 ; ++dx)
    {
        for(int dy = -1 ; dy <=1 ; ++dy)
        {
            int gx = static_cast<int>(gridPos.x) + dx ; 
            int gy = static_cast<int>(gridPos.y) + dy ; 
            if(!inBound(gx, gy)) return true ; 
            if( occupied_.count( key( { static_cast<unsigned>(gx) ,static_cast<unsigned>(gy) } ) ) > 0)
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
            int gx = static_cast<int>(gridPos.x) + dx ; 
            int gy = static_cast<int>(gridPos.y) + dy ; 
            if(!inBound(gx, gy)) return false ;
            if( map_.accessTile( static_cast<unsigned>(gx) ,static_cast<unsigned>(gy) ).getType() != tileType::ground)
            {
                return false ;
            }
        }
    }
    return true ;


}


bool TowerManager::buildable(sf::Vector2u gridPos) const
{
    return inGround(gridPos) && !isOccupied(gridPos) ;
}



bool TowerManager::addTower(sf::RenderTarget& window,  sf::Vector2i cell_pos)
{

    sf::Vector2u cell_unsigned = {static_cast<unsigned>(cell_pos.x),static_cast<unsigned>(cell_pos.y)};

    if(!buildable(cell_unsigned)) return false ; 
    towers_.emplace_back(cell_unsigned , map_) ;

    for(int dx = -1 ; dx <= 1 ; ++dx)
    {
        for(int dy = -1 ; dy <=1 ; ++dy)
        {        
            occupied_.insert( key( { cell_unsigned.x + dx , cell_unsigned.y + dy } ) ) ;
        }
    }
    return true ;
}




void TowerManager::draw(sf::RenderTarget& window) const  {
    for (std::size_t i = 0; i < towers_.size(); ++i)
        const_cast<Tower&>(towers_[i]).draw(window);
}

void TowerManager::Ghost()
{
    ghost_.setSize({static_cast<float>(3*map_.getSizeTile()), static_cast<float>(3*map_.getSizeTile())});
    ghost_.setFillColor(sf::Color(0,255,0,70));
    ghost_.setOutlineThickness(1.f);
    ghost_.setOutlineColor(sf::Color::Black);
}


void TowerManager::updateGhost(sf::RenderWindow& window, sf::Vector2i cell_pos)
{

     if (cell_pos.x < 0 || cell_pos.y < 0) {
      ghostGridPos_ = {-1,-1};
      return;
    }
    ghostGridPos_ = {cell_pos.x, cell_pos.y};   
    
    // Set la position du Ghost : 
    ghost_.setPosition(Grid::gridToWorld(cell_pos.x-1, cell_pos.y-1));

    //Donner une couleur au Ghost : 
    sf::Vector2u center{ static_cast<unsigned>(cell_pos.x), static_cast<unsigned>(cell_pos.y) };
    if (buildable(center)) ghost_.setFillColor(sf::Color(0,255,0,70));
    else ghost_.setFillColor(sf::Color(255,0,0,70));
  }


  void TowerManager::drawGhost(sf::RenderTarget& window) const
  {
    if (ghostGridPos_.x < 0 || ghostGridPos_.y < 0 || ghostGridPos_.x > static_cast<int>(map_.getWidth()) || ghostGridPos_.y > static_cast<int>(map_.getHeight())) return;
    window.draw(ghost_);
  }
