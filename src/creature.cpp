#include "creature.hpp"
#include "hpBar.hpp"
#include "gameEconomy.hpp"
#include <cmath>
#include <iostream>

Creature::Creature(int gridX, int gridY, tileMap& map, int health, float speed, int reward)
    : position(gridX * map.getSizeTile(), gridY * map.getSizeTile()),
      health(health), speed(speed),
      currentPathIndex(0),
      map_(map),
      alive(true),
      reward(reward) // AJOUT : initialisation reward
{
    unsigned cellSize = map_.getSizeTile();
    shape.setRadius(cellSize / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(cellSize / 2.f, cellSize / 2.f); 
    shape.setPosition(position);

    healthBar = std::make_unique<hpBar>(*this);
}

void Creature::move(const std::vector<sf::Vector2i>& pathTiles, float deltaTime)
{
    if (!alive || pathTiles.empty()) return;

    if (currentPathIndex < 0 || currentPathIndex >= static_cast<int>(pathTiles.size())) {
        alive = false;        
        return;
    }

    unsigned cellSize = map_.getSizeTile();
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

    if (distance < 2.f) {
        ++currentPathIndex;
        if (currentPathIndex >= static_cast<int>(pathTiles.size())) {
            alive = false;
        }
    }
}

void Creature::draw(sf::RenderTarget& rt)
{
    if (!alive) return;
    rt.draw(shape);
    healthBar->update();
    healthBar->draw(rt);
}

sf::Vector2f Creature::getCreaturePosition() const { return position; }
bool Creature::isAlive() const { return alive; }
int Creature::getHealth() const { return health; }
float Creature::getCreatureRadius() const { return shape.getRadius(); }

void Creature::takeDamage(int damage, gameEconomy* economy)
{
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
        // ajout economy
        if (economy)
            economy->earn(reward);
    }
}
