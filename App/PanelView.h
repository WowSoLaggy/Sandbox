#pragma once

#include "Fwd.h"
#include "IGuiView.h"

#include <LaggyDx/AnimatedSprite.h>


class PanelView : public IGuiView
{
public:
  PanelView(const Panel& i_panel);

  virtual const IGuiControl& getGuiControl() const override;

  virtual void update(double i_dt) override;
  virtual void render(Dx::IRenderer2d& i_renderer) const override;

  virtual void updateTextures() override;
  virtual void updateSize() override;
  virtual void updateColor() override;

private:
  const Panel& d_panel;
  Dx::AnimatedSprite d_sprite;
};
