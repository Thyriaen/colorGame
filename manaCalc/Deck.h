//
// Created by thyriaen on 25.10.18.
//

#ifndef MANACALC_DECK_H
#define MANACALC_DECK_H

#include <chrono>
#include <random>
#include <vector>

enum Land { basicBlue, basicGreen, basicWhite, shockBG, shockBW, shockGW, checkBG, checkBW, checkGW, noLand };

class Deck {
  private:
    int lands;
    int spells;
    std::default_random_engine generator{ std::random_device()() };
    int w;
    int b;
    int g;
    int swb;
    int swg;
    int sbg;
    int cwb;
    int cwg;
    int cbg;

  public:
    void setLands(int w, int b, int g, int swb, int swg, int sbg, int cwb, int cwg, int cbg);
    void shuffle(int lands);
    Land drawColor();
    explicit Deck(int lands);
    int drawLand();
    int scryDrawForSpell();
    int scryDrawForLand();
    int numberOfLandsInHand(int size);

};


#endif //MANACALC_DECK_H
