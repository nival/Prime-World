#include "StdAfx.h"
#include "StatisticsController.h"

#include "AdventureFlashInterface.h"
#include "PFWorld.h"
#include "PFHero.h"
#include "PFPlayer.h"
#include "PFStatistics.h"
#include "PFWorldNatureMap.h"
#include "PFAIWorld.h"

namespace NGameX
{

StatisticsController::PlayerScoreParams::PlayerScoreParams()
{
  killsCount = assistCount = deathCount = score = primeEarned = -1;
}

bool StatisticsController::PlayerScoreParams::operator==( const PlayerScoreParams &other ) const
{
  return this->killsCount		== other.killsCount &&
				 this->assistCount	== other.assistCount &&	
				 this->deathCount		== other.deathCount &&	
				 this->score				== other.score &&	
				 this->primeEarned	== other.primeEarned;
}

StatisticsController::StatisticsController( AdventureFlashInterface * _flashInterface, NWorld::PFWorld * _world )
: tabPressed(false)
, flashInterface(_flashInterface)
, world(_world)
, elfDomination(0)  
, humanDomination(0)
, timeElapsed(0)
, timeToCreepSpawn(0)
{
  Update();
}

void StatisticsController::TabPressed( bool pressed )
{
  if (!IsValid(flashInterface))
    return;

  if (!tabPressed && pressed)
  {
    Update();
    flashInterface->ShowStatistics(true);
  }
  else if (tabPressed && !pressed)
  {
    flashInterface->ShowStatistics(false);
  }

   tabPressed = pressed;
}

void StatisticsController::Update()
{
  for (int i = 0; i < world->GetPlayersCount(); ++i)
  {
    const NWorld::PFPlayer * player = world->GetPlayer(i);
    if (IsValid(player) && IsValid(player->GetHero()))
    {
      const NWorld::PFHeroStatistics * statistics = player->GetHero()->GetHeroStatistics();
      if (!IsValid(statistics))
        continue;

      int playerID    = player->GetPlayerID();

      PlayerScoreParams & playerParams = playersParams[playerID];

      PlayerScoreParams newParams;

      newParams.killsCount  = statistics->GetTotalNumHeroKills();
      newParams.assistCount = statistics->GetTotalNumHeroAssists();
      newParams.deathCount  = statistics->GetNumDeaths();
      newParams.score       = statistics->GetGrandScore();
			newParams.primeEarned = player->GetHero()->GetTotalNaftaEarned();

      if (playerParams == newParams)
        continue;

      playerParams = newParams;

      flashInterface->SetHeroGameProgress(playerID, newParams.killsCount, newParams.deathCount, newParams.assistCount, newParams.score, newParams.primeEarned);
    }
  }

  const NWorld::PFWorldNatureMap* natureMap = world->GetNatureMap();
  if ( natureMap != NULL )
  {
    float newElfDomination   = natureMap->GetNaturePercent( NDb::FACTION_BURN  );
    float newHumanDomination = natureMap->GetNaturePercent( NDb::FACTION_FREEZE);
    int newTimeElapsed = (int)(world->GetTimeElapsed());
    int newTimeToCreepSpawn = (int)(world->GetAIWorld()->GetBattleStartDelay());

    if (newElfDomination != elfDomination || newHumanDomination!=humanDomination || timeElapsed!=newTimeElapsed || newTimeToCreepSpawn!= timeToCreepSpawn )
    {
      elfDomination = newElfDomination;
      humanDomination = newHumanDomination;
      timeElapsed = newTimeElapsed;
      timeToCreepSpawn = newTimeToCreepSpawn;
      flashInterface->SetGameProgress(humanDomination, elfDomination, timeElapsed, timeToCreepSpawn);
    }
  }


}
}