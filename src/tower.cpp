#include "tower.hpp"
#include <cmath>

Tower::Tower(int gridX, int gridY,tileMap& map)
    : map(map), gridPos(gridX, gridY), range(50), damage(1)
{
    int cellSize=map.getSizeTile();
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setPosition(gridX * cellSize, gridY * cellSize);

    rangeCircle.setRadius(range);
    rangeCircle.setFillColor(sf::Color::Transparent);
    rangeCircle.setOutlineThickness(1.f);
    rangeCircle.setOrigin(range, range); 
    rangeCircle.setPosition(shape.getPosition().x + cellSize / 2.f, 
                            shape.getPosition().y + cellSize / 2.f);
}

void Tower::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(rangeCircle);
}

// position en pixels du centre de la tour
sf::Vector2f Tower::getTowerPosition() const
{
    int cellSize = map.getSizeTile();
    return sf::Vector2f(gridPos.x * cellSize + cellSize / 2.f,
                        gridPos.y * cellSize + cellSize / 2.f);
    
}

//projetile(towerposition, creature cible, vitesse, degat)
void Tower::shoot(Creature& target)
{
    projectiles.push_back(std::make_unique<Projectile>(*this, target, 300.f, damage));
}

//mettre a jour les projectiles
void Tower::updateFrame(float deltatime)
{
    for(auto& p: projectiles){
        p->moveProjectile(deltatime);
        if(p->hasHitTarget()){
            p->applyDamage();
        }
    }
    
    //suprimer les projectiles qui ont touché leur cible
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& p) { return p->hasHitTarget(); }),  //return condition de suppression
        projectiles.end()
    );
}

//utilisé dans main.cpp pour vérifier la portée
float Tower::getRange() const
{
    return rangeCircle.getRadius();
}

//utilisé dans main.cpp pour obtenir les dégats
int Tower::getDamage() const
{
    return damage;
}


