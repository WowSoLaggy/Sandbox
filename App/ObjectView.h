#pragma once

#include "Fwd.h"

#include <LaggyDx/AnimatedSprite.h>


class ObjectView
{
public:
  ObjectView(const Object& i_object);

  const Object& getObject() const;

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

  void updateTextures();
  void updateSize();

private:
  const Object& d_object;
  Dx::AnimatedSprite d_sprite;
};