#include "mediumTower.hpp"
#include <SFML/Graphics.hpp>

MediumTower::MediumTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map, 150.f, 5, 0.6f, 400.f) // range, damage, fireRate, projectileSpeed
{
    shape.setFillColor(sf::Color::Green); 
    rangeCircle.setOutlineColor(sf::Color::Yellow); 
}