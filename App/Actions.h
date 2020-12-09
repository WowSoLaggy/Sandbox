#pragma once

#include <cstdint>


enum class Action : std::int32_t
{
  QuitGame = 0,

  SwitchConsole,

  ZoomIn,
  ZoomOut,
  ResetZoom,

  MoveCameraLeft,
  MoveCameraUp,
  MoveCameraRight,
  MoveCameraDown,
};
