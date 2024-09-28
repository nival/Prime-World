#include "stdafx.h"

#if 0

#include "AdventureScriptMachine.h"
#include "../Scripts/Script.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptLog.h"
#include "../Core/GameNode.h"

namespace NCore
{
	NScript::Script* GetAdventureScript()
	{
		static CObj<NScript::Script> pSingleton = new NScript::Script();
		NI_ASSERT( IsValid( pSingleton ), "Invalid adventure script!" );
		return pSingleton;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static bool AdventureScriptsMachineCmd( const char *name, const vector<wstring>& params )
	{
		if ( strcmp(name, "clear_adventure_scripts_cache" ) == 0 )
		{
			GetAdventureScript()->ClearCache();
			systemLog( NLogg::LEVEL_MESSAGE ) << " clear cached adventure scripts..." << endl;
		}
    return true;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace
	{
		inline lua_State *GetAdventureScriptState()
		{
			return GetAdventureScript()->GetState();
		}
	}

REGISTER_DEV_CMD( clear_adventure_scripts_cache, NCore::AdventureScriptsMachineCmd );

}

#endif //0
