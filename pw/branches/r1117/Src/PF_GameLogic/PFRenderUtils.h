#pragma once

namespace Render
{
  struct SceneConstants;
}

namespace PF_Render
{

void ApplySceneConstantsCameraOnly( const Render::SceneConstants &sceneConsts );
void ApplySceneConstantsColorOnly( const Render::SceneConstants &sceneConsts );
void ApplySceneConstants( const Render::SceneConstants &sceneConsts );

void DumpScreenshots();

}