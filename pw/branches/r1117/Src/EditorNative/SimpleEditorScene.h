#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "ManipulatorElement.h"
#include "ManipulatorsController.h"
#include "IObjectTransformControllersProvider.h"
#include "EditorTerrain.h"
#include "CinemaMode.h"
#include "EditorDebugVars.h"
#include "ISceneElement.h"
#include "SimplePickResult.h"
#include "EditorRender.h"
#include "../Scene/CameraController.h"
#include "../Scene/SceneTypes.h"
#include "../Scene/CameraControllersContainer.h"

using namespace System;

class SimpleCameraController : public NScene::ICameraController
{
  OBJECT_BASIC_METHODS(SimpleCameraController);
  CPtr<NScene::ICamera> pCamera;
  NScene::SCameraPosition position;

  virtual void SetCamera( NScene::ICamera* _pCamera ) { pCamera = _pCamera; }

public:

  void SetNewWantedPosition( const NScene::SCameraPosition& pos );

  virtual const bool IsEffect() const { return false; }
  virtual const bool IsActive() const { return true; }

  virtual void Update( NScene::SCameraPosition* pWantedPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff )
  {
    ASSERT( IsValid( pCamera ) );
    *pWantedPos = position;
  }
  virtual bool ProcessEvent( const Input::Event &	_eEvent ) { return true; }
};

class CalcTransformedAnimLength;

