#ifndef __TILE__
 #define __TILE__

 #include <SFML/Graphics/Color.hpp>
 #include<cstdint>


 enum class tileType : std::uint8_t
 {
    ground, 
    path,
    obstacle,
    start, 
    goal
 };

 class tile 
 {
   public :
    tile(); 
    ~tile() = default ; 
    bool walkable() const noexcept ; 
    void setType(tileType newType) noexcept ; 
    sf::Color displayColor() const noexcept ; 
   private : 

   tileType  type = tileType:: ground ;
   bool buildable = true; 

 };

#endif