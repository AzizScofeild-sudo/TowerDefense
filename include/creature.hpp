#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <SFML/Graphics.hpp>
#include "tileMap.hpp"
#include "hpBar.hpp"
#include <vector>
#include <memory>


class Creature {
public:
    Creature(int gridX, int gridY, tileMap& map, int health, float speed);

    void move(const std::vector<sf::Vector2i>& pathTiles, float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getCreaturePosition() const;
    bool isAlive() const;
    void takeDamage(int damage);
    int getHealth() const;
    float getCreatureRadius() const;

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    int health;
    float speed;
    int currentPathIndex;
    tileMap& map;
    bool alive;

    std::unique_ptr<hpBar> healthBar; // HP bar attachee a la créature
};

#endif
