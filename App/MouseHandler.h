#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class MouseHandler
{
public:
  MouseHandler(Controller& io_controller);

  void handleMouse(const Dx::MouseState& i_mouseState);

private:
  Controller& d_contoller;
};
