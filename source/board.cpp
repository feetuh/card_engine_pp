#include "card_engine_pp/board.hpp"

#include <fmt/format.h>

using card_engine_pp::board;

auto board::add_site(site target,
                     std::string site_name,
                     std::optional<std::string> group_name) -> void
{
  const auto added_it =
      m_sites.emplace(std::move(site_name), std::move(target));
  if (!added_it.second) {
    throw std::runtime_error {
        fmt::format("Encountered duplicate site: {}", site_name)};
  }

  if (group_name == std::nullopt) {
    return;
  }

  const auto group_it = m_group_to_sites.try_emplace(*group_name);
  group_it.first->second.emplace_back(&(added_it.first->second));
}
