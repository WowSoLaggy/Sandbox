#include "stdafx.h"
#include "Cursor.h"

#include "CursorEvents.h"


void Cursor::show()
{
  notify(CursorShownEvent(*this));
}

void Cursor::hide()
{
  notify(CursorHiddenEvent(*this));
}


void Cursor::setTextureName(std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
  notify(CursorTextureChangedEvent(*this));
}

const std::string& Cursor::getTextureName() const
{
  return d_textureName;
}


void Cursor::setPosition(const Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& Cursor::getPosition() const
{
  return d_position;
}


void Cursor::setSize(Sdk::Vector2I i_size)
{
  d_size = std::move(i_size);
  notify(CursorSizeChangedEvent(*this));
}

const Sdk::Vector2I& Cursor::getSize() const
{
  return d_size;
}
