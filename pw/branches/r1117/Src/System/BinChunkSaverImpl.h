#pragma once

#include "BinChunkSerializerBase.h"


class BinChunkSaverImpl : public BinChunkSaverBase
{
  OBJECT_METHODS( 0x1E4A8B49, BinChunkSaverImpl );

private:
  //TEMP: temporary objects
  struct SObjectToStore
  {
    TByte               type;
    CObjectBase *       cobj;
    BaseObjectST *      baseSt;
    BaseObjectMT *      baseMt;
    SObjectToStore() : type( 0 ), cobj( 0 ), baseSt( 0 ), baseMt( 0 ) {}
  };

  list<SObjectToStore> toStore;

  typedef hash_set<void*>  TStoredObjects;
  TStoredObjects storedObjects;

  int version;

  bool WriteShortChunk( CChunkLevel *pDest, chunk_id dwID, const void *pData, const int nLength );
  //
  bool StartChunk( const chunk_id idChunk, int nChunkNumber, int );
  void FinishChunk();
  void AlignDataFileSize();
  int CountChunks( const chunk_id idChunk );
  //
  void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber );
  void RawData( void *pData, int nSize );
  void WriteRawData( const void *pData, int nSize );
  void DataChunkString( string &str );
  void DataChunkString( wstring &str );
  virtual void DataChunkString( nstl::fixed_string_base<char> &str );
  virtual void DataChunkString( nstl::fixed_string_base<wchar_t> &str );
  // storing/loading pointers to objects
  virtual void StoreObject( CObjectBase * pObject );
  virtual CObjectBase * LoadObject();

  virtual void StoreObjectST( BaseObjectST * object );
  virtual BaseObjectST * LoadObjectST();
  virtual void StoreObjectMT( BaseObjectMT * pObject );
	virtual BaseObjectMT * LoadObjectMT();
  //
  void Start();
  void Finish();

  bool IsReading() { return false; }

public:
  BinChunkSaverImpl() : version( 0 ) {}

  BinChunkSaverImpl( Stream * _pResult, const int _version ) :
  BinChunkSaverBase( _pResult ), version( _version )
  {
    Start(); 
  }

  ~BinChunkSaverImpl() { Finish(); }
};
