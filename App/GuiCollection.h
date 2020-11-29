#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>
#include <LaggySdk/Vector.h>


class GuiCollection : public Sdk::EventHandler
{
public:
  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void update(double i_dt);

  const std::vector<std::shared_ptr<IGuiControl>>& getGuis() const;

  void addGui(std::shared_ptr<IGuiControl> i_gui);
  void removeGuiByTag(const std::string& i_tag);

  bool onMouseClick(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos);
  void onMouseRelease(Dx::MouseKey i_button, const Sdk::Vector2I& i_mousePos);
  void onMouseMove(const Sdk::Vector2I& i_mousePos);

private:
  std::vector<std::shared_ptr<IGuiControl>> d_guis;
  std::vector<std::shared_ptr<IGuiControl>> d_guisToAdd;
  std::vector<std::shared_ptr<IGuiControl>> d_guisToRemove;

  void removeRequiredGuis();
  void addRequiredGuis();

  void onGuiAdded(IGuiControl& i_gui);
  void onGuiRemoving(IGuiControl& i_gui);
};
