#include "mediumTower.hpp"
#include <iostream>


MediumTower::MediumTower(int gridX, int gridY, int cellSize)
    : Tower(gridX, gridY, cellSize)
{
    damage = 10;
    range = 100;
    shape.setFillColor(sf::Color::Blue);

    rangeCircle.setRadius(range);
    rangeCircle.setOutlineColor(sf::Color::Blue);
    rangeCircle.setOrigin(range, range);
}

void MediumTower::shoot()
{

}

void MediumTower::draw(sf::RenderWindow& window)
{
    Tower::draw(window);
}
