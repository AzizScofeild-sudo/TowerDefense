#include "strongTower.hpp"
#include <SFML/Graphics.hpp>

StrongTower::StrongTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map, 200.f, 10, 0.4f, 500.f) // range, damage, fireRate, projectileSpeed
{
    shape.setFillColor(sf::Color::Red); 
    rangeCircle.setOutlineColor(sf::Color::Magenta); 
}