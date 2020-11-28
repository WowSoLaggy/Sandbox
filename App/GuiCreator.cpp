#include "stdafx.h"
#include "GuiCreator.h"

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
    panel.setPosition(getClientCenter());
    panel.setPositionOrigin(PositionOrigin::Center);
  }
}
