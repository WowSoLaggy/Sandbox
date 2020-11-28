#pragma once

#include "World.h"

#include <LaggySdk/EventHandler.h>


class WorldController : public Sdk::EventHandler
{
public:
  ~WorldController();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void createNewWorld();
  void disposeWorld();
  [[nodiscard]] bool worldCreated() const;

  void updateWorld(double i_dt);

private:
  std::unique_ptr<World> d_world;
  World& getWorld();

  void onNewWorld();
  void onDiposingWorld();
};
