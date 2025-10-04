#ifndef __TILEMAP__
#define __TILEMAP__

#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class tileMap
{
public:
    ~tileMap() = default;

    // Constructeur
    tileMap(unsigned width, unsigned height, unsigned cell_size);

    // Accès aux tiles
    tile& accessTile(unsigned x, unsigned y);
    const tile& accessTile(unsigned x, unsigned y) const;

    // Vérification des limites
    bool inBounds(unsigned x, unsigned y) const noexcept;

    // Peindre une tile
    void paint(unsigned x, unsigned y, tileType t);

    // Convertir coordonnées monde -> cellule
    sf::Vector2i worldToCell(sf::Vector2f& world) const;

    // Dessiner la map
    void draw(sf::RenderTarget& rt) const;


    // Accesseurs
    unsigned getWidth() const noexcept;
    unsigned getHeight() const noexcept;
    unsigned getSizeTile() const noexcept;

private:
    unsigned width; 
    unsigned height;
    unsigned cell_size;
    std::vector<tile> tiles;
};

#endif
