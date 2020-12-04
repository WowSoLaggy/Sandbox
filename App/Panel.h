#pragma once

#include "IGuiControl.h"

#include <LaggySdk/Vector.h>


class Panel : public IGuiControl
{
public:
  void setTextureName(std::string i_textureName);
  const std::string& getTextureName() const;

  void setPosition(Sdk::Vector2I i_position);
  const Sdk::Vector2I& getPosition() const;

  void setSize(Sdk::Vector2I i_size);
  const Sdk::Vector2I& getSize() const;

  void setColor(Sdk::Vector4F i_color);
  const Sdk::Vector4F& getColor() const;

private:
  std::string d_textureName;
  Sdk::Vector2I d_position;
  Sdk::Vector2I d_size;
  Sdk::Vector4F d_color = Sdk::Vector4F::identity();
};
