#include "stdafx.h"
#include "LobbyEntrance.h"
#include "LobbyServerNode.h"


namespace lobby
{

Entrance::Entrance( ServerNode * _server ) :
server( _server )
{
}



RIServerInstance * Entrance::RequestServerInstance( RILobbyUser * user, int clientRevision )
{
  StrongMT<ServerNode> locked = server.Lock();
  if ( locked )
    return locked->AddClient( user, clientRevision );

  return 0;
}

} //namespace lobby
