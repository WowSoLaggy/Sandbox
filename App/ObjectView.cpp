#include "stdafx.h"
#include "ObjectView.h"

#include "IApp.h"
#include "Object.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


ObjectView::ObjectView(const Object& i_object)
  : d_object(i_object)
{
  auto& rc = IApp::get().getResourceController();
  d_sprite.setTexture(rc.getTextureResource(i_object.getTextureName()));
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
  i_renderer.renderSprite(d_sprite);
}
