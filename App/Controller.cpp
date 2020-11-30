#include "stdafx.h"
#include "Controller.h"

#include "ActionsMaps.h"
#include "CursorEvents.h"
#include "Cursors.h"
#include "MouseEvents.h"


Controller::Controller(Game& io_game)
  : d_cursor(getDefaultCursor())
  , d_keyboardHandler(*this)
  , d_mouseHandler(*this)
  , d_actionsMap(getDefaultActionsMap())
  , d_actionsImpl(io_game)
{
  connectTo(d_cursor);
}


void Controller::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const CursorEvent*>(&i_event))
    notify(i_event);
}


Cursor& Controller::getCursor()
{
  return d_cursor;
}

const Cursor& Controller::getCursor() const
{
  return d_cursor;
}

const ActionsMap& Controller::getActionsMap() const
{
  return d_actionsMap;
}


void Controller::runAction(Action i_action)
{
  d_actionsImpl.runAction(i_action);
}


void Controller::handleKeyboard(const Dx::KeyboardState& i_keyboardState)
{
  d_keyboardHandler.handleKeyboard(i_keyboardState);
}

void Controller::handleMouse(const Dx::MouseState& i_mouseState)
{
  d_mouseHandler.handleMouse(i_mouseState);
}


void Controller::onMouseClick(Dx::MouseKey i_button)
{
  notify(MouseClickEvent(i_button, d_cursor.getPosition()));
}

void Controller::onMouseRelease(Dx::MouseKey i_button)
{
  notify(MouseReleasedEvent(i_button, d_cursor.getPosition()));
}

void Controller::onMouseMove()
{
  notify(MouseMovedEvent(d_cursor.getPosition()));
}

void Controller::onMouseWheelChange(int i_wheelChange)
{
  notify(MouseWheelEvent(d_cursor.getPosition(), i_wheelChange));
}
