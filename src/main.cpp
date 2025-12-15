#include "game.hpp"



int main()
{
    Game g{}; 
    g.run(); 

    return 0 ; 
}



/*
//// Petit resumé de mon code : 
L'architecture a pour objectif la moodularite ou chaque class a une resposabilité specifique !
1) Aa class window a pour respensabite l'affichage du jeu elle tourne selon un cycle SFML 
//a) Detecter et gerer les evenement dans la boucle du pollevent via le callback "onEvent" 
//b) L'implementation de la logiique du jeu grave au callback "onupdate"
//b) L'affichage des differents elements du jeu ! 
////en resumé : capture des envenements---->gerer la logique du jeu----> affichage (et on boucle le tout)!
2) on a ajouter une class (on guise d'interface) : "InterfaceGameMode" qui possede 3 classes enfant qui elles represente
les different mode de jeu possible menu, edit et play
///////////////////////////////:::
a partir de ca on a commmencer a creer notre jeu
3) premiere etape de notre projet etait de creer et afficher la map, on a decidé de creer un egrilles qui contient differents tuille 
on possede 5 type de tuiles: "ground, path, obstacle , start et goal"
les start goal path et obstacle ne permettents pas de construire des tours! 


*/