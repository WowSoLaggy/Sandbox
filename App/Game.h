#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class Game
{
public:
  Game(IApp& i_app, Dx::IResourceController& i_resourceController);

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);
  void handleMouse(const Dx::MouseState& i_mouseState);

private:
  IApp& d_app;
  Dx::IResourceController& d_resourceController;

  bool loadResources();
};
