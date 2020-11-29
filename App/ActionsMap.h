#pragma once

#include "Actions.h"

#include <LaggyDx/KeyboardKeys.h>


class ActionsMap
{
public:
  [[nodiscard]] bool isKeyBinded(Dx::KeyboardKey i_key) const;

  void setAction(Dx::KeyboardKey i_key, Action i_action);
  std::optional<Action> getAction(Dx::KeyboardKey i_key) const;
private:
  std::unordered_map<Dx::KeyboardKey, Action> d_map;
};
