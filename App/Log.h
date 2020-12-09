#pragma once

#include <LaggySdk/EventHandler.h>


class Log : public Sdk::EventHandler
{
public:
  static Log& getInstance();

  static void info(std::string i_text);
};
