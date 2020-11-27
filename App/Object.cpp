#include "stdafx.h"
#include "Object.h"


void Object::setTextureName(const std::string i_textureName)
{
  d_textureName = std::move(i_textureName);
}

const std::string& Object::getTextureName() const
{
  return d_textureName;
}


void Object::setPosition(const Sdk::Vector2D i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2D& Object::getPosition() const
{
  return d_position;
}
