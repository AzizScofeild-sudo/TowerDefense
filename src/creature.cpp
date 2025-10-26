#include "creature.hpp"
#include "tileMap.hpp"
#include <cmath>


Creature::Creature(int gridX, int gridY,tileMap& map, int health, float speed)
    : position(gridX * map.getSizeTile(), gridY* map.getSizeTile()), health(health), speed(speed), currentPathIndex(0),map(map), alive(true)
{
    int cellSize = map.getSizeTile();
    shape.setRadius(cellSize / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(cellSize / 2.f, cellSize / 2.f);
    shape.setPosition(position);
}

void Creature::move(std::vector<sf::Vector2i> path, float deltaTime)
{
    if (path.empty() || !alive) return;

    // terget en pixels
    int cellSize = map.getSizeTile(); 
    sf::Vector2f target(path[currentPathIndex].x * cellSize + cellSize / 2.f,
                        path[currentPathIndex].y * cellSize + cellSize / 2.f);

    // Calcul du vecteur directionnel
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.1f) {
        // Normalisation du vecteur direction
        direction /= distance;
        position += direction * speed * deltaTime;
        shape.setPosition(position);
    }

    if (distance < 2.f) {
        currentPathIndex++;
    }

    if (currentPathIndex >= path.size()) {
        alive = false; 

}
}



void Creature::draw(sf::RenderWindow& window)
{
    if (!alive) return;
    window.draw(shape);
}

sf::Vector2f Creature::getCreaturePosition() const
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