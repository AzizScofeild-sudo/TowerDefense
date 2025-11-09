#include "game.hpp"
#include <iostream>



Game::Game(): 
window_("Tower Defense", 1200, 800), 
map_(window_.getWidth_window(), window_.getHeight_window()),
editor_(map_),
towerManager_ (map_)
{

}

void Game::editMode(const sf::Event& event) {
    //1)Gestion du mode (Edit,Play) via le clavier : 
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
    {
        mode_ = GameMode::Edit;
        std::cout<<"Edit mode !" << std::endl;

    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J )
    {
        mode_ = GameMode::Play;
        std::cout<<"Play mode !" << std::endl;

    }
    //
    //2)Gestion de mode isBuilding : 
    //Remarque on ne doit plus construire quand n'appuis plus sur la touche "B"
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B ) isBuilding_ = true ; 
    else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B) isBuilding_ = false ;
    //
    if(mode_ == GameMode::Edit){
    loaded_ = false ; 
    editor_.keyBoardManager();
    sf::Event e = event;              
    editor_.eventManager(window_, e); 

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F5) 
        {
            mapManager::saveJson("/home/aziz-scofeild/TowerDedense/maps/level2.json", map_);
            std::cout<<"Map enregistrer avec succee"<< std::endl; 
        }
        if (event.key.code == sf::Keyboard::F9) {
            mapManager::loadJson("/home/aziz-scofeild/TowerDedense/maps/level2.json", map_);
            std::cout<<"Map chargee avec succeeeeey !"<<std::endl;
        }
    }
    }
    else return ; 
}

void Game::playMode(sf::Vector2i cell_pos)
{ 
    if (mode_ == GameMode::Play) {

       if(loaded_ == false){
        if (mapManager::loadJson("/home/aziz-scofeild/TowerDedense/maps//level2.json", map_))
            std::cout << "[OK] Map chargee (Play)\n";
        else
            std::cout << "[ERR] Echec chargement (Play)\n";
       }
       loaded_ = true ; 

    if(isBuilding_ == true ){

        towerManager_.Ghost();
        towerManager_.updateGhost(window_, cell_pos);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {        
        if(cell_pos.x >= 0 || static_cast<unsigned>(cell_pos.x) <= window_.getWidth_window()/map_.getSizeTile() || cell_pos.y >= 0 || static_cast<unsigned>(cell_pos.y) <= window_.getHeight_window()/map_.getSizeTile())
        {
        if (towerManager_.addTower(window_, cell_pos)){
            // placé avec succès           
            std ::cout << "Tour construite en (" << cell_pos.x << ", " << cell_pos.y << ")" << std::endl ;
        } else {
            // son / message “impossible de construire ici”
            std::cout << "Impossible de construire une tour ici !" << std::endl ;
        }
        }
        else std::cout<<"Impossible de construire une tour ici"<<std::endl;

           } 
       }
    }
    else return ; 
}


void Game::renderCommon(sf::RenderTarget& rt) 
{
    map_.draw(rt); // NE PAS faire clear/display ici. Juste draw.
    towerManager_.draw(window_);
    if(isBuilding_) towerManager_.drawGhost(window_);
}
void Game::run()
{
    // ici on doit definir les different callBack 
    window_.setEventCallback([this](const sf::Event& e){ this->editMode(e); });
    window_.setGameLoopCallback([this](sf::Vector2i cell_pos){ this->playMode(cell_pos); } );
    window_.setRenderCallback([this](sf::RenderTarget& rt){ this->renderCommon(rt); });

    window_.run(); 
}

// Creer une partie sur onEvent() qui s'occupe des different mode (edit or play) , isBuilding, buildTowerNow 'mdr'

// Important : je veux esseyer un petit truc : 
// je veux qu on maintient al touche "B" on construit et une fois relache on ne construit plus
// ce qui m'obligera a supprimer l'attribut "bool isBuilding"