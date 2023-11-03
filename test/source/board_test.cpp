#include <string>

#include "card_engine_pp/board.hpp"

#include <catch2/catch_test_macros.hpp>

using card_engine_pp::board;
using card_engine_pp::card_id_generator;
using card_engine_pp::rank;
using card_engine_pp::site;
using card_engine_pp::suit;

TEST_CASE("Can create board", "[library]")
{
  card_id_generator generator;
  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace, generator);

  board state;
  state.add_site(std::move(hand), "hand");
  REQUIRE(state.m_sites.size() == 1);
  REQUIRE(state.m_sites.at("hand").m_cards.size() == 1);
  REQUIRE(state.m_sites.at("hand").m_cards.front().m_suit == suit::spade);
  REQUIRE(state.m_sites.at("hand").m_cards.front().m_rank == rank::ace);
}

TEST_CASE("Can add to group", "[library]")
{
  card_id_generator generator;
  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace, generator);

  board state;
  state.add_site(std::move(hand), "hand", "players");
  REQUIRE(state.m_sites.size() == 1);
  REQUIRE(state.m_group_to_sites.size() == 1);
  REQUIRE(state.m_group_to_sites.find("players")
          != state.m_group_to_sites.end());
}

TEST_CASE("Can't add duplicate site", "[library]")
{
  card_id_generator generator;
  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace, generator);

  board state;
  state.add_site(hand, "hand", "players");
  REQUIRE_THROWS(state.add_site(std::move(hand), "hand"));
}
