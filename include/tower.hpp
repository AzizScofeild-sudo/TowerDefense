#ifndef TOWER_HPP
#define TOWER_HPP


#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "tileMap.hpp"
#include "tile.hpp"

#include "creature.hpp"
#include "projectile.hpp"




class Tower {
public :
    virtual ~Tower() = default;

    void draw(sf::RenderTarget& window);              
    sf::Vector2f getTowerPosition() const; 
    sf::RectangleShape geTowerShape(){return tower_shape_;} ///??????

    virtual void update(float deltaTime, const std::vector<std::shared_ptr<Creature>>& creatures); //////////

    int getCost() const { return cost_; } 

protected :
    Tower(sf::Vector2u gridPos, tileMap& map, float range, int damage, float fireRate, float projectileSpeed,int cost); // ajout range ....
    void shoot(std::shared_ptr<Creature> target); //////
    std::shared_ptr<Creature> findTarget(const std::vector<std::shared_ptr<Creature>>& creatures);//////////



protected :

    tileMap& map_ ;
    sf::RectangleShape tower_shape_;
    sf::CircleShape rangeCircle; ////////
    sf::Vector2u gridPos_;
    float size_tower  ;
   

    //
    float range;
    int damage;
    float fireRate;
    float cooldown;
    float projectileSpeed;

    int cost_;

    std::weak_ptr<Creature> currentTarget; //weak ptr parece que la tour ne possède pas la créature
    std::vector<std::unique_ptr<Projectile>> projectiles; //unique ptr parce que la tour possède les projectiles


};

#endif