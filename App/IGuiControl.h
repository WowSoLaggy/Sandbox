#pragma once

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>
#include <LaggySdk/ITaggable.h>
#include <LaggySdk/Vector.h>


class IGuiControl : public Sdk::EventHandler, public Sdk::ITaggable
{
public:
  virtual bool onMouseClick(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos) { return false; };
  virtual void onMouseRelease(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos) { };
  virtual void onMouseMove(const Sdk::Vector2I& i_mousePos) { };
};
