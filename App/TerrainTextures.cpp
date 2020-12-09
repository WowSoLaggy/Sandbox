#include "stdafx.h"
#include "TerrainTextures.h"


namespace
{
  const std::unordered_map<TerrainType, std::string> TexturesMap{
    { TerrainType::Dirt1, "Dirt1.png" },
    { TerrainType::Dirt2, "Dirt2.png" },
    { TerrainType::Grass1, "Grass1.png" },
    { TerrainType::Grass2, "Grass2.png" },
  };

  bool exists(const TerrainType i_terrainType)
  {
    const auto it = TexturesMap.find(i_terrainType);
    return it != TexturesMap.cend();
  }

} // anon NS


const std::string& getTerrainTexture(const TerrainType i_terrainType)
{
  CONTRACT_EXPECT(exists(i_terrainType));
  return TexturesMap.at(i_terrainType);
}

const std::unordered_map<TerrainType, std::string>& getAllTerrainTextures()
{
  return TexturesMap;
}
