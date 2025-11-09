#include "tower.hpp"
#include <cmath>
#include <algorithm>

Tower::Tower(int gridX, int gridY, tileMap& map, float range, int damage, float fireRate, float projectileSpeed)
    : map(map), gridPos(gridX, gridY), range(range), damage(damage),
      fireRate(fireRate), cooldown(0.f), projectileSpeed(projectileSpeed)
{
    int cellSize = map.getSizeTile();
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setPosition(gridX * cellSize, gridY * cellSize);
    shape.setFillColor(sf::Color::Blue);

    rangeCircle.setRadius(range);
    rangeCircle.setFillColor(sf::Color::Transparent);
    rangeCircle.setOutlineThickness(1.f);
    rangeCircle.setOutlineColor(sf::Color::White);
    rangeCircle.setOrigin(range, range);
    rangeCircle.setPosition(shape.getPosition().x + cellSize / 2.f,
                            shape.getPosition().y + cellSize / 2.f);
}

// retourne la position au centre de la tour pour la utilise comme point de depart des projectiles
sf::Vector2f Tower::getTowerPosition() const {
    int cellSize = map.getSizeTile();
    return sf::Vector2f(gridPos.x * cellSize + cellSize / 2.f,
                        gridPos.y * cellSize + cellSize / 2.f);
}

void Tower::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(rangeCircle);
    for (auto& p : projectiles)
        p->draw(window);
}

//methode update pour mise a jour de la tour chaque frame
void Tower::update(float deltaTime, const std::vector<std::shared_ptr<Creature>>& creatures) {
    cooldown -= deltaTime;
    if (cooldown < 0.f)
        cooldown = 0.f;

    // verifie si la creature visee est toujours valide
    std::shared_ptr<Creature> target = currentTarget.lock();
    sf::Vector2f towerPos = getTowerPosition();

    if (target) {
        if (!target->isAlive()) {
            currentTarget.reset();
            target.reset();
        } else {
            sf::Vector2f targetPos = target->getCreaturePosition();
            float dist = std::hypot(towerPos.x - targetPos.x, towerPos.y - targetPos.y);
            if (dist > range)
                currentTarget.reset();
        }
    }

    // rechercher une nouvelle creature si aucune est visee
    if (!target)
        target = findTarget(creatures);

    // lorseque cooldown <=0 tire sur la creature visee
    if (target && cooldown <= 0.f && target->isAlive()) {
        shoot(target);
        cooldown = fireRate; 
    }

    // mettre à jour les projectiles
    for (auto& p : projectiles)
        p->moveProjectile(deltaTime);

    // supprimer les projectiles ayant atteint la creature
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [](const std::unique_ptr<Projectile>& p) { return p->hasHitTarget(); }),
        projectiles.end());
}

// findTarget pour trouver la creature la plus proche dans le rayon 
std::shared_ptr<Creature> Tower::findTarget(const std::vector<std::shared_ptr<Creature>>& creatures) {
    sf::Vector2f towerPos = getTowerPosition();
    std::shared_ptr<Creature> closest = nullptr;
    float minDist = range;

    for (auto& c : creatures) {
        if (c && c->isAlive()) {
            sf::Vector2f pos = c->getCreaturePosition();
            float dist = std::hypot(towerPos.x - pos.x, towerPos.y - pos.y);
            if (dist < range && dist < minDist) {
                minDist = dist;
                closest = c;
            }
        }
    }
    if (closest)
        currentTarget = closest;
    return closest;
}

// shoot pour cree un projectile 
void Tower::shoot(std::shared_ptr<Creature> target) {
    if (!target || !target->isAlive()) return;
    projectiles.push_back(std::make_unique<Projectile>(*this, target, projectileSpeed, damage));
}


/* float Tower::getRange() const {
    return range;
}
int Tower::getDamage() const {
    return damage;
} */