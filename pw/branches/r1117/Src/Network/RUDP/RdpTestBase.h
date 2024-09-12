#ifndef RDPTESTBASE_H_INCLUDED
#define RDPTESTBASE_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include <vector>
#include <string>

namespace ETestObjectState
{
  enum Enum { Init, Handshake, Active, Closing, Failed, Finished };
};


class RdpTestObject : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpTestObject, BaseObjectMT );
public:
  explicit
  RdpTestObject( timer::Time _now, int _instanceIdx, int _uid ) :
  state( ETestObjectState::Init ),
  instanceIdx( _instanceIdx ),
  uid( _uid ),
  now( _now ),
  timerEnds( -1 )
  {
  }


  int InstIdx() const { return instanceIdx; }
  int Uid() const { return uid; }

  ETestObjectState::Enum State() const { return state; }


  bool Poll( timer::Time _now )
  {
    now = _now;

    if ( ( state == ETestObjectState::Failed ) || ( state == ETestObjectState::Finished ) )
      return false;

    if ( timerEnds >= 0 ) 
      if ( _now > timerEnds )
      {
        ErrorTrace( "Timer expired. inst=%d, uid=%d, name=%d", instanceIdx, uid, timerDbgMsg.c_str() );
        Switch( ETestObjectState::Failed );
        return false;
      }

    return true;
  }


protected:
  void SetUid( int _uid ) { uid = _uid; }

  timer::Time Now() const { return now; }

  void Switch( ETestObjectState::Enum _st )
  {
    if ( ( _st == ETestObjectState::Failed ) || ( _st == ETestObjectState::Finished ) )
      StopTimer();

    if ( ( state == ETestObjectState::Failed ) || ( state == ETestObjectState::Finished ) )
      return;

    state = _st;
  }


  void Fail()
  {
    WarningTrace( "Test object failed. inst=%d, uid=%d", instanceIdx, uid );
    Switch( ETestObjectState::Failed );
  }


  void StartTimer( timer::Time _duration, const char * _dbgMsg )
  {
    NI_ASSERT( timerEnds < 0, "" );

    timerEnds = now + _duration;
    timerDbgMsg = _dbgMsg;
  }


  void StopTimer()
  {
    timerEnds = -1;
    timerDbgMsg.clear();
  }


  bool ParseCmd( const void * _data, size_t _size, const char * _key, int & _intVal )
  {
    std::vector<char> buf;
    return ParseCmd( _data, _size, _key, _intVal, buf );
  }


  bool ParseCmd( const void * _data, size_t _size, const char * _key, int & _intVal, std::vector<char> & _leftover )
  {
    const char * data = (const char * )_data;
    size_t textLen = 0;
    for ( ; textLen < _size; ++textLen )
      if ( !data[textLen] )
        break;
    if ( textLen >= _size )
    {
      ErrorTrace( "Command without terminating zchar. uid=%d", uid );
      return false;
    }

    char fmt[64] = "";
    sprintf( fmt, "%s %%i", _key );

    if ( sscanf( data, fmt, &_intVal ) != 1 )
      return false;

    size_t leftoversz = _size - textLen - 1;
    if ( leftoversz )
    {
      _leftover.resize( leftoversz, 0 );
      memcpy( &_leftover[0], data + textLen + 1, leftoversz );
    }
    return true;
  }

private:
  ETestObjectState::Enum    state;
  int                       instanceIdx;
  int                       uid;
  timer::Time               now;
  timer::Time               timerEnds;
  std::string               timerDbgMsg;
};

#endif //RDPTESTBASE_H_INCLUDED
