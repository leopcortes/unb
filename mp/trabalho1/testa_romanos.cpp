#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "romanos.hpp"

TEST_CASE( "Números romanos - algarismos únicos", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("I") == 1 );
    REQUIRE( romanos_para_decimal("V") == 5 );
    REQUIRE( romanos_para_decimal("X") == 10 );
    REQUIRE( romanos_para_decimal("L") == 50 );
    REQUIRE( romanos_para_decimal("C") == 100 );
    REQUIRE( romanos_para_decimal("D") == 500 );
    REQUIRE( romanos_para_decimal("M") == 1000 );
}

TEST_CASE( "Números romanos - algarismos combinados", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("IV") == 4 );
    REQUIRE( romanos_para_decimal("IX") == 9 );
    REQUIRE( romanos_para_decimal("XLIX") == 49 );
    REQUIRE( romanos_para_decimal("XCIX") == 99 );
    REQUIRE( romanos_para_decimal("CDXCIX") == 499 );
    REQUIRE( romanos_para_decimal("CMXCIX") == 999 );
}

TEST_CASE( "Números romanos - algarismos inválidos", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("i") == -1 );
    REQUIRE( romanos_para_decimal("v") == -1 );
    REQUIRE( romanos_para_decimal("x") == -1 );
    REQUIRE( romanos_para_decimal("l") == -1 );
    REQUIRE( romanos_para_decimal("c") == -1 );
    REQUIRE( romanos_para_decimal("d") == -1 );
    REQUIRE( romanos_para_decimal("m") == -1 );
    REQUIRE( romanos_para_decimal("G") == -1 );
    REQUIRE( romanos_para_decimal("H") == -1 );
    REQUIRE( romanos_para_decimal("1") == -1 );
    REQUIRE( romanos_para_decimal("10") == -1 );
    REQUIRE( romanos_para_decimal("XXXX") == -1 );
    REQUIRE( romanos_para_decimal("VV") == -1 );
    REQUIRE( romanos_para_decimal("VX") == -1 );
}

TEST_CASE( "Números romanos - fora do alcançe", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("MMMI") == -1 );
    REQUIRE( romanos_para_decimal("MMMDCCCLXXXVIII") == -1 );
    REQUIRE( romanos_para_decimal("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIII") == -1 );
}
 