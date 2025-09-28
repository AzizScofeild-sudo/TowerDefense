#ifndef __TILEMAP__
 #define __TILEMAP__

#include "tile.hpp"
#include <vector>

class tileMap
{

    public :
    tileMap() = default;
    ~tileMap() = default;   


    private :

    unsigned Width ; 
    unsigned height ;
    std::vector<tile> Case ; 



};
#endif 