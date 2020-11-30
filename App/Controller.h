#pragma once

#include "Actions.h"
#include "ActionsImpl.h"
#include "ActionsMap.h"
#include "Cursor.h"
#include "Fwd.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class Controller : public Sdk::EventHandler
{
public:
  Controller(Game& io_game);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  Cursor& getCursor();
  const Cursor& getCursor() const;

  const ActionsMap& getActionsMap() const;

  void runAction(Action i_action);

  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);
  void handleMouse(const Dx::MouseState& i_mouseState);

  void onMouseClick(Dx::MouseKey i_button);
  void onMouseRelease(Dx::MouseKey i_button);
  void onMouseMove();
  void onMouseWheelChange(int i_wheelChange);

private:
  Cursor d_cursor;
  KeyboardHandler d_keyboardHandler;
  MouseHandler d_mouseHandler;
  ActionsMap d_actionsMap;
  ActionsImpl d_actionsImpl;
};
