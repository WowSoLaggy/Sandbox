#pragma once

#include "TerrainType.h"


class Terrain
{
public:
  Terrain(int i_xSize, int i_ySize);

  int getXSize() const;
  int getYSize() const;

  void setTerrainType(int i_x, int i_y, TerrainType i_type);
  TerrainType getTerrainType(int i_x, int i_y) const;

private:
  const int d_xSize = 0;
  const int d_ySize = 0;

  std::vector<TerrainType> d_tiles;

  int getIndex(int i_x, int i_y) const;
  void assertCoords(int i_x, int i_y) const;
};
