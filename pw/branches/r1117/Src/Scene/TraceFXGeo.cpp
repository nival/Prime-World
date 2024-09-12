#include "stdafx.h"
#include "TraceFXGeo.h"

#include "../Render/dxutils.h"
#include "../Render/smartrenderer.h"
#include "../Render/vertexformatdescriptor.h"
#include "../Render/renderer.h"

#include "../System/InlineProfiler.h"

static bool s_draw_traces = true;
REGISTER_DEV_VAR("draw_traces", s_draw_traces, STORAGE_NONE);

namespace
{
  DECLARE_NULL_RENDER_FLAG

	struct Vertex
	{
		CVec3 pos;
		CVec2 param;
	};

  enum { TRACE_VB_SIZE = 0x10000 }; // 64K
  Render::SharedVB s_TraceVB(TRACE_VB_SIZE);

  struct GeometryDesc
  {
    DXVertexDeclarationRef pVDecl;
    DXIndexBufferRef pIB;

    GeometryDesc()
    {
      pIB = Render::CreateIB16(TraceFXGeo::MAX_SEGMENTS * 2 * 2 * sizeof(WORD), Render::RENDER_POOL_MANAGED);

      Render::VertexFormatDescriptor vf;
      vf.AddVertexElement(Render::VertexElementDescriptor(0,  0, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0));
      vf.AddVertexElement(Render::VertexElementDescriptor(0, 12, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0));
      pVDecl = Render::SmartRenderer::GetVertexFormatDeclaration( vf );

      WORD* pIndex;
      if(pIB->Lock(0, 0, (void**)&pIndex, 0) == D3D_OK)
      {
        unsigned int n = TraceFXGeo::MAX_SEGMENTS * 2;
        for (unsigned int i = 0; i < 2 * n; i++)
          pIndex[i] = i % n;
        pIB->Unlock();
      }
    }
  };

  Render::ManagedResource< Render::SimpleInitializer<GeometryDesc> > s_GeoDesc;

}	// anonymous namespace


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TraceFXGeo::TraceFXGeo(): adding(false), offsetColor(0.0f), offsetAlpha(0.0f), scaleOffset(0.0f, 0.0f, 0.0f, 0.0f)
{
  dipDescr.primitiveType = Render::RENDERPRIMITIVE_TRIANGLESTRIP;
  dipDescr.baseVertexIndex = 0;
  dipDescr.minIndex = 0;
  dipDescr.numVertices = MAX_SEGMENTS * 2; // smirnov [2009/1/21]: slow, need to specify exact vertex block
  dipDescr.primitiveCount = 0;
  dipDescr.startIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TraceFXGeo::~TraceFXGeo()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::Clear()
{
	segments.clear();
  dipDescr.primitiveCount = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::Begin(float t, float dt)
{
  NI_PROFILE_FUNCTION

  ASSERT(!adding);
  adding = true;

	// crop the farthest tail segments (which should be transparent)
	int n = segments.size();
	while (n-- > 1 && max(segments.top(1).ta, segments.top(1).tb) < t - dt)
		segments.pop();

	struct F0F1 {
		// f(x) = ax + b, f(x0) = 0, f(x1) = 1
		static void Solve(float x0, float x1, float* pScale, float* pOffset) {
			*pScale = fabs(x1 - x0) < 1e-5f ? 0.0f : 1.0f / (x1 - x0);
			*pOffset = -x0 * (*pScale);
		}
	};

	F0F1::Solve(t - dt, t - offsetColor * dt, &scaleOffset.x, &scaleOffset.z);
	F0F1::Solve(t - dt, t - offsetAlpha * dt, &scaleOffset.y, &scaleOffset.w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::Append(CVec3 const& a, float ta, CVec3 const& b, float tb)
{
  NI_PROFILE_FUNCTION

  ASSERT(adding);
	segments.push(Segment(a, ta, b, tb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TraceFXGeo::ReplaceLast(CVec3 const& a, float ta, CVec3 const& b, float tb)
{
  ASSERT(adding);
  if (segments.size() < 2)
  {
    Append(a, ta, b, tb);
    return false;
  }
  segments.back() = Segment(a, ta, b, tb);
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::End()
{
  NI_PROFILE_FUNCTION

  ASSERT(adding);
	adding = false;

  if(!s_draw_traces)
    return;

	// smirnov [2009/1/21]: slow, need to update only changed segments
  NI_STATIC_ASSERT(2 * sizeof(Vertex) == sizeof(Segment), Vertex_data_structures_are_different);

  if ( !Render::GetRenderer()->DeviceIsLost() )
  {
    if( s_TraceVB.Lock() && vertexDataHolder.AcquireSpace(MAX_SEGMENTS * sizeof(Segment), s_TraceVB) )
    {
      memcpy( (PBYTE)s_TraceVB.GetPointer( vertexDataHolder.GetPosition() ),
              segments.raw_data(), vertexDataHolder.GetSize() );

      dipDescr.startIndex = segments.raw_top_index() * 2;
      dipDescr.primitiveCount = max(0, segments.size() * 2 - 2);
    }
    else
    {
      dipDescr.startIndex = 0;
      dipDescr.primitiveCount = 0;
    }
  }

	// update parameters

	// update bbox
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::Bind() const
{
  if ( !s_draw_traces )
    return;

  if ( vertexDataHolder.IsValid(s_TraceVB) )
  {
    GeometryDesc* const pDesc = s_GeoDesc.Get();
    Render::SmartRenderer::BindVertexDeclaration(pDesc->pVDecl);
    Render::SmartRenderer::BindIndexBuffer(pDesc->pIB);
    s_TraceVB.Unlock();
    Render::SmartRenderer::BindVertexBuffer( 0, s_TraceVB.GetBuffer(), sizeof(Vertex), vertexDataHolder.GetPosition() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFXGeo::Draw() const
{
	if ( dipDescr.primitiveCount && vertexDataHolder.IsValid(s_TraceVB) ) 
  {
		Render::SmartRenderer::DrawIndexedPrimitive(dipDescr);
	}
}


// end of TraceFXGeo.cpp
