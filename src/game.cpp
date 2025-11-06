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

    editor_.keyBoardManager();
    sf::Event e = event;              // copie locale non-const pour l’éditeur
    editor_.eventManager(window_, e); // OK

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

void Game::playMode(const sf::Event& event)
{
    
if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J) {
    mode_ = Game_mode::Play;
    if (!loaded_) {
        if (mapManager::loadJson("/home/aziz-scofeild/TowerDedense/maps//level2.json", map_))
            std::cout << "[OK] Map chargee (Play)\n";
        else
            std::cout << "[ERR] Echec chargement (Play)\n";
        loaded_ = true;
    }
}
   
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) isBuilding_ = true ; 
    if(isBuilding_ == true ){

        auto mouse = sf::Mouse::getPosition(window_);
        sf::Vector2f world = window_.mapPixelToCoords(mouse, window_.getView());
        auto [gx, gy] = Grid::worldToGrid(world,map_.getSizeTile());

        towerManager_.Ghost();
        towerManager_.updateGhost(window_, mouse);

        if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        // Bornes à vérifier selon ta map (par ex. map.getWidth(), map.getHeight()) :
        // if (gx >= map.getWidth() || gy >= map.getHeight()) continue;

        
        if(gx >= 0 || gx <= window_.getWidth_window() || gy>=0 || gy<=window_.getHeight_window())
        {
        if (towerManager_.addTower(window_, mouse)){
            // placé avec succès
            std ::cout << "Tour construite en (" << gx << ", " << gy << ")" << std::endl ;
        } else {
            // son / message “impossible de construire ici”
            std::cout << "Impossible de construire une tour ici !" << std::endl ;
        }
        }
        else std::cout<<"Impossible de construire une tour ici"<<std::endl;

    } 

    }




}

void Game::gamePlayManager(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::E) {
            mode_ = Game_mode::Edit;
            loaded_ = false;        // prêt à recharger la prochaine fois qu’on passe en Play
            std::cout << "Mode EDIT\n";
        }
        if (event.key.code == sf::Keyboard::J) {
            mode_ = Game_mode::Play;
            std::cout << "Mode PLAY\n";
        }
    }

    if (mode_ == Game_mode::Edit) editMode(event);
    if (mode_ == Game_mode::Play) playMode(event);
}

void Game::renderCommon(sf::RenderTarget& rt) 
{
    map_.draw(rt); // NE PAS faire clear/display ici. Juste draw.
    towerManager_.draw(window_);
    towerManager_.drawGhost(window_);
}



void Game::run()
{

    // ici on doit definir les different callBack 
    window_.setEventCallback([this](const sf::Event& e){ this->gamePlayManager(e); } );
    window_.setRenderCallback([this](sf::RenderTarget& rt){ this->renderCommon(rt); });
  
    
    window_.run(); 
}