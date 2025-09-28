#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "weakTower.hpp"
#include "mediumTower.hpp"
#include "strongTower.hpp"
#include "creature.hpp"

sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window)
{
    const float windowRatio = (height_window == 0 ) ? 1.f :
        static_cast<float>(width_window) /static_cast<float>(height_window);
    const float viewRatio = view.getSize().x / view.getSize().y ;

    float X = 0.f, Y = 0.f ;
    float portion_x = 1.f , portion_y = 1.f ;

    if(windowRatio > viewRatio)
    {
        portion_x = viewRatio / windowRatio ;
        X = (1 - portion_x)/2;
    }
    else if(windowRatio < viewRatio)
    {
        portion_y = windowRatio / viewRatio ;
        Y = (1-portion_y)/2 ;
    }

    view.setViewport(sf::FloatRect( X , Y , portion_x , portion_y));
    return view ;
}

int main() {
    const int cellsize = 25;
    const int width  = 1200;
    const int height = 800;
    const int ligne = width / cellsize;
    const int col   = height / cellsize;
    const sf::Color gridlinecolor = sf::Color::White;

    std::vector<std::vector<sf::Color>> cellcolor(
        ligne, std::vector<sf::Color>(col, sf::Color::Black)
    );

    sf::RenderWindow window(sf::VideoMode(width, height),"Tower Defense");
    sf::View view ;
    view.setSize(static_cast<float>(width), static_cast<float>(height));
    view.setCenter(width/2 , height/2);

    // --- Vecteurs de tours et créatures ---
    std::vector<std::shared_ptr<Tower>> towers;
    std::vector<std::shared_ptr<Creature>> creatures; 

    int towerType = 1; // 1: WeakTower, 2: MediumTower, 3: StrongTower
    creatures.push_back(std::make_shared<Creature>(0, 15, cellsize));

    // --- AJOUTÉ : Timer pour spawn automatique ---
    sf::Clock spawnTimer;
    const float spawnInterval = 2.f; // 2 secondes

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                view = manageWindow(view , event.size.width , event.size.height);
                window.setView(view);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) towerType = 1;
                if (event.key.code == sf::Keyboard::Num2) towerType = 2;
                if (event.key.code == sf::Keyboard::Num3) towerType = 3;
            }

            if(event.type == sf::Event::MouseButtonPressed &&
               event.mouseButton.button == sf::Mouse::Left)
            {
                int mousex = event.mouseButton.x;
                int mousey = event.mouseButton.y;

                const int cellx = mousex / cellsize;
                const int celly = mousey / cellsize;

                if (cellx < ligne && celly < col)
                {
                    if (towerType == 1)
                        towers.push_back(std::make_shared<WeakTower>(cellx, celly, cellsize));
                    else if (towerType == 2)
                        towers.push_back(std::make_shared<MediumTower>(cellx, celly, cellsize));
                    else if (towerType == 3)
                        towers.push_back(std::make_shared<StrongTower>(cellx, celly, cellsize));
                }
            }
        }

        // --- AJOUTÉ : Générer une créature toutes les 2 secondes ---
        if (spawnTimer.getElapsedTime().asSeconds() >= spawnInterval) {
            creatures.push_back(std::make_shared<Creature>(0, 15, cellsize));
            spawnTimer.restart(); // remettre le timer à zéro
        }

        // Déplacer les créatures
        for (auto &c : creatures) {
            c->move(); // avance horizontalement
        }

        window.clear();

        for (int x = 0; x < ligne; ++x) {
            for (int y= 0; y < col; ++y) {
                sf::RectangleShape cell (sf::Vector2f(cellsize,cellsize));
                cell.setPosition(x*cellsize, y*cellsize);
                cell.setFillColor(cellcolor[x][y]);
                window.draw(cell);
            }
        }

        for (int x = 0; x < width; x += cellsize) {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x, 0), gridlinecolor),
                sf::Vertex(sf::Vector2f(x, height), gridlinecolor)
            };
            window.draw(line, 2, sf::Lines);
        }

        for (int y = 0; y < height; y += cellsize) {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0, y), gridlinecolor),
                sf::Vertex(sf::Vector2f(width, y), gridlinecolor)
            };
            window.draw(line, 2, sf::Lines);
        }
        

        for (auto& t : towers) {
            t->draw(window);
        }

        for (auto& c : creatures) {
            c->draw(window);
        }

        window.display();
    }
    return 0;
}
