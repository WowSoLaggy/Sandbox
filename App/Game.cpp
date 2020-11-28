#include "stdafx.h"
#include "Game.h"

#include "GameEvents.h"
#include "ResourceLoader.h"


Game::Game()
{
  d_gameStateController.connectTo(*this);
  d_viewportController.connectTo(d_worldController);
  d_viewController.connectTo(d_viewportController);
  d_viewController.connectTo(d_guiController);

  onStarted();
  ResourceLoader::loadAsync();
}


void Game::update(const double i_dt)
{
  if (!d_isReady && ResourceLoader::isLoaded())
    onReady();

  d_worldController.updateWorld(i_dt);
  d_viewController.update(i_dt);
}

void Game::render(Dx::IRenderer2d& i_renderer) const
{
  d_viewController.render(i_renderer);
}


void Game::onStarted()
{
  d_isReady = false;
  notify(GameStartedEvent());
}

void Game::onReady()
{
  d_isReady = true;
  notify(GameReadyEvent());
}
