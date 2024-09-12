#pragma once
#include "System\Crc32Calculator.h"

_interface IPointerHolder;
namespace NCore
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BinStatsCollector : public IStatsCollector
{
public:
  enum InfoType
  {
    Step,
    Data,
    Object,
    StartChunk,
    FinishChunk,
    Pointer,
    StartObject,
    FinishObject,
    CurrentCrcObject,
    InfoType_Count
  };

protected: 
  template<char Type >
  struct Record;

public:
  BinStatsCollector() : buffer( 0 ), buffCurr( 0 ), buffEnd( 0 ), isOverrun(false) { }
  
  void Init( unsigned char* buffer, size_t size, int step );
  void* GetBuffer() const { return buffer; }
  size_t GetLength() const { return buffCurr - buffer; }
  bool IsOverrun() const { return isOverrun; }

  bool IsChecksum() { return true; }

  void OnReset() {}

  bool OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType );
	void OnFinishChunk();
  void OnStorePointer( const IBinSaver::chunk_id idChunk, CObjectBase* object );
  void OnStartObject();
  void OnFinishObject( CObjectBase* object );

  void OnDataChunk( const IBinSaver::chunk_id idChunk, const void* data, int size );
  void OnDataChunk( const string & ) {}
  void OnDataChunk( const wstring & ) {}
  void OnDataChunk( const nstl::fixed_string_base<char> & ) {}
  void OnDataChunk( const nstl::fixed_string_base<wchar_t> & ) {}
  
  template<class TCrc>
  void OnCurrentCrc( const TCrc &crc );
  
  static void writeToFile( const void *buffer, size_t size, Stream &stream );
  static int getStepFromBuffer( const void *buffer );
  static unsigned int getCrcFromBuffer( const void *buffer );
  static void setStepToBuffer( void *buffer, int _step );
  static void setCrcToBuffer( void *buffer, unsigned int _crc );
  
  
private:
  template<char Type> Record<Type>& AppendObject();
  
  template<class Strategy>
  class ObjectsParser;
  
  class WriteObjectsToFile;
  class CollectPointerData;
  class DebugPrintData;
  class LinearizeData;
  
  struct PointerData
  {
    int typeId;
    int worldId;
  };
  
  typedef map<CObjectBase *, PointerData> PointersData;
  typedef vector< char > Buffer;
  typedef vector< Buffer > BuffersStack;
  
private:
  template<class T>
  static void ParseBuff( const char *pBeg, const char *pEnd, T &obj );
  
  template<class T>
  static void ParseBuff( const BuffersStack &buffStack, T &obj );
  
private:
  unsigned char safeBuffer[64];
  unsigned char* buffer;
  unsigned char* buffCurr;
  unsigned char* buffEnd;
  bool isOverrun;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
struct BinStatsCollector::Record<BinStatsCollector::Step>
{
  char type;
  int step;
  unsigned int crc;

  void Set( int _step )
  {
    step = _step;
    crc = 0;
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::Data>
{
  char type;
  IBinSaver::chunk_id idChunk;
  unsigned int crc;

  void Init( const IBinSaver::chunk_id _idChunk )
  {
    idChunk = _idChunk;
  }

  void SetCrc( unsigned int _crc )
  {
    crc = _crc;
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::Object>
{
  //Nothing
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::StartChunk>
{
  char type;
  IBinSaver::chunk_id idChunk;
  int chunkType;

  void Set( const IBinSaver::chunk_id _idChunk, int _chunkType )
  {
    idChunk = _idChunk;
    chunkType = _chunkType;
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::FinishChunk>
{
  char type;
  char padding[3];

  void Set()
  {
    //Nothing
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::Pointer>
{
  char type;
  IBinSaver::chunk_id idChunk;
  CObjectBase *pointer;

  void Set( const IBinSaver::chunk_id _idChunk, CObjectBase *_pointer )
  {
    idChunk = _idChunk;
    pointer = _pointer;
  }
};


template<>
struct BinStatsCollector::Record<BinStatsCollector::StartObject>
{
  char type;
  char padding[3];

  void Set()
  {
    //Nothing
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::FinishObject>
{
  char type; 
  int typeId;
  CObjectBase *pointer; 

  void Set( CObjectBase *_pointer, int _typeId )
  {
    typeId = _typeId;
    pointer = _pointer;
  }
};

template<>
struct BinStatsCollector::Record<BinStatsCollector::CurrentCrcObject>
{
  char type; 
  unsigned int crc;

  void SetCrc( unsigned int _crc )
  {
    crc = _crc;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<char Type>
BinStatsCollector::Record<Type>& BinStatsCollector::AppendObject()
{
  typedef Record<Type> CurT;

  NI_STATIC_ASSERT( sizeof(CurT) % 4 == 0, AlignmentFailure );
  NI_STATIC_ASSERT( sizeof(CurT) <= sizeof(safeBuffer), IncreaseSizeOfSafeBuffer );
  
  CurT *pResult;
  unsigned char * const nextCurr = buffCurr + sizeof( CurT );

  if( nextCurr <= buffEnd )
  {
    pResult = static_cast<CurT *>( static_cast<void *>(buffCurr) );
    buffCurr = nextCurr;
  }
  else
  {
    NI_VERIFY( isOverrun, "Crc buffer overrun!", isOverrun = true; );
    pResult = static_cast<CurT *>( static_cast<void *>(safeBuffer) );
    buffCurr = buffEnd;
  }
  
  pResult->type = Type;
  return *pResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool BinStatsCollector::OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType )
{
  AppendObject<StartChunk>().Set( idChunk, chunkType );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BinStatsCollector::OnFinishChunk()
{
  AppendObject<FinishChunk>().Set();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BinStatsCollector::OnStorePointer( const IBinSaver::chunk_id idChunk, CObjectBase* object )
{
  AppendObject<Pointer>().Set(idChunk, object);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BinStatsCollector::OnStartObject()
{
  AppendObject<StartObject>().Set();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BinStatsCollector::OnFinishObject( CObjectBase* object )
{
  AppendObject<FinishObject>().Set( object, object != 0 ? object->GetTypeId() : -1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class TCrc>
inline void BinStatsCollector::OnCurrentCrc( const TCrc &crc )
{
#if 0
  AppendObject<CurrentCrcObject>().SetCrc( crc.Get() );
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BinStatsCollector::OnDataChunk( const IBinSaver::chunk_id idChunk, const void* pData, int nSize )
{
  Record<Data> &dr = AppendObject<Data>();

  dr.Init( idChunk );

  switch ( nSize )
  {
  case 0: case 1:
    dr.SetCrc( *static_cast<const BYTE*>( pData ) );
    break;

  case 2: case 3:
    dr.SetCrc( *static_cast<const WORD*>( pData ) );
    break;

  case 4:
    dr.SetCrc( *static_cast<const DWORD*>( pData ) );
    break;

  //Гипотетически здесь можно записать текущее значение CRC 
  //и ничего дополнительно не вычислять, но тогда разность CRC распространится на 
  //все последующие после и понять где именно было расхождение будет сложнее
  default:
    dr.SetCrc( Crc32ChecksumFast::CalcForSmallLength((const unsigned char*)pData, nSize) );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace NCore