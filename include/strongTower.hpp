#ifndef STRONGTOWER_HPP
#define STRONGTOWER_HPP
#include "tower.hpp"

class StrongTower : public Tower {
public:
    StrongTower(int gridX, int gridY, int cellSize);

    void shoot() override;
    void draw(sf::RenderWindow& window) override;
};
#endif