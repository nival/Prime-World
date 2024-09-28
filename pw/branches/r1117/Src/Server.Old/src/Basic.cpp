
#include "TypeProxy.h"
#include <typeinfo>
#include <string.h>
#include <memory.h>
#include "../../System/nvector.h"
#include "../../System/nstring.h"
#include "../../System/nlist.h"
#include "../../System/basic.h"
using namespace nstl;
#include "../../System/StrProc.h"
#include "../../System/Logger.h"
#include "../../System/LoggerStream.h"
#include "../../System/SystemLog.h"


#ifdef TRACK_OBJECTS_STATISTICS
#include "ChunklessSaver.h"
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool bDestroyInProgress = false;
static list<CObjectBase*> *pObjectsToDestroy = 0;
static list<CObjectBase*> *pObjectsToInvalidate = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////
inline static list<CObjectBase*>& GetObjectsToDestroy()
{
	if ( !pObjectsToDestroy )
		pObjectsToDestroy = new list<CObjectBase*>;
	return *pObjectsToDestroy;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline static list<CObjectBase*>& GetObjectsToInvalidate()
{
	if ( !pObjectsToInvalidate )
		pObjectsToInvalidate = new list<CObjectBase*>;
	return *pObjectsToInvalidate;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void FreeLists()
{
	if ( pObjectsToDestroy && pObjectsToDestroy->empty() )
	{
		delete pObjectsToDestroy;
		pObjectsToDestroy = 0;
	}
	if ( pObjectsToInvalidate && pObjectsToInvalidate->empty() )
	{
		delete pObjectsToInvalidate;
		pObjectsToInvalidate = 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct FreeListsHelper
{
private:
	bool isRunning;
public:
	FreeListsHelper() : isRunning( true ) {}
	~FreeListsHelper() { isRunning = false; FreeLists(); }

	void TryFreeLists() { if ( !isRunning ) FreeLists(); }
} freeListsHelper;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DestroyDelayed()
{
	while ( !GetObjectsToDestroy().empty() || !GetObjectsToInvalidate().empty() )
	{
		while ( !GetObjectsToDestroy().empty() )
		{
			CObjectBase *pObject = GetObjectsToDestroy().front();
			GetObjectsToDestroy().pop_front();
			pObject->DeleteThis();
		}
		while ( !GetObjectsToInvalidate().empty() )
		{
			CObjectBase *pObject = GetObjectsToInvalidate().front();
			GetObjectsToInvalidate().pop_front();
			pObject->DestroyContents();
			CObjectBase::SRefCounter::ReleaseRef( pObject );
		}
	}
	bDestroyInProgress = false;
	freeListsHelper.TryFreeLists();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseRef()
{
	DecRef();
	if ( nRefCount == 0 && ( nObjCount & ~INVALID_REF_MASK ) == 0 )
		ReleaseComplete();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseObj()
{
	DecObj();
	if ( ( nObjCount & ~INVALID_REF_MASK ) == 0 )
	{
		if ( nRefCount == 0 )
			ReleaseComplete();
		else
			ReleaseInvalid();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseComplete()
{
	if ( bDestroyInProgress )
		GetObjectsToDestroy().push_back( this );
	else
	{
		bDestroyInProgress = true;
		DeleteThis();
		DestroyDelayed();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseInvalid()
{
	nObjCount |= INVALID_REF_MASK;
	if ( bDestroyInProgress )
	{
		AddRef();
		GetObjectsToInvalidate().push_back( this );
	}
	else
	{
		AddRef();
		bDestroyInProgress = true;
		DestroyContents();
		ReleaseRef();
		DestroyDelayed();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TRACK_OBJECTS_STATISTICS
////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSimplePointerHash
{
	template <class T> 
	int operator()( T *p ) const { return (int)p; }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
hash_set<CObjectBase *, SSimplePointerHash > *pObjectsSet; // do not initialize!
////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterInObjectsSet( CObjectBase *pObject )
{
	if ( pObjectsSet == 0 )
		pObjectsSet = new hash_set<CObjectBase *, SSimplePointerHash >;

	pObjectsSet->insert( pObject );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void UnRegisterInObjectsSet( CObjectBase *pObject )
{
	pObjectsSet->erase( pObject );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
struct STypeStats
{
	int nObjectsNumber;
	int nValidsNumber;
	int nInvalidsNumber;
	int nSizeOf;
	int nSerializeSize;

	STypeStats() :
	nObjectsNumber( 0 ),
		nValidsNumber( 0 ),
		nInvalidsNumber( 0 ),
		nSizeOf( 0 ),
		nSerializeSize( 0 )
	{}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
struct STypeStatsComparer
{
	bool operator()( const pair<string, STypeStats> &left, pair<string, STypeStats> &right ) const
	{
		return left.first < right.first;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CTrivialPointerSerialization: public IPointerHolder, public CObjectBase
{
	OBJECT_BASIC_METHODS(CTrivialPointerSerialization);

	virtual int GetObjectID( CObjectBase *p )
	{
		return (int)p;
	}

	virtual CObjectBase *GetObject( int nID )
	{
		return (CObjectBase *)nID;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
static void CollectObjectsStatistics( hash_map< string, STypeStats > *pTypesMap )
{
	ASSERT( pTypesMap != 0 );
	hash_map< string, STypeStats > &typesMap = *pTypesMap;

	CObj<MemoryStream> pMemoryStream = new MemoryStream();
	int nStreamSize = pMemoryStream->GetSize();
	CPtr<CTrivialPointerSerialization> pPointerSerialization = new CTrivialPointerSerialization();
	CPtr<IBinSaver> pSaver = CreateChunklessSaver( pMemoryStream, pPointerSerialization, false );

	for ( hash_set<CObjectBase *, SSimplePointerHash >::iterator it = pObjectsSet->begin(); it != pObjectsSet->end(); ++it )
	{
		CObjectBase *pObject = *it;
		const char *szTypeName = pObject->GetObjectTypeName();
		STypeStats &typeStats = typesMap[szTypeName];

		++typeStats.nObjectsNumber;
		typeStats.nSizeOf = pObject->GetSizeOf();

		if ( IsValid( pObject ) )
			++typeStats.nValidsNumber;
		else
			++typeStats.nInvalidsNumber;

		pObject->operator&( *pSaver );
		int nNewStreamSize = pMemoryStream->GetSize();
		ASSERT( nNewStreamSize >= nStreamSize );
		typeStats.nSerializeSize += nNewStreamSize - nStreamSize;
		nStreamSize = nNewStreamSize;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintObjectsStatistics( bool toFile )
{
	SYSTEMTIME localTime;
	GetLocalTime( &localTime );
	char dumpFileName[256];
	sprintf_s( dumpFileName, "ObjectsStatistics-%04d%02d%02d-%02d%02d%02d.tsv"
		, localTime.wYear	, localTime.wMonth, localTime.wDay
		, localTime.wHour, localTime.wMinute, localTime.wSecond );

	hash_map< string, STypeStats > typesMap;
	CollectObjectsStatistics( &typesMap );

	vector< pair<string, STypeStats> > statistics;
	statistics.reserve( typesMap.size() );
	for ( hash_map< string, STypeStats >::iterator it = typesMap.begin(); it != typesMap.end(); ++it )
	{
		statistics.push_back( pair<string, STypeStats>( it->first.data(), it->second ) );
	}
	typesMap.clear();

	sort( statistics.begin(), statistics.end(), STypeStatsComparer() );

	FILE *dumpFile = 0;
	if ( toFile )
	{
		fopen_s( &dumpFile, dumpFileName, "w" );
		if ( !dumpFile )
		{
			OutputDebugString( "Warning: Cannot dump objects statistics to file. Dumping to debug output.\n" ); 
			toFile = false;
		}
	}

	if ( dumpFile )
		fprintf( dumpFile, "type name\tobjects number\tvalid\tinvalid\tsizeof\tsizeof*number\tserialize size\n" );
	else
		OutputDebugString( "type name\tobjects number\tvalid\tinvalid\tsizeof\tsizeof*number\tserialize size\n" );
		
	char szBuf[1024];
	int nTotalObjects = 0;
	int nTotalValidsNumber = 0;
	int nTotalInvalidsNumber = 0;
	int nTotalSizeOf = 0;
	int nTotalSerializeSize = 0;
	for ( int i = 0; i < statistics.size(); ++i )
	{
		const pair<string, STypeStats> &tmp = statistics[i];
		const STypeStats &stats = tmp.second;
		const int nNumberXSizeOf = stats.nObjectsNumber*stats.nSizeOf;
		if ( dumpFile )
			fprintf( dumpFile, "%s\t%d\t%d\t%d\t%d\t%d\t%d\n", tmp.first.data(), stats.nObjectsNumber, stats.nValidsNumber, stats.nInvalidsNumber, stats.nSizeOf, nNumberXSizeOf, stats.nSerializeSize );
		else
		{
			sprintf_s( szBuf, 1024, "%s\t%d\t%d\t%d\t%d\t%d\t%d\n", tmp.first.data(), stats.nObjectsNumber, stats.nValidsNumber, stats.nInvalidsNumber, stats.nSizeOf, nNumberXSizeOf, stats.nSerializeSize );
			OutputDebugString( szBuf );
		}
		nTotalObjects += stats.nObjectsNumber;
		nTotalValidsNumber += stats.nValidsNumber;
		nTotalInvalidsNumber += stats.nInvalidsNumber;
		nTotalSizeOf += nNumberXSizeOf;
		nTotalSerializeSize += stats.nSerializeSize;
	}
	if ( dumpFile )
		fprintf( dumpFile, "total (%d types)\t%d\t%d\t%d\t%d\t%d\t%d\n", statistics.size(), nTotalObjects, nTotalValidsNumber, nTotalInvalidsNumber, nTotalSizeOf, nTotalSerializeSize );
	else
	{
		sprintf_s( szBuf, 1024, "total (%d types)\t%d\t%d\t%d\t%d\t%d\t%d\n", statistics.size(), nTotalObjects, nTotalValidsNumber, nTotalInvalidsNumber, nTotalSizeOf, nTotalSerializeSize );
		OutputDebugString( szBuf );
	}

	if ( dumpFile )
		fclose( dumpFile );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // TRACK_OBJECTS_STATISTICS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

