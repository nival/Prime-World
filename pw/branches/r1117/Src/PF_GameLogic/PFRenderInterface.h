#pragma once

#include "../Scene/RenderableScene.h"
#include "../Scene/SHGrid.h"
#include "../Render/RenderInterface.h"
#include "../Render/batch.h"
#include "../Render/texture.h"
#include "../Render/FullScreenFX.h"
#include "PFPostFXParams.h"

namespace NScene
{
  class SceneObject;
}

namespace Terrain {
  class TerrainTextureCache;
}

namespace PF_Render
{
class Interface : public Render::Interface, public Render::DeviceLostHandler
{
protected:
  Interface(HWND hwnd = 0);

public:
  ~Interface();
	virtual bool Start( Render::RenderMode& renderMode );

  void CreateRTs( const Render::RenderMode &mode );
  void ApplyNewParams( const Render::RenderMode &_renderMode );
  void InvalidateResources();
  static void CorrectRendermode( Render::RenderMode &_renderMode );

  virtual void Stop();

  virtual void Render( bool bEditorSpecific );
  virtual void Render( bool bEditorSpecific, int x, int y, int width, int height );

  virtual void RenderUI( bool bEditorSpecific ); //special part for compulsory part of render
  virtual void FlushUI();

  virtual void ConstrainRender(const RECT &_rect) { renderArea = _rect; }

  // From Render::DeviceLostHandler
  virtual void OnDeviceLost() {}
  virtual void OnDeviceReset();

  virtual bool SetShadows( bool val );

	// From NScene::Renderer2Texture
	virtual void Render2SHTexture(const SHMatrix &view, const SHMatrix &proj, const Render::BatchQueue &queue);
	
  Render::Texture2DRef GetDepthTexture() { return pMainRT1; }

  virtual Render::IDebugRender *GetDebugRender() { return &debugRender; }

  CVec4 GetVisibleNature() const { if (pPostFXMan) return pPostFXMan->GetCoeffValue(); return VNULL4; }
  
  static Interface * Get() { return static_cast<Interface *>( Render::Interface::Get() ); }
  
  void SetColorSaturation( float val ) { NI_ASSERT(val >= 0 && val <= 1.0f, NStr::StrFmt("Invalid saturation value %f", val) ); colorSaturation = val; }
  void SetCustomSaturationColor( const CVec4& _col, bool _useColor ) { customSaturationColor = _col; useSaturationColor = _useColor; }
  void SetPostFXParams( const NDb::PostFXParams* params );

protected:
  void DoPostFX(const Render::SceneConstants & _sceneConsts);
	void RenderMainScene(bool GIsEditor);

  void CopyDepth(const DXSurfaceRef& _dest);
  // resolve Z-buffer (multisampled or not) to pMainDepth
  void CopyDepthRESZ();

private:
	void Init();
  void CreateDepthTextures(UINT _width, UINT _height, UINT _copy_width, UINT _copy_height);
  void CreateAdditionalRTs(UINT _width, UINT _height);
  void CreateMainTextures( UINT _width, UINT _height );
  DXSurfaceRef GetDepthSurface();

	void SetDefaultStates();
	void DropAllSamplerStates();
	void RenderSunShadow(const Render::SceneConstants& sceneConsts, IRenderableScene* pScene, float _minHeight, float _maxHeight);
	void RenderHeightfog();

	void RenderDecals(const Render::BatchQueue &queue, NDb::MaterialPriority priority, Render::Texture2D *pDepthTex = 0);
  bool RenderDecalMask( const Render::BatchQueue &queue, NDb::MaterialPriority priority, Render::Texture2D *pDepthTex = 0);
	void RenderOpaque(const Render::BatchQueue &queue, NDb::MaterialPriority priority);
  void RenderSilhouette(const Render::BatchQueue &queue);

	void RenderMainPassOpaque(const Render::BatchQueue &queue);
  void RenderMainPassTransparent(const Render::BatchQueue &queue);
	void RenderMainPassDistortion(const Render::BatchQueue &queue);

  void ProcessSilhouettes(const Render::SceneConstants & sceneConsts);
  void AddObjectSilhouette(NScene::SceneObject* pObject, Render::HDRColor const& color, const Render::SceneConstants & sceneConsts);

  void SetScreenToTextureTransform();

  void CalculateNaturePercent();

  void SwapRTInChain();
  void PrepareForUI(bool _isEditor);
  void DebugRenderTextures();

	Render::BatchQueueSorter batchQueueSorter;
	Render::BatchQueue mainBatchQueue;
	Render::BatchQueue tempBatchQueue;
	Render::BatchQueue shadowBatchQueue;

	ScopedPtr<Render::ConvexVolume> pWaterReflectedFrustum;

	Render::Texture2DRef pRT0Big;
  Render::Texture2DRef pRT0BigCopy;
  Render::Texture2DRef pMainRT0;
	Render::Texture2DRef pMainRT1;
  Render::Texture2DRef pMainRT0Copy;
	Render::Texture2DRef pMainRT1Copy;
  Render::Texture2DRef pMainDepth;

  Render::Texture2DRef firstRTInChain;   
  Render::Texture2DRef secondRTInChain;
  
  Render::Texture2DRef decalRT;
  bool decalRTCreated;

  const char* depthCopyShaderName;

  ScopedPtr<PostFXParamsManager> pPostFXMan;
  ScopedPtr<Render::FullScreenFX> pPostFX;

	vector<RenderableSceneObj*> gatheredRenderableObjects; // used in water

  float visibleNaturePercent[NDb::KnownEnum<NDb::ENatureType>::sizeOf];
  Render::DebugRender debugRender;

  float silhouetteThickness;
  ScopedPtr<Render::BaseMaterial> pSilhouetteMaterialStatic;
  ScopedPtr<Render::BaseMaterial> pSilhouetteMaterialSkeletal;

	friend struct WaterLevelsProcessor;
  
  float colorSaturation;
  CVec4 customSaturationColor;
  bool useSaturationColor;

  DWORD width3D, height3D;
  RECT  renderArea;

  IRenderableScene::SkipFrameSignal skipFrame;
  bool doRTSwap;
}; // class Interface
}; // namespace PF_Render
