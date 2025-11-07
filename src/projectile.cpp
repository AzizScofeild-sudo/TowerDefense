#include "projectile.hpp"
#include "tower.hpp"
#include "creature.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(const Tower& tower, std::shared_ptr<Creature> target, float speed, int damage)
    : targetCreature(target), speed(speed), damage(damage), hit(false)
{
    position = tower.getTowerPosition();

    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(5.f, 5.f);
    shape.setPosition(position);


    //lock transforme le weak_ptr en shared_ptr temporaire
    if (auto tgt = targetCreature.lock()) {
        sf::Vector2f targetPos = tgt->getCreaturePosition();
        sf::Vector2f dirVec = targetPos - position;
        float distance = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
        if (distance != 0.f)
            direction = dirVec / distance; //vecteur unitaire pour que le deplacement soit proportionnel à speed*deltaTime
        else
            direction = sf::Vector2f(0.f, 0.f);
    }
}

void Projectile::moveProjectile(float deltaTime) {
    if (hit) return;

    auto tgt = targetCreature.lock();
    if (!tgt || !tgt->isAlive()) {
        hit = true;
        return;
    }

    // mise à jour de la position
    position += direction * speed * deltaTime;
    shape.setPosition(position);

    // calcul distance à la cible
    sf::Vector2f targetPos = tgt->getCreaturePosition();
    sf::Vector2f diff = targetPos - position;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    // verifier la collision entre projectile et creature
    float hitDistance = shape.getRadius() + tgt->getCreatureRadius();

    if (distance < hitDistance) {
        hit = true;
        tgt->takeDamage(damage);
    }
}

void Projectile::draw(sf::RenderWindow& window) {
    if (!hit)
        window.draw(shape);
}
