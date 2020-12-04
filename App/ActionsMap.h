#pragma once

#include "Actions.h"
#include "ActionType.h"

#include <LaggyDx/KeyboardKeys.h>
#include <LaggyDx/MouseKeys.h>


class ActionsMap
{
public:
  [[nodiscard]] bool isKeyBinded(Dx::KeyboardKey i_key) const;
  [[nodiscard]] bool isKeyBinded(Dx::KeyboardKey i_key, ActionType i_actionType) const;
  [[nodiscard]] bool isKeyBinded(Dx::MouseKey i_key) const;

  void setAction(Dx::KeyboardKey i_key, Action i_action, ActionType i_actionType);
  void setAction(Dx::MouseKey i_key, Action i_action);
  [[nodiscard]] std::optional<Action> getAction(Dx::KeyboardKey i_key, ActionType i_actionType) const;
  [[nodiscard]] std::optional<Action> getAction(Dx::MouseKey i_key) const;
private:
  std::unordered_map<Dx::KeyboardKey, std::pair<Action, ActionType>> d_keyboardMap;
  std::unordered_map<Dx::MouseKey, Action> d_mouseMap;
};
