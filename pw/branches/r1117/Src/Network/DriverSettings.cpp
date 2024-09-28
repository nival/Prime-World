#include "stdafx.h"
#include "DriverSettings.h"

namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  namespace Instrumentation
  {
    NDebug::PerformanceDebugVar counterNet_DriverStep( "NetTotalTime", "Net", 8, 1000.0, false );
    NDebug::DebugVar<int> activeConnections( "ActiveConnections", "Net" );
    NDebug::DebugVar<int> sendQueueSize( "Queue send", "Net" );
    NDebug::DebugVar<int> recvQueueSize( "Queue recv", "Net" );

    NDebug::AveragePerSecondDebugVar2<float> messagesSent( "MessagesSent", "Net" );
    NDebug::AveragePerSecondDebugVar2<float> messagesReceived( "MessagesRecv", "Net" );
    NDebug::AveragePerSecondDebugVar2<int> bytesSent( "BytesSent", "Net" );
    NDebug::AveragePerSecondDebugVar2<int> bytesReceived( "BytesRecv", "Net" );

    NDebug::DebugVar<float> messageSizeAvg( "Net|MessageSizeAvg", "" );
    NDebug::DebugVar<int> messageSizeMax( "Net|MessageSizeMax", "" );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int latencyMin = 0;
  int latencyMax = 0;

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool CmdSetNetworkLatency( const char *name, const vector<wstring> &params )
{
  if ( params.size() != 2 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << "  min_latency(ms)  max_latency(ms)" << endl
      << "current values: min_latency = " << Network::latencyMin << ", max_latency = " << Network::latencyMax << endl;
    return true;
  }
  int min = NStr::ToInt( params[0] );
  int max = NStr::ToInt( params[1] );

  min = Max( min, 0 );
  max = Max( max, min );

  Network::latencyMax = max;
  Network::latencyMin = min;

  return true;
}

REGISTER_DEV_CMD( network_latency, CmdSetNetworkLatency );

