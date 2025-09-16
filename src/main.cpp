#include <SFML/Graphics.hpp>
#include <iostream>
#include "text.hpp"

int main() {

    sf :: RenderWindow window(sf::VideoMode(800,600,32),"ma fenetre !");
    window.setFramerateLimit(32);

    text txt ; 
    
    sf :: Text t =  txt.afficherText("weeee Achraf",26, sf :: Color :: Cyan , 400.f , 300.f ) ; 
    


    while(window.isOpen())
    {
        sf::Event event ;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }

    

        window.clear();
        window.draw(t);
        window.display();

    }



    return 0;
}
