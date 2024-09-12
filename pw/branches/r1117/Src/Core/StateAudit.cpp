#include "stdafx.h"
#include "StateAudit.h"

#include "CoreFSM.h"

#include "MessagesAudit.h"
#include "GameCommand.h"
#include "CommandSerializer.h"
#include "GameNode.h"
#include "Transceiver.h"
#include "WorldBase.h"
#include "MessagesInGame.h"


namespace NCore
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalNode
  : public CGameNode
{
  LocalNode() {}
  OBJECT_METHODS( 0xF6484C0, LocalNode );

  CPtr<CGameNode> remoteNode;
  int clientId;
  int nodeId;
  
public:
  LocalNode( int clientId, int nodeId ) : clientId(clientId), nodeId(nodeId) {}
  virtual void SendGameCommand(CGameCmd *pCmd)
  {
    remoteNode->PushGameCommand(pCmd);
  }
  void SetRemoteNode(const CPtr<CGameNode>& pNode)
  {
    NI_ASSERT(clientId != nodeId, "Linking local node!" );
    remoteNode = pNode;
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CStateAudit::TransceiverHolder::TransceiverHolder( int nodesCount, int clientId )
  : transceiver( new Transceiver() )
  , started(false)
{
  for (int nodeId = 0; nodeId < nodesCount; ++nodeId )
  {
    CPtr<CGameNode> node = new LocalNode(clientId, nodeId);
    nodes.push_back(node);
  }
  transceiver->Init( nodes, clientId );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CStateAudit::CStateAudit( CoreFSM *pContext )
  : CoreFSMState(pContext)
  , playersCount(0)
  , stage(eStartingAudit)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStateAudit::~CStateAudit()
{
  for ( int i = 0; i < maxPlayers; ++i )
    Reset(m_holders[i], NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateAudit::SubscribeUpdates()
{
  CoreFSMState::SubscribeUpdates();
  Subscribe( &CStateAudit::OnAuditGameStarted );
  Subscribe( &CStateAudit::OnAuditStartInfo );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateAudit::OnAuditStartInfo( const AuditStartInfo& msg )
{
  NI_VERIFY( stage == eWaitingStartInfo, "Wrong audit stage!", return; );
  
  // Make copy of MapStartInfo (need to tweak it playersInfo member)
  MapStartInfo mapInfo = msg.startInfo;

  // get players count
  playersCount = 0;
  for( vector<PlayerStartInfo>::iterator iPlayer = mapInfo.playersInfo.begin(), iEnd = mapInfo.playersInfo.end(); iPlayer != iEnd; ++iPlayer )
  {
    if (iPlayer->playerType != NCore::PLAYER_INVALID)
    {
      iPlayer->nodeID = playersCount;
      ++playersCount;
    }
  }

  NI_VERIFY( maxPlayers >= playersCount, "Too much players!", return; );

  // create pipes
  for ( int i = 0; i < playersCount; ++i )
  {
    m_holders[i] = AutoPtr<TransceiverHolder>( new TransceiverHolder(playersCount, i) );
    StartAuditGameInfo info = { m_holders[i]->nodes, mapInfo, i };
    pContext->PushMessageFromCore( new StartAuditGame(info) );
  }

  // Link all nodes to theirs pairs
  for ( int iClient = 0; iClient < playersCount; ++iClient )
  {
    for ( int iNode = 0; iNode < playersCount; ++iNode )
    {
      if ( iNode != iClient )
      {
        LocalNode* pNode1 = dynamic_cast<LocalNode*>(m_holders[iClient]->nodes[iNode].GetPtr());
        LocalNode* pNode2 = dynamic_cast<LocalNode*>(m_holders[iNode]->nodes[iClient].GetPtr());
        pNode1->SetRemoteNode(pNode2);
        pNode2->SetRemoteNode(pNode1);
      }
    }
  }
  
  stage = eStartingGames;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateAudit::OnAuditGameStarted( const AuditGameStarted& msg )
{
  int clientId = msg.clientId;
  NI_VERIFY( clientId >= 0 && clientId < maxPlayers, "Wrong player ID or max players count exceeded!", return; );
  NI_VERIFY( m_holders[clientId], "Game for that client is not inited!", return; );
  
  m_holders[clientId]->transceiver->Init( msg.pWorld, msg.pLoadCmd, msg.mMode, "", 1 );
  m_holders[clientId]->started = true;
  
  for ( int i = 0; i < playersCount; ++i )
    if ( i != clientId )
      m_holders[clientId]->transceiver->OnNodeReady(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateAudit::OnMapLoaded( const struct MapLoaded& msg )	
{
  pContext->PushMessageFromCore( new MapLoaded() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBaseFSMState* CStateAudit::Step(float dt)
{
  if ( stage == eStartingAudit )
  {
    pContext->PushMessageFromCore( new StartingAudit() );
    stage = eWaitingStartInfo;
  }
  else if ( stage == eStartingGames )
  {
    int gamesStarted = 0;
    // check if all games started
    for ( int i = 0; i < playersCount; ++i)
    {
      NI_ASSERT( m_holders[i], "Invalid holder!" );
      if ( m_holders[i] && m_holders[i]->started )
        ++gamesStarted;
    }
    if ( gamesStarted == playersCount )
    {
      // All games started
      stage = eGaming;
      pContext->PushMessageFromCore( new AuditStarted() );
    }
  }
  
  if ( stage == eGaming )
  {
    // Update transceivers in all started holders
    for ( int i = 0; i < playersCount; ++i )
      if ( m_holders[i] )
        m_holders[i]->transceiver->Step(dt);
  }
  
  return NULL;
}

}