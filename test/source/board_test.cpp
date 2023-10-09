#include <string>

#include "card_engine_pp/board.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Can create board", "[library]")
{
  using card_engine_pp::board;
  using card_engine_pp::card;
  using card_engine_pp::rank;
  using card_engine_pp::site;
  using card_engine_pp::suit;

  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace);

  board state;
  state.m_sites.emplace_back(std::move(hand));
}
