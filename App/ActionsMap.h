#pragma once

#include "Actions.h"

#include <LaggyDx/KeyboardKeys.h>
#include <LaggyDx/MouseKeys.h>


class ActionsMap
{
public:
  [[nodiscard]] bool isKeyBinded(Dx::KeyboardKey i_key) const;
  [[nodiscard]] bool isKeyBinded(Dx::MouseKey i_key) const;

  void setAction(Dx::KeyboardKey i_key, Action i_action);
  void setAction(Dx::MouseKey i_key, Action i_action);
  std::optional<Action> getAction(Dx::KeyboardKey i_key) const;
  std::optional<Action> getAction(Dx::MouseKey i_key) const;
private:
  std::unordered_map<Dx::KeyboardKey, Action> d_keyboardMap;
  std::unordered_map<Dx::MouseKey, Action> d_mouseMap;
};
