#ifndef LOBBYENTRANCE_H_INCLUDED
#define LOBBYENTRANCE_H_INCLUDED

#include "LobbyIEntrance.h"


namespace lobby
{

class ServerNode;

class Entrance : public IEntrance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Entrance, IEntrance, BaseObjectMT );

public:
  Entrance( ServerNode * _server );

protected:
  virtual RIServerInstance * RequestServerInstance( RILobbyUser * user, int clientRevision );

private:
  WeakMT<ServerNode>    server;
};

} //namespace lobby

#endif //LOBBYENTRANCE_H_INCLUDED
