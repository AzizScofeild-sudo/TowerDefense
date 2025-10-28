#ifndef __MAPEDITOR__
#define __MAPEDITOR__

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileMap.hpp"

enum class modeJeuEditor : std::uint8_t
{
    Edit,
    PLay
};

class mapEditor {

public:
    mapEditor(tileMap& map);
    ~mapEditor() = default;
    void keyBoardManager();
    void eventManager(sf::RenderWindow& window, sf ::Event& event); 
    sf::Vector2i worldToCell(sf::RenderWindow& window, sf::Vector2i pixel); 
    void paint(sf::Vector2i cell) ; 
    modeJeuEditor getMode() const noexcept ; 

private:

    tileMap& map_;
    bool isPainting_ = false;
    tileType paintType_ = tileType::path;
    modeJeuEditor mode_ = modeJeuEditor:: Edit ;
};

#endif