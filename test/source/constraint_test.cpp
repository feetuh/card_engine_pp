#include <string>

#include "card_engine_pp/constraint.hpp"

#include <catch2/catch_test_macros.hpp>

using card_engine_pp::board;
using card_engine_pp::card;
using card_engine_pp::card_id_generator;
using card_engine_pp::op_move_cards;
using card_engine_pp::rank;
using card_engine_pp::site;
using card_engine_pp::suit;
using card_engine_pp::constraints::move_cards;

TEST_CASE("Constraint for moving one card for any_number conforms", "[library]")
{
  card_id_generator generator;
  card ace_of_spades {suit::spade, rank::ace, generator};
  site hand;
  hand.m_cards.emplace_back(ace_of_spades);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  op_move_cards operation {state, "my_hand", {0}, "other_hand"};

  REQUIRE(move_cards<card_engine_pp::constraints::any_number>()(operation)
          == true);
}

TEST_CASE("Constraint for moving two cards for any_number conforms",
          "[library]")
{
  card_id_generator generator;
  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace, generator);
  hand.m_cards.emplace_back(suit::spade, rank::two, generator);
  hand.m_cards.emplace_back(suit::spade, rank::three, generator);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  auto my_hand = state->m_sites.find("my_hand");

  op_move_cards operation {state, "my_hand", {0, 1}, "other_hand"};

  REQUIRE(move_cards<card_engine_pp::constraints::any_number>()(operation)
          == true);
  operation();
  REQUIRE(my_hand->second.m_cards.size() == 1);
}

TEST_CASE("Constraint for moving one card for n_cards<1> conforms", "[library]")
{
  card_id_generator generator;
  site hand;
  hand.m_cards.emplace_back(suit::spade, rank::ace, generator);
  hand.m_cards.emplace_back(suit::spade, rank::two, generator);
  hand.m_cards.emplace_back(suit::spade, rank::three, generator);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  auto my_hand = state->m_sites.find("my_hand");

  op_move_cards operation {state, "my_hand", {0}, "other_hand"};

  REQUIRE(move_cards<card_engine_pp::constraints::n_cards<1>>()(operation)
          == true);
  operation();
  REQUIRE(my_hand->second.m_cards.size() == 2);
}

TEST_CASE(
    "Constraint for moving one suited card for any_number, matches_suit "
    "conforms",
    "[library]")
{
  card_id_generator generator;
  card ace_of_spades {suit::spade, rank::ace, generator};
  site hand;
  hand.m_cards.emplace_back(ace_of_spades);

  auto state = std::make_shared<board>();
  state->add_site(hand, "my_hand", "players");
  state->add_site(site {}, "other_hand", "players");

  op_move_cards operation {state, "my_hand", {0}, "other_hand"};

  REQUIRE(move_cards<card_engine_pp::constraints::any_number,
                     card_engine_pp::constraints::matches_suit<
                         card_engine_pp::suit::spade>>()(operation)
          == true);
}
