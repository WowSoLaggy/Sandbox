#pragma once

#include "Fwd.h"
#include "Terrain.h"

#include <LaggySdk/EventHandler.h>


class World : public Sdk::EventHandler
{
public:
  ~World();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  const std::optional<Terrain>& getTerrain() const;
  void setTerrain(Terrain i_terrain);
  void resetTerrain();

  const std::vector<std::shared_ptr<Object>>& getObjects() const;
  void addObject(std::shared_ptr<Object> i_object);
  void removeObject(Object& i_object);

private:
  std::optional<Terrain> d_terrain;
  std::vector<std::shared_ptr<Object>> d_objects;

  void removeAllObjects();

  void onObjectAdded(Object& i_object);
  void onObjectRemoving(Object& i_object);
};
