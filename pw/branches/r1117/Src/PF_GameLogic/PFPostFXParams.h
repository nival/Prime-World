#pragma once

#include "../Render/GlobalMasks.h"
#include "../Render/FullscreenFX.h"
#include "../PF_Core/DBEffect.h"

namespace PF_Render
{

class Interface;

class PostFXParamsManager : public Render::DeviceLostHandler
{
protected:
  PostFXParamsManager();

public:
  bool Calculate(bool _postFXEnabled, bool _sharpEnabled, bool _force);  // return true if really done calculation
  Render::TextureVtx* GetCoeff() const { return mapData[currSurf]; }
  CVec4 GetCoeffValue() const { return coeff; }
  void SyncCoeffValue();

  void SetDBParams( const NDb::PostFXParams* params );


  // DeviceLostHandler methods
  virtual void OnDeviceLost();
  virtual void OnDeviceReset();

  static const Render::FullScreenFX::Params* GetPivotParams();
  static void SetOverrideFXParams( const Render::FullScreenFX::Params* params );

private:
  void AcquireSurfaces();
  void OnDBParamsChanged( const NDb::DBID& dbid );
  bool RenderNatureMapToSurface(const DXSurfaceRef& surf);
  //void InterpolateParams(float coefs[NATURE_TYPES_COUNT]);

  NDb::ChangeablePtr<NDb::PostFXParams>  dbParams;

  //Render::FullScreenFX::Params params;

  Render::Texture2DRef  screenMap[2];
  Render::TextureVtxRef mapData[2];
  DXSurfaceRef screenSurf[2];
  DXSurfaceRef mapSurf[2];
  Render::RenderSurfaceRef offscreenSurf;
  UINT currSurf;
  bool isCoeffChanged;
  bool disabled;
  CVec4 coeff;
  void (*coefParser)(void*, CVec4*);
};

}
