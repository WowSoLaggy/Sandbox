#include "stdafx.h"
#include "GuiController.h"

#include "Cursor.h"
#include "CursorEvents.h"
#include "GuiEvents.h"


GuiController::GuiController()
{
  connectTo(d_guiCollection);
}


void GuiController::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GuiControlEvent*>(&i_event))
    notify(i_event);
  if (const auto* event = dynamic_cast<const CursorMovedEvent*>(&i_event))
    onMouseMoved(event->getCursor());
}


void GuiController::updateGui(const double i_dt)
{
}


GuiCollection& GuiController::getGuiCollection()
{
  return d_guiCollection;
}

const GuiCollection& GuiController::getGuiCollection() const
{
  return d_guiCollection;
}


void GuiController::onMouseMoved(const Cursor& i_cursor)
{
  d_guiCollection.onMouseMove(i_cursor.getPosition());
}
