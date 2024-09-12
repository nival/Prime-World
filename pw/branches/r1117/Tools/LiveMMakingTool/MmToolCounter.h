#pragma once

namespace mm_test
{

class MmTestCounter : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MmTestCounter, BaseObjectST );

public:
  MmTestCounter( timer::Time _playbackTime ) :
  gamesMeasurePeriod( 3.0 ),
  totalGames( 0 ), lastGameTime( _playbackTime ), lastGamesCount( 0 )
  {
    for ( int i = 0; i < 5; ++i )
      gamesPerSecond.push_back( 0 );
  }

  void CountGame() {
    ++totalGames;
  }

  void Poll( timer::Time playbackTime ) {
    if ( playbackTime > lastGameTime + gamesMeasurePeriod ) {
      lastGameTime += gamesMeasurePeriod;

      int newGames = totalGames - lastGamesCount;
      lastGamesCount = totalGames;

      gamesPerSecond.push_front( newGames );
      gamesPerSecond.pop_back();
    }
  }

  int TotalGames() const { return totalGames; }

  float AverageGamesPerSec() const {
    if ( gamesPerSecond.empty() )
      return 0;
    float sum = 0;
    for ( TIntList::const_iterator it = gamesPerSecond.begin(); it != gamesPerSecond.end(); ++it )
      sum += (float)(*it);
    return sum / (float)( gamesPerSecond.size() * gamesMeasurePeriod );
  }

private:
  typedef list<int> TIntList;

  const timer::Time             gamesMeasurePeriod;

  int                           totalGames;
  TIntList                      gamesPerSecond;
  timer::Time                   lastGameTime;
  int                           lastGamesCount;
};

} //namespace mm_test
