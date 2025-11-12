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
    mapEditor(tileMap& map); // REtirer le constructeru et passer les methodes en static !!!!
    ~mapEditor() = default;
    void keyBoardManager();  // Passer cette methode sur une class CLavier ! 
    void eventManager(sf ::Event& event, sf::Vector2i cell_pos); 
    void paint(sf::Vector2i cell_pos); 


private:

    tileMap& map_;
    bool isPainting_ = false;
    tileType paintType_ = tileType::path;
    
    
};

#endif