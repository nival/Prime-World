#include "StdAfx.h"
#include "RoadSceneObject.h"
#include "../Render/MeshResource.h"
#include <Terrain\RoadPrimitive.h>
#include "../Render/debugRenderer.h"
#include "../Render/renderresourcemanager.h"
#include "../Terrain/Terrain.h"

// uncomment this to draw affected terrain elements' bboxes
//#define DEBUG_DRAW_ELEMENTS

#ifdef DEBUG_DRAW_ELEMENTS
namespace
{
  Render::IDebugRender* _debugRenderer_ = NULL;
}
#endif

#define BAKED_FILE_VERSION 0x03
#define BAKED_FILE_SIGN  MAKELONG('DR', BAKED_FILE_VERSION)

namespace NScene
{

DECLARE_NULL_RENDER_FLAG

int RoadSceneObject::s_showGeometry = 1;
int RoadSceneObject::s_showSpline = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

RoadSceneObject::RoadSceneObject( IScene* _pScene, const NDb::Road* _pDBRoad, bool _bEditable ) :
  SceneObject(_pScene),
  Render::RenderComponent(),
  bEditable(_bEditable),
  bDebugGeometry(false),
  pDBRoad(this, &RoadSceneObject::OnDBResourceChanged),
  pGeometry(NULL),
  pMaterialN(NULL),
  needUpdateMask(true)
{
  INIT_RGROUP;
  // keep track of parameters
  NI_ASSERT(_pDBRoad, "NULL pointer passed");
  pDBRoad = _pDBRoad;
  SetDBID(pDBRoad->GetDBID()); // pass to RenderComponent

  Rebuild(true);

  pScene->GetTerrain()->GetGeometryManager().SubscribeOnModification(TerrainModificationCB, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoadSceneObject::~RoadSceneObject()
{
  if (GetScene())
  {
    GetScene()->GetTerrain()->GetGeometryManager().UnsubscribeOnModification(TerrainModificationCB, this);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::RemoveFromScene()
{
  GetScene()->GetTerrain()->GetGeometryManager().UnsubscribeOnModification(TerrainModificationCB, this);
  SceneObject::RemoveFromScene();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::UpdatePins(Render::BaseMaterial* pMaterial)
{
  if (!pMaterial)
    return;
  pMaterial->SetTextureFitPinValue((NDb::BooleanPin)pDBRoad->properties.fit);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::Rebuild(bool useBakedData)
{
  if (!pDBRoad)
    return;

  RebuildSpline();

  bool bGeometry = false;

  if (useBakedData)
  {
    // try to load baked geometry data from file
    bGeometry = Load(pDBRoad->bakedFileName);

    if (bGeometry)
      BuildAABB();
  }

  if (!bGeometry)
  {
    RebuildGeometry();
  }

  // create materials
  Reset(pMaterialN, NULL);
  Reset(pMaterialA, NULL);
  Reset(pMaterialB, NULL);

  if (!pDBRoad->properties.materialN.IsEmpty())
    Reset(pMaterialN, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pDBRoad->properties.materialN ) ));

  if (!pDBRoad->properties.materialA.IsEmpty())
    Reset(pMaterialA, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pDBRoad->properties.materialA ) ));

  if (!pDBRoad->properties.materialB.IsEmpty())
    Reset(pMaterialB, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pDBRoad->properties.materialB ) ));

  UpdatePins(Get(pMaterialN));
  UpdatePins(Get(pMaterialA));
  UpdatePins(Get(pMaterialB));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::OnDBResourceChanged( const NDb::DBID& dbid )
{
  //Do nothing
  //Rebuild(false); //it's incorrect
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoadSceneObject::IsIntersectWith( float terrainX, float terrainY, const CVec3& pickLocation )
{
  if (!Get(pSpline))
    return false;

  return pSpline->IsInside(CVec2(terrainX, terrainY));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter /*= GROUPFLAGS_ALL*/ )
{
  // skip rendering to shadow and reflection
  if (groupFlagsFilter == NScene::SceneComponent::GROUPFLAGS_CASTSHADOW ||
      groupFlagsFilter == NScene::SceneComponent::GROUPFLAGS_REFLECTINWATER)
    return;

  // redirect call to RenderComponent overrides
  RenderToQueue(queue);
  
  // render additional helpers
#ifndef _SHIPPING
  Render::DebugRender debugRenderer;
  RenderDebug(&debugRenderer);
#endif // _SHIPPING
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::RenderDebug( Render::IDebugRender* _debugRenderer )
{
#ifndef _SHIPPING
  Render::Color white(255, 255, 255);

  // draw spline
  if (s_showSpline > 0)
  {
    Terrain::Terrain* pTerrain = GetScene() ? GetScene()->GetTerrain() : NULL;

    // draw sample center line of spline
    nstl::vector<CVec2> samples;
    pSpline->Sample(0.5f, 10.0f, samples);
    CVec3 p0;
    for (int i = 0; i < samples.size(); ++i)
    {
      CVec3 p1(samples[i], 0.f);
      if (pTerrain)
        pTerrain->GetHeight(p1.x, p1.y, &p1.z);

      if (i > 0)
        _debugRenderer->DrawLine3D(p0, p1, white, white, false);

      p0 = p1;
    }

    // draw control points
    int n = (pSpline->GetNumPoints()-3) * s_showSpline;
    for (int i = 0; i <= n; ++i)
    {
      CVec2 p0, p1;
      CVec3 pt = CVec3(pSpline->GetSection((float)i / (float)s_showSpline, p0, p1), 0.0f);
      if (pTerrain)
        pTerrain->GetHeight(pt.x, pt.y, &pt.z);
      if (i % s_showSpline == 0)
        _debugRenderer->DrawCircle3D(pt, 0.25f, 8, white, false);
      _debugRenderer->DrawLine3D(CVec3(p0, pt.z), CVec3(p1, pt.z), white, white, false);
    }
  }
/*
  // draw affected terrain elements
#ifdef DEBUG_DRAW_ELEMENTS
  _debugRenderer_ = _debugRenderer;
  ProcessTerrainElements();
  _debugRenderer_ = NULL;
#endif
*/
#endif // _SHIPPING
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//extern bool g_simpleShaders;

void RoadSceneObject::RenderToQueue( Render::BatchQueue& queue )
{
  if (!pGeometry || !pMaterialN || 0 == s_showGeometry)
    return;

  // add all primitives to the queue
  queue.SetCurrentSortingValue(pDBRoad ? -pDBRoad->properties.priority : 0.0f); // large negative sorting values go first
  if (s_showGeometry == 2)
  {
    // raise debug flag
    pMaterialN->SetDebugPinValue(NDb::BOOLEANPIN_PRESENT);
    bDebugGeometry = true;

    //for (int i = 0, n = pGeometry->primitives.size(); i < n; ++i)
    //  queue.Push(NDb::MATERIALPRIORITY_ROADS, this, pGeometry->primitives[i], 0, Get(pMaterialN));
    queue.Push(NDb::MATERIALPRIORITY_ROADS, this, primitive ? Get(primitive) : pGeometry->primitives[0], 0, Get(pMaterialN));
  }
  else
  {
    // drop the debug flag
    if (bDebugGeometry)
    {
      pMaterialN->SetDebugPinValue(NDb::BOOLEANPIN_NONE);
      bDebugGeometry = false;
    }

    //if(!g_simpleShaders)
    //{
    //  for (int i = 0, n = pGeometry->primitives.size(); i < n; ++i)
    //    queue.Push(NDb::MATERIALPRIORITY_ROADS, this, pGeometry->primitives[i], 0, Get(pMaterialN));
    //  for (int i = 0, n = pGeometry->primitives.size(); i < n; ++i)
    //    queue.Push(NDb::MATERIALPRIORITY_ROADS, this, pGeometry->primitives[i], 1, pMaterialA ? Get(pMaterialA) : Get(pMaterialN));
    //  for (int i = 0, n = pGeometry->primitives.size(); i < n; ++i)
    //    queue.Push(NDb::MATERIALPRIORITY_ROADS, this, pGeometry->primitives[i], 2, pMaterialB ? Get(pMaterialB) : Get(pMaterialN));
    //}
    //else {
    //  for (int i = 0, n = pGeometry->primitives.size(); i < n; ++i)
    //    queue.Push( NDb::MATERIALPRIORITY_ROADS, this, pGeometry->primitives[i], UINT_MAX,
    //                pMaterialB ? Get(pMaterialB) : Get(pMaterialN) );
    //}
    queue.Push( NDb::MATERIALPRIORITY_ROADS, this, primitive ? Get(primitive) : pGeometry->primitives[0],
                UINT_MAX, pMaterialB ? Get(pMaterialB) : Get(pMaterialN) );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
  Render::ConstantProtectionBlock block(Render::CCONTEXT_TERRAIN);

  NDb::RoadProperties const& props = pDBRoad->properties;

  float oowidth = props.width > 0.0f ? 1.0f / props.width : 0.0f;
  float ooborder = props.border > 0.0f ? 1.0f / props.border : 0.0f;
  float oofalloff = props.falloff > 0.0f ? 1.0f / props.falloff : 1.0e10f; // todo: it's bad practice to have "infinities" around [6/10/2010 smirnov]
  float length = pSpline->GetLength((float)pSpline->GetNumSegments());
  float oolength = length > 0.0f ? 1.0f / length : 0.0f;

  Render::GetRenderer()->SetVertexShaderConstantsFloat(VSHADER_LOCALCONST2, oowidth);

  if( UINT_MAX == elementNumber )
  {
    Render::BindSampler( 2, *(pMaterialN->GetRoadMap()) );
    Render::BindSampler( 3, *(pMaterialN->GetBorderMap()) );

    Render::BaseMaterial * const pMat = pMaterialA ? Get(pMaterialA) : Get(pMaterialN);
    Render::BindSampler( 5, *(pMat->GetRoadMap()) );
    Render::BindSampler( 6, *(pMat->GetBorderMap()) );

    Render::RenderState tweakedState( Render::GetStatesManager()->GetCurrentState() );
    tweakedState.SetBlendMode(NDb::BLENDMODE_PREMULTIPLIEDLERP);
    Render::SetRenderState(tweakedState);
  }
  else
  {
    CVec4 natureMask[] = {CVec4(0.0f, 1.0f, 0.0f, 0.0f), CVec4(0.0f, 0.0f, 1.0f, 0.0f), CVec4(1.0f, 0.0f, 0.0f, 0.0f)};
    NI_ASSERT(elementNumber < sizeof(natureMask)/sizeof(natureMask[0]), "Road mesh with element number exceeding number of nature types encountered");
    Render::GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST1, natureMask[elementNumber]);
  }
  float uScale = pDBRoad->properties.flip ? -0.5f : 0.5f;
  CVec4 constants[] = {
    CVec4(uScale * props.tileU, 0.5f * props.tileV, ooborder, 0.5f * ooborder * props.tileVBorder), // uvScale
    CVec4(0.5f, 0.0f, 1.0f, 0.0f),                                                                  // uvOffset
    CVec4(-oofalloff, -oofalloff * props.border, props.width * oolength, -0.5f),                    // fadeScale
    CVec4(props.border, 888.888f, 888.888f, props.opacity)                                          // params
  };
  Render::GetRenderer()->SetPixelShaderConstants(PSHADER_LOCALCONST2, ARRAY_SIZE(constants), constants);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::Store(Stream *pStream)
{
  // write signature
  unsigned const s = BAKED_FILE_SIGN;
  pStream->Write(&s, sizeof(unsigned));

  // write geometry
  Render::RenderResourceManager::SaveMeshGeometry(Get(pGeometry), pStream);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoadSceneObject::Load(Stream *pStream)
{
  // check signature
  unsigned s = 0;
  pStream->Read(&s, sizeof(unsigned));
  NI_DATA_VERIFY( s == BAKED_FILE_SIGN, "Failed to load road: invalid signature", return false; );

  Reset(pGeometry, Render::RenderResourceManager::LoadMeshGeometry(pStream->GetBuffer() + pStream->GetPosition(), false, false));
  bool inEditor = false;
  if(const Terrain::Terrain* const pTerrain = GetScene() ? GetScene()->GetTerrain() : NULL)
    inEditor = pTerrain->IsEditable();

  ASSERT(pGeometry->primitives.size() == 1);
  if( pScene->GetTerrain()->GetTextureCache() ) {
    Reset( pPatchMapping, new Terrain::PatchMapping(Get(pGeometry)) );
    Reset( primitive, new Terrain::RoadPrimitive(pGeometry->primitives[0], Get(pPatchMapping)) );
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoadSceneObject::Load( const string& fileName )
{
  if (fileName.empty())
    return false;

  CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if( !pStream || !pStream->IsOk() )
    return false;

  return Load(pStream.GetPtr());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::BuildAABB()
{
  worldAABB.Init2Empty();
  if (!RENDER_DISABLED && Get(pGeometry))
  {
    for (int i = 0; i < pGeometry->primitives.size(); ++i)
    {
      DXVertexBufferRef pVB = pGeometry->primitives[i]->GetVertexBuffer();
      NI_VERIFY(Get(pVB), "NULL vertex buffer", return);
      D3DVERTEXBUFFER_DESC vbDesc;
      pVB->GetDesc(&vbDesc);
      unsigned numVertices = vbDesc.Size / sizeof(RoadGeometryBuilder::RoadGeometryVertex);

      RoadGeometryBuilder::RoadGeometryVertex const* pVertex = Render::LockVB<RoadGeometryBuilder::RoadGeometryVertex>(Get(pVB), D3DLOCK_READONLY);
      NI_VERIFY(pVertex, "Unable to lock road vertices for reading", return);

      for (unsigned j = 0; j < numVertices; ++j, ++pVertex)
      {
        worldAABB.AddPoint(pVertex->position);
      }

      pVB->Unlock();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::TerrainModificationCB( void *pData, int flags, int elementID, Terrain::EModification::Enum callbackType )
{
  if ( !( flags & Terrain::INVALID_GEOMETRY ) )
    return;

  NI_VERIFY( pData, "internal error", return; );

  RoadSceneObject *pObj = (RoadSceneObject*)pData;

  if ( callbackType == Terrain::EModification::First )
  {
    pObj->updateMask.FillZero();
    return;
  }

  if ( callbackType == Terrain::EModification::Next )
  {
    if ( pObj->splineMask.GetData( elementID ) )
      pObj->updateMask.SetData( elementID );

    return;
  }

  if ( callbackType == Terrain::EModification::Last )
  {
    if ( !pObj->updateMask.IsZeroFilled() )
      pObj->RebuildGeometry();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::RebuildSpline()
{
  needUpdateMask = true;

  // create list of control points
  // two additional control points at ends are required so that spline touches start/end points
  // (classic B-spline is not meant to touch any of its control points)
  nstl::vector<CVec2> cp;
  nstl::vector<float> width;
  {
    int pointsCount = pDBRoad->points.size();

    cp.reserve( pointsCount + 2 );
    width.reserve( pointsCount );

    cp.push_back(2.f * pDBRoad->points[0].location - pDBRoad->points[1].location);

    for (int i = 0; i < pointsCount; ++i)
    {
      cp.push_back(pDBRoad->points[i].location);
      width.push_back(pDBRoad->points[i].width * pDBRoad->properties.width);
    }

    cp.push_back(2.f * pDBRoad->points[pointsCount - 1].location - pDBRoad->points[pointsCount - 2].location);
  }

  Reset(pSpline, new CCompositeBSplineWidth<CVec2>(cp, width));

  PrepareSplineElementsMask();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define _DO_TIMING
#ifdef _DO_TIMING
class PerformanceCounter
{
  LARGE_INTEGER m_llCount;
  float  m_scale;

  static LARGE_INTEGER s_llFreq;

public:
  PerformanceCounter(float _scale = 1.0f) : m_scale(_scale)
  {
    static BOOL init = (QueryPerformanceFrequency(&s_llFreq)
                        ? systemLog( NLogg::LEVEL_MESSAGE ) << "PerformanceCounter freq. is " << double(s_llFreq.QuadPart) << endl, TRUE
                        : FALSE);

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    QueryPerformanceCounter(&m_llCount);
  }

  ~PerformanceCounter()
  {
    LARGE_INTEGER llCount;

    BOOL bSuccess = QueryPerformanceCounter(&llCount);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
    if(bSuccess)
      systemLog( NLogg::LEVEL_MESSAGE ) << "road remove/add time:" <<
                                           m_scale * double(llCount.QuadPart - m_llCount.QuadPart)/s_llFreq.QuadPart;
  }
};

LARGE_INTEGER PerformanceCounter::s_llFreq;
#endif // _DO_TIMING

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::RebuildGeometry()
{
  // build geometry
  if ( !Get( pBuilder ) )
    Reset(pBuilder, new RoadGeometryBuilder);

  pBuilder->Begin(pDBRoad.GetPtr(), Get(pSpline));
  ProcessTerrainElements();
  Reset(pGeometry, pBuilder->End());

  const Render::AABB oldAABB = worldAABB;

  BuildAABB();

  if(oldAABB != worldAABB) {
#ifdef _DO_TIMING
    PerformanceCounter timer;
#endif // _DO_TIMING
    pScene->RemoveObject(this);
    pScene->AddSceneObject(this);
  }
}


void RoadSceneObject::PrepareSplineElementsMask()
{
  if ( !GetScene() || !GetScene()->GetTerrain() )
    return;

  if ( !needUpdateMask )
    return;

  Terrain::GridConstants const &gc = GetScene()->GetTerrain()->GetGridConstants();
  Terrain::TerrainElementManager &TEMan = GetScene()->GetTerrain()->GetElementManager();

  // sample spline (ensure that sample points are not too far from each other)
  nstl::vector<CVec2> samples;
  pSpline->Sample(0.01f, 0.9f * gc.metersPerElement, samples);

  int maxElemId = TEMan.GetLastElementId();
  splineMask.SetSize( maxElemId + 1 );
  updateMask.SetSize( maxElemId + 1 );
  splineMask.FillZero();
  updateMask.FillZero();

  // mark in mask all terrain elements which contain any of the spline sample points
  int i;
  CVec3 const &worldSize = gc.worldSize;
  for (i = 0; i < samples.size(); ++i)
  {
    if ( 0.f > samples[i].x || samples[i].x > worldSize.x ||
      0.f > samples[i].y || samples[i].y > worldSize.y )
      continue;

    Terrain::TerrainElementId id = TEMan.LocateElement(samples[i].x, samples[i].y);

    if (id != Terrain::TERRAINELEMENTID_BAD)
    {
      NI_ASSERT(id <= maxElemId, "Internal error");
      splineMask.SetData(id);
    }
  }

  // expand mask by one element in all directions
  // Note: I understand that over-edge bleeding may occur, but such kind of overestimation is acceptable for the algorithm in whole.
  splineMask |= (splineMask << 1);
  splineMask |= (splineMask >> 1);
  splineMask |= (splineMask << (TEMan.GetMaxColumn()+1));
  splineMask |= (splineMask >> (TEMan.GetMaxColumn()+1));

  updateMask = splineMask;

  needUpdateMask = false;
}

void RoadSceneObject::ProcessTerrainElements()
{
  PrepareSplineElementsMask();

  // enumerate all marked elements
  for ( int i = 1; i <= splineMask.GetSize() ; ++i )
  {
    if ( splineMask.GetData(i) )
    {
      TerrainElementGatherTriangles( (Terrain::TerrainElementId)i, updateMask.GetData(i) );
      updateMask.RemoveData(i);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadSceneObject::TerrainElementGatherTriangles( Terrain::TerrainElementId id, bool forceUpdate )
{
  Terrain::TerrainElementManager &TEMan = GetScene()->GetTerrain()->GetElementManager();
  Terrain::TerrainElementInfo &info = TEMan.GetElementInfo(id);

#ifdef DEBUG_DRAW_ELEMENTS
  if (_debugRenderer_)
  {
    _debugRenderer_->DrawAABB(info.pElement->GetWorldAABB(), Render::Color(255, 0, 255), false);
  }
#endif

  if (Get(pBuilder) && info.pElement)
  {
    pBuilder->AddTerrainElement( info.pElement, id, forceUpdate );
  }
}

bool RoadSceneObject::OnRoadShowCommand(const char *pName, const vector<wstring>& params)
{
  int arg = (params.size() == 1) ? NStr::ToInt(params[0].c_str()) : -888;
  if (params.size() != 1 || arg < 0 || arg > 2)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << pName << " <mode>" << endl;
    systemLog( NLogg::LEVEL_MESSAGE ) << "where: <mode> = 0 (don't show), 1 (normal render) or 2 (show unclipped geometry)" << endl;
    systemLog( NLogg::LEVEL_MESSAGE ) << pName << " = " << s_showGeometry << endl;
    return true;
  }

  s_showGeometry = arg;
  return true;
}

bool RoadSceneObject::OnRoadSplineCommand(const char *pName, const vector<wstring>& params)
{
  int arg = (params.size() == 1) ? NStr::ToInt(params[0].c_str()) : -888;
  if (params.size() != 1 || arg < 0)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << pName << " <mode>" << endl;
    systemLog( NLogg::LEVEL_MESSAGE ) << "where: <mode> = 0 (don't show) or >0 (number of subdivisions)" << endl;
    systemLog( NLogg::LEVEL_MESSAGE ) << pName << " = " << s_showSpline << endl;
    return true;
  }

  s_showSpline = arg;
  return true;
}

} // namespace NScene

REGISTER_DEV_CMD( roadshow, NScene::RoadSceneObject::OnRoadShowCommand);
REGISTER_DEV_CMD( roadspline, NScene::RoadSceneObject::OnRoadSplineCommand);
