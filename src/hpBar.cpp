#include "hpBar.hpp"

hpBar::hpBar()
{
    border.setSize(sf::Vector2f(50.f, 8.f));
    border.setFillColor(sf::Color::White);
    border.setOutlineThickness(1.f);
    border.setOutlineColor(sf::Color::Black);

    float width=border.getSize().x-2*1.f;
    sf::Vector2f barSize;
    barSize.x=width;
    barSize.y=border.getSize().y-2*1.f;
    bar.setSize(barSize);
    bar.setFillColor(sf::Color::Red);

    fullHp=100;
    currentHp=fullHp;
}


void hpBar::draw(sf::RenderWindow window)
{
    window.draw(border);
    window.draw(bar);
}

void hpBar::setPosition(sf::Vector2f position)
{

}

