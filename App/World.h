#pragma once

#include "Fwd.h"

#include <LaggySdk/EventHandler.h>


class World : public Sdk::EventHandler
{
public:
  ~World();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  const std::vector<std::shared_ptr<Object>>& getObjects() const;

  void addObject(std::shared_ptr<Object> i_object);
  void removeObject(Object& i_object);

private:
  std::vector<std::shared_ptr<Object>> d_objects;

  void removeAllObjects();

  void onObjectAdded(Object& i_object);
  void onObjectRemoving(Object& i_object);
};
