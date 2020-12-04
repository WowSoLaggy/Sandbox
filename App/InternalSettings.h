#pragma once

#include <string>


struct InternalSettings
{
  std::string applicationName;
  std::string assetsFolder;
  std::string configFolder;
  std::string savesFolder;

  std::string defaultFontName;

  double scaleFactor = 64;
};
