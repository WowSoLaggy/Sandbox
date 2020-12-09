#pragma once

#include "Actions.h"
#include "Fwd.h"


class ActionsImpl
{
public:
  ActionsImpl(Game& io_game);

  void runAction(Action i_action);

private:
  Game& d_game;

  void quitGame() const;

  bool d_isConsoleShown = false;
  void switchConsole();
  void showConsole();
  void hideConsole();

  void zoomIn() const;
  void zoomOut() const;
  void resetZoom() const;

  void moveCameraLeft() const;
  void moveCameraUp() const;
  void moveCameraRight() const;
  void moveCameraDown() const;
};
