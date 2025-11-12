#ifndef __EDITMODE__
#define __EDITMODE__

#include "interfaceGameMode.hpp"
#include<SFML/Graphics.hpp>


class EditMode : public IGameMode {
public:
    EditMode() = default ; 
    void onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i cell_pos) override;
    void onUpdate(GameObject& obj, sf::Vector2i cell_pos) override;
    void onRender(GameObject& obj, sf::RenderTarget& rt) override;

private:

};
#endif 