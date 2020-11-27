#include "stdafx.h"

#include "IApp.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  auto& app = IApp::get();
  app.run();

  return 0;
}
