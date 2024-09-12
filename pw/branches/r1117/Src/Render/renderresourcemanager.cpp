#include "stdafx.h"
#define TOOLSET_IS_PRESENT
#include "renderresourcemanager.h"

#include "../System/nalgoritm.h"
#include "../System/TextFileDumper.h"

#include "texture.h"
#include "renderflagsconverter.h"

#include "../MeshConverter/MeshHeader.h"

#include "smartrenderer.h"
#include "../System/memorypool.h"
#include "multishader.h"
#include "materialspec.h"

#include "../System/2Darray.h"
#include "../System/InlineProfiler.h"

#include "../MeshConverter/SkeletonHeader.h"

#include "MeshResource.h"
#include "InstancedMeshResource.h"
#include "CleanGeometry.h"
#include "../MeshConverter/ParticleNewHeader.h"

#include "../MeshConverter/SkeletonHeader.h"
#include "../MeshConverter/SkeletalAnimationHeader.h"
#include "libdb/DbResourceCache.h"
//#include "System/InlineProfiler.h"

static int shaderIndex = 0;

static NDebug::PerformanceDebugVar render_ShaderCompile( "ShaderCompile", "RenderOffline", 100, 100, false );
static NDebug::PerformanceDebugVar render_LoadTime( "LoadTime", "RenderOffline", 100, 100, false );

NDebug::DebugVar<int> SkeletalAnimationData_Memory( "SkeletalAnimationData_Memory", "MemoryUsage" );
NDebug::DebugVar<int> SkeletonData_Memory( "SkeletonData_Memory", "MemoryUsage" );
NDebug::DebugVar<int> NewPFXBinaryFile_Memory( "NewPFXBinaryFile_Memory", "MemoryUsage" );


#ifdef _DEBUG
//#define INSTANCING_STATISTICS
#endif

namespace Render
{

DECLARE_NULL_RENDER_FLAG

// In TextureManager.cpp
void TickTextureManager();

DEFINE_DEV_VAR(s_clean_terrain_geometry, false, "clean_terrain_geometry", STORAGE_NONE);

namespace RenderResourceManager
{
static MeshGeometry* LoadMeshGeometryFromFile( const nstl::string& fileName, bool bSkeletalMesh, bool appendColorStream );
static InstancedMeshGeometry* LoadInstancedMeshGeometryFromFile( const nstl::string& fileName );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryPool memoryPool;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const void* InPlaceLoad(const nstl::string& fileName, int * size )
{
  //VTuneResumer vtRes( g_Profile_ResourceLoading );
  NI_ASSERT( !NDb::GetDbResourceCache().IsAssertionLoadingFiles(), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", fileName.c_str() ) 
  );

  CObj<Stream> pFileStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pFileStream && pFileStream->IsOk(), NStr::StrFmt( "Cannot open file for reading: %s", fileName.c_str() ), return 0; );
  const int fileSize = pFileStream->GetSize();
	NI_VERIFY( fileSize, NStr::StrFmt( "File size is ZERO: %s", fileName.c_str() ), return 0; );
  void* pData = memoryPool.AllocateMemory( fileSize, fileName.c_str() );
  pFileStream->Read( pData, fileSize );

  if ( size )
    *size += fileSize;

  return pData;
}

namespace
{

struct PoolObjectWrapper
{
  PoolObjectWrapper() {}
  PoolObjectWrapper(void* _pObj, string const &_filename) : pObj(_pObj)
  {
    SFileInfo fileInfo;
    RootFileSystem::GetFileInfo(&fileInfo, _filename);
    
    modificationTime = fileInfo.time;   
  }

