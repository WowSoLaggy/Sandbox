#include "stdafx.h"
#include "Console.h"

#include "LogEvents.h"


Console::Console()
{
}


void Console::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const LogEvent*>(&i_event))
    onLogAdded(event->getText());
}


void Console::update(const double i_dt)
{
  setText(d_fullLog);
}


void Console::onLogAdded(std::string i_log)
{
  d_logs.push_back(std::move(i_log));
  if (d_logs.size() > 15)
    d_logs.pop_front();

  d_fullLog.clear();
  for (const auto& str : d_logs)
    d_fullLog.append(str + "\n");
}
