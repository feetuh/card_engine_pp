#pragma once

#include "card_engine_pp/board.hpp"
#include "card_engine_pp/card.hpp"
#include "card_engine_pp/operation.hpp"

// there needs to be a system for validators that describe generic moves
// MoveCards<1, CardConstraint, FromConstraint_1, ToConstraint2>(from, to);
// and there needs to be operations that actually describe the
// action being taken
// could chain together into single move:
// InSequence<
//    MoveCards<NumberOfCards, CardConstraint, FromConstraint_1, ToConstraint2>,
//    MoveCards<1umberOfCards, CardConstraint, FromConstraint_1, ToConstraint2>,
//    MoveCards<1umberOfCards, CardConstraint, FromConstraint_1, ToConstraint2>
// >

namespace card_engine_pp
{

using card_vec_it = std::vector<card>::iterator;

// NumberOfCards
// AnyNumber
// Exact<N>
// UpTo<N>
// PlayerCount
// OtherPlayerCount

namespace constraints
{

template<typename NumberOfCards>
struct move_cards
{
  auto operator()(const op_move_cards& operation) -> bool
  {
    return NumberOfCards::conforms(operation.cards());
  }
};

struct any_number
{
  static auto conforms(const std::vector<card_vec_it>& targets) -> bool;
};

// CardConstraint
// AnyOf
// OneOf
// MatchingSuit
// MatchingColour
// HigherThan
// LowerThan
// Or (combination)

// {FromConstraint}
// FromCurrentPlayer
// FromAnyPlayer
// FromNextPlayer
// FromSites -- ids
// FromOneOf<>
// FromAnyOf<>

// {ToConstraint}
// ToCurrentPlayer
// ToAnyPlayer
// ToNextPlayer
// ToSites -- ids
// ToOneOf<>
// ToAnyOf<>

// Now for actual operations
// something like:
// Move from stack id cards: [memory addresses] to stack id
// Evaluate against rules defined above
//
//

// - what are the benefits of the following approached
// Move(&state, std::vector<card*>, from, to)
// - ref to each card
// - ref might not exist? Could be unsafe?
// - state means we can do general board validation too
// - use from to query state
// - use to to push to state
// Move(&state, from, std::vector<int>, to)
// - index
// - might be out of bounds?
// - oob is easy to check though
// - the indexes change as we remove cards
// - if we're doing a swap, refs don't change

// class target_selector
// {
// public:
//   auto invoke(board&, ) const -> void;
// };

// define a series of common operations

// shuffle stack
// move card (any)
// move n_card (any)
// move card (specific)
// move n_card (specific)

}  // namespace constraints

}  // namespace card_engine_pp