  void*      pObj;
  SWin32Time modificationTime;
};

struct ReloadGeomMesh
{
  static void Process(const nstl::string& _filename, MeshGeometry *m)
  {
    MeshGeometry *newMesh = LoadMeshGeometryFromFile( _filename, m->pReindex != 0, m->colorStreamAppended );

    NI_VERIFY( m->primitives.size() == newMesh->primitives.size(), "New mesh has invalid number of primitives", return );
    m->Swap(newMesh);
    delete newMesh;
  }
};

struct ReloadInstancedGeomMesh
{
	static void Process(const nstl::string& filename, InstancedMeshGeometry *m)
	{
		InstancedMeshGeometry *newMesh = LoadInstancedMeshGeometryFromFile( filename );
		m->Swap(newMesh);
		delete newMesh;
	}
};


struct ReloadSkeleton
{
public :
  static void Process(const nstl::string& filename, SkeletonDataWrapper *s)
  {
    int currentSize = SkeletonData_Memory.GetValue();
    const SkeletonData *skeletonData = reinterpret_cast<const SkeletonData*>( InPlaceLoad(filename, &currentSize) );
    SkeletonData_Memory.SetValue( currentSize );

    s->SetData( skeletonData );
  }
};

#include "PFXLogger.inl"

struct CReloadPFX
{
public :
  static void Process(const nstl::string& filename, PFXBinaryFileWrapper *pfx)
  {
    int currentSize = NewPFXBinaryFile_Memory.GetValue();
  	const NewPFXBinaryFile* pPFXBinaryFileData = reinterpret_cast<const NewPFXBinaryFile*>( InPlaceLoad(filename, &currentSize) );
    NewPFXBinaryFile_Memory.SetValue( currentSize );
    
    pfx->SetData( pPFXBinaryFileData );

    PFX_LOG(filename, pPFXBinaryFileData);
  }
};

struct ReloadAnim
{
public :
  static void Process(const nstl::string& filename, SkeletalAnimationDataWrapper *a)
  {
    int currentSize = SkeletalAnimationData_Memory.GetValue();
    const SkeletalAnimationData* pSkeletalAnimationData = (SkeletalAnimationData*)InPlaceLoad(filename, &currentSize);
    SkeletalAnimationData_Memory.SetValue( currentSize );
    a->SetData( pSkeletalAnimationData );
  } 
};

template<class Func, class T>
struct UpdateModifiedData
{
 static void Process(string const &_filename, PoolObjectWrapper &obj)
 {
   SWin32Time newTime;
   if( !WasModified(_filename, obj, newTime) )
     return;

   Func::Process(_filename, (T*)obj.pObj);
   obj.modificationTime = newTime;
	 
   systemLog( NLogg::LEVEL_MESSAGE ) << "Object from "<< _filename.c_str(  ) << " was reloaded " << endl;
 }

private :
  static bool WasModified( string const &_filename, PoolObjectWrapper const &obj, SWin32Time &newTime)
  {
    SFileInfo fileInfo;
    RootFileSystem::GetFileInfo(&fileInfo, _filename);
    newTime = fileInfo.time;

    return fileInfo.time.GetFullTime() != obj.modificationTime.GetFullTime();
  }

};


} // namespace
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const MeshGeometry* pDefaultStaticMeshGeometry = 0;
static const MeshGeometry* pDefaultSkeletalMeshGeometry = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool g_Profile_ResourceLoading = true;
static bool g_Profile_CreateBuffers = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef nstl::hash_map< nstl::string, int > TMultyShaderPool;
typedef nstl::vector< Materials::MultiShader* > TMultyShaderIndexPool;
typedef nstl::hash_map< int, int > TMultyShaderTypeIdPool;

TMultyShaderPool& GetMultishaderPool()
{
  static TMultyShaderPool MultyShaderPool;
  return MultyShaderPool;
}

TMultyShaderIndexPool& GetMultishaderIndexPool()
{
  static TMultyShaderIndexPool MultyShaderIndexPool;
  return MultyShaderIndexPool;
}

TMultyShaderTypeIdPool& GetMultishaderTypeIdPool()
{
  static TMultyShaderTypeIdPool MultyShaderTypeIdPool;
  return MultyShaderTypeIdPool;
}

vector<int> shadersToReload;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MeshGeometry* GetDefaultStaticMeshGeometry() { return pDefaultStaticMeshGeometry; }
const MeshGeometry* GetDefaultSkeletalMeshGeometry() { return pDefaultSkeletalMeshGeometry; }
//////////////////////////////////////////////////////////////////////////
void SaveMeshGeometry( MeshGeometry const *pGeometry, Stream *pStream )
{
  NI_VERIFY( pGeometry, "NULL pointer passed", return; );
  NI_VERIFY( pStream && pStream->IsOk(), "invalid stream", return; );

  DummyAllocator allocator(20*1024*1024);
  H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<H6GeometryFileHeader*>(allocator.Allocate(sizeof(H6GeometryFileHeader), 16));
  pH6GeometryFileHeader->signature = 0;
  pH6GeometryFileHeader->fragmentCount = pGeometry->fragmentCount;
  pH6GeometryFileHeader->materialCount = pGeometry->materialCount;
  ///
  pH6GeometryFileHeader->jointsCount = 0;
  pH6GeometryFileHeader->fragments.resize( pGeometry->fragmentCount, &allocator );

  unsigned int strideSize = 0;
  if (pGeometry->primitives.size() > 0)
  {
    strideSize = pGeometry->primitives[0]->GetVBStride();
  }

  ///////////////////////////////////////////////////
  // gather header information
  unsigned int vboffset = 0;
  unsigned int iboffset = 0;
  for (unsigned int fragmentNumber = 0; fragmentNumber < pGeometry->fragmentCount; ++fragmentNumber)
  {
    Primitive *prim = pGeometry->primitives[fragmentNumber];
    H6FragmentHeader& fragmentHeader = pH6GeometryFileHeader->fragments[fragmentNumber];

    D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
    UINT strideElementsCount;
    prim->GetVertexDeclaration()->GetDeclaration( decl, &strideElementsCount);

    /// 
    fragmentHeader.vertexElementDescriptor.resize( strideElementsCount, &allocator );	
    for (unsigned int i = 0; i < strideElementsCount; ++i)
    {
      D3DVERTEXELEMENT9 &d = decl[i];
      fragmentHeader.vertexElementDescriptor[i] = Render::VertexElementDescriptor(d.Stream, d.Offset, Convert2VertexElementType(d.Type),
                                                                                  Convert2VertexElementUsage(d.Usage), d.UsageIndex);
    }

    /// 
    const DipDescriptor& dip = prim->GetDipDescriptor();
    NI_ASSERT(dip.primitiveType == RENDERPRIMITIVE_TRIANGLELIST, "unsupported primitive type");
    fragmentHeader.vertexStrideSizeInBytes = strideSize;
    fragmentHeader.baseVertexIndex = dip.baseVertexIndex;
    fragmentHeader.minIndex = dip.minIndex;
    fragmentHeader.numVertices = dip.numVertices;
    fragmentHeader.startIndex = dip.startIndex;
    fragmentHeader.primitiveCount = dip.primitiveCount;
    fragmentHeader.materialID = fragmentNumber;
    fragmentHeader.streamOffset = 0;
    /// 
    vboffset += dip.numVertices;
    iboffset += dip.primitiveCount * 3;
  }

  pH6GeometryFileHeader->commonIndexBufferSizeInBytes = sizeof(unsigned int) * iboffset;
  pH6GeometryFileHeader->commonVertexBufferSizeInBytes = strideSize * vboffset;

  allocator.Normalize(16);
  pH6GeometryFileHeader->vbOffset = allocator.GetSize();
  pH6GeometryFileHeader->ibOffset = pH6GeometryFileHeader->vbOffset + pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
  pH6GeometryFileHeader->reindexOffset = 0;



  ///////////////////////////////////////////////////
  // write header
  pStream->Write( allocator.GetData(), allocator.GetSize() );

  if (pGeometry->primitives.size() == 0)
    return;

  ///////////////////////////////////////////////////
  // write vertex buffer (single for all primitives)
  {
    DXVertexBufferRef vb = pGeometry->primitives[0]->GetVertexBuffer();
    D3DVERTEXBUFFER_DESC vbDesc;
    vb->GetDesc(&vbDesc);
    void *pData = LockVB(Get(vb), D3DLOCK_READONLY);
    pStream->Write(pData, vbDesc.Size);
    vb->Unlock();
  }

  ///////////////////////////////////////////////////
  // write index buffers
  for (unsigned int fragmentNumber = 0; fragmentNumber < pGeometry->fragmentCount; ++fragmentNumber)
  {
    Primitive const *prim = pGeometry->primitives[fragmentNumber];
    DXIndexBufferRef ib = prim->GetIndexBuffer();
    D3DINDEXBUFFER_DESC ibDesc;
    ib->GetDesc(&ibDesc);
    unsigned int *pData = LockIB(Get(ib), D3DLOCK_READONLY);
    pStream->Write(pData, ibDesc.Size);
    ib->Unlock();
  }
}
//////////////////////////////////////////////////////////////////////////
MeshGeometry* LoadMeshGeometry( const char *pData, bool bSkeletalMesh, bool appendColorStream )
{
	NI_VERIFY( pData, "invalid stream", return 0; );

  const H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<const H6GeometryFileHeader*>(pData);

	NI_VERIFY( pH6GeometryFileHeader->vbOffset < pH6GeometryFileHeader->ibOffset, "stream corrupted", return 0; );
	if(bSkeletalMesh)
	{
		NI_VERIFY( pH6GeometryFileHeader->reindexOffset, "skeletal mesh corrupted", return 0; );
		NI_VERIFY( pH6GeometryFileHeader->ibOffset < pH6GeometryFileHeader->reindexOffset, "skeletal mesh corrupted", return 0; );
	}
	else
	{
		if(pH6GeometryFileHeader->reindexOffset != 0)
		{
			systemLog( NLogg::LEVEL_MESSAGE ) << "static mesh is corrupted" << endl;
			return 0;
		}
		//NI_VERIFY( pH6GeometryFileHeader->reindexOffset == 0, "static mesh file corrupted", return 0; );
	}

	const char* pVBSrcData = pData + pH6GeometryFileHeader->vbOffset;
	const char* pIBSrcData = pVBSrcData +  pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
	const char* pReindexData = pData + pH6GeometryFileHeader->reindexOffset;

	///
  DXVertexBufferRef pVB = RENDER_DISABLED ? DXVertexBufferRef() : CreateVB(pH6GeometryFileHeader->commonVertexBufferSizeInBytes, RENDER_POOL_MANAGED, (void*)pVBSrcData);
  DXIndexBufferRef pIB  = RENDER_DISABLED ? DXIndexBufferRef() : CreateIB(pH6GeometryFileHeader->commonIndexBufferSizeInBytes, RENDER_POOL_MANAGED, (const unsigned int*)pIBSrcData);

  //
	const StaticVector<H6FragmentHeader> &fragments = pH6GeometryFileHeader->fragments;

	///
	MeshGeometry* pMeshGeometry = new MeshGeometry();
	pMeshGeometry->colorStreamAppended = appendColorStream;
	pMeshGeometry->materialCount = pH6GeometryFileHeader->materialCount;
	pMeshGeometry->fragmentCount = pH6GeometryFileHeader->fragmentCount;
	pMeshGeometry->primitives.resize( pH6GeometryFileHeader->fragmentCount );
	for (unsigned int i = 0; i < pH6GeometryFileHeader->fragmentCount; ++i)
	{
		Primitive* pPrimitive = new Primitive();
		pPrimitive->SetVertexStream(pVB, fragments[i].vertexStrideSizeInBytes, fragments[i].streamOffset);
		pPrimitive->SetIndexBuffer(pIB);

		VertexFormatDescriptor formatDescriptor;
		formatDescriptor.AssignVertexElements( fragments[i].vertexElementDescriptor[0], 
																					 fragments[i].vertexElementDescriptor.size() );
		if (appendColorStream)
		{
      const unsigned int usageIndex = (unsigned int)(formatDescriptor.FindMaxUsageIndex(VERETEXELEMENTUSAGE_COLOR) + 1);
      NI_DATA_ASSERT(usageIndex == 0U, "Mesh with vertex colors can't use additional color stream (baked lighting)");
      formatDescriptor.AddVertexElement(VertexElementDescriptor(1U, 0U, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0U));
      formatDescriptor.AddVertexElement(VertexElementDescriptor(2U, 0U, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 1U));
		}
		pPrimitive->SetVertexDeclaration( SmartRenderer::GetVertexFormatDeclaration(formatDescriptor) );

		DipDescriptor &dipDescr = pPrimitive->GetDipDescriptor();
		dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
		dipDescr.baseVertexIndex = fragments[i].baseVertexIndex;
		dipDescr.numVertices = fragments[i].numVertices;
		dipDescr.primitiveCount = fragments[i].primitiveCount;
		pMeshGeometry->triangleCount += dipDescr.primitiveCount;
		dipDescr.startIndex = fragments[i].startIndex;

		pMeshGeometry->primitives[i] = pPrimitive;
		pMeshGeometry->materialID[i] = fragments[i].materialID;
	}
  
	///
	if (pH6GeometryFileHeader->jointsCount > 0)
	{
    // calculate memory taken by reindex table
    StaticVector< StaticVector<unsigned short> > const *reindex = reinterpret_cast< StaticVector< StaticVector<unsigned short> > const * >(pReindexData);
    // the old code contained a bug so I rewrote it for this particular case keeping backward compatibility [12/1/2010 paul.smirnov]
    unsigned int size = Align(reindex->getMemorySize(), 16);
    for (unsigned int i = 0; i < reindex->size(); ++i)
      size += Align((*reindex)[i].size() * sizeof((*reindex)[0][0]), 16);

		pMeshGeometry->pReindex = reinterpret_cast<const GeometryReindex* >( memoryPool.AllocateMemory( size, "reindex" ) );
		memcpy( (void*)pMeshGeometry->pReindex, pReindexData, size );
	}

  // check if there's a hidden copy of the indices
  unsigned totalTriangles = 0;
  for (int i = 0, n = pMeshGeometry->primitives.size(); i < n; i++)
  {
    Primitive* pPrimitive = pMeshGeometry->primitives[i];
    if (pPrimitive->GetDipDescriptor().primitiveType != RENDERPRIMITIVE_TRIANGLELIST)
    {
      totalTriangles = 0;
      break;
    }
    totalTriangles += pPrimitive->GetDipDescriptor().primitiveCount;
  }
  if (pH6GeometryFileHeader->commonIndexBufferSizeInBytes == 6 * totalTriangles * sizeof(unsigned)) // twice as big as declared
    for (int i = 0, n = pMeshGeometry->primitives.size(); i < n; i++)
      pMeshGeometry->primitives[i]->HasHiddenIndices(true);

	return pMeshGeometry;
}


//////////////////////////////////////////////////////////////////////////
static MeshGeometry* LoadMeshGeometryFromFile( const nstl::string& fileName, bool bSkeletalMesh, bool appendColorStream )
{
  //VTuneResumer vtRes( g_Profile_ResourceLoading );
  //systemLog( NLogg::LEVEL_MESSAGE ) << "LoadMeshGeometryFromFile: " << fileName << endl;

  NI_ASSERT( !NDb::GetDbResourceCache().IsAssertionLoadingFiles(), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", fileName.c_str() ) 
  );

  CObj<Stream> pFileStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pFileStream && pFileStream->IsOk(), NStr::StrFmt( "Cannot open file for reading: %s", fileName.c_str() ), return 0 );

