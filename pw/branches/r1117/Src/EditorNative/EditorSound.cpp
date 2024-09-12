#include "stdafx.h"
#include "EditorSound.h"
#include "../Sound/SoundScene.h"
#include "../Sound/EventScene.h"

static bool soundInitialized = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void EditorSound::Initialize( HWND hEditorWindow )
	{
		//return;
		if ( soundInitialized )
			return;
		for(int i = 0; i < NSoundScene::SOUNDCATEGORY_COUNT; i++ )
		{
			NSoundScene::SetMinMaxDistance( (NSoundScene::ESoundCategory) i, 1, 10);
		}
		NSoundScene::TryTurnOnSound();
		soundInitialized = true;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void EditorSound::Release()
	{
		if ( soundInitialized )
		{
			NSoundScene::TryTurnOffSound();
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void EditorSound::Update( float dt )
	{
		if ( soundInitialized )
		{
      NSoundScene::EventSystemUpdate( dt );
      NSoundScene::Update();
		}
	}

  void EditorSound::SetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor )
  {
    NSoundScene::SetListener( position, forward, up );
    NSoundScene::EventSystemSetListener( position, forward, up, anchor );
  }
}