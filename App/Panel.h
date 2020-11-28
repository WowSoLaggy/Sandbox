#pragma once

#include "IGuiControl.h"
#include "PositionOrigin.h"

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

  void setPositionOrigin(PositionOrigin i_positionOrigin);
  PositionOrigin getPositionOrigin() const;

private:
  std::string d_textureName;
  Sdk::Vector2I d_position;
  Sdk::Vector2I d_size;
  PositionOrigin d_positionOrigin = PositionOrigin::TopLeft;
};
