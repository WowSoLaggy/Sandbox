#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class ObjectEvent : public Sdk::IEvent
{
public:
  ObjectEvent(const Object& i_object)
    : d_object(i_object)
  {
  }

  const Object& getObject() const { return d_object; }

private:
  const Object& d_object;
};

class ObjectAddedEvent : public ObjectEvent
{
public:
  ObjectAddedEvent(const Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};

class ObjectRemovingEvent : public ObjectEvent
{
public:
  ObjectRemovingEvent(const Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};
