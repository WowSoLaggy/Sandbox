#include "stdafx.h"
#include "ButtonView.h"

#include "IApp.h"
#include "Button.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


ButtonView::ButtonView(const Button& i_button)
  : d_button(i_button)
{
  updateTextures();
}


const IGuiControl& ButtonView::getGuiControl() const
{
  return d_button;
}


void ButtonView::update(const double i_dt)
{
  d_sprite.update(i_dt);
}

void ButtonView::render(Dx::IRenderer2d& i_renderer) const
{
  const auto translation = d_button.getPositionOrigin() == PositionOrigin::Center ?
    -d_button.getPosition() + d_sprite.getSize() / 2 :
    -d_button.getPosition();

  i_renderer.setTranslation(translation);
  i_renderer.renderSprite(d_sprite);
}


void ButtonView::updateTextures()
{
  const auto state = d_button.getState();

  const auto textureName = d_button.getTextureName(state);
  if (textureName.empty())
    return;

  auto& rc = IApp::get().getResourceController();
  d_sprite.setTexture(rc.getTextureResource(textureName));
}

void ButtonView::updateSize()
{
  d_sprite.setSize(d_button.getSize());
}
