#include "stdafx.h"
#include "ResourceLoader.h"

#include "IApp.h"

#include <LaggyDx/IResourceController.h>
#include <LaggySdk/Contracts.h>


namespace
{
  bool loadResources()
  {
    try
    {
      auto& rc = IApp::get().getResourceController();
      rc.loadResources();
      std::this_thread::sleep_for(100ms);
    }
    catch (...)
    {
      return false;
    }

    return true;
  }

} // anon NS


std::future<bool> ResourceLoader::s_loadResourcesResult;


bool ResourceLoader::isLoaded()
{
  if (!s_loadResourcesResult.valid() || s_loadResourcesResult.wait_for(0ms) == std::future_status::timeout)
    return false;

  const bool success = s_loadResourcesResult.get();
  CONTRACT_ENSURE(success);

  return true;
}


void ResourceLoader::loadAsync()
{
  s_loadResourcesResult = std::async(loadResources);
}
