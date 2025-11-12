#pragma once
#include <string>
#include "tileMap.hpp"
#include "tile.hpp"

// mapManager : utilitaire de sauvegarde/chargement JSON
class mapManager {
public:
    // Sauvegarde la carte 'm' dans 'path'. Retourne true si OK.
    static bool saveJson(const std::string& path, const tileMap& m);

    // Charge depuis 'path' et remplace totalement 'out' si OK. Retourne true si OK.
    static bool loadJson(const std::string& path, tileMap& out);

    // Variante pratique : charge et retourne par valeur. En cas d'échec, width=0.
    static tileMap loadJson(const std::string& path);

    std::vector<sf::Vector2i> extractPathTiles(const tileMap& map);
};