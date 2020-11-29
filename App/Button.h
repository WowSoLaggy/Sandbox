#pragma once

#include "IGuiControl.h"
#include "PositionOrigin.h"

#include <LaggySdk/Vector.h>


class Button : public IGuiControl
{
public:
  enum class State
  {
    Normal,
    Light,
    Pressed,
  };

public:
  void setTextureName(State i_state, std::string i_textureName);
  const std::string& getTextureName(State i_state) const;

  void setPosition(Sdk::Vector2I i_position);
  const Sdk::Vector2I& getPosition() const;

  void setSize(Sdk::Vector2I i_size);
  const Sdk::Vector2I& getSize() const;

  void setPositionOrigin(PositionOrigin i_positionOrigin);
  PositionOrigin getPositionOrigin() const;

  void setState(State i_state);
  State getState() const;

  void setText(std::string i_text);
  const std::string& getText() const;

private:
  std::unordered_map<State, std::string> d_textureNames = {
    { State::Normal, "" },
    { State::Light, ""},
    { State::Pressed, ""} };

  Sdk::Vector2I d_position;
  Sdk::Vector2I d_size;
  PositionOrigin d_positionOrigin = PositionOrigin::TopLeft;
  State d_state = State::Normal;

  std::string d_text;
};
