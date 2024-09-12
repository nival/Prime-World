#include "stdafx.h"

#include "EaselStatistics.h"
#include "LuxDef.h"

#include "Easel.h"
#include "EaselWorld.h"

#include "DBEasel.h"

#include "EaselPriestess.h"

#include "EaselGameWonNotitfication.h"
#include "EaselGameLostNotitfication.h"

#include "PaintLogic.h"

#include "System/FileSystem/FileWriteStream.h"
#include "System/FileSystem/FileUtils.h"

#include "PF_GameLogic/PFStatistics.h"

namespace PF_Minigames
{


EaselStatistics::EaselStatistics()
{
  for ( int i = 0; i < NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf; ++i )
  {
    levelWonCount[i]       = 0;
    levelMedalEarned[i] = NDb::WONGAMEMEDAL_NONE;
  }
}

NDb::WonGameMedal EaselStatistics::GetLevelMedalEarned(int levelId) const
{
  if(levelId < 0 || levelId >= NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf)
  {
    systemLog(NLogg::LEVEL_CRITICAL) << "EaselStatisticsArchive: level id is out of range" << endl;
    return NDb::WONGAMEMEDAL_NONE;
  }

  return levelMedalEarned[levelId];
}

bool EaselStatistics::IsGameFullyCompleted() const
{
  return levelWonCount[NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf - 1] > 0;
}

//////////////////////////////////////////////////////////////////////////
const CObj<EaselLevelStatistics>& EaselStatistics::StartGatherFoNewLevel( PF_Core::IWorld* _pWorld, int paintId, int levelId)
{
  currentLevel = new EaselLevelStatistics( _pWorld, paintId, levelId );
  return currentLevel;
}

//////////////////////////////////////////////////////////////////////////
void EaselStatistics::StopGatherForLevel()
{
  if ( currentLevel->GetRoundStatus() == NDb::EASELROUNDSTATUS_WON )
  {
    levelWonCount[ currentLevel->GetLevelID() ]++;
    levelMedalEarned[ currentLevel->GetLevelID() ] = max( levelMedalEarned[ currentLevel->GetLevelID() ], currentLevel->GetMedal() );
  }

  if ( IsValid( easel ) && easel->GetWorld() && easel->GetWorld()->GetPriestessProxy() )
  {
    if ( IsGameFullyCompleted() )
      easel->GetWorld()->GetPriestessProxy()->MinigameComplete();
  }
}

void EaselStatistics::Copy( const EaselStatistics& _remoteStat )
{
  for ( int i = 0; i < NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf; ++i )
  {
    levelWonCount[i] = _remoteStat.levelWonCount[i];
    levelMedalEarned[i] = _remoteStat.levelMedalEarned[i];
  }

  if ( IsValid(_remoteStat.currentLevel) )
  {
    if ( !IsValid( currentLevel ) )
      currentLevel = new EaselLevelStatistics( 0, 1, 1 );

    currentLevel->Copy( _remoteStat.currentLevel );
  }
}


//////////////////////////////////////////////////////////////////////////
//
// class EaselLevelStatistics implementation
//


//////////////////////////////////////////////////////////////////////////
EaselLevelStatistics::EaselLevelStatistics( PF_Core::IWorld* _pWorld, int _paintId, int _levelId )
: PF_Core::WorldObjectBase( _pWorld, false )
, wonAwardMedal(NDb::WONGAMEMEDAL_NONE)
, paintId(_paintId)
, levelId(_levelId)
, status(NDb::EASELROUNDSTATUS_INCOMPLETE)
, elapsedTime(0.0f)
{

}

//////////////////////////////////////////////////////////////////////////
EaselLevelStatistics::~EaselLevelStatistics()
{

}

//////////////////////////////////////////////////////////////////////////
void EaselLevelStatistics::ProcessStep(int deltaTime)
{
  if ( status == NDb::EASELROUNDSTATUS_INCOMPLETE  )
    elapsedTime += deltaTime / 1000.0f;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLevelStatistics::InitStats( Easel * _easel, IPriestessProxy * spProxy, PaintLogic * _paintLogic )
{
  // getting stats data storage
  priestessStats = _easel->GetData()->priestessStats;
  priestessLevelStats = 0;

  spPriestessProxy = spProxy;

  dbGame = _easel->GetData()->game;
  NI_VERIFY( dbGame, "EaselLevelStatistics: easel game data is invalid", return );

  // init fail gold return
  priestessStats = _easel->GetData()->priestessStats;
  NI_VERIFY(IsValid(priestessStats), "EaselLevelStatistics: priestess stats is invalid", return);

  priestessLevelStats = _easel->GetPriestessLevelStats();
  NI_VERIFY(IsValid(priestessLevelStats), "EaselLevelStatistics: priestess level stats is invalid", return);

  paintLogic = _paintLogic;
}




//////////////////////////////////////////////////////////////////////////
void EaselLevelStatistics::OnGameWon()
{
  NI_VERIFY( status == NDb::EASELROUNDSTATUS_INCOMPLETE, "EaselLevelStatistics: round isn't in incomplete state", return);

  status = NDb::EASELROUNDSTATUS_WON;

  wonAwardMedal = NDb::WONGAMEMEDAL_NONE;

  NI_VERIFY(IsValid(spPriestessProxy), "EaselLevelStatistics: priestess proxy is invalid", return);
  NI_VERIFY(IsValid(priestessLevelStats), "EaselLevelStatistics: priestess level stats is invalid", return);

  // calculating medal (adding it to game statistics)
  DevTrace( "MG2 DEBUG: OnGameWon! time(%f)", elapsedTime );

  EMinigameLevelStatus::Enum statisticsStatus = EMinigameLevelStatus::Done;
  if( elapsedTime <= priestessLevelStats->goldMedalTime )
  {
    wonAwardMedal = NDb::WONGAMEMEDAL_GOLD;
    statisticsStatus = EMinigameLevelStatus::Gold;
    spPriestessProxy->AddGoldDelayed( priestessLevelStats->goldMedalNafta );
    DevTrace( "MG2 DEBUG: Add gold for GoldMedal: goldMedalNafta(%d) = total(%d)", priestessLevelStats->goldMedalNafta, priestessLevelStats->goldMedalNafta );

    // calculate time awarded gold
    float awardedTime = priestessLevelStats->goldMedalTime - elapsedTime;
    awardedTime = max( 0, awardedTime );

    spPriestessProxy->AddGoldDelayed( floorf( awardedTime * priestessLevelStats->fastCompletePerSecondNafta ) );
    DevTrace( "MG2 DEBUG: Add gold for TimeAward: awardedTime(%f) * fastCompletePerSecondNafta(%d) = total(%d)", awardedTime, priestessLevelStats->fastCompletePerSecondNafta, floorf( awardedTime * priestessLevelStats->fastCompletePerSecondNafta ) );
  }
  else if ( elapsedTime <= priestessLevelStats->silverMedalTime )
  {
    wonAwardMedal = NDb::WONGAMEMEDAL_SILVER;
    statisticsStatus = EMinigameLevelStatus::Silver;
    spPriestessProxy->AddGoldDelayed( priestessLevelStats->silverMedalNafta );
    DevTrace( "MG2 DEBUG: Add gold for SilverMedal: silverMedalNafta(%d) = total(%d)", priestessLevelStats->silverMedalNafta, priestessLevelStats->silverMedalNafta );
  }

  spPriestessProxy->AddGoldDelayed( priestessLevelStats->pictureEndNafta );
  DevTrace( "MG2 DEBUG: Add gold for PictureEnd: pictureEndNafta(%d) = total(%d)", priestessLevelStats->pictureEndNafta, priestessLevelStats->pictureEndNafta );

  spPriestessProxy->SetRewardItemId( paintId );

  spPriestessProxy->MinigameLevelEnd( levelId, statisticsStatus );
}

void EaselLevelStatistics::OnGameLost()
{
  NI_VERIFY(status == NDb::EASELROUNDSTATUS_INCOMPLETE, "EaselLevelStatistics: round isn't in incomplete state", return);

  status = NDb::EASELROUNDSTATUS_FAILED;

  if ( IsValid( paintLogic ) && dbGame )
  {
    float fillRatio = Clamp( paintLogic->CalculateFillRatio(), 0.0f, 1.0f );
    float nafta = priestessLevelStats->pictureEndNafta * fillRatio * dbGame->failureExperienceFactor;
    int intNafta = (int)floorf( nafta + 0.5f );
  
    if ( intNafta>0 )
    {
      spPriestessProxy->AddGoldDelayed( intNafta );
      DevTrace( "MG2 DEBUG: Add gold for GameLost: fillRatio(%f) * pictureEndNafta(%d) * failureExperienceFactor(%f) = total(%d)", fillRatio, priestessLevelStats->pictureEndNafta, dbGame->failureExperienceFactor, intNafta );
    }
  }

  spPriestessProxy->MinigameLevelEnd( levelId, EMinigameLevelStatus::Failed );
}

void EaselLevelStatistics::Copy( const EaselLevelStatistics* _remoteStat )
{
  if ( !IsValid( _remoteStat ) )
    return;

  status = _remoteStat->status;
  wonAwardMedal = _remoteStat->wonAwardMedal;
  elapsedTime = _remoteStat->elapsedTime;
  paintId = _remoteStat->paintId;
  levelId = _remoteStat->levelId;
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( EaselLevelStatistics, PF_Minigames )

