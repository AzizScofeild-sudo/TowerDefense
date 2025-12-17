#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Tower;
class Creature;

class Projectile {
public:
    Projectile(const Tower& tower, std::shared_ptr<Creature> target, float speed, int damage);

    void moveProjectile(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool hasHitTarget() const { return hit; }

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    int damage;
    bool hit;

    std::weak_ptr<Creature> targetCreature;
};
