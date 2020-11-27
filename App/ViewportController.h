#pragma once

#include "Fwd.h"

#include <LaggySdk/EventHandler.h>


class ViewportController : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:
  void onObjectAdded(const Object& i_object);
  void onObjectRemoving(const Object& i_object);
};
