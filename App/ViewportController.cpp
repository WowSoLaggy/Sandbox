#include "stdafx.h"
#include "ViewportController.h"

#include "ObjectEvents.h"
#include "ViewportEvents.h"


namespace
{
  [[nodiscard]] bool isObjectVisible(const Object& i_object)
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
}


void ViewportController::onObjectAdded(const Object& i_object)
{
  if (isObjectVisible(i_object))
    notify(ObjectEntersViewport(i_object));
}

void ViewportController::onObjectRemoving(const Object& i_object)
{
  notify(ObjectLeavesViewport(i_object));
}
