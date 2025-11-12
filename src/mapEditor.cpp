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

}


void mapEditor::paint(sf::Vector2i cell_pos) 
{
    if(cell_pos.x >= 0 && cell_pos.y >= 0)
    {map_.paint((unsigned)cell_pos.x, (unsigned)cell_pos.y , paintType_);}
}




void mapEditor::eventManager(sf ::Event& event, sf::Vector2i cell_pos)
{
   
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            {
                isPainting_ = true ;
                paint(cell_pos);
            }

        if (event.type == sf::Event::MouseMoved && isPainting_)
           {
                paint(cell_pos);           
           }
    
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            isPainting_ = false ; 
        } 
}

