#include "stdafx.h"
#include "Game.h"

#include <LaggyDx/IResourceController.h>


Game::Game(IApp& i_app, Dx::IResourceController& i_resourceController)
  : d_app(i_app)
  , d_resourceController(i_resourceController)
{
}


void Game::update(double i_dt)
{
}

void Game::render(Dx::IRenderer2d& i_renderer) const
{
}


bool Game::loadResources()
{
  try
  {
    d_resourceController.loadResources();
    std::this_thread::sleep_for(100ms);
  }
  catch (...)
  {
    return false;
  }

  return true;
}
