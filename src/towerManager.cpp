#include "towerManager.hpp"
#include <iostream>




inline bool TowerManager::inBound(int  grid_x, int grid_y) const  
{
    return (grid_x>=0 && grid_y>=0 && static_cast<unsigned>(grid_x)< map_.getWidth() && static_cast<unsigned>(grid_y)<map_.getHeight() );
}



bool TowerManager::isOccupied(sf::Vector2u gridPos) const
{ 


    int gx = static_cast<int>(gridPos.x); 
    int gy = static_cast<int>(gridPos.y) ; 
    if(!inBound(gx, gy)) return true ; 
    if( occupied_.count( key( { static_cast<unsigned>(gx) ,static_cast<unsigned>(gy) } ) ) > 0)
    {
        return true ;
    }

    return false;
}

bool TowerManager::inGround(sf::Vector2u gridPos) const
{

            int gx = static_cast<int>(gridPos.x) ; 
            int gy = static_cast<int>(gridPos.y) ; 
            if(!inBound(gx, gy)) return false ;
            if( map_.accessTile( static_cast<unsigned>(gx) ,static_cast<unsigned>(gy) ).getType() != tileType::ground)
            {
                return false ;
            }

    return true ;
}


bool TowerManager::buildable(sf::Vector2u gridPos) const
{
    return inGround(gridPos) && !isOccupied(gridPos) ;
}



bool TowerManager::addTower(sf::Vector2i cell_pos)
{

    sf::Vector2u cell_unsigned = {static_cast<unsigned>(cell_pos.x),static_cast<unsigned>(cell_pos.y)};

    if(!buildable(cell_unsigned)) return false ; 
    towers_.push_back(std::make_unique<Tower>(cell_unsigned , map_,150.f, 5, 0.6f, 400.f)) ;
    
            occupied_.insert( key( { cell_unsigned.x  , cell_unsigned.y  } ) ) ;

    return true ;
}





void TowerManager::draw(sf::RenderTarget& window)  {
    for (auto& t : towers_) t->draw(window);    ////change syntaxe
}

void TowerManager::Ghost()
{
    ghost_.setSize({static_cast<float>(map_.getSizeTile()), static_cast<float>(map_.getSizeTile())});
    ghost_.setFillColor(sf::Color(0,255,0,70));
    ghost_.setOutlineThickness(1.f);
    ghost_.setOutlineColor(sf::Color::Black);
}


void TowerManager::updateGhost(sf::Vector2i cell_pos)
{

     if (cell_pos.x < 0 || cell_pos.y < 0) {
      ghostGridPos_ = {-1,-1};                 //////
      return;
    }
    ghostGridPos_ = {cell_pos.x, cell_pos.y};   
    
    // Set la position du Ghost : 
    ghost_.setPosition(Grid::gridToWorld(cell_pos.x, cell_pos.y));

    //Donner une couleur au Ghost : 
    sf::Vector2u center{ static_cast<unsigned>(cell_pos.x), static_cast<unsigned>(cell_pos.y) };
    if (buildable(center)) ghost_.setFillColor(sf::Color(0,255,0,70));
    else ghost_.setFillColor(sf::Color(255,0,0,70));
  }


  void TowerManager::drawGhost(sf::RenderTarget& window) const
  {
    if (ghostGridPos_.x < 0 || ghostGridPos_.y < 0 || ghostGridPos_.x > static_cast<int>(map_.getWidth()) || ghostGridPos_.y > static_cast<int>(map_.getHeight())) return; //// normalement >=
    window.draw(ghost_);
  }



void TowerManager::Update(const std::vector<std::shared_ptr<Creature>>& creatures){
    float frameTime = deltaClock_.restart().asSeconds();
            for (auto& t : towers_) {
            t->update(frameTime,creatures);
        }
}