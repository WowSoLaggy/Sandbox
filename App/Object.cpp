#include "stdafx.h"
#include "Object.h"

#include "ObjectEvents.h"


void Object::setTextureName(const std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
  notify(ObjectTextureChangedEvent(*this));
}

const std::string& Object::getTextureName() const
{
  return d_textureName;
}


void Object::setPosition(const Sdk::Vector2D i_position)
{
  const auto prevPosition = d_position;
  d_position = std::move(i_position);
  notify(ObjectPositionChangedEvent(*this, std::move(prevPosition)));
}

const Sdk::Vector2D& Object::getPosition() const
{
  return d_position;
}


void Object::setSize(const double i_diameter)
{
  d_size = i_diameter;
  notify(ObjectSizeChangedEvent(*this));
}

double Object::getSize() const
{
  return d_size;
}
