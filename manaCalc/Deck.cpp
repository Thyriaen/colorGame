//
// Created by thyriaen on 25.10.18.
//

#include "Deck.h"



Deck::Deck(int lands) {
    this->lands = lands;
    this->spells = 60-lands;
};

void Deck::setLands(int w, int b, int g, int swb, int swg, int sbg, int cwb, int cwg, int cbg) {
    this->w = w;
    this->b = b;
    this->g = g;

    this->swb = swb;
    this->swg = swg;
    this->sbg = sbg;

    this->cwb = cwb;
    this->cwg = cwg;
    this->cbg = cbg;
}

void Deck::shuffle(int lands) {
    this->lands = lands;
    this->spells = 60-lands;
}

Land Deck::drawColor() {
    std::uniform_int_distribution<int> distribution(1,lands);
    int card = distribution(generator);
    if(card <= w) {
        w--;
        return basicWhite;
    }
    card -= w;
    if(card <= b) {
        b--;
        return basicBlue;
    }
    card -= b;
    if(card <= g) {
        g--;
        return basicGreen;
    }
    card -= g;

    if(card <= sbg) {
        sbg--;
        return shockBG;
    }
    card -= sbg;
    if(card <= swb) {
        swb--;
        return shockBW;
    }
    card -= swb;
    if(card <= swg) {
        swg--;
        return shockGW;
    }
    card -= swg;

    if(card <= cbg) {
        cbg--;
        return checkBG;
    }
    card -= cbg;
    if(card <= cwb) {
        cwb--;
        return checkBW;
    }
    card -= cwb;
    if(card <= cwg) {
        cwg--;
        return checkGW;
    }
    throw std::exception();
}

int Deck::drawLand() {
    std::uniform_int_distribution<int> distribution(1,lands+spells);
    if(distribution(generator) <= lands) {
        lands--;
        return 1;
    }
    spells--;
    return 0;
}

int Deck::scryDrawForSpell() {
    std::uniform_int_distribution<int> distribution(1,lands+spells);
    if(distribution(generator) <= lands) {
        if(distribution(generator) <= lands) {
            lands--;
            return 1;
        }
    }
    spells--;
    return 0;
}


int Deck::scryDrawForLand() {
    std::uniform_int_distribution<int> distribution(1,lands+spells);
    if(distribution(generator) <= lands) {
        lands--;
        return 1;
    }
    if(distribution(generator) <= lands) {
        lands--;
        return 1;
    }
    spells--;
    return 0;
}


int Deck::numberOfLandsInHand(int size) {
    int numberOfLands = 0;
    for(int i=0; i<size; i++) {
        if(drawLand()) {
            numberOfLands++;
        }
    }
    return numberOfLands;
}