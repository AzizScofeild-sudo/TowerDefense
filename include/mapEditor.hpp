#ifndef __MAPEDITOR__
#define __MAPEDITOR__

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileMap.hpp"

class mapEditor {
public:
    mapEditor(tileMap& map);
    ~mapEditor() = default;
    void keyBoardManager();
    void eventManager(sf::RenderWindow& window, sf ::Event& event); 
    sf::Vector2i worldToCell(sf::RenderWindow& window, sf::Vector2i pixel); 
    void paint(sf::Vector2i cell) ; 

    


private:

    tileMap& map;
    bool isPainting = false;
    tileType paintType = tileType::path;
};

#endif