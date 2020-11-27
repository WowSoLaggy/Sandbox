#include "stdafx.h"
#include "ViewController.h"

#include "ObjectView.h"
#include "ViewportEvents.h"


void ViewController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const ObjectEntersViewport*>(&i_event))
    onObjectEntersViewport(event->getObject());
  else if (const auto* event = dynamic_cast<const ObjectLeavesViewport*>(&i_event))
    onObjectLeavesViewport(event->getObject());
}


void ViewController::update(const double i_dt)
{
  for (auto& view : d_views)
    view->update(i_dt);
}

void ViewController::render(Dx::IRenderer2d& i_renderer) const
{
  for (const auto& view : d_views)
    view->render(i_renderer);
}


void ViewController::onObjectEntersViewport(const Object& i_object)
{
  const auto view = std::make_shared<ObjectView>(i_object);
  d_views.push_back(std::move(view));
}

void ViewController::onObjectLeavesViewport(const Object& i_object)
{
  const auto it = std::find_if(d_views.cbegin(), d_views.cend(),
                               [&](const auto& i_viewPtr)
  {
    return &i_viewPtr->getObject() == &i_object;
  });

  if (it != d_views.cend())
    d_views.erase(it);
}
