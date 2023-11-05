#pragma once

#include <algorithm>

namespace card_engine_pp
{

template<size_t N>
struct string_literal
{
  constexpr explicit string_literal(const char (&str)[N])
  {
    std::copy_n(str, N, value);
  }

  char value[N];
};
}  // namespace card_engine_pp
