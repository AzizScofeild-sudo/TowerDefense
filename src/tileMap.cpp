#include "tileMap.hpp"
#include "tile.hpp"
#include<iostream>




tileMap::tileMap(unsigned width ,unsigned height ,unsigned cell_size):width_(width),height_(height),cell_size_(cell_size)   
{
    tiles_.resize(width * height);
}


tileMap::tileMap(float width_window , float height_window)
{
    setDimenssion(width_window , height_window);
    tiles_.resize(width_ * height_);
}


tile&  tileMap::accessTile(unsigned x ,unsigned y)
{
    return tiles_[y*width_ + x] ; 

}

const tile& tileMap::accessTile(unsigned x, unsigned y) const
{
    return tiles_[y*width_+x];  
} 

bool tileMap::inBounds(unsigned x ,unsigned y) const  noexcept
{
    return (x < width_ && y < height_) ; 
}

void tileMap::paint(unsigned x ,unsigned y ,tileType t)
{
      if(inBounds(x,y)) {accessTile(x,y).setType(t);}
}

sf::Vector2i tileMap::worldToCell(sf::Vector2f& world) const 
{
   if(world.x < 0.f || world.y < 0.f ) return {-1 ,-1} ; 
   unsigned cell_x = static_cast<unsigned>(world.x) / cell_size_ ; 
   unsigned cell_y = static_cast<unsigned>(world.y) / cell_size_ ;
   if(!inBounds(cell_x,cell_y)) return {-1 ,-1};
   return {static_cast<int>(cell_x) ,static_cast<int>(cell_y)};
}

void tileMap::draw(sf::RenderTarget& rt) const 
{
// Dessiner les casee :     
    sf::RectangleShape cell({static_cast<float>(cell_size_) ,static_cast<float>(cell_size_)});

    for(unsigned y  = 0 ; y < height_ ; ++y)
    {
        for(unsigned x = 0 ; x < width_ ; ++x)
        {   
            
            const tile& t = tiles_[y*width_ + x] ;
            cell.setPosition(static_cast<float>(x*cell_size_), static_cast<float>(y*cell_size_));
            cell.setFillColor(t.displayColor());
            rt.draw(cell);
        }
    }
// Dessiner la grille : 
    const sf::Color lineColor(0, 0, 0, 0);

    for(unsigned x = 0 ; x <= width_ ; ++x)
    {
        sf::Vertex line[] = 
        {
            sf::Vertex({static_cast<float>(x*cell_size_), 0.f}, lineColor),
            sf::Vertex({static_cast<float>(x*cell_size_), static_cast<float>(height_*cell_size_)}, lineColor)  

        };
        rt.draw(line, 2, sf::Lines);
    }
    
    for(unsigned y = 0 ; y <= height_ ; ++y)
    {
        sf::Vertex line[] = 
        {
            sf::Vertex({0.f, static_cast<float>(y*cell_size_)}, lineColor),
            sf::Vertex({static_cast<float>(width_*cell_size_), static_cast<float>(y*cell_size_)}, lineColor)  

        
        };
        rt.draw(line, 2, sf::Lines);
    }


}


void tileMap::setDimenssion(float width_window , float height_window)
{
    width_ = static_cast<unsigned>(width_window) / cell_size_ ; 
    height_ = static_cast<unsigned>(height_window) / cell_size_ ; 

}


  unsigned tileMap::getWidth() const noexcept 
  {
      return width_ ;}




   unsigned tileMap::getHeight() const noexcept

    {
         return height_ ;}



 unsigned tileMap::getSizeTile() const noexcept 
 {
     return cell_size_ ;
 }