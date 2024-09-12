#pragma once


namespace StatisticService
{

namespace RPC
{
  struct SessionEventInfo;
  struct SessionDamageInfo;
}

class IGameStatistics : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IGameStatistics, IBaseInterfaceMT );

public:
  virtual void LogSessionEvent( int step, float x, float y, int eventType, const RPC::SessionEventInfo & info ) = 0;
  virtual void LogSessionDamage( const RPC::SessionDamageInfo & info, int step ) = 0;
  virtual void LogPvxLogin() = 0;
  virtual void LogScreenResolution( int w, int h ) = 0;
};

} //namespace StatisticService
