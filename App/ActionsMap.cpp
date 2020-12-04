#include "stdafx.h"
#include "ActionsMap.h"


bool ActionsMap::isKeyBinded(const Dx::KeyboardKey i_key) const
{
  return d_keyboardMap.find(i_key) != d_keyboardMap.cend();
}

bool ActionsMap::isKeyBinded(const Dx::KeyboardKey i_key, ActionType i_actionType) const
{
  auto it = d_keyboardMap.find(i_key);
  if (it == d_keyboardMap.cend())
    return false;

  return it->second.second == i_actionType;
}

bool ActionsMap::isKeyBinded(const Dx::MouseKey i_key) const
{
  return d_mouseMap.find(i_key) != d_mouseMap.cend();
}


void ActionsMap::setAction(const Dx::KeyboardKey i_key, const Action i_action, const ActionType i_actionType)
{
  d_keyboardMap[i_key] = { i_action, i_actionType };
}

void ActionsMap::setAction(const Dx::MouseKey i_key, const Action i_action)
{
  d_mouseMap[i_key] = i_action;
}

std::optional<Action> ActionsMap::getAction(const Dx::KeyboardKey i_key, const ActionType i_actionType) const
{
  const auto it = d_keyboardMap.find(i_key);
  if (it == d_keyboardMap.cend())
    return std::nullopt;

  const auto&[action, type] = it->second;
  return type == i_actionType ? std::make_optional(action) : std::nullopt;
}

std::optional<Action> ActionsMap::getAction(const Dx::MouseKey i_key) const
{
  const auto it = d_mouseMap.find(i_key);
  return it != d_mouseMap.cend() ? std::make_optional(it->second) : std::nullopt;
}
