#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "tile.hpp"
#include "tileMap.hpp"
#include "mapEditor.hpp"


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
//unsigned int cell_size =  4 ; // atribus de la class 
//unsigned int row = height_window/cell_size ; 
//unsigned int colone = width_window/cell_size ; 
tileMap map{width_window ,height_window};
mapEditor editor{map}; 



/////////

sf::RenderWindow window{sf::VideoMode(width_window,height_window),"Tower Defense"}; 
window.setFramerateLimit(60);


sf::View view ; 
view.setSize(static_cast<float>(width_window), static_cast<float>(height_window));
view.setCenter(width_window/2 , height_window/2);
view = manageWindow(view, window.getSize().x, window.getSize().y);
window.setView(view); 


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

        editor.keyBoardManager();
        editor.eventManager(window , event); 

        

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
