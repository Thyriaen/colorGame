//
// Created by thyriaen on 25.10.18.
//

#include "Mana.h"

Mana::Mana(int island, int forest, int plain, int sBGs, int sBWs, int sGWs, int cBGs, int cBWs, int cGWs) {
    numberOfLands.resize(9);
    numberOfLands[basicBlue] = island;
    numberOfLands[basicGreen] = forest;
    numberOfLands[basicWhite] = plain;
    numberOfLands[shockBG] = sBGs;
    numberOfLands[shockBW] = sBWs;
    numberOfLands[shockGW] = sGWs;
    numberOfLands[checkBG] = cBGs;
    numberOfLands[checkBW] = cBWs;
    numberOfLands[checkGW] = cGWs;
}

Mana::Mana() {
    numberOfLands.resize(9);
}

int Mana::getBlues() {
    return numberOfLands[basicBlue] + numberOfLands[shockBW] + numberOfLands[shockBG] +
           numberOfLands[checkBW] + numberOfLands[checkBG];
}

int Mana::getGreens() {
    return numberOfLands[basicGreen] + numberOfLands[shockGW] + numberOfLands[shockBG] +
           numberOfLands[checkGW] + numberOfLands[checkBG];
}

int Mana::getWhites() {
    return numberOfLands[basicWhite] + numberOfLands[shockGW] + numberOfLands[shockBW] +
           numberOfLands[checkGW] + numberOfLands[checkBW];
}



int Mana::getLands() {
    int landNumber = 0;
    for(auto const &value : numberOfLands) {
        landNumber += value;
    }
    return landNumber;
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