#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain(int i_xSize, int i_ySize)
  : d_xSize(i_xSize)
  , d_ySize(i_ySize)
{
  d_tiles.resize(d_xSize * d_ySize, TerrainType::Dirt1);
}


int Terrain::getXSize() const
{
  return d_xSize;
}

int Terrain::getYSize() const
{
  return d_ySize;
}


void Terrain::setTerrainType(const int i_x, const int i_y, const TerrainType i_type)
{
  assertCoords(i_x, i_y);

  d_tiles[getIndex(i_x, i_y)] = i_type;
}

TerrainType Terrain::getTerrainType(const int i_x, const int i_y) const
{
  assertCoords(i_x, i_y);
  return d_tiles.at(getIndex(i_x, i_y));
}


int Terrain::getIndex(const int i_x, const int i_y) const
{
  return i_x + i_y * d_xSize;
}

void Terrain::assertCoords(const int i_x, const int i_y) const
{
  CONTRACT_EXPECT(i_x >= 0);
  CONTRACT_EXPECT(i_y >= 0);
  CONTRACT_EXPECT(i_x < d_xSize);
  CONTRACT_EXPECT(i_y < d_ySize);
}
