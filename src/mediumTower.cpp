/* #include "mediumTower.hpp"
#include <SFML/Graphics.hpp>

MediumTower::MediumTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map, 150.f, 5, 0.6f, 400.f) // range, damage, fireRate, projectileSpeed
{
    shape.setFillColor(sf::Color::Green); 
    rangeCircle.setOutlineColor(sf::Color::Yellow); 
} */

#include "mediumTower.hpp"

MediumTower::MediumTower(sf::Vector2u pos, tileMap& map)
    : Tower(pos, map,
            150.f, 5, 0.6f, 400.f, 100)  
{
    tower_shape_.setFillColor(sf::Color(100, 100, 255));
}
