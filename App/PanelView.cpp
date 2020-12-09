#include "stdafx.h"
#include "PanelView.h"

#include "IApp.h"
#include "Panel.h"
#include "SettingsProvider.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


PanelView::PanelView(const Panel& i_panel)
  : d_panel(i_panel)
{
  updateTextures();
  updateSize();
  updateColor();
  updateText();
}


const IGuiControl& PanelView::getGuiControl() const
{
  return d_panel;
}


void PanelView::update(const double i_dt)
{
  d_sprite.update(i_dt);
}

void PanelView::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.setTranslation(d_panel.getPosition());
  i_renderer.renderSprite(d_sprite);

  const auto text = d_panel.getText();
  if (!text.empty())
  {
    CONTRACT_ASSERT(d_font);
    i_renderer.renderText(text, *d_font, {});
  }
}


void PanelView::updateTextures()
{
  const auto textureName = d_panel.getTextureName();
  if (textureName.empty())
    return;

  auto& rc = IApp::get().getResourceController();
  d_sprite.setTexture(rc.getTextureResource(textureName));
}

void PanelView::updateSize()
{
  d_sprite.setSize(d_panel.getSize());
}

void PanelView::updateColor()
{
  d_sprite.setColor(d_panel.getColor());
}

void PanelView::updateText()
{
  const auto text = d_panel.getText();

  if (text.empty())
    resetTextFont();
  else
  {
    updateTextFont();
    CONTRACT_ASSERT(d_font);
  }
}


void PanelView::updateTextFont()
{
  if (!d_font)
  {
    const auto& fontName = SettingsProvider::getDefaultInternalSettings().defaultFontName;
    auto& rc = IApp::get().getResourceController();
    d_font = &rc.getFontResource(fontName);
  }
}

void PanelView::resetTextFont()
{
  d_font = nullptr;
}
