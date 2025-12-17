#include <iostream>
#include "playMode.hpp"
#include "mapManager.hpp"
#include "towerManager.hpp"
#include "window.hpp"
#include "creatureManager.hpp"
#include "playerHealth.hpp"


void PlayMode::onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i)
{
    // Charger la map à partir du fichier level2.json
    if (!loaded_) {
        if (mapManager::loadJson("../maps/level2.json", obj.map_)) {
            std::cout << "[OK] Map chargée (Play)\n";
            obj.map_.loadTextures();
            obj.creatureManager_.buildPath();
        } else {
            std::cout << "[ERR] Échec chargement (Play)\n";
        }
        
        if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
        {
        std::cout << "ERREUR: police non chargée\n";
       }

    // Money
    moneyText_.setFont(font_);
    moneyText_.setCharacterSize(22);
    moneyText_.setFillColor(sf::Color::Yellow);
    moneyText_.setPosition(10.f, 10.f);

    // Tower info
    towerText_.setFont(font_);
    towerText_.setCharacterSize(22);
    towerText_.setFillColor(sf::Color::Yellow);
    towerText_.setPosition(10.f, obj.window_.getSize().y - 60.f); // un peu plus haut pour laisser la place

    // Tour sélectionnée
    selectedTowerText_.setFont(font_);
    selectedTowerText_.setCharacterSize(22);
    selectedTowerText_.setFillColor(sf::Color::Yellow);
    selectedTowerText_.setPosition(10.f, obj.window_.getSize().y - 30.f); // en bas
    selectedTowerText_.setString("Selected: Weak Tower 50$"); // texte initial

    gameOverText_.setFont(font_);
    gameOverText_.setString("GAME OVER");
    gameOverText_.setCharacterSize(128);
    gameOverText_.setFillColor(sf::Color::Red);
    gameOverText_.setStyle(sf::Text::Bold);

    // centrer le texte
    sf::FloatRect bounds = gameOverText_.getLocalBounds();
    gameOverText_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    gameOverText_.setPosition(
    obj.window_.getSize().x / 2.f,
    obj.window_.getSize().y / 2.f 
    );

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
    if (gameOver_) return;

    const float dt = dtClock_.restart().asSeconds();
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


    int leaked = obj.creatureManager_.update(dt);
    if (leaked > 0) obj.playerHp_.lose(leaked);

    if (obj.playerHp_.isDead())
    {
        gameOver_ = true;
        std::cout << "GAME OVER !"<<std::endl;
        return;
    }

    obj.towerManager_.Update(obj.creatureManager_.getCreatures());
    moneyText_.setString("Money : " + std::to_string(obj.economy_.getMoney()) + "$");
    towerText_.setString("Tower Info: weak 50$ / medium 100$ / strong 150$");
}

void PlayMode::onRender(GameObject& obj, sf::RenderTarget& rt)
{
    obj.map_.draw(rt);
    obj.towerManager_.draw(rt); 
    if (isBuilding_) obj.towerManager_.drawGhost(rt);
    obj.creatureManager_.draw(rt);
    rt.draw(moneyText_);
    obj.playerHp_.draw(rt);
    if(gameOver_) rt.draw(gameOverText_);

}
