//
// Created by thyriaen on 25.10.18.
//

#ifndef MANACALC_MANA_H
#define MANACALC_MANA_H

#include <chrono>
#include <random>
#include <vector>

enum Color { blue, green, white };
enum Land { basicBlue, basicGreen, basicWhite, shockBG, shockBW, shockGW, checkBG, checkBW, checkGW };

class Mana {
  protected:
    int islands;
    int forests;
    int plains;

    int sBG;
    int sBW;
    int sGW;

    int cBG;
    int cBW;
    int cGW;
  public:
    Mana(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs);
    Mana();
    int getLands() {
        return islands + forests + plains + sBG + sBW + sGW + cBG + cBW + cGW;
    }
};

class Hand : public Mana {

};

class Deck : public Mana {
  private:
    int spells;
    std::default_random_engine generator{ std::random_device()() };
  public:
    Deck(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs);

    Land drawMana();
};

class Board : public Mana {
  public:
    Board();
};

#endif //MANACALC_MANA_H
