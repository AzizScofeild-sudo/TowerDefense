/* #include "weakTower.hpp"
#include <SFML/Graphics.hpp>


WeakTower::WeakTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map, 100.f, 2, 0.8f, 300.f) // range, damage, fireRate, projectileSpeed
{
    shape.setFillColor(sf::Color::Cyan); 
    rangeCircle.setOutlineColor(sf::Color::Blue); 
} */

#include "weakTower.hpp"

WeakTower::WeakTower(sf::Vector2u pos, tileMap& map)
    : Tower(pos, map,
            120.f, 3, 0.4f, 350.f, 50)  
{
    tower_shape_.setFillColor(sf::Color(100, 200, 100));
}
