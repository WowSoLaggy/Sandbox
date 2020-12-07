#include "stdafx.h"
#include "GuiViewFactory.h"

#include "Button.h"
#include "ButtonView.h"
#include "Panel.h"
#include "PanelView.h"


std::shared_ptr<IGuiView> getGuiView(const IGuiControl& i_gui)
{
  if (const auto* panel = dynamic_cast<const Panel*>(&i_gui))
    return std::make_shared<PanelView>(*panel);
  else if (const auto* button = dynamic_cast<const Button*>(&i_gui))
    return std::make_shared<ButtonView>(*button);

  CONTRACT_ASSERT(false);
}
