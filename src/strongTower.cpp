#include "strongTower.hpp"
#include <iostream>

StrongTower::StrongTower(int gridX, int gridY, tileMap& map)
    : Tower(gridX, gridY, map)
{
    damage = 20;
    range = 150;
    shape.setFillColor(sf::Color::Red);

    rangeCircle.setRadius(range);
    rangeCircle.setOutlineColor(sf::Color::Red);
    rangeCircle.setOrigin(range, range);
}

void StrongTower::shoot(Creature& target)
{
    projectiles.push_back(std::make_unique<Projectile>(*this, target, 400.f, damage));
}

void StrongTower::draw(sf::RenderWindow& window)
{
    Tower::draw(window);
}