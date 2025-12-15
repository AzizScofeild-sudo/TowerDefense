#include <iostream>
#include "editMode.hpp"
#include "mapManager.hpp"
#include "mapEditor.hpp" 
#include "window.hpp"






void EditMode::onEvent(GameObject& obj ,const sf::Event& event, sf::Vector2i cell_pos) 
{
    obj.editor_.keyBoardManager();
    sf::Event e = event ;               
    obj.editor_.eventManager(e, cell_pos); 

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F5) 
        {
            mapManager::saveJson("../maps/level2.json", obj.map_);
            std::cout<<"Map enregistrer avec succee"<< std::endl; 
        }
        if (event.key.code == sf::Keyboard::F9) {
            mapManager::loadJson("../maps/level2.json", obj.map_);
            obj.map_.loadTextures();
            std::cout<<"Map chargee avec succeeeeey !"<<std::endl;
        }
    }
}

void EditMode::onUpdate(GameObject& obj, sf::Vector2i cell_pos) 
{

}

void EditMode::onRender(GameObject& obj, sf::RenderTarget& rt) 
{
    obj.map_.draw(rt); 
}