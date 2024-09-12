#pragma once

#include "GameSceneObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "ManipulatorElement.h"
#include "ManipulatorsController.h"
#include "IObjectTransformControllersProvider.h"
#include "EditorTerrain.h"
#include "PickResult.h"
#include "Camera.h"
#include "CinemaMode.h"
#include "EditorDebugVars.h"
#include "Bound.h"
#include "../Scene/EditorSceneObject.h"
#include "EditorSceneObject.h"

namespace EditorNative
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public ref class FrameRect
  {
  private:
    float left;
    float top;
	  float width;
	  float height;
	  System::Drawing::Color color;
    bool hidden;

  internal:
    FrameRect( System::Drawing::Color _color ) : left( 0 ), top( 0 ), width( 0 ), height( 0 ), color( _color ), hidden( true )
    {
    }

	  void Draw();

  public:
    void Show()
    {
      hidden = false;
    }

    void Hide()
    {
      hidden = true;
			width = 0;
			height = 0;
    }

    property float Left
	  {
		  float get() { return left; }
		  void set( float value ) { left = value; }
	  }

	  property float Top
	  {
		  float get() { return top; }
		  void set( float value ) { top = value; }
	  }

	  property float Width
	  {
		  float get() { return width; }
		  void set( float value ) { width = value; }
	  }

	  property float Height
	  {
		  float get() { return height; }
		  void set( float value ) { height = value; }
	  }

    property Vector2^ Location
    {
      void set( Vector2^ value )
      {
        left = value->X;
        top = value->Y;
      }
    }

    property Vector2^ Size
    {
      void set( Vector2^ value )
      {
        width = value->X;
        height = value->Y;
      }
    }
  };
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class EditorScene
	{
  private:
		CPtr<NScene::IScene>* ppScene;

		CinemaMode cinemaMode;
		System::Drawing::Size screenSize;
    System::Drawing::Size oldscreenSize;

    System::IntPtr handle;

		Camera^ camera;
		Terrain::EditorTerrain^ terrain;
		Manipulators::ManipulatorsController^ manipulator;
		System::Collections::Generic::List<SceneElements::SceneElement^> sceneElements;
    System::Collections::Generic::List<SceneElements::IPickableSceneElement^> pickableElements;//it needs for optimize Pick
    System::Collections::Generic::List<Terrain::TcvMarker^> tcvMarkers;//it needs for optimize Pick
		FrameRect^ selectionFrame;

		Manipulators::IObjectTransformControllersProvider^ provider;
		System::Collections::Generic::List<SceneElements::SceneElement^> selectedObjects;

    float gridAreaSize;
		float gridLineDistance;
		float gridSubdivisionDistance;
		int gridSubdivision;

		bool showSelection;

    bool viewportMode;

    bool minimapMode;

    NScene::LightingScene *lightingScene;

    bool isEnabledEffectsInScene;
    bool isMapLoaded;

		bool drawCollisionSelection;

    bool isGlobalManipulatorsMode;

    bool isNightLighting;

	public:
		EditorScene( System::IntPtr _handle, System::Drawing::Size _screenSize, Manipulators::IObjectTransformControllersProvider^ provider, bool needSound );

		~EditorScene();
		!EditorScene();

	public:

    void ToggleViewportMode()
    {
      viewportMode = !viewportMode;
    }

    void InitLightScene();
    NScene::LightingScene* GetLightScene()
    {
      return lightingScene;
    }
    void SetImmediateLightingUpdate(bool bOn);
    bool IsImmediateLighting();

		void Select( SceneElements::SceneElement^ element );
		void Deselect( SceneElements::SceneElement^ element );
		void DeselectAll();

		delegate bool ElementsFilter( SceneElements::SceneElement^ element );
		void SelectByFrame( float left, float top, float right, float bottom, ElementsFilter^ filter, bool isInvert, bool isSub );
    PickResult^ Pick( Vector2^ cursorPosition );
    PickResult^ PickByFrame( float left, float top, float right, float bottom );

    property FrameRect^ SelectionFrame
    {
      FrameRect^ get() { return selectionFrame; }
    }

		bool TryGetHeight( float x, float y, float% height );

    void Add( SceneElements::SceneElement^ element );
    void Remove( SceneElements::SceneElement^ element );

		void ShowMayaGrid( float lineDistance, int subdivision, float areaSize );
		void HideGrid();

		virtual void UpdateCamera( float deltaYaw, float deltaPitch, float deltaDistance, Vector2^ delta, Vector2^ cursorPosition );
		virtual void Draw( System::IntPtr hWnd, float time, float delta );

    void SetCameraPosition( Vector3^ position, float yaw, float pitch, float roll, float rod );
    void GetCameraPosition( Vector3^ position, float% yaw, float% pitch, float% roll );

    bool TryCaptureManipulator( Vector2^ cursorPosition );
		void StartDragManipulator( bool isCommonCenter );
    void DragManipulator( Vector2^ delta, Vector2^ cursorPosition );
    void EndDragManipulator();
		void UncaptureManipulator();

    void ReplaceAllObjectsOnTerrain();
    void CalcObjectHeightMap();

    void UpdateAllMSO();
    void TryFullReload() { TryFullReload(true); }
    void TryFullReload( bool isNeedDisableEffectsInScene );
    System::Drawing::Bitmap^ CreateMinimapTexture();
    array<System::Drawing::Point>^ GetCameraFrustum();
		bool IsInCameraFrustum(float x, float y, float z);

		generic<typename T> where T:SceneElements::SceneElement System::Collections::Generic::IList<T>^ GetSceneElementsByType();
    System::Collections::Generic::IList<SceneElements::SceneElement^>^ GetSceneElementsByType(System::Type^ type);
		System::Collections::Generic::IList<SceneElements::SceneElement^>^ GetSceneElements();

		property bool ShowSelection
		{
			bool get() { return showSelection; }
			void set( bool value );
		}

    property bool IsEnabledEffectsInScene
    {
      bool get() { return isEnabledEffectsInScene; }
    }

    System::IntPtr GetHWnd()
    {
      return handle;
    }

		property Camera^ SceneCamera
		{
			Camera^ get() { return camera; }
		}

    void CheckCameraLimits( float MaxYaw, float MinYaw, float MaxPitch, 
      float MinPitch, float MaxRod, float MinRod, float MaxFov, float MinFov );

		property System::Drawing::Size ScreenSize
		{
			System::Drawing::Size get() { return screenSize; }
			void set( System::Drawing::Size value ) { screenSize = value; }
		}

		property ManipulatorTypes CurrentManipulator
		{
			ManipulatorTypes get() { return manipulator->CurrentManipulator; }
			void set( ManipulatorTypes value );
		}

    property bool IsGlobalManipulatorsMode
		{
			bool get();
			void set( bool value );
		}

    void ResetManipulatorSize()
    {
      return manipulator->ResetManipulatorSize();
    }

    void IncreaseManipulatorSize()
    {
      manipulator->IncreaseManipulatorSize();
    }

    void DecreaseManipulatorSize()
    {
      manipulator->DecreaseManipulatorSize();
    }

		property System::Collections::Generic::IList<SceneElements::SceneElement^>^ SelectedObjects
		{
			System::Collections::Generic::IList<SceneElements::SceneElement^>^ get() { return selectedObjects.AsReadOnly(); }
		}

		property Vector3^ SelectedObjectsGroupCenter
		{
			Vector3^ get();
		}

    SceneElements::SceneObjects::Bound^ GetSelectedObjectsGroupBoundingBox();

		property bool HasSelectedObject
		{
			bool get() { return selectedObjects.Count > 0; }
		}

		property Terrain::EditorTerrain^ SceneTerrain
		{
			Terrain::EditorTerrain^ get () { return terrain; }
			void set( Terrain::EditorTerrain^ value );
		}

		property bool HasTerrain
		{
			bool get() { return !ReferenceEquals( terrain, nullptr ); }
		}

		event System::EventHandler^ SelectedObjectChanged;
		event System::EventHandler^ ShowSelectionChanged;

    void SetDayLightEnvironment( libdb::DB::DBID^ _dbId );
    void SetNightLightEnvironment( libdb::DB::DBID^ _dbId );
    void CalculateLighting();
    void CalculateLightingTerrain();
    void CalculateLightingObjects();
    void UpdateObjectsSH();
    void RecalculateSceneSH();
    void ToggleDebugRenderSH();
    static void BuildVertexColorDB( System::Collections::Generic::IEnumerable<EditorNative::SceneElements::SceneObjects::GameSceneObject^>^ sceneObjects, System::String^ fileName );
    void SaveSceneSH();
    void InitBakedLighting(DBTypes::BakedLighting^ pBakedLighting);
    void ReloadDBIDs( System::String^ dbidString );
    void ReloadSounds();
    void SaveObjectLayer( System::String^ filename );
    void AddObjectToLayer( int layer, NScene::CollisionHull* hull );
    void ClearHeightMapLayer( int layer );

    void EnableEffectsInScene( bool val );

    void SetPostFX( bool val );
		void SetDrawCollisionSelection( bool val )
		{
			drawCollisionSelection = val;
		}
		bool GetDrawCollisionSelection()
		{
			return drawCollisionSelection;
		}

    property CinemaMode ScreenMode
    {
      CinemaMode get() { return cinemaMode; }
      void set( CinemaMode value ) 
      { 
        ClearViewport(handle);
        cinemaMode = value;
        ClearViewport(handle);
      }
    }

    property bool IsMapLoaded
    {
      bool get() { return isMapLoaded; }
      void set( bool value ) 
      { 
        isMapLoaded = value;
      }
    }

    void ClearViewport(System::IntPtr hWnd);

    CVec2 ConvertCursorPosition( Vector2^ cursorPosition );
    Vector2^ ConvertCursorPosition2( Vector2^ cursorPosition );
    
    bool IsValid()
    {
      return NativeScene != 0;
    }

    property bool NightLighting
    {
      bool get();
      void set(bool value);
    }

	internal:
		property NScene::IScene* NativeScene
		{
			NScene::IScene* get();
		}

    property NScene::ICamera& NativeCamera
    {
      NScene::ICamera& get();
    }

	private:
		System::Drawing::Size CalcCinemaRect( CinemaMode mode );
		void DrawCinemaRect( System::Drawing::Size );

		void DrawMayaGrid();

		int ComparePickedElements(
			System::Collections::Generic::KeyValuePair<SceneElements::SceneElement^, Vector3^> left,
			System::Collections::Generic::KeyValuePair<SceneElements::SceneElement^, Vector3^> right
			);

		Manipulators::IObjectTransformController^ TryGetTransformController();
    void ReplaceAllObjectsOnTerrain( bool heightObjects );
	};

  

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
