#include "creature.hpp"
#include "hpBar.hpp"
#include <cmath>

Creature::Creature(int gridX, int gridY, tileMap& map, int health, float speed)
    : position(gridX * map.getSizeTile(), gridY * map.getSizeTile()),
      health(health), speed(speed), currentPathIndex(0), map(map), alive(true)
{
    int cellSize = map.getSizeTile();
    shape.setRadius(cellSize / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(cellSize / 2.f, cellSize / 2.f); 
    shape.setPosition(position);

    healthBar = std::make_unique<hpBar>(*this);
}

void Creature::move(const std::vector<sf::Vector2i>& pathTiles, float deltaTime)
{
    if (pathTiles.empty() || !alive) return;

    int cellSize = map.getSizeTile();
    sf::Vector2f target(
        pathTiles[currentPathIndex].x * cellSize + cellSize / 2.f,
        pathTiles[currentPathIndex].y * cellSize + cellSize / 2.f
    );

    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.1f) {
        direction /= distance;
        position += direction * speed * deltaTime;
        shape.setPosition(position);
    }

    if (distance < 2.f)
        currentPathIndex++;

    if (currentPathIndex >= static_cast<int>(pathTiles.size()))
        alive = false;
}

void Creature::draw(sf::RenderWindow& window)
{
    if (!alive) return;

    window.draw(shape);

    // update et mise a jour hpBar
    healthBar->update();
    healthBar->draw(window);
}

sf::Vector2f Creature::getCreaturePosition() const
{
    return position;
}

bool Creature::isAlive() const
{
    return alive;
}


void Creature::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

int Creature::getHealth() const
{
    return health;
}

float Creature::getCreatureRadius() const
{
    return shape.getRadius();
}
