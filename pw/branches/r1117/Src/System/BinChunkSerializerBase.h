#pragma once

class BinChunkSaverBase : public IBinSaver
{
  OBJECT_ABSTRACT_METHODS( BinChunkSaverBase );

protected:
  struct CChunkLevel
  {
    chunk_id idChunk, idLastChunk;
    int nStart, nLength;
    int nLastPos, nLastNumber;

    void ClearCache();
    void Clear();
    CChunkLevel() { Clear(); }
  };

  typedef unsigned char TByte;

  enum
  {
    Ptr_InvalidCObj = 0,
    Ptr_ValidCObj   = 1,
    Ptr_StrongST    = 2,
    Ptr_StrongMT    = 3
  };

  typedef list<CChunkLevel> TChunks;
  typedef list<CChunkLevel>::iterator TChunksIterator;

  Stream * pResult;
  // objects descriptors
  MemoryStream obj;
  // objects data
  MemoryStream data;
  TChunks chunks;

  void ClearBase();

	bool ReadShortChunk( const CChunkLevel &src, int &nPos, CChunkLevel *pResult );
	int CountShortChunks( const CChunkLevel &src, chunk_id dwID );
	virtual int CountChunks( const chunk_id idChunk );

public:
  BinChunkSaverBase() : pResult( 0 ) {}

  BinChunkSaverBase( Stream * _pResult ) : pResult( _pResult )
  {
  }

  ~BinChunkSaverBase() {}

  Stream * GetStream() { return pResult; }
};
