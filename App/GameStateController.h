#pragma once

#include <LaggySdk/EventHandler.h>


class GameStateController : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:
  void onGameStarted();
  void onGameReady();
};
