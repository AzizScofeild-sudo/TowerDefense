#ifndef TOWER_HPP
#define TOWER_HPP
#include <SFML/Graphics.hpp>
#include "tileMap.hpp"
#include "tile.hpp"



class Tower {
public :
    Tower(sf::Vector2u gridPos, tileMap& map);

    void draw(sf::RenderTarget& window);              
    sf::Vector2u getTowerPosition() const; 
    sf::RectangleShape geTowerShape(){return tower_shape_;}

private :

    tileMap& map_ ;
    sf::RectangleShape tower_shape_;
    sf::Vector2u gridPos_;
    float size_tower  ;
   
};

#endif