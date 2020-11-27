#pragma once

#include "Fwd.h"
#include "GameStateController.h"
#include "ViewController.h"
#include "ViewportController.h"
#include "WorldController.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class Game : public Sdk::EventHandler
{
public:
  Game();

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);
  void handleMouse(const Dx::MouseState& i_mouseState);

private:
  GameStateController d_gameStateController;
  ViewController d_viewController;
  WorldController d_worldController;
  ViewportController d_viewportController;

  bool d_isReady = false;
  void onStarted();
  void onReady();
};
