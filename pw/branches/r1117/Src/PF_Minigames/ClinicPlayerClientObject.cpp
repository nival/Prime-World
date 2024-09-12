#include "stdafx.h"

#include "ClinicPlayerClientObject.h"

#include "Clinic.h"
#include "ClinicPlayer.h"
#include "ClinicCreep.h"

#include "../Scene/AnimatedSceneComponent.h"


namespace PF_Minigames
{

ClinicPlayerClientObject::~ClinicPlayerClientObject()
{
  //bizarre DI AG deconstruction
  if ( sceneObject && pDefaultAG )
  {
    NI_ASSERT( pDefaultAGExtPars, "" )
    NScene::AnimatedSceneComponent * asc = dynamic_cast< NScene::AnimatedSceneComponent *>( sceneObject->GetRootComponent() );
    if ( asc )
    {
      DiAnimGraph * pCustomGraph = asc->GetAG(true);
      DiAnGrExtPars * pCustomExtPars = asc->GetExtPars();

      asc->SetAnimGraphs( pDefaultAG, 0, pDefaultAGExtPars );
      pDefaultAG = 0;
      pDefaultAGExtPars = 0;

      delete pCustomExtPars;
      DiAnimGraph::Destroy( pCustomGraph );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayerClientObject::InitClinicPlayer( ClinicPlayer * player )
{
  NI_ASSERT( IsValid( clinic ), "" );
  clinicPlayer = player;

  SetScaleFactor( clinic->GetClinicDesc()->player.scaleFactor );

  player->SetClientNotify(this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBMinigame_Clinic & ClinicPlayerClientObject::GetClinicDesc() const
{
  return *clinic->GetClinicDesc();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject * ClinicPlayerClientObject::RedirectMouseOver()
{
  if ( IsValid(clinicPlayer) )
    if ( IsValid( clinicPlayer->GetCreep() ) )
      return clinic->GetClientObject( clinicPlayer->GetCreep()->GetObjectID() );

  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayerClientObject::CreateSceneObject( const NDb::DBSceneObject* dbSceneObject )
{
  //Ловим падение в CreatePriestessModel()
 // NI_ASSERT( IsValid( worldObject->GetMinigame()->GetMinigames()->GetClientSessionInterface() ), "" );

  //sceneObject = worldObject->GetMinigame()->GetMinigames()->GetClientSessionInterface()->CreatePriestessModel();
  PostInitSceneObject( Get( sceneObject ), scene, collisionHull, IsVisibleAfterAll() );

  const NDb::AnimGraphCreator * pNewAgDb = clinic->GetClinicDesc()->player.animationGraph;
  if ( pNewAgDb )
  {
    NScene::AnimatedSceneComponent * asc = dynamic_cast< NScene::AnimatedSceneComponent *>( sceneObject->GetRootComponent() );

    if ( asc )
    {
      pDefaultAG = asc->GetAG(true);
      pDefaultAGExtPars = asc->GetExtPars();
      DiAnimGraph * pCustomGraph = DiAnimGraph::CreateByData( pNewAgDb, asc->GetDBAnimations(), asc->GetGraphBlender() );
      asc->SetAnimGraphs( pCustomGraph, 0, new DiAnGrExtPars( pNewAgDb, pCustomGraph ) );
    }
  }

  //MovingUnitClientObject::CreateSceneObject( dbSceneObject );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayerClientObject::OnClientNotification(const char * eventId)
{
  //TODO: remove this when Priestess animation will be done
  systemLog(NLogg::LEVEL_DEBUG).Trace("Player notification '%s'", eventId);

  string event(eventId);

  if (event == "bonusBroom")
  {
    //TODO: play animation
  }
  else if (event == "creepWokeUpWWhip")
  {
    //TODO: play animation
  }
  else if (event == "creepWokeUp")
  {
    //TODO: play animation
  }
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::ClinicPlayerClientObject)
