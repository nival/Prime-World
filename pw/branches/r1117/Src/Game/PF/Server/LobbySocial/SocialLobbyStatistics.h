#ifndef SOCIALLOBBYSTATISTICS_H_INCLUDED
#define SOCIALLOBBYSTATISTICS_H_INCLUDED

namespace StatisticService
{
  namespace RPC
  {
    struct MMakingCanceled;
    struct MMakingGame;
  }
}

namespace socialLobby
{

class IGameStatistics : public IBaseInterfaceMT
{
public:
  NI_DECLARE_CLASS_1( IGameStatistics, IBaseInterfaceMT );

  virtual void LogMMakingCancelled( const StatisticService::RPC::MMakingCanceled & _data ) = 0;
  virtual void LogMMakingGame( const StatisticService::RPC::MMakingGame & _game ) = 0;
};

} //namespace socialLobby

#endif //SOCIALLOBBYSTATISTICS_H_INCLUDED
