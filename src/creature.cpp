#include  "creature.hpp"

Creature::Creature(int gridX, int gridY, int cellSize, int health, float speed)
    : position(gridX * cellSize, gridY * cellSize), cellSize(cellSize), health(100), speed(0.2f)
{
    shape.setRadius(cellSize / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}
void Creature::move()
{
    position.x += speed;
    shape.setPosition(position);
}
void Creature::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
sf::Vector2f Creature::getPosition() const
{
    return position;
}
bool Creature::isAlive() const
{       
    return health > 0;
}
void Creature::takeDamage(int damage)
{
    health = health-damage;
    if (health < 0)
        health = 0;
}
int Creature::getHealth() const
{
    return health;
}

