#include "creature.hpp"
#include "tileMap.hpp"


Creature::Creature(int gridX, int gridY,tileMap& map, int health, float speed)
    : position(gridX * map.getSizeTile(), gridY* map.getSizeTile()), health(health), speed(speed)
{
    int cellSize = map.getSizeTile();
    shape.setRadius(cellSize / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

void Creature::move()
{
    position.x += speed; // simple déplacement horizontal
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
    health -= damage;
    if (health < 0) 
        health = 0;
}

int Creature::getHealth() const
{
    return health;
}
