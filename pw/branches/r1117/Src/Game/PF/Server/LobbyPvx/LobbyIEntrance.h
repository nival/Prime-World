#ifndef LOBBYIENTRANCE_H__INCLUDED
#define LOBBYIENTRANCE_H__INCLUDED


#include "CommonTypes.h"


namespace lobby
{

class RILobbyUser;
class RIServerInstance;


REMOTE class IEntrance : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IEntrance, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual RIServerInstance* RequestServerInstance( RILobbyUser * user, int clientRevision ) = 0;
};

}; //namespace lobby

#endif //LOBBYIENTRANCE_H__INCLUDED
