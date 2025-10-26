#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <SFML/Graphics.hpp>
#include "tileMap.hpp"
#include <vector>


class Creature {
public:
    Creature(int gridX, int gridY ,tileMap& map ,int health, float speed);

    void move(std::vector<sf::Vector2i> path, float deltaTime);                 
    void draw(sf::RenderWindow& window); 

    sf::Vector2f getCreaturePosition() const;  
    bool isAlive() const;  
    void takeDamage(int damage);
    int getHealth() const;
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    int health;
    float speed;
    int currentPathIndex;
    tileMap& map;
    std::vector<sf::Vector2i> path;
    bool alive;
};  
#endif