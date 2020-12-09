#include "stdafx.h"
#include "TerrainView.h"

#include "IApp.h"
#include "SettingsProvider.h"
#include "Terrain.h"
#include "TerrainTextures.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/ResourceController.h>


TerrainView::TerrainView(const Terrain& i_terrain)
  : d_terrain(i_terrain)
{
  prepareTextures();
}


void TerrainView::update(double i_dt)
{
}

void TerrainView::render(Dx::IRenderer2d& i_renderer) const
{
  Dx::AnimatedSprite sprite;
  auto& rc = IApp::get().getResourceController();

  const int scaleFactor = (int)SettingsProvider::getDefaultInternalSettings().scaleFactor;
  sprite.setSize({ scaleFactor, scaleFactor });

  for (int y = 0; y < d_terrain.getYSize(); ++y)
  {
    for (int x = 0; x < d_terrain.getXSize(); ++x)
    {
      sprite.setPosition({ x * scaleFactor, y * scaleFactor });
      
      const auto terrainType = d_terrain.getTerrainType(x, y);
      const auto* texture = d_textures.at(terrainType);
      CONTRACT_ASSERT(texture);
      sprite.setTexture(*texture);

      i_renderer.renderSprite(sprite);
    }
  }
}


void TerrainView::prepareTextures()
{
  if (!d_textures.empty())
    d_textures.clear();

  auto& rc = IApp::get().getResourceController();
  for (const auto&[type, name] : getAllTerrainTextures())
  {
    const auto& texture = rc.getTextureResource(name);
    d_textures[type] = &texture;
  }
}
