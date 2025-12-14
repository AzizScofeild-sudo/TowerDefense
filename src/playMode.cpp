#include <iostream>
#include <string>

#include "playMode.hpp"
#include "mapManager.hpp"
#include "towerManager.hpp"
#include "window.hpp"
#include "creatureManager.hpp"

void PlayMode::onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i)
{
    // Chargement de la map
    if (!loaded_) {
        if (mapManager::loadJson("../maps/level2.json", obj.map_)) {
            std::cout << "[OK] Map chargée (Play)\n";
            obj.creatureManager_.buildPath();
        } else {
            std::cout << "[ERR] Échec chargement (Play)\n";
        }

        // INIT HUD MONEY
    if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        std::cout << "ERREUR: police non chargée\n";
    }



        moneyText_.setFont(font_);
        moneyText_.setCharacterSize(22);
        moneyText_.setFillColor(sf::Color::Yellow);
        moneyText_.setPosition(10.f, 10.f);

        loaded_ = true;
    }

    // Mode construction
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
        isBuilding_ = true;
    else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
        isBuilding_ = false;

    // Sélection type de tour
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
            if (cell_pos.x >= 0 && static_cast<unsigned>(cell_pos.x) < obj.map_.getWidth() &&
                cell_pos.y >= 0 && static_cast<unsigned>(cell_pos.y) < obj.map_.getHeight())
            {
                obj.towerManager_.addTower(cell_pos, selectedTowerType_, obj.economy_);
            }
        }
    }

    obj.creatureManager_.update();
    obj.towerManager_.Update(obj.creatureManager_.getCreatures());

    // UPDATE HUD MONEY
    moneyText_.setString(
        "Money : " + std::to_string(obj.economy_.getMoney())
    );
}

void PlayMode::onRender(GameObject& obj, sf::RenderTarget& rt)
{
    obj.map_.draw(rt);
    obj.towerManager_.draw(rt);
    if (isBuilding_) obj.towerManager_.drawGhost(rt);
    obj.creatureManager_.draw(rt);

    // DRAW HUD
    rt.draw(moneyText_);
}
