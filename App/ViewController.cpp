#include "stdafx.h"
#include "ViewController.h"

#include "CursorEvents.h"
#include "CursorView.h"
#include "GuiEvents.h"
#include "GuiViewFactory.h"
#include "IGuiView.h"
#include "ObjectView.h"
#include "SettingsProvider.h"
#include "TerrainEvents.h"
#include "ViewportEvents.h"
#include "World.h"
#include "WorldEvents.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/Renderer2dGuard.h>
#include <LaggySdk/Vector.h>


namespace
{
  Sdk::Vector2I getClientSize()
  {
    const auto userSettings = SettingsProvider::getDefaultUserSettings();
    return { userSettings.clientWidth, userSettings.clientHeight };
  }

} // anon NS


void ViewController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const ObjectEntersViewport*>(&i_event))
    onObjectEntersViewport(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectLeavesViewport*>(&i_event))
    onObjectLeavesViewport(event->getObject());
  else if (const auto* event = dynamic_cast<const ViewportChangedEvent*>(&i_event))
    onViewportChanged(event->getViewport());
  else if (const auto* event = dynamic_cast<const ObjectTextureChangedEvent*>(&i_event))
    onObjectTextureChanged(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectSizeChangedEvent*>(&i_event))
    onObjectSizeChanged(event->getObject());
  else if (const auto* event = dynamic_cast<const TerrainAddedEvent*>(&i_event))
    onTerrainAdded(event->getTerrain());
  else if (const auto* event = dynamic_cast<const TerrainResetEvent*>(&i_event))
    onTerrainReset();
  else if (const auto* event = dynamic_cast<const WorldCreatedEvent*>(&i_event))
    onWorldCreated(event->getWorld());
  else if (const auto* event = dynamic_cast<const WorldDisposingEvent*>(&i_event))
    onWorldDisposing();
  else if (const auto* event = dynamic_cast<const GuiControlAddedEvent*>(&i_event))
    onGuiControlAdded(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlRemovingEvent*>(&i_event))
    onGuiControlRemoving(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlTextureChangedEvent*>(&i_event))
    onGuiControlTextureChanged(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlSizeChangedEvent*>(&i_event))
    onGuiControlSizeChanged(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlTextChangedEvent*>(&i_event))
    onGuiControlTextChanged(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlColorChangedEvent*>(&i_event))
    onGuiControlColorChanged(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const CursorTextureChangedEvent*>(&i_event))
    onCursorTextureChanged();
  else if (const auto* event = dynamic_cast<const CursorSizeChangedEvent*>(&i_event))
    onCursorSizeChanged();
  else if (const auto* event = dynamic_cast<const CursorShownEvent*>(&i_event))
    onCursorShown(event->getCursor());
  else if (dynamic_cast<const CursorHiddenEvent*>(&i_event))
    onCursorHidden();
}


void ViewController::update(const double i_dt)
{
  if (d_terrainView)
    d_terrainView->update(i_dt);
  for (auto& view : d_objectViews)
    view->update(i_dt);
  for (auto& view : d_guiViews)
    view->update(i_dt);
  if (d_cursorView)
    d_cursorView->update(i_dt);
}

void ViewController::render(Dx::IRenderer2d& i_renderer) const
{
  renderWorld(i_renderer);
  renderGui(i_renderer);

  const int renderedSprites = i_renderer.resetRenderedSprites();
  Log::info("Rendered sprites: " + std::to_string(renderedSprites));
}

void ViewController::renderWorld(Dx::IRenderer2d& i_renderer) const
{
  const Dx::Renderer2dGuard rendererGuard(i_renderer,
                                          d_offset,
                                          d_scaleOrigin,
                                          { d_scale, d_scale });

  if (d_terrainView)
  {
    i_renderer.resetTranslation();
    d_terrainView->render(i_renderer);
  }

  for (const auto& view : d_objectViews)
  {
    i_renderer.resetTranslation();
    view->render(i_renderer);
  }
}

void ViewController::renderGui(Dx::IRenderer2d& i_renderer) const
{
  Dx::Renderer2dGuard rendererGuard(i_renderer);

  for (const auto& view : d_guiViews)
  {
    i_renderer.resetTranslation();
    view->render(i_renderer);
  }

  if (d_cursorView)
  {
    i_renderer.resetTranslation();
    d_cursorView->render(i_renderer);
  }
}


void ViewController::onObjectEntersViewport(const Object& i_object)
{
  const auto viewPtr = std::make_shared<ObjectView>(i_object);
  d_objectViews.push_back(std::move(viewPtr));
}

