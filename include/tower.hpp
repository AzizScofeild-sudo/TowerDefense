#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "creature.hpp"
#include "projectile.hpp"
#include "tileMap.hpp"

class Tower {
public:
    Tower(int gridX, int gridY, tileMap& map, float range, int damage, float fireRate, float projectileSpeed);

    void update(float deltaTime, const std::vector<std::shared_ptr<Creature>>& creatures);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getTowerPosition() const;
/*     float getRange() const;
    int getDamage() const; */

protected:
    void shoot(std::shared_ptr<Creature> target); 
    std::shared_ptr<Creature> findTarget(const std::vector<std::shared_ptr<Creature>>& creatures);

    tileMap& map;
    sf::Vector2i gridPos;
    sf::RectangleShape shape;
    sf::CircleShape rangeCircle;

    float range;
    int damage;
    float fireRate;
    float cooldown;
    float projectileSpeed;

    std::weak_ptr<Creature> currentTarget; //weak ptr parece que la tour ne possède pas la créature
    std::vector<std::unique_ptr<Projectile>> projectiles; //unique ptr parce que la tour possède les projectiles
};
