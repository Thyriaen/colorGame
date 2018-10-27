#include <iostream>

double getProb(int x, int xP) {
    double prob = 1;
    for(int i=0; i<x; i++) {
        prob *= (xP-i);
    }
    return prob;
}

double probability(int w, int b, int g, int swb, int swg, int sbg, int cwb, int cwg, int cbg,
        int wP, int bP, int gP, int swbP, int swgP, int sbgP, int cwbP, int cwgP, int cbgP) {
    double probability = 1;
    probability *= getProb(w, wP);
    probability *= getProb(b, bP);
    probability *= getProb(g, gP);

    probability *= getProb(swb, swbP);
    probability *= getProb(sbg, sbgP);
    probability *= getProb(swg, swgP);

    probability *= getProb(cwb, cwbP);
    probability *= getProb(cbg, cbgP);
    probability *= getProb(cwg, cwgP);

    if(w == 3 || b == 3 || g == 3 || swg == 3 || sbg == 3 || swg == 3 || cwb == 3 || cbg == 3 || cwg == 3) {
        probability *= 4;
    } else {
        if(w == 2 || b == 2 || g == 2 || swg == 2 || sbg == 2 || swg == 2 || cwb == 2 || cbg == 2 || cwg == 2) {
            probability *= 3;
            if(w == 1 || b == 1 || g == 1 || swg == 1 || sbg == 1 || swg == 1 || cwb == 1 || cbg == 1 || cwg == 1) {
                probability *= 4;
            } else {
                probability *= 3;
            }
        } else {
            probability *= 24;
        }
    }

    return probability / (25.0 * 24 * 23 * 22);
}

int getValue(int w, int b, int g, int swb, int swg, int sbg, int cwb, int cwg, int cbg) {
    int sBlueCount = b + cwb + cbg;
    int sWhiteCount = w + cwb + cwg;
    int sGreenCount = g + cwg + cbg;
    if(swb == 1 && swg == 0 && sbg == 0 && sBlueCount >= 1 && sWhiteCount >= 1 && sGreenCount >= 1) {
        return 1;
    }
    if(swb == 0 && swg == 1 && sbg == 0 && sBlueCount >= 2 && sWhiteCount >= 1) {
        return 1;
    }
    if(swb == 0 && swg == 0 && sbg == 1 && sWhiteCount >= 2 && sBlueCount >= 1) {
        return 1;
    }
    int wBlueCount = b + cwb + cwg;
    int wWhiteCount = w + cwb;
    int wGreenCount = g + cwg;
    if(w >= 1 && wBlueCount >= 2 && wWhiteCount >= 2 && wGreenCount >= 1) {
        return 1;
    }
    int bBlueCount = b + cwb + cbg;
    int bWhiteCount = w + cwb;
    int bGreenCount = g + cbg;
    if(b >= 1 && bBlueCount >= 2 && bWhiteCount >= 2 && bGreenCount >= 1) {
        return 1;
    }
    return 0;
}

double maximize(int wP, int bP, int gP, int swbP, int swgP, int sbgP, int cwbP, int cwgP, int cbgP) {
    double value = 0;
    for(int w=0; w<=wP; w++) {
        for(int b=0; b<=bP; b++) {
            for(int g=0; g<=gP; g++) {
                for(int swb=0; swb<=swbP; swb++) {
                    for(int swg=0; swg<=swgP; swg++) {
                        for(int sbg=0; sbg<=sbgP; sbg++) {
                            for(int cwb=0; cwb<=cwbP; cwb++) {
                                for(int cwg=0; cwg<=cwgP; cwg++) {
                                    for(int cbg=0; cbg<=cbgP; cbg++) {
                                        if(w+b+g+swb+swg+sbg+cwb+cwg+cbg == 4) {
                                            value += getValue(w,b,g,swb,swg,sbg,cwb,cwg,cbg) *
                                                    probability(w,b,g,swb,swg,sbg,cwb,cwg,cbg,
                                                            wP,bP,gP,swbP,swgP,sbgP,cwbP,cwgP,cbgP);
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

int main() {

    double best = 0;

    for(int w=0; w<=5; w++) {
        for(int b=0; b<=25; b++) {
            for(int g=0; g<=25; g++) {
                for(int swb=0; swb<=4; swb++) {
                    for(int swg=0; swg<=4; swg++) {
                        for(int sbg=0; sbg<=4; sbg++) {
                            for(int cwb=0; cwb<=4; cwb++) {
                                for(int cwg=0; cwg<=4; cwg++) {
                                    for(int cbg=0; cbg<=4; cbg++) {
                                        if(w+b+g+swb+swg+sbg+cwb+cwg+cbg == 25) {
                                            double value = maximize(w,b,g,swb,swg,sbg,cwb,cwg,cbg);
                                            if(value >= best) {
                                                std::cout << "New best found: "
                                                << w << " " << b << " " << g << " :: "
                                                << cwb << " " << cwg << " " << cbg << " :: "
                                                << swb << " " << swg << " " << sbg
                                                << " with " << value << std::endl;
                                                best = value;
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