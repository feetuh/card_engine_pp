#pragma once

#include <vector>

#include "card_engine_pp/board.hpp"

namespace card_engine_pp
{

using card_vec_it = std::vector<card>::iterator;

auto move_cards(board& state,
                const std::string& from_site,
                const std::vector<card_vec_it>& cards,
                const std::string& to_site) -> void;

}  // namespace card_engine_pp
