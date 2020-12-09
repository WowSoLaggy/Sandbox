#include "stdafx.h"
#include "Log.h"

#include "LogEvents.h"


Log& Log::getInstance()
{
  static Log log;
  return log;
}


void Log::info(std::string i_text)
{
  getInstance().notify(LogEvent(std::move(i_text)));
}
