#pragma once

#error "File was removed from project due to BVS's refactoring @ 18.11.2008"

#include "../Scene/SceneObject.h"

namespace NGameX
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HeroSceneObject : public NScene::SceneObject
{
	CVec3 destination;
	float dstAngle;
	float curAngle;
	float rotSpeed;
	float speed;
	bool  isMove;
	bool  isDying;

	HeroSceneObject() : isMove( false ), isDying( false ), speed( 0.0f ), destination( VNULL3 ) {}

public:
	HeroSceneObject( NScene::IScene *_pScene, const NDb::DBSceneObject* pVisual, const Placement& pl )
	: NScene::SceneObject ( _pScene )
	,	isMove ( false )
	, isDying( false )
	, dstAngle( 0.0f )
	, curAngle( 0.0f )
	, rotSpeed( 0.0f )
	, speed( 0.0f )
	{
		SetPosition( pl );

		destination = GetPosition().pos;

		vector<NScene::SceneComponent*> comps = NScene::ParseSceneObject( pVisual, NULLPLACEMENT );
		for ( int  i = 0; i < comps.size(); i++ )
		{
			Add( comps[i] );
		}
	}

	virtual void Update( const float timeDiff );
	//CRAP{
	void Move( const Placement& newpos );
	void Die();
	void Stop();
	//CRAP}
	const bool IsMoving() const { return isMove; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroSceneObject* CreateHeroSceneObject( NScene::IScene* pScene, const NDb::DBSceneObject* pVisual, const Placement& placement );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}