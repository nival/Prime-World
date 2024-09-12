#pragma once

#include "Vector3.h"

namespace EditorNative
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class EditorRender sealed abstract
{
public:
	static void Initialize( HWND hEditorWindow, bool loadUI );
	static void Release();

  static void DrawPoint3D( Vector3^ point, float size, System::Drawing::Color color );
	static void DrawPoint3D( float x, float y, float z, float size, System::Drawing::Color color );
  static void DrawCircle3D( Vector3 ^point, float size, int numSegments, System::Drawing::Color color );
  static void DrawLine3D( Vector3^ point1, Vector3^ point2, System::Drawing::Color color, bool zTest );
	static void ResetTexture( System::String^ textureFileName );

	static void MarkAsDirtyGeometry(System::String^ filename);
	static void MarkAsDirtyPFX(System::String^ filename);
	static void MarkAsDirtySkeletonData(System::String^ filename);
	static void MarkAsDirtySkeletonAnim(System::String^ filename);

	static void ReloadShaders();
	static void ReloadGeometry();
	static void ReloadPFX();
	static void SetFFTT(bool mode);

  static void ToggleMipMaps();

	static void ToggleShowLocators();

  static void DumpScreenShoot(System::String^ filename);
  static System::Drawing::Bitmap^ GetSurfaceBuffer();

  static bool SetShadows( bool val );

  static void SetViewport( float x, float y, float height, float width );

  static void Present( HWND hEditorWindow );

internal:
	static unsigned int GetWidth();
	static unsigned int GetHeight();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
