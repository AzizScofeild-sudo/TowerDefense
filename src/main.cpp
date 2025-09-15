#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std :: cout << "Hello World!" << std :: endl ;
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

        float dt = clock.restart().asSeconds();

        // --- MISE A JOUR POSITION ---
        sf::Vector2f pos = ball.getPosition();
        pos += velocity * dt;

        // --- WRAP TORIQUE ---
        const auto size = window.getSize();
        const float W = static_cast<float>(size.x);
        const float H = static_cast<float>(size.y);
        const float r = ball.getRadius();
        if (pos.x < -r)      pos.x = W + r; 
        if (pos.x > W + r)   pos.x = -r;
        if (pos.y < -r)      pos.y = H + r;
        if (pos.y > H + r)   pos.y = -r;

        std :: cout << "x = " << pos.x << std :: endl ; 
        std :: cout << "y = " << pos.y << std :: endl ;  

        ball.setPosition(pos);

        // (Option) afficher la position au centre (debug)
        // std::cout << "pos = (" << pos.x << ", " << pos.y << ")\n";

        window.clear();
        window.draw(ball);
        window.display();
    }
    return 0;
}



