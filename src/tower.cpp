#include "tower.hpp"


Tower::Tower(sf::Vector2u gridPos, tileMap& map): gridPos_(gridPos), map_(map)
{
    int cellSize = map_.getSizeTile(); // Retirer l'attribus map_ p
    tower_shape_.setSize(sf::Vector2f(3*cellSize, 3*cellSize));
    tower_shape_.setPosition((gridPos.x-1) * cellSize, (gridPos.y-1) * cellSize);
}


sf::Vector2u Tower::getTowerPosition() const
{
    return gridPos_;
}


void Tower::draw(sf::RenderTarget& window)
{
    window.draw(tower_shape_);
}
