#include "tower.hpp"


Tower::Tower(sf::Vector2u gridPos, tileMap& map): gridPos_(gridPos), map_(map)
{
    int cellSize = map_.getSizeTile();
    tower_shape_.setSize(sf::Vector2f(cellSize, cellSize));
    tower_shape_.setPosition(gridPos.x * cellSize, gridPos.y * cellSize);
}


sf::Vector2u Tower::getTowerPosition() const
{
    return gridPos_;
}


void Tower::draw(sf::RenderWindow& window)
{
    window.draw(tower_shape_);
}
