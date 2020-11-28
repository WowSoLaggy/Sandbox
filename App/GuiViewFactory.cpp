#include "stdafx.h"
#include "GuiViewFactory.h"

#include "Panel.h"
#include "PanelView.h"

#include <LaggySdk/Contracts.h>


std::shared_ptr<IGuiView> getGuiView(const IGuiControl& i_gui)
{
  if (const auto* panel = dynamic_cast<const Panel*>(&i_gui))
    return std::make_shared<PanelView>(*panel);

  CONTRACT_ASSERT(false);
}
