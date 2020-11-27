#include "stdafx.h"
#include "GameStateController.h"

#include "GameEvents.h"


void GameStateController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const GameStartedEvent*>(&i_event))
    onGameStarted();
  else if (const auto* event = dynamic_cast<const GameReadyEvent*>(&i_event))
    onGameReady();
}


void GameStateController::onGameStarted()
{
}

void GameStateController::onGameReady()
{
}
