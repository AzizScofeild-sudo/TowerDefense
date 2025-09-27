#include "tower.hpp"

Tower::Tower(int gridX, int gridY, int cellSize)
    : gridPos(gridX, gridY), cellSize(cellSize), range(50), damage(1)
{
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setPosition(gridX * cellSize, gridY * cellSize);

    rangeCircle.setRadius(range);
    rangeCircle.setFillColor(sf::Color::Transparent);
    rangeCircle.setOutlineThickness(1.f);
    rangeCircle.setOrigin(range, range); //
    rangeCircle.setPosition(shape.getPosition().x + cellSize / 2.f,//
                            shape.getPosition().y + cellSize / 2.f);//
}

void Tower::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(rangeCircle);
}

sf::Vector2i Tower::getGridPosition() const
{
    return gridPos;
}
