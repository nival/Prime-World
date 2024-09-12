#ifndef DRIVERSETTINGS_H_71BCEB34_34D1_4
#define DRIVERSETTINGS_H_71BCEB34_34D1_4
#include "System/Events.h"
namespace Network
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  namespace Instrumentation
  {
    extern NDebug::PerformanceDebugVar counterNet_DriverStep;

    extern NDebug::AveragePerSecondDebugVar2<float> messagesSent;
    extern NDebug::AveragePerSecondDebugVar2<float> messagesReceived;
    extern NDebug::AveragePerSecondDebugVar2<int> bytesSent;
    extern NDebug::AveragePerSecondDebugVar2<int> bytesReceived;

    extern NDebug::DebugVar<int> activeConnections;
    extern NDebug::DebugVar<int> sendQueueSize;
    extern NDebug::DebugVar<int> recvQueueSize;

    extern NDebug::DebugVar<float> messageSizeAvg;
    extern NDebug::DebugVar<int> messageSizeMax;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // one-side trip time
  extern int latencyMin;
  extern int latencyMax;

}

#endif //#define DRIVERSETTINGS_H_71BCEB34_34D1_4
