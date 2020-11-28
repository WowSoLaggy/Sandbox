#include "stdafx.h"
#include "Panel.h"

#include "GuiEvents.h"


void Panel::setTextureName(std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
  notify(GuiControlTextureChangedEvent(*this));
}

const std::string& Panel::getTextureName() const
{
  return d_textureName;
}


void Panel::setPosition(Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& Panel::getPosition() const
{
  return d_position;
}
