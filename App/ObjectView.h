#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/AnimatedSprite.h>


class ObjectView
{
public:
  ObjectView(const Object& i_object);

  const Object& getObject() const;

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

private:
  const Object& d_object;
  Dx::AnimatedSprite d_sprite;
};