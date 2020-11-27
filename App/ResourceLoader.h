#pragma once

class ResourceLoader
{
public:
  [[nodiscard]] static bool isLoaded();

  static void loadAsync();

private:
  static std::future<bool> s_loadResourcesResult;
};
