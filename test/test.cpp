#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../Point.h"
#include "../Universe.h"


TEST_CASE( "Testing single points and whiteness") {
    Point myPoint;
    myPoint.setGreen(20);
    myPoint.setBlue(10);
    myPoint.setRed(50);

    REQUIRE( myPoint.whiteness() == 10 );

    myPoint.setGreen(5);

    REQUIRE( myPoint.whiteness() == 5 );
}

TEST_CASE( "new constructor") {
    Point newPoint(30,20,10);
    REQUIRE( newPoint.whiteness() == 10 );
}

TEST_CASE( "Testing a new universe") {
    Universe myUniverse(3,2);

    REQUIRE( myUniverse.getRaw().size() == 24 );
}

TEST_CASE( "Testing a new universe again ") {
    Universe myUniverse2(3,5);

    myUniverse2.setPixel(2,1,Point(10,20,30));
    myUniverse2.setPixel(0,4,Point(40,50,60));
    myUniverse2.setPixel(1,2,Point(70,80,90));
    myUniverse2.setPixel(2,0,Point(1,2,3));

    std::vector<unsigned char> rV2 = myUniverse2.getRaw();

    REQUIRE( myUniverse2.getRaw().size() == 60 );

    REQUIRE( rV2[20] == 30 );
    REQUIRE( rV2[21] == 20 );
    REQUIRE( rV2[22] == 10 );
    REQUIRE( rV2[23] == 0 );

    REQUIRE( rV2[48] == 60 );
    REQUIRE( rV2[49] == 50 );
    REQUIRE( rV2[50] == 40 );
    REQUIRE( rV2[51] == 0 );

    REQUIRE( rV2[28] == 90 );
    REQUIRE( rV2[29] == 80 );
    REQUIRE( rV2[30] == 70 );
    REQUIRE( rV2[31] == 0 );

    REQUIRE( rV2[8] == 3 );
    REQUIRE( rV2[9] == 2 );
    REQUIRE( rV2[10] == 1 );
    REQUIRE( rV2[11] == 0 );

    myUniverse2.setPixels(rV2.data());

}

TEST_CASE( "setPoint" ) {
    Universe newUni(1,1);

    newUni.setPixel(0,0,Point(10,20,40));
    std::vector<unsigned char> rV = newUni.getRaw();

    REQUIRE( rV.size() == 4);

    REQUIRE( rV[0] == 40 );
    REQUIRE( rV[1] == 20 );
    REQUIRE( rV[2] == 10 );

}