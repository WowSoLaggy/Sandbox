#pragma once

#include <LaggySdk/Vector.h>
#include <LaggySdk/EventHandler.h>


class Object : public Sdk::EventHandler
{
public:
  void setTextureName(std::string i_textureName);
  [[nodiscard]] const std::string& getTextureName() const;

  void setPosition(Sdk::Vector2D i_position);
  [[nodiscard]] const Sdk::Vector2D& getPosition() const;

  void setSize(double i_diameter);
  double getSize() const;

private:
  std::string d_textureName;
  Sdk::Vector2D d_position;

  // Diameter, in meters
  double d_size = 0;
};
