#include "stdafx.h"
#include "ViewController.h"

#include "GuiEvents.h"
#include "GuiViewFactory.h"
#include "IGuiView.h"
#include "ObjectView.h"
#include "ViewportEvents.h"


void ViewController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const ObjectEntersViewport*>(&i_event))
    onObjectEntersViewport(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectLeavesViewport*>(&i_event))
    onObjectLeavesViewport(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectTextureChangedEvent*>(&i_event))
    onObjectTextureChanged(event->getObject());
  else if (const auto* event = dynamic_cast<const GuiControlAddedEvent*>(&i_event))
    onGuiControlAdded(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlRemovingEvent*>(&i_event))
    onGuiControlRemoving(event->getGuiControl());
  else if (const auto* event = dynamic_cast<const GuiControlTextureChangedEvent*>(&i_event))
    onGuiControlTextureChanged(event->getGuiControl());
}


void ViewController::update(const double i_dt)
{
  for (auto& view : d_objectViews)
    view->update(i_dt);
  for (auto& view : d_guiViews)
    view->update(i_dt);
}

void ViewController::render(Dx::IRenderer2d& i_renderer) const
{
  for (const auto& view : d_objectViews)
    view->render(i_renderer);
  for (const auto& view : d_guiViews)
    view->render(i_renderer);
}


void ViewController::onObjectEntersViewport(const Object& i_object)
{
  const auto viewPtr = std::make_shared<ObjectView>(i_object);
  d_objectViews.push_back(std::move(viewPtr));
}

void ViewController::onObjectLeavesViewport(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_objectViewPtr)
  {
    if (const auto* objectView = dynamic_cast<const ObjectView*>(i_objectViewPtr.get()))
      return &objectView->getObject() == &i_object;
    return false;
  });

  if (it != d_objectViews.cend())
    d_objectViews.erase(it);
}

void ViewController::onObjectTextureChanged(const Object& i_object)
{
  const auto it = std::find_if(d_objectViews.cbegin(), d_objectViews.cend(),
                               [&](const auto& i_objectViewPtr)
  {
    return &i_objectViewPtr->getObject() == &i_object;
  });
  if (it == d_objectViews.cend())
    return;

  auto& objectView = **it;
  objectView.updateTextures();
}

void ViewController::onGuiControlAdded(const IGuiControl& i_gui)
{
  const auto viewPtr = getGuiView(i_gui);
  d_guiViews.push_back(std::move(viewPtr));
}

void ViewController::onGuiControlRemoving(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr)
  {
    return &i_guiViewPtr->getGuiControl() == &i_gui;
  });

  if (it != d_guiViews.cend())
    d_guiViews.erase(it);
}

void ViewController::onGuiControlTextureChanged(const IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guiViews.cbegin(), d_guiViews.cend(),
                               [&](const auto& i_guiViewPtr)
  {
    return &i_guiViewPtr->getGuiControl() == &i_gui;
  });
  if (it == d_guiViews.cend())
    return;

  auto& guiView = **it;
  guiView.updateTextures();
}

