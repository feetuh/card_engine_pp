#include "card_engine_pp/operation.hpp"

using card_engine_pp::card_vec_it;

auto card_engine_pp::move_cards(board& state,
                                const std::string& from_site,
                                const std::vector<card_vec_it>& cards,
                                const std::string& to_site) -> void
{
  const auto found_from_it = state.m_sites.find(from_site);
  if (found_from_it == std::end(state.m_sites)) {
    // err
    return;
  }

  const auto found_to_it = state.m_sites.find(to_site);
  if (found_to_it == std::end(state.m_sites)) {
    // err
    return;
  }

  auto& from_cards = found_from_it->second.m_cards;

  for (const auto& card_it : cards) {
    found_to_it->second.m_cards.emplace_back(*card_it);
    from_cards.erase(card_it);
  }
}
