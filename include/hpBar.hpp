#ifndef HPBAR_HPP
#define HPBAR_HPP

#include <SFML/Graphics.hpp>

class Creature;

class hpBar {
public:
    hpBar(Creature& creature);

    void update();
    void draw(sf::RenderTarget& window);

private:
    Creature& creature;
    float fullHp;
    sf::RectangleShape bar;
};

#endif
