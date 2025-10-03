#include "mapEditor.hpp"
#include <SFML/Graphics.hpp>






mapEditor::mapEditor(tileMap& map) : map{map} {}



void mapEditor::keyBoardManager()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) paintType = tileType::ground;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) paintType = tileType::obstacle;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) paintType = tileType::start;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) paintType = tileType::goal; 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) paintType = tileType::path;  
}

sf::Vector2i mapEditor::worldToCell(sf::RenderWindow& window, sf::Vector2i pixel)
{
    sf::Vector2f world = window.mapPixelToCoords(pixel, window.getView());

    return map.worldToCell(world);
}

void mapEditor::paint(sf::Vector2i cell) 
{
    if(cell.x >= 0 && cell.y >= 0)
    {map.paint((unsigned)cell.x, (unsigned)cell.y , paintType);}
}




void mapEditor::eventManager(sf::RenderWindow& window, sf ::Event& event)
{
   
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            {
                isPainting = true ;
                sf::Vector2i cell  = worldToCell(window,{ event.mouseButton.x, event.mouseButton.y });
                paint(cell);
            }

        if (event.type == sf::Event::MouseMoved && isPainting)
           {
                sf::Vector2i cell = worldToCell(window,{ event.mouseMove.x, event.mouseMove.y });
                paint(cell);           
           }
    
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            isPainting = false ; 
        }
    


    
}
    