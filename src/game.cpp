#include <iostream>
#include <game.hpp>






Game::Game() :
    window_("Tower Defense", 1200, 800),
    map_(window_.getWidth_window(), window_.getHeight_window()),
      economy_(),                   
      editor_(map_),
      towerManager_(map_),  
      creatureManager_(map_, economy_),
      obj_{map_, editor_, towerManager_, creatureManager_, window_, economy_}
{
    switchMode(GameMode::Edit); // mode par default "Edit"
    wireCallBacks();
}


void Game::switchMode(GameMode m)
{
    mode_ = m ; 
    if(mode_ == GameMode::Edit)
    {
        current_ = &editMode_ ; 
        std::cout<<"Edit mode actif..."<<std::endl;
    }
    else
    {
        current_ = &playMode_ ;
        std::cout<<"Play mode est actif..."<<std::endl;  
    }
}

void Game::wireCallBacks()
{
    window_.setEventCallback([this](const sf::Event& event, sf::Vector2i cell_pos){    
        if(event.type ==sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::E) switchMode(GameMode::Edit);
            if(event.key.code == sf::Keyboard::J) switchMode(GameMode::Play);
        }
        if(current_) current_->onEvent(obj_, event, cell_pos);
    });

    window_.setGameLoopCallback([this](sf::Vector2i cell_pos){
        if(current_) current_->onUpdate(obj_, cell_pos);
    });

    window_.setRenderCallback([this](sf::RenderTarget& rt){
        if(current_) current_->onRender(obj_, rt);
    });
}


void Game::run()
{
    window_.run();
}



//je dois ajouter pour le playMode.cpp une methode inBound que j'ajouterai surement dans utils .hpp pour 
//ne pas dupliquer le code a chauqe fois, la methode devoir avoir accees a la taille de la fentre en cellule donc 
//elle deverait y avoir accees sans probleme a partir de la classe tileMap en creeant un petit seteur pour faire 
//les choses proprements !!!! 