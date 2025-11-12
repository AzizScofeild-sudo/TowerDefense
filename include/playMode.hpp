#ifndef __PLAYMODE__
#define __PLAYMODE__

#include "interfaceGameMode.hpp"
#include<SFML/Graphics.hpp>


class PlayMode : public IGameMode {
public:
    PlayMode() = default ; 
    void onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i cell_pos) override;
    void onUpdate(GameObject& obj, sf::Vector2i cell_pos) override;
    void onRender(GameObject& obj, sf::RenderTarget& rt) override;

private:

bool isBuilding_ = false ;
bool loaded_ = false ;

};
#endif 