void ViewController::onObjectLeavesViewport(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_objectViewPtr) {
                                 if (const auto* objectView = dynamic_cast<const ObjectView*>(i_objectViewPtr.get()))
                                   return &objectView->getObject() == &i_object;
                                 return false;
                               });

  if (it != d_objectViews.cend())
    d_objectViews.erase(it);
}

void ViewController::onViewportChanged(const Viewport& i_viewport)
{
  const double scaleFactor = SettingsProvider::getDefaultInternalSettings().scaleFactor;

  d_offset = {
    (int)(-i_viewport.lookAt.x * scaleFactor + i_viewport.width / 2),
    (int)(-i_viewport.lookAt.y * scaleFactor + i_viewport.height / 2) };

  d_scaleOrigin = {
    (int)(i_viewport.lookAt.x * scaleFactor),
    (int)(i_viewport.lookAt.y * scaleFactor) };

  d_scale = i_viewport.scale;

  updateProjector();

  if (d_terrainView)
    updateTerrainViewArea();
}

void ViewController::onObjectTextureChanged(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_objectViewPtr) {
                                 return &i_objectViewPtr->getObject() == &i_object;
                               });
  if (it == d_objectViews.cend())
    return;

  auto& objectView = **it;
  objectView.updateTextures();
}

void ViewController::onObjectSizeChanged(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_objectViewPtr) {
                                 return &i_objectViewPtr->getObject() == &i_object;
                               });
  if (it == d_objectViews.cend())
    return;

  auto& objectView = **it;
  objectView.updateSize();
}

void ViewController::onTerrainAdded(const Terrain& i_terrain)
{
  d_terrainView.emplace(i_terrain);
  updateTerrainViewArea();
}

void ViewController::onTerrainReset()
{
  d_terrainView.reset();
}

void ViewController::onWorldCreated(const World& i_world)
{
  if (const auto& terrain = i_world.getTerrain())
    onTerrainAdded(*terrain);
}

void ViewController::onWorldDisposing()
{
  if (d_terrainView)
    onTerrainReset();
}

void ViewController::onGuiControlAdded(const IGuiControl& i_gui)
{
  const auto viewPtr = getGuiView(i_gui);
  d_guiViews.push_back(std::move(viewPtr));
}

void ViewController::onGuiControlRemoving(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr) {
                                 return &i_guiViewPtr->getGuiControl() == &i_gui;
                               });

  if (it != d_guiViews.cend())
    d_guiViews.erase(it);
}

void ViewController::onGuiControlTextureChanged(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr) {
                                 return &i_guiViewPtr->getGuiControl() == &i_gui;
                               });
  if (it == d_guiViews.cend())
    return;

  auto& guiView = **it;
  guiView.updateTextures();
}

void ViewController::onGuiControlSizeChanged(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr) {
                                 return &i_guiViewPtr->getGuiControl() == &i_gui;
                               });
  if (it == d_guiViews.cend())
    return;

  auto& guiView = **it;
  guiView.updateSize();
}

void ViewController::onGuiControlTextChanged(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr) {
                                 return &i_guiViewPtr->getGuiControl() == &i_gui;
                               });
  if (it == d_guiViews.cend())
    return;

  auto& guiView = **it;
  guiView.updateText();
}

void ViewController::onGuiControlColorChanged(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr) {
                                 return &i_guiViewPtr->getGuiControl() == &i_gui;
                               });
  if (it == d_guiViews.cend())
    return;

  auto& guiView = **it;
  guiView.updateColor();
}

void ViewController::onCursorTextureChanged()
{
  if (d_cursorView)
    d_cursorView->updateTextures();
}

void ViewController::onCursorSizeChanged()
{
  if (d_cursorView)
    d_cursorView->updateSize();
}

void ViewController::onCursorShown(const Cursor& i_cursor)
{
  d_cursorView.emplace(i_cursor);
}

void ViewController::onCursorHidden()
{
  d_cursorView.reset();
}


void ViewController::updateProjector()
{
  d_projector.setTranslation(d_offset);
  d_projector.setScaleOrigin(d_scaleOrigin);
  d_projector.setScale(d_scale);
}

void ViewController::updateTerrainViewArea()
{
  CONTRACT_ASSERT(d_terrainView);

  const auto topLeft = d_projector.screenToWorld(Sdk::Vector2I::zero());
  const auto bottomRight = d_projector.screenToWorld(getClientSize());

  d_terrainView->updateDrawArea({ (int)topLeft.x, (int)(bottomRight.x), (int)topLeft.y, (int)(bottomRight.y) });
}
