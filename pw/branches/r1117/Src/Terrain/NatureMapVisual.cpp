#include "stdafx.h"
#include "NatureMapVisual.h"
#include "../Render/debugrenderer.h"
#include "../Render/smartrenderer.h"
#include "../Render/batch.h"
#include "../Render/GlobalMasks.h"
#include "../Render/SceneConstants.h"
#include "../Render/ImmediateRenderer.h"
#include "../Render/IConfigManager.h"
#include "../Render/NullRenderSignal.h"

#include "../System/lerp.h"

#define DATA_FILE_VERSION(ver) (0x00565848 | ((ver) << 24))

namespace Terrain {

static NDebug::PerformanceDebugVar profile_Changed("NMV::OnNatureChanged", "Terrain", 0, 5, false);

namespace {
  DECLARE_NULL_RENDER_FLAG

  struct NatureMapVertex
  {
    CVec3 pos;
    float index;
  };

  struct DataFileHeader
  {
    static const unsigned SIGNATURE = DATA_FILE_VERSION(3);
    unsigned sign;
    unsigned vertexSize;
    unsigned numVertices;
    unsigned numIndices;
  };

  float bell(float x, float alpha)
  {
    return 0.5f * (1.0f - cosf(6.28318530718f * x * (1.0f - alpha) / (alpha + (1.0f - 2.0f * alpha) * x)));
  }
} // anonymous namespace

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool NatureMapVisual::Primitive::Add(CVec2 _pos, CVec4 const& _params)
{
  int idx = hexCount * CONSTANTS_PER_HEX;
  hexConstants[idx++].Set(_pos.x, _pos.y, 888.888f, 888.888f);
  hexConstants[idx++].Set(_params);

  hexCount++;
  return (hexCount == NUM_HEXES_SUPPORTED);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::AttackVisual::GetParams(CVec4 &params, float alpha, bool overburnOnRetreat) const
{
  if (t < 0.0f)
    return false;

  float x = ClampFast(t / length, 0.0f, 1.0f);

  float retreat = 0.0f;
  float overburn = 0.0f;
  if (action == ACTION_ATTACK)
  {
     overburn = bell(x, alpha);
     retreat = alpha > 0.0f ? 0.5f * (1.0f - x / alpha) : 0.0f;
  }
  else
  {
    if ( overburnOnRetreat )
      overburn = bell(x, alpha);
    retreat = x;
  }

  if (nature == NDb::NATURETYPE_B)
    params.Set(1 - retreat, retreat, 0, overburn);
  else
    params.Set(0, retreat, 1 - retreat, overburn);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMapVisual::NatureMapVisual(bool editable_)
: NatureMap(editable_)
, DeviceLostHandlerLoadable(HANDLERPRIORITY_LOW)
, primitives(1)
, mappingCoeff(VNULL4)
, prevTime(0.0f)
, overburn(0.0f, 0.0f, 0.0f, 0.0f)
, disabled(false)
{
}

NatureMapVisual::~NatureMapVisual()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::InitializeParams()
{
  // support separate overburn for different factions
  overburn[3] = Max(Max(dbNatureMap.visual.overburnA, dbNatureMap.visual.overburnB), 0.0f );
  if (overburn[3] > FP_EPSILON)
  {
    overburn[NDb::NATURETYPE_A] = dbNatureMap.visual.overburnA / overburn[3];
    overburn[NDb::NATURETYPE_B] = dbNatureMap.visual.overburnB / overburn[3];
  }
  else
    overburn = VNULL4;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::OnCreate()
{
  // call parent first
  if (!NatureMap::OnCreate())
    return false;
  
  disabled = RENDER_DISABLED || Render::GetIConfigManager()->GetSysInfo().IsNullRef;

  // allocate data
  if( disabled || !CreateRenderStructures() )
    return false;

  FillRenderBuffers();
  InitializeTerrainMask();
  InitializeParams();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::OnLoadAtRuntime(Stream* pStream, int fraction, bool fromRecconect )
{
  // call parent first
  bool natureMapLoaded = NatureMap::OnLoad(pStream, fraction, fromRecconect);
  if( !natureMapLoaded )
    return false;

  disabled = RENDER_DISABLED || Render::GetIConfigManager()->GetSysInfo().IsNullRef;
  if(disabled)
    return natureMapLoaded;

  // check consistency
  DataFileHeader const* pHeader = pStream->ReadInPlaceAs<DataFileHeader>();
  bool ok = pHeader && 
    pHeader->sign == DataFileHeader::SIGNATURE &&
    pHeader->vertexSize == sizeof(NatureMapVertex) &&
    pHeader->numVertices == GetNumVertices() &&
    pHeader->numIndices == GetNumIndices();
  NI_VERIFY(ok, "Data file is inconsistent with runtime", return false);

  LoaderCS cs(loadFinished);

  // allocate data
  if (!CreateRenderStructures())
    return false;

  FillRenderBuffers();
  InitializeTerrainMask();
  InitializeParams();

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::OnLoad(Stream* pStream, int fraction, bool fromRecconect )
{
  return OnLoadAtRuntime(pStream, fraction, fromRecconect);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::OnSaveAtRuntime( Stream* pStream, bool fromRecconect ) const
{
  // call parent first
  if (!NatureMap::OnSave( pStream, fromRecconect ))
    return false;

  // check consistency
  DataFileHeader header = {DataFileHeader::SIGNATURE, sizeof(NatureMapVertex), GetNumVertices(), GetNumIndices()};
  pStream->Write(&header, sizeof(DataFileHeader));
  
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::OnSave( Stream* pStream, bool fromRecconect ) const
{
  return OnSaveAtRuntime(pStream, fromRecconect);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMapVisual::CreateRenderStructures()
{
  // create vertex buffer
  pVertexBuffer = Render::CreateVB(GetNumVertices() * sizeof(NatureMapVertex), Render::RENDER_POOL_MANAGED);
  NI_VERIFY(Get(pVertexBuffer), "Unable to create vertex buffer", return false);

  // create index buffer
  pIndexBuffer.Resize( GetNumIndices() * sizeof(unsigned) );
  NI_VERIFY(Get(pIndexBuffer), "Unable to create index buffer", return false);

  // create vertex format declaration
  Render::VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement(Render::VertexElementDescriptor(0, 0, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0));
  formatDescriptor.AddVertexElement(Render::VertexElementDescriptor(0, 12, Render::VERTEXELEMENTTYPE_FLOAT1, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0));
  pVertexFormat = Render::SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);

  // fill DIP description
  dipDescriptor.primitiveType = Render::RENDERPRIMITIVE_TRIANGLELIST;
  dipDescriptor.baseVertexIndex = 0;
  dipDescriptor.minIndex = 0;
  dipDescriptor.numVertices = GetNumVertices();
  dipDescriptor.startIndex = 0;
  dipDescriptor.primitiveCount = 0;

  // create material
  ::Reset(pMaterial, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::NatureMapMaterial::typeId ) ) );
  NI_VERIFY(Get(pMaterial), "Unable to create material", return false);

  unsigned const minSize = 32;
  unsigned width  = Max(NUM_PIXELS_PER_TEN_METERS * unsigned(worldSize.x / 10), minSize);
  unsigned height = Max(NUM_PIXELS_PER_TEN_METERS * unsigned(worldSize.y / 10), minSize);

  natureMap = Render::CreateRenderTexture2D(width, height, Render::FORMAT_A8R8G8B8);
  blurredNatureMap = Render::CreateRenderTexture2D(width, height, Render::FORMAT_A8R8G8B8);
  noiseMap = Render::Load2DTextureFromFile( "Tech/Default/Terrnoise.dds" );
  retreatMap = Render::Load2DTextureFromFile( "Tech/Default/Terrmask.dds" );

  blurEffect.Init(width, height);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::FillRenderBuffers()
{
  if ( Render::GetRenderer()->DeviceIsLost() )
    return;

  const int numHexVertices = 6;

  if(pVertexBuffer)
  {
    // fill the vertex buffer
    NatureMapVertex* pVertices = Render::LockVB<NatureMapVertex>(Get(pVertexBuffer), 0);
    NI_VERIFY(pVertices, "Unable to lock vertices", return);
    NatureMapVertex* pVertex = pVertices;
    float step = GetElementSize();
    float step3 = step / 3.0f;

    float x[numHexVertices] = { -0.5f * step, 0, 0.5f * step, 0.5f * step, 0, -0.5f * step };
    float y[numHexVertices] = { step3, 2 * step3, step3, -step3, -2 * step3, -step3 };
    for(unsigned i = 0, offset = 0; i != Primitive::NUM_HEXES_SUPPORTED; ++i, offset += numHexVertices)
    {
      for( unsigned j = 0, endJ = numHexVertices; j != endJ; ++j )
      {
        pVertex[ offset + j ].pos.Set(x[j], y[j], 0);
        pVertex[ offset + j ].index = i + 0.5f;
      }
    }

    pVertexBuffer->Unlock();
  }

  if( ::Get(pIndexBuffer) )
  {
    unsigned* pIndices = Render::LockIB(Get(pIndexBuffer), D3DLOCK_DISCARD);
    unsigned indices[Primitive::INDICES_PER_ELEMENT] = { 0, 5, 4, 0, 4, 1, 1, 4, 3, 1, 3, 2 };
    for(unsigned i = 0, vOffset = 0, iOffset = 0; i != Primitive::NUM_HEXES_SUPPORTED;
        ++i, vOffset += numHexVertices, iOffset += Primitive::INDICES_PER_ELEMENT)
      for(unsigned j = 0, endJ = Primitive::INDICES_PER_ELEMENT; j != endJ; ++j)
        pIndices[iOffset + j] = vOffset + indices[j];

    pIndexBuffer->Unlock();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::OnDeviceReset()
{
  if(!loadFinished)
    return;
  FillRenderBuffers();
  InitializeTerrainMask();
}

bool NatureMapVisual::Reinit( NDb::ENatureType faction, const NDb::DBNatureMap* pDbNatureMap, bool forceCreate )
{
  bool res = NatureMap::Reinit( faction, pDbNatureMap, forceCreate );
  if ( res )
  {
    FillRenderBuffers();
    InitializeTerrainMask();
  }
  return res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::RenderDebug()
{
  NatureMap::RenderDebug();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::Update()
{
  float time = Render::SceneConstants::Global().renderTime;

  UpdateAttackVisual(time - prevTime);

  prevTime = time;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::RenderAdd(NatureMapElementId id, CVec4 const& params)
{
  CVec2 pos;
  GetElementPosition(id, pos);
  if( primitives.back().Add(pos, params) )
    primitives.push_back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NatureMapVisual::OnRender()
{
  Render::LogMarker( "NatureAttack" );

  static SHMatrix world;
  static const bool inited = (Identity(&world), true); // Just setting up "world" variable

  Render::Renderer& renderer = *Render::GetRenderer();
  bool doBloor = false;

  for(int i = 0; i < primitives.size(); ++i) {
    const Primitive &prim = primitives[i];

    if(prim.hexCount <= 0)
      break;

    if(!doBloor) { // first time
      pMaterial->PrepareRenderer();
      renderer.SetVertexShaderConstantsMatrix( WORLD, world );
      renderer.SetVertexShaderConstantsVector4( VSHADER_LOCALCONST0, CVec4(2.0f / worldSize.x, 2.0f / worldSize.y, -1.0f, -1.0f) );
      renderer.SetVertexShaderConstantsVector4( VSHADER_LOCALCONST1, CVec4(dbNatureMap.visual.retreatTiling * 0.1f,
        888.888f, 888.888f, 888.888f) );

      Render::RenderStatesManager& rsManager = *Render::GetStatesManager();
      rsManager.SetState( Render::RenderState::NoBlendNoTest().SetCulling(NDb::ONOFFSTATE_OFF) );
      rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
      rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
      rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);
      rsManager.SetSampler(0, Render::SamplerState::PRESET_WRAP_BILINEAR(), retreatMap);

      Render::SmartRenderer::BindRenderTarget(natureMap);
      Render::SmartRenderer::BindVertexDeclaration(pVertexFormat);
      Render::SmartRenderer::BindIndexBuffer(pIndexBuffer);
      Render::SmartRenderer::BindVertexBuffer(0, Get(pVertexBuffer), sizeof(NatureMapVertex));

      doBloor = true;
    }

    Render::GetRenderer()->SetVertexShaderConstants(VSHADER_LOCALCONST2,
                                                    prim.hexCount * Primitive::CONSTANTS_PER_HEX, prim.hexConstants);
    dipDescriptor.primitiveCount = 4 * prim.hexCount;
    Render::SmartRenderer::DrawIndexedPrimitive(dipDescriptor);
  }

  if(doBloor) {
    Render::SmartRenderer::BindRenderTargetDefault();
    // Set sampler
    Render::GetStatesManager()->SetSampler(1, Render::SamplerState::PRESET_WRAP_BILINEAR(), noiseMap);
    // set shader parameters
    NDb::DBNatureMapVisual const& visual = dbNatureMap.visual;
    float noiseR2 = visual.noiseR2 / worldSize.x;
    float noiseTile = visual.noiseTile * worldSize.x;

    CVec4 noiseParams(noiseTile, 0, 0, noiseR2);
    renderer.SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, noiseParams);

    blurEffect.Apply(natureMap, blurredNatureMap, "BlurDistort");
  }

  primitives.clear();
  primitives.push_back();

  return doBloor;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::RenderElement(NatureMapElementId id, NatureMapElementInfo const& info)
{
  float burnPercent = (info.natureCur == NDb::NATURETYPE_B);
  float freezePercent = (info.natureCur == NDb::NATURETYPE_A);

  CVec4 params;
  params.Set(burnPercent, 1 - (burnPercent + freezePercent), freezePercent, 0);
  RenderAdd(id, params);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::RenderElementFX(AttackVisual &attackElem)
{
  CVec4 params;
  if (attackElem.GetParams(params, dbNatureMap.visual.attackIntro / dbNatureMap.visual.attackTime, dbNatureMap.visual.overburnRethreat))
  {
    params.w *= overburn[attackElem.nature]; // support different overburn scales
    RenderAdd(attackElem.id, params);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::AddAttackVisual(NatureMapElementId id, NatureMapElementInfo &info)
{
  // smirnov [2009/5/5]: what's the case?
  if (info.natureCur == info.natureOld)
    return;

  // replace previous visual if any
  struct {
    NatureMapElementId id;
    bool operator()(AttackVisual const& fx) { return fx.id == id; }
  } compareId = {id};
  attack_elements_container::iterator it = find_if(attackHexes.begin(), attackHexes.end(), compareId);
  AttackVisual& fx = (it == attackHexes.end() ? attackHexes.push_back() : *it);

  // There are three cases:
  // 1)  N  -> A|B : hex is under attack, overburn it
  // 2) A|B ->  N  : nature is retreating, fade it
  // 3) A|B -> B|A : two natures are in contact, hex is under attack, no fade!

  if (info.natureCur != NDb::NATURETYPE_N)
  {
    // determine delay ( 0.f for overridden elements )
    float delayTime = 0.f;
    if (info.ownerData == 0)
    {
      delayTime = dbNatureMap.visual.attackDelay;
    }

    fx = AttackVisual(AttackVisual::ACTION_ATTACK, id, (NDb::ENatureType)info.natureCur, delayTime, dbNatureMap.visual.attackTime);
  }
  else
    fx = AttackVisual(AttackVisual::ACTION_RETREAT, id, (NDb::ENatureType)info.natureOld, 0.0f, dbNatureMap.visual.retreatTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::UpdateAttackVisual(float timeElapsed)
{
  if (attackHexes.empty() || disabled)
    return;

  if( !Render::GetRenderer()->DeviceIsLost() ) { // update texture
    for (attack_elements_container::iterator it = attackHexes.begin(); it != attackHexes.end(); ++it)
    {
      AttackVisual& fx = *it;
      fx.Update(timeElapsed);
      RenderElementFX(fx);
    }
  }

  // check for expired elements
  for (attack_elements_container::iterator it = attackHexes.begin(); it != attackHexes.end(); )
  {
    AttackVisual& fx = *it;
/* Nature attack uses blending so we need both terrains (cur+old) [7/22/2010 smirnov]
    if (fx.t >= 0.0f)
    {
      NatureMapElementInfo &info = GetElementInfo(fx.id);
      if (info.natureCur != NDb::NATURETYPE_N&& info.natureOld != info.natureCur)
      {
        info.natureOld = info.natureCur;
        MarkAsModified(fx.id, info);
      }
    }
*/
    if ( fx.IsEnd() )
    {
      NatureMapElementInfo &info = GetElementInfo(fx.id);
// Always delete previous nature since attack design has changed [7/22/2010 smirnov]
//      if (info.natureCur == NDb::NATURETYPE_N) // retreating done - delete old nature
      {
        info.natureOld = info.natureCur;
        MarkAsModified(fx.id, info);
      }

      it = attackHexes.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::InitializeTerrainMask()
{
  Render::Renderer &renderer = *Render::GetRenderer();
  if ( renderer.DeviceIsLost() || disabled )
    return;

  ForAllElements(this, &NatureMapVisual::RenderElement);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::OnNatureChanged(int const* pQuadRanges, int numQuadRanges)
{
  NatureMap::OnNatureChanged(pQuadRanges, numQuadRanges);

  NDebug::PerformanceDebugVarGuard profile(profile_Changed, true);
  ForAllModifiedElements(this, &NatureMapVisual::AddAttackVisual);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMapVisual::GetElementVisualBounds(NatureMapElementId id, Render::AABB& aabb) const
{
  GetElementBounds(id, aabb);
  aabb.halfSize += CVec3(2, 2, 50);
}

} // namespace Terrain

// end of NatureMapVisual.cpp
