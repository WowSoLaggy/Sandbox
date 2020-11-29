#include "stdafx.h"
#include "GuiCollection.h"

#include "GuiEvents.h"
#include "IGuiControl.h"


void GuiCollection::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GuiControlEvent*>(&i_event))
    notify(i_event);
}


void GuiCollection::update(double i_dt)
{
  removeRequiredGuis();
  addRequiredGuis();

  for (auto& guiControlPtr : d_guis)
    guiControlPtr->update(i_dt);
}


const std::vector<std::shared_ptr<IGuiControl>>& GuiCollection::getGuis() const
{
  return d_guis;
}


void GuiCollection::addGui(std::shared_ptr<IGuiControl> i_gui)
{
  d_guisToAdd.push_back(i_gui);
}

void GuiCollection::removeGuiByTag(const std::string& i_tag)
{
  std::copy_if(d_guis.cbegin(), d_guis.cend(), std::back_inserter(d_guisToRemove),
               [&](const auto& i_guiPtr) {
                 return i_guiPtr->getTag() == i_tag;
               });
}


void GuiCollection::removeRequiredGuis()
{
  if (d_guisToRemove.empty())
    return;

  d_guis.erase(std::remove_if(d_guis.begin(), d_guis.end(),
               [&](const auto& i_guiPtr) {
                 return std::any_of(d_guisToRemove.begin(), d_guisToRemove.end(),
                                    [&](const auto& i_guiToRemovePtr) {
                                      if (i_guiPtr.get() == i_guiToRemovePtr.get())
                                      {
                                        onGuiRemoving(*i_guiPtr);
                                        return true;
                                      }
                                      return false;
                                    });
               }), d_guis.end());

  d_guisToRemove.clear();
}

void GuiCollection::addRequiredGuis()
{
  if (d_guisToAdd.empty())
    return;

  for (auto guiPtr : d_guisToAdd)
  {
    d_guis.push_back(guiPtr);
    onGuiAdded(*guiPtr);
  }

  d_guisToAdd.clear();
}


void GuiCollection::onGuiAdded(IGuiControl& i_gui)
{
  connectTo(i_gui);
  notify(GuiControlAddedEvent(i_gui));
}

void GuiCollection::onGuiRemoving(IGuiControl& i_gui)
{
  disconnectFrom(i_gui);
  notify(GuiControlRemovingEvent(i_gui));
}


bool GuiCollection::onMouseClick(const Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  for (auto& guiControlPtr : d_guis)
  {
    if (guiControlPtr->onMouseClick(i_button, i_mousePos))
      return true;
  }

  return false;
}

void GuiCollection::onMouseRelease(const Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos)
{
  for (auto& guiControlPtr : d_guis)
    guiControlPtr->onMouseRelease(i_button, i_mousePos);
}

void GuiCollection::onMouseMove(const Sdk::Vector2I& i_mousePos)
{
  for (auto& guiControlPtr : d_guis)
    guiControlPtr->onMouseMove(i_mousePos);
}
