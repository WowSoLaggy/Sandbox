#include "stdafx.h"
#include "IApplication.h"

#include "Application.h"


IApplication& IApplication::get()
{
  static Application app;
  return app;
}
