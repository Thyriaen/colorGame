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

    std::vector<unsigned char> myVector = myPoint.getRaw();

    REQUIRE( (int)myVector[0] == 10 );
    REQUIRE( (int)myVector[1] == 5 );
    REQUIRE( (int)myVector[2] == 50 );
    REQUIRE( myVector[3] == 0 );
}

TEST_CASE( "new constructor") {
    Point newPoint(30,20,10);
    REQUIRE( newPoint.whiteness() == 10 );
    std::vector<unsigned char> newVector = newPoint.getRaw();

    REQUIRE( (int)newVector[0] == 10 );
    REQUIRE( (int)newVector[1] == 20 );
    REQUIRE( (int)newVector[2] == 30 );
}

TEST_CASE( "Testing a new universe") {
    Universe myUniverse(3,2);

    REQUIRE( myUniverse.getRaw().size() == 24 );

    // todo
    myUniverse.setPixel(0,0, Point(1,10,70));
    myUniverse.setPixel(1,0, Point(2,20,80));
    myUniverse.setPixel(2,0, Point(3,30,90));
    myUniverse.setPixel(0,1, Point(4,40,100));
    myUniverse.setPixel(1,1, Point(5,50,110));
    myUniverse.setPixel(2,1, Point(6,60,120));

    //std::vector<unsigned char> myRawUniverse = myUniverse.getRaw();


}