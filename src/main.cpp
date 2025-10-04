#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "tile.hpp"
#include "tileMap.hpp"
#include "weakTower.hpp"
#include "mediumTower.hpp"
#include "strongTower.hpp"
#include "creature.hpp"

// --- Gestion redimensionnement fenêtre ---
sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window) {
    const float windowRatio = (height_window == 0 ) ? 1.f :
        static_cast<float>(width_window) / static_cast<float>(height_window);
    const float viewRatio = view.getSize().x / view.getSize().y ;
    float X = 0.f, Y = 0.f ;
    float portion_x = 1.f , portion_y = 1.f ;

    if(windowRatio > viewRatio) {
        portion_x = viewRatio / windowRatio ;
        X = (1 - portion_x)/2;
    } else if(windowRatio < viewRatio) {
        portion_y = windowRatio / viewRatio ;
        Y = (1-portion_y)/2 ;
    }
    view.setViewport(sf::FloatRect( X , Y , portion_x , portion_y));
    return view ;
}

int main() {
    const unsigned width_window = 1200, height_window = 800;
    const unsigned cell_size = 25;
    unsigned row = height_window / cell_size;
    unsigned col = width_window / cell_size;

    sf::RenderWindow window(sf::VideoMode(width_window,height_window), "Tower Defense");
    window.setFramerateLimit(60);

    sf::View view;
    view.setSize((float)width_window, (float)height_window);
    view.setCenter(width_window/2, height_window/2);
    view = manageWindow(view, window.getSize().x, window.getSize().y);
    window.setView(view);

    // --- TileMap pour éditeur ---
    tileMap map{col , row , cell_size};
    bool isPainting = false;
    tileType paintType = tileType::path;

    // --- Tours et créatures ---
    std::vector<std::shared_ptr<Tower>> towers;
    std::vector<std::shared_ptr<Creature>> creatures;
    int towerType = 1;
    sf::Clock spawnTimer;
    const float spawnInterval = 7.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) {
                view = manageWindow(view, event.size.width, event.size.height);
                window.setView(view);
            }

            // --- Choix du type de tour ---
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) towerType = 1;
                if (event.key.code == sf::Keyboard::Num2) towerType = 2;
                if (event.key.code == sf::Keyboard::Num3) towerType = 3;
            }

            // --- Peinture avec clic gauche ---
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) 
            {
                isPainting = true;
                sf::Vector2f world = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                sf::Vector2i cell = map.worldToCell(world);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) paintType = tileType::ground;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) paintType = tileType::obstacle;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) paintType = tileType::start;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) paintType = tileType::goal;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) paintType = tileType::path;

                if (cell.x >= 0 && cell.y >= 0) {
                    // --- Créer les tours si la case est walkable ---
                    if (map.accessTile(cell.x, cell.y).walkable()) {
                        if (towerType == 1)
                            towers.push_back(std::make_shared<WeakTower>(cell.x, cell.y, map));
                        else if (towerType == 2)
                            towers.push_back(std::make_shared<MediumTower>(cell.x, cell.y, map));
                        else if (towerType == 3)
                            towers.push_back(std::make_shared<StrongTower>(cell.x, cell.y, map));
                    }
                    map.paint(cell.x, cell.y, paintType);
                }
            }

            // --- Peinture continue ---
            if (event.type == sf::Event::MouseMoved && isPainting) {
                sf::Vector2f world = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                sf::Vector2i cell = map.worldToCell(world);
                if (cell.x >= 0 && cell.y >= 0)
                    map.paint(cell.x, cell.y, paintType);
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left) 
            {
                isPainting = false;
            }
        }

        // --- Spawner une créature toutes les 5s ---
        if (spawnTimer.getElapsedTime().asSeconds() >= spawnInterval) {
            creatures.push_back(std::make_shared<Creature>(0, row / 2, map, 100, 0.5f));
            spawnTimer.restart();
        }

        // Déplacer créatures
        for (auto &c : creatures) c->move();

        // --- Rendering ---
        window.clear();
        map.draw(window);
        for (auto& t : towers) t->draw(window);
        for (auto& c : creatures) c->draw(window);
        window.display();
    }
}
