#pragma once

#include "ObjectEvents.h"
#include "Viewport.h"

#include <LaggySdk/IEvent.h>


class ObjectEntersViewport : public ObjectEvent
{
public:
  ObjectEntersViewport(const Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};

class ObjectLeavesViewport : public ObjectEvent
{
public:
  ObjectLeavesViewport(const Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};


class ViewportChangedEvent : public Sdk::IEvent
{
public:
  ViewportChangedEvent(Viewport i_viewport)
    : d_viewport(std::move(i_viewport))
  {
  }

  const Viewport& getViewport() const { return d_viewport; }

private:
  Viewport d_viewport;
};
