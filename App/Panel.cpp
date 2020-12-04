#include "stdafx.h"
#include "Panel.h"

#include "GuiEvents.h"


void Panel::setTextureName(const std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
  notify(GuiControlTextureChangedEvent(*this));
}

const std::string& Panel::getTextureName() const
{
  return d_textureName;
}


void Panel::setPosition(const Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& Panel::getPosition() const
{
  return d_position;
}


void Panel::setSize(const Sdk::Vector2I i_size)
{
  d_size = std::move(i_size);
  notify(GuiControlSizeChangedEvent(*this));
}

const Sdk::Vector2I& Panel::getSize() const
{
  return d_size;
}


void Panel::setColor(Sdk::Vector4F i_color)
{
  d_color = std::move(i_color);
  notify(GuiControlColorChangedEvent(*this));
}

const Sdk::Vector4F& Panel::getColor() const
{
  return d_color;
}

