#include <window.hpp>
#include <algorithm>


Window::Window(const std::string window_name, unsigned width_window, unsigned height_window) : 
sf::RenderWindow(sf::VideoMode(width_window, height_window), window_name),
window_name_(window_name),
width_window_(width_window),
height_window_(height_window),
map_(width_window, height_window),
editor_(map_),
towerManager(map_)
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


void Window::play_mode(sf::Event& event)
{
    if(!playLoaded_)
    {
    std::cout << "play mode.... " << std::endl ;
    if (mapManager::loadJson("/home/aziz-scofeild/TowerDedense/maps//level2.json", map_))
        std::cout << "[OK] Map chargee depuis maps/level1.json\n";
    else
    std::cout << "[ERR] Echec du chargement\n";
    }
    playLoaded_ = true ;
    


    //Placement des tours : 

    editor_.keyBoardManager();
        if (editor_.isBuilding() && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        auto mouse = sf::Mouse::getPosition(*this);
        auto [gx, gy] = worldToGrid(mouse, *this, map_.getSizeTile());

        // Bornes à vérifier selon ta map (par ex. map.getWidth(), map.getHeight()) :
        // if (gx >= map.getWidth() || gy >= map.getHeight()) continue;

        if (towerManager.addTower({gx, gy})) {
            // placé avec succès
            std ::cout << "Tour construite en (" << gx << ", " << gy << ")" << std::endl ;
        } else {
            // son / message “impossible de construire ici”
            std::cout << "Impossible de construire une tour ici !" << std::endl ;
        }

    }

    


}

void Window::edit_mode(sf::Event& event)
{   
    if(playLoaded_) std::cout << "edit mode.... " << std::endl ;
        editor_.keyBoardManager();
        editor_.eventManager(*this, event);
        
        
                    // ------------------------------
            // Raccourcis save (F5) / load (F9)
            // ------------------------------
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F5) {
                    if (mapManager::saveJson("/home/aziz-scofeild/TowerDedense/maps//level2.json", map_))
                        std::cout << "[OK] Map sauvegardee dans maps/level1.json\n";
                    else
                        std::cout << "[ERR] Echec de la sauvegarde\n";
                }
                if (event.key.code == sf::Keyboard::F9) {
                    if (mapManager::loadJson("/home/aziz-scofeild/TowerDedense/maps//level2.json", map_))
                        std::cout << "[OK] Map chargee depuis maps/level1.json\n";
                    else
                        std::cout << "[ERR] Echec du chargement\n";
                }

            }
    playLoaded_ = false ;
      
}






void Window::start_window()
{
    // Un “ghost” de prévisualisation (facultatif mais très pratique)
sf::RectangleShape ghost;
ghost.setSize({static_cast<float>(map_.getSizeTile()), static_cast<float>(map_.getSizeTile())});
ghost.setFillColor(sf::Color(0, 255, 0, 70));        // vert translucide si OK
ghost.setOutlineThickness(1.f);
ghost.setOutlineColor(sf::Color::Black);


while (this->isOpen())
{
    sf::Event event;
    while (this->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) this->close();  

        if (event.type == sf::Event::Resized)
        {
            view_ = manageWindow(view_, event.size.width, event.size.height);
            this->setView(view_);
        }

        editor_.keyBoardManager();

            // Gestion des modes de jeu

        switch (editor_.getMode())
        {
        case modeJeuEditor::Edit: 
            this->edit_mode(event); 
            break;
        case modeJeuEditor::PLay:
            this->play_mode(event);
            if (editor_.isBuilding()) {
    auto mouse = sf::Mouse::getPosition(*this);
    auto [gx, gy] = worldToGrid(mouse, *this, map_.getSizeTile());
    ghost.setPosition(gridToWorld(gx, gy, map_.getSizeTile()));

    // Couleur selon possibilité de build
    if (towerManager.buildable({gx, gy})) {
        ghost.setFillColor(sf::Color(0, 255, 0, 70));   // vert si OK
    } else {
        ghost.setFillColor(sf::Color(255, 0, 0, 70));   // rouge si interdit
    }
} 
            break;
        default:
            break;
        }
    }
    
     // fin pollEvent

    // ---- Rendu (une seule fois par frame) ----
    this->clear(sf::Color::Black);
    map_.draw(*this);
    towerManager.draw(*this);
    if (editor_.isBuilding()) this->draw(ghost);
    this->display();
    this->display();
}
}










// fonction temporaire UTILES : 


 sf::Vector2u Window::worldToGrid(sf::Vector2i mousePixel, const sf::RenderWindow& win, int cellSize) {
    // (si tu utilises une view, transforme les coords pixel → monde)
    sf::Vector2f world = win.mapPixelToCoords(mousePixel);
    unsigned gx = static_cast<unsigned>(std::max(0, int(world.x) / cellSize));
    unsigned gy = static_cast<unsigned>(std::max(0, int(world.y) / cellSize));
    return {gx, gy};
}
 sf::Vector2f Window::gridToWorld(unsigned gx, unsigned gy, int cellSize) {
    return {gx * static_cast<float>(cellSize), gy * static_cast<float>(cellSize)};
}
