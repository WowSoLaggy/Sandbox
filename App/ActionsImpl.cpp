#include "stdafx.h"
#include "ActionsImpl.h"

#include "Game.h"
#include "IApp.h"
#include "SettingsProvider.h"

#include <LaggySdk/Contracts.h>


namespace
{
  double getCameraSpeed()
  {
    return SettingsProvider::getDefaultUserSettings().cameraSpeed;
  }

} // anon NS


ActionsImpl::ActionsImpl(Game& io_game)
  : d_game(io_game)
{
}


void ActionsImpl::runAction(const Action i_action) const
{
  switch (i_action)
  {
  case Action::QuitGame:
    quitGame();
    break;
  case Action::ZoomIn:
    zoomIn();
    break;
  case Action::ZoomOut:
    zoomOut();
    break;
  case Action::MoveCameraLeft:
    moveCameraLeft();
    break;
  case Action::MoveCameraUp:
    moveCameraUp();
    break;
  case Action::MoveCameraRight:
    moveCameraRight();
    break;
  case Action::MoveCameraDown:
    moveCameraDown();
    break;
  default:
    CONTRACT_ASSERT(false);
    break;
  }
}


void ActionsImpl::quitGame() const
{
  IApp::get().stop();
}


void ActionsImpl::zoomIn() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.scale *= 1.1;
  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::zoomOut() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.scale *= 0.9;
  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::moveCameraLeft() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.lookAt.x -= getCameraSpeed();
  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::moveCameraUp() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.lookAt.y -= getCameraSpeed();
  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::moveCameraRight() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.lookAt.x += getCameraSpeed();
  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::moveCameraDown() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.lookAt.y += getCameraSpeed();
  d_game.getViewportController().setViewport(viewport);
}
