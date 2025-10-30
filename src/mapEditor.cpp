#include "mapEditor.hpp"
#include <SFML/Graphics.hpp>


mapEditor::mapEditor(tileMap& map) : map_{map} {}


void mapEditor::keyBoardManager()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) paintType_ = tileType::ground;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) paintType_ = tileType::obstacle;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) paintType_ = tileType::start;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) paintType_ = tileType::goal; 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) paintType_ = tileType::path; 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) mode_ = modeJeuEditor::PLay ;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) mode_ = modeJeuEditor::Edit ;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) building = true ;
}

sf::Vector2i mapEditor::worldToCell(sf::RenderWindow& window, sf::Vector2i pixel)
{
    sf::Vector2f world = window.mapPixelToCoords(pixel, window.getView());

    return map_.worldToCell(world);
}

void mapEditor::paint(sf::Vector2i cell) 
{
    if(cell.x >= 0 && cell.y >= 0)
    {map_.paint((unsigned)cell.x, (unsigned)cell.y , paintType_);}
}




void mapEditor::eventManager(sf::RenderWindow& window, sf ::Event& event)
{
   
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            {
                isPainting_ = true ;
                sf::Vector2i cell  = worldToCell(window,{ event.mouseButton.x, event.mouseButton.y });
                paint(cell);
            }

        if (event.type == sf::Event::MouseMoved && isPainting_)
           {
                sf::Vector2i cell = worldToCell(window,{ event.mouseMove.x, event.mouseMove.y });
                paint(cell);           
           }
    
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            isPainting_ = false ; 
        } 
}

modeJeuEditor mapEditor::getMode() const noexcept 
{
    return mode_ ;
}
    