#include <SFML/Graphics.hpp>
#include <iostream>
#include "text.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Toroïde SFML");
    window.setFramerateLimit(120);

    sf::CircleShape ball(20.f);                 // rayon = 20 px
    ball.setFillColor(sf::Color::Cyan);
    ball.setOrigin(ball.getRadius(), ball.getRadius());  // l'origine = centre
    ball.setPosition(0.f, 0.f);

    sf::Vector2f velocity(120.f, 70.f);         // px/s (x,y)
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

    

        window.clear();
        window.draw(t);
        window.display();

    }



    return 0;
}
