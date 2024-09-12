#include "stdafx.h"
#include "Utility.h"
#include "EditorScene.h"
#include "EditorRender.h"
#include "EditorSound.h"
#include "Settings.h"
#include "TerrainUtils.h"
#include "CompositeTransformController.h"
#include "../Scene/StaticSceneComponent.h"
#include "../Scene/SceneObject.h"
#include "../Scene/VertexColorManager.h"
#include "../Scene/LightingScene.h"
#include "../Render/light.h"
#include "../Render/sceneconstants.h"
#include "../Scene/SHGridCalculator.h"
#include "../Scene/CollisionGeometry.h"
#include "../Scene/BitMap.h"
#include "../Scene/SceneUtils.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

using namespace EditorNative;
using namespace EditorNative::Terrain;
using namespace EditorNative::DebugVars;
using namespace EditorNative::Manipulators;
using namespace EditorNative::SceneElements;
using namespace EditorNative::SceneElements::SceneObjects;

static NDebug::PerformanceDebugVar editorScene_Pick( "Map Pick Time", "MainPerf", 0, 10000, false );
static NDebug::PerformanceDebugVar nativeScene_Pick( "Native Pick Time", "MainPerf", 0, 10000, false );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorScene::EditorScene( IntPtr _handle, Size _screenSize, IObjectTransformControllersProvider^ _provider, bool needSound )
: ppScene ( new CPtr<NScene::IScene>( NScene::CreateScene() ) )
, handle( _handle )
, screenSize ( 3200, 2400 )
, provider( _provider )
, cinemaMode( CinemaMode::None )
, gridAreaSize( 0.0f )
, gridLineDistance( 0.0f )
, gridSubdivisionDistance( 0.0f )
, gridSubdivision( 0 )
, showSelection ( true )
, lightingScene( nullptr )
, viewportMode( false ) // set this to true in order to work with PerfHUD
, minimapMode( false )
, isEnabledEffectsInScene( false )
, isMapLoaded( false )
, drawCollisionSelection( true )
, oldscreenSize(screenSize)
, isNightLighting(false)
{
  if ( handle == IntPtr::Zero )
    NullRenderSignal::Signal( RENDER_DISABLE_FLAG );

	manipulator = gcnew ManipulatorsController();
  camera = gcnew Camera( this );
 
  selectionFrame = gcnew FrameRect( System::Drawing::Color::White );

  if ( needSound )
    EditorSound::Initialize( (HWND)handle.ToPointer() );
  EditorRender::Initialize( (HWND)handle.ToPointer(), false );
  screenSize.Width = EditorRender::GetWidth();
  screenSize.Height = EditorRender::GetHeight();
  oldscreenSize = screenSize;

  NativeScene->Init( "Editor", 1, CVec3(-128.f, -128.f, -128.f), 1024.f );
  NativeScene->CreateMeshVertexColorsManager(true);
	NativeScene->GetCamera()->SetScreenSize( screenSize.Width, screenSize.Height );
  NativeScene->GetCamera()->SetPlanes( 0.5f, 1000.0f );

  camera->Fov = 50.0f;
  ClearViewport(handle);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::InitLightScene()
{
	NI_ASSERT(lightingScene == nullptr, "Lighting scene already initialized");
  NI_ASSERT(ppScene != nullptr, "Scene not available");
  lightingScene = new NScene::LightingScene( *ppScene, terrain->Native );
  terrain->Native->GetGeometryManager().SetLightingScene(lightingScene);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::SetImmediateLightingUpdate(bool bOn)
{
  if ( lightingScene )
  {
    lightingScene->SetImmediateUpdate(bOn);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorScene::~EditorScene()
{
	this->!EditorScene();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorScene::!EditorScene()
{
	if ( lightingScene != nullptr )
	{
		delete lightingScene;
		lightingScene = nullptr;
	}

	if ( !ReferenceEquals( terrain, nullptr ) )
	{
		terrain->Owner = nullptr;
	}

	while ( sceneElements.Count > 0 )
	{
		Remove( sceneElements[0] );
	}

  if ( ppScene != nullptr )
	{
		delete ppScene;
		ppScene = nullptr;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::IScene* EditorScene::NativeScene::get()
{
	if ( ppScene != nullptr )
	{
		return *ppScene;
	}
	else
	{
		return nullptr;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::ICamera& EditorScene::NativeCamera::get()
{
  return camera->Native;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::UpdateCamera( float deltaYaw, float deltaPitch, float deltaDistance, Vector2^ delta, Vector2^ cursorPosition )
{
	if ( NativeScene == nullptr ) 
		return;

	// calculate new anchor position
	NScene::ICamera& nativeCamera = *NativeScene->GetCamera();
	const CVec3 center = camera->Anchor->Native;
	const CVec3 normal = -camera->Direction->Native;
	const CVec2 convertedCursorPosition = ConvertCursorPosition( cursorPosition );
	const CVec3 currentIntersection = GetRayIntersection( nativeCamera, convertedCursorPosition, center, normal );
	const CVec3 prevIntersection = GetRayIntersection( nativeCamera, convertedCursorPosition - delta->Native, center, normal );
	CVec3 newAnchor = center + currentIntersection - prevIntersection;

	if ( terrain != nullptr )
	{
		float height = 0;
		terrain->TryGetHeight( newAnchor.x, newAnchor.y, height );
		newAnchor.z = height;
	}

	camera->Anchor = gcnew Vector3( newAnchor );

	const float MIN = 0.2f;
	const float MAX = 750.0f;
	const float T = 100.0f;
	const float C = Math::Log( MAX / MIN ) / T;

	const float t = Math::Min( Math::Max( (float)Math::Log( camera->Rod / MIN ) / C - deltaDistance, 0.0f ), T );
	camera->Rod = Math::Exp( t * C ) * MIN;

	camera->Yaw += deltaYaw;
	camera->Pitch += deltaPitch;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorNative::EditorScene::SetCameraPosition( Vector3^ position, float yaw, float pitch, float roll, float rod )
{
  NScene::SCameraPosition pos = camera->Position;
  pos.fYaw = ToRadian( yaw );
  pos.fPitch = ToRadian( pitch );
  pos.fRoll = ToRadian( roll );
  pos.fRod = rod;

  CVec3 camDir = pos.GetCameraDir();
  Normalize( &camDir );

  pos.vAnchor = CVec3( position->X, position->Y, position->Z) + camDir * rod;

  camera->Position = pos;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorNative::EditorScene::GetCameraPosition( Vector3^ position, float% yaw, float% pitch, float% roll )
{
  NScene::SCameraPosition pos = camera->Position;
  yaw = ToDegree( pos.fYaw );
  pitch = ToDegree( pos.fPitch );
  roll = ToDegree( pos.fRoll );

  CVec3 camDir = pos.GetCameraDir();
  Normalize( &camDir );

  CVec3 positionVec = pos.vAnchor - camDir * pos.fRod;
  position->X = positionVec.x;
  position->Y = positionVec.y;
  position->Z = positionVec.z;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrameRect::Draw()
{
  if ( hidden )
    return;
  
  const CVec2 topLeft( left, top );
  const CVec2 topRight( left + width, top );
  const CVec2 bottomLeft( left, top + height );
  const CVec2 bottomRight( left + width, top + height );

  DrawLine2D( topLeft, topRight, color );
  DrawLine2D( topRight, bottomRight, color );
  DrawLine2D( bottomRight, bottomLeft, color );
  DrawLine2D( bottomLeft, topLeft, color );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::Draw( System::IntPtr hWnd, float time, float delta )
{
  handle = hWnd;

  const float width = oldscreenSize.Width;
  const float height = oldscreenSize.Height;
  const unsigned int left = ( EditorRender::GetWidth() - width ) / 2;
  const unsigned int top = ( EditorRender::GetHeight() - height ) / 2;

  Render::Rect rect( left, left + width, top, top + height );
  Render::Rect rect_dest( 0, width, 0, height );

	EditorSound::Update( delta );

  NDebug::ResetDebugVarsOnFrame( delta );

	if ( NativeScene != nullptr )
	{
		NativeScene->Update( time, delta, false );
		NativeScene->Draw();
		NScene::ICamera& camera = *NativeScene->GetCamera();
		manipulator->Draw( camera );

		if ( showSelection )
		{
			for each ( SceneElement^ element in sceneElements )
			{
				if ( element->IsVisible )
				{
					element->Draw();
				}
			}
		}

    selectionFrame->Draw();
  	camera.SetViewportSize( 0, 0 );

		if ( gridLineDistance > 0.0f )
			DrawMayaGrid();
	
    Render::Interface* const pIface = Render::Interface::Get();

    pIface->DisableWarFog(true);
    
    if ( oldscreenSize != screenSize )
    {
      ClearViewport(hWnd);
      oldscreenSize = screenSize;
      ClearViewport(hWnd);
    }
    else if ( cinemaMode != CinemaMode::None )
    {
      static const Render::Rect null_rect;
      System::Drawing::Size cinemaSize = CalcCinemaRect(cinemaMode);
      NativeScene->ConstrainRender(null_rect);
      camera.SetScreenSize(cinemaSize.Width, cinemaSize.Height);
      Render::Rect rect_orig( 0, EditorRender::GetWidth(), 0, EditorRender::GetHeight() );
      const unsigned int left = ( oldscreenSize.Width - cinemaSize.Width ) / 2;
      const unsigned int top = ( oldscreenSize.Height - cinemaSize.Height ) / 2;
      Render::Rect rect_cinema( left, left + cinemaSize.Width, top, top + cinemaSize.Height );
      Render::Rect rect_cinema2( 0, cinemaSize.Width, 0, cinemaSize.Height );
      pIface->ConstrainRender(rect_cinema2);
      pIface->Render( true, 0, 0, cinemaSize.Width, cinemaSize.Height );
      pIface->Present( (HWND)hWnd.ToPointer(), rect_cinema2, rect_cinema );
    }
    else {
      if(minimapMode) {
        Render::SceneConstants &g_sceneConsts = Render::SceneConstants::RetriveForModification();
        const Render::SceneConstants & sceneConsts = NativeScene->GetSceneConstants();
        g_sceneConsts.view           = sceneConsts.view;
        g_sceneConsts.viewProjection = sceneConsts.viewProjection;
        g_sceneConsts.projection     = sceneConsts.projection;
        g_sceneConsts.invView        = sceneConsts.invView;

        Render::LogMarker("CreateMinimap");
        pIface->Render(true);
        // pIface->Present( (HWND)hWnd.ToPointer(), rect, rect_dest );
      }
      else if ( viewportMode )
      {
        camera.SetScreenSize( width, height );
        pIface->Render( true, 0, 0, width, height );
        pIface->Present( (HWND)hWnd.ToPointer(), rect_dest, rect_dest );
      }
      else
      {
        NativeScene->ConstrainRender(rect);
        camera.SetScreenSize( EditorRender::GetWidth(), EditorRender::GetHeight() );
        pIface->ConstrainRender(rect);
        pIface->Render( true );
        pIface->Present( (HWND)hWnd.ToPointer(), rect, rect_dest );
      }
    }
	}
}

void EditorScene::ReplaceAllObjectsOnTerrain()
{
  ReplaceAllObjectsOnTerrain( true );   //сначала перосчитываем heightObjects
  ReplaceAllObjectsOnTerrain( false );  //потом все остальные
}

void EditorScene::ReplaceAllObjectsOnTerrain( bool heightObjects )
{
  for each( SceneElement^ element in sceneElements )
  {
    if ( !GameSceneObject::typeid->IsInstanceOfType( element ) )
      continue;

    GameSceneObject^ obj = (GameSceneObject^)element;

    if( heightObjects == obj->GetGameObject()->heightObject )
    {
        obj->ReplaceObjectOnTerrain();
    }
  }
}

void EditorNative::EditorScene::CalcObjectHeightMap()
{
  ClearHeightMapLayer( 1 ); // зануляем слой height объектов

  for each( SceneElement^ element in sceneElements )
  {
    if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
    {
      GameSceneObject^ obj = (GameSceneObject^)element;
      
      if( obj->GetGameObject() )
        if(obj->GetGameObject()->heightObject)
           obj->AddObjectToHeightMap();
    }
  }
}

void EditorNative::EditorScene::TryFullReload( bool isNeedDisableEffectsInScene )
{
  bool isReload = false;
  for each( SceneElement^ element in sceneElements )
  {
    if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
    {
      GameSceneObject^ obj = (GameSceneObject^)element;
      if ( obj->IsPointLight() )
        continue;
      if ( obj->IsFullyLoaded )
        break;
      obj->IsFullyLoaded = true;
      element->Scene = nullptr;
      element->Scene = this;
      isReload = true;
    }
  }
  if ( isReload && isNeedDisableEffectsInScene )
  {
    EnableEffectsInScene( false );
  }
}

array<System::Drawing::Point>^ EditorScene::GetCameraFrustum()
{
	array<System::Drawing::Point>^ points = gcnew array<System::Drawing::Point>(4);

  if ( NativeScene->GetRenderScene() )
  {
    const FrustumIntersection & fi = NativeScene->GetRenderScene()->GetCameraFrustumIntersection();
    for ( int i = 0; i < 4; i++ )
		{
			points[i] = System::Drawing::Point(fi.points[i].x, fi.points[i].y);
		}
  }

	return points;
}

bool EditorScene::IsInCameraFrustum(float x, float y, float z)
{
	return NativeScene->GetRenderScene()->GetCameraFrustum().IntersectSphere(CVec3(x, y, z), 0.0f);
}

System::Drawing::Bitmap^ EditorScene::CreateMinimapTexture()
{
  NScene::SCameraPosition oldPos;
  NScene::SCameraPosition newPos;

  static const float rodScale = 300.f;
  static const float pi_2 = 1.570796f;

  newPos.vAnchor.x = ( terrain->SizeX * Terrain::TerrainUtils::PatchSize ) / 2.0f;
  newPos.vAnchor.y = ( terrain->SizeY * Terrain::TerrainUtils::PatchSize ) / 2.0f;
  newPos.fPitch = - pi_2;

  const float maxSize = Max(newPos.vAnchor.x, newPos.vAnchor.y);
  newPos.fRod = rodScale * maxSize;
  // Не спрашивайте меня, при чём здесь pi/2 - умом это понять нэвозможно. Вообще-то здесь должна быть двойка.
  const float fov = pi_2 * ToDegree( atan(newPos.vAnchor.x / newPos.fRod) );

  const uint e_width  = EditorRender::GetWidth();
  const uint e_height = EditorRender::GetHeight();
  const int e_width_border  = e_width * .1f;
  const int e_height_border = e_height * .1f;
  RECT rect = { -e_width_border, -e_height_border, e_width + e_width_border, e_height + e_height_border };
  NativeScene->ConstrainRender(rect);

  minimapMode = true;
  camera->Native.GetPosition(&oldPos);
  camera->Native.SetPosition(newPos);
  camera->Native.SetPerspectiveTransform(fov, terrain->SizeX, terrain->SizeY, (rodScale - 1.f) * maxSize, newPos.fRod+20.f, 0.f);
  //camera->Native.SetOrthographicTransform( terrain->SizeX * Terrain::TerrainUtils::PatchSize, 
  //  terrain->SizeY * Terrain::TerrainUtils::PatchSize, 0.0f, newPos.fRod+20.0f );
  bool oldShadows = EditorRender::SetShadows( false );

  int vp_x, vp_y, vp_width, vp_height;
  bool useMainViewport = Render::SmartRenderer::UseMainViewport();
  if(useMainViewport)
    Render::SmartRenderer::GetMainViewport(vp_x, vp_y, vp_width, vp_height);
  Render::SmartRenderer::SetMainViewport(0, 0, e_height * terrain->SizeX / float(terrain->SizeY), e_height);

  Draw( handle, 0.0f, 0.0f );
  System::Drawing::Bitmap^ res = EditorRender::GetSurfaceBuffer();

  if(useMainViewport)
    Render::SmartRenderer::SetMainViewport(vp_x, vp_y, vp_width, vp_height);
  Render::SmartRenderer::SetUseMainViewport(useMainViewport);

  minimapMode = false;
  camera->Native.SetPosition(oldPos);
  camera->Native.SetScreenSize(e_width, e_height);
  camera->Native.SetPlanes( 0.5f, 1000.0f );
  camera->Fov = 50.0f;
  EditorRender::SetShadows( oldShadows );

  return res;
}

generic<typename T> where T:SceneElements::SceneElement System::Collections::Generic::IList<T>^ EditorScene::GetSceneElementsByType()
{
  List<T>^ result = gcnew List<T>();

  for each( SceneElement^ element in sceneElements )
  {
		if ( element->GetType() == T::typeid )
    {
      result->Add((T)element);
    }
  }

  return result->AsReadOnly();
}

System::Collections::Generic::IList<SceneElements::SceneElement^>^ EditorScene::GetSceneElementsByType(System::Type^ type)
{
  List<SceneElements::SceneElement^> result = gcnew List<SceneElements::SceneElement^>();

  for each( SceneElement^ element in sceneElements )
  {
    if ( element->GetType() == type )
    {
      result.Add(element);
    }
  }

  return result.AsReadOnly();
}

System::Collections::Generic::IList<SceneElements::SceneElement^>^ EditorScene::GetSceneElements()
{
	return sceneElements.AsReadOnly();
}


void EditorScene::EnableEffectsInScene( bool val )
{
  if ( NativeScene != nullptr )
  {
    NScene::EnableEffectsInScene( NativeScene, val );
    isEnabledEffectsInScene = val;
    if ( isEnabledEffectsInScene )
    {
      NSoundScene::UpdateVolumes( 1.0f, 0.1f, 1.0f, 1.0f );
    }
    else
    {
      NSoundScene::UpdateVolumes( 0.0f, 0.0f, 0.0f, 1.0f );
    }
  }
}

void EditorScene::UpdateAllMSO()
{
  for each( SceneElement^ element in sceneElements )
  {
    if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
    {
      GameSceneObject^ obj = (GameSceneObject^)element;
      if ( obj->IsMSO() )
      {
        int nature = terrain->GetFraction( obj->GetCurrentPlacement()->location->x, obj->GetCurrentPlacement()->location->y );
        obj->SetSceneObject( nature );
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Drawing::Size EditorScene::CalcCinemaRect( CinemaMode mode )
{
  float xSz = screenSize.Width, ySz = screenSize.Height;
  if( mode == CinemaMode::Mode4x3 )
  {
    float unitXsize = (float)screenSize.Width / 4;
    float unitYsize = (float)screenSize.Height / 3;
    float unitSize = min(unitXsize, unitYsize);
    xSz = unitSize * 4;
    ySz = unitSize * 3;
  }	
  else if( mode == CinemaMode::Mode5x4 )
  {
    float unitXsize = (float)screenSize.Width / 5;
    float unitYsize = (float)screenSize.Height / 4;
    float unitSize = min(unitXsize, unitYsize);
    xSz = unitSize * 5;
    ySz = unitSize * 4;
  }	
  else if( mode == CinemaMode::Mode16x9)
  {
    float unitXsize = (float)screenSize.Width / 16;
    float unitYsize = (float)screenSize.Height / 9;
    float unitSize = min(unitXsize, unitYsize);
    xSz = unitSize * 16;
    ySz = unitSize * 9;
  }
  else if( mode == CinemaMode::Mode16x10)
  {
    float unitXsize = (float)screenSize.Width / 16;
    float unitYsize = (float)screenSize.Height / 10;
    float unitSize = min(unitXsize, unitYsize);
    xSz = unitSize * 16;
    ySz = unitSize * 10;
  }

  return System::Drawing::Size( xSz, ySz );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::DrawCinemaRect( System::Drawing::Size size )
{
	int xSz2 = (int)(size.Width / 2);
	int ySz2 = (int)(size.Height / 2);

	int xC = EditorRender::GetWidth() / 2;
	int yC = EditorRender::GetHeight() / 2;

	System::Drawing::Color col = System::Drawing::Color::FromKnownColor(System::Drawing::KnownColor::Red);
	DrawLine2D( CVec2(xC-xSz2, yC-ySz2), CVec2(xC+xSz2-1, yC-ySz2), col );
	DrawLine2D( CVec2(xC+xSz2-1, yC-ySz2), CVec2(xC+xSz2-1, yC+ySz2), col );
	DrawLine2D( CVec2(xC+xSz2-1, yC+ySz2), CVec2(xC-xSz2, yC+ySz2), col );
	DrawLine2D( CVec2(xC-xSz2, yC+ySz2), CVec2(xC-xSz2, yC-ySz2), col );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::DrawMayaGrid()
{
	System::Drawing::Color blackColor = System::Drawing::Color::FromArgb( 192, 192, 192 );
	System::Drawing::Color grayColor = System::Drawing::Color::FromArgb( 96, 96, 96 );

	DrawLine3D( CVec3( -gridAreaSize, 0.0f, 0.0f ), CVec3( 0.0f, 0.0f, 0.0f ), blackColor, true );
	DrawLine3D( CVec3( 0.0f, -gridAreaSize, 0.0f ), CVec3( 0.0f, 0.0f, 0.0f ), blackColor, true );

	DrawLine3D( CVec3( 0.0f, 0.0f, 0.0f ), CVec3( gridAreaSize, 0.0f, 0.0f ), System::Drawing::Color::FromArgb( 255, 128, 128 ), true );
	DrawLine3D( CVec3( 0.0f, 0.0f, 0.0f ), CVec3( 0.0f, gridAreaSize, 0.0f ), System::Drawing::Color::FromArgb( 128, 255, 128 ), true );

	for( float linePosition = gridLineDistance; linePosition < gridAreaSize; linePosition += gridLineDistance )
	{
		DrawLine3D( CVec3( -gridAreaSize, linePosition, 0.0f ), CVec3( gridAreaSize, linePosition, 0.0f ), blackColor, true );
		DrawLine3D( CVec3( -gridAreaSize, -linePosition, 0.0f ), CVec3( gridAreaSize, -linePosition, 0.0f ), blackColor, true );
		DrawLine3D( CVec3( linePosition, -gridAreaSize, 0.0f ), CVec3( linePosition, gridAreaSize, 0.0f ), blackColor, true );
		DrawLine3D( CVec3( -linePosition, -gridAreaSize, 0.0f ), CVec3( -linePosition, gridAreaSize, 0.0f ), blackColor, true );
		
		if ( gridSubdivision > 0 )
		{

			float subdivPosition = linePosition + gridSubdivisionDistance - gridLineDistance;
			for( int i = 0; i < gridSubdivision; ++i, subdivPosition += gridSubdivisionDistance )
			{
				DrawLine3D( CVec3( -gridAreaSize, subdivPosition, 0.0f ), CVec3( gridAreaSize, subdivPosition, 0.0f ), grayColor, true );
				DrawLine3D( CVec3( -gridAreaSize, -subdivPosition, 0.0f ), CVec3( gridAreaSize, -subdivPosition, 0.0f ), grayColor, true );
				DrawLine3D( CVec3( subdivPosition, -gridAreaSize, 0.0f ), CVec3( subdivPosition, gridAreaSize, 0.0f ), grayColor, true );
				DrawLine3D( CVec3( -subdivPosition, -gridAreaSize, 0.0f ), CVec3( -subdivPosition, gridAreaSize, 0.0f ), grayColor, true );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::ShowMayaGrid( float lineDistance, int subdivision, float areaSize )
{
	gridAreaSize = areaSize / 2.0f;
	gridLineDistance = lineDistance;
	if ( subdivision < 2 )
		gridSubdivisionDistance = 0.0f;
	else
		gridSubdivisionDistance = gridLineDistance / subdivision;

	gridSubdivision = subdivision - 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::HideGrid()
{
	gridAreaSize = 0.0f;
	gridLineDistance = 0.0f;
	gridSubdivisionDistance = 0.0f;
	gridSubdivision = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 EditorScene::ConvertCursorPosition( Vector2^ cursorPosition )
{
	NScene::ICamera& camera = *NativeScene->GetCamera();
  CVec2 result;
  if( cinemaMode != CinemaMode::None )
  {
    System::Drawing::Size cinemaSize = CalcCinemaRect(cinemaMode);
    float Width = camera.GetScreenWidth();
    float Height = camera.GetScreenHeight();
    result = cursorPosition->Native;
    result.x -= (screenSize.Width - cinemaSize.Width) / 2.0f;
    result.y -= (screenSize.Height - cinemaSize.Height) / 2.0f;
    result.x *= Width/cinemaSize.Width;
    result.y *= Height/cinemaSize.Height;
  }
  else
  {
    float Width = camera.GetScreenWidth();
    float Height = camera.GetScreenHeight();
    result = CVec2( Width - screenSize.Width, Height - screenSize.Height ) / 2 + cursorPosition->Native;
  }
	
  return result;
}

Vector2^ EditorScene::ConvertCursorPosition2( Vector2^ cursorPosition )
{
  NScene::ICamera& camera = *NativeScene->GetCamera();
  Vector2^ result = nullptr;
  if( cinemaMode != CinemaMode::None )
  {
    System::Drawing::Size cinemaSize = CalcCinemaRect(cinemaMode);
    float Width = camera.GetScreenWidth();
    float Height = camera.GetScreenHeight();
    CVec2 native_result = cursorPosition->Native;
    native_result.x -= ( screenSize.Width - cinemaSize.Width ) / 2.0f;
    native_result.y -= ( screenSize.Height - cinemaSize.Height ) / 2.0f;
    native_result.x *= Width/cinemaSize.Width;
    native_result.y *= Height/cinemaSize.Height;
    result = gcnew Vector2( native_result.x, native_result.y );
  }
  else
  {
    float Width = camera.GetScreenWidth();
    float Height = camera.GetScreenHeight();
    CVec2 native_result = CVec2( Width - screenSize.Width, Height - screenSize.Height ) / 2 + cursorPosition->Native;
    result = gcnew Vector2( native_result.x, native_result.y );
  }

  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PickResult^ EditorScene::Pick( Vector2^ cursorPosition )
{
  if ( !NativeScene ) return nullptr;
  
  NScene::ICamera& camera = *NativeScene->GetCamera();
	const CVec2 realCursorPosition = ConvertCursorPosition( cursorPosition );

	NScene::PickResult pickResult;
  nativeScene_Pick.Start(true);
	NativeScene->Pick( &pickResult, realCursorPosition );
  nativeScene_Pick.Stop();

	List<KeyValuePair<SceneElement^, Vector3^>> pickedElements;

	const CVec3 cameraLocation = this->camera->Location->Native;

  editorScene_Pick.Start(true);

  if(pickResult.hasTerrainIntersection)
  {
    for each ( IPickableSceneElement^ element in pickableElements )
    {
      SceneElement^ se = (SceneElement^)element;

      if(se->IsSelectable)
      {
        Vector3^ pickCoordinate = gcnew Vector3( 0, 0, 0 );
        if ( element->IsIntersectWith( pickResult.terrainIntersection.x, pickResult.terrainIntersection.y, pickCoordinate ) )
        {
          pickedElements.Add( KeyValuePair<SceneElement^, Vector3^>( se, pickCoordinate ) );
        }
      }
    }
  }

  for each ( TcvMarker^ element in tcvMarkers )
  {
		CVec3 pickCoordinate;
		if ( element->IsSelectable && element->TryPick( camera, realCursorPosition, pickCoordinate ) )
		{
			pickedElements.Add( KeyValuePair<SceneElement^, Vector3^>( element, gcnew Vector3( pickCoordinate ) ) );
		}
  }

	for ( int i = 0; i < pickResult.usedIntersections; ++i )
	{
		NScene::Intersection& intersection = pickResult.intersections[i];
    
    int index = intersection.pHull->GetSceneObject()->GetOwnerID();
    
    if(index >= 0 && index < sceneElements.Count)
    {
      if ( sceneElements[index]->IsSelectable )
      {
		    pickedElements.Add( KeyValuePair<SceneElement^, Vector3^>( sceneElements[index], gcnew Vector3( intersection.enter  ) ) );
		  }
    }
	}

  editorScene_Pick.Stop();

	pickedElements.Sort( gcnew Comparison<KeyValuePair<SceneElement^, Vector3^>>( this, &EditorScene::ComparePickedElements ) );

	List<SceneElement^>^ result = gcnew List<SceneElement^>();
	for each ( KeyValuePair<SceneElement^, Vector3^> pair in pickedElements )
	{
    if(!result->Contains(pair.Key))
		  result->Add( pair.Key );
	}

	return gcnew PickResult( gcnew Vector3( pickResult.terrainIntersection ), result, pickResult.hasTerrainIntersection );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditorScene::ComparePickedElements( KeyValuePair<SceneElement^, Vector3^> left, KeyValuePair<SceneElement^, Vector3^> right )
{
  //маркеры всегда вверху списка
  bool leftIsMarker = TcvMarker::typeid->IsInstanceOfType( left.Key );
  bool rightIsMarker = TcvMarker::typeid->IsInstanceOfType( right.Key );

  if	( leftIsMarker && !rightIsMarker)
    return -1;
  
  if	(!leftIsMarker && rightIsMarker)
    return 1;
  
  return fabs( camera->Location->Native - left.Value->Native ).CompareTo( fabs( camera->Location->Native - right.Value->Native ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PickResult^ EditorScene::PickByFrame( float left, float top, float right, float bottom )
{
  List<SceneElement^>^ result = gcnew List<SceneElement^>();

  for each ( SceneElement^ element in sceneElements )
  {
    if ( !element->IsSelectable )
      continue;

    const CVec3 location = element->LocationInternal;

    float height = 0;
    if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
    {
      terrain->TryGetHeight( location.x, location.y, height );
    }
    const CVec2 projectedLocation = PerformProjection( camera->Native, location + CVec3( 0, 0, height ) );

    if ( projectedLocation.x >= left && projectedLocation.x <= right && projectedLocation.y >= top && projectedLocation.y <= bottom	)
      result->Add( element );
  }

  return gcnew PickResult( gcnew Vector3( 0, 0, 0 ), result, false );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::Add( SceneElement^ element )
{
  if ( ReferenceEquals( element, nullptr ) || sceneElements.Contains( element ) )
    return;

  sceneElements.Add( element );
  element->SetOwnerId(sceneElements.Count-1);
  element->Scene = this;
  
  //we need to fill this Lists for optimize Pick() method
  if ( TcvMarker::typeid->IsInstanceOfType( element ) )
	  tcvMarkers.Add((TcvMarker^)element);
	else if ( IPickableSceneElement::typeid->IsInstanceOfType( element ) )
    pickableElements.Add((IPickableSceneElement^)element);  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::Remove( SceneElement^ element )
{             
  int index = sceneElements.IndexOf( element ); 
  
  if(index == -1) return;

	//Deselect( element );
  element->IsSelected = false;
  element->Scene = nullptr;

  //дешевый remove, не надо перестраивать весь список
  sceneElements[index] = sceneElements[sceneElements.Count - 1];
  sceneElements[index]->SetOwnerId( index );//it needs for optimize Pick
  sceneElements.RemoveAt( sceneElements.Count - 1 );

  //don't forget remove unused elements from this Lists too
	if ( TcvMarker::typeid->IsInstanceOfType( element ) )
    tcvMarkers.Remove((TcvMarker^)element);
	else if ( IPickableSceneElement::typeid->IsInstanceOfType( element ) )
    pickableElements.Remove((IPickableSceneElement^)element);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::SceneTerrain::set( EditorTerrain^ value )
{
	if ( !ReferenceEquals( terrain, value ) )
	{
		if ( HasTerrain )
		{
			terrain->Owner = nullptr;
		}

		terrain = nullptr;

		if ( !ReferenceEquals( value, nullptr ) )
		{
			value->Owner = this;
		}

		terrain = value;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::CurrentManipulator::set( ManipulatorTypes value )
{
	manipulator->SetState( value, TryGetTransformController() );
	if ( HasSelectedObject )
	{
		for each ( SceneElement^ element in selectedObjects.ToArray() )
		{
			element->RaiseManipulatorChangedEvent();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::IsGlobalManipulatorsMode::set( bool value )
{
	manipulator->IsGlobal = value;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditorScene::IsGlobalManipulatorsMode::get()
{
	return manipulator->IsGlobal;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::Select( SceneElement^ value )
{
	if ( !ReferenceEquals( value, nullptr ) && sceneElements.Contains( value ) && !selectedObjects.Contains( value ) )
	{
		ShowSelection = true;
		manipulator->SetInactiveState();

		selectedObjects.Add( value );
		value->RaiseSelectionChangedEvent();

		SelectedObjectChanged( this, EventArgs::Empty );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::Deselect( SceneElement^ valueToDeselect )
{
	if ( !ReferenceEquals( valueToDeselect, nullptr ) && sceneElements.Contains( valueToDeselect ) && selectedObjects.Contains( valueToDeselect ) )
	{
		selectedObjects.Remove( valueToDeselect );
		valueToDeselect->RaiseSelectionChangedEvent();

		manipulator->SetInactiveState();
		valueToDeselect->RaiseManipulatorChangedEvent();

		SelectedObjectChanged( this, EventArgs::Empty );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::DeselectAll()
{
	while ( selectedObjects.Count > 0 )
	{
		Deselect( selectedObjects[0] );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3^ EditorScene::SelectedObjectsGroupCenter::get()
{
	if ( HasSelectedObject )
	{
		CVec3 sum = VNULL3;
		for each ( SceneElement^ selectedObject in selectedObjects )
		{
			sum += selectedObject->Location->Native;
		}
		sum /= selectedObjects.Count;
		return gcnew Vector3( sum );
	}
	else
	{
		return nullptr;
	}
}

SceneElements::SceneObjects::Bound^ EditorScene::GetSelectedObjectsGroupBoundingBox()
{
  if ( HasSelectedObject )
  {
    CVec3 sum = VNULL3;

    int count = 0;
    for each ( GameSceneObject^ selectedObject in selectedObjects )
    {
      NativeSceneObject^ sceneObject = selectedObject->GetCurrentSceneObject();

      if ( sceneObject != nullptr && sceneObject->ppObject )
      {
        sum += selectedObject->GetCurrentSceneObject()->ppObject->GetPosition().pos;
        count++;
      }
    }

    if(count == 0) 
      return nullptr;

    sum /= count;

    SBound result;
    for each ( GameSceneObject^ selectedObject in selectedObjects )
    {
      if ( selectedObject->GetCurrentSceneObject() != nullptr)
      {
        SBound toadd = selectedObject->GetBoundingBox();
        result.Grow( toadd );
      }
    }
    return gcnew SceneElements::SceneObjects::Bound( sum + result.s.ptCenter, result.ptHalfBox );
  }

  return nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IObjectTransformController^ EditorScene::TryGetTransformController()
{
	if ( !ReferenceEquals( provider, nullptr ) )
	{
		List<IObjectTransformController^> controllers;
		for each ( SceneElement^ selectedObject in selectedObjects )
		{
			IObjectTransformController^ controller = provider->GetObjectTransformController( selectedObject );
			if ( !ReferenceEquals( controller, nullptr ) )
			{
				controllers.Add( controller );
			}
		}

		if ( controllers.Count > 0 )
		{
			return gcnew CompositeTransformController( controllers.ToArray() );
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::ShowSelection::set( bool value )
{
	showSelection = value;
	ShowSelectionChanged( this, EventArgs::Empty );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::SelectByFrame( float left, float top, float right, float bottom, ElementsFilter^ canBeSelected, bool isInvert, bool isSub )
{
	for each ( SceneElement^ element in sceneElements )
	{
		if ( !element->IsSelectable )
      continue;

    if ( !ReferenceEquals( canBeSelected, nullptr ) && !canBeSelected( element ) )
      continue;

    const CVec3 location = element->LocationInternal;

		float height = 0;
		if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
		{
			terrain->TryGetHeight( location.x, location.y, height );
		}
		const CVec2 projectedLocation = PerformProjection( camera->Native, location + CVec3( 0, 0, height ) );

		if ( projectedLocation.x >= left && projectedLocation.x <= right && projectedLocation.y >= top && projectedLocation.y <= bottom	)
		{
      if ( isInvert && !isSub )
      {
        if ( element->IsSelected )
        {
          Deselect( element );
        }
        else
        {
          Select( element );
        }
      }
      else if ( !isInvert && isSub )
      {
        Deselect( element );
      }
      else
      {
        Select( element );
      }
		}
	}
}

bool EditorScene::TryGetHeight( float x, float y, float% height )
{
	if ( NativeScene != nullptr )
	{
		//float h;
		//bool result = NativeScene->GetHeightsController().GetHeight( x, y, 1, &h, 0 );
		//height = h;
		//return result;

		height = NativeScene->GetTerrain()->GetHeightManager().GetHeightFast(x, y);
		return true;
	}
	else
	{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditorScene::TryCaptureManipulator( Vector2^ cursorPosition )
{
	return manipulator->TryCapture( ConvertCursorPosition( cursorPosition ), camera->Native );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::StartDragManipulator( bool isCommonCenter )
{
  manipulator->StartDrag( isCommonCenter );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::DragManipulator( Vector2^ delta, Vector2^ cursorPosition )
{
  if ( fabs(delta->Native) > 0.0f )
  {
	  manipulator->Drag(
		  ConvertCursorPosition( cursorPosition ),
		  delta->Native,
		  *NativeScene->GetCamera()
		  );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::EndDragManipulator()
{
  manipulator->EndDrag();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::UncaptureManipulator()
{
	manipulator->Uncapture();
}

void EditorScene::SetDayLightEnvironment( libdb::DB::DBID^ _dbId )
{
  NDb::Ptr<NDb::LightEnvironment> pEnvironment = GetObject<NDb::LightEnvironment>( _dbId );

  if (!pEnvironment.IsEmpty())
    NativeScene->LoadAdvMapLightEnvironment(pEnvironment, NDb::LIGHTENVIRONMENT_DAY);
}

void EditorScene::SetNightLightEnvironment(libdb::DB::DBID^ _dbId)
{
  NDb::Ptr<NDb::LightEnvironment> pEnvironment = GetObject<NDb::LightEnvironment>( _dbId );

  if (!pEnvironment.IsEmpty())
    NativeScene->LoadAdvMapLightEnvironment(pEnvironment, NDb::LIGHTENVIRONMENT_NIGHT);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorScene::CalculateLighting()
{
  CalculateLightingTerrain();
  CalculateLightingObjects();
  RecalculateSceneSH();
  SaveSceneSH();
  UpdateObjectsSH();
  MessageTrace( "EditorScene::CalculateLighting done" );
}

void EditorScene::CalculateLightingTerrain()
{
  // calculate lighting for terrain
  terrain->Native->GetGeometryManager().SetLightingScene(lightingScene);
  terrain->Native->WeldVertices();
  terrain->Native->RecalculateLighting();
}

void EditorScene::CalculateLightingObjects()
{
  // calculate lighting for all scene objects
  for each ( SceneElement^ element in sceneElements )
  {
    System::Collections::Generic::List<NativeSceneObject^>^ objects = element->EnumerateSceneObjects();
    if (objects)
    {
      for each ( NativeSceneObject^ obj in objects )
      {
        if (obj->ppObject)
        {
          lightingScene->CalculateLighting(*obj->ppObject);
        }
      }
    }
  }
}

void EditorScene::UpdateObjectsSH()
{
  // update SH coefs for all scene objects
  for each ( SceneElement^ element in sceneElements )
  {
    System::Collections::Generic::List<NativeSceneObject^>^ objects = element->EnumerateSceneObjects();
    if (objects)
    {
      for each ( NativeSceneObject^ obj in objects )
      {
        if (obj->ppObject)
        {
          obj->ppObject->UpdateSH();
        }
      }
    }
  }
}

void EditorScene::RecalculateSceneSH()
{
  NScene::SHGridCalculator::RecalculateSceneSH((*ppScene)->GetSHGrid(), *lightingScene);
}

void EditorScene::ToggleDebugRenderSH()
{
  (*ppScene)->GetSHGrid().ToggleDebugRender();
}

void EditorScene::InitBakedLighting(DBTypes::BakedLighting^ pBakedLighting)
{
  NDb::BakedLighting ndbBL;
  ndbBL.dynObjBakedLighting = ToMBCS(pBakedLighting->dynObjBakedLighting);
  ndbBL.dynObjLightingGridResX = pBakedLighting->dynObjLightingGridResX;
  ndbBL.dynObjLightingGridResY = pBakedLighting->dynObjLightingGridResY;
  NativeScene->InitSHGrid(ndbBL);
}

void EditorScene::ReloadDBIDs( System::String^ dbidString )
{
  for each ( SceneElement^ element in sceneElements )
  {
		if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
		{
			GameSceneObject^ obj = (GameSceneObject^)element;
			if ( obj->DbId->FileName->IndexOf( dbidString ) != -1 )
			{
				obj->Scene = nullptr;
				obj->Scene = this;
			}
		}
	}
}

void EditorScene::ReloadSounds()
{
  for each ( SceneElement^ element in sceneElements )
  {
    if ( GameSceneObject::typeid->IsInstanceOfType( element ) )
    {
      GameSceneObject^ obj = (GameSceneObject^)element;
      if ( obj->IsSound() )
      {
        obj->Scene = nullptr;
        obj->Scene = this;
      }
    }
  }
}

void EditorScene::SaveSceneSH()
{
  NativeScene->SaveSceneSH();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StoreColorsTraverser : public NScene::FullTraverser
{
  NScene::MeshVertexColorsManager &man;
  int curStaticComponentIdx;

  StoreColorsTraverser(NScene::MeshVertexColorsManager &man) : man(man), curStaticComponentIdx(0) {}

  void operator() (NScene::SceneComponent *sc)
  {
    NScene::StaticSceneComponent *ssc = dynamic_cast<NScene::StaticSceneComponent*>(sc);
    if (ssc)
    {
      man.SceneComponentVCStore( curStaticComponentIdx++, ssc );
    }
  }
};

void EditorScene::BuildVertexColorDB( System::Collections::Generic::IEnumerable<EditorNative::SceneElements::SceneObjects::GameSceneObject^>^ sceneObjects,
                                      System::String^ fileName )
{
  NScene::MeshVertexColorsManager man(true);

  System::Collections::Generic::IEnumerator<EditorNative::SceneElements::SceneObjects::GameSceneObject^>^  enumerator = sceneObjects->GetEnumerator();
  
  int i = 0;
  
  while (enumerator->MoveNext())
  {
    GameSceneObject^ sceneObj = enumerator->Current;
    
    man.AdvMapObjectVCBegin(i);

    System::Collections::Generic::List<NativeSceneObject^>  nativeObjects = sceneObj->EnumerateSceneObjects();

    for( int j = 0; j < nativeObjects.Count; ++j )
    {
      NativeSceneObject^ obj = nativeObjects[j];

      man.SceneObjectVCBegin( &NDb::DBID( ToMBCS( obj->dbId->Name ) ) );

      if (obj->ppObject)
      {
        StoreColorsTraverser sct(man);
        obj->ppObject->Traverse(sct);
      }

      man.SceneObjectVCEnd( &NDb::DBID( ToMBCS( obj->dbId->Name ) ) );
    }

    man.AdvMapObjectVCEnd(i);

    ++i;
  }

  man.Save(ToMBCS(fileName));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EditorScene::ClearViewport( System::IntPtr hWnd )
{
  const float width = oldscreenSize.Width;
  const float height = oldscreenSize.Height;
  const unsigned int left = ( EditorRender::GetWidth() - width ) / 2;
  const unsigned int top = ( EditorRender::GetHeight() - height ) / 2;

  Render::Rect rect( left, left + width, top, top + height );
  Render::Rect rect_dest( 0, width, 0, height );

  Render::Interface::Get()->Render(true);
  Render::Interface::Get()->Clear();
  Render::Interface::Get()->Present( (HWND)hWnd.ToPointer(), rect, rect_dest );
}

bool EditorScene::IsImmediateLighting()
{
  if ( lightingScene )
  {
    return lightingScene->IsImmediateUpdateOn();
  }

  return false;
}

void EditorScene::ClearHeightMapLayer( int layer )
{
  if ( NativeScene )
  {
    NativeScene->ClearHeightMapLayer( layer );
  }
}

void EditorScene::SaveObjectLayer( System::String^ filename )
{
  if ( NativeScene )
  {
    NativeScene->SaveObjectLayer( 1, ToMBCS( filename ) );
  }
}

void EditorScene::AddObjectToLayer( int layer, NScene::CollisionHull* hull )
{
  if ( NativeScene )
  {
    NativeScene->AddCollisionObjectToLayer( layer, hull );
  }
}

void EditorScene::CheckCameraLimits( float MaxYaw, float MinYaw, float MaxPitch, float MinPitch, float MaxRod, float MinRod, float MaxFov, float MinFov )
{
  if (camera->Yaw > MaxYaw)
  {
    camera->Yaw = MaxYaw;
  }
  if (camera->Yaw < MinYaw)
  {
    camera->Yaw = MinYaw;
  }

  if (camera->Pitch > MaxPitch)
  {
    camera->Pitch = MaxPitch;
  }
  if (camera->Pitch < MinPitch)
  {
    camera->Pitch = MinPitch;
  }

  if (camera->Rod > MaxRod)
  {
    camera->Rod = MaxRod;
  }
  if (camera->Rod < MinRod)
  {
    camera->Rod = MinRod;
  }

  if (camera->Fov > MaxFov)
  {
    camera->Fov = MaxFov;
  }
  if (camera->Fov < MinFov)
  {
    camera->Fov = MinFov;
  }
}

void EditorScene::SetPostFX( bool val )
{
  NGlobal::VariantValue value( val );
  SetVar( "pfx_enable", value, STORAGE_NONE );
}

bool EditorNative::EditorScene::NightLighting::get()
{
  return isNightLighting;
}

void EditorNative::EditorScene::NightLighting::set(bool value)
{
  isNightLighting = value;

  if (isNightLighting)
    NativeScene->SetNightFraction(1.f);
  else
    NativeScene->SetNightFraction(0.f);

  UpdateAllMSO();
}
