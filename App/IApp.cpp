#include "stdafx.h"
#include "IApp.h"

#include "App.h"


IApp& IApp::get()
{
  static App app;
  return app;
}
