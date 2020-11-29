#include "stdafx.h"
#include "ActionsMap.h"


bool ActionsMap::isKeyBinded(const Dx::KeyboardKey i_key) const
{
  return d_map.find(i_key) != d_map.cend();
}


void ActionsMap::setAction(const Dx::KeyboardKey i_key, const Action i_action)
{
  d_map[i_key] = i_action;
}

std::optional<Action> ActionsMap::getAction(const Dx::KeyboardKey i_key) const
{
  const auto it = d_map.find(i_key);
  return it != d_map.cend() ? std::make_optional(it->second) : std::nullopt;
}
