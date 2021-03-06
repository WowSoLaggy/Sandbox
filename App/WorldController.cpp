#include "stdafx.h"
#include "WorldController.h"

#include "GameEvents.h"
#include "Object.h"
#include "ObjectEvents.h"
#include "WorldCreator.h"
#include "WorldEvents.h"


WorldController::~WorldController()
{
  if (worldCreated())
    disposeWorld();
}


void WorldController::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const ObjectEvent*>(&i_event))
    notify(i_event);
  if (dynamic_cast<const NewGameEvent*>(&i_event))
    onNewGame();
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


World& WorldController::getWorld()
{
  CONTRACT_ASSERT(d_world);
  return *d_world;
}


void WorldController::onNewWorld()
{
  connectTo(getWorld());
  notify(WorldCreatedEvent(getWorld()));
}

void WorldController::onDiposingWorld()
{
  disconnectFrom(getWorld());
  notify(WorldDisposingEvent(getWorld()));
}

void WorldController::onNewGame()
{
  if (worldCreated())
    disposeWorld();
  createNewWorld();
}


void WorldController::update(const double i_dt)
{
}
