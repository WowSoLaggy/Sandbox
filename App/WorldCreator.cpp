#include "stdafx.h"
#include "WorldCreator.h"

#include "Object.h"

#include <LaggySdk/Vector.h>


std::unique_ptr<World> WorldCreator::createWorld()
{
  World world;

  auto add = [&](const std::string i_textureName, const Sdk::Vector2D i_position)
  {
    Object obj;
    obj.setTextureName(std::move(i_textureName));
    obj.setPosition(std::move(i_position));
    world.addObject(std::make_shared<Object>(std::move(obj)));
  };

  add("Man.png", { 0, 0 });

  return std::make_unique<World>(std::move(world));
}
