#pragma once

#include "Vector3.h"
#include "CinemaMode.h"

namespace EditorNative {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class EditorScene;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class Camera
	{
	public:
		literal float DEFAULT_ROD = 100;

	private:
		EditorScene^ scene;
		NScene::SCameraPosition* prevPosition;

	internal:
		Camera( EditorScene^ scene );
		~Camera();
		!Camera();

	public:
		property float Yaw
		{
			float get();
			void set( float value );
		}

		property float Pitch
		{
			float get();
			void set( float value );
		}

		property float Roll
		{
			float get();
			void set( float value );
		}

		property float Rod
		{
			float get();
			void set( float value );
		}

		property float Fov
		{
			float get();
			void set( float value );
		}

		property Vector3^ Anchor
		{
			Vector3^ get();
			void set( Vector3^ value );
		}

		property Vector3^ Location
		{
			Vector3^ get();
		}

		property Vector3^ Direction
		{
			Vector3^ get();
		}

		property Vector3^ UpDirection
		{
			Vector3^ get();
		}

		property Vector3^ RightDirection
		{
			Vector3^ get();
		}

		property float Near
		{
			float get();
			void set( float value );
		}

		property float Far
		{
			float get();
			void set( float value );
		}

		property CinemaMode ScreenMode
		{
			CinemaMode get();
			void set( CinemaMode value );
		}

		void Update();

		event System::EventHandler^ ParametersChanged;

    EditorScene^ GetEditorScene()
    {
      return scene;
    }

	internal:
		property NScene::ICamera& Native
		{
			NScene::ICamera& get();
		}

		property NScene::SCameraPosition Position
		{
			NScene::SCameraPosition get();
			void set( NScene::SCameraPosition value );
		}

  private:
    void FireChangedEvent();
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
