#include "stdafx.h"

#include "Basic.h"
#include "interlocked.h"

#ifdef TRACK_COBJECTS
#include "ChunklessSaver.h"
#include "../System/LogFileName.h"
#include "../System/FileUtils.h"
#endif

// Enable this if you want internal validation for the pointers checking
//#define TRACK_COBJECTS_POINTERS_INTERNAL_CHECK

// Enable check weak refs VS strong refs
//#define OBJECT_CHECK_COUNTERS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseRef()
{
  int refCount = nival::interlocked_decrement( nRefCount );
	if ( refCount == 0 && ( nObjCount & ~INVALID_REF_MASK ) == 0 )
  {
    if ( nObjCount == 0 )
      OnDestroyContents();
		ReleaseComplete();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseObj()
{
  int objCount = nival::interlocked_decrement( nObjCount );
	//DecObj();
	if ( ( objCount & ~INVALID_REF_MASK ) == 0 )
	{
    nObjCount = INVALID_REF_MASK + 1;
    OnDestroyContents();
		if ( nRefCount == 0 )
			ReleaseComplete();
		else
			ReleaseInvalid();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::ReleaseComplete()
{
#ifdef TRACK_COBJECTS_POINTERS // Release pointers only here!
	delete pPointers; 
#endif
	DeleteThis();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CObjectBase::AddRef() 
{ 
#ifdef OBJECT_CHECK_COUNTERS
  NI_ASSERT(nObjCount != 0, "CObjectBase. Attempt to create weak reference to object with 0 obj references");
#endif

  nival::interlocked_increment( nRefCount ); 
}


void CObjectBase::ReleaseInvalid()
{

//#ifdef OBJECT_CHECK_COUNTERS
//  NI_ALWAYS_ASSERT("COBjectBase release: Weak reference object counter != 0, but Strong == 0");
//#endif


	nObjCount = INVALID_REF_MASK;
#ifdef TRACK_COBJECTS_POINTERS
	TRACK_ADDPTR(this, (void*)0xFFFFFFAA);
	AddRef();
	TPointersHash *pPointersBackup = pPointers; // Save pointers
	DestroyContents();
	pPointers = pPointersBackup; // Restore pointers
	TRACK_DECPTR(this, (void*)0xFFFFFFAA);
	ReleaseRef();
#else
	AddRef();
	DestroyContents();
	ReleaseRef();
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(TRACK_COBJECTS)
////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSimplePointerHash
{
	template <class T> 
	int operator()( T *p ) const { return (int)p; }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_set<CObjectBase *, SSimplePointerHash> TObjectsSet;
static TObjectsSet *g_pObjectsSet; // do not initialize!
////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::RegisterInObjectsSet()
{
	if ( g_pObjectsSet == 0 )
		g_pObjectsSet = new TObjectsSet;

	g_pObjectsSet->insert( this );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::UnRegisterInObjectsSet()
{
	g_pObjectsSet->erase( this );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TRACK_COBJECTS_POINTERS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FindObjectByPointerInIt(void *pPtr, int &offset, CObjectBase* &pObject)
{
	int nPtr = int(pPtr);
	for ( TObjectsSet::iterator it = g_pObjectsSet->begin(); it != g_pObjectsSet->end(); ++it )
	{
		CObjectBase *pObj = *it;
		int nObj = int(pObj);
		if (nObj <= nPtr && nPtr < nObj + it->GetSizeOf())
		{
			offset = nPtr - nObj;
			pObject = pObj;
			return true;
		}
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::TrackRef(void *pPtr, bool inc, bool isStrong)
{
	// Create pointers tracking hash
	if (!pPointers)
		pPointers = new TPointersHash;

#ifdef TRACK_COBJECTS_POINTERS_INTERNAL_CHECK
	NI_ASSERT(!((nObjCount & INVALID_REF_MASK) != 0 && inc && isStrong), "Referencing by CObj on dead object!");

	int cntStrong = 0;
	int cntWeak   = 0;
	for (TPointersHash::iterator it = pPointers->begin(); it != pPointers->end(); ++it)
	{
		if (it->second.isStrong)
			++cntStrong;
		else
			++cntWeak;
	}
	NI_ASSERT(cntStrong == nObjCount || (nObjCount & INVALID_REF_MASK) != 0, "Strong referencing logic failure");
	NI_ASSERT(cntWeak == nRefCount, "Weak referencing logic failure");
#endif
  // Convert pointer
	if (inc)
	{
#ifdef TRACK_COBJECTS_POINTERS_INTERNAL_CHECK
		TPointersHash::iterator it = pPointers->find(pPtr);
		if (it != pPointers->end())
		{
			NI_ALWAYS_ASSERT(NI_STRFMT("The %08X pointer already found", int(pPtr)));
		}
#endif
		CObjectPointerInfo &info = (*pPointers)[pPtr];
		info.isStrong = isStrong;
	}
	else
	{
#ifdef TRACK_COBJECTS_POINTERS_INTERNAL_CHECK
		NI_ASSERT(pPointers->find(pPtr) != pPointers->end(), NI_STRFMT("The %08X pointer not found", int(pPtr)));
#endif
		pPointers->erase(pPtr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CObjectBase::DumpRefs(int depth, int maxDepth)
{
	// Offset string
	char identStr[64];
	const int identation = 4;
	for (int i = 0; i < depth*identation; i++)
		identStr[i] = ' ';
	identStr[depth*identation] = '\0';

	DebugTrace("%sTRACKPTR: Object %s (%08X). Strong: %d. Weak: %d.", identStr, GetObjectTypeName(), int(this), nObjCount, nRefCount);
	int thisBorderMin = int(this);
	int thisBorderMax = int(this) + GetSizeOf();
	for (TPointersHash::iterator it = pPointers->begin(); it != pPointers->end(); ++it)
	{
		CObjectBase *pObject;
		int          offset;
		int          nPtr = int(it->first);
		if (!(thisBorderMin <= nPtr && nPtr < thisBorderMax))
		{
			if (FindObjectByPointerInIt(it->first, offset, pObject))
			{
				DebugTrace("%s  %08X %s. Object %s (%08X) @ %d", identStr, it->first, it->second.isStrong ? "strong" : "  weak", pObject->GetObjectTypeName(), int(pObject), offset);
				if (depth < maxDepth)
					pObject->DumpRefs(depth + 1, maxDepth);
			}
			else
			{
				DebugTrace("%s  %08X %s. No object found.", identStr, it->first, it->second.isStrong ? "strong" : "  weak");
			}
		}
		else
		{
			DebugTrace("%s  Ring (%s) @ %d.", identStr, it->second.isStrong ? "strong" : "weak", nPtr - thisBorderMin);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool TrackReferences(const char *name, const vector<wstring>& params)
{
	if (params.size() == 0)
		return true;

	wchar_t *pEnd;
	CObjectBase *pObject = (CObjectBase*)wcstol(params[0].c_str(), &pEnd, 0);
	if (params[0].c_str() == pEnd)
	{
		DebugTrace("TRACKPTR: Can't parse parameter 1");
		return true;
	}

	int dumpDepth = 0;
	if (params.size() >= 2)
	{
		int d = wcstol(params[1].c_str(), &pEnd, 0);
		if (params[1].c_str() == pEnd)
		{
			DebugTrace("TRACKPTR: Can't parse parameter 2");
			return true;
		}
		if (0 <= d && d < 6)
			dumpDepth = d;
	}

	TObjectsSet::iterator it = g_pObjectsSet->find(pObject);
	if (it == g_pObjectsSet->end())
	{
		DebugTrace("TRACKPTR: Object %08X not found", int(pObject));
		return true;
	}

	pObject->DumpRefs(0, dumpDepth);
	return true;
}
REGISTER_DEV_CMD( cobj_track_references, TrackReferences );

#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// Statistics
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

	for ( hash_set<CObjectBase *, SSimplePointerHash >::iterator it = g_pObjectsSet->begin(); it != g_pObjectsSet->end(); ++it )
	{
		CObjectBase *pObject = *it;
		if ( pObject == pMemoryStream || pObject == pPointerSerialization || pObject == pSaver )
			continue; // ignore objects made to collect statistics
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
void PrintObjectsStatistics( const char *fileName )
{
	bool toFile = (fileName != NULL);

	hash_map< string, STypeStats > typesMap;
	CollectObjectsStatistics( &typesMap );

	vector< pair<string, STypeStats> > statistics;
	statistics.reserve( typesMap.size() );
	for ( hash_map< string, STypeStats >::iterator it = typesMap.begin(); it != typesMap.end(); ++it )
	{
		statistics.push_back( pair<string, STypeStats>( it->first.data(), it->second ) );
	}
	typesMap.clear();

	if ( !statistics.size() )
	{
		OutputDebugString( "There is no allocated objects.\n" );
		return;
	}

	sort( statistics.begin(), statistics.end(), STypeStatsComparer() );

	FILE *dumpFile = 0;
	if ( toFile )
	{
		char dumpFileName[256];
		strcpy_s( dumpFileName, NDebug::GenerateDebugFileName( fileName, "txt" ).c_str() );
		string logFileName = NFile::GetFullName( string( dumpFileName ) );
		fopen_s( &dumpFile, logFileName.c_str(), "w" );
		if ( !dumpFile )
		{
			OutputDebugString( "Warning: Cannot dump objects statistics to file. Dumping to debug output.\n" ); 
			toFile = false;
		}
	}

	char szBuf[1024];
	strcpy_s( szBuf, " obj count      valid    invalid     sizeof   sizeof*N  serialize  type name\n" );
	if ( dumpFile )
		fprintf( dumpFile, szBuf );
	else
		OutputDebugString( szBuf );
		
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
		sprintf_s( szBuf, "%10d %10d %10d %10d %10d %10d  %s\n",
			stats.nObjectsNumber, stats.nValidsNumber, stats.nInvalidsNumber, stats.nSizeOf, nNumberXSizeOf, stats.nSerializeSize, tmp.first.data() );
		if ( dumpFile )
			fprintf( dumpFile, "%s", szBuf );
		else
			OutputDebugString( szBuf );
		nTotalObjects += stats.nObjectsNumber;
		nTotalValidsNumber += stats.nValidsNumber;
		nTotalInvalidsNumber += stats.nInvalidsNumber;
		nTotalSizeOf += nNumberXSizeOf;
		nTotalSerializeSize += stats.nSerializeSize;
	}
	sprintf_s( szBuf,
		"-----------------------------------------------------------------\n"
		"%10d %10d %10d %10d %10d %10d  (total %d types)\n",
		nTotalObjects, nTotalValidsNumber, nTotalInvalidsNumber, 0, nTotalSizeOf, nTotalSerializeSize, statistics.size() );
	if ( dumpFile )
		fprintf( dumpFile, "%s", szBuf );
	else
		OutputDebugString( szBuf );

	if ( dumpFile )
		fclose( dumpFile );
}
static bool CommandDumpObjects(const char *name, const vector<wstring> &params)
{
	int toFile = 0;
	if ( params.size() > 0 )
		toFile = (int)NGlobal::VariantValue(params[0]).GetFloat();
	PrintObjectsStatistics( toFile ? "ObjectsStatistics" : NULL );
	return true;
}
REGISTER_DEV_CMD(cobj_dump, CommandDumpObjects)
static struct SRegister_DetectMemoryLeaks
{
	SRegister_DetectMemoryLeaks()
	{}
	~SRegister_DetectMemoryLeaks()
	{
		PrintObjectsStatistics( "ObjectLeaks" );
	}
} detectMemoryLeaks;
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // TRACK_COBJECTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
