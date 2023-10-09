#pragma once

#include <map>
#include <vector>

#include "card_engine_pp/card.hpp"

namespace card_engine_pp
{

struct site
{
  std::vector<card> m_cards;
};

struct board
{
  auto add_site(site target,
                std::string site_name,
                std::optional<std::string> group_name = std::nullopt) -> void;

  std::map<std::string, site> m_sites;
  std::map<std::string, std::vector<site*>> m_group_to_sites;
};

}  // namespace card_engine_pp
