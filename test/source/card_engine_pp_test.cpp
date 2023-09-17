#include <string>

#include "card_engine_pp/card_engine_pp.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is card_engine_pp", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("card_engine_pp") == exported.name());
}
