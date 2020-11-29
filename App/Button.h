#pragma once

#include "IGuiControl.h"


using ButtonHandler = std::function<void()>;


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

  void setState(State i_state);
  State getState() const;

  void setText(std::string i_text);
  const std::string& getText() const;

  void setHandler(ButtonHandler i_handler);

  virtual bool onMouseClick(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos) override;
  virtual void onMouseRelease(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos) override;
  virtual void onMouseMove(const Sdk::Vector2I& i_mousePos) override;

private:
  std::unordered_map<State, std::string> d_textureNames = {
    { State::Normal, "" },
    { State::Light, ""},
    { State::Pressed, ""} };

  Sdk::Vector2I d_position;
  Sdk::Vector2I d_size;
  State d_state = State::Normal;

  std::string d_text;

  ButtonHandler d_handler = nullptr;

  void press();
};
