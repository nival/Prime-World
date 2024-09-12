#include "stdafx.h"
#include "LightningFX.h"
#include "../System/Spline.h"
#include "../System/DebugVar.h"
#include "../System/RandomGen.h"
#include "../Render/batch.h"
#include "../Render/renderer.h"
#include "../Render/GlobalMasks.h"
#include "../Render/debugrenderer.h"
#include "../Render/smartrenderer.h"
#include "../Render/sceneconstants.h"

LightningFX::Params const LightningFX::DEFAULT_PARAMS;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
  DECLARE_NULL_RENDER_FLAG

  struct Vertex
	{
		CVec3 pos;
		CVec4 param; // [texcoordV, startShiftCoeff, endShiftCoeff, opacity]
	};
	static Vertex s_vertices[] = {
		{CVec3( 0.0f, -1.0f, 0.0f), CVec4(1.0f, 0.0f, 0.0f, 0.0f)},
		{CVec3( 0.0f, +1.0f, 0.0f), CVec4(0.0f, 0.0f, 0.0f, 0.0f)},
    {CVec3( 0.0f, -1.0f, 0.0f), CVec4(1.0f, 1.0f, 0.0f, 1.0f)},
    {CVec3( 0.0f, +1.0f, 0.0f), CVec4(0.0f, 1.0f, 0.0f, 1.0f)},
    {CVec3( 0.0f, -1.0f, 1.0f), CVec4(1.0f, 0.0f,-1.0f, 1.0f)},
    {CVec3( 0.0f, +1.0f, 1.0f), CVec4(0.0f, 0.0f,-1.0f, 1.0f)},
		{CVec3( 0.0f, -1.0f, 1.0f), CVec4(1.0f, 0.0f, 0.0f, 0.0f)},
		{CVec3( 0.0f, +1.0f, 1.0f), CVec4(0.0f, 0.0f, 0.0f, 0.0f)},
	};
	static unsigned int s_indices[] = {
		0, 1, 3,
		0, 3, 2,
    2, 3, 5,
    2, 5, 4,
    4, 5, 7,
    4, 7, 6,
	};
}	// anonymous namespace


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LightningFX::LightningFX()
	: params(LightningFX::DEFAULT_PARAMS)
	, enabled(true)
	, worldMatrix(IDENTITY_MATRIX)
	, pMaterial(NULL)
	, scrollOffset(0.0f)
	, animFrame(0)
	, progress(1.0f)
{
  if(RENDER_DISABLED)
    return;

	geo.SetVertexStream(Render::CreateVB(sizeof(s_vertices), Render::RENDER_POOL_MANAGED, s_vertices), sizeof(Vertex));
	geo.SetIndexBuffer(Render::CreateIB(sizeof(s_indices), Render::RENDER_POOL_MANAGED, s_indices));

	Render::DipDescriptor &dipDescr = geo.GetDipDescriptor();

	Render::VertexFormatDescriptor vf;
	vf.AddVertexElement(Render::VertexElementDescriptor(0,  0, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0));
	vf.AddVertexElement(Render::VertexElementDescriptor(0, 12, Render::VERTEXELEMENTTYPE_FLOAT4, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0));
	geo.SetVertexDeclaration( Render::SmartRenderer::GetVertexFormatDeclaration(vf) );
	dipDescr.primitiveType = Render::RENDERPRIMITIVE_TRIANGLELIST;
	dipDescr.baseVertexIndex = 0;
	dipDescr.numVertices = ARRAY_SIZE(s_vertices);
	dipDescr.primitiveCount = ARRAY_SIZE(s_indices) / 3;
	dipDescr.startIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LightningFX::~LightningFX()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::SetMaterial(NDb::LightningMaterial const* pDBMaterial)
{
	if (pDBMaterial)
		Reset(pMaterial, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial(pDBMaterial)));
	else
		Reset(pMaterial, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::SetParameters(Params const& newParams)
{
	params = newParams;
	animFrame = params.animFirstFrame;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::SetProgress(float progress)
{
	ASSERT(0.0f <= progress && progress <= 1.0f);
	this->progress = progress;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::RenderToQueue( Render::BatchQueue &queue )
{
	if (!pMaterial)
		return;

	queue.Push(NDb::MATERIALPRIORITY_TRANSPARENT, this, &geo, 0, Get(pMaterial));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
	Render::Renderer* renderer = Render::GetRenderer();
	
	renderer->SetVertexShaderConstantsMatrix(WORLD, xform);
  renderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, scaleOffset);
  renderer->SetVertexShaderConstantsColor(VSHADER_LOCALCONST1, params.color);
	renderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST2, CVec4(params.opacityDistance1, params.opacityDistance2, 888.888f, 888.888f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::Enable(bool onoff)
{
	if (onoff == enabled)
		return;

	enabled = onoff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float LightningFX::MakeLocalTransform(SHMatrix* res, CVec3 const& a, CVec3 const& b)
{
	// construct orientation matrix
  SHMatrix m;
  {
    CVec3 at = b - a;
    if (!Normalize(&at))
      at = V3_AXIS_Z;

    CVec3 up = at ^ Render::SceneConstants::Global().view.GetZAxis3();
    if (!Normalize(&up))
      up = V3_AXIS_Y;

    CVec3 right = at ^ up;

    res->Set(right.x, up.x, at.x, a.x,
             right.y, up.y, at.y, a.y,
             right.z, up.z, at.z, a.z,
             0.f, 0.f, 0.f, 1.f);
  }

	// scale its length
	float length = fabs(b - a) * progress;
	res->_13 *= length;
	res->_23 *= length;
	res->_33 *= length;

	// scale its radius
	res->_11 *= params.radius;
	res->_21 *= params.radius;
	res->_31 *= params.radius;
	res->_12 *= params.radius;
	res->_22 *= params.radius;
	res->_32 *= params.radius;
	
	return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningFX::Update(CVec3 const& a, CVec3 const& b, float dt)
{
	if (dt <= 0.0f)
		return;

	// update geometry transformation matrix
	SHMatrix orientation;
	float length = MakeLocalTransform(&orientation, a, b);
	SHMatrix world;
	Copy(&world, worldMatrix);
	Multiply(&xform, world, orientation);

	// animate V coordinate in texture atlas
	float increment = 0.0f;
	frameOffset = modf(frameOffset + params.animSpeed * dt, &increment);
  int animFrameCount = Max(0, params.animLastFrame - params.animFirstFrame) + 1;
	switch (params.animType)
	{
	case NDb::LIGHTNINGANIMTYPE_NONE:
		animFrame = params.animFirstFrame;
		break;
	case NDb::LIGHTNINGANIMTYPE_SEQUENTIAL:
		if (increment > 0.0f)
			animFrame = params.animFirstFrame + ((animFrame - params.animFirstFrame) + (int)increment) % animFrameCount;
		break;
	case NDb::LIGHTNINGANIMTYPE_RANDOMIZED:
		if (increment > 0.0f)
			animFrame = params.animFirstFrame + NRandom::Random(animFrameCount);
		break;
	}

	// animate U coordinate
	scrollOffset = modf(scrollOffset + params.scrollSpeed * dt / params.tiling, &increment);

	// prepare UV scale and offset for shader
	float animFrameCountInv = 1.0f / float(params.animAtlasSize);
	scaleOffset.Set(length / params.tiling, animFrameCountInv, -scrollOffset, float(animFrame) * animFrameCountInv);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// end of LightningFX.cpp
