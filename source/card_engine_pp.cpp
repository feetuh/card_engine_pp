#include <string>

#include "card_engine_pp/card_engine_pp.hpp"

#include <fmt/core.h>

exported_class::exported_class()
    : m_name {fmt::format("{}", "card_engine_pp")}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
