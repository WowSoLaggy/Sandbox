#include "stdafx.h"
#include "Game.h"


Game::Game()
  : d_gameLoadController(*this)
{
  d_viewportController.connectTo(d_worldController);
  d_viewController.connectTo(d_viewportController);
  d_viewController.connectTo(d_guiController);
  d_viewController.connectTo(d_controller);
}


void Game::update(const double i_dt)
{
  d_gameLoadController.check();

  d_worldController.updateWorld(i_dt);
  d_viewController.update(i_dt);
}

void Game::render(Dx::IRenderer2d& i_renderer) const
{
  d_viewController.render(i_renderer);
}


void Game::handleKeyboard(const Dx::KeyboardState& i_keyboardState)
{
  d_controller.handleKeyboard(i_keyboardState);
}

void Game::handleMouse(const Dx::MouseState& i_mouseState)
{
  d_controller.handleMouse(i_mouseState);
}


GuiController& Game::getGuiController()
{
  return d_guiController;
}

Controller& Game::getController()
{
  return d_controller;
}
