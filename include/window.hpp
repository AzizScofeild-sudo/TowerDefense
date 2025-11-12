#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include "utils.hpp"


class Window : public sf::RenderWindow {
  using EventCallback  = std::function<void(const sf::Event& event, sf::Vector2i cell_pos)>; 
  using GameLoopCallback = std::function<void(sf::Vector2i cell_pos)>;         
  using RenderCallback = std::function<void(sf::RenderTarget& target)>; 
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
    sf::Vector2i mouseToCell() {
        // Capturer la position de la souris e en coordonnees window (int) : 
        sf::Vector2i mouse = sf::Mouse::getPosition(*this); 
        //convertir les coordonnees window en coordonnees world (float):
        sf::Vector2f world = this->mapPixelToCoords(mouse, this->getView());
        //convertir les coordonnees world en coordonnees map (grid) (unsigned ou int)  pour les utiliser pour la logique du jeu : 
        sf::Vector2i cell = Grid::worldToGrid(world);
        return cell; 
    }

    private : 
    std::string window_name_ ; 
    unsigned width_window_ ;
    unsigned height_window_ ;
    sf::View view_ ;

    private : 
    EventCallback  onEvent_;   //libre
    GameLoopCallback onGame_ ; //libre 
    RenderCallback onRender_; //libre  

};
#endif 