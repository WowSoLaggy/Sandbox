#pragma once

#include <cstdint>


enum class ActionType : std::int32_t
{
  OnPress = 0,
  OnRelease,
  Continuous,
};