  MeshGeometry* pMeshGeometry = LoadMeshGeometry( pFileStream->GetBuffer(), bSkeletalMesh, appendColorStream );
  NI_ASSERT(pMeshGeometry, NStr::StrFmt( "Failed to load mesh from file: %s", fileName.c_str() ));

  return pMeshGeometry;
}

//============================================================================================================

#ifndef _DLL
#define USE_TLS
#endif // _DLL


class BasicPoolFinder
{
  typedef nstl::hash_map<nstl::string, bool> DirtySet; // Is it optimal to use map here?
  typedef nstl::hash_map<nstl::string, PoolObjectWrapper> GeometryPool;

  DirtySet     dirtySet;
  GeometryPool loadingPool;

  threading::Mutex loadMutex;
#ifdef USE_TLS
  THREAD_LS static bool s_isSecondaryThread;
#else
  static DWORD s_mainThreadID;
#endif // USE_TLS

protected:
  typedef nstl::vector<void*> DeletePool;

  DeletePool   deletePool;
  GeometryPool geometryPool;

  void* FindMain(const nstl::string& _filename);
  void* FindSecondary(const nstl::string& _filename);
  void* MarkAsLoaded(void* _pObj, const nstl::string& _filename);
  void* Find(const nstl::string& filename)
  {
    return IsSecondaryThread() ? FindSecondary(filename) : FindMain(filename);
  }

public:
  static void MarkAsSecondaryThread()
  {
#ifdef USE_TLS
    s_isSecondaryThread = true;
#endif // USE_TLS
  }
  static bool IsSecondaryThread()
  {
//    NI_PROFILE_HEAVY_FUNCTION
#ifdef USE_TLS
    return s_isSecondaryThread;
#else
    return s_mainThreadID != GetCurrentThreadId();
#endif // USE_TLS
  }

