#include <string>

#include "card_engine_pp/card.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Can create card", "[library]")
{
  using card_engine_pp::card;
  using card_engine_pp::card_id_generator;
  using card_engine_pp::rank;
  using card_engine_pp::suit;

  card_id_generator generator;

  card_engine_pp::card card_1 {suit::spade, rank::ace, generator};
  REQUIRE(card_1.m_suit == suit::spade);
  REQUIRE(card_1.m_rank == rank::ace);
}
