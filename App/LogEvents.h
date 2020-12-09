#pragma once

#include <LaggySdk/IEvent.h>


class LogEvent : public Sdk::IEvent
{
public:
  LogEvent(std::string i_text)
    : d_text(std::move(i_text))
  {
  }

  const std::string& getText() const { return d_text; }

private:
  std::string d_text;
};
