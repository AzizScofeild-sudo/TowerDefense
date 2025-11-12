#pragma once
#include <SFML/Graphics.hpp>

// Déclarations avancées pour éviter les #include croisés ici
class Window;
class tileMap;
class mapEditor;
class TowerManager;

// Regroupe les objets du jeu que les modes utilisent
struct GameObject {
    tileMap&      map_;
    mapEditor&    editor_;
    TowerManager& towerManager_;
    Window&       window_;
};

// Interface polymorphe des modes de jeu
class IGameMode {
public:
    virtual ~IGameMode() = default;  // destructeur virtuel !

    // Gestion des événements (clavier/souris...)
    virtual void onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i cell_pos) = 0;

    // Logique par frame (dt optionnel si tu veux l’ajouter plus tard)
    virtual void onUpdate(GameObject& obj, sf::Vector2i mouseCell) = 0;

    // Rendu
    virtual void onRender(GameObject& obj, sf::RenderTarget& rt) = 0;
};