//
// Created by thyriaen on 25.10.18.
//

#include "Deck.h"

Deck::Deck(int lands) {
    this->lands = lands;
    this->spells = 60-lands;
};

void Deck::shuffle(int lands) {
    this->lands = lands;
    this->spells = 60-lands;
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