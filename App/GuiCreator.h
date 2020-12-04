#pragma once

#include "Fwd.h"


class GuiCreator
{
public:
  GuiCreator(GameStateController& io_gameStateController, GuiCollection& io_guiCollection);

  void createLoadingScreen();
  void deleteLoadingScreen();

  void createMainMenu();
  void deleteMainMenu();

private:
  GameStateController& d_gameStateController;
  GuiCollection& d_guiCollection;
};
