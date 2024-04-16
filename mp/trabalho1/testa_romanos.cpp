#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "romanos.hpp"

TEST_CASE( "Numeros romanos - algarismos unicos", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("I") == 1 );
    REQUIRE( romanos_para_decimal("V") == 5 );
    REQUIRE( romanos_para_decimal("X") == 10 );
    REQUIRE( romanos_para_decimal("L") == 50 );
    REQUIRE( romanos_para_decimal("C") == 100 );
    REQUIRE( romanos_para_decimal("D") == 500 );
    REQUIRE( romanos_para_decimal("M") == 1000 );
}

TEST_CASE( "Numeros romanos - algarismos combinados - apenas tres vezes consecutivas", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("I") == 1 );
    REQUIRE( romanos_para_decimal("II") == 2 );
    REQUIRE( romanos_para_decimal("III") == 3 );
    REQUIRE( romanos_para_decimal("X") == 10 );
    REQUIRE( romanos_para_decimal("XX") == 20 );
    REQUIRE( romanos_para_decimal("XXX") == 30 );
    REQUIRE( romanos_para_decimal("C") == 100 );
    REQUIRE( romanos_para_decimal("CC") == 200 );
    REQUIRE( romanos_para_decimal("CCC") == 300 );
    REQUIRE( romanos_para_decimal("M") == 1000 );
    REQUIRE( romanos_para_decimal("MM") == 2000 );
    REQUIRE( romanos_para_decimal("MMM") == 3000 );
}    

TEST_CASE( "Numeros romanos - algarismos combinados - valores somados a letra de maior valor", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("VI") == 6 );
    REQUIRE( romanos_para_decimal("VII") == 7 );
    REQUIRE( romanos_para_decimal("VIII") == 8 );
    REQUIRE( romanos_para_decimal("XI") == 11 );
    REQUIRE( romanos_para_decimal("XII") == 12 );
    REQUIRE( romanos_para_decimal("CI") == 101 );
    REQUIRE( romanos_para_decimal("CII") == 102 );
    REQUIRE( romanos_para_decimal("CIII") == 103 );
    REQUIRE( romanos_para_decimal("CI") == 101 );
    REQUIRE( romanos_para_decimal("DCC") == 700 );
    REQUIRE( romanos_para_decimal("MI") == 1001 );
    REQUIRE( romanos_para_decimal("MX") == 1010 );
}

TEST_CASE( "Numeros romanos - algarismos combinados - valores subtraidos da letra de maior valor", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("IV") == 4 );
    REQUIRE( romanos_para_decimal("IX") == 9 );
    REQUIRE( romanos_para_decimal("XL") == 40 );
    REQUIRE( romanos_para_decimal("CD") == 400 );
    REQUIRE( romanos_para_decimal("CM") == 900 );
}

TEST_CASE( "Numeros romanos - algarismos combinados - outras combinacoes", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("XLIX") == 49 );
    REQUIRE( romanos_para_decimal("XCIX") == 99 );
    REQUIRE( romanos_para_decimal("CDXCIX") == 499 );
    REQUIRE( romanos_para_decimal("CMXCIX") == 999 );
}

TEST_CASE( "Numeros romanos - algarismos invalidos - minusculos", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("i") == -1 );
    REQUIRE( romanos_para_decimal("v") == -1 );
    REQUIRE( romanos_para_decimal("x") == -1 );
    REQUIRE( romanos_para_decimal("l") == -1 );
    REQUIRE( romanos_para_decimal("c") == -1 );
    REQUIRE( romanos_para_decimal("d") == -1 );
    REQUIRE( romanos_para_decimal("m") == -1 );
}

TEST_CASE( "Numeros romanos - algarismos invalidos - outros algarismos", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("G") == -1 );
    REQUIRE( romanos_para_decimal("H") == -1 );
    REQUIRE( romanos_para_decimal("1") == -1 );
    REQUIRE( romanos_para_decimal("5") == -1 );
    REQUIRE( romanos_para_decimal("10") == -1 );
}

TEST_CASE( "Numeros romanos - algarismos invalidos - combinacoes proibidas", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("VV") == -1 );
    REQUIRE( romanos_para_decimal("VX") == -1 );
    REQUIRE( romanos_para_decimal("VL") == -1 );
    REQUIRE( romanos_para_decimal("VC") == -1 );
    REQUIRE( romanos_para_decimal("VD") == -1 );
    REQUIRE( romanos_para_decimal("VM") == -1 );
    REQUIRE( romanos_para_decimal("IIII") == -1 );
    REQUIRE( romanos_para_decimal("XXXX") == -1 );
    REQUIRE( romanos_para_decimal("LLLL") == -1 );
    REQUIRE( romanos_para_decimal("CCCC") == -1 );
    REQUIRE( romanos_para_decimal("DDDD") == -1 );
    REQUIRE( romanos_para_decimal("MMMM") == -1 );
}

TEST_CASE( "Numeros romanos - algarismos invalidos - fora de alcance", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("MMMI") == -1 );
    REQUIRE( romanos_para_decimal("MMMDCCCLXXXVIII") == -1 );
    REQUIRE( romanos_para_decimal("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIII") == -1 );
}

TEST_CASE( "Numeros romanos - outros valores", "[romanos]" ) {
    REQUIRE( romanos_para_decimal("XIV") == 14 );
    REQUIRE( romanos_para_decimal("XXXVIII") == 38 );
    REQUIRE( romanos_para_decimal("LVII") == 57 );
    REQUIRE( romanos_para_decimal("CCXXIX") == 229 );
    REQUIRE( romanos_para_decimal("CCCXCIV") == 394 );
    REQUIRE( romanos_para_decimal("DCCXXI") == 721 );
    REQUIRE( romanos_para_decimal("MXL") == 1040 );
    REQUIRE( romanos_para_decimal("MCCCXXXIX") == 1339 );
    REQUIRE( romanos_para_decimal("MCDXLVI") == 1446 );
    REQUIRE( romanos_para_decimal("MDCCCLXXXIV") == 1884 );
    REQUIRE( romanos_para_decimal("MMXXIV") == 2024 );
    REQUIRE( romanos_para_decimal("MMCCCLXXXVII") == 2387 );
    REQUIRE( romanos_para_decimal("MMCMXLVIII") == 2948 );
}
 