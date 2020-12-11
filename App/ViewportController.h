#pragma once

#include "Fwd.h"
#include "Viewport.h"

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/Vector.h>


class ViewportController : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void setViewport(Viewport i_viewport);
  const Viewport& getViewport() const;

private:
  Viewport d_viewport;

  void createDefaultViewport();

  void onWorldCreated();
  void onViewportChanged();
};
