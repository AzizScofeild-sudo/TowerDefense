#pragma once
#include "tower.hpp"

class StrongTower : public Tower {
public:
    StrongTower(int gridX, int gridY, int cellSize);

    void shoot() override;
    void draw(sf::RenderWindow& window) override;
};
