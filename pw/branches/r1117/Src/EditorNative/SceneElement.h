#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace SceneElements {

namespace SceneObjects {
ref class NativeSceneObject;
}

	public ref class SceneElement abstract
	{
	private:
    EditorScene^ scene;
		Vector3^ location;
		Quaternion^ rotation;
		Vector3^ scale;
    bool isVisible;
		bool selectable;
    int ownerId;

	protected:
		SceneElement();
		SceneElement( Vector3^ location, Quaternion^ rotation, Vector3^ scale );
    int GetOwnerId();

  internal:
    virtual void SetOwnerId(int id);

	public:
    property EditorScene^ Scene
    {
      virtual EditorScene^ get() { return scene; }
      virtual void set( EditorScene^ value )
      {
        if ( !ReferenceEquals( scene, value ) )
        {
          OnBeforeOwnerChanged();
          scene = value;
          OnOwnerChanged();
        }
      }
    }

		property Vector3^ Location
		{
			Vector3^ get() { return location; }
			void set( Vector3^ value ) { location = value; OnPositionChanged(); }
		}

		property Quaternion^ Rotation
		{
			Quaternion^ get() { return rotation; }
			void set( Quaternion^ value ) { rotation = value; OnPositionChanged(); }
		}

		property Vector3^ Scale
		{
			Vector3^ get() { return scale; }
			void set( Vector3^ value ) { scale = value; OnPositionChanged(); }
		}

		property bool IsSelected
		{
			bool get();
			void set( bool value );
		}

		property bool IsSelectable
		{
			bool get() { return selectable; }
			void set( bool value );
		}

    property bool IsVisible
    {
      bool get() { return isVisible; }
      void set( bool value ) { isVisible = value; }
    }

		virtual void Draw() abstract;

  internal:
		property CVec3 LocationInternal
		{
			CVec3 get() { return Location->Native; }
			void set( CVec3 value ) { Location = gcnew Vector3( value ); }
		}

		property CQuat RotationInternal
		{
			CQuat get() { return Rotation->Native; }
			void set( CQuat value ) { Rotation = gcnew Quaternion( value ); }
		}

		property CVec3 ScaleInternal
		{
			CVec3 get() { return Scale->Native; }
			void set( CVec3 value ) { Scale = gcnew Vector3( value ); }
		}

		void RaiseSelectionChangedEvent() { OnSelectionChanged(); }
		void RaiseManipulatorChangedEvent() { OnManipulatorChanged(); }

    virtual System::Collections::Generic::List<SceneObjects::NativeSceneObject^>^ EnumerateSceneObjects()
    {
      return nullptr;
    }

	protected:
		virtual void OnPositionChanged() {}
		virtual void OnSelectionChanged() {}
		virtual void OnManipulatorChanged() {}
    virtual void OnBeforeOwnerChanged() {}
    virtual void OnOwnerChanged() {}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public interface class IPickableSceneElement
  {
  public:
    virtual bool IsIntersectWith( float terrainX, float terrainY, Vector3^ pickLocation ) abstract;
  };

}	// namespace SceneElements
}	// namespace EditorNative
