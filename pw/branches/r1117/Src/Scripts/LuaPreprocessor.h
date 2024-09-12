#pragma once

namespace Lua
{

class LuaPreprocessor
{
  typedef hash_map<string, string> TConstants;
  TConstants constants;

  LuaPreprocessor();
  LuaPreprocessor(LuaPreprocessor const&);
  LuaPreprocessor& operator = (LuaPreprocessor const&);
public:
  
  static LuaPreprocessor& Instance();

  bool RegisterConstant(char const* name, char const* value);
  bool Preprocess(string& result, char const* data, const int size);
};

}