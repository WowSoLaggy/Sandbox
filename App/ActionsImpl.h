#pragma once

#include "Actions.h"
#include "Fwd.h"


class ActionsImpl
{
public:
  ActionsImpl(Game& io_game);

  void runAction(Action i_action) const;

private:
  Game& d_game;

  void quitGame() const;

  void zoomIn() const;
  void zoomOut() const;
  void moveCameraLeft() const;
  void moveCameraUp() const;
  void moveCameraRight() const;
  void moveCameraDown() const;
};
