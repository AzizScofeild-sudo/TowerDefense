#ifndef __TEXT__
  #define __TEXT__
#include <SFML/Graphics.hpp>
#include<string>
class text 
{

    public : 

    text(const std :: string& path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf" );
    ~text() = default;
    sf :: Text afficherText(const std :: string& name ,unsigned size , sf::Color color, float x , float y);

    private : 

    sf :: Font font ; 
    
};
#endif