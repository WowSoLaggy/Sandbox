#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class KeyboardHandler
{
public:
  KeyboardHandler(Controller& io_controller);

  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);

private:
  Controller& d_contoller;
};
