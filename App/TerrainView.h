#pragma once

#include "Fwd.h"
#include "TerrainType.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Rect.h>


class TerrainView
{
public:
  TerrainView(const Terrain& i_terrain);

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

  /// \param i_area - shall be defined in world coords
  void updateDrawArea(const Sdk::RectD& i_area);

private:
  const Terrain& d_terrain;
  std::unordered_map<TerrainType, const Dx::ITextureResource*> d_textures;
  
  /// Defined in tiles, not world coords!
  int d_drawLeft = 0;
  int d_drawRight = -1;
  int d_drawTop = 0;
  int d_drawBottom = -1;

  void prepareTextures();
};
