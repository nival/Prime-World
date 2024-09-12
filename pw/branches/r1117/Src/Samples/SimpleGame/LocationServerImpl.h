#ifndef LOCATIONSERVERIMPL_H_B5DD1900_B6
#define LOCATIONSERVERIMPL_H_B5DD1900_B6

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template < bool block >
inline LocationServer::BlockUnblockHelper<block>::BlockUnblockHelper( int _receiverID, ClientPlayers& _clientPlayers, World* _world, rpc::Gate& _gate ) :
  gate(_gate),
  receiverNode(0),
  clientPlayers(_clientPlayers),
  receiverID(_receiverID ),
  world(_world),
  counter(0)
{
  playerObject = world->GetObjectById( receiverID );

  ClientPlayers::iterator it = clientPlayers.find( receiverID );

  if ( it != clientPlayers.end() )
  {
    receiverNode = it->second.connection ? it->second.connection->node : 0;
    receiverPlayer = it->second.player;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template < bool block >
inline void LocationServer::BlockUnblockHelper<block>::operator()( int objectID ) 
{ 
  if ( receiverID == objectID )
    return;

  ClientPlayers::iterator it = clientPlayers.find( objectID );

  if ( it == clientPlayers.end() )
    return;

  counter++;

  CPtr<GameObject> otherPlayer = world->GetObjectById( objectID );

  if ( block )
  {
    NI_ASSERT( it->second.player, "Must be not null" ); 
    NI_ASSERT( receiverPlayer, "Must be not null" ); 

    gate.Block( *it->second.player, *receiverNode );
    gate.Block( *receiverPlayer, *it->second.connection->node );

//    otherPlayer->AddNeighbourCount( -1 );
  }
  else
  {
    if ( IsValid( it->second.player ) )
      gate.Unblock( *it->second.player, *receiverNode );
    else
    {
      if ( receiverNode )
        it->second.player = receiverNode->Create<RGameObject>( otherPlayer->GetID(), otherPlayer->GetPlacement(), otherPlayer->GetClientResource() );
    }

    if ( receiverNode )
      ExlusiveMoveTo( it->second.player, otherPlayer, gate, receiverNode );

    if ( IsValid( receiverPlayer ) && it->second.connection )
      gate.Unblock( *receiverPlayer, *it->second.connection->node );
    else
    {
      if ( it->second.connection )
      {
        receiverPlayer = it->second.connection->node->Create<RGameObject>( otherPlayer->GetID(), otherPlayer->GetPlacement(), otherPlayer->GetClientResource() );
        ClientPlayers::iterator it = clientPlayers.find( receiverID );
        it->second.player = receiverPlayer;
      }
    }

    if ( it->second.connection )
      ExlusiveMoveTo( receiverPlayer, playerObject, gate, it->second.connection->node );

//    otherPlayer->AddNeighbourCount( +1 );
  }
}

} // namespace Location

#endif //#define LOCATIONSERVERIMPL_H_B5DD1900_B6