#include "tileMap.hpp"
#include <iostream>

// Constructeur
tileMap::tileMap(unsigned width, unsigned height, unsigned cell_size)
    : width(width), height(height), cell_size(cell_size)
{
    tiles.resize(width * height);
}

// Accès aux tiles
tile& tileMap::accessTile(unsigned x, unsigned y)
{
    return tiles[y * width + x];
}

const tile& tileMap::accessTile(unsigned x, unsigned y) const
{
    return tiles[y * width + x];
}

// Vérification des limites
bool tileMap::inBounds(unsigned x, unsigned y) const noexcept
{
    return (x < width && y < height);
}

// Peindre une tile
void tileMap::paint(unsigned x, unsigned y, tileType t)
{
    if (inBounds(x, y))
        accessTile(x, y).setType(t);
}

// Convertir coordonnées monde -> cellule
sf::Vector2i tileMap::worldToCell(sf::Vector2f& world) const
{
    if (world.x < 0.f || world.y < 0.f)
        return {-1, -1};

    unsigned cell_x = static_cast<unsigned>(world.x) / cell_size;
    unsigned cell_y = static_cast<unsigned>(world.y) / cell_size;

    if (!inBounds(cell_x, cell_y))
        return {-1, -1};

    return {static_cast<int>(cell_x), static_cast<int>(cell_y)};
}

// Dessiner la map
void tileMap::draw(sf::RenderTarget& rt) const
{
    sf::RectangleShape cell({static_cast<float>(cell_size), static_cast<float>(cell_size)});

    for (unsigned y = 0; y < height; ++y)
    {
        for (unsigned x = 0; x < width; ++x)
        {
            const tile& t = tiles[y * width + x];
            cell.setPosition(static_cast<float>(x * cell_size), static_cast<float>(y * cell_size));
            cell.setFillColor(t.displayColor());
            rt.draw(cell);
        }
    }

    // Dessiner la grille
    const sf::Color lineColor(0, 0, 0, 60);

    for (unsigned x = 0; x <= width; ++x)
    {
        sf::Vertex line[] = {
            sf::Vertex({static_cast<float>(x * cell_size), 0.f}, lineColor),
            sf::Vertex({static_cast<float>(x * cell_size), static_cast<float>(height * cell_size)}, lineColor)
        };
        rt.draw(line, 2, sf::Lines);
    }

    for (unsigned y = 0; y <= height; ++y)
    {
        sf::Vertex line[] = {
            sf::Vertex({0.f, static_cast<float>(y * cell_size)}, lineColor),
            sf::Vertex({static_cast<float>(width * cell_size), static_cast<float>(y * cell_size)}, lineColor)
        };
        rt.draw(line, 2, sf::Lines);
    }
}

// Accesseurs
unsigned tileMap::getWidth() const noexcept
{
    return width;
}

unsigned tileMap::getHeight() const noexcept
{
    return height;
}

unsigned tileMap::getSizeTile() const noexcept
{
    return cell_size;
}


