#pragma once

#include <LaggySdk/Vector.h>


struct Viewport
{
  Sdk::Vector2D lookAt;
  double scale = 1.0;
  int width = 0;
  int height = 0;
};
