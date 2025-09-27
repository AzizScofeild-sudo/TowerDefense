#include "strongTower.hpp"
#include <iostream>

StrongTower::StrongTower(int gridX, int gridY, int cellSize)
    : Tower(gridX, gridY, cellSize)
{
    damage = 20;
    range = 150;
    shape.setFillColor(sf::Color::Red);

    rangeCircle.setRadius(range);
    rangeCircle.setOutlineColor(sf::Color::Red);
    rangeCircle.setOrigin(range, range);
}

void StrongTower::shoot()
{

}

void StrongTower::draw(sf::RenderWindow& window)
{
    Tower::draw(window);
}
