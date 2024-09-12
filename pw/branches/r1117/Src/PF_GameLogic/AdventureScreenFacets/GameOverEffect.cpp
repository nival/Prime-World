#include "stdafx.h"

#include "GameOverEffect.h"
#include "./../AdventureScreen.h"
#include "./../PF_Core/EffectsPool.h"
#include "./../AdventureScreen.h"
#include "./../Scene/Camera.h"
#include "./../Scene/CameraControllersContainer.h"
#include "./../MoveToCameraController.h"       
#include "./../PFAIWorld.h"
#include "./../PFMainBuilding.h" 
#include "System/StarForce/StarForce.h"

namespace NGameX { namespace AdventureScreenFacets
{
GameOverEffect::GameOverEffect( AdventureScreen *pAdvScreen ):
  pAdvScreen(pAdvScreen), cameraCanBeMoved(true)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameOverEffect::Update( float dt )
{
  if( startEffectTimer.Tick(dt) )
  {
    Protection::CheckReadOnlyAndExecutable();
  
    effectPtr = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>( effectId );

    if ( effectPtr )
    {
      effectPtr->AddToScene( pAdvScreen->GetScene() );
      effectPtr->SetPosition( targetPos );
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameOverEffect::Start( NDb::EFaction failedFaction )
{
  NScene::ICamera * pCamera = pAdvScreen->GetScene()->GetCamera();
  NScene::SCameraPosition from;
  pCamera->GetPosition( &from );

  FactionToPos::const_iterator itTargetPos = factionToPos.find( failedFaction );

  if( itTargetPos == factionToPos.end() )
  {
    DebugTrace( "Can't find the main building" );
    return;
  }

  targetPos = itTargetPos->second;

  const NDb::EFaction ourFaction = pAdvScreen->GetPlayerFaction();
  const NDb::EWinLose cond = ourFaction != failedFaction ? NDb::WINLOSE_WIN : NDb::WINLOSE_LOSE;

  const NDb::WinLoseEffect &params =
    NDb::SessionRoot::GetRoot()->visualRoot->winLoseEffects[cond];

  NDb::ViewCamera to( params.cameraPos ); 
  to.anchor += targetPos;

  if( effectPtr != 0 )
  {
    effectPtr->DieImmediate();
    effectPtr = 0;
  }

  effectId = params.effect;

  if(cameraCanBeMoved)
  {
    PF_Core::MoveToCameraController *pMoveToCtrl = new PF_Core::MoveToCameraController;

    pMoveToCtrl->Init( from, to, params.cameraMovementTime );
    pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( pMoveToCtrl );
    startEffectTimer.Start( params.effectDelay );
  }
  else
    startEffectTimer.Start( 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameOverEffect::PrecacheEffects()
{
  const NDb::WinLoseEffect &winParams =
    NDb::SessionRoot::GetRoot()->visualRoot->winLoseEffects[NDb::WINLOSE_WIN];

  CObj<PF_Core::BasicEffectStandalone > winEffect = 
    PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>( winParams.effect );

  if ( IsValid(winEffect) )
  {
    winEffect->DieImmediate();
  }

  const NDb::WinLoseEffect &loseParams =
    NDb::SessionRoot::GetRoot()->visualRoot->winLoseEffects[NDb::WINLOSE_LOSE];

  CObj<PF_Core::BasicEffectStandalone > loseEffect = 
    PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>( loseParams.effect );

  if ( IsValid(loseEffect) )
  {
    loseEffect->DieImmediate();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameOverEffect::BuildingCollector : NonCopyable
{
public:
  BuildingCollector( FactionToPos &factionToPos )
    : factionToPos( factionToPos )
  {}

  void operator()( NWorld::PFLogicObject &baseUnit )
  {
    CDynamicCast<NWorld::PFMainBuilding> unit = &baseUnit;
    
    if( IsValid( unit ) )
    {	
      NI_ASSERT( factionToPos.find(unit->GetFaction()) == factionToPos.end(), "Logic error" );
      factionToPos[ unit->GetFaction() ] =  unit->GetVisualPosition3D();
    }
  }

private:
  FactionToPos &factionToPos;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameOverEffect::UpdateBuildingsInfo( NWorld::PFAIWorld* pWorld )
{
  factionToPos.clear();
  BuildingCollector collector( factionToPos );       
  pWorld->ForAllUnits( collector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace AdventureScreenFacets 

bool MoveCameraToMainBuilding( const char *name, const vector<wstring> &params )
{
  NGameX::AdventureScreen * const pAS = NGameX::AdventureScreen::Instance();

  pAS->gameOverEffect.Start( GetFaction(pAS->GetPlayer()) );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_DEV_CMD(move_camera_to_main_building, MoveCameraToMainBuilding);

} //namespace NGameX

