#include "stdafx.h"
#include "GuiCreator.h"

#include "Button.h"
#include "GameStateController.h"
#include "GuiCollection.h"
#include "Panel.h"
#include "SettingsProvider.h"


namespace
{
  const std::string TagLoading = "loading";
  const std::string TagMainMenu = "main_menu";

  Sdk::Vector2I getClientSize()
  {
    const auto& settings = SettingsProvider::getDefaultExternalSettings();
    return { settings.clientWidth, settings.clientHeight };
  }

  Sdk::Vector2I getClientCenter()
  {
    const auto& settings = SettingsProvider::getDefaultExternalSettings();
    return { settings.clientWidth / 2, settings.clientHeight / 2 };
  }

} // anon NS


GuiCreator::GuiCreator(GameStateController& io_gameStateController, GuiCollection& io_guiCollection)
  : d_gameStateController(io_gameStateController)
  , d_guiCollection(io_guiCollection)
{
}


void GuiCreator::createLoadingScreen()
{
  auto createPanel = [&]() -> Panel&
  {
    auto panelPtr = std::make_shared<Panel>();
    panelPtr->setTag(TagLoading);
    d_guiCollection.addGui(panelPtr);
    return *panelPtr;
  };

  {
    // Background
    auto& panel = createPanel();
    panel.setTextureName("Black.png");
    panel.setSize(getClientSize());
  }

  {
    // "Loading" label
    auto& panel = createPanel();
    panel.setTextureName("Loading.png");
    panel.setSize({ 256, 64 });
    panel.setPosition(getClientCenter() - panel.getSize() / 2);
  }
}

void GuiCreator::deleteLoadingScreen()
{
  d_guiCollection.removeGuiByTag(TagLoading);
}

void GuiCreator::createMainMenu()
{
  auto createPanel = [&]() -> Panel&
  {
    auto panelPtr = std::make_shared<Panel>();
    panelPtr->setTag(TagMainMenu);
    d_guiCollection.addGui(panelPtr);
    return *panelPtr;
  };

  auto createButton = [&]() -> Button&
  {
    auto buttonPtr = std::make_shared<Button>();
    buttonPtr->setTag(TagMainMenu);
    d_guiCollection.addGui(buttonPtr);
    return *buttonPtr;
  };

  auto createMainMenuButton = [&]() -> Button&
  {
    auto& btn = createButton();
    btn.setTextureName(Button::State::Normal, "Button.png");
    btn.setTextureName(Button::State::Light, "ButtonLight.png");
    btn.setTextureName(Button::State::Pressed, "ButtonPressed.png");
    btn.setSize({ 256, 32 });
    return btn;
  };


  {
    // Background
    auto& panel = createPanel();
    panel.setTextureName("Black.png");
    panel.setSize(getClientSize());
  }

  {
    // New Game
    auto& btn = createMainMenuButton();
    btn.setPosition(getClientCenter() - btn.getSize() / 2);
    btn.setText("New Game");
    btn.setHandler(std::bind(&GameStateController::onNewGame, &d_gameStateController));
  }

  {
    // New Game
    auto& btn = createMainMenuButton();
    btn.setPosition(getClientCenter() - btn.getSize() / 2 + Sdk::Vector2I{ 0, 48 });
    btn.setText("Exit");
    btn.setHandler(std::bind(&GameStateController::onExit, &d_gameStateController));
  }
}

void GuiCreator::deleteMainMenu()
{
  d_guiCollection.removeGuiByTag(TagMainMenu);
}
