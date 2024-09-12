#include "stdafx.h"
#include "LuaConstants.h"
#include "LuaPreprocessor.h"

namespace Lua
{
  LuaSimpleDefine::LuaSimpleDefine(const char* prefix, char const* name, char const* value)
  {
    Lua::LuaPreprocessor::Instance().RegisterConstant(NStr::StrFmt("%s%s", prefix, name), value);
  }

  LuaSimpleDefine::LuaSimpleDefine(const char* prefix, char const* name, int value)
  {
    Lua::LuaPreprocessor::Instance().RegisterConstant(NStr::StrFmt("%s%s", prefix, name), NStr::StrFmt("%i", value));
  }
};