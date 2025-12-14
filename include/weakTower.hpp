#pragma once
#include "tower.hpp"

class WeakTower : public Tower {
public:
    WeakTower(sf::Vector2u pos, tileMap& map);
};

