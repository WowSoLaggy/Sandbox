#include "stdafx.h"
#include "ActionsMaps.h"


ActionsMap getDefaultActionsMap()
{
  ActionsMap actionsMap;

  auto set = [&](const auto i_key, const Action i_action) {
    actionsMap.setAction(i_key, i_action);
  };

  set(Dx::KeyboardKey::Escape, Action::QuitGame);
  set(Dx::KeyboardKey::A, Action::MoveCameraLeft);
  set(Dx::KeyboardKey::W, Action::MoveCameraUp);
  set(Dx::KeyboardKey::D, Action::MoveCameraRight);
  set(Dx::KeyboardKey::S, Action::MoveCameraDown);
  set(Dx::MouseKey::WheelUp, Action::ZoomIn);
  set(Dx::MouseKey::WheelDown, Action::ZoomOut);

  return actionsMap;
}
