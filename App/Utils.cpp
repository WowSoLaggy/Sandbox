#include "stdafx.h"
#include "Utils.h"

#include <LaggySdk/StringUtils.h>


std::string v2s(const Sdk::Vector2I& i_vector)
{
  return "{" + std::to_string(i_vector.x) + ", " + std::to_string(i_vector.y) + "}";
}

std::string v2s(const Sdk::Vector2D& i_vector)
{
  return "{" + Sdk::toString(i_vector.x) + ", " + Sdk::toString(i_vector.y) + "}";
}
