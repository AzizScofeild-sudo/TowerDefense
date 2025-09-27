#ifndef TOWER_HPP
#define TOWER_HPP
#include <SFML/Graphics.hpp>

class Tower {
public:
    Tower(int gridX, int gridY, int cellSize);

    virtual void draw(sf::RenderWindow& window);  // virtual pour polymorphisme
    virtual void shoot() = 0;                     // pure virtual = obligation override

    sf::Vector2i getGridPosition() const;

protected:
    sf::RectangleShape shape;
    sf::CircleShape rangeCircle;
    sf::Vector2i gridPos;
    int cellSize;
    int range;
    int damage;
};

#endif