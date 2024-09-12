#pragma once

#include "../Scripts/Script.h"

#if 0

namespace NCore
{
	/**
	 * Adventure script system
	 * used lua threads to demand function call and realize event system on adventure map
	 * thread resume will be after world command execution
	 * threads are implemented in NScript::Script
	 */

	/** return adventure script machine singleton */
	NScript::Script* GetAdventureScript();
}

#endif //0
