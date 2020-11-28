#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class IGuiView
{
public:
  virtual ~IGuiView() = default;

  virtual const IGuiControl& getGuiControl() const = 0;

  virtual void update(double i_dt) = 0;
  virtual void render(Dx::IRenderer2d& i_renderer) const = 0;

  virtual void updateTextures() = 0;
};
