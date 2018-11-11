#include <iostream>
#include <iomanip>
#include <set>
#include <fstream>

#include "Deck.h"

bool isBlue(Land land, bool plai, bool fore, bool isla ) {
    switch(land) {
        case (basicBlue) :
            return true;
        case (basicWhite) :
            return false;
        case(basicGreen) :
            return false;
        case(checkBG) :
            return (isla || fore);
        case(checkBW) :
            return (isla || plai);
        case(checkGW) :
            return false;
        default:
            return false;
    }
}

bool isWhite(Land land, bool plai, bool fore, bool isla ) {
    switch(land) {
        case (basicBlue) :
            return false;
        case (basicWhite) :
            return true;
        case(basicGreen) :
            return false;
        case(checkBG) :
            return false;
        case(checkBW) :
            return (isla || plai);
        case(checkGW) :
            return (plai || fore);
        default:
            return false;
    }
}

bool isGreen(Land land, bool plai, bool fore, bool isla) {
    switch(land) {
        case (basicBlue) :
            return false;
        case (basicWhite) :
            return false;
        case(basicGreen) :
            return true;
        case(checkBG) :
            return (isla || fore);
        case(checkBW) :
            return false;
        case(checkGW) :
            return (plai || fore);
        default:
            return false;
    }
}

bool isPlayable(Land land, bool plai, bool fore, bool isla) {
    switch(land) {
        case (basicBlue) :
            return true;
        case (basicWhite) :
            return true;
        case(basicGreen) :
            return true;
        case(checkBG) :
            return (isla || fore);
        case(checkBW) :
            return (isla || plai);
        case(checkGW) :
            return (plai || fore);
        default:
            return false;
    }
}

Land playLand(int turn, std::multiset<Land>* hand, bool plai, bool fore, bool isla, int w, int b, int g) {
    if(turn == 1) {
        int shocker = 0;
        int checker = 0;
        bool sgw = false;
        bool sbg = false;
        bool sbw = false;
        bool cgw = false;
        bool cbg = false;
        bool cbw = false;
        bool island = false;
        bool plain = false;
        bool forest = false;
        int blue = 0;
        int white = 0;
        int green = 0;
        for (auto elem: *hand) {
            switch (elem) {
                case (basicBlue) :
                    blue++;
                    island = true;
                    break;
                case (basicGreen) :
                    green++;
                    forest = true;
                    break;
                case (basicWhite) :
                    white++;
                    plain = true;
                    break;
                case (checkGW) :
                    green++;
                    white++;
                    if (!cgw) {
                        checker++;
                    }
                    cgw = true;
                    break;
                case (checkBW) :
                    blue++;
                    white++;
                    if (!cbw) {
                        checker++;
                    }
                    cbw = true;
                    break;
                case (checkBG) :
                    blue++;
                    green++;
                    if (!cbg) {
                        checker++;
                    }
                    cbg = true;
                    break;
                case (shockGW) :
                    if (!sgw) {
                        shocker++;
                    }
                    sgw = true;
                    break;
                case (shockBW) :
                    if (!sbw) {
                        shocker++;
                    }
                    sbw = true;
                    break;
                case (shockBG) :
                    if (!sbg) {
                        shocker++;
                    }
                    sbg = true;
                    break;
                default:
                    throw std::exception();
            }
        }
        switch (shocker) {
            case (1) :
                if (sgw) return shockGW;
                if (sbg) return shockBG;
                if (sbw) return shockBW;
                break;
            case (2) :
                if (!sgw) {
                    if (white > green) return shockBG;
                    return shockBW;
                }
                if (!sbg) {
                    if (green > blue) return shockBW;
                    return shockGW;
                }
                if (!sbw) {
                    if (white > blue) return shockBG;
                    return shockGW;
                }
                throw std::exception();
            case (3) :
                if (blue == 0) {
                    if (white > green) return shockBG;
                    return shockBW;
                }
                return shockGW;
            default:
                switch (checker) {
                    case (1) :
                        if (cgw) return checkGW;
                        if (cbg) return checkBG;
                        if (cbw) return checkBW;
                        break;
                    case (2) :
                        if (!cgw) {
                            if (white > green) return checkBG;
                            return checkBW;
                        }
                        if (!cbg) {
                            if (green > blue) return checkBW;
                            return checkGW;
                        }
                        if (!cbw) {
                            if (white > blue) return checkBG;
                            return checkGW;
                        }
                        throw std::exception();
                    case (3) :
                        if (blue == 0) {
                            if (white > green) return checkBG;
                            return checkBW;
                        }
                        return checkGW;
                    default:
                        if (island) return basicBlue;
                        if (forest) return basicGreen;
                        if (plain) return basicWhite;
                        return noLand;
                }
        }
    }

    if(turn == 2) {
        if(b >= 1) {
            if(g < 1) {
                for (auto elem: *hand) {
                    if (isGreen(elem, plai, fore, isla)) {
                        return elem;
                    }
                }
            }
            for (auto elem: *hand) {
                if (isPlayable(elem, plai, fore, isla)) {
                    return elem;
                }
            }
            return noLand;
        }
        for (auto elem: *hand) {
            if (isBlue(elem, plai, fore, isla)) {
                return elem;
            }
        }
        return noLand;
    }
    if(turn == 3) {
        if(g >= 1) {
            if(w  < 2) {
                for (auto elem: *hand) {
                    if (isWhite(elem, plai, fore, isla)) {
                        return elem;
                    }
                }
            }
            for (auto elem: *hand) {
                if (isPlayable(elem, plai, fore, isla)) {
                    return elem;
                }
            }
            return noLand;
        }
        for (auto elem: *hand) {
            if (isGreen(elem, plai, fore, isla)) {
                return elem;
            }
        }
        return noLand;
    }
    if(turn == 4) {
        if(w < 2) {
            for (auto elem: *hand) {
                if (isWhite(elem, plai, fore, isla)) {
                    return elem;
                }
            }
            return noLand;
        }
        for (auto elem: *hand) {
            if (isPlayable(elem, plai, fore, isla)) {
                return elem;
            }
        }
        return noLand;
    }
}

