#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"

#include <iostream>
#include "Point.h"


TEST_CASE( "Testing single points and whiteness") {

    Point myPoint;
    myPoint.setGreen(20);
    myPoint.setBlue(10);
    myPoint.setRed(50);

    REQUIRE( myPoint.whiteness() == 10 );

    myPoint.setGreen(5);

    REQUIRE( myPoint.whiteness() == 5 );


    // todo handle this
    myPoint.setGreen(-20);

    REQUIRE( myPoint.whiteness() == 5 );

}