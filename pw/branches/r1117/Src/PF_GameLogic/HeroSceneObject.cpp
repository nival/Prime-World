#include "stdafx.h"
#include "HeroSceneObject.h"
#include "../Scene/SceneComponent.h"
#include "../Scene/AnimatedSceneComponent.h"

#error "File was removed from project due to BVS's refactoring @ 18.11.2008"

namespace NGameX
{

float g_rotSpeedTemp = FP_PI * 1.5f;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSceneObject::Move( const Placement& newpos )
{
	if ( isDying )
		return;

	if ( !isMove )
	{
		isMove = true;
		NScene::SceneComponent* startComp = GetRootComponent();
		if ( startComp )
		{
			NScene::SceneComponent* it = startComp;
			do
			{
				if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
				{
					asc->StartAnimation( 1 );
				}
				it = it->GetBrother();
			} while ( it != startComp );
		}
	}

	destination = newpos.pos;
	CVec3 dir = destination - GetPosition().pos;
	dir.z = 0.0f;

	//CRAP{ Step calculation Ctrl+C Ctrl+V
	const float fStep = 1000 / 10.0f;
	//CRAP}
	speed = 1000.0f * fabs( dir ) / fStep;  //?? should get speed from WorldUnit

	// calculate rotation params
	if ( fabs( dir ) > 0.02f )
	{
		// get current rotation
		float tmpPitch, tmpRoll;
		GetPosition().rot.DecompEulerAngles( &curAngle, &tmpPitch, &tmpRoll );
		// get desired rotation
		dstAngle = atan2(dir.x, -dir.y);
		// get angle delta
		float rotDelta = dstAngle - curAngle;
		// normalize it
		while (rotDelta > FP_PI)
			rotDelta -= FP_2PI;
		while (rotDelta < -FP_PI)
			rotDelta += FP_2PI;
		// compute rotation speed
		rotSpeed = 1000.0f * rotDelta / fStep;   //?? should get speed from WorldUnit
		// clamp by maximal rotation speed
		if ( rotSpeed > g_rotSpeedTemp )
			rotSpeed = g_rotSpeedTemp;
		else if ( rotSpeed < -g_rotSpeedTemp )
			rotSpeed = -g_rotSpeedTemp;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSceneObject::Update( const float timeDiff )
{
	NScene::SceneObject::Update( timeDiff );

	if ( !isMove )
		return;

	Placement oldPosition = GetPosition();

	CVec3 dir = destination - oldPosition.pos;
	dir.z = 0;

	Normalize( &dir );
	CQuat rot = oldPosition.rot;

	if ( curAngle != dstAngle )
	{
		float remaining  = fabs( curAngle - dstAngle );
		float deltaAngle = rotSpeed * timeDiff;
		if ( fabs( remaining ) <= fabs( deltaAngle ) )
			curAngle = dstAngle;
		else
			curAngle += deltaAngle;
		rot.FromEulerAngles( curAngle, 0, 0 );
	}

	Placement newposrot(NULLPLACEMENT);
	newposrot.pos = oldPosition.pos + ( dir * speed * timeDiff );
	newposrot.pos.z = 0;
	newposrot.rot = rot;

	SetPosition( newposrot );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSceneObject::Die()
{
	if ( isDying )
		return;

	isDying = true;
	NScene::SceneComponent* startComp = GetRootComponent();
	if ( startComp )
	{
		NScene::SceneComponent* it = startComp;
		do
		{
			if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
			{
				asc->StartAnimation( 2 );
			}
			it = it->GetBrother();
		} while ( it != startComp );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSceneObject::Stop()
{
	isMove = false;

	NScene::SceneComponent* startComp = GetRootComponent();
	if ( startComp )
	{
		NScene::SceneComponent* it = startComp;
		do
		{
			if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
			{
				asc->StartAnimation( 0 );
			}
			it = it->GetBrother();
		} while ( it != startComp );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroSceneObject* CreateHeroSceneObject( NScene::IScene* pScene, const NDb::DBSceneObject* pVisual, const Placement& placement )
{
	if ( !pVisual )
		return 0;

	HeroSceneObject* pResult = new HeroSceneObject( pScene, pVisual, placement );
	pScene->AddSceneObject( pResult );
	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR("rotspeedA", g_rotSpeedTemp, STORAGE_NONE);
}