  void MoveMarkedInPool();
  void MarkAsDirty(const nstl::string& filename);
  void ClearAll();
};


void* BasicPoolFinder::FindMain(const nstl::string& _filename)
{ // All this dirtySet stuff is valid in single-threaded case only
  DirtySet::iterator it_mark = dirtySet.find(_filename);
  if(it_mark != dirtySet.end() && it_mark->second)
  { //Dirty - reload
    it_mark->second = false;
    GeometryPool::iterator it = geometryPool.find(_filename);
    if( it != geometryPool.end() ) {
      deletePool.push_back(it->second.pObj);
      geometryPool.erase(it);
    }
    return 0;
  }
  GeometryPool::iterator it = geometryPool.find(_filename);
  if(geometryPool.end() != it)
    return it->second.pObj;

  threading::MutexLock lock(loadMutex);
  it = loadingPool.find(_filename);
  return (loadingPool.end() == it) ? 0 : it->second.pObj;
}


void* BasicPoolFinder::FindSecondary(const nstl::string& _filename)
{
  threading::MutexLock lock(loadMutex);

  GeometryPool::iterator it = geometryPool.find(_filename);
  if(geometryPool.end() != it)
    return it->second.pObj;

  it = loadingPool.find(_filename);
  return (loadingPool.end() == it) ? 0 : it->second.pObj;
}


void* BasicPoolFinder::MarkAsLoaded(void* _pObj, const nstl::string& _filename)
{ 
  threading::MutexLock lock(loadMutex);

  nstl::pair<GeometryPool::iterator, bool> result =
    loadingPool.insert( make_pair(_filename, PoolObjectWrapper(_pObj, _filename)) );

  return result.first->second.pObj;
}


void BasicPoolFinder::MoveMarkedInPool()
{
  threading::MutexLock lock(loadMutex);
  geometryPool.insert( loadingPool.begin(), loadingPool.end() );
  loadingPool.clear();
}


void BasicPoolFinder::MarkAsDirty(const nstl::string& filename) { dirtySet[filename] = true; }


void BasicPoolFinder::ClearAll()
{
  geometryPool.clear();
  deletePool.clear();
  dirtySet.clear();
}

#ifdef USE_TLS
THREAD_LS bool BasicPoolFinder::s_isSecondaryThread = false;
#else
DWORD BasicPoolFinder::s_mainThreadID = GetCurrentThreadId();
#endif


//============================================================================================================
template<class _Geometry> 
class PoolFinder : public BasicPoolFinder
{
protected:
  ~PoolFinder() { ClearAll(); }

  _Geometry* Find(const nstl::string& filename) { return (_Geometry*)BasicPoolFinder::Find(filename); }

  _Geometry* MarkAsLoaded(_Geometry* _pObj, const nstl::string& _filename)
  {
    _Geometry* result = (_Geometry*)BasicPoolFinder::MarkAsLoaded(_pObj, _filename);
    if(result != _pObj)
      delete _pObj;
    return result;
  }

public:
  template<class Func>
  void Update()
  {
    GeometryPool::iterator const endIt = geometryPool.end();
    for(GeometryPool::iterator it = geometryPool.begin(); it != endIt; ++it)
      UpdateModifiedData<Func, _Geometry>::Process(it->first, it->second);
  }

  void ClearAll()
  {
    MoveMarkedInPool();

    GeometryPool::iterator const geometryPoolEnd = geometryPool.end();
    for(GeometryPool::iterator it = geometryPool.begin(); it != geometryPoolEnd; ++it)
      delete (_Geometry*)(it->second.pObj);

    DeletePool::iterator const deletePoolEnd = deletePool.end();
    for(DeletePool::iterator it = deletePool.begin(); it != deletePoolEnd; ++it )
      delete (_Geometry*)(*it);

    BasicPoolFinder::ClearAll();
  }
};

//============================================================================================================
class MeshGeometryLoader : public PoolFinder<MeshGeometry>
{
public:
  const MeshGeometry* LoadStatic(const nstl::string& filename, bool appendColorStream)
  {
    //VTuneResumer vtRes( g_Profile_ResourceLoading );
    NDebug::PerformanceDebugVarGuard render_LoadTimeGuard( render_LoadTime, false );

    MeshGeometry* pMeshGeometry = Find(filename);
    if(pMeshGeometry) {
      if(pMeshGeometry->colorStreamAppended != appendColorStream)
      {
        NI_DATA_ALWAYS_ASSERT( NStr::StrFmt("Mesh geometry '%s' is duplicated with different vertex colors flag", filename) );
        if( MeshGeometry* pMG = LoadMeshGeometryFromFile(filename, false, appendColorStream) )
        {
          pMeshGeometry->Swap(pMG);
          delete pMG;
        }
        //FIXME: What to do with 'MeshGeometryPool_Mark' entries?
      }
    }
    else {
      pMeshGeometry = LoadMeshGeometryFromFile(filename, false, appendColorStream);
      if(pMeshGeometry)
        pMeshGeometry = MarkAsLoaded(pMeshGeometry, filename);
    }

    return pMeshGeometry;
  }

  const MeshGeometry* LoadSkeletal(const nstl::string& filename)
  {
    //VTuneResumer vtRes( g_Profile_ResourceLoading );
    NDebug::PerformanceDebugVarGuard render_LoadTimeGuard( render_LoadTime, false );

    MeshGeometry* pMeshGeometry = Find(filename);
    if(!pMeshGeometry ) {
      pMeshGeometry = LoadMeshGeometryFromFile(filename, true, false);
      if(!pMeshGeometry )
        return GetDefaultSkeletalMeshGeometry();

      pMeshGeometry = MarkAsLoaded(pMeshGeometry, filename);
    }
    return pMeshGeometry;
  }
};


