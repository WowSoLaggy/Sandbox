#include "stdafx.h"
#include "ViewportController.h"

#include "Object.h"
#include "ObjectEvents.h"
#include "SettingsProvider.h"
#include "ViewportEvents.h"
#include "World.h"
#include "WorldEvents.h"


namespace
{
  [[nodiscard]] bool isObjectVisible(const Sdk::Vector2D& i_position)
  {
    // TODO: ae
    return true;
  }

} // anon NS


void ViewportController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const ObjectAddedEvent*>(&i_event))
    onObjectAdded(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectRemovingEvent*>(&i_event))
    onObjectRemoving(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectPositionChangedEvent*>(&i_event))
    onObjectPositionChanged(event->getObject(), event->getPrevPosition());
  else if (const auto* event = dynamic_cast<const WorldCreatedEvent*>(&i_event))
    onWorldCreated(event->getWorld());
  else if (const auto* event = dynamic_cast<const WorldDisposingEvent*>(&i_event))
    onWorldDisposing(event->getWorld());
  else if (const auto* event = dynamic_cast<const ObjectTextureChangedEvent*>(&i_event))
    onObjectTextureChanged(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectSizeChangedEvent*>(&i_event))
    onObjectSizeChanged(event->getObject());
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


void ViewportController::onObjectAdded(const Object& i_object)
{
  if (isObjectVisible(i_object.getPosition()))
    onObjectEntersViewport(i_object);
}

void ViewportController::onObjectRemoving(const Object& i_object)
{
  onObjectLeavesViewport(i_object);
}

void ViewportController::onObjectPositionChanged(const Object& i_object, const Sdk::Vector2D& i_prevPosition)
{
  if (!isObjectVisible(i_prevPosition) && isObjectVisible(i_object.getPosition()))
    onObjectEntersViewport(i_object);
  else if (isObjectVisible(i_prevPosition) && !isObjectVisible(i_object.getPosition()))
    onObjectLeavesViewport(i_object);
}

void ViewportController::onObjectEntersViewport(const Object& i_object)
{
  notify(ObjectEntersViewport(i_object));
}

void ViewportController::onObjectLeavesViewport(const Object& i_object)
{
  notify(ObjectLeavesViewport(i_object));
}

void ViewportController::onObjectTextureChanged(const Object& i_object)
{
  if (isObjectVisible(i_object.getPosition()))
    notify(ObjectTextureChangedEvent(i_object));
}

void ViewportController::onObjectSizeChanged(const Object& i_object)
{
  if (isObjectVisible(i_object.getPosition()))
    notify(ObjectSizeChangedEvent(i_object));
}

void ViewportController::onWorldCreated(const World& i_world)
{
  createDefaultViewport();

  for (const auto& obj : i_world.getObjects())
    onObjectAdded(*obj);
}

void ViewportController::onWorldDisposing(const World& i_world)
{
  for (const auto& obj : i_world.getObjects())
    onObjectRemoving(*obj);
}

void ViewportController::onViewportChanged()
{
  notify(ViewportChangedEvent(d_viewport));
}
