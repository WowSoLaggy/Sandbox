#pragma once

#include "GuiCollection.h"

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class GuiController : public Sdk::EventHandler
{
public:
  GuiController();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void update(double i_dt);

  GuiCollection& getGuiCollection();
  const GuiCollection& getGuiCollection() const;

private:
  GuiCollection d_guiCollection;

  bool onMouseClick(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos);
  void onMouseRelease(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos);
  void onMouseMoved(const Sdk::Vector2I& i_mousePos);
};
