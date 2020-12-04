#include "stdafx.h"
#include "ActionsMaps.h"


ActionsMap getDefaultActionsMap()
{
  ActionsMap actionsMap;

  auto setKey = [&](const Dx::KeyboardKey i_key, const Action i_action, const ActionType i_actionType) {
    actionsMap.setAction(i_key, i_action, i_actionType);
  };
  auto setMouse = [&](const Dx::MouseKey i_key, const Action i_action) {
    actionsMap.setAction(i_key, i_action);
  };

  setKey(Dx::KeyboardKey::Escape, Action::QuitGame, ActionType::OnPress);

  setKey(Dx::KeyboardKey::A, Action::MoveCameraLeft, ActionType::Continuous);
  setKey(Dx::KeyboardKey::W, Action::MoveCameraUp, ActionType::Continuous);
  setKey(Dx::KeyboardKey::D, Action::MoveCameraRight, ActionType::Continuous);
  setKey(Dx::KeyboardKey::S, Action::MoveCameraDown, ActionType::Continuous);

  setMouse(Dx::MouseKey::WheelUp, Action::ZoomIn);
  setMouse(Dx::MouseKey::WheelDown, Action::ZoomOut);

  return actionsMap;
}
