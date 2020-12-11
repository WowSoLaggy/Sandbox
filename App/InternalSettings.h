#pragma once

#include <string>


struct InternalSettings
{
  std::string applicationName;
  std::string assetsFolder;
  std::string configFolder;
  std::string savesFolder;

  std::string defaultFontName;

  /// Number of pixels in one meter with scale = 1
  double scaleFactor = 0;

  double maxZoom = 0;
  double minZoom = 0;

  std::array<float, 4> clearColor;
};
