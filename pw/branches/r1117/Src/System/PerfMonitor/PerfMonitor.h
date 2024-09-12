#ifndef PERFMONITOR_H_6B52B396_D5C4_4843
#define PERFMONITOR_H_6B52B396_D5C4_4843

#include "System/ThreadHelpers.h"

namespace PerfMonitor
{
  class PerfThread;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PerfMonitor
  {
  public:
    PerfMonitor( int updateIntervalMs, const char* debugVarScreen = 0, const char* debugVarName = 0 );
    ~PerfMonitor();

    int GetCoresCount() const { return coresCount; }
    float GetCPUUsagePercent() const 
    { 
      return coresUsage / coresCount * 100.f; 
    }
    float GetUsedCores() const // equals to GetCPUUsagePercent * GetCoresCount / 100  
    {
      return coresUsage;
    }
  private:
    int coresCount;
    volatile float coresUsage;
    PerfThread* pThread;
    NDebug::DebugVar<float>* pDebugVar;

    int CountCores();
    void SetUsage( float _coresUsage );
    friend class PerfThread;
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};



#endif //#define PERFMONITOR_H_6B52B396_D5C4_4843
