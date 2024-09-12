#ifndef PERFCOUNTERS_H_INCLUDED
#define PERFCOUNTERS_H_INCLUDED

namespace Transport
{

class IPerfCounters : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPerfCounters, IBaseInterfaceMT );
public:
  virtual void AutoPerfCounterRate( const char * _name, unsigned _number ) = 0;
  virtual void AutoPerfCounterValue( const char * _name, double _value ) = 0;
};

} //namespace Transport

#endif //PERFCOUNTERS_H_INCLUDED
