
#include "stdafx.h"
#include "EditorPassabilityMask.h"



namespace PF_EditorNative
{


EditorPassabilityMask::EditorPassabilityMask()
:m_scenePassabilityMask (new CPtr<NScene::ScenePassabilityMask> () )
{

}

EditorPassabilityMask::~EditorPassabilityMask()
{

}


} // namespace
