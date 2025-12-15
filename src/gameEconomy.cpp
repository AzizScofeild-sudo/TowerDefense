#include "gameEconomy.hpp"
#include <iostream>


gameEconomy::gameEconomy(int initialMoney) : money(initialMoney) {}


bool gameEconomy::canAfford(int amount) const {
    return money >= amount;
}

void gameEconomy::spend(int amount) {
    if (amount > money) {
        std::cerr << "[GameEconomy] Erreur : tentative de dépenser plus que l'argent disponible !" << std::endl;
        return;
    }
    money -= amount;
}

void gameEconomy::earn(int amount) {
    money += amount;
}

int gameEconomy::getMoney() const {
    return money;
}
