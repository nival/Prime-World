#ifndef HYBRIDSERVERMULTICASTIFACE_H_62B
#define HYBRIDSERVERMULTICASTIFACE_H_62B

#include "System/Pointers/BaseInterface.h"

namespace Peered
{
  struct IGameClient;
}

namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IMcChannelsWrapper : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IMcChannelsWrapper, IBaseInterfaceMT);

public:
  virtual bool AddClient(const Peered::IGameClient * client, uint clientId, int clientIndex) = 0;
  virtual bool RemoveClient(uint clientId) = 0;
  virtual bool FindClient(uint clientId) = 0;
  virtual int GetClientsCount() = 0;
  virtual bool SendData(const byte * data, int size) = 0;
  virtual void Close() = 0;
};


} // namespace HybridServer


#endif //#define HYBRIDSERVERMULTICASTIFACE_H_62B