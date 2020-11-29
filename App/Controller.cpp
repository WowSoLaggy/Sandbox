#include "stdafx.h"
#include "Controller.h"

#include "CursorEvents.h"
#include "Cursors.h"
#include "IApp.h"
#include "MouseEvents.h"

#include <LaggyDx/KeyboardState.h>
#include <LaggyDx/MouseState.h>


Controller::Controller()
  : d_mouseHandler(*this)
  , d_cursor(getDefaultCursor())
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


void Controller::handleKeyboard(const Dx::KeyboardState& i_keyboardState)
{
  const auto& pressedKeys = i_keyboardState.getPressedKeys();
  const auto& currentKeys = i_keyboardState.getCurrentKeys();
  const auto& releasedKeys = i_keyboardState.getReleasedKeys();

  if (pressedKeys.Escape)
    IApp::get().stop();
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
}
