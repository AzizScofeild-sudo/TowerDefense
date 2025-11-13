#include <window.hpp>
#include <algorithm>



Window::Window(const std::string window_name, unsigned width_window, unsigned height_window) : 
sf::RenderWindow(sf::VideoMode(width_window, height_window), window_name),
window_name_(window_name),
width_window_(width_window),
height_window_(height_window)
{

    this->setFramerateLimit(60);
    view_.setSize(static_cast<float>(width_window_), static_cast<float>(height_window_));
    view_.setCenter(width_window_/2 , height_window_/2);
    view_ = manageWindow(view_ , width_window_ , height_window_);
    this->setView(view_);

}


sf::View Window::manageWindow(sf::View view , unsigned width_window , unsigned height_window) // methode pour ma class windowManager
{
    const float windowRatio = (height_window == 0 ) ? 1.f : static_cast<float>(width_window) /static_cast<float>(height_window) ;
    const float viewRatio = view.getSize().x / view.getSize().y ;

    float X = 0.f, Y = 0.f ;
    float portion_x = 1.f , portion_y = 1.f ; 

    if(windowRatio > viewRatio) // on considere que height_window = view.getSize().y donc ==>  width_window > view.getSize().x 
    {
        portion_x = viewRatio / windowRatio ;
        X = (1 - portion_x)/2; 

    }
    else if(windowRatio < viewRatio)
    { 
        portion_y = windowRatio / viewRatio ; 
        Y = (1-portion_y)/2 ;        
    }
    view.setViewport(sf::FloatRect( X , Y , portion_x , portion_y)); 
    return view ;
}



void Window::run()
{

    while (this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) this->close();
            if (event.type == sf::Event::Resized)
        {   
            // A faire : en capsuler cette partie !
            view_ = manageWindow(view_, event.size.width, event.size.height);
            this->setView(view_);
            // 
        }
        // 1)gestion des evenemeents du jeu hors resize et close !!!!
        sf::Vector2i cell_pos = mouseToCell(); 
        if (onEvent_) onEvent_(event, cell_pos);
        }





    // 2) Ici on  implemente la logie du jeu avec le meme proceder callBack !!!!
    sf::Vector2i cell_pos = mouseToCell();
    if(onGame_) onGame_(cell_pos); // un truc comme ca !!!!

    // 3) gestion de l'affichage de la fenetre////
        this->clear(sf::Color::Black);

        if (onRender_) onRender_(*this);

        this->display();
    }
}



// Mon organisation est temporaire, j'essaie d'utiliser des callBack que j'ai vu en faisant du ROS2
// pour separer les differentes parties de la boucle de jeu ( gestion des evenements , logique du jeu , affichage )
//pour rendre la cllass window plus generique et plus modulaire celon le pragmatisme de la programmation orienter objet !!!!
// Important : !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Modiefier l'architecture de programme : 
// le callBack ----> onEvent doit de s'occuper des entrer de l'utilisateur, en mode edition(modification est creation des map) et en mode jeu, on
//devra donc ajouter un controle du mode pour definir comme se deroulera le callBack
// Remarque : la capture de la position de la souris doit n'est pas un Event donc elle doit etre presente dans la l'update,  