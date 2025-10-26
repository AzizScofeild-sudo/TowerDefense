#include "tower.hpp"
#include <cmath>

Tower::Tower(int gridX, int gridY,tileMap& map)
    : map(map), gridPos(gridX, gridY), range(50), damage(1)
{
    int cellSize=map.getSizeTile();
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setPosition(gridX * cellSize, gridY * cellSize);

    rangeCircle.setRadius(range);
    rangeCircle.setFillColor(sf::Color::Transparent);
    rangeCircle.setOutlineThickness(1.f);
    rangeCircle.setOrigin(range, range); //
    rangeCircle.setPosition(shape.getPosition().x + cellSize / 2.f, 
                            shape.getPosition().y + cellSize / 2.f);
}

void Tower::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(rangeCircle);
}

sf::Vector2i Tower::getTowerPosition() const
{
    return gridPos;
}
 
bool Tower::isCreatureInRange(const Creature& creature) const
{
    sf::Vector2f towerCenter = rangeCircle.getPosition();
    sf::Vector2f creaturePos = creature.getCreaturePosition();

    float dx = towerCenter.x - creaturePos.x;
    float dy = towerCenter.y - creaturePos.y;
    float distance= std::sqrt(dx * dx + dy * dy);
    return distance<= rangeCircle.getRadius();
}
