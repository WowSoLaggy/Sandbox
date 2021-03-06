#include "stdafx.h"
#include "World.h"

#include "Object.h"
#include "ObjectEvents.h"
#include "TerrainEvents.h"


World::~World()
{
  removeAllObjects();
  resetTerrain();
}


void World::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const ObjectEvent*>(&i_event))
    notify(i_event);
}


const std::optional<Terrain>& World::getTerrain() const
{
  return d_terrain;
}

void World::setTerrain(Terrain i_terrain)
{
  d_terrain.emplace(std::move(i_terrain));
  notify(TerrainAddedEvent(*d_terrain));
}

void World::resetTerrain()
{
  if (d_terrain.has_value())
  {
    d_terrain.reset();
    notify(TerrainResetEvent());
  }
}


const std::vector<std::shared_ptr<Object>>& World::getObjects() const
{
  return d_objects;
}

void World::addObject(std::shared_ptr<Object> i_object)
{
  d_objects.push_back(i_object);
  onObjectAdded(*i_object);
}

void World::removeObject(Object& i_object)
{
  const auto it = std::find_if(d_objects.cbegin(), d_objects.cend(),
                               [&](const auto& i_objectPtr)
  {
    return i_objectPtr.get() == &i_object;
  });

  if (it != d_objects.cend())
  {
    onObjectRemoving(**it);
    d_objects.erase(it);
  }
}


void World::removeAllObjects()
{
  for (auto& obj : d_objects)
    onObjectRemoving(*obj);
  d_objects.clear();
}


void World::onObjectAdded(Object& i_object)
{
  connectTo(i_object);
  notify(ObjectAddedEvent(i_object));
}

void World::onObjectRemoving(Object& i_object)
{
  disconnectFrom(i_object);
  notify(ObjectRemovingEvent(i_object));
}
