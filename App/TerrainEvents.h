#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class TerrainAddedEvent : public Sdk::IEvent
{
public:
  TerrainAddedEvent(const Terrain& i_terrain)
    : d_terrain(i_terrain)
  {
  }

  const Terrain& getTerrain() const { return d_terrain; }

private:
  const Terrain& d_terrain;
};

class TerrainResetEvent : public Sdk::IEvent
{
};
