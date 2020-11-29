#include "stdafx.h"
#include "MouseHandler.h"

#include "Controller.h"

#include <LaggyDx/MouseState.h>


MouseHandler::MouseHandler(Controller& io_controller)
  : d_contoller(io_controller)
{
}


void MouseHandler::handleMouse(const Dx::MouseState& i_mouseState)
{
  const auto& mousePosRaw = i_mouseState.getPosition();
  if (i_mouseState.getMode() == Dx::MouseMode::Absolute)
  {
    if (mousePosRaw != d_contoller.getCursor().getPosition())
    {
      d_contoller.getCursor().setPosition(mousePosRaw);
      d_contoller.onMouseMove();
    }
  }
  else
  {
    if (mousePosRaw != Sdk::Vector2I{ 0, 0 })
    {
      auto& cursor = d_contoller.getCursor();
      cursor.setPosition(cursor.getPosition() + mousePosRaw);
      d_contoller.onMouseMove();
    }
  }

  if (int wheelChange = i_mouseState.getWheelPositionChange(); wheelChange != 0)
    d_contoller.onMouseWheelChange(wheelChange > 0 ? +1 : -1);

  if (i_mouseState.getLeftButtonState() == Dx::ButtonState::Pressed)
    d_contoller.onMouseClick(Dx::MouseKey::Left);
  else if (i_mouseState.getLeftButtonState() == Dx::ButtonState::Released)
    d_contoller.onMouseRelease(Dx::MouseKey::Left);

  if (i_mouseState.getRightButtonState() == Dx::ButtonState::Pressed)
    d_contoller.onMouseClick(Dx::MouseKey::Right);
  else if (i_mouseState.getRightButtonState() == Dx::ButtonState::Released)
    d_contoller.onMouseRelease(Dx::MouseKey::Right);
}