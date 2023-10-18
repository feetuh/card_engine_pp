#include <algorithm>
#include <string>
#include <vector>

#include "card_engine_pp/constraint.hpp"

auto card_engine_pp::constraints::any_number::conforms(
    const std::vector<card_vec_it>& targets) -> bool
{
  (void)targets;
  return true;
}
