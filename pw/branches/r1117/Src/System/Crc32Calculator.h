#pragma once
#ifndef CRC32CALCULATOR_H_38DCEC19_7286
#define CRC32CALCULATOR_H_38DCEC19_7286

#include "Basic.h"
#include "BinSaver.h"
#include "Crc32Checksum.h"
#include "nqueue.h"
#include "InlineProfiler.h"
#include "Crc32ChecksumFast.h"
#include "Crc32ChecksumCopy.h"

class IStatsCollector
{
public:
  virtual void Init( unsigned char* buffer, size_t size, int step ) = 0;
  virtual size_t GetLength() const = 0;
};

class ICrcCalculator : public IBinSaver
{
public:
  virtual IStatsCollector& GetStatsCollector() = 0;
  virtual const IStatsCollector& GetStatsCollector() const = 0;
  virtual void BeginCalculate( bool reset ) = 0;
  virtual unsigned int EndCalculate() = 0;
  virtual unsigned int GetBytesHashed() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TStatsCollector>
class Crc32Calculator : public ICrcCalculator
{
	OBJECT_BASIC_METHODS( Crc32Calculator )

  void BeforeCalculate()
	{
    ++marker;
    if ( marker == 0 )
      marker = 1;
	}

	void SerializeObjects()
	{
		while ( !storedObjects.empty() )
		{
		  statsCollector.OnCurrentCrc(crc);
      CObjectBase * const pObject = storedObjects.back();
			storedObjects.pop_back();
			
			statsCollector.OnStartObject();
			AddPolymorphicBaseWithoutChunks( pObject );
			statsCollector.OnFinishObject( pObject );
			statsCollector.OnCurrentCrc(crc);
		}
	}

protected:
	virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber, int chunkType )
	{
	  statsCollector.OnCurrentCrc(crc);
    return statsCollector.OnStartChunk( idChunk, chunkType );
	}

	virtual void FinishChunk()
	{
    statsCollector.OnFinishChunk();
    statsCollector.OnCurrentCrc(crc);
	}

  virtual void DataChunkString( string &data )
	{
		crc.Add( (const unsigned char*)data.c_str(), data.size() );
    statsCollector.OnDataChunk( data );
	}

	virtual void DataChunkString( wstring &data )
	{
		crc.Add( (const unsigned char*)data.c_str(), 2 * data.size() );
    statsCollector.OnDataChunk( data );
	}

  virtual void DataChunkString( nstl::fixed_string_base<char> &data )
  {
    crc.Add( reinterpret_cast<const unsigned char*>(data.GetData()), data.GetStorageSize() );
    statsCollector.OnDataChunk( data );
  }

  virtual void DataChunkString( nstl::fixed_string_base<wchar_t> &data )
  {
    crc.Add( reinterpret_cast<const unsigned char*>(data.GetData()), data.GetStorageSize() );
    statsCollector.OnDataChunk( data );
  }

	virtual void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
	{
		crc.Add( (const unsigned char*)pData, nSize );
    statsCollector.OnDataChunk( idChunk, pData, nSize );
	}
	
  virtual void DataChunk_1( const chunk_id idChunk, void *pData, int nChunkNumber )
  {
    crc.AddKnownSize<1>( (const unsigned char*)pData );
    statsCollector.OnDataChunk( idChunk, pData, 1 );
  }

  virtual void DataChunk_4( const chunk_id idChunk, void *pData, int nChunkNumber )
  {
    crc.AddKnownSize<4>( (const unsigned char*)pData );
    statsCollector.OnDataChunk( idChunk, pData, 4 );
  }

  virtual void StoreObject( CObjectBase *pObject ) {  NI_ALWAYS_ASSERT( "Crc32Calculator doesn't implement StoreObject( CObjectBase *pObject )" ); }
  
  virtual void StoreObject( const chunk_id idChunk, CObjectBase *pObject )
	{
	  statsCollector.OnCurrentCrc(crc);
    statsCollector.OnStorePointer( idChunk, pObject );
    
    if ( !IsValid( pObject ) || pObject->GetCRCMark() == marker )
      return;

    pObject->SetCrcMark( marker );
    
    const bool needCallSerialize = storedObjects.empty();
    storedObjects.push_back( pObject );
    
    #if !defined(BIN_SAVER_USE_PROFILER)
      if( needCallSerialize )
        SerializeObjects();
    #else
      (void) needCallSerialize;
    #endif
	}

