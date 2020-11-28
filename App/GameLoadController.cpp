#include "stdafx.h"
#include "GameLoadController.h"

#include "Game.h"
#include "GuiCreator.h"
#include "ResourceLoader.h"


GameLoadController::GameLoadController(Game& io_game)
  : d_game(io_game)
{
  d_isStarted = false;
  d_isReady = false;
}


void GameLoadController::check()
{
  if (!d_isStarted)
    onGameStarted();
  else if (!d_isReady && ResourceLoader::isLoaded())
    onGameReady();
}


void GameLoadController::onGameStarted()
{
  d_isStarted = true;
  createLoadingScreen();
  ResourceLoader::loadAsync();
}

void GameLoadController::onGameReady()
{
  deleteLoadingScreen();
  createMainMenu();
}


void GameLoadController::createLoadingScreen()
{
  GuiCreator::createLoadingScreen(d_game.getGuiController().getGuiCollection());
}

void GameLoadController::deleteLoadingScreen()
{
}

void GameLoadController::createMainMenu()
{
}