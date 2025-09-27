#ifndef WEAKTOWER_HPP
#define WEAKTOWER_HPP
#include "tower.hpp"

class WeakTower : public Tower {
public:
    WeakTower(int gridX, int gridY, int cellSize);

    void shoot() override;               
    void draw(sf::RenderWindow& window) override;
};

#endif
