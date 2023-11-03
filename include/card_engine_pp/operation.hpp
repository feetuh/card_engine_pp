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
                         std::vector<uint8_t> card_ids,
                         std::string to_site);

  auto operator()() const -> bool;

  auto state() const -> const std::shared_ptr<board>&;
  auto site() const -> const std::string&;
  auto card_ids() const -> const std::vector<uint8_t>&;
  auto to_site() const -> const std::string&;

private:
  std::shared_ptr<board> m_state;
  std::string m_site;
  std::vector<uint8_t> m_card_ids;
  std::string m_to_site;
};

}  // namespace card_engine_pp
