#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <SFML/Graphics.hpp>
#include "tileMap.hpp"


class Creature {
public:
    Creature(int gridX, int gridY ,tileMap& map ,int health, float speed);

    void move();                 

    void draw(sf::RenderWindow& window); 

    sf::Vector2f getPosition() const;    
    bool isAlive() const;  
    void takeDamage(int damage);
    int getHealth() const;
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    int health;
    float speed;
    int map;
};  
#endif