#include "stdafx.h"
#include "GameStateController.h"

#include "Game.h"
#include "GameEvents.h"
#include "IApp.h"
#include "ResourceLoader.h"


GameStateController::GameStateController(Game& io_game)
  : d_game(io_game)
  , d_guiCreator(*this, io_game.getGuiController().getGuiCollection())
{
  d_isStarted = false;
  d_isReady = false;
}


void GameStateController::check()
{
  if (!d_isStarted)
    onGameStarted();
  else if (!d_isReady && ResourceLoader::isLoaded())
    onGameReady();
}


void GameStateController::onNewGame()
{
  d_guiCreator.deleteMainMenu();
  notify(NewGameEvent());
}

void GameStateController::onExit()
{
  IApp::get().stop();
}


void GameStateController::onGameStarted()
{
  d_isStarted = true;
  showLoadingScreen();
  ResourceLoader::loadAsync();
}

void GameStateController::onGameReady()
{
  showMainMenu();
  showCursor();
}


void GameStateController::showLoadingScreen()
{
  d_guiCreator.createLoadingScreen();
}

void GameStateController::showMainMenu()
{
  d_guiCreator.deleteLoadingScreen();
  d_guiCreator.createMainMenu();
}

void GameStateController::showCursor()
{
  d_game.getController().getCursor().show();
}
