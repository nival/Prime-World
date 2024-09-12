#include "stdafx.h"

#include "../Render/renderer.h"
#include "../Render/GlobalMasks.h"
#include "../Render/smartrenderer.h"
#include "../Render/sceneconstants.h"
#include "../System/TimeUtils.h"
#include "../System/LogFileName.h"
#include "../System/StrProc.h"
#include "../System/ProfileManager.h"
#include "../System/FileSystem/FilePath.h"
#include "../System/FileSystem/FileUtils.h"
#include "PFRenderUtils.h"

using namespace Render;

#define DEFAULT_SCREENSHOT_EXTENSION "jpg"

namespace {
string s_screenshotExt(DEFAULT_SCREENSHOT_EXTENSION);
string s_screenshotName;
bool s_screenshotFire = false;
bool s_screenshotAsIs = false;
} // anonymous namespace

namespace PF_Render
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplySceneConstantsCameraOnly( const SceneConstants &sceneConsts )
{
	ConstantProtectionBlock block(CCONTEXT_RENDER_TIME);

	GetRenderer()->SetVertexShaderConstantsMatrix( VIEW,  sceneConsts.view );
	GetRenderer()->SetVertexShaderConstantsMatrix( VIEWPROJECTION, sceneConsts.viewProjection );
	GetRenderer()->SetVertexShaderConstantsMatrix( PROJECTION, sceneConsts.projection );

	CVec4 eyePos = sceneConsts.invView.GetTrans4();
	GetRenderer()->SetVertexShaderConstantsVector4( EYEPOSITION, eyePos );

	CVec4 cameraDir( sceneConsts.view.GetYAxis3(), 0.0f );
	Normalize(&cameraDir);
	GetRenderer()->SetVertexShaderConstantsVector4( CAMERADIRECTION, cameraDir );

	SceneConstants &copy = SceneConstants::RetriveForModification();
	copy.view           = sceneConsts.view;
	copy.viewProjection = sceneConsts.viewProjection;
	copy.projection     = sceneConsts.projection;
	copy.invView        = sceneConsts.invView;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplySceneConstantsColorOnly( const SceneConstants &sceneConsts )
{
	ConstantProtectionBlock block(CCONTEXT_RENDER_TIME);

	if(sceneConsts.pEnvCubeMap)
		SmartRenderer::BindTexture( GLOBALENVIROMENTSAMPLERINDEX, sceneConsts.pEnvCubeMap );

  const CVec4 nightParams(sceneConsts.nightFraction, 1.f - sceneConsts.nightSpecularReduction * sceneConsts.nightFraction, 0.f, 0.f);

	// Vertex shader constants
	GetRenderer()->SetVertexShaderConstantsFloat( RENDERTIME, sceneConsts.renderTime );
  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_NIGHT_PARAMS, nightParams );

	// Pixel shader constants
	GetRenderer()->SetPixelShaderConstantsVector4( LIGHT1DIRECTION, -sceneConsts.light1Direction );
	GetRenderer()->SetPixelShaderConstantsVector4( LIGHT2DIRECTION, -sceneConsts.light2Direction );
	GetRenderer()->SetPixelShaderConstantsHDRColor( AMBIENTCOLOR, sceneConsts.ambientColor );
	GetRenderer()->SetPixelShaderConstantsHDRColor( LIGHT1DIFFUSECOLOR, sceneConsts.diffuse1Color );
	GetRenderer()->SetPixelShaderConstantsHDRColor( LIGHT2DIFFUSECOLOR, sceneConsts.diffuse2Color );
  GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_NIGHT_PARAMS, nightParams );

	//GetRenderer()->SetPixelShaderConstantsFloat(EMISSIVETHRESHOLD, emissiveThreshold);

	SceneConstants &copy = SceneConstants::RetriveForModification();
	copy.renderTime        = sceneConsts.renderTime;
	copy.light1Direction   = sceneConsts.light1Direction;
	copy.light2Direction   = sceneConsts.light2Direction;
	copy.ambientColor      = sceneConsts.ambientColor;
	copy.diffuse1Color     = sceneConsts.diffuse1Color;
	copy.diffuse2Color     = sceneConsts.diffuse2Color;
	copy.minBakedColor     = sceneConsts.minBakedColor;
	copy.maxBakedColor     = sceneConsts.maxBakedColor;
  copy.nightFraction     = sceneConsts.nightFraction;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplySceneConstants( const SceneConstants &sceneConsts )
{
	ApplySceneConstantsCameraOnly( sceneConsts );
	ApplySceneConstantsColorOnly( sceneConsts );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DumpScreenshots()
{
	if (s_screenshotFire)
	{
	  //Поддержка D3DXSaveSurfaceToFile появилась в wine 1.5.6
	  //(коммит ec70b67b8d908d1ee11708d18a75774cb9a9bdf8). Пока мы не перейдём на 
	  //эту, или более позднюю версию, скриншоты можно отключить
    if( !Compatibility::IsRunnedUnderWine() )  
      Render::SmartRenderer::DumpScreenshot(s_screenshotName, s_screenshotAsIs);
      
		s_screenshotFire = false;
	}
}

static bool CommandScreenshot( const char *name, const vector<wstring>& params )
{
  // double check that default extension is correct
  struct not_isalnum { bool operator()(char c) { return !isalnum(c); } };
  NStr::TrimInsideIf(s_screenshotExt, not_isalnum());
  if (s_screenshotExt.empty())
    s_screenshotExt = DEFAULT_SCREENSHOT_EXTENSION;

  int paramIndex = 0;

  // check for AsIs option
  s_screenshotAsIs = false;
  if (paramIndex < params.size())
  {
    string option = NStr::ToMBCS(params[paramIndex]);
    if (NStr::ICmp(option.c_str(), "asis") == 0 || NStr::ICmp(option.c_str(), "as-is") == 0)
    {
      s_screenshotAsIs = true;
      paramIndex++;
    }
  }

  // generate base filename
  string screenshotExt(s_screenshotExt);
  bool nameProvided = paramIndex < params.size();

  if(nameProvided) {
    s_screenshotName = NStr::ToMBCS(params[paramIndex]);
    NFile::NormalizePath(&s_screenshotName);
    
    // append default extension if absent
    switch( s_screenshotName.rfind('.') )
    {
      case string::npos :
        s_screenshotName += '.';
        s_screenshotName += s_screenshotExt;
        break;
      case 0 :
        screenshotExt.assign( s_screenshotName.begin() + 1, s_screenshotName.end() ); // skip '.'
        nameProvided = false;
    }
  }

  if(!nameProvided) {
    tm tim;
    GetOsUtcTime(&tim);
    static char buffer[MAX_PATH];
    sprintf_s(buffer, "%s-%04d.%02d.%02d-%02d.%02d.%02d.%s", NDebug::GetProductName()
      , tim.tm_year, tim.tm_mon, tim.tm_mday
      , tim.tm_hour, tim.tm_min, tim.tm_sec, screenshotExt.c_str());
    s_screenshotName = buffer;
  }

  // prepend path if absent
  if (NFile::GetFilePath(s_screenshotName).empty())
  {
    string path = GetFullFolderPath( NProfile::FOLDER_SCREENSHOTS );
    if (!NFile::DoesFolderExist(path))
      NFile::CreatePath(path);
    s_screenshotName = NFile::Combine(path, s_screenshotName);
  }

	s_screenshotFire = true;
	return true;
}

} // namespace PF_Render

REGISTER_CMD( screenshot, PF_Render::CommandScreenshot );
REGISTER_VAR( "screenshot_ext", s_screenshotExt, STORAGE_USER );