  virtual int CountChunks( const chunk_id idChunk ) { NI_ALWAYS_ASSERT( "Crc32Calculator doesn't implement CountChunks" ); return 0; }
	virtual CObjectBase* LoadObject() { NI_ALWAYS_ASSERT( "Crc32Calculator doesn't implement LoadObject" ); return 0; }

  virtual void StoreObject2( SerializableBase * pObject ) { NI_ALWAYS_ASSERT( "Not implemented" ); }
  virtual SerializableBase * LoadObject2() { NI_ALWAYS_ASSERT( "Not implemented" ); return 0; }

  virtual void StoreObjectST( BaseObjectST * pObject ) { NI_ALWAYS_ASSERT( "Not implemented" ); }
	virtual BaseObjectST * LoadObjectST() { NI_ALWAYS_ASSERT( "Not implemented" ); return 0; }
  virtual void StoreObjectMT( BaseObjectMT * pObject ) { NI_ALWAYS_ASSERT( "Not implemented" ); }
	virtual BaseObjectMT * LoadObjectMT() { NI_ALWAYS_ASSERT( "Not implemented" ); return 0; }

  virtual bool IsReading() { return false; }
	virtual bool IsChecksum() { return statsCollector.IsChecksum(); }

public:
  Crc32Calculator() : calculate( false ), marker( 0 ) {}

	template<class T>
  void Calculate( T* object, bool reset )
  {
    if ( reset )
      Reset();
    if ( !calculate )
      BeforeCalculate();
    Add( 1, object, 1 );
    if ( !calculate )
      SerializeObjects();
  }

  template<class T>
  void Calculate( T& object, bool reset )
  {
    if ( reset )
      Reset();
    if ( !calculate )
      BeforeCalculate();
    Add( 1, &object, 1 );
    if ( !calculate )
      SerializeObjects();
      
  }

  void BeginCalculate( bool reset )
	{
		if ( reset )
			Reset();
		BeforeCalculate();
		calculate = true;
	}

  unsigned int EndCalculate()
	{
	  //NI_PROFILE_FUNCTION
	
		calculate = false;
		SerializeObjects();
		return crc.Get();
	}

  unsigned int GetCrc() { return crc.Get(); }

  void Reset() { crc.Reset(); statsCollector.OnReset(); StatisticReset(); }

  IStatsCollector& GetStatsCollector() { return statsCollector; }
  const IStatsCollector& GetStatsCollector() const { return statsCollector; }
  Stream* GetStream() { return 0; }
  
  unsigned int GetBytesHashed() const { return 0 /*crc.GetBytesHashed()*/; }

private:
  class Crc32Statistics;
  class Crc32NullStatistics;
 
 #if !defined(_SHIPPING) && 0
  Crc32ChecksumBase<Crc32Statistics> crc;
 #elif !defined(_SHIPPING) && 0
  Crc32ChecksumCopy crc;
 #else
  //Crc32ChecksumBaseFast<Crc32NullStatistics> crc;
  Crc32ChecksumFast crc;
 #endif

  bool calculate;
  vector<CObjectBase*> storedObjects;
  int marker;

  TStatsCollector statsCollector;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NullStatsCollector : public IStatsCollector
{
public:
  bool IsChecksum() { return true; }

  void OnReset() {}

  bool OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType ) { return true; }
	void OnFinishChunk() {}
  void OnStorePointer( const IBinSaver::chunk_id idChunk, CObjectBase* pObject ) {}
  void OnStartObject() {}
  void OnFinishObject( CObjectBase* pObject ) {}

  void OnDataChunk( const IBinSaver::chunk_id, const void* pData, int nSize ) {}
  void OnDataChunk( const string& data ) {}
  void OnDataChunk( const wstring& data ) {}
  
  template<class TCrc>
  void OnCurrentCrc( const TCrc &crc ) {}

  virtual void Init( unsigned char* buffer, size_t size, int step ) {};
  virtual size_t GetLength() const { return 0; };
};

template < typename TStatsCollector >
class Crc32Calculator<TStatsCollector>::Crc32Statistics 
{
protected:
  void Reset() { curBytes = 0; }
  void HashByte() { ++curBytes; }
  
public:
  unsigned int GetBytesHashed() const { return curBytes; }
  
private:
  unsigned int curBytes;
};

template < typename TStatsCollector >
class Crc32Calculator<TStatsCollector>::Crc32NullStatistics 
{
protected:
  static void Reset() {}
  static void HashByte() {}

public:
  unsigned int GetBytesHashed() const { return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define CRC32CALCULATOR_H_38DCEC19_7286
