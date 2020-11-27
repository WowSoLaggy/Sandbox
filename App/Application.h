#pragma once

#include "IApplication.h"

class Application : public IApplication
{
public:
  virtual void run() override;
};
