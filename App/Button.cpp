#include "stdafx.h"
#include "Button.h"

#include "GuiEvents.h"

#include <LaggySdk/Rect.h>


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


bool Button::onMouseClick(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  const auto rect = Sdk::RectI(d_position, d_position + d_size);

  if (i_button == Dx::MouseKey::Left && rect.containsPoint(i_mousePos))
  {
    setState(State::Pressed);
    return true;
  }

  return false;
}

void Button::onMouseRelease(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  const auto rect = Sdk::RectI(d_position, d_position + d_size);

  if (d_state == State::Pressed)
  {
    if (rect.containsPoint(i_mousePos))
    {
      setState(State::Light);
      //press();
    }
    else
      setState(State::Normal);
  }
}

void Button::onMouseMove(const Sdk::Vector2I& i_mousePos)
{
  const auto rect = Sdk::RectI(d_position, d_position + d_size);

  if (d_state == State::Normal && rect.containsPoint(i_mousePos))
    setState(State::Light);
  else if (d_state == State::Light && !rect.containsPoint(i_mousePos))
    setState(State::Normal);
}
