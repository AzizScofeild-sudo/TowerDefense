#include "menuMode.hpp"

void MenuMode::onEnter(GameObject& obj)
{
    obj.gui_.removeAllWidgets();

    auto panel = tgui::Panel::create({"40%", "30%"});
    panel->setPosition({"30%", "35%"});
    obj.gui_.add(panel);

    auto btnEdit = tgui::Button::create("Edit Mode");
    btnEdit->setSize({"80%", "30%"});
    btnEdit->setPosition({"10%", "15%"});
    panel->add(btnEdit);

    auto btnPlay = tgui::Button::create("Play Mode");
    btnPlay->setSize({"80%", "30%"});
    btnPlay->setPosition({"10%", "55%"});
    panel->add(btnPlay);

    // ICI : brancher les actions des boutons
    btnEdit->onPress([&obj] {
    if (obj.requestEditMode) obj.requestEditMode();
    });

    btnPlay->onPress([&obj] {
    if (obj.requestPlayMode) obj.requestPlayMode();
    });


    built_ = true;
}


void MenuMode::onEvent(GameObject& obj, const sf::Event& event, sf::Vector2i)
{
    obj.gui_.handleEvent(event); // indispensable
}

void MenuMode::onUpdate(GameObject&, sf::Vector2i) {}

void MenuMode::onRender(GameObject& obj, sf::RenderTarget& rt)
{
    // Optionnel: dessiner un fond
    //obj.map_.draw(rt);

    // TGUI se dessine sur la fenêtre (GuiSFML), pas sur RenderTarget générique
    // Donc en pratique: rt doit être ta Window (sf::RenderWindow).
    obj.gui_.draw();
}
