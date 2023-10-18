#include <string>

#include "card_engine_pp/constraint.hpp"

#include <catch2/catch_test_macros.hpp>

using card_engine_pp::board;
using card_engine_pp::card;
using card_engine_pp::op_move_cards;
using card_engine_pp::rank;
using card_engine_pp::site;
using card_engine_pp::suit;
using card_engine_pp::constraints::move_cards;

TEST_CASE("Constraint for moving any card conforms", "[library]")
{
  card ace_of_spades {suit::spade, rank::ace};
  site hand;
  hand.m_cards.emplace_back(ace_of_spades);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  auto my_hand = state->m_sites.find("my_hand");
  auto my_card = my_hand->second.m_cards.begin();

  op_move_cards operation {state, "my_hand", {my_card}, "other_hand"};

  REQUIRE(move_cards<card_engine_pp::constraints::any_number>()(operation)
          == true);
}
