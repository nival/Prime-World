#pragma once

#include "../Client/DefaultScreenBase.h"


namespace PF_Minigames
{

class MinigameScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( MinigameScreen, NMainLoop::DefaultScreenBase );

public:
	MinigameScreen();
};

} // namespace PF_Minigames