bool update(std::multiset<Land>* hand, bool* plai, bool* fore, bool* isla, int* w, int* b, int* g, Land newLand) {
    switch(newLand) {
        case (basicBlue) :
            *isla = true;
            (*b)++;
            hand->erase(hand->find(newLand));
            break;
        case (basicWhite) :
            *plai = true;
            (*w)++;
            hand->erase(hand->find(newLand));
            break;
        case(basicGreen) :
            *fore = true;
            (*g)++;
            hand->erase(hand->find(newLand));
            break;
        case(checkBG) :
            (*b)++;
            (*g)++;
            hand->erase(hand->find(newLand));
            break;
        case(checkBW) :
            (*b)++;
            (*w)++;
            hand->erase(hand->find(newLand));
            break;
        case(checkGW) :
            (*g)++;
            (*w)++;
            hand->erase(hand->find(newLand));
            break;
        case(shockBG) :
            *isla = true;
            (*b)++;
            *fore = true;
            (*g)++;
            hand->erase(hand->find(newLand));
            break;
        case(shockBW) :
            *isla = true;
            (*b)++;
            *plai = true;
            (*w)++;
            hand->erase(hand->find(newLand));
            break;
        case(shockGW) :
            *fore = true;
            (*g)++;
            *plai = true;
            (*w)++;
            hand->erase(hand->find(newLand));
            break;
        case(noLand) :
            return false;
    }
    return true;
}

double manaDraw(int tries, int w, int b, int g, int swb, int swg, int sbg, int cwb, int cwg, int cbg) {
    int i=w+b+g+swb+swg+sbg+cwb+cwg+cbg;
    int hit = 0;
    for (auto j = 0; j < tries; j++) {

        Deck myDeck(i);
        std::multiset<Land> hand;
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
        myDeck.setLands(w,b,g,swb,swg,sbg,cwb,cwg,cbg);
        for (int k = 0; k < lands; k++) {
            hand.insert(myDeck.drawColor());
        }
        // turn 1
        bool plains = false;
        bool forest = false;
        bool island = false;
        int pl = 0;
        int fo = 0;
        int is = 0;

        Land newLand;
        newLand = playLand(1, &hand, plains, forest, island, pl ,fo ,is);
        bool succ = false;
        succ = update(&hand, &plains, &forest, &island, &pl, &fo, &is, newLand);

        // turn 2-4
        for(int a = 0; a < 3; a++) {
            if(succ) {
                if(myDeck.drawLand()) {
                    lands++;
                    hand.insert(myDeck.drawColor());
                }
                newLand = playLand(a+2, &hand, plains, forest, island, pl ,fo ,is );
                succ = update(&hand, &plains, &forest, &island, &pl, &fo, &is, newLand);
            }
        }
        if (succ) {
            hit++;
        }
    }

    return hit / (tries *1.0);
}

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
    /*
    turnBased(4);
    drawBased(4);
    starting();
    */

    std::ofstream csvFile;
    double threshold = 0.51;
    double best = threshold;

    csvFile.open("stats.csv", std::ios_base::app);
    csvFile << "w, b, g, cwb, cwg, cbg, swb, swg, sbg, value" << std::endl;

    for(int w=5; w<=6; w++) {
        for(int b=3; b<=4; b++) {
            for(int g=1; g<=2; g++) {
                for(int swb=0; swb<=0; swb++) {
                    for(int swg=3; swg<=4; swg++) {
                        for(int sbg=0; sbg<=0; sbg++) {
                            for(int cwb=4; cwb<=4; cwb++) {
                                for(int cwg=3; cwg<=4; cwg++) {
                                    for(int cbg=3; cbg<=4; cbg++) {
                                        if(w+b+g+swb+swg+sbg+cwb+cwg+cbg == 24) {
                                            if(manaDraw(5000,w,b,g,swb,swg,sbg,cwb,cwg,cbg) > 0.50) {
                                                double value = manaDraw(1000000,w,b,g,swb,swg,sbg,cwb,cwg,cbg);
                                                if(value >= best) {
                                                    std::cout << "New best candidate found: "
                                                              << w << " " << b << " " << g << " :: "
                                                              << cwb << " " << cwg << " " << cbg << " :: "
                                                              << swb << " " << swg << " " << sbg
                                                              << " with " << value * 100 << "%" << std::endl;
                                                    best = value;
                                                }
                                                if(value >= threshold) {
                                                    csvFile  << w << "," << b << "," << g << ","
                                                             << cwb << "," << cwg << "," << cbg << ","
                                                             << swb << "," << swg << "," << sbg
                                                             << "," << value << std::endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}