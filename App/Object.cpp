#include "stdafx.h"
#include "Object.h"

#include "ObjectEvents.h"


void Object::setTextureName(const std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
  onTextureChanged();
}

const std::string& Object::getTextureName() const
{
  return d_textureName;
}


void Object::setPosition(const Sdk::Vector2D i_position)
{
  const auto prevPosition = d_position;
  d_position = std::move(i_position);
  onPositionChanged(std::move(prevPosition));
}

const Sdk::Vector2D& Object::getPosition() const
{
  return d_position;
}


void Object::onPositionChanged(Sdk::Vector2D i_prevPosition)
{
  notify(ObjectPositionChangedEvent(*this, std::move(i_prevPosition)));
}

void Object::onTextureChanged()
{
  notify(ObjectTextureChangedEvent(*this));
}