MeshGeometryLoader meshGeometryLoader;

const MeshGeometry* LoadStaticMeshGeometry(const nstl::string& filename, bool appendColorStream)
{
  return meshGeometryLoader.LoadStatic(filename, appendColorStream);
}

const MeshGeometry* LoadSkeletalMeshGeometry(const nstl::string& filename)
{
  return meshGeometryLoader.LoadSkeletal(filename);
}

//============================================================================================================
class InstancedMeshGeometryLoader : public PoolFinder<InstancedMeshGeometry>
{
public:
  InstancedMeshGeometry* Load(const nstl::string& filename)
  {
    //VTuneResumer vtRes( g_Profile_ResourceLoading );
    NDebug::PerformanceDebugVarGuard render_LoadTimeGuard( render_LoadTime, false );

    InstancedMeshGeometry* pMeshGeometry = Find(filename);
    if(!pMeshGeometry ) {
      pMeshGeometry = LoadInstancedMeshGeometryFromFile(filename);
      if(pMeshGeometry)
        pMeshGeometry = MarkAsLoaded(pMeshGeometry, filename);
    }
    return pMeshGeometry;
  }
};

InstancedMeshGeometryLoader instMeshGeometryLoader;

InstancedMeshGeometry* LoadInstancedMeshGeometry(const nstl::string& filename) { return instMeshGeometryLoader.Load(filename); }

//============================================================================================================

void MarkAsDirtyGeometry( const nstl::string& filename )
{
  meshGeometryLoader.MarkAsDirty(filename);
  instMeshGeometryLoader.MarkAsDirty(filename);
}

void ReloadGeometry( bool )
{
  meshGeometryLoader.Update<ReloadGeomMesh>();
  instMeshGeometryLoader.Update<ReloadInstancedGeomMesh>();
}

static void UnloadMeshGeometry()
{
  meshGeometryLoader.ClearAll();
  instMeshGeometryLoader.ClearAll();
}

//============================================================================================================

template<class _Data>
class InPlaceLoader : public PoolFinder<_Data>, public NonCopyable
{
  NDebug::DebugVar<int> &counter;
public:
  explicit InPlaceLoader(NDebug::DebugVar<int> &_counter) : counter(_counter) {}

  _Data* Load(const nstl::string& filename)
  {
    //VTuneResumer vtRes( g_Profile_ResourceLoading );
    NDebug::PerformanceDebugVarGuard render_LoadTimeGuard( render_LoadTime, false );

    _Data* result = Find(filename);
    if(!result) {
      int currentSize = counter.GetValue();
      const _Data::value_type* pData = reinterpret_cast<const _Data::value_type*>( InPlaceLoad(filename, &currentSize) );
      counter.SetValue( currentSize );

      result = new _Data(pData);
      result = MarkAsLoaded(result, filename);
    }
    return result;
  }
};

//============================================================================================================

InPlaceLoader<PFXBinaryFileWrapper> partFXLoader(NewPFXBinaryFile_Memory);

const PFXBinaryFileWrapper* LoadPFXData(const nstl::string& filename)
{
  const PFXBinaryFileWrapper* result = partFXLoader.Load(filename);
  PFX_LOG( filename, result->GetData() );
  return result;
}
void  MarkAsDirtyPFX(const nstl::string& filename) { partFXLoader.MarkAsDirty(filename); }

void        ReloadPFXNew( bool )        { PFX_LOGGER_RESET; partFXLoader.Update<CReloadPFX>(); }
static void UnloadInPlacedPFXWrappers() { partFXLoader.ClearAll(); }

//============================================================================================================

InPlaceLoader<SkeletonDataWrapper> skeletonLoader(SkeletonData_Memory);

SkeletonDataWrapper* LoadSkeletonData(const nstl::string& filename) { return skeletonLoader.Load(filename); }
void          MarkAsDirtySkeletonData(const nstl::string& filename) { skeletonLoader.MarkAsDirty(filename); }

void        ReloadSkeletons( bool )      { skeletonLoader.Update<ReloadSkeleton>(); }
static void UnloadSkeletalMeshWrappers() { return skeletonLoader.ClearAll(); }

//============================================================================================================

InPlaceLoader<SkeletalAnimationDataWrapper> animationLoader(SkeletonData_Memory);

const SkeletalAnimationDataWrapper* LoadSkeletalAnimation(const nstl::string& filename) { return animationLoader.Load(filename); }
void                              MarkAsDirtySkeletonAnim(const nstl::string& filename) { animationLoader.MarkAsDirty(filename); }

void        ReloadAnims( bool )                       { animationLoader.Update<ReloadAnim>(); }
static void UnloadInPlacedSkeletalAnimationWrappers() { return animationLoader.ClearAll(); }

//============================================================================================================

static InstancedMeshGeometry* LoadInstancedMeshGeometryFromFile( const nstl::string& fileName )
{
  NI_ASSERT( !NDb::GetDbResourceCache().IsAssertionLoadingFiles(), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", fileName.c_str() ) 
  );
  
  CObj<Stream> pFileStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( pFileStream && pFileStream->IsOk(), NStr::StrFmt( "Cannot open file for reading: %s", fileName.c_str() ), delete pFileStream; return 0; );

	const H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<const H6GeometryFileHeader*>(pFileStream->GetBuffer());
	NI_VERIFY( pH6GeometryFileHeader, NStr::StrFmt( "Cannot load mesh from zero size file: %s", fileName.c_str() ), delete pFileStream; return 0; );

	NI_VERIFY( pH6GeometryFileHeader->vbOffset < pH6GeometryFileHeader->ibOffset, "file corrupted", delete pFileStream; return 0; );
	if (pH6GeometryFileHeader->reindexOffset != 0)
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << fileName << ": static mesh is corrupted" << endl;
		return 0;
	}

	InstancedMeshGeometry *pIMG = new InstancedMeshGeometry( pH6GeometryFileHeader, fileName );

	return pIMG;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define CLEAN_INDICES

