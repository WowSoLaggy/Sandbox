#pragma once

#include "World.h"

#include <LaggySdk/EventHandler.h>


class WorldController : public Sdk::EventHandler
{
public:
  ~WorldController();

  void createNewWorld();
  void disposeWorld();
  [[nodiscard]] bool worldCreated() const;

  void addObject(std::shared_ptr<Object> i_object);
  void removeObject(std::shared_ptr<Object> i_object);

  void updateWorld(double i_dt);

private:
  std::unique_ptr<World> d_world;
  World& getWorld();

  void onNewWorld();
  void onDiposingWorld();
  void onObjectAdded(const Object& i_object);
  void onObjectRemoving(const Object& i_object);
};
