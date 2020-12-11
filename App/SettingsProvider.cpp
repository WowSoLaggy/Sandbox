#include "stdafx.h"
#include "SettingsProvider.h"


namespace
{
  UserSettings createDefaultUserSettings()
  {
    UserSettings settings;

    settings.clientWidth = 1600;
    settings.clientHeight = 900;
    settings.cameraSpeed = 0.2;

    return settings;
  }

  InternalSettings createDefaultInternalSettings()
  {
    InternalSettings settings;

    settings.applicationName = "Sandbox";
    settings.assetsFolder = "Data/Assets";
    settings.configFolder = "Data/Configs";
    settings.savesFolder = "Saves";
    settings.defaultFontName = "MyFont.spritefont";

    settings.scaleFactor = 64;

    settings.maxZoom = 3.0;
    settings.minZoom = 0.75;

    settings.clearColor = { 0, 0, 0, 0 };

    return settings;
  }

} // anonymous NS


const UserSettings& SettingsProvider::getDefaultUserSettings()
{
  static const auto userSettings = createDefaultUserSettings();
  return userSettings;
}

const InternalSettings& SettingsProvider::getDefaultInternalSettings()
{
  static const auto internalSettings = createDefaultInternalSettings();
  return internalSettings;
}
