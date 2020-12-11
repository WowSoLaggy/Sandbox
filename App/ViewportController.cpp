#include "stdafx.h"
#include "ViewportController.h"

#include "SettingsProvider.h"
#include "ViewportEvents.h"
#include "WorldEvents.h"


void ViewportController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const WorldCreatedEvent*>(&i_event))
    onWorldCreated();
}


void ViewportController::setViewport(Viewport i_viewport)
{
  d_viewport = std::move(i_viewport);
  onViewportChanged();
}

const Viewport& ViewportController::getViewport() const
{
  return d_viewport;
}


void ViewportController::createDefaultViewport()
{
  const auto userSettings = SettingsProvider::getDefaultUserSettings();
  d_viewport = Viewport{ { 0, 0 }, 1.0, userSettings.clientWidth, userSettings.clientHeight };
  onViewportChanged();
}


void ViewportController::onWorldCreated()
{
  createDefaultViewport();
}

void ViewportController::onViewportChanged()
{
  notify(ViewportChangedEvent(d_viewport));
}