namespace EditorNative
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class SimpleEditorScene
	{

  public:

    ref class SimpleCamera
    {
    private:
      SimpleEditorScene^ scene;
      Vector3^ firstAncher;
      Vector3^ secondAncher;
      NScene::SCameraPosition* position;

      property Vector3^ SecondAnchor
      {
        Vector3^ get() { return secondAncher; }
        void set( Vector3^ value )
        {
          secondAncher = value;
          NScene::SCameraPosition pos = Position;
          pos.vAnchor = value->Native + firstAncher->Native;
          Position = pos;
        }
      }
    
      property Vector3^ Anchor
      {
        Vector3^ get() { return firstAncher; }
        void set( Vector3^ value )
        {
          firstAncher = value;
          NScene::SCameraPosition pos = Position;
          pos.vAnchor = value->Native + secondAncher->Native;
          Position = pos;
        }
      }

    internal:
      SimpleCamera( SimpleEditorScene^ _scene ) 
        : scene( _scene )
      {
        firstAncher = gcnew Vector3( 0.0f, 0.0f, 0.0f );
        secondAncher = gcnew Vector3( 0.0f, 0.0f, 0.0f );
        position = new NScene::SCameraPosition();
      }
      ~SimpleCamera() { this->!SimpleCamera(); }
      !SimpleCamera() { delete position; }

    public:
      property float Yaw
      {
        float get() { return Position.fYaw; }
        void set( float value )
        {
          NScene::SCameraPosition pos = Position;
          pos.fYaw = value;
          Position = pos;
        }
      }

      property float Pitch
      {
        float get() { return Position.fPitch; }
        void set( float value )
        {
          NScene::SCameraPosition pos = Position;
          pos.fPitch = value;
          Position = pos;
        }
      }

      property float Fov
      {
        float get() { return scene->NativeScene->GetCamera()->GetFOV(); }
        void set( float value ) { scene->NativeScene->GetCamera()->SetFOV(value); }
      }

      property float Rod
      {
        float get() { return Position.fRod; }
        void set( float value )
        {
          NScene::SCameraPosition pos = Position;
          pos.fRod = value;
          Position = pos;
        }
      }

      property NScene::SCameraPosition Position
      {
        NScene::SCameraPosition get()
        {
          return *position;
        }
        void set( NScene::SCameraPosition value )
        {
          *position = value;
          scene->GetCameraController()->SetNewWantedPosition( *position );
        }
      }

      void SetAnchor(Vector3^ anchor)
      {
        Anchor = anchor;
      }

      Vector3^ GetAnchor()
      {
        return Anchor;
      }

      void SetSecondAnchor( Vector3^ anchor )
      {
        SecondAnchor = anchor;
      }
    };
  
  private:

		CPtr<NScene::IScene>* ppScene;
    IntPtr handle;

    CinemaMode _cinemaMode;
    System::Drawing::Size screenSize;
    System::Drawing::Size oldscreenSize;

		System::Collections::Generic::List<SceneElements::SceneObjects::ISceneElement^> sceneElements;

    SimpleCameraController* cameraController;
    SimpleCamera^ camera;

		float gridAreaSize;
		float gridLineDistance;
		float gridSubdivisionDistance;
		int gridSubdivision;

    Render::Texture2DRef* ppTexture;
    Render::Texture2DRef* ppBackgroundTexture;

		CalcTransformedAnimLength* framesCounter;

    float timeSpeed;

    float currentTime;

    int numFrames;

	public:
		SimpleEditorScene( System::IntPtr _handle, System::Drawing::Size _screenSize );

		~SimpleEditorScene();
		!SimpleEditorScene();
    
	public:
		void ShowMayaGrid( float lineDistance, int subdivision, float areaSize );
		void HideGrid();

    void EnableCameraEffects( bool val )
    {
      NativeScene->GetCameraControllers()->EnableEffects( val );
    }

		void Add( SceneElements::SceneObjects::ISceneElement^ obj );
		void Remove( SceneElements::SceneObjects::ISceneElement^ obj );

    System::Collections::Generic::List<SceneElements::SceneObjects::ISceneElement^>^ GetSceneElements()
    {
      return %sceneElements;
    }

		virtual void UpdateCamera( float deltaYaw, float deltaPitch, float deltaDistance, Vector2^ delta, Vector2^ cursorPosition );
		virtual void Draw( System::IntPtr hWnd, float time, float delta );

		SimplePickResult^ Pick( Vector2^ cursorPosition );

		property System::Drawing::Size ScreenSize
		{
			System::Drawing::Size get() { return screenSize; }
			void set( System::Drawing::Size value ) { screenSize = value; }
		}

    property float TimeSpeed
    {
      float get() { return timeSpeed; }
      void set( float value ) { timeSpeed = value; }
    }

    void SetPostFX( bool val );

    void SetCinemaMode( int mode );

    void ClearViewport(System::IntPtr hWnd);

    void SetLightEnvironment( libdb::DB::DBID^ _dbId );

    void OnDbResourceChanged( libdb::DB::DBID^ dbId );

    void CheckCameraLimits( float MaxYaw, float MinYaw, float MaxPitch, 
      float MinPitch, float MaxRod, float MinRod, float MaxFov, float MinFov );

    SimpleCameraController* GetCameraController()
    {
      return cameraController;
    }

    SimpleCamera^ GetCamera()
    {
      return camera;
    }

    void SetCamera(SimpleCamera^ _camera)
    {
      camera = _camera;
    }

    void SetTexture(DBTypes::Texture^ texture)
    {
      if ( ppTexture )
      {
        delete ppTexture;
      }
      string filename = ToMBCS( texture->textureFileName );
      ppTexture = new Render::Texture2DRef(Render::Load2DTextureFromFile( filename ));
    }

    bool IsValid()
    {
      return NativeScene != 0;
    }

    CVec2 ConvertCursorPosition( Vector2^ cursorPosition );
    CVec2 GetCursorScale();

    int GetCurrentFrame( SceneElements::SceneObjects::EditorSceneObject^ so );
    void SetCurrentFrame( SceneElements::SceneObjects::EditorSceneObject^ so, int value );
    int GetFrameNumbers( SceneElements::SceneObjects::EditorSceneObject^ so );
    void CalcFrameNumbers( SceneElements::SceneObjects::EditorSceneObject^ so );
    void SetWaterMap( bool isWater );
    void CalculateLighting();

	internal:

		property NScene::IScene* NativeScene
		{
			NScene::IScene* get();
		}

	private:
		System::Drawing::Size CalcCinemaRect( CinemaMode mode );

		int ComparePickedElements(
			System::Collections::Generic::KeyValuePair<SceneElements::SceneObjects::EditorSceneObject^, Vector3^> left,
			System::Collections::Generic::KeyValuePair<SceneElements::SceneObjects::EditorSceneObject^, Vector3^> right
			);

		void DrawMayaGrid();

	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
