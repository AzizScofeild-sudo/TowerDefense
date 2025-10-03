#ifndef __TILEMAP__
 #define __TILEMAP__

#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class tileMap
{

    public :
    ~tileMap() = default;
    tileMap(unsigned width , unsigned height , unsigned cell_size);
    tileMap(float width_window , float height_window);

   tile& accessTile(unsigned x , unsigned y);
   const tile& accessTile(unsigned x , unsigned y) const;
   bool inBounds(unsigned x ,unsigned y) const noexcept;
   void  paint(unsigned x , unsigned y , tileType t );
   sf::Vector2i worldToCell(sf::Vector2f& world) const;
   void draw(sf::RenderTarget& rt) const;

   // les accesseurs : 

   unsigned getWidth() const noexcept ;
   unsigned getheight() const noexcept ;
   unsigned getSizeTile() const noexcept ; 

    private : 

    void setDimenssion(float width_window , float height_window);


    private :

    unsigned width ; 
    unsigned height ;
    unsigned cell_size = 25 ;
    std::vector<tile> tiles ;
};
#endif 