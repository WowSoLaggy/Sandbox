#include "stdafx.h"
#include "Button.h"

#include "GuiEvents.h"


void Button::setTextureName(const State i_state, const std::string i_textureName)
{
  d_textureNames[i_state] = std::move(i_textureName);
  notify(GuiControlTextureChangedEvent(*this));
}

const std::string& Button::getTextureName(const State i_state) const
{
  return d_textureNames.at(i_state);
}


void Button::setPosition(const Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& Button::getPosition() const
{
  return d_position;
}


void Button::setSize(const Sdk::Vector2I i_size)
{
  d_size = std::move(i_size);
  notify(GuiControlSizeChangedEvent(*this));
}

const Sdk::Vector2I& Button::getSize() const
{
  return d_size;
}


void Button::setPositionOrigin(const PositionOrigin i_positionOrigin)
{
  d_positionOrigin = std::move(i_positionOrigin);
}

PositionOrigin Button::getPositionOrigin() const
{
  return d_positionOrigin;
}


void Button::setState(const State i_state)
{
  d_state = i_state;
  notify(GuiControlTextureChangedEvent(*this));
}

Button::State Button::getState() const
{
  return d_state;
}


void Button::setText(std::string i_text)
{
  d_text = std::move(i_text);
  notify(GuiControlTextChangedEvent(*this));
}

const std::string& Button::getText() const
{
  return d_text;
}
