#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class GuiControlEvent : public Sdk::IEvent
{
public:
  GuiControlEvent(const IGuiControl& i_gui)
    : d_gui(i_gui)
  {
  }

  const IGuiControl& getGuiControl() const { return d_gui; }

private:
  const IGuiControl& d_gui;
};


class GuiControlAddedEvent : public GuiControlEvent
{
public:
  GuiControlAddedEvent(const IGuiControl& i_gui)
    : GuiControlEvent(i_gui)
  {
  }
};

class GuiControlRemovingEvent : public GuiControlEvent
{
public:
  GuiControlRemovingEvent(const IGuiControl& i_gui)
    : GuiControlEvent(i_gui)
  {
  }
};

class GuiControlTextureChangedEvent : public GuiControlEvent
{
public:
  GuiControlTextureChangedEvent(const IGuiControl& i_gui)
    : GuiControlEvent(i_gui)
  {
  }
};
