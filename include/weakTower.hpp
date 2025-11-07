#pragma once
#include "tower.hpp"

class WeakTower : public Tower {
public:
    WeakTower(int gridX, int gridY, tileMap& map);
    ~WeakTower() = default;
};
