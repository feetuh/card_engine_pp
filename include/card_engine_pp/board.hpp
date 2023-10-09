#pragma once

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
  std::vector<site> m_sites;
};

}  // namespace card_engine_pp
