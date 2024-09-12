#include "stdafx.h"
#include "ScriptLog.h"
#include "../System/SystemLog.h"

NLogg::CChannelLogger &GetScriptLog()
{
	static NLogg::CChannelLogger g_scriptLog( "Core" );
	return g_scriptLog;
}
