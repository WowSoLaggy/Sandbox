#include "stdafx.h"
#include "RandomTerrainTypeGenerator.h"

#include <LaggySdk/UniformIntGenerator.h>


RandomTerrainTypeGenerator::RandomTerrainTypeGenerator(const std::unordered_set<TerrainType> i_allowedTypes)
  : d_allowedTypes(std::move(i_allowedTypes))
{
  CONTRACT_EXPECT(!d_allowedTypes.empty());
}


TerrainType RandomTerrainTypeGenerator::getNextType() const
{
  const int count = (int)d_allowedTypes.size();
  Sdk::UniformIntGenerator<int> generator(0, count - 1);

  return *std::next(d_allowedTypes.begin(), generator.getNextValue());
}
