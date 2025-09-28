#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "tile.hpp"
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
////Couleur des cases de la fenetre :
std::vector<std::vector<sf::Color>> cell_color(row,std::vector<sf::Color>(colone,sf::Color::Black));


/////////

sf::RenderWindow window{sf::VideoMode(width_window,height_window),"Tower Defense"}; 
window.setFramerateLimit(60);


sf::View view ; 
view.setSize(static_cast<float>(width_window), static_cast<float>(height_window));
view.setCenter(width_window/2 , height_window/2);
//view = manageWindow(view, window.getSize().x, window.getSize().y);
//window.setView(view); 




while (window.isOpen())
{
////////Gestion des evenements :
    sf :: Event event ; 
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) window.close(); 
        if (event.type == sf::Event::Resized)
        {
            view = manageWindow(view , event.size.width , event.size.height);
            window.setView(view); 
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f world = window.mapPixelToCoords({event.mouseButton.x ,event.mouseButton.y});
            unsigned int mouse_x = world.x ; 
            unsigned int mouse_y = world.y ; 
//////// Detecter la case selectionnee :
            unsigned int cell_x = mouse_x/cell_size;
            unsigned int cell_y = mouse_y/cell_size;
//////// Affecter une couleur a une case 
            if(cell_x < colone && cell_y < row )
            {
                if(cell_color[cell_y][cell_x] == sf::Color::Black)
                {
                    cell_color[cell_y][cell_x] = sf::Color::Red ; 
                }
                else
                {
                    cell_color[cell_y][cell_x] = sf::Color::Black ; 
                }
                 
                
            }
        }
    }////fin de la bouble de gestion d'evenement

window.clear(sf::Color::Black);

    
////////dessiner les differentes cases 
    for(unsigned int y = 0 ; y < row ; ++y )
    {
        for(unsigned int x = 0 ; x < colone ; ++x)
        {
            sf::RectangleShape cell(sf::Vector2f(cell_size,cell_size));
            cell.setPosition(x * cell_size ,y * cell_size);
            cell.setFillColor(cell_color[y][x]);
            window.draw(cell);
        }
    }////Fin de la boucle (Dessiner les cases)

////////Dessiner les line verticales : 
    for(unsigned int x = 0 ; x < width_window ; x+=cell_size)
       {
        sf::Vertex line[] = 
        {
            sf::Vertex(sf::Vector2f(x,0),sf::Color::White),
            sf::Vertex(sf::Vector2f(x,height_window),sf::Color::White) 
        };
        window.draw(line,2,sf::Lines); 
       }
    
////////Dessiner les ligne horizontales :
        for(unsigned int y = 0 ; y < height_window ; y+=cell_size)
       {
        sf::Vertex line[] = 
        {
            sf::Vertex(sf::Vector2f(0,y),sf::Color::White),
            sf::Vertex(sf::Vector2f(width_window,y),sf::Color::White) 
        };
        window.draw(line,2,sf::Lines); 
        std :: cout << "window X = " << window.getSize().x <<  "  Y = " << window.getSize().y << std::endl;
       }



    window.display();
    }

    tile t ; 
    t.setType(tileType::start);   
    return 0 ; 
}
