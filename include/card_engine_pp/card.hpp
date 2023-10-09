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
      : m_suit(card_suit)
      , m_rank(card_rank)
      , m_dir(card_dir)
  {
  }

  auto operator==(const card& other) const -> bool
  {
    // note: eq ignores direction
    return m_suit == other.m_suit && m_rank == other.m_rank;
  }

  enum suit m_suit;
  enum rank m_rank;
  enum direction m_dir;
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
    size_t hash_1 = hash<int> {}(static_cast<int>(card.m_rank));
    const size_t hash_2 = hash<int> {}(static_cast<int>(card.m_suit));
    boost::hash_combine(hash_1, hash_2);
    return hash_1;
  }
};
}  // namespace std
