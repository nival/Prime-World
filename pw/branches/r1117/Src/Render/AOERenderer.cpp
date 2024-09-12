#include "stdafx.h"
#include "AOERenderer.h"
#include "MaterialSpec.h"
#include "GlobalMasks.h"
#include "../System/FastMath.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
  DECLARE_NULL_RENDER_FLAG

  struct AOERendererVertex
  {
    float x, y;
    int i;
  };
} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Render
{

AOERenderer* AOERenderer::s_pInstance = NULL;

void AOERenderer::Init()
{
  NI_VERIFY(s_pInstance == NULL, "AOERenderer already inited", return);
  s_pInstance = new AOERenderer();
}

void AOERenderer::Term()
{
  SAFE_DELETE(s_pInstance);
}

AOERenderer* AOERenderer::Get()
{
  return s_pInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AOERenderer::AOERenderer() :
  bInit(false),
  saturation(0.f),
  satColor(0.f,0.f,0.f,0.f),
  saturate(false)
{
  if(!RENDER_DISABLED) {
    if (!CreateQuad() || !CreateFan() || !CreateStrip())
      return;
  }

  for (int i = 0; i < _NUM_CHANNELS; i++)
  {
    AreaChannel& channel = channels[i];
    channel.type = AREA_DISK;
    Reset(channel.pMaterial, NULL);
    channel.color = HDRColor::WHITE();
    channel.radius = 0.0f;
    channel.span = 0.0f;
    Identity(&channel.xform);
    channel.enabled = false;
  }

  bInit = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AOERenderer::~AOERenderer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AOERenderer::CreateQuad()
{
  //  1      0
  //   +----+
  //   |  / |
  //   | /  |
  //   +----+
  //  2      3

  // vertex buffer
  AOERendererVertex vertices[] = {
    {+1.0f, +1.0f, 0},
    {-1.0f, +1.0f, 1},
    {-1.0f, -1.0f, 2},
    {+1.0f, -1.0f, 3}
  };
  DXVertexBufferRef pVB = CreateVB(sizeof(vertices), RENDER_POOL_MANAGED, vertices);
  NI_VERIFY(::Get(pVB), "Unable to create vertex buffer for AOE", return false);

  // index buffer
  unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  DXIndexBufferRef pIB = CreateIB(sizeof(indices), RENDER_POOL_MANAGED, indices);
  NI_VERIFY(::Get(pIB), "Unable to create index buffer for AOE", return false);

  // prepare primitive
  Primitive& geo = quad;
  DipDescriptor& dip = geo.GetDipDescriptor();
  dip.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  dip.baseVertexIndex = 0;
  dip.minIndex = 0;
  dip.numVertices = ARRAY_SIZE(vertices);
  dip.startIndex = 0;
  dip.primitiveCount = ARRAY_SIZE(indices) / 3;

  VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_SHORT2, VERETEXELEMENTUSAGE_BLENDINDICES, 0) );

  geo.SetVertexStream(pVB, sizeof(AOERendererVertex));
  geo.SetVertexDeclaration(SmartRenderer::GetVertexFormatDeclaration(formatDescriptor));
  geo.SetIndexBuffer(pIB);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AOERenderer::CreateFan()
{
  //  sector  and  left/right boundaries
  //
  // 2      1       6      5         6 2 5    1
  //  +----+         +----+           +++----+
  //  |  / |         |  / |           |||  / |
  //  | /  |        3| /  |4         3|||4/  |
  // 0+<   |  and    #====#    =>     +0+    |
  //  | \  |        9|  / |A         9|||A\  |
  //  |  \ |         | /  |           |||  \ |
  //  +----+         +----+           +++----+
  // 8      7       C      B         C 8 B    7

  // vertex buffer
  static const float eps = 1e-5f;
  AOERendererVertex vertices[] = {
    { 0.00f,  0.0f, 0},
    {+1.00f, +1.0f, 1},
    { 0.00f, +1.0f, 2},
    {-0.25f,   eps, 3},
    { 0.25f,   eps, 4},
    { 0.25f, +1.0f, 5},
    {-0.25f, +1.0f, 6},
    {+1.00f, -1.0f, 1},
    { 0.00f, -1.0f, 2},
    {-0.25f,  -eps, 3},
    { 0.25f,  -eps, 4},
    { 0.25f, -1.0f, 5},
    {-0.25f, -1.0f, 6},
  };
  NI_STATIC_ASSERT(ARRAY_SIZE(vertices) == 2 * ARRAY_SIZE(fanParams) - 1, SIZES_DO_NOT_MATCH);
  DXVertexBufferRef pVB = CreateVB(sizeof(vertices), RENDER_POOL_MANAGED, vertices);
  NI_VERIFY(::Get(pVB), "Unable to create vertex buffer for AOE", return false);

  // index buffer
  unsigned int indices[] = {0, 8, 7, 0, 7, 1, 0, 1, 2, 3, 4, 5, 3, 5, 6, 12, 11, 10, 12, 10, 9};
  NI_STATIC_ASSERT(ARRAY_SIZE(indices) == 3 * 7, SIZES_DO_NOT_MATCH);
  DXIndexBufferRef pIB = CreateIB(sizeof(indices), RENDER_POOL_MANAGED, indices);
  NI_VERIFY(::Get(pIB), "Unable to create index buffer for AOE", return false);

  // prepare primitive
  Primitive& geo = fan;
  DipDescriptor& dip = geo.GetDipDescriptor();
  dip.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  dip.baseVertexIndex = 0;
  dip.minIndex = 0;
  dip.numVertices = ARRAY_SIZE(vertices);
  dip.startIndex = 0;
  dip.primitiveCount = ARRAY_SIZE(indices) / 3;

  VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_SHORT2, VERETEXELEMENTUSAGE_BLENDINDICES, 0) );

  geo.SetVertexStream(pVB, sizeof(AOERendererVertex));
  geo.SetVertexDeclaration(SmartRenderer::GetVertexFormatDeclaration(formatDescriptor));
  geo.SetIndexBuffer(pIB);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::PrepareFan(float angle)
{
  // 2      1       6      5         6 2 5    1
  //  +----+         +----+           +++----+
  //  |  / |         |  / |           |||  / |
  //  | /  |        3| /  |4         3|||4/  |
  // 0+<   |  and    #====#    =>     +0+    |
  //  | \  |         |  / |           ||| \  |
  //  |  \ |         | /  |           |||  \ |
  //  +----+         +----+           +++----+
  //                                           
  NI_STATIC_ASSERT(ARRAY_SIZE(fanParams) == 7, SIZES_DO_NOT_MATCH);
  float sina = sinf(angle);
  float cosa = cosf(angle);
  float tana = tanf(0.5f * angle);
  fanParams[0].Set(0.0f, 0.0f, 0.5f, 0.5f);
  fanParams[1].Set(1.0f, tana, 1.0f, 0.5f - 0.5f * tana);
  fanParams[2].Set(cosa, sina, 0.5f + 0.5f * cosa, 0.5f - 0.5f * sina);

  float dx = 0.125f * sina;
  float dy = 0.125f * cosa;
  fanParams[3].Set(-dx, dy, 0.125f, 0.5f);
  fanParams[4].Set(dx, -dy, 0.375f, 0.5f);
  fanParams[5].Set(cosa+dx, sina-dy, 0.375f, 0.0f);
  fanParams[6].Set(cosa-dx, sina+dy, 0.125f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AOERenderer::CreateStrip()
{
  // 0    1  2    3
  //  +----++----+
  //  |  / ||  / |
  //  | /  || /  |
  //  +----++----+
  // 4    5  6    7

  // vertex buffer
  AOERendererVertex vertices[] = {
    { 0.0f, +1.0f, 0},
    { 0.5f, +1.0f, 1},
    { 0.5f, +1.0f, 2},
    { 1.0f, +1.0f, 3},
    { 0.0f, -1.0f, 0},
    { 0.5f, -1.0f, 1},
    { 0.5f, -1.0f, 2},
    { 1.0f, -1.0f, 3},
  };
  NI_STATIC_ASSERT(ARRAY_SIZE(vertices) == 2 * ARRAY_SIZE(stripParams[0]), SIZES_DO_NOT_MATCH);
  DXVertexBufferRef pVB = CreateVB(sizeof(vertices), RENDER_POOL_MANAGED, vertices);
  NI_VERIFY(::Get(pVB), "Unable to create vertex buffer for AOE", return false);

  // index buffer
  unsigned int indices[] = {0, 4, 1, 1, 4, 5, 1, 5, 2, 2, 5, 6, 2, 6, 3, 3, 6, 7};
  NI_STATIC_ASSERT(ARRAY_SIZE(indices) == 3 * 6, SIZES_DO_NOT_MATCH);
  DXIndexBufferRef pIB = CreateIB(sizeof(indices), RENDER_POOL_MANAGED, indices);
  NI_VERIFY(::Get(pIB), "Unable to create index buffer for AOE", return false);

  // prepare primitive
  Primitive& geo = strip;
  DipDescriptor& dip = geo.GetDipDescriptor();
  dip.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  dip.baseVertexIndex = 0;
  dip.minIndex = 0;
  dip.numVertices = ARRAY_SIZE(vertices);
  dip.startIndex = 0;
  dip.primitiveCount = ARRAY_SIZE(indices) / 3;

  VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_SHORT2, VERETEXELEMENTUSAGE_BLENDINDICES, 0) );

  geo.SetVertexStream(pVB, sizeof(AOERendererVertex));
  geo.SetVertexDeclaration(SmartRenderer::GetVertexFormatDeclaration(formatDescriptor));
  geo.SetIndexBuffer(pIB);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::PrepareStrip(ChannelType channelId, float width, float base)
{
  // 0    1  2    3
  //  +----++----+
  //  |  / ||  / |
  //  | /  || /  |
  //  +----++----+
  // 
  NI_STATIC_ASSERT(ARRAY_SIZE(stripParams[channelId]) == 4, SIZES_DO_NOT_MATCH);
  float skip = 1.0f <= base ? 0.0f : 1.0f - base;
  float step = 0.5f * (1.0f - skip);

  stripParams[channelId][0].Set(0.0f, width, 0.0f, 0.0f);
  stripParams[channelId][1].Set(step, width, 0.5f, 0.0f);
  stripParams[channelId][2].Set(step + skip, width, 0.5f, 0.0f);
  stripParams[channelId][3].Set(1.0f, width, 1.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::SetAreaParams(ChannelType channelId, AreaType type, NDb::Material const* pMaterial, float radius, float span)
{
  NI_ASSERT(0 <= channelId && channelId < _NUM_CHANNELS, NStr::StrFmt("Invalid AOE channel index %i of %i maximum", channelId, _NUM_CHANNELS));
  NI_ASSERT(channelId != CHANNEL_DIRECTION || type == AREA_LINE, "Only linee type is supported for direction channel");

  AreaChannel& channel = channels[channelId];
  channel.type = type;
  channel.radius = radius;
  channel.span = span;

  // allow missing material for lazy artists and designers
  if (!pMaterial)
  {
    // just don't show nothing
    Reset(channel.pMaterial, NULL);
  }
  else
  {
    // recreate material only if it has changed
    if (!channel.pMaterial || channel.pMaterial->GetDBMaterial()->GetDBID().GetHashKey() != pMaterial->GetDBID().GetHashKey())
    {
      NI_DATA_VERIFY(pMaterial->GetObjectTypeID() == NDb::AOEMaterial::typeId, NStr::StrFmt("AOE must use AOEMaterial, not '%s'", pMaterial->GetObjectTypeName()), return);
      Reset(channel.pMaterial, static_cast<BaseMaterial*>(CreateRenderMaterial(pMaterial)));
    }
  }

  // rebuild geometry
  if (channel.type == AREA_SECTOR)
    PrepareFan(fabs(channel.span));
  else if ( channel.type == AREA_LINE || channel.type == AREA_WALL )
  {
    SetAreaRadius(channelId, channel.radius);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::SetAreaRadius(ChannelType channelId, float radius)
{
  NI_ASSERT(0 <= channelId && channelId < _NUM_CHANNELS, NStr::StrFmt("Invalid AOE channel index %i of %i maximum", channelId, _NUM_CHANNELS));

  AreaChannel& channel = channels[channelId];
  channel.radius = radius;

  if ( channel.type == AREA_LINE || channel.type == AREA_WALL )
  {
    // for safety
    if (fabs(channel.radius) < FP_EPSILON)
    {
      channel.radius = 1.0f;
      channel.span = 0.0f;
    }

    float aspectRatio = 1.0f;
    if (channel.pMaterial)
      if (NDb::AOEMaterial const* pDBMaterial = dynamic_cast<NDb::AOEMaterial const*>(channel.pMaterial->GetDBMaterial()))
        aspectRatio = pDBMaterial->aspectRatio;
    float baseLength = aspectRatio * (2.0f * channel.span);
    PrepareStrip(channelId, fabs(channel.span) / channel.radius, fabs(baseLength) / channel.radius);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::SetAreaPosition(ChannelType channelId, CVec3 const& pos, CVec3 const& dir, bool usePrimaryColor, float interpolateColor /*= -1.0f*/)
{
  NI_ASSERT(0 <= channelId && channelId < _NUM_CHANNELS, NStr::StrFmt("Invalid AOE index %i of %i maximum", channelId, _NUM_CHANNELS));
  AreaChannel& channel = channels[channelId];
  if (channel.type == AREA_DISK)
    channel.xform.Set(pos);
  else
  {
    CVec2 dir2d = (channel.span < 0 ? -dir : dir).AsVec2D();
    if (!Normalize(&dir2d))
      dir2d.Set(1.0f, 0.0f);
    if ( channel.type == AREA_WALL )
    {
      dir2d = CVec2( -dir2d.y, dir2d.x );
      CVec3 newpos = pos - CVec3( dir2d * channel.radius * 0.5f, 0.0f );
      channel.xform.Set( newpos, CQuat(NMath::GetAngle( dir2d ), V3_AXIS_Z) );
    }
    else
    {
      channel.xform.Set(pos, CQuat(NMath::GetAngle(dir2d), V3_AXIS_Z));
    }
  }

  channel.enabled = true;

  HDRColor color(1.0f);
  if (channel.pMaterial)
  {
    if (NDb::AOEMaterial const* pDBMaterial = dynamic_cast<NDb::AOEMaterial const*>(channel.pMaterial->GetDBMaterial()))
    {
      if (interpolateColor < 0.0f)
      {
        color = usePrimaryColor ? pDBMaterial->primaryColor : pDBMaterial->secondaryColor;
      }
      else
      {
        float primaryPercent =  (usePrimaryColor) ? (interpolateColor) : (1.0f - interpolateColor);
        float secondaryPercent =  (!usePrimaryColor) ? (interpolateColor) : (1.0f - interpolateColor);
        color.R = pDBMaterial->primaryColor.R * primaryPercent + pDBMaterial->secondaryColor.R * secondaryPercent;
        color.G = pDBMaterial->primaryColor.G * primaryPercent + pDBMaterial->secondaryColor.G * secondaryPercent;
        color.B = pDBMaterial->primaryColor.B * primaryPercent + pDBMaterial->secondaryColor.B * secondaryPercent;
        color.A = pDBMaterial->primaryColor.A * primaryPercent + pDBMaterial->secondaryColor.A * secondaryPercent;
      }
    }
  }
  channel.color = color;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::ResetArea(ChannelType channelId)
{
  NI_ASSERT(0 <= channelId && channelId < _NUM_CHANNELS, NStr::StrFmt("Invalid AOE index %i of %i maximum", channelId, _NUM_CHANNELS));
  AreaChannel& channel = channels[channelId];
  channel.enabled = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::ResetAll()
{
  for (int i = 0; i < _NUM_CHANNELS; i++)
    channels[i].enabled = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AOERenderer::Render()
{
  for (int i = 0; i < _NUM_CHANNELS; i++)
  {
    AreaChannel& channel = channels[i];
    if (channel.enabled && channel.pMaterial)
    {
      channel.pMaterial->SetCustomizedGeometryPin(channel.type != AREA_DISK ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE);
      channel.pMaterial->PrepareRenderer();
      GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);
      GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 0);

      GetRenderer()->SetVertexShaderConstantsMatrix(WORLD, channel.xform);
      GetRenderer()->SetVertexShaderConstantsFloat(VSHADER_LOCALCONST0, channel.radius);

      if ( saturate )
        GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST0, Render::Saturate( channel.color, saturation, satColor ) );
      else
        GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST0, channel.color );

      switch (channel.type)
      {
      case AREA_DISK:
        quad.Bind();
        quad.Draw();
        break;
      case AREA_SECTOR:
        GetRenderer()->SetVertexShaderConstants(VSHADER_LOCALCONST1, ARRAY_SIZE(fanParams), fanParams);
        fan.Bind();
        fan.Draw();
        break;
      case AREA_LINE:
      case AREA_WALL:
        GetRenderer()->SetVertexShaderConstants(VSHADER_LOCALCONST1, ARRAY_SIZE(stripParams[i]), stripParams[i]);
        strip.Bind();
        strip.Draw();
        break;
      default:
        NI_ALWAYS_ASSERT(NStr::StrFmt("Unknown AOE area type %i", channel.type));
      }

      GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 1);
      GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 1);
    }
  }
}

bool AOERenderer::IsActive( ChannelType channelId )
{
  NI_ASSERT(0 <= channelId && channelId < _NUM_CHANNELS, NStr::StrFmt("Invalid AOE index %i of %i maximum", channelId, _NUM_CHANNELS));
  AreaChannel& channel = channels[channelId];
  return (channel.enabled);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}; // namespace Render

// end of AOERenderer.cpp
