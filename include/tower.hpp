#ifndef TOWER_HPP
#define TOWER_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tileMap.hpp"
#include "creature.hpp"
#include "projectile.hpp"

class Tower {
public:
    Tower(int gridX, int gridY, tileMap& map);

    virtual void draw(sf::RenderWindow& window);  
    virtual void shoot(Creature& target); 
    virtual void updateFrame(float deltaTime); 
        
    const std::vector<std::unique_ptr<Projectile>>& getProjectiles() const { return projectiles; }
    sf::Vector2f getTowerPosition() const; 
    float getRange() const;
    int getDamage() const; //
    /* bool isCreatureInRange(const Creature& creature) const; */
protected:
    tileMap& map;
    sf::RectangleShape shape;
    sf::CircleShape rangeCircle;
    sf::Vector2i gridPos;
    int range;
    int damage;
    std::vector<std::unique_ptr<Projectile>> projectiles; //std::unique_ptr parceque un seul propriétaire qui est la tour

    float fireRate; 
    float fireCooldown;
};

#endif