template<typename INDEX>
static void CleanGeometry(const TerrainElementGeometryRaw &_in, TerrainElementGeometryRaw &_out)
{
  NI_PROFILE_FUNCTION
  const INDEX *pIndicesIn = (INDEX*)_in.indexBuffer;
  const H6GeometryFileHeader* const pHeader = reinterpret_cast<const H6GeometryFileHeader*>(_out.rawData);
  Render::VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AssignVertexElements( pHeader->fragments[0].vertexElementDescriptor[0],
                                         pHeader->fragments[0].vertexElementDescriptor.size() );

  Render::GeneralVtx::hasher.Init(formatDescriptor, true);

  _out.dipDescriptor.numVertices = Render::RemoveDuplicateVertices(_in.vertexBuffer, _out.vertexBuffer, _in.vertexBufferStride,
                                                                   _in.vertexBufferSize, pIndicesIn, _out.indexBuffer,
                                                                   _in.indexBufferSize);
  _out.vertexBufferSize = _out.dipDescriptor.numVertices * _out.vertexBufferStride;

#ifdef CLEAN_INDICES
  // TODO: account for duplicated IB's.
  const UINT numIndices = Render::RemoveDuplicateTriangles( (INDEX*)_out.indexBuffer, _out.dipDescriptor.primitiveCount * 3 );
  _out.dipDescriptor.primitiveCount = numIndices / 3;
  _out.indexBufferSize = numIndices * sizeof(INDEX);
#endif // CLEAN_INDICES
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GetTerrainElementGeometryRawData( Stream* pStream, TerrainElementGeometryRaw* pRawData )
{
  struct Local
  {
    static bool GetTerrainElementGeometryRawData(const char* const streamData, const H6GeometryFileHeader* const header, TerrainElementGeometryRaw* const data)
    {
      data->version             = 0U;

      // save raw data pointers
      data->rawData             = const_cast<char*>(streamData);
      data->rawDataSize         = header->ibOffset + header->commonIndexBufferSizeInBytes;

      // load vertex buffer
      data->vertexBufferSize    = header->commonVertexBufferSizeInBytes;
      data->vertexBufferStride  = header->fragments[0].vertexStrideSizeInBytes;
      data->vertexBuffer        = data->rawData + header->vbOffset;

      // load index buffer
      data->indexBufferSize     = header->commonIndexBufferSizeInBytes;
      data->indexBuffer         = data->rawData + header->ibOffset;

      // load dip descriptor
      {
        DipDescriptor& dip = data->dipDescriptor;

        dip.primitiveType   = RENDERPRIMITIVE_TRIANGLELIST;
        dip.baseVertexIndex = header->fragments[0].baseVertexIndex;
        dip.numVertices     = header->fragments[0].numVertices;
        dip.primitiveCount  = header->fragments[0].primitiveCount;
        dip.startIndex      = header->fragments[0].startIndex;
      }

      // load vertex format declaration
      {
        VertexFormatDescriptor formatDescriptor;

        formatDescriptor.AssignVertexElements( header->fragments[0].vertexElementDescriptor[0], header->fragments[0].vertexElementDescriptor.size() );

        data->pVtxDecl = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
      }

      return true;
    }
  };

	NI_VERIFY( pStream && pStream->IsOk(), "Invalid stream!", return false; );
	NI_VERIFY( pRawData, "Invalid storage!", return false; );

	const char* data = pStream->GetBuffer() + pStream->GetPosition();
	const H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<const H6GeometryFileHeader*>( data );

  ASSERT( pH6GeometryFileHeader->fragmentCount == 1 );

  switch (pH6GeometryFileHeader->signature)
  {
  case Signs::telmSIGN:
    ASSERT( pH6GeometryFileHeader->fragments[0].vertexStrideSizeInBytes == sizeof(TerrainElementStrideNew) );
    break;
  default:
    ASSERT( pH6GeometryFileHeader->fragments[0].vertexStrideSizeInBytes == sizeof(TerrainElementStride) );
    break;
  }

  const bool result = Local::GetTerrainElementGeometryRawData(data, pH6GeometryFileHeader, pRawData);

  switch (pH6GeometryFileHeader->signature)
  {
  case Signs::telmSIGN:
    pRawData->version = 1U;
    break;
  default:
    pRawData->version = 0U;
    break;
  }

  // change position to end of raw data
  if (result)
  {
    pStream->Seek( pRawData->rawDataSize, SEEKORIGIN_OFFSET );
  }
  else
  {
    // fallback
    pStream->Seek(pH6GeometryFileHeader->ibOffset + pH6GeometryFileHeader->commonIndexBufferSizeInBytes, SEEKORIGIN_OFFSET);
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CreateTerrainElementRawData( Stream* pStream, TerrainElementGeometryRaw* pRawData )
{
	if( !GetTerrainElementGeometryRawData(pStream, pRawData) )
    return false;

  ConvertTerrainElementGeometry(*pRawData);

  CopyElementGeometry(pRawData);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CheckTerrainElementGeometryRawDataVersion(const TerrainElementGeometryRaw& geometry)
{
  return (geometry.version == 1U);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CreateTerrainFragmentGeometry( Primitive* pGeometry, const TerrainElementGeometryRaw& source )
{
	ASSERT( pGeometry );
	ASSERT( source.vertexBufferSize != 0 );
	ASSERT( source.indexBufferSize != 0 );

	// create DX resources
	pGeometry->GetDipDescriptor() = source.dipDescriptor;

  if(!RENDER_DISABLED)
  {
    pGeometry->SetVertexStream( CreateVB(source.vertexBufferSize, RENDER_POOL_MANAGED, source.vertexBuffer), source.vertexBufferStride );
    pGeometry->SetIndexBuffer( CreateIB(source.indexBufferSize, RENDER_POOL_MANAGED, reinterpret_cast<UINT*>(source.indexBuffer)) );
    pGeometry->SetVertexDeclaration( source.pVtxDecl );
  }

	return true;
}

void ConvertTerrainElementGeometry(TerrainElementGeometryRaw& data)
{
  static DummyAllocator allocator(20U * 1024U * 1024U);

  allocator.Clear();

  if (data.version == 1U)
    return;

  ASSERT(data.vertexBufferStride == sizeof(TerrainElementStride));
  ASSERT(data.vertexBufferSize > 0);
  ASSERT(data.indexBufferSize > 0);

  const H6GeometryFileHeader* const src_header = reinterpret_cast<const H6GeometryFileHeader*>(data.rawData);

  ASSERT(src_header->fragmentCount == 1);

  const unsigned vertexCount = data.vertexBufferSize / data.vertexBufferStride;

  void* const memory = allocator.Allocate(sizeof(H6GeometryFileHeader), 16);

  H6GeometryFileHeader* const header = reinterpret_cast<H6GeometryFileHeader*>(memory);

  header->signature = Signs::telmSIGN;
  header->fragmentCount = src_header->fragmentCount;
  header->materialCount = src_header->materialCount;
  header->commonVertexBufferSizeInBytes = vertexCount * sizeof(TerrainElementStrideNew);
  header->commonIndexBufferSizeInBytes = src_header->commonIndexBufferSizeInBytes;
  header->vbOffset = 0;
  header->ibOffset = 0;
  header->reindexOffset = 0;
  header->jointsCount = 0;
  header->fragments.resize(1, &allocator);

  {
    const H6FragmentHeader& src_fragment = src_header->fragments[0];

    H6FragmentHeader& fragment = header->fragments[0];

    fragment.vertexStrideSizeInBytes = sizeof(TerrainElementStrideNew);
    fragment.baseVertexIndex = src_fragment.baseVertexIndex;
    fragment.minIndex = src_fragment.minIndex;
    fragment.numVertices = src_fragment.numVertices;
    fragment.startIndex = src_fragment.startIndex;
    fragment.primitiveCount = src_fragment.primitiveCount;
    fragment.materialID = src_fragment.materialID;
    fragment.streamOffset = src_fragment.streamOffset;

    fragment.vertexElementDescriptor.resize(6, &allocator);
    fragment.vertexElementDescriptor[0] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, position),  Render::VERTEXELEMENTTYPE_FLOAT3,   Render::VERETEXELEMENTUSAGE_POSITION, 0U);
    fragment.vertexElementDescriptor[1] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, normal),    Render::VERTEXELEMENTTYPE_FLOAT3,   Render::VERETEXELEMENTUSAGE_NORMAL,   0U);
    fragment.vertexElementDescriptor[2] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, texcoord0), Render::VERTEXELEMENTTYPE_FLOAT2,   Render::VERETEXELEMENTUSAGE_TEXCOORD, 0U);
    fragment.vertexElementDescriptor[3] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, color0),    Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR,    0U);
    fragment.vertexElementDescriptor[4] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, color1),    Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR,    1U);
    fragment.vertexElementDescriptor[5] = Render::VertexElementDescriptor(0U, offsetof(TerrainElementStrideNew, mask),      Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR,    2U);
  }

  allocator.Normalize(16);

  // NOTE: no more allocations

  header->vbOffset = allocator.GetSize();
  header->ibOffset = header->vbOffset + header->commonVertexBufferSizeInBytes;

  {
    const TerrainElementStride* const src_vb = reinterpret_cast<const TerrainElementStride*>(data.vertexBuffer);

    TerrainElementStrideNew* const vb = reinterpret_cast<TerrainElementStrideNew*>(reinterpret_cast<char*>(memory) + header->vbOffset);

    for (unsigned i = 0; i < vertexCount; ++i)
    {
      const TerrainElementStride& src_v = src_vb[i];

      TerrainElementStrideNew& v = vb[i];

      v.position = src_v.position;
      v.normal = src_v.normal;
      v.texcoord0 = src_v.texcoord0;
      v.color0 = src_v.color;
      v.color1 = src_v.color;
      v.mask = src_v.mask;
    }
  }

  {
    const unsigned* const src_ib = reinterpret_cast<const unsigned*>(data.indexBuffer);

    unsigned* const ib = reinterpret_cast<unsigned*>(reinterpret_cast<char*>(memory) + header->ibOffset);

    memcpy(ib, src_ib, header->commonIndexBufferSizeInBytes);
  }

  data.version = 1U;

  // load raw data
  data.rawData = reinterpret_cast<char*>(const_cast<void*>(allocator.GetData()));
  data.rawDataSize = header->ibOffset + header->commonIndexBufferSizeInBytes;

  // load vertex buffer
  data.vertexBuffer = data.rawData + header->vbOffset;
  data.vertexBufferSize = header->commonVertexBufferSizeInBytes;
  data.vertexBufferStride = sizeof(TerrainElementStrideNew);

  // load index buffer
  data.indexBuffer = data.rawData + header->ibOffset;
  data.indexBufferSize = header->commonIndexBufferSizeInBytes;

  // load vertex format declaration
  {
    VertexFormatDescriptor formatDescriptor;

    formatDescriptor.AssignVertexElements( header->fragments[0].vertexElementDescriptor[0], header->fragments[0].vertexElementDescriptor.size() );

    data.pVtxDecl = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void UnloadInPlacedBinaries()
{
  UnloadInPlacedPFXWrappers();
  UnloadInPlacedSkeletalAnimationWrappers();
  UnloadSkeletalMeshWrappers();
  ///memory
	memoryPool.Release();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetTypeId( const string& typeName, const int typeId )
{
  string fileName = "Shaders/UberShaders/" + typeName;
  TMultyShaderPool::iterator it = GetMultishaderPool().find( fileName );

  if ( it != GetMultishaderPool().end() )
    return;

  GetMultishaderTypeIdPool()[typeId] = shaderIndex;

  GetMultishaderPool()[ fileName ] = shaderIndex;
  shaderIndex++;
//  multyShaderIndexPool.push_back( new Materials::MultiShader( fileName ) );
}

int GetShaderIndexByTypeId(const int typeId)
{
  TMultyShaderTypeIdPool::iterator it = GetMultishaderTypeIdPool().find( typeId );
  if ( it != GetMultishaderTypeIdPool().end() )
    return it->second;

  return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Render::Materials::MultiShader* GetMultiShader( int index )
{
	ASSERT(GetMultishaderIndexPool()[index]);		
	return GetMultishaderIndexPool()[index];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ReloadShader( int index )
{
	ASSERT(GetMultishaderIndexPool()[index]);
	GetMultishaderIndexPool()[index]->ReloadShaders();
}
//////////////////////////////////////////////////////////////////////////
void ReloadTextures()
{
	
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void ReloadShaders()
{
	if(!shadersToReload.size())
		return;
	for(vector<int>::const_iterator it = shadersToReload.begin(); it != shadersToReload.end(); ++it)
	{
		const int index = *it;
		NI_VERIFY(GetMultishaderIndexPool()[index], "no such shader loaded", continue; );
		ReloadShader(index);
		systemLog( NLogg::LEVEL_MESSAGE ) << GetMultishaderIndexPool()[index]->GetShaderName() << " has been reloaded" << endl;
	}
	shadersToReload.resize(0);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void UnloadShaders()
{
	for ( TMultyShaderIndexPool::iterator it = GetMultishaderIndexPool().begin(); it != GetMultishaderIndexPool().end(); ++it )
		delete *it;
	GetMultishaderPool().clear();
	GetMultishaderIndexPool().clear();

	Materials::MultiShader::ReleaseDefaultShaderPair();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Init()
{
  shadersToReload.reserve(10);
	memoryPool.Initialize( "megapool" );
	GetMultishaderIndexPool().clear();

	render_ShaderCompile.Start();
	Materials::MultiShader::InitializeDefaultShaderPair();
  GetMultishaderIndexPool().resize(shaderIndex);
  for ( TMultyShaderPool::iterator it = GetMultishaderPool().begin(); it != GetMultishaderPool().end(); it++ )
  {
    GetMultishaderIndexPool()[it->second] = new Materials::MultiShader( it->first );
  }
	//RegisterShaders();
	render_ShaderCompile.Stop();

	pDefaultStaticMeshGeometry = LoadMeshGeometryFromFile( "/Tech/Default/Default.stat", false, false );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Release()
{
	UnloadInPlacedBinaries();

	UnloadShaders();
	UnloadMeshGeometry();

	delete pDefaultStaticMeshGeometry;
	delete pDefaultSkeletalMeshGeometry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

static bool ReloadShaderCmd( const char *name, const vector<wstring>& params )
{
	if ( params.empty() )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << " list of loaded shaders : " << endl;
		for(TMultyShaderPool::iterator it = GetMultishaderPool().begin(); it != GetMultishaderPool().end(); ++it)
		{
			systemLog( NLogg::LEVEL_MESSAGE ) << it->second << " : " << it->first << endl;
		}
		return true;
	}
	
	const wstring& param = params[0];
	if(param.size() < 2 )
	{
		const int index = NStr::ToInt(param);
		if(GetMultishaderIndexPool()[index])
		{
			systemLog( NLogg::LEVEL_MESSAGE ) << GetMultishaderIndexPool()[index]->GetShaderName() << " shader was invalidated ... " << endl;
			shadersToReload.push_back(index);
		}
		else
		{
			systemLog( NLogg::LEVEL_MESSAGE ) << "#" << index << " : no such shader was loaded! " << endl;
		}

		return true;
	}

	return true;
}

void DeferredReloadShaders()
{
	for(TMultyShaderPool::iterator it = GetMultishaderPool().begin(); it != GetMultishaderPool().end(); ++it)
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << " send request on reload: " << it->first << endl;
		shadersToReload.push_back(it->second);
	}
}

//========================================================================================================

void FrameTick()
{ // ASL: Yeah, I know - this is disgusting. Yet I don't want to mess with virtual methods, heap etc.
  meshGeometryLoader.MoveMarkedInPool();
  instMeshGeometryLoader.MoveMarkedInPool();
  partFXLoader.MoveMarkedInPool();
  skeletonLoader.MoveMarkedInPool();
  animationLoader.MoveMarkedInPool();

  TickTextureManager();
}

void MarkAsSecondaryThread()
{
  BasicPoolFinder::MarkAsSecondaryThread();
}

bool IsSecondaryThread()
{
  return BasicPoolFinder::IsSecondaryThread();
}

//========================================================================================================

static bool ReloadShadersCmd( const char *name, const vector<wstring>& params )
{
	DeferredReloadShaders();
  return true;
}

static bool ReloadGeometryCmd( const char *name, const vector<wstring>& params )
{
  ReloadGeometry( true );
  return true;
}

static bool ReloadSkeletonCmd( const char *name, const vector<wstring>& params )
{
  ReloadSkeletons( true );
  return true;
}

static bool ReloadPFXCmd( const char *name, const vector<wstring>& params )
{
  ReloadPFXNew( true );
  return true;
}

static bool ReloadAnimCmd( const char *name, const vector<wstring>& params )
{
  ReloadAnims( true );
  return true;
}


//==========================================================================================================
void CopyElementGeometry( TerrainElementGeometryRaw* _pRawData, bool _consolidate )
{
  char* data = (char*)Aligned_MAlloc(_pRawData->rawDataSize, 4); // We don't need any specific alignment; however, I want to use nedmalloc
  memcpy(data, _pRawData->rawData, _pRawData->rawDataSize);
  const int vbOffset = _pRawData->vertexBuffer - _pRawData->rawData;
  const int ibOffset = _pRawData->indexBuffer - _pRawData->rawData;

  NI_ASSERT( vbOffset > 0, "Invalid vb offset!" );
  NI_ASSERT( ibOffset > 0 && ibOffset > vbOffset, "Invalid ib offset!" );

  _pRawData->rawData = data;
  _pRawData->vertexBuffer = data + vbOffset;
  _pRawData->indexBuffer  = data + ibOffset;

  if(s_clean_terrain_geometry) {
    const uint vbSizeOld = _pRawData->vertexBufferSize;
    const uint ibSizeOld = _pRawData->indexBufferSize;

    CleanGeometry<unsigned>(*_pRawData, *_pRawData);

    if(_consolidate) {
      const bool vbSizeChanged = (vbSizeOld != _pRawData->vertexBufferSize);
      if(vbSizeChanged) {
        char* const dest = _pRawData->vertexBuffer + _pRawData->vertexBufferSize;
        NI_ASSERT( _pRawData->vertexBuffer + vbSizeOld == _pRawData->indexBuffer, "Wrong assumption about IB location" );
        memmove(dest, _pRawData->indexBuffer, _pRawData->indexBufferSize);
        _pRawData->indexBuffer = dest;
      }

      if(vbSizeChanged || ibSizeOld != _pRawData->indexBufferSize)
      {
        const int newSize = _pRawData->indexBuffer - _pRawData->rawData + _pRawData->indexBufferSize;
        _pRawData->rawData = (char*)Realloc(_pRawData->rawData, newSize);
        _pRawData->rawDataSize = newSize;
        _pRawData->vertexBuffer = _pRawData->rawData + vbOffset;
        _pRawData->indexBuffer = _pRawData->vertexBuffer + _pRawData->vertexBufferSize;
      }
#ifdef _DEBUG
      const unsigned* const pIndices = (const unsigned*)_pRawData->indexBuffer;
      const unsigned  numVertices = _pRawData->vertexBufferSize / _pRawData->vertexBufferStride;
      const unsigned  numIndices = _pRawData->indexBufferSize / 4;
      for(UINT i = 0; i < numIndices; ++i) {
        NI_VERIFY(pIndices[i] < numVertices, "RemoveDuplicateVertices: wrong indices", continue);
      }
#endif // _DEBUG
    }

    // modify RawData header
    H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<H6GeometryFileHeader*>(_pRawData->rawData);
    pH6GeometryFileHeader->commonIndexBufferSizeInBytes = _pRawData->indexBufferSize;
    pH6GeometryFileHeader->commonVertexBufferSizeInBytes = _pRawData->vertexBufferSize;
    if(_consolidate)
      pH6GeometryFileHeader->ibOffset = pH6GeometryFileHeader->vbOffset + pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // RenderResourceManager
}; // namespace Render



REGISTER_DEV_CMD( reloadshader, Render::RenderResourceManager::ReloadShaderCmd );
REGISTER_DEV_CMD( reloadshaders, Render::RenderResourceManager::ReloadShadersCmd );

REGISTER_DEV_CMD( reloadgeometry, Render::RenderResourceManager::ReloadGeometryCmd );
REGISTER_DEV_CMD( reloadskeleton, Render::RenderResourceManager::ReloadSkeletonCmd );
REGISTER_DEV_CMD( reloadpfx,      Render::RenderResourceManager::ReloadPFXCmd );
REGISTER_DEV_CMD( reloadanim,     Render::RenderResourceManager::ReloadAnimCmd );
