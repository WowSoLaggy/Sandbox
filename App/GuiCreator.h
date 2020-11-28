#pragma once

#include "Fwd.h"


class GuiCreator
{
public:
  static void createLoadingScreen(GuiCollection& io_guiCollection);
  static void deleteLoadingScreen(GuiCollection& io_guiCollection);
  static void createMainMenu(GuiCollection& io_guiCollection);
};
