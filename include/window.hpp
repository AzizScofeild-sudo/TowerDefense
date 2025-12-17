#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "tile.hpp"
#include "tileMap.hpp"
#include "mapEditor.hpp"
#include "mapManager.hpp"  


class Window : public sf::RenderWindow {


    public : 
    Window(const std::string window_name, unsigned width_window, unsigned height_window); 
    ~Window() = default ;
    void start_window();

    void play_mode();
    void edit_mode(sf::Event& event); 

    private : 
    sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window);

    private : 
    std::string window_name_ ; 
    unsigned width_window_ ;
    unsigned height_window_ ;
    tileMap map_ ; 
    sf::View view_ ;
    mapEditor editor_ ;
    bool playLoaded_ = true ;

};
#endif 