#include "stdafx.h"

#include "TriggerMarkerHandler.h"
#include "PFAIContainer.h"
#include "PFAIWorld.h"
#include "TileMap.h"
#include "WarFog.h"
#include "AdventureScreen.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TriggerMarkerHandler::TriggerMarkerHandler( PFWorld* pWorld, NDb::AdvMapSettings const * _advMapSettings )
  : PFWorldObjectBase( pWorld, 0 )
  , advMapSettings(_advMapSettings)
{
  for( vector<NDb::TriggerMarkerBinding>::const_iterator it = advMapSettings->triggerMarkerBinding.begin(), itEnd = advMapSettings->triggerMarkerBinding.end(); it != itEnd; ++it )
  {
    for( int k = 0; k < it->MarkerPoints.size(); k++ )
    {
      if( activeStates.find( it->MarkerPoints[k] ) == activeStates.end() )
      {
        activeStates[it->MarkerPoints[k]].resize( NDb::KnownEnum<NDb::EFaction>::SizeOf() );

        for( int i = 0; i < activeStates[it->MarkerPoints[k]].size(); i++ )
        {
          activeStates[it->MarkerPoints[k]][i].current = 0;
          activeStates[it->MarkerPoints[k]][i].previous = 0;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TriggerMarkerHandler::Step(float dt)
{
  for( vector<NDb::TriggerMarkerBinding>::const_iterator it = advMapSettings->triggerMarkerBinding.begin(), itEnd = advMapSettings->triggerMarkerBinding.end(); it != itEnd; ++it )
  {
    if ( const NDb::ScriptArea* scriptAreaTrigger = GetWorld()->GetAIContainer()->GetScriptArea( it->TriggerPoint.c_str() ) )
    {
      UnitAccumulatorFunctor func( scriptAreaTrigger->position, scriptAreaTrigger->radius, scriptAreaTrigger->targetType );
      
      GetWorld()->GetAIWorld()->ForAllInRange( CVec3(scriptAreaTrigger->position, 0.0f), scriptAreaTrigger->radius + GetWorld()->GetAIWorld()->GetMaxObjectSize() * 0.5f, func );

      for( int k = 0; k < it->MarkerPoints.size(); k++ )
      {
        activeStates[it->MarkerPoints[k]][NDb::FACTION_NEUTRAL].current += func[NDb::FACTION_NEUTRAL];
        activeStates[it->MarkerPoints[k]][NDb::FACTION_FREEZE].current += func[NDb::FACTION_FREEZE];
        activeStates[it->MarkerPoints[k]][NDb::FACTION_BURN].current += func[NDb::FACTION_BURN];
      }
    }
  }

  for( ActiveStates::iterator it = activeStates.begin(), itEnd = activeStates.end(); it != itEnd; ++it )
  {
    if ( const NDb::ScriptArea* scriptAreaMarker = GetWorld()->GetAIContainer()->GetScriptArea( it->first.c_str() ) )
    {
      const SVector tile = GetWorld()->GetTileMap()->GetTile( scriptAreaMarker->position );
      
      if( it->second[NDb::FACTION_FREEZE].current && !it->second[NDb::FACTION_FREEZE].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_FREEZE );

      if( it->second[NDb::FACTION_BURN].current && !it->second[NDb::FACTION_BURN].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_BURN );

      if( it->second[NDb::FACTION_NEUTRAL].current && !it->second[NDb::FACTION_NEUTRAL].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_NEUTRAL );

      if( !it->second[NDb::FACTION_FREEZE].current && it->second[NDb::FACTION_FREEZE].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_FREEZE, true );

      if( !it->second[NDb::FACTION_BURN].current && it->second[NDb::FACTION_BURN].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_BURN, true );

      if( !it->second[NDb::FACTION_NEUTRAL].current && it->second[NDb::FACTION_NEUTRAL].previous )
        GetWorld()->GetFogOfWar()->FillVisibilityMap( tile , scriptAreaMarker->radius, NDb::FACTION_NEUTRAL, true );

    }

    it->second[NDb::FACTION_FREEZE].previous = it->second[NDb::FACTION_FREEZE].current;
    it->second[NDb::FACTION_FREEZE].current = 0;

    it->second[NDb::FACTION_BURN].previous = it->second[NDb::FACTION_BURN].current;
    it->second[NDb::FACTION_BURN].current = 0;

    it->second[NDb::FACTION_NEUTRAL].previous = it->second[NDb::FACTION_NEUTRAL].current;
    it->second[NDb::FACTION_NEUTRAL].current = 0;
  }

  return true;
}

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(TriggerMarkerHandler,  NWorld)
