#include "stdafx.h"
#include "GuiCollection.h"

#include "GuiEvents.h"
#include "IGuiControl.h"


void GuiCollection::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GuiControlEvent*>(&i_event))
    notify(i_event);
}


const std::vector<std::shared_ptr<IGuiControl>>& GuiCollection::getGuis() const
{
  return d_guis;
}


void GuiCollection::addGui(std::shared_ptr<IGuiControl> i_gui)
{
  d_guis.push_back(i_gui);
  onGuiAdded(*i_gui);
}

void GuiCollection::removeGui(IGuiControl& i_gui)
{
  const auto it = std::find_if(d_guis.cbegin(), d_guis.cend(),
                               [&](const auto& i_guiPtr)
                               {
                                 return i_guiPtr.get() == &i_gui;
                               });

  if (it != d_guis.cend())
  {
    onGuiRemoving(**it);
    d_guis.erase(it);
  }
}

void GuiCollection::removeGuiByTag(const std::string& i_tag)
{
  d_guis.erase(std::remove_if(d_guis.begin(), d_guis.end(),
               [&](const auto& i_guiPtr)
               {
                 if (i_guiPtr->getTag() == i_tag)
                 {
                   onGuiRemoving(*i_guiPtr);
                   return true;
                 }
                 return false;
               }),
               d_guis.end());
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
