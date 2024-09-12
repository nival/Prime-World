#pragma once

namespace PF_EditorNative
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class Utils sealed abstract
{
public:
	static void RecolorSceneObject( System::IntPtr so, float r, float g, float b );
	static void RecolorSceneComponent( System::IntPtr so, System::String^ componentId, float r, float g, float b );
  static void ResetSceneObjectRecolor( System::IntPtr so );
  static void ResetRecolorableTextureCache();
	static void ResetCache();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
