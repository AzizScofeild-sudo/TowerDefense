#include "weakTower.hpp"
#include <iostream>


WeakTower::WeakTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map)
{
    damage = 5;
    range = 50;
    shape.setFillColor(sf::Color::Green);

    rangeCircle.setRadius(range);
    rangeCircle.setOutlineColor(sf::Color::Green);
    rangeCircle.setOrigin(range, range);
}

void WeakTower::shoot()
{

}

void WeakTower::draw(sf::RenderWindow& window)
{
    Tower::draw(window); 
}
