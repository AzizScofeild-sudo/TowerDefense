#pragma once
#include "interfaceGameMode.hpp"

class MenuMode : public IGameMode {
public:
    void onEnter(GameObject& obj); // optionnel mais pratique

    void onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i cell) override;
    void onUpdate(GameObject& obj, sf::Vector2i cell) override;
    void onRender(GameObject& obj, sf::RenderTarget& rt) override;

private:
    bool built_ = false;
};
