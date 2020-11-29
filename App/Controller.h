#pragma once

#include "Cursor.h"
#include "MouseHandler.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class Controller : public Sdk::EventHandler
{
public:
  Controller();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  Cursor& getCursor();
  const Cursor& getCursor() const;

  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);
  void handleMouse(const Dx::MouseState& i_mouseState);

  void onMouseClick(Dx::MouseKey i_button);
  void onMouseRelease(Dx::MouseKey i_button);
  void onMouseMove();
  void onMouseWheelChange(int i_wheelChange);

private:
  Cursor d_cursor;
  MouseHandler d_mouseHandler;
};
