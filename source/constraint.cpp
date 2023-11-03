#include <algorithm>
#include <string>
#include <vector>

#include "card_engine_pp/constraint.hpp"

auto card_engine_pp::constraints::any_number::conforms(
    const std::vector<const card*>& targets) -> bool
{
  (void)targets;
  return true;
}

auto card_engine_pp::constraints::any_card::conforms(
    const std::vector<const card*>& targets) -> bool
{
  (void)targets;
  return true;
}
