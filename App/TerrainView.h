#pragma once

#include "Fwd.h"
#include "TerrainType.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/LaggyDxFwd.h>


class TerrainView
{
public:
  TerrainView(const Terrain& i_terrain);

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

private:
  const Terrain& d_terrain;
  std::unordered_map<TerrainType, const Dx::ITextureResource*> d_textures;

  void prepareTextures();
};
