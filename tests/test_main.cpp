#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_USE_ASYNC

#include <b64.hpp>

#include <catch2/catch.hpp>

using namespace Catch::Matchers;
using namespace std;

TEST_CASE("Empty string encode") {
  constexpr auto input = "";

  const auto encoded = b64::encode(input);
  REQUIRE_THAT(encoded, Equals(""));

  const auto decoded = b64::decode(encoded);
  REQUIRE_THAT(input, Equals(decoded));

  REQUIRE(0 == encoded.length());
}

TEST_CASE("a") {
  constexpr auto input = "a";

  const auto encoded = b64::encode(input);
  REQUIRE_THAT(encoded, Equals("YQ=="));

  const auto decoded = b64::decode(encoded);
  REQUIRE_THAT(input, Equals(decoded));

  REQUIRE(4 == encoded.length());
}

TEST_CASE("public static void main") {
  constexpr auto input = "public static void main";

  const auto encoded = b64::encode(input);
  REQUIRE_THAT(encoded, Equals("cHVibGljIHN0YXRpYyB2b2lkIG1haW4="));

  const auto decoded = b64::decode(encoded);
  REQUIRE_THAT(input, Equals(decoded));

  REQUIRE(32 == encoded.length());
}

TEST_CASE("std find") {
  constexpr auto input =
      "Finds the first substring equal to the given character sequence. Search "
      "begins at pos, i.e. the found substring must not begin in a position "
      "preceding pos.";

  const auto encoded = b64::encode(input);
  REQUIRE_THAT(
      encoded,
      Equals("RmluZHMgdGhlIGZpcnN0IHN1YnN0cmluZyBlcXVhbCB0byB0aGUgZ2l2ZW4gY"
             "2hhcmFjdGVyIHNlcXVlbmNlLiBTZWFyY2ggYmVnaW5zIGF0IHBvcywgaS5lLi"
             "B0aGUgZm91bmQgc3Vic3RyaW5nIG11c3Qgbm90IGJlZ2luIGluIGEgcG9zaXR"
             "pb24gcHJlY2VkaW5nIHBvcy4="));

  const auto decoded = b64::decode(encoded);
  REQUIRE_THAT(input, Equals(decoded));

  REQUIRE(208 == encoded.length());
}
