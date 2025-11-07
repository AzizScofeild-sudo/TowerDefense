#ifndef HPBAR_HPP
#define HPBAR_HPP

#include <SFML/Graphics.hpp>

class hpBar {
public:
    hpBar();
    ~hpBar();

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f movement);

    void setFullHp(int hp);
    void increaseBar(int hp);
    bool empty();
    void draw(sf::RenderWindow window);

private:
    sf::RectangleShape border;
    sf::RectangleShape bar;
    int fullHp;
    int currentHp;

};

#endif