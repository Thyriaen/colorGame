//
// Created by thyriaen on 25.10.18.
//

#include "Mana.h"

Mana::Mana(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs) :
        islands(island),
        forests(forest),
        plains(plain),
        sBG(sBGs),
        sBW(sBWs),
        sGW(sGWs),
        cBG(cBGs),
        cBW(cBWs),
        cGW(cGWs) {
}

Mana::Mana() :
        islands(0),
        forests(0),
        plains(0),
        sBG(0),
        sBW(0),
        sGW(0),
        cBG(0),
        cBW(0),
        cGW(0) {
}

Deck::Deck(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs) :
        Mana(island, forest, plain, sBGs, sBWs, sGWs, cBGs, cBWs, cGWs),
        spells(35) {
}

Land Deck::drawMana() {
    std::uniform_int_distribution<int> distribution(1,getLands());
    int card = distribution(generator);

}

Board::Board() :
        Mana() {
}