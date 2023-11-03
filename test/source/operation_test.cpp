#include <string>

#include "card_engine_pp/operation.hpp"

#include <catch2/catch_test_macros.hpp>

using card_engine_pp::board;
using card_engine_pp::card;
using card_engine_pp::card_id_generator;
using card_engine_pp::op_move_cards;
using card_engine_pp::rank;
using card_engine_pp::site;
using card_engine_pp::suit;

TEST_CASE("Can move cards", "[library]")

{
  card_id_generator generator;
  card ace_of_spades {suit::spade, rank::ace, generator};
  site hand;
  hand.m_cards.emplace_back(ace_of_spades);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  // auto my_hand = state->m_sites.find("my_hand");
  // auto my_card = my_hand->second.m_cards.begin();

  op_move_cards {state, "my_hand", {0}, "other_hand"}();

  auto other_hand = state->m_sites.find("other_hand");
  auto& other_cards = other_hand->second.m_cards;

  REQUIRE(other_cards.size() == 1);
  REQUIRE(other_cards.front() == ace_of_spades);
}
