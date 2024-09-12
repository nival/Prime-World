#pragma once

#include "../System/Placement.h"
#include "EditorSceneObject.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class EditorSceneObject : ISceneElement
{
	libdb::DB::DBID^ dbId;
	NScene::EditorSceneObject* ppObject;
  System::Collections::Generic::List<int> visibleSkins;
	int animationIndex;
	libdb::DB::DBID^ activeDBID;
	bool collisionGeometryVisible;

  Placement* initialPlacement;

  EditorSceneComponent^ rootEditorSceneComponent;

  NScene::SceneObject* effect;

public:
	EditorSceneObject( libdb::DB::DBID^ _dbId );

  void SetInitialPlacement(DBTypes::Placement2^ _placement);
  DBTypes::Placement2^ GetInitialPlacement();

  void SetCurrentPlacement(DBTypes::Placement^ _placement);
  DBTypes::Placement^ GetCurrentPlacement();

  virtual void SetPlacement( const Placement& placement )
  {
    if ( Object )
    {
      Object->SetPositionWithPlacingOnTerrain( placement );
    }
  }

  virtual const Placement& GetPlacement()
  {
    if ( Object )
    {
      return Object->GetPosition();
    }
    return NULLPLACEMENT;
  }

	void ShowSkin( int skinName, bool show, libdb::DB::DBID^ _dbId );
	void StartAnimation( int animationIndex, libdb::DB::DBID^ _dbId );
	System::IntPtr GetAnimGraph( libdb::DB::DBID^ _dbId );
	System::IntPtr GetExtPars( libdb::DB::DBID^ _dbId );
	System::Collections::Generic::IList<DBTypes::Animation^>^ GetAnimationList( libdb::DB::DBID^ _dbId );

	virtual void Reinit();
	void ClearVisibleSkins();
  System::Collections::Generic::List<int>^ GetActiveSkins(libdb::DB::DBID^ _dbId);

	virtual void Create( System::IntPtr _scene );
  virtual void Delete( System::IntPtr _scene );
  virtual void Apply( bool isMoved, bool isRotated, bool isScaled ) {}

  void ApplyTrack( System::String^ track );

  void SetParentTransformUsageFlags( unsigned int _flags );

  int GetListOfComponentsVersion() { return ppObject->GetListOfComponentsVersion(); }
	bool IsEqual( NScene::EditorSceneObject* ptr ) { return ptr == ppObject; }

	property int AnimationIndex {	int get() { return animationIndex; } }

	property libdb::DB::DBID^ DbId
	{
		libdb::DB::DBID^ get() { return dbId; }
		void set( libdb::DB::DBID^ value ) { dbId = value; }
	}

	property NScene::EditorSceneObject* Object 
  { 
    NScene::EditorSceneObject* get() 
    { 
      return ppObject; 
    }
  }

  void SetEffect( System::IntPtr so )
  {
    effect = (NScene::SceneObject*)so.ToPointer();
    if ( effect )
      effect->UpdateForced();
  }
  
  System::IntPtr GetRawEditorSceneObject()
  {
    return System::IntPtr(Object);
  }

	property bool CollisionGeometryVisible
	{
		bool get() { return collisionGeometryVisible; }
		void set( bool value )
		{
			collisionGeometryVisible = value;
			if ( Object )
			{
				Object->Highlight( collisionGeometryVisible ? NScene::HT_COLLISION : NScene::HT_OFF );
			}
		}
	}

  EditorSceneComponent^ GetRootEditorSceneComponent() { return rootEditorSceneComponent; }

  System::Collections::Generic::List<System::String^>^ GetLocatorsNames();

  void AttachToByLocator( System::String^ _name, EditorSceneObject^ so, DBTypes::Placement2^ _placement );
  DBTypes::Placement^ GetStandAloneEffectPlacement( System::String^ parentType, int parentFlags );

  property bool IsValid { bool get() { return Object != nullptr; } }

  void SetOpacity( float val );

  void SelectLocator( System::String^ locatorName );

  virtual void Draw( NScene::IScene& scene ) {}

  void SetTerrainLikeObject();

  bool IsContainWaterComponent();
  void FillEditorSceneComponents( NScene::SceneObject* so );

  virtual void Update( float delta ) {}
  virtual void Die() {}

  virtual bool IsNeedFillSceneHierarchy()
  {
    return true;
  }

protected:
  virtual NScene::EditorSceneObject* CreateNativeObject( NScene::IScene& scene );
  NScene::EditorSceneObject* CreateNativeObject( NScene::IScene& scene, bool isCollObject );
};

public ref class WithoutSHSceneObject : EditorSceneObject
{
public:
  WithoutSHSceneObject( libdb::DB::DBID^ _dbId ) : EditorSceneObject( _dbId ) {}

  virtual bool IsNeedFillSceneHierarchy() override
  {
    return false;
  }

};
}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
