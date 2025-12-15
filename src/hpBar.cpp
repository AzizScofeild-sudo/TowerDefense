#include "hpBar.hpp"
#include "creature.hpp"

hpBar::hpBar(Creature& creature)
    : creature(creature)
{
    fullHp = creature.getHealth();

    bar.setSize(sf::Vector2f(50.f, 8.f));
    bar.setFillColor(sf::Color::Green);
    bar.setOutlineColor(sf::Color::Black);
    bar.setOutlineThickness(1.f);
}

void hpBar::update()
{
    if (!creature.isAlive()) 
    return;

    float healthRatio=static_cast<float>(creature.getHealth()) / fullHp;

    if (healthRatio<0.f) 
    healthRatio=0.f;

    bar.setSize(sf::Vector2f(50.f*healthRatio,8.f));

    if (healthRatio>0.5f)
        bar.setFillColor(sf::Color::Green);
    else if (healthRatio>0.2f)
        bar.setFillColor(sf::Color::Yellow);
    else
        bar.setFillColor(sf::Color::Red);

    sf::Vector2f pos=creature.getCreaturePosition();
    float radius=creature.getCreatureRadius();

    bar.setPosition(pos.x-bar.getSize().x /2.f, pos.y-radius-15.f);
}

void hpBar::draw(sf::RenderTarget& window)
{
    if (!creature.isAlive()) return;
    window.draw(bar);
}