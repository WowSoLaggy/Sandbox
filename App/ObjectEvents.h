#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>
#include <LaggySdk/Vector.h>


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

class ObjectPositionChangedEvent : public ObjectEvent
{
public:
  ObjectPositionChangedEvent(const Object& i_object, Sdk::Vector2D i_prevPosition)
    : ObjectEvent(i_object)
    , d_prevPosition(std::move(i_prevPosition))
  {
  }

  const Sdk::Vector2D& getPrevPosition() const { return d_prevPosition; }

private:
  Sdk::Vector2D d_prevPosition;
};

class ObjectTextureChangedEvent : public ObjectEvent
{
public:
  ObjectTextureChangedEvent(const Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};
