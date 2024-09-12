#include "stdafx.h"
#include "Utility.h"
#include "EditorRender.h"
#include "../Render/RenderInterface.h"
#include "../Render/ShadowManager.h"
#include "../UI/FontRender.h"
#include "../UI/SkinStyles.h"
#include "../System/Color.h"
#include "../UI/Root.h"
#include "../UI/Scripts.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Render::Interface *pInterface = 0;
static bool isUILoaded = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK EnumProc(HMONITOR hMonitor, HDC hdc, LPRECT prcMonitor, LPARAM dwData)
{
  SIZE* pSize = reinterpret_cast<SIZE*>(dwData);
  pSize->cx = Max(pSize->cx, prcMonitor->right - prcMonitor->left);
  pSize->cy = Max(pSize->cy, prcMonitor->bottom - prcMonitor->top);
  return TRUE;
}

void EditorRender::Initialize( HWND hEditorWindow, bool loadUI )
{
  if ( loadUI )
  {
    if ( isUILoaded )
      return;
    if ( pInterface )
    {
      UI::Initialize( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot.xdb" ) ) );
      isUILoaded = true;
      return;
    }
  }

	if ( pInterface )
		return;

	pInterface = Render::Interface::Create(hEditorWindow);

  SIZE screenSizeMax = {0, 0};
  EnumDisplayMonitors( 0, 0, EnumProc, LPARAM(&screenSizeMax) );

	Render::RenderMode renderMode;
  renderMode.width = min(4096, screenSizeMax.cx);
  renderMode.height = min(2400, screenSizeMax.cy);
	renderMode.isFullScreen = false;
	renderMode.vsyncCount = 0;
	renderMode.multiSampleQuality = 0;
	renderMode.multiSampleType = Render::MULTISAMPLE_NONE;
	renderMode.refreshRate = D3DPRESENT_RATE_DEFAULT;

  systemLog( NLogg::LEVEL_MESSAGE ) << "Framebuffers size choosed: " << renderMode.width << "x" << renderMode.height << endl;

	pInterface->Start( renderMode );


  Render::ShadowManager::Init();
	
	//Render::RenderManager::SetFade( false ); @BVS@PFRENDER
  if ( loadUI )
  {
    UI::Initialize( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot.xdb" ) ) );
    isUILoaded = true;
  }
	
	pInterface->SetClearColor( Render::Color( 64, 64, 64 ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::Release()
{
	if ( pInterface )
	{
		UI::Release();
		UI::ReleaseUIScript();
		pInterface->Stop();
		delete pInterface;
		pInterface = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int EditorRender::GetWidth()
{
	return Render::GetRenderer()->GetCurrentRenderMode().width;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int EditorRender::GetHeight()
{
	return Render::GetRenderer()->GetCurrentRenderMode().height;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::DrawPoint3D( Vector3 ^point, float size, System::Drawing::Color color )
{
	EditorNative::DrawPoint3D( point->Native, size, color );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::DrawPoint3D( float x, float y, float z, float size, System::Drawing::Color color )
{
	EditorNative::DrawPoint3D( CVec3(x, y, z), size, color );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::DrawCircle3D( Vector3 ^point, float size, int numSegments, System::Drawing::Color color )
{
  EditorNative::DrawCircle3D( point->Native, size, numSegments, color );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::DrawLine3D( Vector3^ point1, Vector3^ point2, System::Drawing::Color color, bool zTest )
{
  EditorNative::DrawLine3D( point1->Native, point2->Native, color, zTest );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::ResetTexture( System::String^ textureFileName )
{
  if ( pInterface )
	  Render::Reset2DTextureFromFile( ToMBCS( textureFileName ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::ReloadShaders()
{
  if ( pInterface )
  	Render::RenderResourceManager::DeferredReloadShaders();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::ReloadGeometry()
{
  if ( pInterface )
    Render::RenderResourceManager::ReloadGeometry( true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::ReloadPFX()
{
  if ( pInterface )
  {
    Render::RenderResourceManager::ReloadPFXNew( true );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::SetFFTT(bool mode)
{
		//Render::RenderManager::SetFFTT( mode ); // @BVS@PFRENDER
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::ToggleShowLocators()
{
	NScene::ToggleShowLocators();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorRender::MarkAsDirtyGeometry( System::String^ filename )
{
	string filename_s = ToMBCS( filename );
	Render::RenderResourceManager::MarkAsDirtyGeometry(filename_s);
	return;
}
void EditorRender::MarkAsDirtyPFX( System::String^ filename )
{
	string filename_s = ToMBCS( filename );
	Render::RenderResourceManager::MarkAsDirtyPFX(filename_s);
	return;
}
void EditorRender::MarkAsDirtySkeletonData( System::String^ filename )
{
	string filename_s = ToMBCS( filename );
	Render::RenderResourceManager::MarkAsDirtySkeletonData(filename_s);
	return;
}
void EditorRender::MarkAsDirtySkeletonAnim( System::String^ filename )
{
	string filename_s = ToMBCS( filename );
	Render::RenderResourceManager::MarkAsDirtySkeletonAnim(filename_s);
	return;
}

void EditorRender::DumpScreenShoot(System::String^ filename)
{
  string filename_s = ToMBCS( filename );
  Render::SmartRenderer::DumpScreenshot( filename_s, false );
}

void EditorRender::SetViewport( float x, float y, float height, float width )
{
  D3DVIEWPORT9 vp;
  vp.X = x;
  vp.Y = y;
  vp.MinZ = 0;
  vp.MaxZ = 1;
  vp.Width = width;
  vp.Height = height;
  Render::GetDevice()->SetViewport(&vp);
}

System::Drawing::Bitmap^ EditorRender::GetSurfaceBuffer()
{
  int width = GetWidth();
  int height = GetHeight();
  byte* data = Render::SmartRenderer::DumpScreenshotToMemory(width,height);
  System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(width,height,width*4,
    System::Drawing::Imaging::PixelFormat::Format32bppRgb, System::IntPtr(data));
  return bitmap;
}

void EditorRender::Present( HWND hEditorWindow )
{
  Render::GetDevice()->Present(0,0,hEditorWindow,0);
}

void EditorRender::ToggleMipMaps()
{
  static bool mipmaps = true;
  Render::ShowMipmapsWithReload( mipmaps );
  mipmaps = !mipmaps;
}

bool EditorRender::SetShadows( bool val )
{
  if ( pInterface )
  {
    return pInterface->SetShadows( val );
  }
  return false;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
