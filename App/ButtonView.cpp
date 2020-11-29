#include "stdafx.h"
#include "ButtonView.h"

#include "IApp.h"
#include "Button.h"
#include "SettingsProvider.h"

#include <LaggyDx/IFontResource.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>
#include <LaggySdk/Contracts.h>


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
  i_renderer.setTranslation(-d_button.getPosition());
  i_renderer.renderSprite(d_sprite);

  const auto text = d_button.getText();
  if (!text.empty())
  {
    CONTRACT_ASSERT(d_font);
    i_renderer.renderText(text, *d_font, d_textOffset);
  }
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

void ButtonView::updateText()
{
  const auto text = d_button.getText();

  if (text.empty())
    resetTextFont();
  else
  {
    updateTextFont();
    CONTRACT_ASSERT(d_font);

    const auto textSize = d_font->getStringRect(text).size();
    const auto buttonSize = d_sprite.getSize();

    d_textOffset = (buttonSize - textSize) / 2;
  }
}


void ButtonView::updateTextFont()
{
  if (!d_font)
  {
    const auto& fontName = SettingsProvider::getDefaultInternalSettings().defaultFontName;
    auto& rc = IApp::get().getResourceController();
    d_font = &rc.getFontResource(fontName);
  }
}

void ButtonView::resetTextFont()
{
  d_font = nullptr;
}
