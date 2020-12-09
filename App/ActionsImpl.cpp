#include "stdafx.h"
#include "ActionsImpl.h"

#include "Console.h"
#include "Game.h"
#include "GuiCreator.h"
#include "IApp.h"
#include "Log.h"
#include "SettingsProvider.h"


namespace
{
  const std::string ConsoleTag = "console";

  double getCameraSpeed()
  {
    return SettingsProvider::getDefaultUserSettings().cameraSpeed;
  }

  Sdk::Vector2I getClientSize()
  {
    const auto& settings = SettingsProvider::getDefaultUserSettings();
    return { settings.clientWidth, settings.clientHeight };
  }

} // anon NS


ActionsImpl::ActionsImpl(Game& io_game)
  : d_game(io_game)
{
}


void ActionsImpl::runAction(const Action i_action)
{
  switch (i_action)
  {
  case Action::QuitGame:
    quitGame();
    break;
  case Action::SwitchConsole:
    switchConsole();
    break;

  case Action::ZoomIn:
    zoomIn();
    break;
  case Action::ZoomOut:
    zoomOut();
    break;
  case Action::ResetZoom:
    resetZoom();
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


void ActionsImpl::switchConsole()
{
  d_isConsoleShown ? hideConsole() : showConsole();
}

void ActionsImpl::showConsole()
{
  auto consolePtr = std::make_shared<Console>();

  consolePtr->setTag(ConsoleTag);

  const auto size = getClientSize();
  consolePtr->setSize({ size.x, size.y / 2 });

  consolePtr->setTextureName("Black.png");
  consolePtr->setColor({ 1, 1, 1, 0.5f });

  d_game.getGuiController().getGuiCollection().addGui(consolePtr);

  consolePtr->connectTo(Log::getInstance());

  d_isConsoleShown = true;
}

void ActionsImpl::hideConsole()
{
  d_game.getGuiController().getGuiCollection().removeGuiByTag(ConsoleTag);
  d_isConsoleShown = false;
}


void ActionsImpl::zoomIn() const
{
  auto viewport = d_game.getViewportController().getViewport();

  const double maxZoom = SettingsProvider::getDefaultInternalSettings().maxZoom;
  viewport.scale = std::min(viewport.scale * 1.1, maxZoom);

  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::zoomOut() const
{
  auto viewport = d_game.getViewportController().getViewport();
  
  const double minZoom = SettingsProvider::getDefaultInternalSettings().minZoom;
  viewport.scale = std::max(viewport.scale * 0.9, minZoom);

  d_game.getViewportController().setViewport(viewport);
}

void ActionsImpl::resetZoom() const
{
  auto viewport = d_game.getViewportController().getViewport();
  viewport.scale = 1.0;
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
