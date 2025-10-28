#include "mapManager.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using nlohmann::json;

// ---------- helpers d'encodage ----------
static int encodeTileType(tileType t) {
    switch (t) {
        case tileType::ground:   return 0;
        case tileType::path:     return 1;
        case tileType::obstacle: return 2;
        case tileType::start:    return 3;
        case tileType::goal:     return 4;
    }
    return 0; // défaut
}

static tileType decodeTileType(int v) {
    switch (v) {
        case 0: return tileType::ground;
        case 1: return tileType::path;
        case 2: return tileType::obstacle;
        case 3: return tileType::start;
        case 4: return tileType::goal;
    }
    return tileType::ground;
}

// ---------- petite API utilitaire pour (ré)initialiser un tileMap ----------
// Si ton tileMap n'a PAS de méthode publique pour changer de taille,
// on utilise l'opérateur d'affectation par défaut : out = tileMap(newW,newH,cell)
static void recreateMap(tileMap& out, unsigned W, unsigned H, unsigned cell) {
    // on reconstruit un objet temporaire et on swap (copie/assign simple)
    tileMap tmp{ W, H, cell };
    out = std::move(tmp);
}

// ---------- save ----------
bool mapManager::saveJson(const std::string& path, const tileMap& m) {
    try {
        json j;
        j["width"]    = m.getWidth();     // colonnes
        j["height"]   = m.getHeight();    // lignes
        j["cellSize"] = m.getSizeTile();

        const unsigned W = m.getWidth();
        const unsigned H = m.getHeight();
        std::vector<int> tiles;
        tiles.reserve(W * H);

        for (unsigned y = 0; y < H; ++y) {
            for (unsigned x = 0; x < W; ++x) {
                const tile& t = m.accessTile(x, y);
                tiles.push_back(encodeTileType(t.getType())); // si tu n'as pas type(), fais un getter ou adapte
                // NOTE: si tu n'as pas de getter type(), utilise un accès public ou ajoute-le :
                // [[nodiscard]] tileType type() const noexcept { return type_; }
            }
        }
        j["tiles"] = tiles;

        std::ofstream f(path);
        if (!f) {
            std::cerr << "mapManager::saveJson: impossible d'ouvrir '" << path << "'\n";
            return false;
        }
        f << j.dump(2);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "mapManager::saveJson: exception: " << e.what() << "\n";
        return false;
    }
}

// ---------- load (in-place) ----------
bool mapManager::loadJson(const std::string& path, tileMap& out) {
    try {
        std::ifstream f(path);
        if (!f) {
            std::cerr << "mapManager::loadJson: impossible d'ouvrir '" << path << "'\n";
            return false;
        }
        json j; f >> j;

        // lecture des champs obligatoires
        if (!j.contains("width") || !j.contains("height") || !j.contains("cellSize") || !j.contains("tiles")) {
            std::cerr << "mapManager::loadJson: champs manquants\n";
            return false;
        }

        unsigned W = j["width"].get<unsigned>();
        unsigned H = j["height"].get<unsigned>();
        unsigned C = j["cellSize"].get<unsigned>();

        const auto& arr = j["tiles"];
        if (!arr.is_array() || arr.size() != W*H) {
            std::cerr << "mapManager::loadJson: taille 'tiles' incohérente\n";
            return false;
        }

        // (ré)initialise la map de sortie
        recreateMap(out, W, H, C);

        // remplissage ligne par ligne
        for (unsigned y = 0; y < H; ++y) {
            for (unsigned x = 0; x < W; ++x) {
                int code = arr[y*W + x].get<int>();
                out.accessTile(x, y).setType(decodeTileType(code));
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "mapManager::loadJson: exception: " << e.what() << "\n";
        return false;
    }
}

// ---------- load (par valeur) ----------
tileMap mapManager::loadJson(const std::string& path) {
    tileMap empty{ 0, 0, 0 }; // au cas où; nécessite un ctor (0,0,0)
    bool ok = loadJson(path, empty);
    if (!ok) {
        return tileMap{ 0, 0, 0 };
    }
    return empty;
}
