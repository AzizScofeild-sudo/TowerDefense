#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>



class Window : public sf::RenderWindow {

    
  using EventCallback  = std::function<void(const sf::Event&)>;          
  using RenderCallback = std::function<void(sf::RenderTarget& target)>; 
  using GameLoopCallback = std::function<void(const sf::Event&)>;
    public : 
    Window(const std::string window_name, unsigned width_window, unsigned height_window); 
    ~Window() = default ;

    void run(); 

    void setEventCallback(EventCallback callback) { onEvent_ = std::move(callback); }
    void setRenderCallback(RenderCallback callback) { onRender_ = std::move(callback); }
    void setGameLoopCallback(GameLoopCallback callback) { onGame_ = std::move(callback); }
    unsigned getWidth_window(){return width_window_ ;}
    unsigned getHeight_window(){return height_window_;}

    private : 
    sf::View manageWindow(sf::View view , unsigned width_window , unsigned height_window);

    private : 
    std::string window_name_ ; 
    unsigned width_window_ ;
    unsigned height_window_ ;
    sf::View view_ ;

    private : 
    EventCallback  onEvent_;   //libre 
    RenderCallback onRender_; //libre 
    GameLoopCallback onGame_ ; //libre 



};
#endif 