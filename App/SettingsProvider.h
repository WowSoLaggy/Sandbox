#pragma once

#include "InternalSettings.h"
#include "UserSettings.h"


class SettingsProvider
{
public:
  static const UserSettings& getDefaultUserSettings();
  static const InternalSettings& getDefaultInternalSettings();
};
