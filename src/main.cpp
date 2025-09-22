#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>


sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window)
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

int main(){
    const int cellsize = 25;
    const int width  = 1200;
    const int height = 800;
    const int ligne = width / cellsize;  
    const int col   = height / cellsize; 
    const sf::Color gridlinecolor = sf::Color::White;

    std::vector<std::vector<sf::Color>> cellcolor(ligne, std::vector<sf::Color>(col, sf::Color::Black));

    sf::RenderWindow window(sf::VideoMode(width, height),"Tower Defense");
    sf::View view ; 
    view.setSize(static_cast<float>(width), static_cast<float>(height));
    view.setCenter(width/2 , height/2);

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

            if(event.type== sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) {
                int mousex = event.mouseButton.x;
                int mousey = event.mouseButton.y;

                const int cellx = mousex / cellsize;
                const int celly = mousey / cellsize;

                if (cellx < ligne && celly < col){
                    if(cellcolor[cellx][celly]==sf::Color::Black)
                        cellcolor[cellx][celly]=sf::Color::Red;
                    else
                        cellcolor[cellx][celly]=sf::Color::Black;
                }
            }
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

        for (int x = 0; x <width; x += cellsize) {
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

        window.display();
    }
    return 0;
}
