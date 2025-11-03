#include "hpBar.hpp"

hpBar::hpBar()
{
    border.setSize(sf::Vector2f(50.f, 8.f));
    border.setFillColor(sf::Color(130, 110, 90));
    thicknessSize=1.f;
    border.setOutlineThickness(thicknessSize);
    border.setOutlineColor(sf::Color(111, 222, 111));

    width=border.getSize().x-2*thicknessSize;
    sf::Vector2f barSize;
    barSize.x=width;
    barSize.y=border.getSize().y-2*thicknessSize;
    bar.setSize(barSize);
    bar.setFillColor(sf::Color::Red);

    fullHp=100;
    currentHp=fullHp;
}

hpBar::~hpBar()
{
}

void hpBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(border, states);
    target.draw(bar, states);
}

void hpBar::setPosition(sf::Vector2f position)
{
    border.setPosition(position);
    bar.setPosition(position+sf::Vector2f(thicknessSize,thicknessSize));
}

void hpBar::move(sf::Vector2f movement)
{
    border.move(movement);
    bar.move(movement);
}

void hpBar::setFullHp(int hp)
{
    fullHp=hp;
    currentHp=fullHp;
}

void hpBar::shrinkBar(int damage)
{
    currentHp-=damage;
    if(currentHp<0) currentHp=0;

    sf::Vector2f newBarSize;
    newBarSize.x=width*(static_cast<float>(currentHp)/static_cast<float>(fullHp));
    newBarSize.y=border.getSize().y-2*thicknessSize;

    bar.setSize(newBarSize);
}

void hpBar::increaseBar(int hp)
{
    currentHp+=hp;
    if(currentHp>fullHp) currentHp=fullHp;

    sf::Vector2f newBarSize;
    newBarSize.x=width*(static_cast<float>(currentHp)/static_cast<float>(fullHp));
    newBarSize.y=border.getSize().y-2*thicknessSize;

    bar.setSize(newBarSize);
}
void hpBar::setWidth(float BarWidth)
{
    border.setSize(sf::Vector2f(BarWidth, 8.f));
    width=border.getSize().x-2*thicknessSize;

    sf::Vector2f barSize;
    barSize.x=width;
    barSize.y=border.getSize().y-2*thicknessSize;
    bar.setSize(barSize);
}

bool hpBar::empty()
{
    return currentHp<=0;
}

int* hpBar::getHP()
{
    return &currentHp;
}

sf::Vector2f hpBar::getSize()
{
    return border.getSize();
}