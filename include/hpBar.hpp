#ifndef HPBAR_HPP
#define HPBAR_HPP

#include <SFML/Graphics.hpp>

class hpBar : public sf::Drawable {
public:
    hpBar();
    ~hpBar();

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f movement);

    void setFullHp(int hp);
    void shrinkBar(int damage);
    void increaseBar(int hp);

    void setWidth(float BarWidth);

    bool empty();
    int* getHP();
    sf::Vector2f getSize();
    
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RectangleShape border;
    sf::RectangleShape bar;
    float width;
    float thicknessSize;

    int fullHp;
    int currentHp;

};

#endif