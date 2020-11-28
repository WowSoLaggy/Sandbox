#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class WorldEvent : public Sdk::IEvent
{
public:
  WorldEvent(const World& i_world)
    : d_world(i_world)
  {
  }

  const World& getWorld() const { return d_world; }

private:
  const World& d_world;
};


class WorldCreatedEvent : public WorldEvent
{
public:
  WorldCreatedEvent(const World& i_world)
    : WorldEvent(i_world)
  {
  }
};

class WorldDisposingEvent : public WorldEvent
{
public:
  WorldDisposingEvent(const World& i_world)
    : WorldEvent(i_world)
  {
  }
};
