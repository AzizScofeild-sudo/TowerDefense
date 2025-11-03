#ifndef MEDIUMTOWER_HPP
#define MEDIUMTOWER_HPP
#include "tower.hpp"

class MediumTower : public Tower {
public:
    MediumTower(int gridX, int gridY, tileMap& map);

    void shoot(Creature& target) override;
    void draw(sf::RenderWindow& window) override;
};
#endif