#include "stdafx.h"
#include "GuiController.h"

#include "Cursor.h"
#include "GuiEvents.h"
#include "MouseEvents.h"


GuiController::GuiController()
{
  connectTo(d_guiCollection);
}


void GuiController::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GuiControlEvent*>(&i_event))
    notify(i_event);
  else if (const auto* event = dynamic_cast<const MouseMovedEvent*>(&i_event))
    onMouseMoved(event->getMousePos());
  else if (const auto* event = dynamic_cast<const MouseClickEvent*>(&i_event))
    onMouseClick(event->getMouseKey(), event->getMousePos());
  else if (const auto* event = dynamic_cast<const MouseReleasedEvent*>(&i_event))
    onMouseRelease(event->getMouseKey(), event->getMousePos());
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


bool GuiController::onMouseClick(const Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  return d_guiCollection.onMouseClick(i_button, i_mousePos);
}

void GuiController::onMouseRelease(const Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  d_guiCollection.onMouseRelease(i_button, i_mousePos);
}

void GuiController::onMouseMoved(const Sdk::Vector2I& i_mousePos)
{
  d_guiCollection.onMouseMove(i_mousePos);
}
