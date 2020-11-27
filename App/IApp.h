#pragma once

class IApp
{
public:
  static IApp& get();

public:
  virtual void run() = 0;
};
