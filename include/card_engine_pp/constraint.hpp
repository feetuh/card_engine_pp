#pragma once

#include <string_view>

#include "card_engine_pp/board.hpp"
#include "card_engine_pp/card.hpp"
#include "card_engine_pp/operation.hpp"
#include "card_engine_pp/util.hpp"

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

struct any_number
{
  static auto conforms(const std::vector<const card*>& targets) -> bool;
};

template<int N>
struct n_cards
{
  static auto conforms(const std::vector<const card*>& targets) -> bool
  {
    return targets.size() == N;
  }
};

// CardConstraint
// AnyOf
// OneOf
// MatchingSuit
// MatchingColour
// HigherThan
// LowerThan
// Or (combination)

struct any_card
{
  static auto conforms(const std::vector<const card*>& targets) -> bool;
};

template<suit S>
struct matches_suit
{
  static auto conforms(const std::vector<const card*>& targets) -> bool
  {
    return std::all_of(targets.begin(),
                       targets.end(),
                       [](const auto& target) { return target->m_suit == S; });
  }
};

// {FromConstraint}
// FromCurrentPlayer
// FromAnyPlayer
// FromNextPlayer
// FromSites -- ids
// FromOneOf<>
// FromAnyOf<>

struct any_site
{
  static auto conforms(const std::string_view site_name) -> bool
  {
    (void)site_name;
    return true;
  }
};

template<string_literal Site>
struct matches_site
{
  static auto conforms(const std::string_view site_name) -> bool
  {
    return site_name == Site.value;
  }
};

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

template<typename CountConstraint,
         typename CardConstraint = any_card,
         typename FromConstraint = any_site>
struct move_cards
{
  auto operator()(const op_move_cards& operation) const -> bool
  {
    const auto& sites = operation.state()->m_sites;
    auto site = sites.find(operation.site());
    if (site == sites.end()) {
      // TODO: use custom exceptions
      throw std::runtime_error("Invalid operation, site not found: "
                               + operation.site());
    }
    std::vector<const card*> cards;
    const auto& card_ids = operation.card_ids();
    for (const auto& current : site->second.m_cards) {
      if (std::find(card_ids.begin(), card_ids.end(), current.m_id)
          != card_ids.end())
      {
        cards.push_back(&current);
      }
    }

    return CountConstraint::conforms(cards) && CardConstraint::conforms(cards)
        && FromConstraint::conforms(operation.site());
  }
};

}  // namespace constraints

}  // namespace card_engine_pp
