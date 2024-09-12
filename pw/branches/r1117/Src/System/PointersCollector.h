#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PointersCollector : public IBinSaver
{
	OBJECT_METHODS( 0x1E4A8B43, PointersCollector );
	vector<CObjectBase*> *pObjects;

	virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber ) { return true;}
	virtual void FinishChunk() {}
	virtual int CountChunks( const chunk_id idChunk ){ return 0; }

	virtual void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber ){}
	virtual void DataChunkString( string &data ) {}
	virtual void DataChunkString( wstring &data ) {}
	// storing/loading pointers to objects
	virtual void StoreObject( CObjectBase *pObject )
	{
		if ( pObjects )
			pObjects->push_back( pObject );
	}
	virtual CObjectBase* LoadObject() { return 0; }
public:
	virtual bool IsReading() { return false; }
	PointersCollector() : pObjects(0) {}
	PointersCollector( vector<CObjectBase*> *_pObjects ) 
		: pObjects(_pObjects) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
