#include "tile.hpp"
#include<iostream>




tile::tile()
{
    std::cout << " ON EST LAAAA !!!!" << std::endl;
}


void tile::setType(tileType newType) noexcept
{
    type = newType ;
    buildable = (newType == tileType::ground) ;
}

bool tile::walkable() const noexcept
{
    return (type == tileType::path || type == tileType::start || type == tileType::goal);
}


sf::Color tile::displayColor() const  noexcept
{
    switch (type)
    {
            case tileType::ground:   return sf::Color(30, 120, 30);   // vert
            case tileType::path:     return sf::Color(180,140, 90);   // brun
            case tileType::obstacle: return sf::Color(60,  60,  60);  // gris
            case tileType::start:    return sf::Color(80, 200, 80);   // vert vif
            case tileType::goal:     return sf::Color(200, 80,  80);  // rouge
    
    default:
            return sf::Color::Magenta; // fallback, ne devrait pas arriver
    };
}

