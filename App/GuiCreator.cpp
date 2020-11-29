#include "stdafx.h"
#include "GuiCreator.h"

#include "Button.h"
#include "GuiCollection.h"
#include "Panel.h"
#include "SettingsProvider.h"


namespace
{
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


void GuiCreator::createLoadingScreen(GuiCollection& io_guiCollection)
{
  auto createPanel = [&]() -> Panel&
  {
    auto panelPtr = std::make_shared<Panel>();
    panelPtr->setTag("loading");
    io_guiCollection.addGui(panelPtr);
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

void GuiCreator::deleteLoadingScreen(GuiCollection& io_guiCollection)
{
  io_guiCollection.removeGuiByTag("loading");
}

void GuiCreator::createMainMenu(GuiCollection& io_guiCollection)
{
  auto createPanel = [&]() -> Panel&
  {
    auto panelPtr = std::make_shared<Panel>();
    panelPtr->setTag("main");
    io_guiCollection.addGui(panelPtr);
    return *panelPtr;
  };

  auto createButton = [&]() -> Button&
  {
    auto buttonPtr = std::make_shared<Button>();
    buttonPtr->setTag("main");
    io_guiCollection.addGui(buttonPtr);
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
  }
}
