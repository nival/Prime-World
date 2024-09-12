#include "StdAfx.h"

#include "JSONChunkSerializer.h"
#include "JSONReader.h"
#include "../System/Texts.h"

#pragma warning(push)
#pragma warning( disable: 4238)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JSONChunkSerializer::Start()
{
  if ( IsReading() ) 
	{
    pJsonReader = new NJson::CJsonReader( *pJsonString );
    serializationStack.Push( "__root__", *pJsonReader->GetRootElement() );
	}
	else
	{
		/*NI_VERIFY( _pStream->CanWrite(), "Read only stream passed", return );
		pStream = _pStream;*/
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JSONChunkSerializer::Finish()
{
	if ( !IsReading() && !serializationStack.Empty() ) 
	{
		Json::StyledWriter writer;
    *pJsonString = writer.write(serializationStack.Bottom()->value).c_str();

    serializationStack.Reset();
	}

  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::StartChunk( const string& idChunk, int nChunkNumber )
{
  if (IsReading())
  {
    // если в стеке только рут - читаем текущий объект относительно него
    if (idChunk != "__root__") 
    {
      Json::Value& current = serializationStack.Top()->value;
      if (!idChunk.empty())
        serializationStack.Push( idChunk, current[idChunk.c_str()] );
      else
      {
        Json::Value subValue = current.get(nChunkNumber, Json::nullValue);
        if (subValue == Json::nullValue)
          return false;

        serializationStack.Push( idChunk, subValue );
      }
    }
  }
  else
  {
    //current = new Json::Value();
    serializationStack.Push( idChunk, Json::Value() );
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JSONChunkSerializer::FinishChunk()
{
  CObj<SerializationStackElement> cur = serializationStack.Top();
  serializationStack.Pop();
  
  if ( IsReading() )
	{
      
	}
	else
	{
    if (serializationStack.Empty() && cur->key == "__root__")
    {
      serializationStack.Push(cur->key, cur->value);
    }
    else
    {
      SerializationStackElement* last = serializationStack.Top();
      Json::Value& lastNode = last->value;
      if (cur->key.empty())
        lastNode.append(cur->value);
      else
        lastNode[cur->key.c_str()] = cur->value;
    }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunk( const string& idChunk, int *pnData, int nChunkNumber )
{
	return DataChunkInternal(idChunk, pnData, nChunkNumber);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunk( const string& idChunk, float *pfData, int nChunkNumber )
{
	return DataChunkInternal(idChunk, pfData, nChunkNumber);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunk( const string& idChunk, bool *pData, int nChunkNumber )
{
	return DataChunkInternal(idChunk, pData, nChunkNumber);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunk( const string& idChunk, void *pData, int nSize, int nChunkNumber )
{
	string szString;
	if ( IsReading() ) 
	{
		DataChunkString( idChunk, szString, nChunkNumber );
		if ( !szString.empty() )
		{
			NI_ASSERT( szString.size() == nSize * 2, "Wrong bin chunk size" );
			NStr::StringToBin( szString.c_str(), pData, 0 );
		}
		else
			memset( pData, 0, nSize );
	}
	else
	{
		szString.resize( nSize * 2 );
		NStr::BinToString( pData, nSize, &(szString[0]) );
		DataChunkString( idChunk, szString, nChunkNumber );
	}
	
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
bool JSONChunkSerializer::DataChunk( const string& idChunk, GUID *pgData, int nChunkNumber )
{
	bool bRetVal = false;
	string szValue;
	if ( IsReading() )
	{
		if ( DataChunkString(idChunk, szValue) )
		{
			NStr::String2GUID( szValue.c_str(), pgData );
			bRetVal = true;
		}
	}
	else
	{
		NStr::GUID2String( &szValue, *pgData );
		bRetVal = DataChunkString( idChunk, szValue );
	}
	return bRetVal;
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunkString( const string& idChunk, string &data, int nChunkNumber )
{
  return DataChunkInternal(idChunk, &data, nChunkNumber);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JSONChunkSerializer::DataChunkString( const string& idChunk, wstring &data, int nChunkNumber )
{
  string szString;
  if ( IsReading() ) 
  {
    if (!DataChunkString(idChunk, szString, nChunkNumber))
      return false;
      
    NStr::UTF8ToUnicode( &data, szString );
  }
  else
  {
    NStr::UnicodeToUTF8( &szString, data );

    if (!DataChunkString(idChunk, szString, nChunkNumber))
      return false;
  }

	return true;
}

int JSONChunkSerializer::CurrentContainerSize() const
{
  return serializationStack.Top()->value.size();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IJsonSerializerBase *CreateJsonLoader( const string& jsonString )
{
	return new JSONChunkSerializer( jsonString );
}

IJsonSerializerBase *CreateJsonWriter( string& jsonString )
{
  return new JSONChunkSerializer( jsonString );
}

#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_SAVELOAD_CLASS( JSONChunkSerializer );
