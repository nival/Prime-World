#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "JSONReader.h"
#include "JsonSerializer.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NJson
{
	class CJSONReader;
	class CJSONNode;
}

class SerializationStackElement : public CObjectBase
{
  OBJECT_METHODS( 0xB1B3AA80, SerializationStackElement );

public:
  string key;
  Json::Value value; 
  
  SerializationStackElement() {}
  SerializationStackElement(const string& key_, const Json::Value& value_) : key(key_)
  {
    value = value_;
  }
};

class SerializationStack
{
  typedef list< CObj<SerializationStackElement> > TSerializationStack;
  TSerializationStack stack;

public:

  void Push( const string& key, const Json::Value& jvalue )
  {
    stack.push_back(new SerializationStackElement(key, jvalue));
  }

  void Pop() 
  {
    stack.pop_back();
  }

  SerializationStackElement* Top() const
  {
    return stack.back().GetPtr();
  }

  SerializationStackElement* Bottom() const
  {
    return stack.front().GetPtr();
  }

  void Reset() { stack.clear(); }
  ~SerializationStack() { Reset(); }
  bool Empty() { return stack.empty(); }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class JSONChunkSerializer : public IJsonSerializerBase, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( JSONChunkSerializer, IJsonSerializerBase, BaseObjectMT );

  StrongMT<NJson::CJsonReader> pJsonReader;
  SerializationStack serializationStack;
  
  bool bReading;
  
  bool DataChunk( const string& idChunk, void *pData, int nSize, int nChunkNumber );
	bool DataChunk( const string& idChunk, int *pnData, int nChunkNumber );
	bool DataChunk( const string& idChunk, float *pfData, int nChunkNumber );
	bool DataChunk( const string& idChunk, bool *pData, int nChunkNumber );

  template<class T>
  T Data2Type(Json::Value& data)
  {
    return data.asCString();
  }

  template<class T>
  Json::Value Type2Data(T* pData)
  {
    Json::Value res = *pData;
    return res;
  }


  template <class T>
  bool DataChunkInternal(const string& idChunk, T *pData, int nChunkNumber)
  {
    Json::Value& cur = serializationStack.Top()->value;  
    if ( IsReading() ) 
    {
      Json::Value data;
      if (idChunk.empty())
        data = cur.get(nChunkNumber, Json::nullValue);        
      else
        data = cur[idChunk.c_str()];

      *pData = Data2Type<T>(data);
    }
    else 
    {
      if ( idChunk.empty() )
        cur.append(Type2Data<T>(pData));
      else
        cur[idChunk.c_str()] = Type2Data<T>(pData);
        
    }
    return true;
  }


  #ifdef WIN32	
	  bool DataChunk( const string& idChunk, GUID *pgData, int nChunkNumber );
  #endif	  

	bool DataChunkString( const string& idChunk, string &data, int nChunkNumber = 0 );
	bool DataChunkString( const string& idChunk, wstring &data, int nChunkNumber = 0 );
	
	void Start();
	void Finish();
	
  int CurrentContainerSize() const;
  
  JSONChunkSerializer() : bReading( true ) {	}

  string* pJsonString;
public:
  JSONChunkSerializer( const string& jsonString )	
  : bReading( true )
	{ 
    pJsonString = const_cast<string*>(&jsonString);
    Start();
	}

  JSONChunkSerializer( string& jsonString )	
    : bReading( false )
  { 
    pJsonString = &jsonString;
    Start();
  }
	~JSONChunkSerializer() { Finish(); }

	bool StartChunk( const string& idChunk, int nChunkNumber );
  void FinishChunk();

	bool IsReading() const { return bReading; }
};

template <> inline
bool JSONChunkSerializer::Data2Type<bool>(Json::Value& data)
{
  return data.asBool();
}

template <> inline
float JSONChunkSerializer::Data2Type<float>(Json::Value& data)
{
  return static_cast<float>(data.asDouble());
}

template <> inline
int JSONChunkSerializer::Data2Type<int>(Json::Value& data)
{
  return data.asInt();
}

template <> inline
long JSONChunkSerializer::Data2Type<long>(Json::Value& data)
{
  return data.asInt();
}

template <> inline
signed char JSONChunkSerializer::Data2Type<signed char>(Json::Value& data)
{
  return data.asInt();
}

template <> inline
unsigned int JSONChunkSerializer::Data2Type<unsigned int>(Json::Value& data)
{
  return data.asUInt();
}

template <> inline
unsigned char JSONChunkSerializer::Data2Type<unsigned char>(Json::Value& data)
{
  return data.asUInt();
}

template <> inline
unsigned long JSONChunkSerializer::Data2Type<unsigned long>(Json::Value& data)
{
  return data.asUInt();
}

template <> inline
double JSONChunkSerializer::Data2Type<double>(Json::Value& data)
{
  return data.asDouble();
}


template <> inline
Json::Value JSONChunkSerializer::Type2Data<string>(string* pData)
{
  Json::Value res = pData->c_str();
  return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

