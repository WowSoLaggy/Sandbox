#pragma once

#include "Fwd.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/LaggyDxFwd.h>


class CursorView
{
public:
  CursorView(const Cursor& i_cursor);

  const Cursor& getCursor() const;

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

  void updateTextures();
  void updateSize();

private:
  const Cursor& d_cursor;
  Dx::AnimatedSprite d_sprite;
};
