#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "window.hpp"
#include "tileMap.hpp"
#include "mapEditor.hpp"
#include "towerManager.hpp"
#include "creatureManager.hpp"
#include "interfaceGameMode.hpp"
#include "editMode.hpp"
#include "playMode.hpp"
#include "menuMode.hpp"


enum class GameMode {Edit, Play, Menu}; 

class Game
{

public:
    Game() ; 
    ~Game() = default;

    void run(); 

    void switchMode(GameMode m);
    void wireCallBacks(); 


private : 
    void buildMenu();
    void handleMenuEvent(const sf::Event& e);
    void renderMenu(sf::RenderTarget& rt);  

private : 

GameMode mode_ = GameMode::Menu ;  
Window window_ ; 
tileMap map_ ;
mapEditor editor_ ; 
TowerManager towerManager_ ; 
gameEconomy economy_; 
CreatureManager creatureManager_ ; 
GameObject obj_ ; 
IGameMode* current_ = nullptr ; 
EditMode editMode_ ; 
PlayMode playMode_ ;
MenuMode menuMode_ ;
tgui::Gui gui_ ;

};
#endif 