#pragma once

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/ITaggable.h>


class IGuiControl : public Sdk::EventHandler, public Sdk::ITaggable
{
};
