#include "stdafx.h"
#include "CursorView.h"

#include "IApp.h"
#include "Cursor.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


CursorView::CursorView(const Cursor& i_cursor)
  : d_cursor(i_cursor)
{
  updateTextures();
  updateSize();
}


const Cursor& CursorView::getCursor() const
{
  return d_cursor;
}


void CursorView::update(const double i_dt)
{
  d_sprite.update(i_dt);
}

void CursorView::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.setTranslation(-d_cursor.getPosition());
  i_renderer.renderSprite(d_sprite);
}


void CursorView::updateTextures()
{
  auto& rc = IApp::get().getResourceController();
  d_sprite.setTexture(rc.getTextureResource(d_cursor.getTextureName()));
}

void CursorView::updateSize()
{
  d_sprite.setSize(d_cursor.getSize());
}
