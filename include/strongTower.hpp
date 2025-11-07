#pragma once
#include "tower.hpp"

class StrongTower : public Tower {
public:
    StrongTower(int gridX, int gridY, tileMap& map);
    ~StrongTower() = default;
};
