#include "stdafx.h"
#include "ViewController.h"

#include "CursorEvents.h"
#include "CursorView.h"
#include "GuiEvents.h"
#include "GuiViewFactory.h"
#include "IGuiView.h"
#include "Object.h"
#include "ObjectEvents.h"
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
  if (const auto* event = dynamic_cast<const ObjectAddedEvent*>(&i_event))
    onObjectAdded(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectRemovingEvent*>(&i_event))
    onObjectRemoving(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectPositionChangedEvent*>(&i_event))
    onObjectPositionChanged(event->getObject(), event->getPrevPosition());
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
    onWorldDisposing(event->getWorld());
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

void ViewController::onObjectAdded(const Object& i_object)
{
  if (isObjectVisible(i_object))
    onObjectEntersViewport(i_object);
}

void ViewController::onObjectRemoving(const Object& i_object)
{
  onObjectLeavesViewport(i_object);
}

void ViewController::onObjectPositionChanged(const Object& i_object, const Sdk::Vector2D& i_prevPosition)
{
  if (!isObjectVisible(i_object, i_prevPosition) && isObjectVisible(i_object))
    onObjectEntersViewport(i_object);
  else if (isObjectVisible(i_object, i_prevPosition) && !isObjectVisible(i_object))
    onObjectLeavesViewport(i_object);
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
  updateViewArea();

  if (d_terrainView)
    updateTerrainViewArea();

  updateVisibleObjects();
}

void ViewController::onObjectTextureChanged(const Object& i_object)
{
  if (!isObjectVisible(i_object))
    return;

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
  if (!isObjectVisible(i_object))
    return;

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
  d_world = &i_world;

  if (const auto& terrain = i_world.getTerrain())
    onTerrainAdded(*terrain);

  for (const auto& obj : i_world.getObjects())
    onObjectAdded(*obj);
}

void ViewController::onWorldDisposing(const World& i_world)
{
  if (d_terrainView)
    onTerrainReset();

  for (const auto& obj : i_world.getObjects())
    onObjectRemoving(*obj);

  d_world = nullptr;
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

void ViewController::updateViewArea()
{
  const auto topLeft = d_projector.screenToWorld(Sdk::Vector2I::zero());
  const auto bottomRight = d_projector.screenToWorld(getClientSize());

  const double scaleFactor = SettingsProvider::getDefaultInternalSettings().scaleFactor;

  d_viewArea = Sdk::Rect(topLeft / scaleFactor, bottomRight / scaleFactor);
}

void ViewController::updateTerrainViewArea()
{
  CONTRACT_ASSERT(d_terrainView);
  d_terrainView->updateDrawArea({ d_viewArea.left(), d_viewArea.right(), d_viewArea.top(), d_viewArea.bottom() });
}


bool ViewController::isObjectVisible(const Object& i_object)
{
  return isObjectVisible(i_object, i_object.getPosition());
}

bool ViewController::isObjectVisible(const Object& i_object, const Sdk::Vector2D& i_position)
{
  const double halfSize = i_object.getSize() / 2;
  const auto rect = Sdk::RectD(
    i_position.x - halfSize, i_position.x + halfSize,
    i_position.y - halfSize, i_position.y + halfSize);

  return d_viewArea.intersectRect(rect);
}


bool ViewController::hasViewForObject(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_viewPtr)
                               {
                                 return &i_viewPtr->getObject() == &i_object;
                               });
  return it != d_objectViews.cend();
}

void ViewController::updateVisibleObjects()
{
  if (!d_world)
    return;

  for (const auto objectPtr : d_world->getObjects())
  {
    const auto& object = *objectPtr;

    if (hasViewForObject(object))
    {
      if (!isObjectVisible(object))
        onObjectRemoving(object);
    }
    else
    {
      onObjectAdded(object);
    }
  }
}
