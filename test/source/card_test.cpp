#include <string>

#include "card_engine_pp/card.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Can create card", "[library]")
{
  using card_engine_pp::card;
  using card_engine_pp::rank;
  using card_engine_pp::suit;

  card_engine_pp::card card_1 {suit::spade, rank::ace};
  REQUIRE(card_1.get_suit() == suit::spade);
  REQUIRE(card_1.get_rank() == rank::ace);
}
