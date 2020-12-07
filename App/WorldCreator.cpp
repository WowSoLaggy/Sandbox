#include "stdafx.h"
#include "WorldCreator.h"

#include "Object.h"
#include "TerrainCreator.h"

#include <LaggySdk/Vector.h>


namespace
{
  void createTerrain(World& i_world)
  {
    const auto terrain = TerrainCreator::generateDefault();
    i_world.setTerrain(std::move(terrain));
  }

  void createObjects(World& i_world)
  {
    auto createHuman = [&]() -> Object&
    {
      auto objPtr = std::make_shared<Object>();
      i_world.addObject(objPtr);
      objPtr->setSize(1);
      objPtr->setTextureName("Man.png");
      return *objPtr;
    };

    {
      // Adam
      createHuman();
    }

    {
      // Tom
      auto& obj = createHuman();
      obj.setPosition({ 5, 0 });
    }
  }

} // anon NS


std::unique_ptr<World> WorldCreator::createWorld()
{
  World world;

  createTerrain(world);
  createObjects(world);

  return std::make_unique<World>(std::move(world));
}
