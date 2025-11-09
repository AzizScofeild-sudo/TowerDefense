#pragma once
#include "tower.hpp"

class MediumTower : public Tower {
public:
    MediumTower(int gridX, int gridY, tileMap& map);
    ~MediumTower() = default;
};
