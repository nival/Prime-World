#ifndef MMAKINGUNISTAT_H_INCLUDED
#define MMAKINGUNISTAT_H_INCLUDED

#include <map>
#include <string>

namespace mmaking
{

class Loger;

class UniStatLoger : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( UniStatLoger, BaseObjectMT );

public:
  UniStatLoger( const char * _logSuffix );

  void Poll( timer::Time _now );
  void AddStat( const char * _id, double _value );

private:
  struct Stat;
  typedef std::map<std::string, StrongMT<Stat>> TStats;

  TStats            stats;
  bool              headerChangedMinute, headerChangedHour;
  timer::Time       minuteEnds, hourEnds;
  unsigned          minuteIndex, hourIndex;
  StrongMT<Loger>   minuteLoger, hourLoger;

  void MinuteDump( timer::Time _now );
  void HourDump( timer::Time _now );
  void WriteHeader( timer::Time _now, const char * _idxFldName, Loger * _loger );
  void WriteStats( timer::Time _now, unsigned _idxFld, double Stat::*sumFld, unsigned Stat::*samplesFld, Loger * _loger );
};

} //namespace mmaking

#endif //MMAKINGUNISTAT_H_INCLUDED
