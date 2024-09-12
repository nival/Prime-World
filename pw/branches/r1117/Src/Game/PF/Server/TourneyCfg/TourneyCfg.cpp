#include "stdafx.h"
#include "TourneyCfg.h"

namespace tourney
{

static bool enable = false;

REGISTER_VAR( "tourney_enable", enable, STORAGE_NONE );

bool Enabled() { return enable; }

}
