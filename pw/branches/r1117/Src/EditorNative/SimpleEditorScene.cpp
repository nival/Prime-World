#include "stdafx.h"
#include "Utility.h"
#include "SimpleEditorScene.h"
#include "EditorRender.h"
#include "EditorSound.h"
#include "Settings.h"
#include "TerrainUtils.h"
#include "CompositeTransformController.h"
#include "../Render/ImmediateRenderer.h"
#include "ManipulatorSceneObject.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/StaticSceneComponent.h"
#include "../Scene/ParticleSceneComponent.h"
#include "../Terrain/Terrain.h"
#include "../Scene/BitMap.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

namespace
{
  int g_editorRenderWidth  = 3200;
  int g_editorRenderHeight = 2400;
}

class CalcTransformedAnimLength : public NScene::GenericTraverser, private NonCopyable
{
  NScene::SceneComponent* cycleNonZeroResult;
  float cycleNonZeroTime;

	NScene::SceneComponent* result;
	float time;

  NScene::SceneComponent* agResult;
  float agTime;

public:
  CalcTransformedAnimLength() 
  : result( 0 ), cycleNonZeroResult( 0 ), agResult( 0 ), cycleNonZeroTime( 0.0f ), time( 0.0f ), agTime( 0.0f ) {}

	void Reset()
	{
		result = 0;
		cycleNonZeroResult = 0;
		agResult = 0;
		cycleNonZeroTime = 0.0f;
		time = 0.0f;
		agTime = 0.0f;
	}

	bool IsNonZero()
	{
		if ( agResult )
			return false;

		if ( result )
			return false;

		if ( cycleNonZeroResult )
			return true;

		return false;
	}

	NScene::SceneComponent* GetResultComponent()
	{
		if ( agResult )
			return agResult;

		if ( result )
			return result;

		if ( cycleNonZeroResult )
			return cycleNonZeroResult;

		return 0;
	}

	float GetResultTime()
	{
		if ( agResult )
			return agTime;

		if ( result )
			return time;

		if ( cycleNonZeroResult )
			return cycleNonZeroTime;

		return 0.0f;
	}
	
  void operator()( NScene::SceneComponent *sc )
  {
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( sc );
    if ( asc && !asc->GetDBComponent().IsEmpty() && !asc->GetDBComponent()->animGraph.IsEmpty() )
    {
      float t = sc->CalculateTransformedAnimLength();
      if ( t > agTime )
      {
        agResult = sc;
        agTime = t;
      }
    }

    if ( dynamic_cast<NScene::AnimatedSceneComponent*>( sc )
         || dynamic_cast<NScene::ParticleSceneComponent*>( sc )
         || dynamic_cast<NScene::StaticSceneComponent*>( sc ) 
         )
    {
			int cycleCount = 0;
			if ( !sc->GetTimeControllerDesc().IsEmpty() )
			{
				cycleCount = sc->GetTimeControllerDesc()->cycleCount;
			}

			float t = sc->CalculateTransformedAnimLength();
			if ( cycleCount == 0 )
			{
				if ( t > time )
				{
					result = sc;
					time = t;
				}
			}
			else
			{
				if ( t > cycleNonZeroTime )
				{
					cycleNonZeroResult = sc;
					cycleNonZeroTime = t;
				}
			}
    }
  }
};

struct SaveAndRestoreAGState : public NScene::GenericTraverser, private NonCopyable
{
  nstl::vector<NScene::AnimatedSceneComponent*> components;
  nstl::vector<uint> node;
  bool isSave;

  void operator()( NScene::SceneComponent *sc )
  {
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( sc );
    if ( asc )
    {
      components.push_back( asc );
      node.push_back( asc->GetMainAnimGraph()->GetNearestNode() );
    }
  }

