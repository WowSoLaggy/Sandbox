#pragma once

#include "Fwd.h"
#include "GuiCreator.h"

#include <LaggySdk/EventHandler.h>


class GameStateController : public Sdk::EventHandler
{
public:
  GameStateController(Game& io_game);

  void check();

  void onNewGame();
  void onExit();

private:
  Game& d_game;
  GuiCreator d_guiCreator;

  bool d_isStarted = false;
  bool d_isReady = false;

  void onGameStarted();
  void onGameReady();

  void showLoadingScreen();
  void showMainMenu();
  void showCursor();
};
