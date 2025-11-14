#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <SFML/Graphics.hpp>
#include "tileMap.hpp"
#include <vector>
#include <memory>
#include "hpBar.hpp"


class Creature {
public:
    Creature(int gridX, int gridY, tileMap& map, int health, float speed);

    void move(const std::vector<sf::Vector2i>& pathTiles, float deltaTime);
    void draw(sf::RenderTarget& rt);

    sf::Vector2f getCreaturePosition() const;
    bool isAlive() const;
    void takeDamage(int damage); // elle etait commentee par cheikh jamal
    int getHealth() const;
    float getCreatureRadius() const;

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    int health;
    float speed;
    int currentPathIndex;
    tileMap map_ ; // Solution chatGPT !!!!
    bool alive;

    std::unique_ptr<hpBar> healthBar; // HP bar attachee a la créature
};

#endif