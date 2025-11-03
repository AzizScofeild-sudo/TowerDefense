#include "mediumTower.hpp"
#include <iostream>


MediumTower::MediumTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map)
{
    damage = 10;
    range = 100;
    shape.setFillColor(sf::Color::Blue);

    rangeCircle.setRadius(range);
    rangeCircle.setOutlineColor(sf::Color::Blue);
    rangeCircle.setOrigin(range, range);
}

void MediumTower::shoot(Creature& target)
{
    projectiles.push_back(std::make_unique<Projectile>(*this, target, 300.f, damage));
}

void MediumTower::draw(sf::RenderWindow& window)
{
    Tower::draw(window);
}