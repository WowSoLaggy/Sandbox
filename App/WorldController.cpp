#include "stdafx.h"
#include "WorldController.h"

#include "ObjectEvents.h"
#include "WorldCreator.h"

#include <LaggySdk/Contracts.h>


WorldController::~WorldController()
{
  if (worldCreated())
    disposeWorld();
}


void WorldController::createNewWorld()
{
  CONTRACT_EXPECT(!worldCreated());
  d_world = WorldCreator::createWorld();
  CONTRACT_ENSURE(worldCreated());

  onNewWorld();
}

void WorldController::disposeWorld()
{
  CONTRACT_EXPECT(worldCreated());
  onDiposingWorld();
  d_world.reset();
  CONTRACT_ENSURE(!worldCreated());
}

bool WorldController::worldCreated() const
{
  return d_world.get();
}


void WorldController::addObject(std::shared_ptr<Object> i_object)
{
  getWorld().getObjects().push_back(i_object);
  onObjectAdded(*i_object);
}

void WorldController::removeObject(std::shared_ptr<Object> i_object)
{
  auto& objs = getWorld().getObjects();

  const auto it = std::find_if(objs.cbegin(), objs.cend(),
                               [&](const auto& i_objectPtr)
  {
    return i_objectPtr.get() == i_object.get();
  });

  if (it != objs.cend())
  {
    onObjectRemoving(**it);
    objs.erase(it);
  }
}


World& WorldController::getWorld()
{
  CONTRACT_ASSERT(d_world);
  return *d_world;
}


void WorldController::onNewWorld()
{
  for (const auto& obj : getWorld().getObjects())
    onObjectAdded(*obj);
}

void WorldController::onDiposingWorld()
{
  for (const auto& obj : getWorld().getObjects())
    onObjectRemoving(*obj);
}

void WorldController::onObjectAdded(const Object& i_object)
{
  notify(ObjectAddedEvent(i_object));
}

void WorldController::onObjectRemoving(const Object& i_object)
{
  notify(ObjectRemovingEvent(i_object));
}


void WorldController::updateWorld(const double i_dt)
{
}
