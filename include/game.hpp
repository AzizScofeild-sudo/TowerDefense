#ifndef __GAME_HPP__
#define __GAME_HPP__

#include<SFML/Graphics.hpp>
#include "mapEditor.hpp"
#include "window.hpp"
#include "tileMap.hpp"
#include "towerManager.hpp"
#include "mapManager.hpp"


enum class GameMode {Edit , Play }; 

class Game
{

public:
    Game() ; 
    ~Game() = default;

    void editMode(const sf::Event& event); 
    void playMode(sf::Vector2i cell_pos); 
    void renderCommon(sf::RenderTarget& rt);
    void run();

private : 
GameMode mode_ = GameMode::Edit;  
Window window_ ; 
tileMap map_ ;
mapEditor editor_ ; 
TowerManager towerManager_ ; 
bool isBuilding_ = false ;
bool loaded_ = false ; 
};
#endif 