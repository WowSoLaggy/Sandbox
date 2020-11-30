#include "stdafx.h"
#include "ObjectView.h"

#include "IApp.h"
#include "Object.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


ObjectView::ObjectView(const Object& i_object)
  : d_object(i_object)
{
  updateTextures();
  updateSize();
}


const Object& ObjectView::getObject() const
{
  return d_object;
}


void ObjectView::update(const double i_dt)
{
  d_sprite.update(i_dt);
}

void ObjectView::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.setTranslation(d_sprite.getSize() / 2);
  i_renderer.renderSprite(d_sprite);
}


void ObjectView::updateTextures()
{
  auto& rc = IApp::get().getResourceController();
  d_sprite.setTexture(rc.getTextureResource(d_object.getTextureName()));
}

void ObjectView::updateSize()
{
  d_sprite.setSize({ 64, 64 });
}
