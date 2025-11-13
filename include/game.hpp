#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "tileMap.hpp"
#include "mapEditor.hpp"
#include "towerManager.hpp"
#include "creatureManager.hpp"
#include "interfaceGameMode.hpp"
#include "editMode.hpp"
#include "playMode.hpp"


enum class GameMode {Edit , Play }; 

class Game
{

public:
    Game() ; 
    ~Game() = default;

    void run(); 

    void switchMode(GameMode m);
    void wireCallBacks(); 


     

private : 

GameMode mode_ = GameMode::Edit;  
Window window_ ; 
tileMap map_ ;
mapEditor editor_ ; 
TowerManager towerManager_ ; 
CreatureManager creatureManager_ ; 
GameObject obj_ ; 
IGameMode* current_ = nullptr ; 
EditMode editMode_ ; 
PlayMode playMode_ ;

};
#endif 