#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "creature.hpp"

class Tower; // déclaration anticipée parceque on a un membre référence vers Tower et pour dire au compilateur que la classe existe

class Projectile {
public:
    Projectile(const Tower& towerPosition, Creature& target,float speed, int damage);
    void moveProjectile(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool hasHitTarget()const;
    void applyDamage();

private:
    const Tower& towerPosition;
    sf::CircleShape shape;
    sf::Vector2f position;
    Creature& targetCreature;
    float speed;
    int damage;
    bool hit;
    sf::Vector2f direction;
};

#endif