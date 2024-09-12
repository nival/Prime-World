#ifndef RATINGSORTMMJOB_H_INCLUDED
#define RATINGSORTMMJOB_H_INCLUDED

#include "FullSweep.h"
#include "GameEstimFunction.h"
#include "MmQueueIterator.h"


namespace mmaking
{

namespace ERatingSortBpType
{
  enum Enum
  {
    Normal,
    LongWait,
    FullParties
  };

  NI_ENUM_DECL_STD;
}



namespace ELongWaitMode
{
  enum Enum { None, Normal, TooLong };

  NI_ENUM_DECL_STD;
};


struct RatingSortBasePoint : public GeolocationConstraints
{
  ERatingSortBpType::Enum   type;
  EBasket::Enum             basket;
  int                       rating;
  int                       force;
  int                       frequency, counter;
  lobby::ETeam::Enum        pveFaction;

  RatingSortBasePoint( const GeolocationConstraints & _geo, ERatingSortBpType::Enum t, EBasket::Enum b, int r, int f, int _freq = 1, int _counter = 0 ) :
  GeolocationConstraints( _geo ),
  type( t ),
  basket( b ),
  rating( r ),
  force( f ),
  frequency( _freq ), counter( _counter % _freq ),
  pveFaction( lobby::ETeam::None )
  {
  }
};






struct RatingSortSampleSlot
{
  const static size_t MaxConstTeamSz = 5;

  MmRequest * req;
  int waitTimeSec;
  bool mandatory;

  //Here is cached request data, to improve data locality
  struct SMember {
    lobby::ESex::Enum sex;
    THeroShortId heroid;
    EBasket::Enum basket;
    int rating;
    int force;
    int loseStreak;
    SHeroClassEfficiency heroClassEff;

    SMember() : sex( lobby::ESex::Undefined ), heroid( 0 ), rating( 0 ), force( 0 ), loseStreak( 0 ) {}

    SMember( lobby::ESex::Enum s, THeroShortId h, EBasket::Enum b, int r, int f, int loseStrk, const SHeroClassEfficiency & _heroClassEff ) :
    sex( s ), heroid( h ), basket( b ), rating( r ), force( f ), loseStreak( loseStrk ), heroClassEff( _heroClassEff ) {}
  };

  int                 size;
  SMember             memb[MaxConstTeamSz];

  RatingSortSampleSlot() :
  req( 0 ), waitTimeSec( 0 ), size( 0 ) {}

  RatingSortSampleSlot( MmRequest * _req, int _wait, bool _mandatory, EBasket::Enum _gameBasket, const NDb::MapMMakingSettings * _sett );

  int GetSlotSize() const { return size; }
};


//#define MATCHMAKING_DEBUG_ESTIM_FUNC

#ifdef MATCHMAKING_DEBUG_ESTIM_FUNC
struct ValueStat
{
  double minv, maxv, sum;
  unsigned counter;

  ValueStat() : minv( 0 ), maxv( 0 ), sum( 0 ), counter( 0 ) {}

  void Add( double f ) {
    if ( counter ) {
      sum += f;
      if ( f < minv )
        minv = f;
      if ( f > maxv )
        maxv = f;
    } else {
      sum = f;
      minv = f;
      maxv = f;
    }
    ++counter;
  }

  double Avg() const { return counter ? sum / counter : 0; }

  string ToString() const { return NI_STRFMT( "avg=%.2f, min=%.2f, max=%.2f", Avg(), minv, maxv ); }
};
#endif //MATCHMAKING_DEBUG_ESTIM_FUNC


struct RatingSortDraft : public NonCopyable
{
  GameEstimFun        fun;
  ELongWaitMode::Enum longWaitMode;
  vector<StrongMT<MmRequest>> lineup[2];
  unsigned            updates;
  vector<StrongMT<MmRequest>> bestLineup[2];
  float               minValue;
  SGameEstimDetails   minValueDetails;

#ifdef MATCHMAKING_DEBUG_ESTIM_FUNC
  ValueStat           efMaxValue, efSumValue, efForceSpanTerm, efHeroClassesTerm, efSexTerm;
#endif //MATCHMAKING_DEBUG_ESTIM_FUNC

  RatingSortDraft( const RatingSortBasePoint & _basePoint, int teamSize, const NDb::MapMMakingSettings * dbSett, lobby::ETeam::Enum manoeuvresFaction ) :
  fun( teamSize, dbSett, _basePoint.basket, manoeuvresFaction, _basePoint.pveFaction != lobby::ETeam::None ),
  longWaitMode( ELongWaitMode::None ),
  updates( 0 ),
  minValue( 0 )
  {}

  void PushBack( int teamIndex, const RatingSortSampleSlot & slot );
  void PopBack( int teamIndex, const RatingSortSampleSlot & slot );
  void CheckOut();
};



typedef TFullSweepAlgorithm<RatingSortSampleSlot, RatingSortDraft> RatingSortFSAlgorithm;



class RatingSortJob : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RatingSortJob, BaseObjectMT );

public:
  RatingSortJob( const RatingSortBasePoint & _basePoint, lobby::ETeam::Enum _manvrsFaction, const NDb::MapMMakingSettings * _dbSett, int _teamSz ) :
  teamSize( _teamSz ),
  basePoint( _basePoint ),
  manoeuvresFaction( _manvrsFaction ),
  draft( _basePoint, _teamSz, _dbSett, _manvrsFaction ),
  sample(),
  iterations( 0 ), timeWasted( 0 )
  {}

  const RatingSortBasePoint & BasePoint() const { return basePoint; }
  lobby::ETeam::Enum ManoeuvresFaction() const { return manoeuvresFaction; }
  RatingSortFSAlgorithm::Sample & Sample() { return sample; }
  RatingSortDraft & Draft() { return draft; }

  void Do();

  unsigned Iterations() const { return iterations; }
  timer::Time  TimeWasted() const { return timeWasted; }

private:
  const int                       teamSize;
  const RatingSortBasePoint       basePoint; //for debug only
  const lobby::ETeam::Enum        manoeuvresFaction;
  RatingSortDraft                 draft;
  RatingSortFSAlgorithm::Sample   sample;
  unsigned                        iterations;
  timer::Time                     timeWasted;
};

} //namespace mmaking

#endif //RATINGSORTMMJOB_H_INCLUDED
