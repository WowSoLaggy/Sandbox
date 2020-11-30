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

  void onObjectAdded(const Object& i_object);
  void onObjectRemoving(const Object& i_object);
  void onObjectPositionChanged(const Object& i_object, const Sdk::Vector2D& i_prevPosition);
  void onObjectEntersViewport(const Object& i_object);
  void onObjectLeavesViewport(const Object& i_object);
  void onObjectTextureChanged(const Object& i_object);
  void onObjectSizeChanged(const Object& i_object);
  void onWorldCreated(const World& i_world);
  void onWorldDisposing(const World& i_world);
  void onViewportChanged();
};
