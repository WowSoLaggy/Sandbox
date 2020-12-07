#pragma once

#include <cstdint>


enum class Action : std::int32_t
{
  QuitGame = 0,
  ZoomIn,
  ZoomOut,
  ResetZoom,
  MoveCameraLeft,
  MoveCameraUp,
  MoveCameraRight,
  MoveCameraDown,
};
