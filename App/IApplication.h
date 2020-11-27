#pragma once

class IApplication
{
public:
  static IApplication& get();

public:
  virtual void run() = 0;
};
