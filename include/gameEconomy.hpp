#pragma once

class gameEconomy {
public:
    gameEconomy(int initialMoney = 1000);

    bool canAfford(int amount) const;

    void spend(int amount);

    void earn(int amount);

    int getMoney() const;

private:
    int money;
};
