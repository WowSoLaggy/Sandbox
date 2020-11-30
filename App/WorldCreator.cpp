#include "stdafx.h"
#include "WorldCreator.h"

#include "Object.h"

#include <LaggySdk/Vector.h>


std::unique_ptr<World> WorldCreator::createWorld()
{
  World world;

  auto createHuman = [&]() -> Object&
  {
    auto objPtr = std::make_shared<Object>();
    world.addObject(objPtr);
    objPtr->setSize(1);
    objPtr->setTextureName("Man.png");
    return *objPtr;
  };

  {
    // Adam
    createHuman();
  }

  return std::make_unique<World>(std::move(world));
}
