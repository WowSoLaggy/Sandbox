#pragma once

#include <LaggySdk/Vector.h>


class Object
{
public:
  void setTextureName(std::string i_textureName);
  [[nodiscard]] const std::string& getTextureName() const;

  void setPosition(Sdk::Vector2D i_position);
  [[nodiscard]] const Sdk::Vector2D& getPosition() const;

private:
  std::string d_textureName;
  Sdk::Vector2D d_position;
};
