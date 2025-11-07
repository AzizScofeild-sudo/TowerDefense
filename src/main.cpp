#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <iostream>
#include <cmath>

#include "tile.hpp"
#include "tileMap.hpp"
#include "weakTower.hpp"
#include "mediumTower.hpp"
#include "strongTower.hpp"
#include "creature.hpp"
#include "mapManager.hpp"
#include "projectile.hpp"

// --- Gestion du redimensionnement de la fenêtre ---
sf::View manageWindow(sf::View view, unsigned width_window, unsigned height_window) {
    const float windowRatio = (height_window == 0) ? 1.f :
        static_cast<float>(width_window) / static_cast<float>(height_window);
    const float viewRatio = view.getSize().x / view.getSize().y;
    float X = 0.f, Y = 0.f;
    float portion_x = 1.f, portion_y = 1.f;

    if (windowRatio > viewRatio) {
        portion_x = viewRatio / windowRatio;
        X = (1 - portion_x) / 2;
    } else if (windowRatio < viewRatio) {
        portion_y = windowRatio / viewRatio;
        Y = (1 - portion_y) / 2;
    }
    view.setViewport(sf::FloatRect(X, Y, portion_x, portion_y));
    return view;
}

int main() {
    const unsigned width_window = 1200, height_window = 800;
    const unsigned cell_size = 25;
    unsigned row = height_window / cell_size;
    unsigned col = width_window / cell_size;

    // --- Créer le dossier "map" si nécessaire ---
    if (!std::filesystem::exists("map"))
        std::filesystem::create_directory("map");

    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "Tower Defense");
    window.setFramerateLimit(60);

    sf::View view;
    view.setSize((float)width_window, (float)height_window);
    view.setCenter(width_window / 2, height_window / 2);
    view = manageWindow(view, window.getSize().x, window.getSize().y);
    window.setView(view);

    // --- Initialisation de la carte ---
    tileMap map{col, row, cell_size};
    mapManager manager; 
    std::string mapPath = "/home/achraf/project/TowerDefense/map/saveMap.json";

    if (std::filesystem::exists(mapPath)) {
        if (manager.loadJson(mapPath, map))
            std::cout << "Map loaded successfully.\n";
        else
            std::cout << "Failed to load map.\n";
    }

    std::vector<sf::Vector2i> path = manager.extractPathTiles(map);
    if (path.empty())
        std::cout << "Aucun chemin (tileType::path) trouvé dans la map !\n";

    // --- Listes principales ---
    std::vector<std::shared_ptr<Tower>> towers;
    std::vector<std::shared_ptr<Creature>> creatures;


    bool isPainting = false;
    tileType paintType = tileType::path;
    int towerType;

    sf::Clock spawnTimer, deltaClock;
    const float spawnInterval = 2.f;

    while (window.isOpen()) {
        float frameTime = deltaClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) {
                view = manageWindow(view, event.size.width, event.size.height);
                window.setView(view);
            }

            // gestion des evenement
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1: towerType = 1; break;
                    case sf::Keyboard::Num2: towerType = 2; break;
                    case sf::Keyboard::Num3: towerType = 3; break;
                    case sf::Keyboard::Num5:
                        manager.saveJson(mapPath, map)
                            ? std::cout << "Map saved successfully!\n"
                            : std::cout << "Failed to save map!\n";
                        break;
                    case sf::Keyboard::Num7:
                        if (manager.loadJson(mapPath, map)) {
                            std::cout << "Map loaded successfully!\n";
                            path = manager.extractPathTiles(map);
                        } else {
                            std::cout << "Failed to load map!\n";
                        }
                        break;
                }
            }

            // placement de tours ou peinture
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                isPainting = true;
                sf::Vector2f world = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                sf::Vector2i cell = map.worldToCell(world);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) paintType = tileType::ground;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) paintType = tileType::obstacle;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) paintType = tileType::start;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) paintType = tileType::goal;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) paintType = tileType::path;

                if (cell.x >= 0 && cell.y >= 0) {
                    if (map.accessTile(cell.x, cell.y).buildable()) {
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

            if (event.type == sf::Event::MouseMoved && isPainting) {
                sf::Vector2f world = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                sf::Vector2i cell = map.worldToCell(world);
                if (cell.x >= 0 && cell.y >= 0)
                    map.paint(cell.x, cell.y, paintType);
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
                isPainting = false;
        }

        // spawn des creatures
        if (!path.empty() && spawnTimer.getElapsedTime().asSeconds() >= spawnInterval) {
            creatures.push_back(std::make_shared<Creature>(
                path.front().x, path.front().y, map, 70, 100.f)); // gridX, gridY, map, health, speed
            spawnTimer.restart();
        }

        // deplacement des creatures
        for (auto& c : creatures)
            c->move(path, frameTime);

        // tours tirent et mettent à jour leurs projectiles
        for (auto& t : towers) {
            t->update(frameTime,creatures);
        }

        // supprimer les creatures mort
        creatures.erase(std::remove_if(creatures.begin(), creatures.end(),
            [](const std::shared_ptr<Creature>& c) { return !c->isAlive(); }),
            creatures.end());


        window.clear();
        map.draw(window);
        for (auto& t : towers) t->draw(window);
        for (auto& c : creatures) c->draw(window);

        window.display();
    }

    return 0;
}
