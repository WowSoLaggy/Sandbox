#pragma once

class IApp
{
public:
  static IApp& get();

public:
  virtual ~IApp() = default;

  virtual void run() = 0;
};