  void Restore()
  {
    for ( int i = 0; i < components.size(); i++ )
    {
      components[i]->GetMainAnimGraph()->Restart( node[i], true );
      components[i]->ResetCurAnimTime();
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleEditorScene::SimpleEditorScene( IntPtr _handle, Size _screenSize )
: ppScene ( new CPtr<NScene::IScene>( NScene::CreateScene() ) )
, handle( _handle )
, screenSize ( _screenSize )
, _cinemaMode( CinemaMode::None )
, gridAreaSize( 0.0f )
, gridLineDistance( 0.0f )
, gridSubdivisionDistance( 0.0f )
, gridSubdivision( 0 )
, numFrames( -1 )
, framesCounter( 0 )
{
	EditorRender::Initialize( (HWND)handle.ToPointer(), false );
	EditorSound::Initialize( (HWND)handle.ToPointer() );

  g_editorRenderWidth = EditorRender::GetWidth();
  g_editorRenderHeight = EditorRender::GetHeight();

	NativeScene->Init( "", 1, CVec3(-128.f, -128.f, -128.f), 1024.f );
  NativeScene->CreateMeshVertexColorsManager(true);
	//	NativeScene->SetObserverPlayer( PLAYER_INDEX );

	NativeScene->GetCamera()->SetScreenSize( EditorRender::GetWidth(), EditorRender::GetHeight() );
	NativeScene->GetCamera()->SetPlanes( 0.2f, 500.0f );

  cameraController = new SimpleCameraController();
  NativeScene->GetCameraControllers()->AddCameraController( cameraController );
  camera = gcnew SimpleCamera( this );

  camera->Rod = 50.0f;
  camera->Fov = 50.0f;
  camera->Pitch = -1.0f;
  camera->Yaw = -6.0f;

  ppTexture = 0;
  ppBackgroundTexture = new Render::Texture2DRef(Render::Load2DTextureFromFile( "Tech/Default/Background.dds" ));
	framesCounter = new CalcTransformedAnimLength();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleEditorScene::~SimpleEditorScene()
{
	this->!SimpleEditorScene();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleEditorScene::!SimpleEditorScene()
{
	while ( sceneElements.Count > 0 )
	{
		Remove( sceneElements[0] );
	}

	if ( ppScene != nullptr )
	{
		delete ppScene;
		ppScene = nullptr;
	}

  if ( ppTexture )
  {
    delete ppTexture;
  }
  if ( ppBackgroundTexture )
  {
    delete ppBackgroundTexture;
  }
	if ( framesCounter )
	{
		delete framesCounter;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::IScene* SimpleEditorScene::NativeScene::get()
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleEditorScene::UpdateCamera( float deltaYaw, float deltaPitch, float deltaDistance, Vector2^ delta, Vector2^ cursorPosition )
{
	if ( NativeScene != nullptr )
	{
		const float MIN_ROD = 1;

		if ( deltaDistance > 0 )
		{
			if ( camera->Rod > MIN_ROD )
			{
				camera->Rod *= (float) Math::Pow( 2, -deltaDistance / 32.0 );
			}
			else
			{
				camera->SetAnchor( camera->GetAnchor() + gcnew Vector3( camera->Position.GetCameraDir() ) * ( deltaDistance / 32.f ) );
			}
		}
		else
		{
			if ( camera->Rod < MIN_ROD )
			{
				const CVec3 delta = camera->Position.GetCameraDir() * ( deltaDistance / 32.f );
				const CVec3 newAnchor = camera->GetAnchor()->Native + delta;

				if ( newAnchor.z > 0 )
				{
					camera->SetAnchor( gcnew Vector3( newAnchor.x, newAnchor.y, 0 ) );
					camera->Rod = MIN_ROD;
				}
				else
				{
					camera->SetAnchor( gcnew Vector3( newAnchor ) );
				}
			}
			else
			{
				camera->Rod *= (float) Math::Pow( 2, -deltaDistance / 32.0 );
			}
		}

		camera->Yaw += deltaYaw;
		camera->Pitch += deltaPitch;

		NScene::ICamera& nativeCamera = *NativeScene->GetCamera();
		const CVec2 convertedCursorPosition = ConvertCursorPosition( cursorPosition );

		const CVec3 center = camera->GetAnchor()->Native;
		const CVec3 normal = -camera->Position.GetCameraDir();
		const CVec3 currentIntersection = GetRayIntersection( nativeCamera, convertedCursorPosition, center, normal );
		const CVec3 prevIntersection = GetRayIntersection( nativeCamera, convertedCursorPosition - delta->Native, center, normal );

		camera->SetAnchor( camera->GetAnchor() + gcnew Vector3( currentIntersection - prevIntersection ) );
	}
}

struct Trav : public NScene::FullTraverser
{
  virtual void operator()( NScene::SceneComponent *pSC ) 
  { 
    pSC->DisableStrongWithWaitingForFinish();
  }
} f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleEditorScene::Draw( System::IntPtr hWnd, float time, float delta )
{
  handle = hWnd;
  currentTime = time;
  Render::Interface* const pIface = Render::Interface::Get();

  pIface->DisableWarFog(true);

  EditorSound::Update( delta );

  //EditorRender::DumpScreenShoot( "c:/file.png" );

  const float width = oldscreenSize.Width;
  const float height = oldscreenSize.Height;
  const unsigned int left = ( EditorRender::GetWidth() - width ) / 2;
  const unsigned int top = ( EditorRender::GetHeight() - height ) / 2;

  Render::Rect rect( left, left + width, top, top + height );
  Render::Rect rect_dest( 0, width, 0, height );

  NDebug::ResetDebugVarsOnFrame( delta );

  for ( int i = 0; i < sceneElements.Count; i++ )
  {
    sceneElements[i]->Update( delta );
  }

  Render::Rect rect_orig( 0, EditorRender::GetWidth(), 0, EditorRender::GetHeight() );

  if ( ppTexture )
  {
    pIface->Render(true);
		pIface->Clear();
    Render::RenderState renderState;
    renderState.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
    Render::GetStatesManager()->SetState(renderState);
    Render::GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);
    Render::ImmRenderer::Params params( "DiffuseMap", *ppBackgroundTexture, &Render::SamplerState::PRESET_WRAP_BILINEAR() );
    float w = (float)(*ppTexture)->GetWidth()/(float)(*ppBackgroundTexture)->GetWidth();
    float h = (float)(*ppTexture)->GetHeight()/(float)(*ppBackgroundTexture)->GetHeight();
    params.uvRect = CTRect<float>(0.f, 0.f, w, h);
    Render::GetImmRenderer()->RenderScreenQuad(CTRect<int>(left, top, left + (*ppTexture)->GetWidth(), 
      top + (*ppTexture)->GetHeight()), params);
    Render::GetImmRenderer()->RenderScreenQuad(CTRect<int>(left, top, left + (*ppTexture)->GetWidth(), 
      top + (*ppTexture)->GetHeight()), Render::ImmRenderer::Params("DiffuseMap", *ppTexture));
  }
	else if ( NativeScene != nullptr )
	{
    static const Render::Rect null_rect;
    //NativeScene->ConstrainRender( _cinemaMode == CinemaMode::None ? rect : null_rect );
    NativeScene->ConstrainRender( null_rect );

		NScene::ICamera& camera = *NativeScene->GetCamera();
		NativeScene->Update( time, delta, false );
		NativeScene->Draw();

    camera.SetViewportSize( 0, 0 );

		if ( gridLineDistance > 0.0f )
			DrawMayaGrid();

    for ( int i = 0; i < sceneElements.Count; i++ )
    {
      sceneElements[i]->Draw( *NativeScene );
    }

    pIface->ConstrainRender(_cinemaMode == CinemaMode::None ? rect : rect_orig);
    pIface->Render( true, 0, 0, g_editorRenderWidth, g_editorRenderHeight );
//    Render::Interface::Get()->Render( true );
  }

  if ( oldscreenSize != screenSize )
  {
    ClearViewport(hWnd);
    oldscreenSize = screenSize;
    ClearViewport(hWnd);
    return;
  }

  if( _cinemaMode != CinemaMode::None )
  {
    static const Render::Rect null_rect;
    System::Drawing::Size cinemaSize = CalcCinemaRect(_cinemaMode);
    NativeScene->ConstrainRender(null_rect);
    NativeScene->GetCamera()->SetScreenSize(cinemaSize.Width, cinemaSize.Height);
    Render::Rect rect_orig( 0, EditorRender::GetWidth(), 0, EditorRender::GetHeight() );
    const unsigned int left = ( oldscreenSize.Width - cinemaSize.Width ) / 2;
    const unsigned int top = ( oldscreenSize.Height - cinemaSize.Height ) / 2;
    Render::Rect rect_cinema( left, left + cinemaSize.Width, top, top + cinemaSize.Height );
    Render::Rect rect_cinema2( 0, cinemaSize.Width, 0, cinemaSize.Height );
    pIface->ConstrainRender(rect_cinema2);
    pIface->Render( true, 0, 0, cinemaSize.Width, cinemaSize.Height );
    pIface->Present( (HWND)hWnd.ToPointer(), rect_cinema2, rect_cinema );
  }
  else
  {
//    EditorRender::Present( (HWND)hWnd.ToPointer() );
    pIface->Present( (HWND)hWnd.ToPointer(), rect, rect_dest );
  }

  // ÕÀÊ! NUM_TASK
  if ( NativeScene && framesCounter )
  {
    if ( framesCounter->GetResultComponent() )
		{
			if ( framesCounter->IsNonZero() )
			{
				if ( framesCounter->GetResultComponent()->GetCurTime() > framesCounter->GetResultTime() )
				{
          framesCounter->GetResultComponent()->Traverse( f );
        }
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Drawing::Size SimpleEditorScene::CalcCinemaRect( CinemaMode mode )
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
void SimpleEditorScene::DrawMayaGrid()
{
	System::Drawing::Color blackColor = System::Drawing::Color::FromArgb( 192, 192, 192 );
	System::Drawing::Color grayColor = System::Drawing::Color::FromArgb( 96, 96, 96 );
  System::Drawing::Color redColor = System::Drawing::Color::FromArgb( 255, 0, 0 );

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
void SimpleEditorScene::ShowMayaGrid( float lineDistance, int subdivision, float areaSize )
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
void SimpleEditorScene::HideGrid()
{
	gridAreaSize = 0.0f;
	gridLineDistance = 0.0f;
	gridSubdivisionDistance = 0.0f;
	gridSubdivision = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 SimpleEditorScene::ConvertCursorPosition( Vector2^ cursorPosition )
{
  NScene::ICamera& camera = *NativeScene->GetCamera();
  CVec2 result;
  if( _cinemaMode != CinemaMode::None )
  {
    System::Drawing::Size cinemaSize = CalcCinemaRect(_cinemaMode);
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

void SimpleEditorScene::SetLightEnvironment( libdb::DB::DBID^ _dbId )
{
	NDb::Ptr<NDb::LightEnvironment> pEnvironment = GetObject<NDb::LightEnvironment>( _dbId );
	if ( !pEnvironment.IsEmpty() )
	{
		NativeScene->LoadAdvMapLightEnvironment( pEnvironment );
    CalculateLighting();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleEditorScene::Add( SceneElements::SceneObjects::ISceneElement^ element )
{
	if ( !sceneElements.Contains( element ) )
	{
		sceneElements.Add( element );
    element->Create( System::IntPtr(NativeScene) );
		element->Reinit();
    CalculateLighting();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleEditorScene::Remove( SceneElements::SceneObjects::ISceneElement^ element )
{
	if ( sceneElements.Contains( element ) )
	{
		sceneElements.Remove( element );
		element->Delete( System::IntPtr(NativeScene) );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimplePickResult^ SimpleEditorScene::Pick( Vector2^ cursorPosition )
{
	NScene::ICamera& camera = *NativeScene->GetCamera();
	const CVec2 realCursorPosition = ConvertCursorPosition( cursorPosition );
  
	NScene::PickResult pickResult;
	NativeScene->Pick( &pickResult, realCursorPosition );

	List<KeyValuePair<EditorSceneObject^, Vector3^>> pickedElements;

	const CVec3 cameraLocation = this->camera->Position.GetCameraPos();

	// 	const float maximalDistance = pickResult.hasTerrainIntersection ? fabs( cameraLocation - pickResult.terrainIntersection ) : float::MaxValue;
	if ( pickResult.usedIntersections > 0 )
	{
		for each( Object^ item in sceneElements )
		{
      if ( !EditorSceneObject::typeid->IsInstanceOfType( item ) )
        continue;

      EditorSceneObject^ element = (EditorSceneObject^)item;

			for ( int i = 0; i < pickResult.usedIntersections; ++i )
			{
				NScene::Intersection& intersection = pickResult.intersections[i];
				NScene::EditorSceneObject* ptr = dynamic_cast<NScene::EditorSceneObject*>(intersection.pHull->GetSceneObject());
				if ( element->IsEqual( ptr ) )
				{
					pickedElements.Add( KeyValuePair<EditorSceneObject^, Vector3^>( element, gcnew Vector3( intersection.enter ) ) );
				}
			}
		}
	}

	pickedElements.Sort( gcnew Comparison<KeyValuePair<EditorSceneObject^, Vector3^>>( this, &SimpleEditorScene::ComparePickedElements ) );

	List<EditorSceneObject^>^ result = gcnew List<EditorSceneObject^>();
	for each ( KeyValuePair<EditorSceneObject^, Vector3^> pair in pickedElements )
	{
		result->Add( pair.Key );
	}

  SimplePickResult^ resultPickInfo = gcnew SimplePickResult( gcnew Vector3( pickResult.terrainIntersection ), result, pickResult.hasTerrainIntersection );

  resultPickInfo->hasZIntersection = false;
  CRay ray;
  camera.GetProjectiveRay( &ray.ptOrigin, &ray.ptDir, realCursorPosition );
  float cosin = ray.ptDir.Dot(CVec3(0.f,0.f,1.f));
  if ( fabs(cosin) > FP_EPSILON )
  {
    float dist = ray.ptOrigin.Dot(CVec3(0.f,0.f,1.f));
    float lamda = -dist/cosin;
    CVec3 intersection = ray.ptOrigin + lamda*ray.ptDir;
    resultPickInfo->hasZIntersection = true;
    resultPickInfo->zIntersection = gcnew Vector3(intersection);
  }

	return resultPickInfo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SimpleEditorScene::ComparePickedElements( KeyValuePair<SceneElements::SceneObjects::EditorSceneObject^, Vector3^> left, KeyValuePair<SceneElements::SceneObjects::EditorSceneObject^, Vector3^> right )
{
	return fabs( this->camera->Position.GetCameraPos() - left.Value->Native ).CompareTo( fabs( this->camera->Position.GetCameraPos() - right.Value->Native ) );
}

void SimpleEditorScene::OnDbResourceChanged( libdb::DB::DBID^ dbId )
{
	for each ( ISceneElement^ element in sceneElements )
	{
    EditorSceneObject^ so = dynamic_cast<EditorSceneObject^>(element);
    if ( so != nullptr )
    {
      if ( libdb::DB::DataBase::HasDependency( so->DbId, dbId ) )
      { 
        element->Delete( System::IntPtr(NativeScene) );
        element->Create( System::IntPtr(NativeScene) );
        //element->Reinit();
        CalculateLighting();
      }
    }
	}
}

void SimpleEditorScene::CheckCameraLimits( float MaxYaw, float MinYaw, float MaxPitch, float MinPitch, float MaxRod, float MinRod, float MaxFov, float MinFov )
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

void SimpleEditorScene::ClearViewport( System::IntPtr hWnd )
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

void SimpleEditorScene::SetCinemaMode( int mode )
{
  ClearViewport(handle);
  _cinemaMode = (CinemaMode)mode;
  ClearViewport(handle);
}

CVec2 SimpleEditorScene::GetCursorScale()
{
  CVec2 scale(1.0f,1.0f);
  if( _cinemaMode != CinemaMode::None )
  {
    NScene::ICamera& camera = *NativeScene->GetCamera();
    System::Drawing::Size cinemaSize = CalcCinemaRect(_cinemaMode);
    float Width = camera.GetScreenWidth();
    float Height = camera.GetScreenHeight();
    scale.x *= Width/cinemaSize.Width;
    scale.y *= Height/cinemaSize.Height;
  }
  return scale;
}

int SimpleEditorScene::GetCurrentFrame( SceneElements::SceneObjects::EditorSceneObject^ so )
{
  if ( NativeScene && so->Object && framesCounter )
  {
    if ( framesCounter->GetResultComponent() )
		{
			if ( framesCounter->IsNonZero() )
			{
				if ( framesCounter->GetResultComponent()->GetCurTime() > framesCounter->GetResultTime() )
				{
					return 0;
				}
				else
				{
					return Round(fmod(framesCounter->GetResultComponent()->GetCurTime(),framesCounter->GetResultTime())*30.0f);
				}
			}
			else
			{
				return Round(fmod(framesCounter->GetResultComponent()->GetCurTime(),framesCounter->GetResultTime())*30.0f);
			}
		}
  }
  return -1;
}

static bool TestForMoreCount( const nstl::vector<int>& frames, int frame, int number )
{
  int count = 0;
  for ( int i = 0; i < frames.size(); i++ )
  {
    if ( frames[i] == frame )
      count++;
  }
  if ( count >= number )
  {
    return true;
  }
  return false;
}

void SimpleEditorScene::SetCurrentFrame( SceneElements::SceneObjects::EditorSceneObject^ so, int value )
{
  if ( !NativeScene || !so->Object )
    return;

  nstl::vector<int> frames;
  frames.reserve(200);
  int curFrame = GetCurrentFrame( so );
  if ( curFrame > value || curFrame == -1 )
  {
    SaveAndRestoreAGState stater;
    so->Object->Traverse( stater );
    so->Object->Reinit();
    stater.Restore();
  }
  if ( NativeScene && so->Object )
  {
    curFrame = GetCurrentFrame( so );
    while ( value != curFrame && curFrame != -1 )
    {
      NativeScene->Update( currentTime, 1.0f/30.0f, false, true );
      currentTime += 1.0f/30.0f;
      if ( TestForMoreCount( frames, curFrame, 3 ) )
      {
        break;
      }

      curFrame = GetCurrentFrame( so );
      frames.push_back( curFrame );
    }
    return;
  }
}

void SimpleEditorScene::CalcFrameNumbers( SceneElements::SceneObjects::EditorSceneObject^ so )
{
	framesCounter->Reset();
  if ( NativeScene && so->Object )
  {
    so->Object->Traverse(*framesCounter);
    if ( framesCounter->GetResultComponent() )
    {
      numFrames = Round( framesCounter->GetResultTime()*30.0f );
      return;
    }
  }
  numFrames = -1;
  return;
}

int SimpleEditorScene::GetFrameNumbers( SceneElements::SceneObjects::EditorSceneObject^ so )
{
  return numFrames;
}

void SimpleEditorScene::SetWaterMap( bool isWater )
{
  if ( NativeScene )
  {
    CVec2 mapSize(512, 512);
    NScene::BitMap* waterMap = new NScene::BitMap( isWater, mapSize );
    NativeScene->LoadWaterMap( waterMap );
  }
}

void SimpleEditorScene::SetPostFX( bool val )
{
  NGlobal::VariantValue value( val );
  SetVar( "pfx_enable", value, STORAGE_NONE );
}

void SimpleEditorScene::CalculateLighting()
{
  // calculate lighting for all scene objects
  for each ( ISceneElement^ element in sceneElements )
  {
    EditorSceneObject ^eobj = dynamic_cast<EditorSceneObject^>(element);

    if (eobj && eobj->Object)
    {
      eobj->Object->CalculateLighting(NativeScene->GetRenderScene()->GetSceneConstants());
    }
  }
}

void SimpleCameraController::SetNewWantedPosition( const NScene::SCameraPosition& pos )
{
  position = pos;
}
