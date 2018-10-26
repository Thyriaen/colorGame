//
// Created by thyriaen on 25.10.18.
//

#include <vector>
#include <iostream>

enum Land { basicBlue = 0,
        basicGreen = 1,
        basicWhite = 2,
        shockBG = 3,
        shockBW = 4,
        shockGW = 5,
        checkBG = 6,
        checkBW = 7,
        checkGW = 8 };

int main() {

    /**
     *  0000 0001 0002 0003 0004 0005 0006 0007 0008
     *       0011 0012 0013 0014 0015 0016 0017 0018
     *            0022 0023 0024 0025 0026 0027 0028
     *                 0033
     */

    std::vector<unsigned char> ratings(495,0);
    for(int i=0; i<9; i++) {
        for(int j=i; j<9; j++) {
            for(int k=j; k<9; k++) {
                for(int l=k; l<9; l++) {




                }
            }
        }
    }

}
