#include "stdafx.h"

#include "EaselLocal.h"

#include "EaselWorld.h"
#include "EaselView.h"
#include "EaselCommands.h"

#include "EaselWorldClientConvertHelper.h"

#include "Scene/Scene.h"
#include "PF_GameLogic/PFWorld.h"

namespace
{
  // ruler offsets
  int g_rulerOffsetX = 5; 
  int g_rulerOffsetY = 5;

  REGISTER_DEV_VAR("Easel_Ruler_Offset_x",g_rulerOffsetX,STORAGE_NONE);
  REGISTER_DEV_VAR("Easel_Ruler_Offset_y",g_rulerOffsetY,STORAGE_NONE);
}

namespace PF_Minigames
{

EaselLocal::EaselLocal( PF_Core::IWorld* _pWorld ) : 
  Easel( _pWorld ),
  numMouseLeftButtonClicked( 0 ),
  numMouseRightButtonClicked( 0 ),
  stepCounter( 0 ),
  gameStarted( false )
{

}



EaselLocal::~EaselLocal()
{
  
}



void EaselLocal::StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer* player )
{
  Easel::StartLevel( paintId, levelID, seed, player );

  gameStarted = true;
  stepCounter = 0;
}



void EaselLocal::StopLevel()
{
  gameStarted = false;
  Easel::StopLevel();
}



bool EaselLocal::Update( float deltaTime, bool gameOnPause )
{
  if ( gameStarted )
  {
    if ( IsValid( GetWorld() ) )
      GetWorld()->UpdateInputMove( mousePos );
  }

  return Easel::Update( deltaTime, gameOnPause );
}



void EaselLocal::StepM( float deltaTime )
{
  if ( !gameStarted )
    return;

  StepInterval();
  Easel::StepM( deltaTime );
}



void EaselLocal::StepInterval()
{
  if ( !IsValid( sessionHatch ) )
    return;

  bool leftButton = false, rightButton = false;
  if ( numMouseLeftButtonClicked > 0 )
  {
    leftButton = true;
    --numMouseLeftButtonClicked;
  }

  if ( numMouseRightButtonClicked > 0 )
  {
    rightButton = true;
    --numMouseRightButtonClicked;
  }

  sessionHatch->SendRemoteUpdateCommand( stepCounter, (short)mousePos.x,(short)mousePos.y, leftButton, rightButton );
  // prepare step info for easel world logic
  {
    EaselStepInfo info;
    info.deltaTime  = 0;   
    info.inputState.mousePos = mousePos;
    info.inputState.mouseLeftButton = leftButton;
    info.inputState.mouseRightButton = rightButton;

    GetWorld()->StepM( info );
  }

  {
    EaselStepInfo info;
    info.deltaTime = GetScene()->GetStepLength();
    info.inputState.mousePos = mousePos;

    GetWorld()->StepM( info );
  }

  stepCounter++;
}



bool EaselLocal::ProcessMouseMove(const CVec2& _pos)
{
  if ( !IsValid( GetScene() ) )
    return false;
  mousePos = GetConvertHelper()->ConvertScreenToWorldCoordinates( _pos );
  return true;
}



bool EaselLocal::ProcessMouseEvent( EEaselMouseEvents::Enum _key )
{
  switch(_key)
  {
    case EEaselMouseEvents::LeftButton:
      ++numMouseLeftButtonClicked;
      return true;
      
    case EEaselMouseEvents::RightButton:
      ++numMouseRightButtonClicked;
      return true;

    default:
      return false;
  }
  
  //return true;
}


// creation overloads
EaselWorld* EaselLocal::CreateWorldObject()
{
  return new EaselWorldLocal( PF_Core::WorldObjectBase::GetWorld() );
}



EaselView* EaselLocal::CreateViewObject( Easel* _easel )
{
  return new EaselView( _easel );
}

}

REGISTER_SAVELOAD_CLASS_NM( EaselLocal, PF_Minigames )

