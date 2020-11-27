#include "stdafx.h"

#include "IApplication.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  auto& app = IApplication::get();
  app.run();

  return 0;
}
