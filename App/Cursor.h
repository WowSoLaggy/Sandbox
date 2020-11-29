#pragma once

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/Vector.h>


class Cursor : public Sdk::EventHandler
{
public:
  void show();
  void hide();

  void setTextureName(std::string i_textureName);
  const std::string& getTextureName() const;

  void setPosition(Sdk::Vector2I i_position);
  const Sdk::Vector2I& getPosition() const;

private:
  std::string d_textureName;
  Sdk::Vector2I d_position;
};
