//
// Created by thyriaen on 25.10.18.
//

#ifndef MANACALC_DECK_H
#define MANACALC_DECK_H

#include <chrono>
#include <random>
#include <vector>


class Deck {
  private:
    int lands;
    int spells;
    std::default_random_engine generator{ std::random_device()() };

  public:
    void shuffle(int lands);
    explicit Deck(int lands);
    int drawLand();
    int scryDrawForSpell();
    int scryDrawForLand();
    int numberOfLandsInHand(int size);

};


#endif //MANACALC_DECK_H
