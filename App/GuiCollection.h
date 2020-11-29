#pragma once

#include "Fwd.h"

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/Vector.h>


class GuiCollection : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

  const std::vector<std::shared_ptr<IGuiControl>>& getGuis() const;

  void addGui(std::shared_ptr<IGuiControl> i_gui);
  void removeGui(IGuiControl& i_gui);
  void removeGuiByTag(const std::string& i_tag);

  void onMouseMove(const Sdk::Vector2I& i_mousePos);

private:
  std::vector<std::shared_ptr<IGuiControl>> d_guis;

  void onGuiAdded(IGuiControl& i_gui);
  void onGuiRemoving(IGuiControl& i_gui);
};
