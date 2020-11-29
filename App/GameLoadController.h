#pragma once

#include "Fwd.h"


class GameLoadController
{
public:
  GameLoadController(Game& io_game);

  void check();

private:
  Game& d_game;

  bool d_isStarted = false;
  bool d_isReady = false;

  void onGameStarted();
  void onGameReady();

  void showLoadingScreen();
  void showMainMenu();
  void showCursor();
};
