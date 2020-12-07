#pragma once

#include "TerrainType.h"


class RandomTerrainTypeGenerator
{
public:
  RandomTerrainTypeGenerator(std::unordered_set<TerrainType> i_allowedTypes);

  TerrainType getNextType() const;

private:
  std::unordered_set<TerrainType> d_allowedTypes;
};
