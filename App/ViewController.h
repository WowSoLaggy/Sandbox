#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class ViewController : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

private:
  std::shared_ptr<CursorView> d_cursorView;
  std::vector<std::shared_ptr<ObjectView>> d_objectViews;
  std::vector<std::shared_ptr<IGuiView>> d_guiViews;

  void onObjectEntersViewport(const Object& i_object);
  void onObjectLeavesViewport(const Object& i_object);
  void onObjectTextureChanged(const Object& i_object);
  void onGuiControlAdded(const IGuiControl& i_gui);
  void onGuiControlRemoving(const IGuiControl& i_gui);
  void onGuiControlTextureChanged(const IGuiControl& i_gui);
  void onGuiControlSizeChanged(const IGuiControl& i_gui);
  void onGuiControlTextChanged(const IGuiControl& i_gui);
  void onCursorTextureChanged();
  void onCursorSizeChanged();
  void onCursorShown(const Cursor& i_cursor);
  void onCursorHidden();
};
