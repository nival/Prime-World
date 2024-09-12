#include "stdafx.h"
#include "WaterMesh.h"
#include "WaterManager.h"
#include "shadercompiler.h"
#include "ImmediateRenderer.h"
#include "GlobalMasks.h"

static const bool noRefraction = true;

static CVec4 reflColors[2];

// ATTENTION!!! There is corresponding define in WaterMaterial.hlsl. They should have the same state!
//#define SKY_FROM_CUBEMAP

SINGLETON4DLL_DEF(Render::WaterManager)

namespace Render
{

void WaterLevel::PushWaterBatches( BatchQueue &queue )
{
	ListElement *pLE = pHead;
	while ( pLE )
	{
		pLE->pWaterMesh->RenderToQueuePostponed( queue );
		pLE = pLE->pNext;
	}
}

void WaterLevel::BuildMatricesForReflection(SceneConstants *_pOutConsts, const SceneConstants &_inConsts, float _levelShift) const
{
	SHMatrix& invView = _pOutConsts->invView;
  invView = _inConsts.invView;
	// Reflection of matrix = reflection of 3 vectors (by y) + negation of x-vector + reflection of pos.y (by level)
	invView.zx = -invView.zx;
	invView.xy = -invView.xy;
	invView.yy = -invView.yy;
	invView.zz = -invView.zz;
	invView.zw = 2 * level - invView.zw;
	_pOutConsts->view.HomogeneousInverse(invView);

  CVec4 reflPlane(0, 0, 1, -level + _levelShift);
  invView.RotateHVectorTransposed(&reflPlane, reflPlane);

	// Correct projection matrix
  SHMatrix& projection = _pOutConsts->projection;
  //projection = _inConsts.projection;
  NI_ASSERT(!projection._12 && !projection._14 && !projection._21 && !projection._24 && !projection._31 && !projection._32
            && !projection._41 && !projection._42 && (1.0f == projection._43) && !projection._44,
            "Unsupported projection matrix");

  CVec4 corner( (Sign(reflPlane.x) - projection._13) / projection._11,
                (Sign(reflPlane.y) - projection._23) / projection._22,
                1.0f, (1.0f - projection._33) / projection._34 );

  //CVec4 scaledPlane = reflPlane / reflPlane.Dot(corner); 
  (CVec4&)projection.m[2] = reflPlane / reflPlane.Dot(corner);
}

WaterManager::WaterManager( const CreateParams &pars )
	: isReflectionRendering(false)
	, isRefractionEnabled(true)
	, animationSpeedFactor(1.0f)
  , hnTexture( 4, Render::FORMAT_A8R8G8B8 )
  , pDummyMaterial( static_cast<BaseMaterial*>(CreateRenderMaterial(NDb::WaterDummyMaterial::typeId)) )
{
	halfMtx.Set( 0.5f,  0.0f, 0.0f, 0.5f,
							 0.0f, -0.5f, 0.0f, 0.5f, 
							 0.0f,  0.0f, 1.0f, 0.0f, 
							 0.0f,  0.0f, 0.0f, 1.0f );
  halfMtxV = halfMtx;
	//
	listElements.reserve(20); // Reserve N elements for N visible water static meshes
	// Here we'll analyze resolution width & height and evaluate dimensions of water render target texture
	const RenderMode& renderMode = GetRenderer()->GetCurrentRenderMode();
	int width = int( renderMode.width3D * pars.reflectionTextureSizeFactor );
	int height = int( renderMode.height3D * pars.reflectionTextureSizeFactor );
	// Create textures
  if( NGlobal::GetVar( "waterrefl" ).GetInt64() )
	  pRTTexture = Render::CreateRenderTexture2D( width, height, FORMAT_A8R8G8B8 );

	pRTDepth   = Render::CreateDepthStencilSurface( width, height );
	// Create texture for refraction
	if (isRefractionEnabled)
	{
		width = int( renderMode.width3D * pars.refractionTextureSizeFactor );
		height = int( renderMode.height3D * pars.refractionTextureSizeFactor );
		pRefrTexture = Render::CreateRenderTexture2D( width, height, FORMAT_A8R8G8B8 );
	}
	//
	pReflTexClearPS = 0;//CompilePixelShaderFromFile("../data/Shaders/OnlineShaders/refltex_clear.hlsl");
  pDummyMaterial->SetMaterialFlags((NDb::MaterialFlags)(pDummyMaterial->GetMaterialFlags() | NDb::MATERIALFLAGS_SHADOWRECEIVER));
}

void WaterManager::SetAnimationSpeedFactor( float factor ) 
{ 
	Get()->animationSpeedFactor = factor; 
}

void WaterManager::SetReflectedColors(const HDRColor& _color0, const HDRColor& _color1)
{ 
  reflColors[0] = (CVec4&)_color0;
  reflColors[1] = (CVec4&)_color1;
}

void WaterManager::StartRenderingToReflectionTexture(/*const Render::SceneConstants &sceneConsts, float level*/ bool _clearColor)
{
	if(pRTTexture)
    SmartRenderer::BindRenderTarget(pRTTexture, pRTDepth);

  if(_clearColor)
    GetRenderer()->Clear(Color(77,138,175,0));
  else
    GetDevice()->Clear(0, 0, D3DCLEAR_STENCIL|D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	//// Transform plane
	//CVec4 worldPlane(0.0f, 0.0f, 1.0f, -level + 0.05f);
	//CVec4 plane;
	//SHMatrix invVP;
	//Invert( &invVP, sceneConsts.viewProjection );
	//invVP.RotateHVectorTransposed( &plane, worldPlane );

	//GetRenderer()->SetClipPlane(true, &plane);
}

void WaterManager::ShowWaterTexture(int index)
{
	CTRect<float> rect(-0.9f, -0.5f, -0.2f, 0.5f)/*, rect2( -0.1f, -0.5f, 0.6f, 0.5f )*/;
	switch (index)
	{
		case 1:
			GetImmRenderer()->RenderScreenQuad(rect, ImmRenderer::Params("DiffuseMap", pRTTexture));
			break;
		case 2:
			GetImmRenderer()->RenderScreenQuad(rect, ImmRenderer::Params("DiffuseMap", pRefrTexture));
			break;
		case 3:
			GetImmRenderer()->RenderScreenQuad(rect, ImmRenderer::Params("NormalMap", GetHDxDyTexture()));
      //GetImmRenderer()->RenderScreenQuad(rect2, ImmRenderer::Params("NormalMapTest", hnTexture.getTexture()));
			break;
	}
}

void WaterManager::SetupTextureMatrix(const Render::Texture2D &_texture)
{
  if ( SmartRenderer::UseMainViewport() )
  {
    int x, y, width, height;

    SmartRenderer::GetMainViewport( x, y, width, height );

    const float x_scale = 1.f / float( _texture.GetWidth() );
    const float y_scale = 1.f / float( _texture.GetHeight() );

    float scaleX = 0.5f * x_scale * width;
    float scaleY = 0.5f * y_scale * height;

    halfMtxV.m[0][0] = scaleX;
    halfMtxV.m[1][1] = -scaleY;

    halfMtxV.m[0][3] = scaleX + x_scale * x;
    halfMtxV.m[1][3] = scaleY + y_scale * y;
  }
  else
    halfMtxV = halfMtx;
}

static inline void SetCorrectedMatrix(UINT _startIdx, const SHMatrix &_src, const SHMatrix &_corrector, bool setInVS = false)
{
  SHMatrix result;
  Multiply(&result, _corrector, _src);
  if(setInVS)
    GetRenderer()->SetVertexShaderConstantsMatrix(_startIdx, result);
  else
    GetRenderer()->SetPixelShaderConstantsMatrix(_startIdx, result);
}

static inline void SetCorrectedMatrix(UINT _startIdx, const SHMatrix &_src, SHMatrix &_corrector, const Render::Texture2D &_texture, bool setInVS = false)
{
  float &shiftX = _corrector.m[0][3], &shiftY = _corrector.m[1][3];
  const float shiftXold = shiftX, shiftYold = shiftY;
  shiftX += 0.5f / _texture.GetWidth();
  shiftY += 0.5f / _texture.GetHeight();
  SetCorrectedMatrix(_startIdx, _src, _corrector, setInVS);
  shiftX = shiftXold;
  shiftY = shiftYold;
}

void WaterManager::StartWaterSurfaceRendering( const SHMatrix &reflViewProj, const SHMatrix &refrViewProj, const Render::SceneConstants &sceneConsts, Render::Texture2DRef const& pMainDepth )
{
  ConstantProtectionBlock block(CCONTEXT_WATER);

  Renderer* const pRenderer = GetRenderer();
  RenderStatesManager* const pStatesManager = GetStatesManager();

	// Set reflection texture
	pStatesManager->SetSampler(0, SamplerState::PRESET_CLAMP_BILINEAR(), pRTTexture);
	// Set refraction texture
	pStatesManager->SetSampler(1, SamplerState::PRESET_CLAMP_BILINEAR(), pRefrTexture);
	// Set depth buffer texture
	pStatesManager->SetSampler(2, SamplerState::PRESET_CLAMP_BILINEAR(), pMainDepth);
	// Set water texture
  pStatesManager->SetSampler(3, SamplerState::PRESET_WRAP_BILINEAR(), GetHDxDyTexture() );
	
  SetupTextureMatrix(*pMainDepth);

	// Set reflection matrix
  SetCorrectedMatrix(WATER_REFLECTION_MTX, reflViewProj, halfMtx);
	// Set refraction matrix
  SetCorrectedMatrix(noRefraction ? VSHADER_LOCALCONST6 : WATER_REFRACTION_MTX, refrViewProj, halfMtxV, *pMainDepth, noRefraction);

  // Set camera matrix
	pRenderer->SetPixelShaderConstantsVector4(WATER_VIEWINV_Z, sceneConsts.invView.GetZ());

	// Set inverse projection data
	pRenderer->SetPixelShaderConstantsVector4(WATER_PARAMS0, CVec4(1.0f / sceneConsts.projection.xx, 1.0f / sceneConsts.projection.yy, 0.0f, 0.0f));

  if( GetRuntimePins().ShaderQualityValue == NDb::SHADERQUALITYPIN_FAST )
  {
    pRenderer->SetPixelShaderConstants(PSHADER_LOCALCONST3, 2, reflColors);
  }

  //{ // account for viewport
  //  int x, y, width, height;

  //  SmartRenderer::GetMainViewport( x, y, width, height );

  //  NI_ASSERT(x == 0 && y == 0, "bad viewport");
  //  const float x_scale =  width / float( pMainDepth->GetWidth() );
  //  const float y_scale = height / float( pMainDepth->GetHeight() );

  //  pRenderer->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST5, CVec4( x_scale, y_scale, 0.0f, 0.0f) );
  //}

	// Set blending state
	Render::RenderState renderState;
	renderState.SetBlendMode(NDb::BLENDMODE_OFF);
	renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
	renderState.SetCulling(NDb::ONOFFSTATE_ON);
	pStatesManager->SetState(renderState);
	pStatesManager->SetStateDirect(D3DRS_ZENABLE, 1);
	pStatesManager->SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  pStatesManager->SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption

	// Disable clip plane
	pRenderer->SetClipPlane(false, NULL);
}

void WaterManager::StopWaterSurfaceRendering()
{
  GetStatesManager()->SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F); // enable alpha

  SmartRenderer::BindTexture(2, GetEmptyTexture2D());
  SmartRenderer::BindTexture(3, GetEmptyTexture2D());
	GetRenderer()->ResetConstantProtectionBlock(CCONTEXT_WATER);
}

void WaterManager::Update( float time )
{
  hnTexture.Update( time );

	if ( waterLevels.size() == 0 )
		return;

	// Copy main target to refraction surface
  const RenderMode &mode = GetRenderer()->GetCurrentRenderMode();
  RECT srcRect = { 0, 0, mode.width3D, mode.height3D };

  GetDevice()->StretchRect(SmartRenderer::GetRenderTarget(0), &srcRect, ::Get(pRefrTexture->GetSurface(0)), NULL, D3DTEXF_LINEAR);
}

void WaterManager::AddWaterMesh(WaterMesh &mesh)
{
	float level = mesh.GetLevel();

	// Add new element
	WaterLevel::ListElement &listElem = listElements.push_back();
	listElem.pWaterMesh = &mesh;

	// Find where to link it
	for (TWaterLevelVector::iterator it = waterLevels.begin(); it != waterLevels.end(); ++it)
	{
		if (fabsf(it->level - level) < 0.1f) // 10 cm tolerance
		{	
			// The same level is found! Link to corresponding water level
			listElem.pNext = it->pHead;
			it->pHead = &listElem;
			// Job done - exit
			return;
		}
	}

	// New level required
  NI_ASSERT( waterLevels.size() < g_numWaterLevels, "Try add excess water mesh" );
	WaterLevel &newLevel = waterLevels.push_back();
	newLevel.pHead = &listElem;
	newLevel.level = level;
	listElem.pNext = 0;
}

}