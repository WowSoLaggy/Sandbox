#include "stdafx.h"
#include "World.h"


std::vector<std::shared_ptr<Object>>& World::getObjects()
{
  return d_objects;
}

const std::vector<std::shared_ptr<Object>>& World::getObjects() const
{
  return d_objects;
}
