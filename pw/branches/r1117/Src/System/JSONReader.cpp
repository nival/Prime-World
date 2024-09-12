#include "stdafx.h"
#include "JsonReader.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NJson
{
void CJsonReader::Start()
{
	if ( jsonString.empty() )
		return;
	
  bool parsingSuccessful = reader.parse( jsonString.c_str(), rootNode );
  NI_VERIFY( parsingSuccessful, "Cannot parse json buffer", return );
}
CJsonReader::CJsonReader( const string &jsonString ) : jsonString(jsonString)
{
	Start();
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_SAVELOAD_CLASS_NM( CJsonReader, NJson );
