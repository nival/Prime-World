#include "stdafx.h"
#include "Utils.h"
#include "../Scene/EditorSceneObject.h"
#include "../PF_Core/RecolorableTexture.h"
#include "../EditorNative/StringUtils.h"

namespace PF_EditorNative
{

void Utils::RecolorSceneObject( System::IntPtr so, float r, float g, float b )
{
  NScene::EditorSceneObject* eso = (NScene::EditorSceneObject*)(so.ToPointer());
  PF_Core::RecolorSceneObject( *eso, Render::HDRColor(r, g, b) );
}

void Utils::RecolorSceneComponent( System::IntPtr so, System::String^ _componentId, float r, float g, float b )
{
	NScene::EditorSceneObject* eso = (NScene::EditorSceneObject*)(so.ToPointer());
	nstl::string componentId = EditorNative::ToMBCS( _componentId );
	PF_Core::RecolorSceneComponent( *eso, componentId, Render::HDRColor(r, g, b) );
}

void Utils::ResetSceneObjectRecolor( System::IntPtr so )
{
  NScene::EditorSceneObject* eso = (NScene::EditorSceneObject*)(so.ToPointer());
  PF_Core::ResetSceneObjectRecolor( *eso );
}

void Utils::ResetRecolorableTextureCache()
{
  PF_Core::RecolorableTextureManager *pMan = PF_Core::RecolorableTextureManager::Get();
  if (pMan)
  {
    pMan->EnableRecolor(!pMan->IsRecolorEnabled());
  }
}

void Utils::ResetCache()
{
  PF_Core::RecolorableTextureManager *pMan = PF_Core::RecolorableTextureManager::Get();
  if (pMan)
  {
    pMan->ResetCache();
  }
}

}