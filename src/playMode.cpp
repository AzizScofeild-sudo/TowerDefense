#include <iostream>
#include "playMode.hpp"
#include "mapManager.hpp"
#include "towerManager.hpp"
#include "window.hpp"
#include "creatureManager.hpp"



void PlayMode::onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i)
{
    //Charger la map a partir du fichier level2.json
       if(loaded_ == false){
        if (mapManager::loadJson("../maps/level2.json", obj.map_))
            {std::cout << "[OK] Map chargee (Play)\n";
            obj.creatureManager_.buildPath();
            }
        else
            std::cout << "[ERR] Echec chargement (Play)\n";

       loaded_ = true ; 
       }
       
    
    //2)Gestion de mode isBuilding : 
    //Remarque on ne doit plus construire quand n'appuis plus sur la touche "B"
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B ) isBuilding_ = true ; 
    else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B) isBuilding_ = false ;

}


void PlayMode::onUpdate(GameObject& obj, sf::Vector2i cell_pos)
{
    if(isBuilding_ == true ){

        obj.towerManager_.Ghost();
        obj.towerManager_.updateGhost(cell_pos);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {        
        if(cell_pos.x >= 0 || static_cast<unsigned>(cell_pos.x) <= obj.window_.getWidth_window()/obj.map_.getSizeTile() || cell_pos.y >= 0 || static_cast<unsigned>(cell_pos.y) <= obj.window_.getHeight_window()/obj.map_.getSizeTile())
        {
        if (obj.towerManager_.addTower(cell_pos)){
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
       
    obj.creatureManager_.update();
    obj.towerManager_.Update(obj.creatureManager_.getCreatures());

}



void PlayMode::onRender(GameObject& obj, sf::RenderTarget& rt)
{
    obj.map_.draw(rt);
    obj.towerManager_.draw(rt); 
    if(isBuilding_) obj.towerManager_.drawGhost(rt);
    obj.creatureManager_.draw(rt);
}