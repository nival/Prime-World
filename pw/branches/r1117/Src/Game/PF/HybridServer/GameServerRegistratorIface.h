#pragma once

namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IGameServerInstanceRegistrator : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IGameServerInstanceRegistrator, IBaseInterfaceMT );

  virtual void RegisterInstance( Peered::IGameServer * instance, const char * instanceId ) = 0;
  virtual void UnregisterInstance( Peered::IGameServer * instance ) = 0;
};

} // namespace HybridServer
