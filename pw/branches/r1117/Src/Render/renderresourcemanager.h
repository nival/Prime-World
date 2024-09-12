
#pragma once


#include "../System/2Darray.h"

#include "dxutils.h"
#include "texture.h"
#include "renderformat.h"

struct SkeletonData;
struct SkeletalAnimationData;
struct SkeletalAnimationDataWrapper;
struct PFXBinaryFileWrapper;
struct SkeletonDataWrapper;

static const uint BLOOMDOWNSCALEFACTOR = 2;
static const uint WARFOGUPSCALEFACTOR = 4;

namespace Render
{
namespace Materials 
{
	class MultiShader;
}

struct MeshGeometry;
class  InstancedMeshGeometry;
struct TerrainElementGeometryRaw;
class Primitive;
class PrimitiveWithAddonStream;
class RenderSurface;

namespace RenderResourceManager
{

void Init();
void Release();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkeletonDataWrapper* LoadSkeletonData( const nstl::string& filename );
const PFXBinaryFileWrapper* LoadPFXData( const nstl::string& filename );

// common functions to load mesh geometry from file
const MeshGeometry* LoadStaticMeshGeometry( const nstl::string& filename, bool appendColorStream );
const MeshGeometry* LoadSkeletalMeshGeometry( const nstl::string& filename );
InstancedMeshGeometry* LoadInstancedMeshGeometry( const nstl::string& filename );

// Load geometry directly from memory stream.
// Warning! No pools, no caching, no reload, caller is responsible for destroy.
MeshGeometry* LoadMeshGeometry( const char *pData, bool bSkeletalMesh, bool appendColorStream );

// Save geometry to stream
void SaveMeshGeometry( MeshGeometry const *pGeometry, Stream *pStream );

const SkeletalAnimationDataWrapper* LoadSkeletalAnimation(const nstl::string& filename);

//void SetMultiShadersCount( int count );
//void RegisterMultiShader( const nstl::string& fileName, int index );
Render::Materials::MultiShader* GetMultiShader( int index );
void SetTypeId( const string& typeName, const int typeId );
int GetShaderIndexByTypeId(const int typeId);

//void ReloadShader( int index );


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MeshGeometry* GetDefaultStaticMeshGeometry();
const MeshGeometry* GetDefaultSkeletalMeshGeometry();

//bool LoadTerrainFragmentGeometry( const nstl::string& filename, TerrainFragmentGeometry* pGeometry );

/** load raw data for terrain geometry, memory will be destroyed with stream */
bool GetTerrainElementGeometryRawData( Stream* pStream, TerrainElementGeometryRaw* pRawData );
/** load geometry and copy to new buffer */
bool CreateTerrainElementRawData( Stream* pStream, TerrainElementGeometryRaw* pRawData );

bool CheckTerrainElementGeometryRawDataVersion(const TerrainElementGeometryRaw& geometry);

void CopyElementGeometry( TerrainElementGeometryRaw* _pRawData, bool _consolidate = true );
/** create dx resources from raw data */
bool CreateTerrainFragmentGeometry( Primitive* pGeometry, const TerrainElementGeometryRaw& source );

void ConvertTerrainElementGeometry(TerrainElementGeometryRaw& data);

void DeferredReloadShaders();

void ReloadShaders();
void ReloadTextures();
void ReloadGeometry( bool bModifiedOnly );
void ReloadSkeletons( bool bModifiedOnly );
void ReloadPFXNew( bool bModifiedOnly );
void ReloadAnims( bool bModifiedOnly );

void MarkAsDirtyGeometry(const nstl::string& filename);
void MarkAsDirtyPFX(const nstl::string& filename);
void MarkAsDirtySkeletonData(const nstl::string& filename);
void MarkAsDirtySkeletonAnim(const nstl::string& filename);

void FrameTick();
void MarkAsSecondaryThread();
bool IsSecondaryThread();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // RenderResourceManager
}; // namespace Render
