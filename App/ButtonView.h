#pragma once

#include "Fwd.h"
#include "IGuiView.h"

#include <LaggyDx/AnimatedSprite.h>


class ButtonView : public IGuiView
{
public:
  ButtonView(const Button& i_button);

  virtual const IGuiControl& getGuiControl() const override;

  virtual void update(double i_dt) override;
  virtual void render(Dx::IRenderer2d& i_renderer) const override;

  virtual void updateTextures() override;
  virtual void updateSize() override;

private:
  const Button& d_button;
  Dx::AnimatedSprite d_sprite;
};
