#include "stdafx.h"
#include "TerrainCreator.h"

#include "RandomTerrainTypeGenerator.h"


Terrain TerrainCreator::generateDefault()
{
  constexpr int SizeX = 50;
  constexpr int SizeY = SizeX;

  Terrain terrain(SizeX, SizeY);

  RandomTerrainTypeGenerator rnd({ TerrainType::Dirt1, TerrainType::Dirt2 });
  for (int y = 0; y < SizeY; ++y)
  {
    for (int x = 0; x < SizeX; ++x)
      terrain.setTerrainType(x, y, rnd.getNextType());
  }

  return terrain;
}
