#pragma once
#include "tower.hpp"

class MediumTower : public Tower {
public:
    MediumTower(int gridX, int gridY, int cellSize);

    void shoot() override;
    void draw(sf::RenderWindow& window) override;
};
