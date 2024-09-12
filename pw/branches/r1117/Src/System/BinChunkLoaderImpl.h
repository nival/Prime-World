#pragma once

#include "BinChunkSerializerBase.h"

_interface IProgressHook;

class BinChunkLoaderImpl : public BinChunkSaverBase
{
  OBJECT_METHODS( 0xC57BD480, BinChunkLoaderImpl );

private:
  struct SObjectToRestore
  {
    CObj<CObjectBase>   cobj;
    Strong<BaseObjectST> baseSt;
    StrongMT<BaseObjectMT> baseMt;
    SObjectToRestore() {}
  };

  // maps objects addresses during save(first) to addresses during load(second) - during loading
  // or serves as a sign that some object has been already stored - during storing
  typedef hash_map< void*, SObjectToRestore > TObjectsToRestore;
  TObjectsToRestore objectsToRestore;
	int version;

  CPtr<IProgressHook> pProgress;
  int nStepSize;
  int nLastStep;

  bool GetShortChunk( CChunkLevel *pSrc, chunk_id dwID, CChunkLevel *pResult, int nNumber );

  bool GetShortChunkSave( Stream *pFile, chunk_id dwID, MemoryStream *pChunk, int baseSeek );
  bool ReadShortChunkSave( Stream *pFile, chunk_id &dwID, MemoryStream *pChunk );
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

  bool IsReading() { return true; }

public:
  BinChunkLoaderImpl() : version( 0 ) {}

  BinChunkLoaderImpl( Stream * _pResult, IProgressHook *_pProgress ) :
  BinChunkSaverBase( _pResult ),
  version( 0 ),
  pProgress( _pProgress )
  {
    Start(); 
  }

  ~BinChunkLoaderImpl() { Finish(); }
};
