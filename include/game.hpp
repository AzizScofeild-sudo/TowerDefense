#ifndef __GAME_HPP__
#define __GAME_HPP__

#include<SFML/Graphics.hpp>
#include "mapEditor.hpp"
#include "window.hpp"
#include "tileMap.hpp"
#include "towerManager.hpp"
#include "mapManager.hpp"



// cette class doit avoir comme tresposabilite de gerer la logique du jeu
// elle gere appelle une fenetre ou on dessine la map da ns on appelleera surement TileMap ! 
// on doit gerer les mode de jeu  editeur / player => donc il faut capturer les evenements clavier / souris 
// pour cela on crer une enum classe Mode { EDITOR , PLAYER }

// la calasse doit avoir une lmethode start_game pôur lancer le jeu !
// et avoir une mathode play_mode et edit_mode   
// donc on devra attribuer une foction au callBack de la classe window 


enum class Game_mode {Edit , Play }; 

class Game
{

public:
    Game() ; 
    ~Game() = default;

    void editMode(const sf::Event& event); 
    void playMode(const sf::Event& event); 
    void renderCommon(sf::RenderTarget& rt);

    void gamePlayManager(const sf::Event& event); 

    void run();





    
private : 
Game_mode mode_ = Game_mode::Edit;  
Window window_ ; 
tileMap map_ ;
mapEditor editor_ ; 
TowerManager towerManager_ ; 
bool isBuilding_ = false ;
bool loaded_ = false ; 


};
#endif 