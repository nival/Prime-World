#include "stdafx.h"
#include "PFStatisticsStuff.h"
#include "PFStatistics.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"
#endif

#include "PFStatisticsImpl.h"

namespace
{
  bool g_isStatFull = true;
  bool g_isStatOutput = true;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FillKillInstance_
{
  FillKillInstance_(NWorld::StatisticsStuff::HeroKillInstance &killInstance): killInstance(killInstance) {}
  
  void operator()(NWorld::PFBaseHero &pHero) const
  {    
    NI_ASSERT( IsValid(killInstance.pVictim), "Victim must be valid!" );
    killInstance.heroPositions.push_back(NWorld::StatisticsStuff::HeroPosition(pHero.GetObjectId(), pHero.GetPosition()));
  }

  NWorld::StatisticsStuff::HeroKillInstance &killInstance;
private:
  FillKillInstance_ &operator = (FillKillInstance_ const &);
};

}

namespace NWorld
{

namespace StatisticsStuff
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroKillInstance::HeroKillInstance(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, float time, PFStatistics &statistics): HeroDeathInstance(pVictim, pKiller, time), victimPosition(pVictim->GetPosition())
{  
  FillKillInstance_ classObj(*this);
  statistics.ForAllHeroes(classObj);
}


} //namespace StatisticsStuff

} //namespace NWorld

REGISTER_DEV_VAR( "score_stat_full", g_isStatFull, STORAGE_NONE );
REGISTER_DEV_VAR( "score_stat_output",  g_isStatOutput, STORAGE_NONE );
