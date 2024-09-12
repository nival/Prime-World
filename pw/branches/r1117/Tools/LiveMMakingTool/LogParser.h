#ifndef LOGPARSER_H_INCLUDED
#define LOGPARSER_H_INCLUDED

#include "Server/LiveMMaking/LiveMMakingTypes.h"

namespace mm_test
{

namespace ELogVersion {
  enum Enum {
    v82x,
    v902,
    v903,
    v911,
    v914,
    v923,
    v932,
    v940,
    v941,
    v942,
    trunk
  };

  NI_ENUM_DECL_STD;
};



struct Date
{
  int year, mon, day;
  
  Date() : year( 0 ), mon( 0 ), day( 0 ) {}
  Date( int y, int m, int d ) : year( y ), mon( m ), day( d ) {}
  
  bool operator < ( const Date & other ) const {
    if ( year < other.year ) return true;
    if ( mon < other.mon ) return true;
    return day < other.day;
  }
  bool operator == ( const Date & other ) const { return year==other.year && mon==other.mon && day==other.day; }
  bool IsValid() const { return mon >= 1 && mon <= 12 && day >= 1 && day <= 31; }
};

struct Time
{
  int hour, minute, sec, ms;
  
  Time() : hour( 0 ), minute( 0 ), sec( 0 ), ms( 0 ) {}
  Time( int h, int m, int s, int _ms = 0 ) : hour( h ), minute( m ), sec( s ), ms( _ms ) {}

  bool operator < ( const Time & other ) const {
    if ( hour < other.hour ) return true;
    if ( minute < other.minute ) return true;
    if ( sec < other.sec ) return true;
    return ms < other.ms;
  }
  bool operator == ( const Time & other ) const { return hour==other.hour && minute==other.minute && sec==other.sec && ms==other.ms; }
  bool IsValid() const { return hour>=0 && hour<=24 && minute>=0 && minute<=59 && sec>=0 && sec<=59 && ms>=0 && ms<=999; }
};

struct Timestamp
{
  Date date;
  Time time;

  Timestamp() {}
  Timestamp( const Date & d, const Time & t ) : date( d ), time( t ) {}

  explicit Timestamp( timer::Time t ) : date(), time( (int)t / 3600, ((int)t % 3600 ) / 60, (int)t % 60, t - floor(t) ) {}

  bool operator < ( const Timestamp & other ) const {
    if ( date < other.date ) return true;
    return time < other.time;
  }
  bool operator == ( const Timestamp & other ) const { return date==other.date && time==other.time; }
  bool IsValid() const { return date.IsValid() && time.IsValid(); }
};



timer::Time TimeDiff( const Timestamp & ts1, const Timestamp & ts0 );
void Advance( Timestamp & ts, timer::Time delta );


class ILogParserCb : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( ILogParserCb, IBaseInterfaceST );

public:
  virtual void OnAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait ) = 0;
  virtual void OnRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId ) = 0;
  virtual void OnGame( const Timestamp & ts, const mmaking::SGame & game ) = 0;
  virtual void OnProgress( int progress ) = 0;

  virtual void Finish() = 0;
  virtual void Output() = 0;
};

} //namespace mm_test

#endif //LOGPARSER_H_INCLUDED
