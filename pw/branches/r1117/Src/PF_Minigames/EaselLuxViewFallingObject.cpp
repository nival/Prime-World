#include "stdafx.h"

#include "EaselLuxViewFallingObject.h"
#include "EaselWorldClientConvertHelper.h"

#include "DBEasel.h"

#include "../Scene/SceneObject.h"

#include "Easel.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselLuxViewFallingObject::EaselLuxViewFallingObject() :
localIntTime( 0 ), localTime( 0 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::DBSceneObject> EaselLuxViewFallingObject::GetDB( NDb::EFallingObject type )
{
  NI_VERIFY( IsValid(easel), "EaselLuxViewFallingObject: something strange happened. easel is dead", return NULL);

  const nstl::vector<NDb::Ptr<NDb::DBSceneObject>>& objects = easel->GetData()->commonParams->fallingObjects;

  NI_VERIFY( objects.size() >= NDb::KnownEnum<NDb::EFallingObject>::SizeOf(), "EaselLuxViewFallingObject: creating object type is invalid", return NULL);
  return objects[type];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselLuxViewFallingObject::Init( Easel * _easel, CLuxFallingObject * _object )
{
	easel = _easel;
	object = _object;

  localObject = new CLuxFallingObject( 0, *_object );

  NDb::Ptr<NDb::DBSceneObject> dbSceneObject = GetDB( NDb::FALLINGOBJECT_COIN );
	if( !dbSceneObject )
		return false;

  Placement objPlacement = easel->GetPlacement();

  NScene::SceneObject *pSceneObject = MinigameClientObject::Init( NULL, _easel->GetScene(), dbSceneObject.GetPtr(), objPlacement, false );
  if( pSceneObject == NULL)
    return false;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewFallingObject::Update( float deltaTime, bool gameOnPause )
{
	NI_VERIFY( IsValid(easel), "EaselLuxViewFallingObject: something strange happened. easel is dead", return );

  if ( gameOnPause )
    gameOnPause = true;

  if ( IsValid( object ) && localObject )
  {
    if ( !gameOnPause )
      localTime += deltaTime;

    int prevIntTime = localIntTime;
    localIntTime = (int)( 0.5f + localTime * 1e3f );

    int intTimeDelta = localIntTime - prevIntTime;

    localObject->Update( intTimeDelta );

    CVec3 point = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( 
      localObject->GetPosition(),
      easel->GetData()->commonParams->coin.zLift * EaselConst::Get_BALL_DEF_DIAMETER() );

    SetPosition( point );
  }
  else
  {
    Reset();
  }
	
	MinigameClientObject::Update( deltaTime, gameOnPause );
}

bool EaselLuxViewFallingObject::IsPicked() const
{
  if ( !IsValid( object ) )
    return false;

  return object->IsPicked();
}

void EaselLuxViewFallingObject::Reset()
{
  localObject = 0;
  SetVisible(false);
}


} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselLuxViewFallingObject );
