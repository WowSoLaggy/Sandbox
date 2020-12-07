#include "stdafx.h"
#include "App.h"

#include "SettingsProvider.h"

#include <LaggySdk/Cursor.h>
#include <LaggySdk/HandleMessages.h>
#include <LaggySdk/Locker.h>
#include <LaggySdk/Random.h>


App::App()
{
  const auto hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  CONTRACT_ASSERT(hres == S_OK);

  Sdk::randomize();

  const auto& userSettings = SettingsProvider::getDefaultUserSettings();
  const auto& internalSettings = SettingsProvider::getDefaultInternalSettings();
  const Sdk::Vector2I resolution = { userSettings.clientWidth, userSettings.clientHeight };

  d_window = std::make_unique<Sdk::Window>(resolution, internalSettings.applicationName);

  d_renderDevice = Dx::IRenderDevice::create(d_window->getHWnd(), resolution);
  CONTRACT_ENSURE(d_renderDevice);

  d_resourceController = Dx::IResourceController::create(*d_renderDevice, internalSettings.assetsFolder);
  CONTRACT_ENSURE(d_resourceController);

  d_renderer2d = Dx::IRenderer2d::create(*d_renderDevice, resolution);
  CONTRACT_ENSURE(d_renderer2d);

  d_inputDevice = Dx::IInputDevice::create(d_window->getHWnd());
  CONTRACT_ENSURE(d_inputDevice);

  d_game = std::make_unique<Game>();

  Sdk::setCursorToCenter();
  d_window->show();
}

App::~App()
{
  CoUninitialize();
}


void App::run()
{
  d_continueLoop = true;
  d_timer.start();

  while (getContinueLoop())
    mainloop();
}

void App::stop()
{
  d_continueLoop = false;
}


Dx::IResourceController& App::getResourceController()
{
  CONTRACT_ASSERT(d_resourceController);
  return *d_resourceController;
}


bool App::getContinueLoop()
{
  CONTRACT_EXPECT(d_inputDevice);
  if (!Sdk::handleMessages(std::bind(&Dx::IInputDevice::processMessage, std::ref(*d_inputDevice), std::placeholders::_1)))
    return false;

  return d_continueLoop;
}

void App::mainloop()
{
  double dt = d_timer.restart();

  d_game->handleKeyboard(d_inputDevice->checkKeyboard());
  d_game->handleMouse(d_inputDevice->checkMouse());

  d_game->update(dt);

  {
    const Sdk::Locker scopeLocker(*d_renderDevice);

    d_renderDevice->beginScene();

    d_game->render(*d_renderer2d);

    d_renderDevice->endScene();
  }

  std::this_thread::sleep_for(1ms);
}
