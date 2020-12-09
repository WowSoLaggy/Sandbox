#pragma once

#include "TerrainType.h"


const std::string& getTerrainTexture(TerrainType i_terrainType);
const std::unordered_map<TerrainType, std::string>& getAllTerrainTextures();
