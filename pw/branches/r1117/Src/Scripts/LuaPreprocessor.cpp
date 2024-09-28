#include "stdafx.h"
#include "LuaPreprocessor.h"

namespace 
{
  char const* const delimiters = " \n\r[](),;{}:.<>!=+-/*";
  char const* const skipped    = " \n\r";
}

namespace Lua
{

LuaPreprocessor::LuaPreprocessor()
{
}

LuaPreprocessor& LuaPreprocessor::Instance()
{
  static LuaPreprocessor theInstance;
  return theInstance;
}

bool LuaPreprocessor::RegisterConstant(char const* name, char const* value)
{
  if( constants.end() != constants.find(name) )
  {
    systemLog(NLogg::LEVEL_ASSERT) << "Lua constant <" << name << "> is already defined!" << endl;
    return false;
  }

  constants[name] = value;
  return true;
}

bool LuaPreprocessor::Preprocess(string& result, char const* data, const int size)
{
  if( NULL == data )
  {
    NI_ALWAYS_ASSERT("Missing input data!");
    return false;
  } 

  string buffer(data, data + size);
  result.reserve(size);

  TConstants::const_iterator end = constants.end();
  for(size_t cur = 0; cur != string::npos;)
  {
    size_t pos   = buffer.find_first_of(delimiters, cur);
    string token = buffer.substr(cur, max<size_t>(pos - cur, 1));

    TConstants::const_iterator it = constants.find(token);
    result += end != it ? it->second : token;
    cur     = min<size_t>( pos + (cur == pos), string::npos);
  }
  
  return true;
}





}