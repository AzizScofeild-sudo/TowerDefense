#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>  
#include <cmath>      
#include "tileMap.hpp"



namespace Grid {

    inline unsigned tileSize = 1 ;  
    inline void setTileSize( unsigned tileSizeFromMap) { tileSize = tileSizeFromMap; }

inline sf::Vector2i worldToGrid(const sf::Vector2f& world) {
    if (tileSize == 0) return { -1, -1 }; // sécurité contre une division par zéro

    int gx = static_cast<int>(std::floor(world.x / static_cast<float>(tileSize)));
    int gy = static_cast<int>(std::floor(world.y / static_cast<float>(tileSize)));


    gx = std::max(0, gx);
    gy = std::max(0, gy);

    return { gx, gy };
}



inline sf::Vector2f gridToWorld(unsigned gx, unsigned gy) {
    
    return {
        static_cast<float>(gx * tileSize),
        static_cast<float>(gy * tileSize)
    };
}

}