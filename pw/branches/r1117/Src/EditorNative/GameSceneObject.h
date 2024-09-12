#pragma once

#include "Bound.h"
#include "SceneElement.h"
#include "Vector3.h"
#include "Quaternion.h"


namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

  public ref class NativeSceneObject
  {
  public:
    System::Collections::Generic::List<System::String^> visibleSkins;
    int animationIndex;

    libdb::DB::DBID^ dbId;
    NScene::EditorSceneObject* ppObject;
    bool collisionGeometryVisible;

		NativeSceneObject( libdb::DB::DBID^ _dbId )
		{
			dbId = _dbId;
			animationIndex = 0;
			ppObject = 0;
			collisionGeometryVisible = false;
		}
  };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class GameSceneObject : SceneElement
	{
	private:
    Render::PointLight* pointLight;
    bool isPointLight;
    System::Collections::Generic::List<NativeSceneObject^>^ sceneObjects;
    int currentSceneObject;
    bool isHidden;
    bool isFreezed;
    DBTypes::GameObject^ gameObject;
    System::String^ scriptGroupName;
    bool isMSO;
    bool isFullyLoaded;
    bool isSound;

		void CreateSceneObjects( NScene::IScene& scene );
    void OnShowSelectionChanged( System::Object^ sender, System::EventArgs^ e );
    void Initialize( DBTypes::GameObject^ gameObj, int layer, bool isPlacedToMap, System::String^ scriptGN );

	public:
    GameSceneObject( DBTypes::GameObject^ gameObj, int layer, System::String^ scriptGN );
    GameSceneObject( DBTypes::GameObject^ gameObj, int layer, bool isPlacedToMap, System::String^ scriptGN );
    GameSceneObject( libdb::DB::DBID^ dbid, int layer, System::String^ scriptGN );
    ~GameSceneObject();
    !GameSceneObject();

		void CreateLight();
    void UpdateLightInfo( DBTypes::PointLightInfo^ pointLightInfo );

    DBTypes::GameObject^ GetGameObject()
    {
      return gameObject;
    }

    int GetSceneObjectsCount()
    {
      return sceneObjects->Count;
    }

		NativeSceneObject^ GetCurrentSceneObject()
    {
      if(currentSceneObject >= 0 && currentSceneObject < sceneObjects->Count)
      {
        return sceneObjects[currentSceneObject];
      }
      
      return nullptr;
    }

		int GetCurrentSceneObjectIndex()
    {
      return currentSceneObject;
    }

		virtual System::Collections::Generic::List<NativeSceneObject^>^ EnumerateSceneObjects() override
    {
      return sceneObjects;
    }

		void SetSceneObject( int index );

		property int AnimationIndex
		{
			int get() { return sceneObjects[currentSceneObject]->animationIndex; }
		}

    property libdb::DB::DBID^ DbId
    {
      libdb::DB::DBID^ get()
      {
        if ( currentSceneObject < sceneObjects->Count )
          return sceneObjects[currentSceneObject]->dbId;
        if ( sceneObjects->Count )
          return sceneObjects[0]->dbId;
        return libdb::DB::DBID::Empty;
      }
    }

    System::String^ GetScriptGroupName()
    {
      return scriptGroupName;
    }

    property Bound^ BoundingBox
    {
      Bound^ get();
    }

    SBound GetBoundingBox()
    {
      SBound bound;
      Object->GetBound(bound);
      return bound;
    }

    property bool CollisionGeometryVisible
    {
      bool get() { return sceneObjects[currentSceneObject]->collisionGeometryVisible; }
      void set( bool value );
    }

    void SetCurrentPlacement( DBTypes::Placement^ _placement );
    DBTypes::Placement^ GetCurrentPlacement();
    void SetCurrentPlacement( DBTypes::Placement2^ _placement );
    void ReplaceObjectOnTerrain();
    void AddObjectToHeightMap();

    void Hide() { Hide( true ); }
    void Hide( bool resetSelection );
    void Show() { Show( true); }
    void Show( bool resetSelection );

    bool IsMSO()
    {
      return isMSO;
    }

    bool IsSound()
    {
      return isSound;
    }

    void SetSound( bool val )
    {
      isSound = val;
    }

    bool IsPointLight()
    {
      return isPointLight;
    }

    void SetMSO( bool val )
    {
      isMSO = val;
    }

    void SetFreezed( bool val )
    {
      isFreezed = val;
    }

    virtual void Draw() override; 

    property bool IsFullyLoaded
    {
      bool get() { return isFullyLoaded; }
      void set( bool value ) { isFullyLoaded = value; }
    }

    bool isPlaceOnTerrain;

  protected:
    virtual System::Collections::Generic::List<libdb::DB::DBID^>^ InitSceneObjects(DBTypes::GameObject^ gameObj)
    {
      System::Collections::Generic::List<libdb::DB::DBID^>^ objs = gcnew System::Collections::Generic::List<libdb::DB::DBID^>();
      return objs;
    }

    virtual void OnPositionChanged() override;
    virtual void OnSelectionChanged() override;

    virtual void OnBeforeOwnerChanged() override;
    virtual void OnOwnerChanged() override;

    property NScene::EditorSceneObject* Object
    {
      NScene::EditorSceneObject* get()
      {
        if ( IsValid )
        {
          return sceneObjects[currentSceneObject]->ppObject;
        }
        else
        {
          return nullptr;
        }
      }
    }

    property bool IsValid
    {
      bool get() { return !ReferenceEquals( Scene, nullptr ) && (sceneObjects->Count > currentSceneObject) && sceneObjects[currentSceneObject]->ppObject != nullptr; }
    }

    bool isPlacedToMap;//объект поставлен на карту
  internal:
    void DrawCircle( const nstl::vector<CVec3>& points, const Render::Color& color )
    {
      for ( int i = 0; i < points.size() - 1; ++i )
      {
        Render::DebugRenderer::DrawLine3D( points[i], points[i + 1], color, color, false );
      }
      Render::DebugRenderer::DrawLine3D( points[points.size() - 1], points[0], color, color, false );
    }

    void CalculateCirclePoints( const NScene::ICamera& camera, int deltaDegree, const CQuat& rotation, const CVec3& location, float radius, nstl::vector<CVec3>& outpoints )
    {
      const CVec3 base = rotation.Rotate( V3_AXIS_X ) * radius;
      const CVec3 normal = rotation.Rotate( V3_AXIS_Z );

      outpoints.clear();
      for ( int degree = 0; degree < 360; degree += deltaDegree )
      {
        outpoints.push_back( location + CQuat( ToRadian( degree ), normal, true ).Rotate( base ) );
      }
    }

    bool IsEqual( NScene::EditorSceneObject* ptr );
    void Reload();

    virtual void SetOwnerId(int id) override;
	};
}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
