#include "stdafx.h"

#include "../System/BoundCalcer.h"
#include "../System/lerp.h"
#include "../System/staticvector.h"

#include "../System/InlineProfiler.h"

#include "ParticleFX.h"
#include "debugrenderer.h"
#include "ConvexVolume.h"
#include "batch.h"
#include "renderresourcemanager.h"
#include "SkeletalMesh.h"
#include "smartrenderer.h"
#include "sceneconstants.h"
#include "SkeletonWrapper.h"
#include "GlobalMasks.h"
#include "../MeshConverter/ParticleNewHeader.h"
#include "DXUtils.h"
#include "IConfigManager.h"

static const short g_ParticlePivotOffset = 16380;
static const int   MAX_PARTICLES = 8192; // Up to 16K

static bool g_rndSwitch_PFX = true;
REGISTER_DEV_VAR( "rnd_PFX", g_rndSwitch_PFX, STORAGE_NONE );

//static bool s_dbgEatMemory = false;
//REGISTER_DEV_VAR( "debug_EatMemory", s_dbgEatMemory, STORAGE_NONE );

static NDebug::DebugVar<int> render_PFX_Update( "PFX_Update", "PerfCnt", true );
static NDebug::DebugVar<int> render_PFX_Render( "PFX_Render", "PerfCnt", true );
static NDebug::DebugVar<int> render_PFX_Count( "PFX_Count", "PerfCnt", true );
static NDebug::DebugVar<int> render_PFX_VBSize( "PFX_VBSize", "PerfCnt", true );
static NDebug::AverageDebugVar<int> render_PFX_AvgCount( "PFX_CountAvg", "PerfCnt" );

static NDebug::PerformanceDebugVar render_PFX_UpdateTime( "PFX_UpdateTime", "PerfCnt", 10, 10, true );

//static bool useHWInstancing = true;
//REGISTER_DEV_VAR("useHWI", useHWInstancing, STORAGE_NONE)

#define useHWInstancing (!Compatibility::IsRunnedUnderWine())

DECLARE_NULL_RENDER_FLAG

template<class T>
__forceinline bool chain_less(T _lhs, T _rhs, bool _next = false)
{
  if(_lhs == _rhs)
    return _next;
  else
    return _lhs < _rhs;
}

namespace Render
{

struct ParticleVertexSW
{
  CVec3 Position;         //12
  CVec3 Direction;        //12
  CVec4 UV;               //16
  CVec3 RotationAndSize;  //12
  CVec4 Color;            //16
};

struct ParticleVertexHW
{
  CVec4 PositionAndID;      //16
  CVec4 DirectionAndOrient; //16
  CVec4 UV;                 //16
  CVec3 RotationAndSize;    //12
  CVec4 Color;              //16

  ParticleVertexHW(ParticleVertexSW const &_src, float _pfxID, float _orient)
    : PositionAndID(_src.Position, _pfxID), DirectionAndOrient(_src.Direction, _orient)
    , UV(_src.UV), RotationAndSize(_src.RotationAndSize), Color(_src.Color)
  {}
};

struct ParticleVertexHWnoHWI : ParticleVertexSW
{
  DWORD CornerMasks;
};

static const int SW_PART_SIZE = sizeof(ParticleVertexSW);

struct ParticleIndex
{
  int   indices;  // ID of particle + (ID of particle system in MSByte)
  float distance;

  bool operator<(const ParticleIndex& v) const
  {
    return distance > v.distance;
  }
};

struct CompositeParticleIndex : ParticleIndex
{
  static int const SUBPRIORITY_SHIFT = (8 * sizeof(int) - Material::SUBPRIORITY_SIZE);
  static int const SYS_ID_SIZE = 9;
  static int const PART_ID_SIZE = SUBPRIORITY_SHIFT - SYS_ID_SIZE;
  static int const SUBPRIORITY_MASK = -1 << SUBPRIORITY_SHIFT;
  static int const SYS_ID_MASK = (1 << SYS_ID_SIZE) - 1;
  static int const PART_ID_MASK = (1 << PART_ID_SIZE) - 1;

  void ComposeIndex(int _subPriority, UINT _sysID, UINT _partID)
  {
    ASSERT(_sysID < SYS_ID_MASK);
    ASSERT(_partID < PART_ID_MASK);
    indices = (_subPriority << SUBPRIORITY_SHIFT) | (_sysID << PART_ID_SIZE) | _partID;
    ASSERT(_subPriority == (indices >> SUBPRIORITY_SHIFT));
  }

  int MaskNonPriority() { return indices & SUBPRIORITY_MASK; }

  int GetSubPriority() { return indices >> SUBPRIORITY_SHIFT; }
  UINT GetSysId()  { return (indices >> PART_ID_SIZE) & SYS_ID_MASK; }
  UINT GetPartId() { return  indices & PART_ID_MASK; }

