#pragma once

#include "Fwd.h"


class World
{
public:
  std::vector<std::shared_ptr<Object>>& getObjects();
  const std::vector<std::shared_ptr<Object>>& getObjects() const;

private:
  std::vector<std::shared_ptr<Object>> d_objects;
};
