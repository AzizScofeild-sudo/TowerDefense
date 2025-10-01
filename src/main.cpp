#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "tile.hpp"
#include "tileMap.hpp"

sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window) // methode pour ma class windowManager
{
    const float windowRatio = (height_window == 0 ) ? 1.f : static_cast<float>(width_window) /static_cast<float>(height_window) ;
    const float viewRatio = view.getSize().x / view.getSize().y ;

    float X = 0.f, Y = 0.f ;
    float portion_x = 1.f , portion_y = 1.f ; 

    if(windowRatio > viewRatio) // on considere que height_window = view.getSize().y donc ==>  width_window > view.getSize().x 
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






// Ma bouclez main doit contenir une seul ligne d'execution 
// je dois donc eventuelllement creer une class window pour afficher le fenetre 
// et une class windowManager pour la creatrtion des chmains (path)

int main(){
//declaration : 
////taille de la fenetre :
const unsigned int width_window =1200 ,height_window = 800 ; // les atributs de ma class 
/////cellules : 
unsigned int cell_size = 25 ; // atribus de la class 
unsigned int row = height_window/cell_size ; 
unsigned int colone = width_window/cell_size ; 
tileMap map{colone ,row ,cell_size};


/////////

sf::RenderWindow window{sf::VideoMode(width_window,height_window),"Tower Defense"}; 
window.setFramerateLimit(60);


sf::View view ; 
view.setSize(static_cast<float>(width_window), static_cast<float>(height_window));
view.setCenter(width_window/2 , height_window/2);
view = manageWindow(view, window.getSize().x, window.getSize().y);
window.setView(view); 




// --- au-dessus de la boucle, si tu veux tracer en glissant :
bool isPainting = false;      // vrai quand on maintient le clic gauche
tileType paintType = tileType::path; // type en cours (sera recalculé à chaque clic)

while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized)
        {
            view = manageWindow(view, event.size.width, event.size.height);
            window.setView(view);
        }

        // -------------------------
        // choix du type à peindre :
        // -------------------------
        auto computePaintType = [&]() -> tileType {
            // On lit l'état du clavier AU MOMENT du clic
            // (left click + G/O/S/T)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) return tileType::ground;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) return tileType::obstacle;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return tileType::start;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) return tileType::goal;
            // par défaut : Path
            return tileType::path;
        };

        // ------------------------------------------------
        // CLIC GAUCHE : peindre (avec ou sans modificateur)
        // ------------------------------------------------
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            isPainting = true;

            // 1) pixel écran -> coords monde (prend en compte la view)
            sf::Vector2f world = window.mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y }, window.getView());

            // 2) monde -> cellule (x,y)
            sf::Vector2i cell = map.worldToCell(world); // <- si ta signature prend Vector2i, caste world.x/y en int d’abord

            // 3) déterminer le type à peindre en fonction des touches
            paintType = computePaintType();

            // 4) peindre si dans la carte
            if (cell.x >= 0 && cell.y >= 0)
                map.paint((unsigned)cell.x, (unsigned)cell.y, paintType);
        }

        // ------------------------------------------------
        // DRAG (glisser en maintenant le clic gauche)
        // ------------------------------------------------
        if (event.type == sf::Event::MouseMoved && isPainting)
        {
            sf::Vector2f world = window.mapPixelToCoords(
                { event.mouseMove.x, event.mouseMove.y }, window.getView());

            sf::Vector2i cell = map.worldToCell(world);
            if (cell.x >= 0 && cell.y >= 0)
                map.paint((unsigned)cell.x, (unsigned)cell.y, paintType);
        }

        // ------------------------------------------------
        // RELÂCHEMENT clic gauche : on arrête de peindre
        // ------------------------------------------------
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            isPainting = false;
        }

        // ------------------------------------------------
        // CLIC DROIT : gomme (force Ground)
        // ------------------------------------------------
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2f world = window.mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y }, window.getView());

            sf::Vector2i cell = map.worldToCell(world);
            if (cell.x >= 0 && cell.y >= 0)
                map.paint((unsigned)cell.x, (unsigned)cell.y, tileType::ground);
        }
    } // fin pollEvent

    // ---- Rendu (une seule fois par frame) ----
    window.clear(sf::Color::Black);
    map.draw(window);
    window.display();
}


    tile t ; 
    t.setType(tileType::start);   
    return 0 ; 
}