  bool operator<(const CompositeParticleIndex& v) const
  {
    if(distance == v.distance)
      return (indices & SUBPRIORITY_MASK) > (v.indices & SUBPRIORITY_MASK);
    else
      return distance > v.distance;
  }
};

namespace
{

template<class T>
void insertSort(T a[], long size)
{
	T x;
	long i, j;

	// цикл проходов, i - номер прохода
	for ( i = 0; i < size; i++ ) 
	{
		x = a[i];

		// поиск места элемента в готовой последовательности 
		for ( j = i - 1; j >= 0 && x < a[j]; j-- )
		{
			a[j+1] = a[j];  	// сдвигаем элемент направо, пока не дошли
		}

		// место найдено, вставить элемент
		a[j+1] = x;
	}
}

// dichotomical search
// returns index of the right end of the interval
unsigned int FindSegment(StaticVector<float> const &sortedVector, float value)
{
  unsigned int left, right, center;
  left = 0;
  right = sortedVector.size();
  
  while (right - left > 1)
  {
    center = (left + right) / 2;
    if ( value <= sortedVector[center] )
    {
      right = center;
    }
    else
    {
      left = center;
    }
  }

  return right;
}

// This should be faster. Unfortunately, it is not.
unsigned int FindSegmentNew(StaticVector<float> const &_sortedVector, float _value)
{
  unsigned left = 0, right = _sortedVector.size();
  int* const pData = (int*)(&_sortedVector[0]);
  int const value = (int&)_value;
  while (right > left + 1)
  {
    unsigned const center = (right + left) >> 1;
    unsigned mask = (pData[center] - value) >> 31; // 0xffffffff if value > sortedVector[center], else 0
    unsigned invmask = ~mask;
    //right = right&mask | center&invmask;
    //left = left&invmask | center&mask;
    right &= mask;
    mask &= center;
    left &= invmask;
    invmask &= center;
    left |= mask;
    right |= invmask;
  }
  return right;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int FindSegmentLerp(StaticVector<float> const &sortedVector, float val, float* lerpCoeff)
{
  unsigned const rightKeyIndex = FindSegment(sortedVector, val);
  const float *pTimeB = &sortedVector[rightKeyIndex], *pTimeA = pTimeB-1;

  float numerator = val - *pTimeA;
  float denominator = *pTimeB - *pTimeA;
  NI_VERIFY( numerator >= 0, "numerator should be > 0", return rightKeyIndex); // move checks to initialization [10/15/2009 smirnov]
  NI_VERIFY( denominator > 0, "denominator should be > 0", return rightKeyIndex);

  *lerpCoeff = numerator / denominator;
  NI_VERIFY( *lerpCoeff >= 0 && *lerpCoeff <= 1, "alpha should be between 0 and 1", return rightKeyIndex);

  return rightKeyIndex;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetPositionOnly( CVec3* pos, CVec3* /*ignored*/, TParticleTracks const& particle, float time )
{
  float lerpCoeff = 0.0f;
  unsigned int rightKeyIndex = FindSegmentLerp(particle.positionTrack.timeData, time, &lerpCoeff);

  StaticVector<CVec3> const& track = particle.positionTrack.trackData;
  pos->Interpolate( track[rightKeyIndex-1], track[rightKeyIndex], lerpCoeff );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetPositionAndSpeed( CVec3* pos, CVec3* speed, TParticleTracks const& particle, float time )
{
  float lerpCoeff = 0.0f;
  unsigned int rightKeyIndex = FindSegmentLerp(particle.positionTrack.timeData, time, &lerpCoeff);

  StaticVector<CVec3> const& track = particle.positionTrack.trackData;
  pos->Interpolate( track[rightKeyIndex-1], track[rightKeyIndex], lerpCoeff );

  speed->Sub(track[rightKeyIndex], track[rightKeyIndex-1]);
  if (rightKeyIndex + 1 < track.size())
    speed->Interpolate( *speed, (track[rightKeyIndex+1] - track[rightKeyIndex]), lerpCoeff );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetRotationAndSize( CVec3* rot, TParticleTracks const& particle, float time )
{
  float lerpCoeff = 0.0f;
  unsigned int rightKeyIndex = FindSegmentLerp(particle.rotationAndScaleTrack.timeData, time, &lerpCoeff);

  StaticVector<CVec3> const& track = particle.rotationAndScaleTrack.trackData;
  rot->Interpolate( track[rightKeyIndex-1], track[rightKeyIndex], lerpCoeff );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetColor( CVec4* color, TParticleTracks const& particle, float time )
{
  float lerpCoeff = 0.0f;
  unsigned int rightKeyIndex = FindSegmentLerp(particle.colorTrack.timeData, time, &lerpCoeff);

  StaticVector<CVec4> const& track = particle.colorTrack.trackData;
  color->Interpolate( track[rightKeyIndex-1], track[rightKeyIndex], lerpCoeff );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetUV( CVec4* uv, nstl::vector<CVec4> const& uvPairs, TParticleTracks const& particle, float time )
{
  unsigned int rightKeyIndex = FindSegment(particle.uvTrack.timeData, time);
	int spriteID = (int)particle.uvTrack.trackData[rightKeyIndex-1];
  uv->Set(spriteID < uvPairs.size() ? uvPairs[spriteID] : VNULL4);
}

}

DECLARE_INSTANCE_COUNTER(ParticleFX);


namespace {
  enum { PARTICLES_VB_SIZE = 0x100000 }; // 1MB
  //enum { PARTICLES_VB_SIZE = 0x40000 }; // 256K
  SharedVB g_ParticlesVB(PARTICLES_VB_SIZE);

  struct InitQuadVB : public IntrusivePtrDeleter
  {
    typedef DXVertexBufferRef Type;

    void Init(DXVertexBufferRef& _result)
    {
      _result = CreateVB(4*sizeof(DWORD), RENDER_POOL_MANAGED);
      NI_VERIFY( _result, "Couldn't create Quad VB", return );

      if( PDWORD const pData = LockVB<DWORD>(::Get(_result), 0) )
      {
        pData[0] = 0x00010100;
        pData[1] = 0x00000101;
        pData[2] = 0x01000001;
        pData[3] = 0x01010000;

        _result->Unlock();
      }
      else
        _result.Attach(0);
    }
  };

  ManagedResource<InitQuadVB> g_QuadVB;

  struct QuadIBInit : public IntrusivePtrDeleter
  {
    typedef DXIndexBufferRef Type;

    static void Init(Type &p)
    {
      if(useHWInstancing)
        InitSingle(p);
      else
        InitMulti(p);
    }

    static void InitSingle(Type &p);
    static void InitMulti(Type &p);
  };

  ManagedResource<QuadIBInit> g_QuadIB;

  void QuadIBInit::InitSingle(Type &p)
  {
    static const WORD indices[6] = { 0, 2, 1,
                                     0, 3, 2 };
    p.Attach( CreateIB16(sizeof(indices), RENDER_POOL_MANAGED, indices).Detach() );
  }

  void QuadIBInit::InitMulti(Type &p)
  {
    const int IB_SIZE = 6 * MAX_PARTICLES;
    static WORD indices[IB_SIZE];

    static bool initialized = false;
    if(!initialized) {
      unsigned quadNum = 0;
      for( int i = 0; i < IB_SIZE; i+=6 )
      {
        indices[i+0] = quadNum * 4 + 0;
        indices[i+1] = quadNum * 4 + 2;
        indices[i+2] = quadNum * 4 + 1;

        indices[i+3] = quadNum * 4 + 0;
        indices[i+4] = quadNum * 4 + 3;
        indices[i+5] = quadNum * 4 + 2;
        ++quadNum;
      }
      initialized = true;
    }

    p.Attach( CreateIB16(sizeof(indices), RENDER_POOL_MANAGED, indices).Detach() );
  }

};

static void InitializeDescriptors(DXVertexDeclarationRef &_pVertexDecl, DipDescriptor &_dipDescr)
{
  VertexFormatDescriptor fd;
  const UINT stream = useHWInstancing ? 1 : 0;
  fd.AddVertexElement( VertexElementDescriptor(stream,  0, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) ); // CVec3 Position;         //12
  fd.AddVertexElement( VertexElementDescriptor(stream, 12, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_NORMAL,   0) ); // CVec3 Direction;        //12
  fd.AddVertexElement( VertexElementDescriptor(stream, 24, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_TEXCOORD, 0) ); // CVec4 UV;               //16
  fd.AddVertexElement( VertexElementDescriptor(stream, 40, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_TEXCOORD, 1) ); // CVec3 RotationAndSize;  //12
  fd.AddVertexElement( VertexElementDescriptor(stream, 52, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_COLOR,    0) ); // CVec4 Color;            //16
  fd.AddVertexElement( VertexElementDescriptor(0,  useHWInstancing ? 0 : 68,
                                               VERTEXELEMENTTYPE_UBYTE4, VERETEXELEMENTUSAGE_TEXCOORD, 2) ); // DWORD CornerMasks;      //4

  _pVertexDecl = SmartRenderer::GetVertexFormatDeclaration( fd );

  // dip descriptor
  _dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  _dipDescr.baseVertexIndex = 0;
  _dipDescr.numVertices = 4;
  _dipDescr.primitiveCount = 2;
  _dipDescr.startIndex = 0;
}

static void InitializeDescriptorsB(DXVertexDeclarationRef &_pVertexDecl, DipDescriptor &_dipDescr)
{
  VertexFormatDescriptor fd;
  fd.AddVertexElement( VertexElementDescriptor(1,  0, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_POSITION, 0) ); // CVec3 Position;         //12
  fd.AddVertexElement( VertexElementDescriptor(1, 16, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_NORMAL,   0) ); // CVec3 Direction;        //12
  fd.AddVertexElement( VertexElementDescriptor(1, 32, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_TEXCOORD, 0) ); // CVec4 UV;               //16
  fd.AddVertexElement( VertexElementDescriptor(1, 48, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_TEXCOORD, 1) ); // CVec3 RotationAndSize;  //12
  fd.AddVertexElement( VertexElementDescriptor(1, 60, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_COLOR,    0) ); // CVec4 Color;            //16
  fd.AddVertexElement( VertexElementDescriptor(0,  0, VERTEXELEMENTTYPE_UBYTE4, VERETEXELEMENTUSAGE_TEXCOORD, 2) ); // DWORD CornerMasks;      //4

  _pVertexDecl = SmartRenderer::GetVertexFormatDeclaration( fd );

  // dip descriptor
  _dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  _dipDescr.baseVertexIndex = 0;
  _dipDescr.numVertices = 4;
  _dipDescr.primitiveCount = 2;
  _dipDescr.startIndex = 0;
}


class ParticlesManager : public DeviceDeleteHandler, public IParticlesManager
{
  static const int PART_SIZE = sizeof(ParticleVertexHW);

  struct PFX_holder
  {
    ParticleFX const * p;
    float sortingValue;

    PFX_holder() {}
    PFX_holder(ParticleFX const * _p) : p(_p) {}
    PFX_holder(ParticleFX const * _p, float _sortingValue) : p(_p), sortingValue(_sortingValue) {}

    bool operator<(const PFX_holder& _rhs) const { return p->GetMaterial()->GetSortId() < _rhs.p->GetMaterial()->GetSortId(); }
    //bool operator<(const PFX_holder& _rhs) const
    //{
    //  const ParticleFXMaterial* const pMat = (ParticleFXMaterial*)(p->GetMaterial());
    //  const ParticleFXMaterial* const p_rMat = (ParticleFXMaterial*)(_rhs.p->GetMaterial());

    //  RenderState const rsLeft  = ParticleFXMaterial::CorrectRS(pMat->renderState);
    //  RenderState const rsRight = ParticleFXMaterial::CorrectRS(p_rMat->renderState);

    //  if( rsLeft.GetBitMask() == rsRight.GetBitMask() )
    //    return pMat->GetDiffuseMap()->GetTexture()->GetDXTexture() < p_rMat->GetDiffuseMap()->GetTexture()->GetDXTexture();
    //  else
    //    return rsLeft.GetBitMask() < rsRight.GetBitMask();

    //  //return  chain_less(pMat->renderState.GetBitMask(), p_rMat->renderState.GetBitMask(),
    //  //  chain_less(pMat->GetDiffuseMap()->GetTexture()->GetDXTexture(), p_rMat->GetDiffuseMap()->GetTexture()->GetDXTexture())
    //  //  );
    //}

    bool operator==(const PFX_holder& _rhs) const { return p->GetMaterial()->GetSortId() == _rhs.p->GetMaterial()->GetSortId(); }
    //bool operator==(const PFX_holder& _rhs) const
    //{
    //  ParticleFXMaterial* const pMat = (ParticleFXMaterial*)(p->GetMaterial());
    //  ParticleFXMaterial* const p_rMat = (ParticleFXMaterial*)(_rhs.p->GetMaterial());

    //  return (ParticleFXMaterial::CorrectRS(pMat->renderState) == ParticleFXMaterial::CorrectRS(p_rMat->renderState)) &&
    //         (pMat->GetDiffuseMap()->GetTexture()->GetDXTexture() == p_rMat->GetDiffuseMap()->GetTexture()->GetDXTexture());
    //}
    bool operator!=(const PFX_holder& _rhs) const { return !operator==(_rhs); }
  };
  typedef vector<PFX_holder> Systems;

  struct PFX_Batch : RenderComponent, IRenderablePrimitive
  {
    Systems systems;
    vector<CVec4> constants;
    SpaceHolder vertexDataHolder;
    UINT activeParticleCount;

    PFX_Batch() : activeParticleCount()
    {
      constants.push_back( CVec4(-g_ParticlePivotOffset,-g_ParticlePivotOffset,
                                  g_ParticlePivotOffset, g_ParticlePivotOffset) / 32767.0f );
    }

    void AddPFX(PFX_holder const &_holder, CompositeParticleIndex* const _pParticlesReindex);
    void CopyParticles(ParticleVertexHW* _dest, CompositeParticleIndex* _pParticlesReindex);
    bool Finalize(BatchQueue* _queue, CompositeParticleIndex* const _pParticlesReindex);
    bool Finalize();
    void CollectConstants();
    void Clear()
    {
      systems.clear();
      constants.resize(1);
      activeParticleCount = 0;
    }

    virtual OcclusionQueries* GetQueries() const { return 0; }
    virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
    virtual void Bind() const;
    virtual void Draw() const;

    virtual GeometryBuffers  GetBuffers() const { GeometryBuffers res = {0}; return res; }
    virtual GeometryStatistics GetStats() const { 
      return GeometryStatistics(0, 0); 
      //return GeometryStatistics(dipDescr.primitiveCount, dipDescr.numVertices); 
    }
  };
  typedef list<PFX_Batch> Batches;  // can't use vector as it invalidates iterators

  Systems systems;
  Batches batches;

  DipDescriptor dipDescr;
  DXVertexDeclarationRef pVertexDecl;
  vector<CompositeParticleIndex> activeParticlesReindex;
  int activeParticleCount;
  int maxSysNum;

  void Init()
  {
    InitializeDescriptorsB(pVertexDecl, dipDescr);
    // next constant depends on PFX_Batch::PrepareRendererAfterMaterial() and PFX_Batch::CollectConstants() implementation
    maxSysNum = (GetIConfigManager()->GetSysInfo().MaxVertexShaderConst - VSHADER_LOCALCONST0) / 5;
    if(maxSysNum > PFX_MAX_INSTANCES)
      maxSysNum = PFX_MAX_INSTANCES;
  }

public:
  ParticlesManager() : activeParticleCount(0)
  {
    Init();
    batches.push_back();
  }

  void Bind(UINT _position) const;
  void Draw(UINT _particleCount) const;

  virtual void AddBatch(Batch *_pBatch);
  virtual void FinalizeBatch()
  {
    if( batches.back().Finalize() )
      batches.push_back();
    else
      batches.back().Clear();
  }
  virtual void RenderToQueue(BatchQueue* _queue);
  virtual void Clear()
  {
    systems.clear();
    batches.clear();
    batches.push_back();
    activeParticleCount = 0;
  }

  void AddFX(ParticleFX* _pFX, float _sortingValue)
  {
    systems.push_back( PFX_holder(_pFX, _sortingValue) );
    activeParticleCount += _pFX->activeParticleCount;
  }

  virtual void OnDeviceDelete()
  {
    pVertexDecl = 0;
    Clear();
  }

  virtual void OnDeviceCreate() { Init(); }
};

IParticlesManager* GetParticlesManager()
{
  static ParticlesManager manager;
  return &manager;
}

static float const orientType[NDb::KnownEnum<NDb::EOrientType>::sizeOf] = {0, 1, 1, 0};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ParticlesManager::PFX_Batch::AddPFX(PFX_holder const &_holder, CompositeParticleIndex* const _pParticlesReindex)
{
  ASSERT(_holder.p);
  ParticleFX const &partFX = *_holder.p;

  const int particleCount = partFX.activeParticleCount;
  ASSERT(systems.size() <= CompositeParticleIndex::SYS_ID_MASK);
  const int sysID = systems.size() << CompositeParticleIndex::PART_ID_SIZE;
  const int subPriority = partFX.pFXMaterial->GetSubPriority();
  const int composedID = (subPriority << CompositeParticleIndex::SUBPRIORITY_SHIFT) | sysID;
  ASSERT(subPriority == (composedID >> CompositeParticleIndex::SUBPRIORITY_SHIFT));
                          
  ParticleIndex* const pFXParticlesReindex = partFX.pActiveParticlesReindex;
  CompositeParticleIndex* const pParticlesReindex = _pParticlesReindex + activeParticleCount;

  for(int i = 0; i < particleCount; ++i)
  {
    pParticlesReindex[i].distance = pFXParticlesReindex[i].distance;
    pParticlesReindex[i].indices = composedID | pFXParticlesReindex[i].indices;
    ASSERT(UINT(pFXParticlesReindex[i].indices) <= CompositeParticleIndex::PART_ID_MASK);
  }
  activeParticleCount += particleCount;
  systems.push_back(_holder);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::PFX_Batch::CopyParticles(ParticleVertexHW* _dest, CompositeParticleIndex* _pParticlesReindex)
{
  for(UINT n = 0; n < activeParticleCount; ++n)
  {
    unsigned const particleId = _pParticlesReindex[n].GetPartId();
    unsigned const pSysId = _pParticlesReindex[n].GetSysId();

    ParticleFX const * const pPartFX = systems[pSysId].p;
    new(_dest++) // Initialize *currVBData with placement new
      ParticleVertexHW(pPartFX->pActiveParticles[particleId], pSysId, orientType[pPartFX->orient]);
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////
inline void ParticlesManager::PFX_Batch::CollectConstants()
{
  CVec3 xPlaneAxisG(SceneConstants::Global().view.GetXAxis3());
  Normalize(&xPlaneAxisG);
  CVec3 yPlaneAxisG(SceneConstants::Global().view.GetYAxis3());
  Normalize(&yPlaneAxisG);

  for(Systems::iterator it = systems.begin(); it != systems.end(); ++it)
  {
    ParticleFX const * const pFX = it->p;
    constants.push_back( CVec4(pFX->camoffset, pFX->scale,
                               pFX->pivot.x * 2.0f, pFX->pivot.y * 2.0f) ); // * 2.0f for pivot moved from shader

    NI_ASSERT(pFX->pFXMaterial && pFX->pFXMaterial->GetDBMaterial()->GetObjectTypeID() == NDb::ParticleFXMaterial::typeId,
              "wrong material in particle FX");
    ParticleFXMaterial* const pMat = static_cast<ParticleFXMaterial*>(pFX->pFXMaterial);

    const float colorScale = pMat->GetScale();
    const bool clearedAlpha = (colorScale < 0);
    float dontMulByAlpha = 1.f;
    bool dontClearAlpha = true;
    switch( pMat->renderState.GetBlendMode() )
    {
    case NDb::BLENDMODE_LERPBYALPHA:
      dontMulByAlpha = 0.f;
      NI_ASSERT( !clearedAlpha, NStr::StrFmt("ALL-WHITE ALPHA is supported only with BLENDMODE_ADDCOLORMULALPHA! "
                                             "material %s", pMat->GetDBMaterial()->GetDBID().GetFileName()) );
      break;
    case NDb::BLENDMODE_ADDCOLOR:
      dontClearAlpha = false; break;
    case NDb::BLENDMODE_ADDCOLORMULALPHA:
      dontClearAlpha = false; dontMulByAlpha = clearedAlpha ? 1.5f : 0.f; break;
    }


    if(pFX->orient == NDb::ORIENTTYPE_PLANE) {
      Matrix43 const &worldMatrix = pFX->worldMatrix;
      CVec3 xPlaneAxis(worldMatrix._11, worldMatrix._21, worldMatrix._31);
      Normalize(&xPlaneAxis);
      constants.push_back( CVec4(xPlaneAxis, dontMulByAlpha) );
      CVec3 yPlaneAxis(worldMatrix._12, worldMatrix._22, worldMatrix._32);
      Normalize(&yPlaneAxis);
      constants.push_back( CVec4(yPlaneAxis, dontClearAlpha) );
    }
    else { // if(pFX->orient == NDb::ORIENTTYPE_NONE)
      constants.push_back( CVec4(xPlaneAxisG, dontMulByAlpha) );
      constants.push_back( CVec4(yPlaneAxisG, dontClearAlpha) );
    }

    HDRColor dmMultiply, dmAdd;
    pMat->ParticleFXMaterial::GetDiffuseMap()->GetMultiplierAndAdd(dmMultiply, dmAdd);

//    NI_DATA_ASSERT( dmAdd.A == 0.f,
//      NStr::StrFmt("Non-zero alpha displacement is not supported in particles! Encountered in %s",
//      pFX->GetDBID()->GetFileName()) );

    float const opacity = pMat->opacity;
    switch( pMat->ParticleFXMaterial::GetOpacityModePin() )
    {
    case NDb::OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY:
      dmMultiply.AsVec3D() *= opacity;
      dmAdd.AsVec3D() *= opacity;
      break;
    case NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY :
      dmMultiply.A *= opacity;
      dmAdd.A *= opacity;
      break;
    }

    constants.push_back((CVec4&)dmMultiply);
    constants.push_back((CVec4&)dmAdd);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int INSERT_SORT_BOUND = 200; // efficiency bound for insertSort

bool ParticlesManager::PFX_Batch::Finalize(BatchQueue* _queue, CompositeParticleIndex* const _pParticlesReindex)
{
  if(activeParticleCount) {
    if( vertexDataHolder.AcquireSpace(activeParticleCount * PART_SIZE, g_ParticlesVB) )
    {
      render_PFX_VBSize.AddValue( vertexDataHolder.GetSize() );

      void* const pVBData = (PBYTE)g_ParticlesVB.GetPointer( vertexDataHolder.GetPosition() );
      ParticleVertexHW* currVBData = (ParticleVertexHW*)pVBData;

      // sort indices
      if(activeParticleCount > INSERT_SORT_BOUND)
        sort(_pParticlesReindex, _pParticlesReindex + activeParticleCount);
      else
        insertSort(_pParticlesReindex, activeParticleCount);
      // copy particles in sorted order
      CopyParticles(currVBData, _pParticlesReindex);
      CollectConstants();

      float sortingValue = FLT_MAX;
      for(Systems::iterator it = systems.begin(); it != systems.end(); ++it)
        if(sortingValue > it->sortingValue)
          sortingValue = it->sortingValue;

      _queue->SetCurrentSortingValue(sortingValue);
      BaseMaterial* const pMat = systems.back().p->GetMaterial();
      _queue->Push(pMat->GetPriority(), this, this, 0, pMat);
      return true;
    }
    else
      OutputDebugString("AcquireSpace failed\n");
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParticlesManager::PFX_Batch::Finalize()
{
  for(Systems::iterator it = systems.begin(); it != systems.end(); ++it)
    activeParticleCount += it->p->activeParticleCount;

  if(activeParticleCount) {
    if( g_ParticlesVB.Lock() &&
        vertexDataHolder.AcquireSpace(activeParticleCount * PART_SIZE, g_ParticlesVB) )
    {
      render_PFX_VBSize.AddValue( vertexDataHolder.GetSize() );

      void* const pVBData = (PBYTE)g_ParticlesVB.GetPointer( vertexDataHolder.GetPosition() );
      ParticleVertexHW* currVBData = (ParticleVertexHW*)pVBData;

      UINT sysID = 0;
      for(Systems::iterator it = systems.begin(); it != systems.end(); ++it, ++sysID)
      {
        const ParticleFX* const pFX = it->p;
        ParticleIndex* pSystemParticlesReindex = pFX->pActiveParticlesReindex;
        int const systemParticlesCount = pFX->activeParticleCount;
        // sort indices
        insertSort(pSystemParticlesReindex, systemParticlesCount);
        float const orient = orientType[pFX->orient];
        float const fSysID = sysID;
        // copy particles in sorted order
        for(ParticleIndex* const reindexBound = pSystemParticlesReindex + systemParticlesCount;
            pSystemParticlesReindex < reindexBound; ++pSystemParticlesReindex)
	        new(currVBData++) // Initialize *currVBData with placement new
	          ParticleVertexHW(pFX->pActiveParticles[pSystemParticlesReindex->indices], fSysID, orient);
      }

      CollectConstants();
      return true;
    }
    else
      OutputDebugString("AcquireSpace failed\n");
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::PFX_Batch::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
  GetRenderer()->SetVertexShaderConstants( VSHADER_LOCALCONST0, constants.size(), constants.begin() );

  ParticleFXMaterial const * const pMat = static_cast<ParticleFXMaterial*>(systems.begin()->p->GetMaterial());
  GetStatesManager()->SetState( ParticleFXMaterial::CorrectRS(pMat->renderState) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::PFX_Batch::Bind() const
{
  if(activeParticleCount && vertexDataHolder.IsValid(g_ParticlesVB) && g_rndSwitch_PFX &&
    GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE)
    ((ParticlesManager*)GetParticlesManager())->Bind( vertexDataHolder.GetPosition() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::PFX_Batch::Draw() const
{
  if(activeParticleCount && vertexDataHolder.IsValid(g_ParticlesVB) && g_rndSwitch_PFX &&
    GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE)
    ((ParticlesManager*)GetParticlesManager())->Draw(activeParticleCount);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class ParticlesManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ParticlesManager::Bind(UINT _position) const
{
  g_ParticlesVB.Unlock();

  SmartRenderer::BindVertexDeclarationRaw( Get(pVertexDecl) );
  SmartRenderer::BindIndexBuffer( g_QuadIB.Get() );

  SmartRenderer::BindVertexBufferRaw( 0, g_QuadVB.Get(), sizeof(DWORD) );
  SmartRenderer::BindVertexBufferRaw( 1, g_ParticlesVB.GetBuffer(), PART_SIZE, _position );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ParticlesManager::Draw(UINT _particleCount) const
{
  SmartRenderer::EnableHardwareInstancing(_particleCount);
  render_PFX_Count.AddValue(_particleCount);

  SmartRenderer::DrawIndexedPrimitive(dipDescr);

  SmartRenderer::DisableHardwareInstancing();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::AddBatch(Batch *_pBatch)
{
  PFX_Batch *pCurrBatch = &batches.back();
  const ParticleFX* const pFX = static_cast<const ParticleFX*>(_pBatch->pOwner);
  bool isBatchEmpty;
  {
    Systems &currSystems = pCurrBatch->systems;
    isBatchEmpty = currSystems.empty();
    if( !isBatchEmpty && (currSystems.back() != PFX_holder(pFX) || currSystems.size() >= maxSysNum) )
    {
      ParticlesManager::FinalizeBatch();
      pCurrBatch = &batches.back();
      isBatchEmpty = true;
    }
  }
  if(isBatchEmpty) {
    _pBatch->pOwner = pCurrBatch;
    _pBatch->pPrimitive = pCurrBatch;
  }
  else
    _pBatch->dontDraw = true;

  pCurrBatch->systems.push_back( PFX_holder(pFX, _pBatch->sortValue) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticlesManager::RenderToQueue(BatchQueue* _queue)
{
  if( systems.empty() )
    return;

#ifdef _DEBUG
  static hash_set<void*> texSet;
#endif

  insertSort( systems.begin(), systems.size() );

  if( g_ParticlesVB.Lock() )
  {
    activeParticlesReindex.clear();
    activeParticlesReindex.resize(activeParticleCount);
    CompositeParticleIndex* const pParticlesReindex = &*activeParticlesReindex.begin();
    //unsigned curSortId = 0;
    ParticleFX const * pBatchFX = 0;

    for(Systems::iterator it = systems.begin(); it != systems.end(); ++it)
    {
      ParticleFX const * const pFX = it->p;
      ASSERT(pFX);
#ifdef _DEBUG
      texSet.insert( ::Get(pFX->GetMaterial()->GetDiffuseMap()->GetTexture()->GetDXTexture()) );
#endif // _DEBUG
      PFX_Batch &currBatch = batches.back();
      //unsigned const sortId = pFX->GetMaterial()->GetSortId();
      //if(sortId == curSortId) {
      if( !pBatchFX || PFX_holder(pBatchFX) == PFX_holder(pFX) )
      {
        currBatch.AddPFX(*it, pParticlesReindex);
        pBatchFX = pFX;
        continue;
      }
      if( currBatch.Finalize(_queue, pParticlesReindex) )
        batches.push_back();
      else
        currBatch.Clear();

      //curSortId = sortId;
      pBatchFX = pFX;
      batches.back().AddPFX(*it, pParticlesReindex);
    }
  }
  batches.back().Finalize( _queue, activeParticlesReindex.begin() );

  activeParticleCount = 0;
#ifdef _DEBUG
  UINT const numBatches = batches.size(), numTex = texSet.size(); numBatches,numTex;
  texSet.clear();
#endif // _DEBUG
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class ParticleFX
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleFX::ParticleFX() : pPFXData(0), pFXMaterial(0), vertexDataHolder(), activeParticleCount(0)
                         , lastTime(0.0f), pivot(0.f,0.f), isFirstPlacement(true), isDying(false)
{
	memset( &oldTime, 0, sizeof(oldTime) );
	memset( &currentTime, 0, sizeof(currentTime) );
	playingSecondTrack = false;
	uvPairs.reserve( 16 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleFX::~ParticleFX()
{
	delete pFXMaterial;
	Aligned_Free(pMemory);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Initialize( const Matrix43& _worldMatrix, const NDb::DBParticleSceneComponent* _pDBPFXInstance, bool doubleBufferred )
{
  currentTime[0] = 0.0f;
  oldTime[0] = 0.0f;

  // save database parameters
  NI_ASSERT( _pDBPFXInstance, "nullptr" );
	camoffset = _pDBPFXInstance->camoffset;
  orient = _pDBPFXInstance->orient;
	pivot = _pDBPFXInstance->pivot;
  isWorldSpace = _pDBPFXInstance->leaveParticlesWhereStarted;
  isDblBuffered = doubleBufferred;

/*  if( NDb::Texture const *pTex = dynamic_cast<NDb::Texture const*>(_pDBPFXInstance->material->DiffuseMap.texture.GetPtr()) )
  {
    string const &name = pTex->textureFileName;
    if(name.find("Flat2BFX") != string::npos && name.find(".dds") != string::npos)
    {
      int a = 0;
      a;
    }
  } */
  pFXMaterial = static_cast<BaseMaterial*>( CreateRenderMaterial( _pDBPFXInstance->material.GetPtr() ) );
	pFXMaterial->SetOrientTypePin( (NDb::OrientTypePin)( (int)orient ) );

  // copy texture coordinates for texture atlas
	uvPairs.resize( _pDBPFXInstance->uvPairs.size() );
  for ( int i = 0; i < uvPairs.size(); ++i )
  {
    NDb::UVPair const& uv = _pDBPFXInstance->uvPairs[i];
    uvPairs[i] = CVec4( uv.uvTopLeft.x, uv.uvTopLeft.y, uv.uvBottomRight.x, uv.uvBottomRight.y );
  }

  // access particle tracks
  pPFXData = RenderResourceManager::LoadPFXData( _pDBPFXInstance->fxFileName );
  if(!pPFXData) {
    particlesCount = 0;
    return;
  }
	particlesCount = pPFXData->GetData()->GetParticleCount();
  particlesMaxCount = isDblBuffered ? 2 * particlesCount : particlesCount;
  NI_ASSERT(particlesMaxCount <= MAX_PARTICLES, "Too small index buffer");
//#ifndef _SHIPPING
//  if(s_dbgEatMemory)
//  particlesMaxCount = 100500;
//#endif // _SHIPPING

  for ( int particleId = 0; particleId < particlesCount; ++particleId )
  {
    const TParticleTracks& particle = pPFXData->GetData()->particlesTracks[particleId];
    for ( unsigned int i = 0; i < particle.uvTrack.trackData.size(); i++ )
    {
      NI_DATA_ASSERT( particle.uvTrack.trackData[i] < uvPairs.size(), NStr::StrFmt( "SpriteID is not valid for %s", _pDBPFXInstance->fxFileName.c_str() ) );
    }
  }

  // allocate memory
  int const matricesSize = isWorldSpace ? particlesMaxCount * sizeof(Matrix43) : 0;
  int const matricesTempSize = isDblBuffered && isWorldSpace ? particlesCount * sizeof(Matrix43) : 0;
  int const verticesSize = particlesMaxCount * SW_PART_SIZE;
  int const indicesSize = particlesMaxCount * sizeof(ParticleIndex);
  int const memorySize = matricesSize + matricesTempSize + verticesSize + indicesSize;
  pMemory = reinterpret_cast<unsigned char*>(Aligned_MAlloc(memorySize, 16));

  // redistribute memory
  unsigned char* ptr = pMemory;
  pParticleMatrix = isWorldSpace ? reinterpret_cast<Matrix43*>(ptr) : 0;
  ptr += matricesSize;
  pParticleMatrixTemp = isDblBuffered && isWorldSpace ? reinterpret_cast<Matrix43*>(ptr) : 0;
  ptr += matricesTempSize;
  pActiveParticles = reinterpret_cast<ParticleVertexSW*>(ptr);
  ptr += verticesSize;
  pActiveParticlesReindex = reinterpret_cast<ParticleIndex*>(ptr);
  ptr += indicesSize;
  NI_ASSERT(ptr == pMemory + memorySize, "Memory distribution has a bug");

  // setup transformations
  SetWorldMatrix(_worldMatrix);

  if ( isWorldSpace )
  {
    for ( int i = 0; i < particlesMaxCount; ++i )
	    pParticleMatrix[i] = worldMatrix;
  }

	newGlobalPos.FromMatrix( worldMatrix );
	oldGlobalPos = newGlobalPos;
  isFirstPlacement = true;

  // setup graphics
	InitializeInternal();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::UpdateScale()
{
	scale = sqrt( worldMatrix._11 * worldMatrix._11 + worldMatrix._12 * worldMatrix._12 + worldMatrix._13 * worldMatrix._13 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::SetWorldMatrix( const Matrix43& transform )
{ 
	NI_ASSERT(transform.IsFinite(), "Bad matrix passed");
	worldMatrix = transform; 
	UpdateScale();

  if (isFirstPlacement) // matrix is wrong on Reinit(), so override position here
  {
    newGlobalPos.FromMatrix( worldMatrix );
    isFirstPlacement = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::SetMaterial( BaseMaterial* pMaterial )  
{ 
	NI_VERIFY( pMaterial, "null ptr to material", return ); 
	delete pFXMaterial; 
	pFXMaterial = pMaterial; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Reinit()
{
	currentTime[0] = currentTime[1] = 0.0f;
	oldTime[0] = oldTime[1] = 0.0f;
	lastTime = 0.0f;
	activeParticleCount = 0;
	playingSecondTrack = false;
  isFirstPlacement = true;
  isDying = false;
	UpdateScale(); // is it necessary? [10/27/2009 smirnov]
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ParticleFX::GetTotalTime() const
{
  return pPFXData ? pPFXData->GetData()->header.duration : 0.f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::InitializeInternal()
{
	NI_STATIC_ASSERT( sizeof( ParticleVertexHWnoHWI ) == 72, omg_stride_wrong );

  render_PFX_VBSize.AddValue(vertexDataHolder.GetSize());
  RenderState renderState = ((ParticleFXMaterial*)(pFXMaterial))->renderState;
  //if(renderState.GetBlendMode() == NDb::BLENDMODE_MULCOLOR || renderState.GetBlendMode() == NDb::BLENDMODE_MULINVCOLOR)
  //   renderState = renderState;

  InitializeDescriptors(pVertexDecl, dipDescr);

  activeParticleIndices.resize( particlesMaxCount );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Sorting( void* _pVBData )
{
  insertSort( pActiveParticlesReindex, activeParticleCount );
  // sort indices
  if(useHWInstancing)
  {
    ParticleVertexSW* const pVBData = (ParticleVertexSW*)_pVBData;
    // copy particles in sorted order
	  for(int idx = 0; idx < activeParticleCount; ++idx)
	  {
      const int i = pActiveParticlesReindex[idx].indices;
		  memcpy(&pVBData[idx], &pActiveParticles[i], sizeof(ParticleVertexSW));
    }
  }
  else
  {
    // copy particles in sorted order
    ParticleVertexHWnoHWI* const pVBData = (ParticleVertexHWnoHWI*)_pVBData;
	  for(int idx = 0; idx < activeParticleCount; ++idx)
	  {
      ParticleVertexHWnoHWI* pVertices = pVBData + idx * 4;

      int i = pActiveParticlesReindex[idx].indices;

		  memcpy(&pVertices[0], &pActiveParticles[i], sizeof(ParticleVertexSW));
      memcpy(&pVertices[1], &pActiveParticles[i], sizeof(ParticleVertexSW));
      memcpy(&pVertices[2], &pActiveParticles[i], sizeof(ParticleVertexSW));
      memcpy(&pVertices[3], &pActiveParticles[i], sizeof(ParticleVertexSW));

      pVertices[0].CornerMasks = 0x00010100;
      pVertices[1].CornerMasks = 0x00000101;
      pVertices[2].CornerMasks = 0x01000001;
      pVertices[3].CornerMasks = 0x01010000;
    }
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Sampling( int groupId, CVec3 const& cameraPos, const CVec3& addSpeed )
{
  NI_PROFILE_FUNCTION

  if(!pPFXData)
    return;

  float const time = currentTime[groupId];
  float const timeOld = oldTime[groupId];

  // choose right functor
  void (*pGetPositionAndSpeed)(CVec3*, CVec3*, TParticleTracks const&, float) = (orient == NDb::ORIENTTYPE_SPEED ? &GetPositionAndSpeed : &GetPositionOnly);

  const PFXBinaryFileWrapper::value_type* const pData = pPFXData->GetData();
  NI_VERIFY( pData, "Invalid pPFXData", return );

  int idx = activeParticleCount;
  for ( int particleId = 0; particleId < particlesCount; ++particleId )
  {
    const TParticleTracks& particle = pData->particlesTracks[particleId];
                                      
    int particleOffset = particleId + groupId * particlesCount;
    activeParticleIndices[particleOffset] = -1;

    // skip dead particles
    if (!( particle.beginTime <= time && time <= particle.endTime ) )
      continue;

    // recalculate matrix if the particle just appeared
    if (isWorldSpace && timeOld < particle.beginTime )
    {
      // interpolate placement
      float t = 1.f;
      NI_ASSERT( time >= timeOld, "Time backward");
      if ( time - timeOld > 1e-5f )
        t = (particle.beginTime - timeOld) / (time - timeOld);

      Placement place;
      place.Interpolate(oldGlobalPos, newGlobalPos, t);
      place.GetMatrix(&pParticleMatrix[particleOffset]);
    }

    ParticleVertexSW* const __restrict pVertices = pActiveParticles + idx;

    (*pGetPositionAndSpeed)( &pVertices->Position, &pVertices->Direction, particle, time );
    GetRotationAndSize( &pVertices->RotationAndSize, particle, time );
    GetColor( &pVertices->Color, particle, time );
    GetUV( &pVertices->UV, uvPairs, particle, time );

    // adjust position
    Matrix43 const& xformMatrix = isWorldSpace ? pParticleMatrix[particleOffset] : worldMatrix;
    pVertices->Position = Transform(pVertices->Position, xformMatrix);
    NI_ASSERT(pVertices->Position.IsFinite(), "Bad particle position");

    // adjust speed
    switch (orient)
    {
    case NDb::ORIENTTYPE_SPEED:
      pVertices->Direction = Rotate(pVertices->Direction, xformMatrix);
      pVertices->Direction += addSpeed;
      Normalize(&pVertices->Direction);
      break;
    case NDb::ORIENTTYPE_AXIS:
      pVertices->Direction = Rotate(V3_AXIS_Z, xformMatrix);
      Normalize(&pVertices->Direction);
      break;
    default:
      pVertices->Direction = VNULL3;
      break;
    }

    pActiveParticlesReindex[idx].indices = idx;
    pActiveParticlesReindex[idx].distance = fabs2( pVertices->Position - cameraPos );

    activeParticleIndices[particleOffset] = idx;
    ++idx;
  }

  // number of particles stored
  activeParticleCount = Min(idx, MAX_PARTICLES);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::RenderToQueue( BatchQueue& queue )
{
  if (!activeParticleCount)
    return;

  if(!useHWInstancing)
  {
    dipDescr.numVertices = 4 * activeParticleCount;
    dipDescr.primitiveCount = 2 * activeParticleCount;
  }
  render_PFX_Render.AddValue(1);

	const int priority = pFXMaterial->GetPriority();
  queue.Push( priority, this, this, 0, pFXMaterial ); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::OnTimeLooped(float time, float time2StartWith)
{
  if ( !isDying )
  {
	  if ( isDblBuffered && (time < GetTotalTime() || playingSecondTrack) )
	  { // We didn't finished one track and thus have to start another one (or we already playing 2 tracks)
  		
		  // Copy buffer
		  if (playingSecondTrack)
		  {
        if ( isWorldSpace )
        {
          memcpy( pParticleMatrixTemp, pParticleMatrix, particlesCount * sizeof( Matrix43 ) );
          memcpy( pParticleMatrix, &pParticleMatrix[particlesCount], particlesCount*sizeof( Matrix43 ) );
          memcpy( &pParticleMatrix[particlesCount], pParticleMatrixTemp, particlesCount*sizeof( Matrix43 ) );
        }
			  oldTime[0] = oldTime[1];
			  currentTime[0] = currentTime[1];
		  }

		  // Activate additional channel
		  playingSecondTrack = true;

		  // Setup new channel
		  oldTime[1] = time2StartWith;
		  currentTime[1] = time2StartWith;
	  }
	  else
	  { // We finished one track and have to restart it
		  oldTime[0] = time2StartWith;
		  currentTime[0] = time2StartWith;
	  }
  }

	// Reset last time to support SetTime()
	lastTime = time2StartWith;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParticleFX::SetTime( float _time )
{
	if ( _time < 0.f ) return false;

	float deltaTime = _time - lastTime;
	NI_ASSERT(deltaTime >= 0.0f, "Logic failed");
	if (deltaTime < 0.001f) 
		return true;

  static const float MAX_TIME_ALLOWED = 1 << 14; // FLT_MAX is not a good choice due to accuracy issues 
  
  float const totalTime = pPFXData ? GetTotalTime() : MAX_TIME_ALLOWED;
  float const maxTime = totalTime - deltaTime;

  if(currentTime[0] <= maxTime) {
    oldTime[0] = currentTime[0];
    currentTime[0] += deltaTime;
  }
  else {
    currentTime[0] = totalTime;
    oldTime[0] = maxTime;
  }

  if(currentTime[1] <= maxTime) {
	  oldTime[1] = currentTime[1];
	  currentTime[1] += deltaTime;
  }
  else {
    currentTime[1] = totalTime;
    oldTime[1] = maxTime;
  }

	//NI_ASSERT(oldTime[0] >= 0.0f && oldTime[1] >= 0.0f, "Logic bug");
	NI_ASSERT(currentTime[0] >= 0.0f && currentTime[1] >= 0.0f, "Logic bug");

	lastTime = _time;
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Update(CVec3 const& cameraPos)
{
  NDebug::PerformanceDebugVarGuard perfGuard(render_PFX_UpdateTime, false);

  activeParticleCount = 0;
  if (!g_rndSwitch_PFX)
		return;
	
  //sampling
	oldGlobalPos = newGlobalPos;
	newGlobalPos.FromMatrix( worldMatrix );
	CVec3 addSpeed = ( newGlobalPos.pos - oldGlobalPos.pos ) / ( currentTime[0] - oldTime[0] );

  Sampling(0, cameraPos, addSpeed);
	if (playingSecondTrack)
		Sampling(1, cameraPos, addSpeed);

  render_PFX_AvgCount.AddValue(activeParticleCount);

  if(GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE && GetMaterial()->GetPriority() != NDb::MATERIALPRIORITY_DISTORTION)
    return;

  // sort
  if( !RENDER_DISABLED && g_ParticlesVB.Lock() )
  {
    const int VERTEX_COUNT_PER_PART = 4;
    const int PART_SIZE = useHWInstancing ? sizeof(ParticleVertexSW) : VERTEX_COUNT_PER_PART * sizeof(ParticleVertexHW);
    if( vertexDataHolder.AcquireSpace(activeParticleCount * PART_SIZE, g_ParticlesVB) )
    {
      render_PFX_VBSize.AddValue( vertexDataHolder.GetSize() );

      void* const pVBData = (PBYTE)g_ParticlesVB.GetPointer( vertexDataHolder.GetPosition() );
      Sorting(pVBData);
    }
    else
      OutputDebugString("AcquireSpace failed\n");
      //NI_ASSERT(success, "AcquireSpace failed");
  }

	// Add particles count
	render_PFX_Update.AddValue(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
  Renderer& renderer = *GetRenderer();
  renderer.SetVertexShaderConstantsVector4( VSHADER_LOCALCONST0, CVec4(-g_ParticlePivotOffset,-g_ParticlePivotOffset,+g_ParticlePivotOffset,+g_ParticlePivotOffset) / 32767.0f );

	CVec4 constants(camoffset, scale, pivot.x * 2.0f, pivot.y * 2.0f); // * 2.0f for pivot moved from shader
	renderer.SetVertexShaderConstantsVector4( VSHADER_LOCALCONST1, constants );

  CVec4 planeAxises[2];
  int   numRegs = 2;
	if (orient == NDb::ORIENTTYPE_PLANE)
	{
		planeAxises[0].Set(worldMatrix._11, worldMatrix._21, worldMatrix._31, 0.0f);
    Normalize(&planeAxises[0]);
		planeAxises[1].Set(worldMatrix._12, worldMatrix._22, worldMatrix._32, 0.0f);
    Normalize(&planeAxises[1]);
	}
  else if (orient == NDb::ORIENTTYPE_NONE) {
		planeAxises[0].Set(SceneConstants::Global().view.GetXAxis3(), 0.0f);
    Normalize(&planeAxises[0]);
		planeAxises[1].Set(SceneConstants::Global().view.GetYAxis3(), 0.0f);
    Normalize(&planeAxises[1]);
	}
  else
    numRegs = 1;

  planeAxises[0].w = ((ParticleFXMaterial*)GetMaterial())->opacity;
  renderer.SetVertexShaderConstants(VSHADER_LOCALCONST2, numRegs, planeAxises);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Bind() const
{
  if( !g_rndSwitch_PFX || GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE ||
      !vertexDataHolder.IsValid(g_ParticlesVB, *GetDBID()) )
    return;

  g_ParticlesVB.Unlock();

  SmartRenderer::BindVertexDeclarationRaw(Get(pVertexDecl));
  SmartRenderer::BindIndexBuffer( g_QuadIB.Get() );

  const size_t vertexSize = useHWInstancing ? sizeof(ParticleVertexSW) : sizeof(ParticleVertexHWnoHWI);
  if(useHWInstancing)
  {
    SmartRenderer::BindVertexBufferRaw( 0, g_QuadVB.Get(), sizeof(DWORD) );
    SmartRenderer::BindVertexBufferRaw( 1, g_ParticlesVB.GetBuffer(), vertexSize, vertexDataHolder.GetPosition() );
  }
  else
    SmartRenderer::BindVertexBufferRaw( 0, g_ParticlesVB.GetBuffer(), vertexSize, vertexDataHolder.GetPosition() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Draw() const
{
  if (!g_rndSwitch_PFX || GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE)
    return;
	if (!vertexDataHolder.IsValid(g_ParticlesVB) || !activeParticleCount)
		return;
	
  if(useHWInstancing)
    SmartRenderer::EnableHardwareInstancing(activeParticleCount);
  render_PFX_Count.AddValue(activeParticleCount);

  SmartRenderer::DrawIndexedPrimitive(dipDescr);

  if( useHWInstancing )
    SmartRenderer::DisableHardwareInstancing();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParticleFX::CalcWorldAABB(AABB &aabb)
{
  BoundCalcer calcer;
	for ( int particleInd = 0; particleInd < activeParticleCount; ++particleInd )
	{
    ParticleVertexSW& particleVertex = pActiveParticles[particleInd];
		float maxSize = Max(particleVertex.RotationAndSize.x, particleVertex.RotationAndSize.y);
		calcer.Add(particleVertex.Position, 0.5f * maxSize);
	}
	
	if (calcer.IsEmpty())
		return false;

  SBound bound;
	calcer.Make( &bound );
	aabb.center   = bound.s.ptCenter;
  aabb.halfSize = bound.ptHalfBox;

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParticleFX::IsParticleActive(int particleNumber) const
{
  if(!pPFXData)
    return false;

  int flowIdx = particleNumber / particlesCount;
  int particleIdx = particleNumber % particlesCount;
  
  const TParticleTracks& track = pPFXData->GetData()->particlesTracks[particleIdx];
  return (track.beginTime <= currentTime[flowIdx] && currentTime[flowIdx] < track.endTime);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::GetParticleWorldPos(int particleNumber, CVec3 &pos) const
{
  if(!pPFXData) {
    pos.Set(0,0,0);
    return;
  }

  int idx = activeParticleIndices[particleNumber];
  
  if (idx >= 0)
  {
    pos = pActiveParticles[idx].Position;
  }
  else
  {
    const TParticleTracks& particle = pPFXData->GetData()->particlesTracks[particleNumber % particlesCount];
    float const time = currentTime[particleNumber / particlesCount];
		GetPositionOnly( &pos, NULL, particle, time );

    Matrix43 const& xformMatrix = isWorldSpace ? pParticleMatrix[ particleNumber ] : worldMatrix;
    pos = Transform( pos, xformMatrix );
  }
}

void ParticleFX::Die()
{
  //DebugTrace("Die!");
  isDying = true;
  //playingSecondTrack = false;
}

bool ParticleFX::Ready2Die()
{
  if ( isDying )
  {
    if ( !isWorldSpace )
    {
      return true;
    }
    else if ( currentTime[0] < GetTotalTime() || currentTime[1] < GetTotalTime() )
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  if ( isWorldSpace )
    return false;

  return true;
}

bool ParticleFX::IsDying()
{
	return isDying;
}

void ParticleFX::SetWorldMatrixForWorldSpace( const Matrix43& transform )
{
	SetWorldMatrix(transform);

	if ( isWorldSpace )
	{
		for ( int i = 0; i < particlesMaxCount; ++i )
			pParticleMatrix[i] = worldMatrix;
	}
}
}
