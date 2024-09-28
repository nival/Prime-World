#pragma once

#include "MMakingLogParser.h"
#include <string>

namespace mm_test
{

class BasicLogParser : public ILogParserCb, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( BasicLogParser, ILogParserCb, BaseObjectST );

public:
  BasicLogParser( const float _playbackStep = 1.0f, const char * _consoleTitle = "Job" ) :
  playbackStep( _playbackStep ),
  consoleTitle( _consoleTitle ), lastProgress( -1 ), workStated( timer::Now() ),
  playbackStarted( false ), playbackTime( 0.0 ) {}

  virtual void OnAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait ) {}
  virtual void OnRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId ) {}
  virtual void OnGame( const Timestamp & ts, const mmaking::SGame & game ) {}

  virtual void OnProgress( int progress ) {
    timer::Time t = timer::Now();
    if ( progress == lastProgress )
      return;
    lastProgress = progress;

    timer::Time eta = 0;
    timer::Time passed = t - workStated;
    if ( ( passed > 1.0 ) && ( progress > 0 ) ) {
      double speed = progress / passed;
      eta = ( 100 - progress ) / speed;
    }

    int h = (int)( eta / 3600.0 ), m = (int)( ( eta - h * 3600.0 ) / 60.0 ), s = (int)( ( eta - h * 3600 - m * 60.0 ) );
    SetConsoleTitle( NI_STRFMT( "%s progress: %d%%. ETA: %02d:%02d:%02d", consoleTitle.c_str(), progress, h, m, s ) );
  }

  virtual void Finish() {}

  virtual void Output() {}

protected:
  void PlayToTimestamp( const Timestamp & ts ) {
    if ( !playbackStarted ) {
      playbackStarted = true;
      playbackStartTime = ts;
    }

    timer::Time time = TimeDiff( ts, playbackStartTime );
    PlayTo( time );
  }


  void PlayTo( timer::Time time ) {
    while ( playbackTime + playbackStep < time )
    {
      playbackTime += playbackStep;

      playbackTimestamp = playbackStartTime;
      Advance( playbackTimestamp, playbackTime );

      PlaybackPoll();
    }
  }

  const timer::Time PlaybackTime() const { return playbackTime; }
  const Timestamp & PlaybackTimestamp() const { return playbackTimestamp; }

  virtual void PlaybackPoll() {}

private:
  const float     playbackStep;

  //Console title & ETA
  std::string     consoleTitle;
  int             lastProgress;
  timer::Time     workStated;

  bool            playbackStarted;
  Timestamp       playbackStartTime;

  timer::Time     playbackTime;
  Timestamp       playbackTimestamp;
};

} //namespace mm_test
