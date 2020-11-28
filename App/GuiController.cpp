#include "stdafx.h"
#include "GuiController.h"

#include "GuiEvents.h"


GuiController::GuiController()
{
  connectTo(d_guiCollection);
}


void GuiController::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GuiControlEvent*>(&i_event))
    notify(i_event);
}


void GuiController::updateGui(const double i_dt)
{
}
