#include "stdafx.h"
#include "ChunklessSaver.h"

#include <System/ported/cwfn.h>

class CTextDumpSerializer : public IBinSaver
{
	OBJECT_METHODS(0x1E4A8B20,CTextDumpSerializer);
	CPtr<IPointerHolder> pTracker;
	FILE *pLog;
	int nChunkLevel;

	void LogChunckLevel()
	{
		if ( !pLog )
			return;
		for ( int i = 0; i < nChunkLevel; ++i )
			fprintf( pLog, "\t" );
	}

	virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber, int )
	{
		if ( pLog )
		{
			LogChunckLevel();
			fprintf( pLog, "chunk %d:\n", idChunk );
			LogChunckLevel();
			fprintf( pLog, "{\n", idChunk );
		}
		++nChunkLevel;
		return true;
	}
	virtual void FinishChunk()
	{
		--nChunkLevel;
		nChunkLevel = max( 0, nChunkLevel );

		LogChunckLevel();
		if ( pLog )
			fprintf( pLog, "}\n" );
	}

	virtual int CountChunks( const chunk_id idChunk )
	{
		NI_ASSERT(0, "CTextDumpSerializer: function not supported");
		return 0;
	}
	virtual void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
	{
		if ( !pLog )
			return;

		LogChunckLevel();
		fprintf( pLog, "chunk %d: ", idChunk );
		for ( int k = 0; k < nSize; ++k )
		{
			const int data = ((const unsigned char*)pData)[ k ];
			fprintf( pLog, "%02x ", data );
		}
		fprintf( pLog, "\n" );
	}
	virtual void DataChunkString( string &data )
	{
		if ( !pLog )
			return;

		LogChunckLevel();
		fprintf( pLog, ">>>%s<<<\n", data.c_str() );
	}
	virtual void DataChunkString( wstring &data )
	{
		if ( !pLog )
			return;

		LogChunckLevel();
		fwprintf( pLog, L">>>%s<<<\n", data.c_str() );
	}

  virtual void DataChunkString( nstl::fixed_string_base<char> &data )
  {
    if ( !pLog )
      return;

    LogChunckLevel();
    fprintf( pLog, ">>>%s<<<\n", data.GetData() );
  }

  virtual void DataChunkString( nstl::fixed_string_base<wchar_t> &data )
  {
    if ( !pLog )
      return;

    LogChunckLevel();
    fwprintf( pLog, L">>>%s<<<\n", data.GetData() );
  }


	// storing/loading pointers to objects
	virtual void StoreObject( CObjectBase *pObject )
	{
		if ( !pLog )
			return;

		NI_VERIFY( IsValid(pTracker), "Version tracker must be valid",	return );
		const int nID = pTracker->GetObjectID( pObject );
		LogChunckLevel();
		fprintf( pLog, "Pointer to object %d.\n", nID );
	}

	virtual CObjectBase* LoadObject()
	{
		NI_ASSERT(0, "CTextDumpSerializer: function not supported");
		return 0;
	}

  virtual void StoreObjectST( BaseObjectST * object )
  {
    NI_ALWAYS_ASSERT( "Not implemented" );
  }

	virtual BaseObjectST * LoadObjectST()
  {
    NI_ALWAYS_ASSERT( "Not implemented" );
    return 0;
  }

  virtual void StoreObjectMT( BaseObjectMT * pObject )
  {
    NI_ALWAYS_ASSERT( "Not implemented" );
  }

	virtual BaseObjectMT * LoadObjectMT()
  {
    NI_ALWAYS_ASSERT( "Not implemented" );
    return 0;
  }

public:
	virtual bool IsReading() { return false; }
	virtual int GetVersion() const { return 4; }
  Stream* GetStream() { return 0; }

	CTextDumpSerializer() : pLog(0), nChunkLevel(0) {}
	CTextDumpSerializer( IPointerHolder *_pTracker, FILE *_pLog ) 
		: pTracker(_pTracker), pLog(_pLog), nChunkLevel(0) {}
};


IBinSaver *CreateTextDumpSaver( IPointerHolder *pPtr, FILE *pLog )
{
	return new CTextDumpSerializer( pPtr, pLog );
}

void DumpObjectContents( const char *logName, IPointerHolder *pTracker, CObjectBase *pObject )
{
#ifndef _SHIPPING
	FILE *pLog;
	fopen_s( &pLog, logName, "wt" );

	fprintf( pLog, "Object %s\n", pObject->GetObjectTypeName() );
	{
		CPtr<IBinSaver> pSaver = CreateTextDumpSaver( pTracker, pLog );
		pObject->operator&( *pSaver );
	}

	fclose ( pLog );
#endif
}


