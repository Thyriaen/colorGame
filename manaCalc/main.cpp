#include <iostream>
#include <iomanip>

#include "Deck.h"


void drawBased(int turn) {
    std::cout << turn << ". turn OnDraw" << std::endl;

    for(int i = 24; i < 27; i++) {
        int tries = 100000;
        int hit = 0;
        int flood = 0;
        for (auto j = 0; j < tries; j++) {

            Deck myDeck(i);
            int lands = myDeck.numberOfLandsInHand(7);
            if (lands > 1 && lands < 5) {
                if(myDeck.drawLand()) {
                    lands++;
                }
            } else {
                myDeck.shuffle(i);
                lands = myDeck.numberOfLandsInHand(6);
                if (lands > 1 && lands < 5) {
                } else {
                    myDeck.shuffle(i);
                    lands = myDeck.numberOfLandsInHand(5);
                    if (lands > 0 && lands < 5) {
                    } else {
                        myDeck.shuffle(i);
                        lands = myDeck.numberOfLandsInHand(4);
                    }
                }
                if(lands > 2) {
                    if(myDeck.scryDrawForSpell()) {
                        lands++;
                    }
                }
                if(myDeck.scryDrawForLand()) {
                    lands++;
                }
            }

            for(int a = 0; a < turn-1; a++) {
                if(myDeck.drawLand()) {
                    lands++;
                }
            }

            if(lands > turn-1) {
                hit++;
            }
            if(lands < turn+2) {
                flood++;
            }
        }

        std::cout << i << " Lands: "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (hit) / (1.0 * tries) * 100  << "%" << " Hit and "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (flood) / (1.0 * tries) * 100  << "%" << " not Flood "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (flood+hit) / (2.0 * tries) * 100  << "%" << " Total "
                  << std::endl;
    }

    std::cout << "==================================" << std::endl;
}

void turnBased(int turn) {
    std::cout << turn << ". turn OnTurn" << std::endl;

    for(int i = 24; i < 27; i++) {
        int tries = 100000;
        int hit = 0;
        int flood = 0;
        for (auto j = 0; j < tries; j++) {

            Deck myDeck(i);
            int lands = myDeck.numberOfLandsInHand(7);
            if (lands > 1 && lands < 5) {
                if(myDeck.drawLand()) {
                    lands++;
                }
            } else {
                myDeck.shuffle(i);
                lands = myDeck.numberOfLandsInHand(6);
                if (lands > 1 && lands < 5) {
                } else {
                    myDeck.shuffle(i);
                    lands = myDeck.numberOfLandsInHand(5);
                    if (lands > 0 && lands < 5) {
                    } else {
                        myDeck.shuffle(i);
                        lands = myDeck.numberOfLandsInHand(4);
                    }
                }
                if(lands > 2) {
                    if(myDeck.scryDrawForSpell()) {
                        lands++;
                    }
                }
                if(myDeck.scryDrawForLand()) {
                    lands++;
                }
            }

            for(int a = 0; a < turn-2; a++) {
                if(myDeck.drawLand()) {
                    lands++;
                }
            }

            if(lands > turn-1) {
                hit++;
            }
            if(lands < turn+2) {
                flood++;
            }
        }

        std::cout << i << " Lands: "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (hit) / (1.0 * tries) * 100  << "%" << " Hit and "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (flood) / (1.0 * tries) * 100  << "%" << " not Flood "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 2 ) << std::setfill( '0' )
                  << (flood+hit) / (2.0 * tries) * 100  << "%" << " Total "
                  << std::endl;
    }

    std::cout << "==================================" << std::endl;
}



void starting() {
    std::cout << "No Mulligans with:" << std::endl;
    for(int i = 24; i < 27; i++) {
        int tries = 100000;
        int hit = 0;
        for(auto j=0; j<tries; j++) {
            Deck myDeck(i);
            int hand = myDeck.numberOfLandsInHand(7);
            if(hand > 1 && hand < 5) {
                hit++;
            }
        }
        std::cout << i << " Lands: "
                  << std::fixed << std::setw( 3 ) << std::setprecision( 1 ) << std::setfill( '0' )
                  << hit / (tries * 1.0) * 100 << "%" << std::endl;
    }

    std::cout << "=================" << std::endl;
}

int main() {
    turnBased(4);
    drawBased(4);
    starting();

    return 0;
}