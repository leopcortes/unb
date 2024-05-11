// Copyright 2024 - Leonardo P Cortes (200030582)
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "8_rainhas.hpp"

TEST_CASE("teste 1", "[rainhas]") {
  REQUIRE(teste_8_rainhas("teste_8_rainhas.txt") == 0);
}
