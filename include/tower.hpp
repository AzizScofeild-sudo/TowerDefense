#ifndef TOWER_HPP
#define TOWER_HPP
#include <SFML/Graphics.hpp>
#include "tileMap.hpp"

class Tower {
public:
    Tower(int gridX, int gridY, tileMap& map);

    virtual void draw(sf::RenderWindow& window);  
    virtual void shoot() = 0;                     
    sf::Vector2i getGridPosition() const;

protected:
    tileMap& map;
    sf::RectangleShape shape;
    sf::CircleShape rangeCircle;
    sf::Vector2i gridPos;
    int range;
    int damage;
};

#endif