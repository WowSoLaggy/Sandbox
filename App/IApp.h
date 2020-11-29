#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class IApp
{
public:
  static IApp& get();

public:
  virtual ~IApp() = default;

  virtual void run() = 0;
  virtual void stop() = 0;

  virtual Dx::IResourceController& getResourceController() = 0;
};
