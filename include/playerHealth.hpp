#pragma once
#include <SFML/Graphics.hpp>

class PlayerHealth {
public:
    explicit PlayerHealth(int maxHp = 20) : maxHp_(maxHp), hp_(maxHp) {}

    void reset(int maxHp) { maxHp_ = maxHp; hp_ = maxHp; }

    void lose(int amount) {
        hp_ -= amount;
        if (hp_ < 0) hp_ = 0;
    }

    bool isDead() const { return hp_ <= 0; }
    int  getHp() const { return hp_; }
    int  getMaxHp() const { return maxHp_; }

    void draw(sf::RenderTarget& rt) const {
        // Barre simple en haut à gauche
        const float w = 400.f;
        const float h = 25.f;
        const float x = 400.f;
        const float y = 20.f;

        sf::RectangleShape bg({w, h});
        bg.setPosition(x, y);
        bg.setFillColor(sf::Color(60, 60, 60));

        float ratio = (maxHp_ > 0) ? static_cast<float>(hp_) / static_cast<float>(maxHp_) : 0.f;
        sf::RectangleShape fg({w * ratio, h});
        fg.setPosition(x, y);
        fg.setFillColor(sf::Color::Green);

        rt.draw(bg);
        rt.draw(fg);
    }

private:
    int maxHp_;
    int hp_;
    

};
