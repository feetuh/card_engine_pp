#include "card_engine_pp/operation.hpp"

using card_engine_pp::card_vec_it;
using card_engine_pp::op_move_cards;

op_move_cards::op_move_cards(std::shared_ptr<board> state,
                             std::string from_site,
                             std::vector<card_vec_it> cards,
                             std::string to_site)
    : m_state(std::move(state))
    , m_site(std::move(from_site))
    , m_cards(std::move(cards))
    , m_to_site(std::move(to_site))
{
}

auto op_move_cards::op_move_cards::operator()() const -> bool
{
  const auto found_from_it = m_state->m_sites.find(m_site);
  if (found_from_it == std::end(m_state->m_sites)) {
    return false;
  }

  const auto found_to_it = m_state->m_sites.find(m_to_site);
  if (found_to_it == std::end(m_state->m_sites)) {
    return false;
  }

  auto& from_cards = found_from_it->second.m_cards;

  for (const auto& card_it : m_cards) {
    found_to_it->second.m_cards.emplace_back(*card_it);
    from_cards.erase(card_it);
  }
  return true;
}

auto op_move_cards::state() const -> const std::shared_ptr<board>&
{
  return m_state;
}
auto op_move_cards::site() const -> const std::string&
{
  return m_site;
}
auto op_move_cards::cards() const -> const std::vector<card_vec_it>&
{
  return m_cards;
}
auto op_move_cards::to_site() const -> const std::string&
{
  return m_to_site;
}
