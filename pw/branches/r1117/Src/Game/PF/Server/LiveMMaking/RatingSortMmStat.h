#ifndef RATINGSORTMMSTAT_H_INCLUDED
#define RATINGSORTMMSTAT_H_INCLUDED

#include "ProdMmLogicBase.h"
#include "RatingSortMmJob.h"
#include <vector>

namespace mmaking
{

class Loger;
class UniStatLoger;

class RatingSortStatistics : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RatingSortStatistics, BaseObjectMT );

public:
  RatingSortStatistics( UniStatLoger * _uniStats ) :
  gamesDone( 0 ), samplesMade( 0 ),
  manoeuvresGames( 0 ),
  longWaitGames( 0 ), waitTooLongGames( 0 ),
  fullPartyGames( 0 ),
  lastBasePointCycleStartTime( 0 ),
  timeInProMode( 0 ),
  uniStats( _uniStats )
  {
  }

  void OnSample() { ++samplesMade; }
  void OnBpCycleStart( timer::Time _now );
  void OnProModeEnd( timer::Time _duration ) { timeInProMode += _duration; }
  void OnGame( ERatingSortBpType::Enum _bpType, ELongWaitMode::Enum _longWaitMode, lobby::ETeam::Enum _manoeuvresFaction );

  void Dump( Loger * loger, timer::Time _now, timer::Time _currentlyInProMode );

private:
  unsigned          gamesDone;
  unsigned          samplesMade;
  unsigned          manoeuvresGames;
  unsigned          fullPartyGames;

  unsigned          longWaitGames;
  unsigned          waitTooLongGames;

  timer::Time       lastBasePointCycleStartTime;
  timer::Time       timeInProMode;

  StrongMT<UniStatLoger> uniStats;
};

} //namespace mmaking

#endif RATINGSORTMMSTAT_H_INCLUDED
