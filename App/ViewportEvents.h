#pragma once

#include "ObjectEvents.h"

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
