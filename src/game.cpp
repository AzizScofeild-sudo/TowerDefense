#include <iostream>
#include <game.hpp>






Game::Game() :
    window_("Tower Defense", 1200, 800),
    map_(window_.getWidth_window(), window_.getHeight_window()),
    economy_(),                   
    editor_(map_),
    towerManager_(map_),  
    creatureManager_(map_, economy_),
    gui_(window_),
    obj_{map_, editor_, towerManager_, creatureManager_, window_, economy_, gui_}
    
{

    obj_.requestEditMode = [this]{ switchMode(GameMode::Edit); };
    obj_.requestPlayMode = [this]{ switchMode(GameMode::Play); };
    obj_.requestMenuMode = [this]{ switchMode(GameMode::Menu); }; // si tu veux

    buildMenu();
    if (!map_.loadTextures()) {
        std::cerr << "[WARN] Textures non chargees, fallback couleur.\n";
    }
    switchMode(GameMode::Menu); // mode par default "Edit"
    wireCallBacks();
}


void Game::switchMode(GameMode m)
{
    // 1) Si on QUITTE le menu -> on nettoie l’UI
    if (mode_ == GameMode::Menu && m != GameMode::Menu) {
        gui_.removeAllWidgets();
    }

    mode_ = m;

    if (mode_ == GameMode::Menu) {
        current_ = &menuMode_;
        menuMode_.onEnter(obj_); // construit widgets
    }
    else if (mode_ == GameMode::Edit) {
        current_ = &editMode_;
    }
    else {
        current_ = &playMode_;
    }
}



void Game::wireCallBacks()
{
    window_.setEventCallback([this](const sf::Event& event, sf::Vector2i cell_pos){    
        gui_.handleEvent(event);
        if(event.type ==sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) switchMode(GameMode::Menu);
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

void Game::buildMenu()
{
    gui_.removeAllWidgets();

    auto panel = tgui::Panel::create({"40%", "30%"});
    panel->setPosition({"30%", "35%"}); // centré
    gui_.add(panel);

    auto btnEdit = tgui::Button::create("Edit Mode");
    btnEdit->setSize({"80%", "30%"});
    btnEdit->setPosition({"10%", "15%"});
    panel->add(btnEdit);

    auto btnPlay = tgui::Button::create("Play Mode");
    btnPlay->setSize({"80%", "30%"});
    btnPlay->setPosition({"10%", "55%"});
    panel->add(btnPlay);

    btnEdit->onPress([this]{
        mode_ = GameMode::Edit;
        gui_.removeAllWidgets();     // on quitte le menu
        // si besoin : map_.loadTextures(); etc.
    });

    btnPlay->onPress([this]{
        mode_ = GameMode::Play;
        gui_.removeAllWidgets();
        // si besoin : charger map ici (ou au 1er update Play)
    });
}




//je dois ajouter pour le playMode.cpp une methode inBound que j'ajouterai surement dans utils .hpp pour 
//ne pas dupliquer le code a chauqe fois, la methode devoir avoir accees a la taille de la fentre en cellule donc 
//elle deverait y avoir accees sans probleme a partir de la classe tileMap en creeant un petit seteur pour faire 
//les choses proprements !!!! 