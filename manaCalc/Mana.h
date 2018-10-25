//
// Created by thyriaen on 25.10.18.
//

#ifndef MANACALC_MANA_H
#define MANACALC_MANA_H

enum Color { blue, green, white };
enum Basic { island, forest, plains };
enum Shock { bg, bw, gw };
enum Check { BG, BW, GW };

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
};

class Hand : public Mana {

};

class Deck : public Mana {
  private:
    int spells;
  public:
    Deck(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs);

};

class Board : public Mana {
  public:
    Board();
};

#endif //MANACALC_MANA_H
