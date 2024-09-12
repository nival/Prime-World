#ifndef CHUNKLESS_SAVER_H_
#define CHUNKLESS_SAVER_H_

#include "stdafx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IPointerHolder : public IObjectBase
{
	virtual int GetObjectID( CObjectBase *p ) = 0;
	virtual CObjectBase *GetObject( int nID ) = 0;

  virtual int GetObjectIdST( BaseObjectST * object ) = 0;
  virtual BaseObjectST * GetObjectST( int id ) = 0;
  virtual int GetObjectIdMT( BaseObjectMT * pObject ) = 0;
	virtual BaseObjectMT * GetObjectMT( int id ) = 0;

  ZDATA
  ZNOPARENT(IObjectBase)
public:
  ZEND int operator&( IBinSaver &f ) { return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Stream;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// uses the fact that order of chunks during save and during load is the same
// also requires no countchunks() use
class ChunklessSaver : public IBinSaver
{
  OBJECT_BASIC_METHODS( ChunklessSaver );

  CPtr<IPointerHolder> pPointerHolder;
  Stream *pResult;
  bool reading;

  void CheckChunk( const chunk_id idChunk, int nChunkNumber );
  virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber, int )
  {
    CheckChunk( idChunk, nChunkNumber );
    return true;
  }
  virtual void FinishChunk()
  {
    CheckChunk( 0, -1 );
  }
  virtual int CountChunks( const chunk_id idChunk )
  {
    ASSERT(0);
    return 0;
  }

  virtual void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber );
  virtual void DataChunkString( string &data );
  virtual void DataChunkString( wstring &data );
  virtual void DataChunkString( nstl::fixed_string_base<char> &data );
  virtual void DataChunkString( nstl::fixed_string_base<wchar_t> &data );
  // storing/loading pointers to objects
  virtual void StoreObject( CObjectBase *pObject );
  virtual CObjectBase* LoadObject();

  virtual void StoreObjectST( BaseObjectST * object );
  virtual BaseObjectST * LoadObjectST();
  virtual void StoreObjectMT( BaseObjectMT * pObject );
	virtual BaseObjectMT * LoadObjectMT();

  ChunklessSaver() : pResult(0) {}

public:
  virtual bool IsReading() { return reading; }
  virtual void Reset( Stream* data, bool isReading ) 
  {
    pResult = data;
    reading = isReading;
  } 

  ChunklessSaver( Stream *_pResult, IPointerHolder *_pPointerHolder, bool _reading, uint containerSizeLimit = 0, uint totalSizeLimit = 0) 
    : IBinSaver( containerSizeLimit, totalSizeLimit )
    , pPointerHolder( _pPointerHolder )
    , pResult( _pResult )
    , reading( _reading )
  {
  }
  Stream* GetStream() { return pResult; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBinSaver *CreateChunklessSaver( Stream *pStream, IPointerHolder *pPointerHolder, const bool reading, uint containerSizeLimit = 0, uint totalSizeLimit = 0 );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

