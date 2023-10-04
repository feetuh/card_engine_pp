#pragma once

#include <functional>

#include <boost/functional/hash.hpp>

namespace card_engine_pp
{

enum class suit
{
  club,
  diamond,
  heart,
  spade,
};

enum class rank
{
  ace,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten,
  jack,
  queen,
  king,
};

enum class direction
{
  up,
  down,
};

struct card
{
  explicit card(suit card_suit,
                rank card_rank,
                direction card_dir = direction::up)
      : suit(card_suit)
      , rank(card_rank)
      , dir(card_dir)
  {
  }

  auto operator==(const card& other) const -> bool
  {
    // note: eq ignores direction
    return suit == other.suit && rank == other.rank;
  }

  enum suit suit;
  enum rank rank;
  enum direction dir;
};

}  // namespace card_engine_pp

namespace std
{

template<>
struct hash<card_engine_pp::card>
{
  auto operator()(const card_engine_pp::card& card) const -> size_t
  {
    // note: hash ignores direction
    size_t hash_1 = hash<int> {}(static_cast<int>(card.rank));
    const size_t hash_2 = hash<int> {}(static_cast<int>(card.suit));
    boost::hash_combine(hash_1, hash_2);
    return hash_1;
  }
};
}  // namespace std
