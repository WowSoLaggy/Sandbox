#pragma once

#include "Panel.h"


class Console : public Panel
{
public:
  Console();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  virtual void update(double i_dt) override;

private:
  std::string d_fullLog;
  std::deque<std::string> d_logs;

  void onLogAdded(std::string i_log);
};
