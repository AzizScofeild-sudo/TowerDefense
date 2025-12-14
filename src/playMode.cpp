#include <iostream>
#include "playMode.hpp"
#include "mapManager.hpp"
#include "towerManager.hpp"
#include "window.hpp"
#include "creatureManager.hpp"

void PlayMode::onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i)
{
    // Charger la map à partir du fichier level2.json
    if (!loaded_) {
        if (mapManager::loadJson("../maps/level2.json", obj.map_)) {
            std::cout << "[OK] Map chargée (Play)\n";
            obj.creatureManager_.buildPath();
        } else {
            std::cout << "[ERR] Échec chargement (Play)\n";
        }
        loaded_ = true;
    }

    // Gestion du mode construction
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
        isBuilding_ = true;
    else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
        isBuilding_ = false;

    // Changer le type de tour avec les touches 1,2,3
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) selectedTowerType_ = TowerType::Weak;
        if (event.key.code == sf::Keyboard::Num2) selectedTowerType_ = TowerType::Medium;
        if (event.key.code == sf::Keyboard::Num3) selectedTowerType_ = TowerType::Strong;
    }
}

void PlayMode::onUpdate(GameObject& obj, sf::Vector2i cell_pos)
{
    if (isBuilding_) {
        obj.towerManager_.Ghost();
        obj.towerManager_.updateGhost(cell_pos);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Vérification des limites de la grille
            if (cell_pos.x >= 0 && static_cast<unsigned>(cell_pos.x) < obj.map_.getWidth() &&
                cell_pos.y >= 0 && static_cast<unsigned>(cell_pos.y) < obj.map_.getHeight())
            {
                // Construire la tour du type sélectionné
                if (obj.towerManager_.addTower(cell_pos, selectedTowerType_, obj.economy_)) {
                    std::cout << "Tour construite en (" << cell_pos.x << ", " << cell_pos.y << ") de type ";
                    switch (selectedTowerType_) {
                        case TowerType::Weak:   std::cout << "Weak\n"; break;
                        case TowerType::Medium: std::cout << "Medium\n"; break;
                        case TowerType::Strong: std::cout << "Strong\n"; break;
                    }
                } else {
                    std::cout << "Impossible de construire une tour ici !" << std::endl;
                }
            } else {
                std::cout << "Position hors limites !" << std::endl;
            }
        }
    }

    obj.creatureManager_.update();
    obj.towerManager_.Update(obj.creatureManager_.getCreatures());
}

void PlayMode::onRender(GameObject& obj, sf::RenderTarget& rt)
{
    obj.map_.draw(rt);
    obj.towerManager_.draw(rt); 
    if (isBuilding_) obj.towerManager_.drawGhost(rt);
    obj.creatureManager_.draw(rt);
}
