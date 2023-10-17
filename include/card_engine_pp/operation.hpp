#pragma once

#include <vector>

#include "card_engine_pp/board.hpp"

namespace card_engine_pp
{

using card_vec_it = std::vector<card>::iterator;

class op_move_cards
{
public:
  explicit op_move_cards(std::shared_ptr<board> state,
                         std::string from_site,
                         std::vector<card_vec_it> cards,
                         std::string to_site);

  auto operator()() -> bool;

private:
  std::shared_ptr<board> m_state;
  std::string m_site;
  std::vector<card_vec_it> m_cards;
  std::string m_to_site;
};

}  // namespace card_engine_pp
