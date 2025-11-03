#include "projectile.hpp"
#include "tower.hpp"
#include <cmath>

Projectile::Projectile(const Tower& tower, Creature& target, float speed, int damage)
    : towerPosition(tower), targetCreature(target), speed(speed), damage(damage), hit(false)
{
    // initialiser le membre position
    position = tower.getTowerPosition(); 

    // cercle du projectile
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);

    // direction vers la position initiale de la créature (ligne droite)
    sf::Vector2f targetPos = targetCreature.getCreaturePosition();
    sf::Vector2f dirVec = targetPos - position;
    float distance = std::sqrt(dirVec.x*dirVec.x + dirVec.y*dirVec.y);
    if (distance != 0.f)
        direction = dirVec / distance;
    else
        direction = sf::Vector2f(0.f, 0.f);
}

void Projectile::moveProjectile(float deltaTime) {
    if (hit) return;

    // déplacement projectile
    position += direction * speed * deltaTime;
    shape.setPosition(position);

    // vérifier collision avec la créature
    sf::Vector2f targetPos = targetCreature.getCreaturePosition();
    sf::Vector2f diff = targetPos - position;
    float distance = std::sqrt(diff.x*diff.x + diff.y*diff.y);

    float hitDistance = shape.getRadius() + targetCreature.getCreatureRadius();
    if (distance < hitDistance) 
    hit = true;
}

void Projectile::draw(sf::RenderWindow& window){
    if(hit) return;
    window.draw(shape);
}

// utilise dans tower.cpp pour nettoyer les projectiles
bool Projectile::hasHitTarget()const{
    return hit;
}

// utilise dans tower.cpp pour appliquer les dégats
void Projectile::applyDamage(){
    if(hit){
        targetCreature.takeDamage(damage);
    }
}
