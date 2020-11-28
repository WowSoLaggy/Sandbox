#pragma once

#include "GuiCollection.h"

#include <LaggySdk/EventHandler.h>


class GuiController : public Sdk::EventHandler
{
public:
  GuiController();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void updateGui(double i_dt);

private:
  GuiCollection d_guiCollection;
};
