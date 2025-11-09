#ifndef __MAPEDITOR__
#define __MAPEDITOR__

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileMap.hpp"
#include "weakTower.hpp"
#include "mediumTower.hpp"
#include "strongTower.hpp"
#include <vector>
#include <memory>

enum class modeJeuEditor : std::uint8_t
{
    Edit,
    PLay
};

class mapEditor {

public:
    mapEditor(tileMap& map);
    ~mapEditor() = default;
    void keyBoardManager();
    void eventManager(sf::RenderWindow& window, sf ::Event& event); 
    sf::Vector2i worldToCell(sf::RenderWindow& window, sf::Vector2i pixel); 
    void paint(sf::Vector2i cell) ; 
    modeJeuEditor getMode() const noexcept ; 

    // #######zedt les tours #######
    void setTowerType(int type) { towerType_ = type; }
    void placeTower(sf::Vector2i cell);

    std::vector<std::shared_ptr<Tower>> towers_;

private:

    tileMap& map_;
    bool isPainting_ = false;
    tileType paintType_ = tileType::path;
    modeJeuEditor mode_ = modeJeuEditor:: Edit ;

    int towerType_ = 1; // 1 = weak, 2 = medium, 3 = strong
};

#endif