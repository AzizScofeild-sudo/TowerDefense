#include <iostream>
#include "text.hpp"
#include <SFML/Graphics.hpp>


text::text(const std::string& path )
{
    if(!font.loadFromFile(path))
     throw std::runtime_error("Impossible de charger la police: " + path);

}

sf::Text text :: afficherText(const std :: string& name ,unsigned size , sf::Color color, float x , float y)
{

    sf :: Text txt ; 
    txt.setFont(font) ;
    txt.setString(name);
    txt.setCharacterSize(size);
    txt.setFillColor(color);
    txt.setPosition(x,y);


   return txt ; 
}




