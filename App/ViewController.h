#pragma once

#include "CursorView.h"
#include "Fwd.h"
#include "TerrainView.h"
#include "Viewport.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class ViewController : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void update(double i_dt);
  void render(Dx::IRenderer2d& i_renderer) const;

private:
  std::optional<TerrainView> d_terrainView;
  std::vector<std::shared_ptr<ObjectView>> d_objectViews;
  std::vector<std::shared_ptr<IGuiView>> d_guiViews;
  std::optional<CursorView> d_cursorView;

  Sdk::Vector2I d_offset;
  Sdk::Vector2I d_scaleOrigin;
  double d_scale = 1;

  void renderWorld(Dx::IRenderer2d& i_renderer) const;
  void renderGui(Dx::IRenderer2d& i_renderer) const;

  void onObjectEntersViewport(const Object& i_object);
  void onObjectLeavesViewport(const Object& i_object);
  void onViewportChanged(const Viewport& i_viewport);
  void onObjectTextureChanged(const Object& i_object);
  void onObjectSizeChanged(const Object& i_object);
  void onTerrainAdded(const Terrain& i_terrain);
  void onTerrainReset();
  void onWorldCreated(const World& i_world);
  void onWorldDisposing();
  void onGuiControlAdded(const IGuiControl& i_gui);
  void onGuiControlRemoving(const IGuiControl& i_gui);
  void onGuiControlTextureChanged(const IGuiControl& i_gui);
  void onGuiControlSizeChanged(const IGuiControl& i_gui);
  void onGuiControlTextChanged(const IGuiControl& i_gui);
  void onGuiControlColorChanged(const IGuiControl& i_gui);
  void onCursorTextureChanged();
  void onCursorSizeChanged();
  void onCursorShown(const Cursor& i_cursor);
  void onCursorHidden();
};
