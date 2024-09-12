#pragma once

#include <Server/RPC/LocalEntityFactory.h>
#include <Server/RPC/P2PNode.h>

#include "HybridServer/PeeredImpl.h"
#include "HybridServer/RPeered.auto.h"
#include "HybridServer/LPeered.auto.h"
#include "Client/Lobby/HybridServerNodeImpl.h"
#include "RSessionConnector.auto.h"

namespace rpc
{
struct P2PNode;
} // rpc

#pragma warning(disable:4482)
enum ConnectionStage
{
  Disabled,
  RequestSent,
  SessionRecieved,  
  SchedulerRecieved,
  ConnectionFinished
};

class ServerNodeHelper
{
  DUMMY_ASSIGNMENT(ServerNodeHelper);
public:
  ServerNodeHelper( Transport::IChannel * _channel, rpc::Gate * _gate, rpc::P2PNode* _node) :
  gate( _gate ),
  clientId(10000),
  factory( _gate ),
  stage(Disabled),
  channel(_channel),
  node(_node)
  {
    thread = new threading::ProcessingThread<ServerNodeHelper>( *this, true );
    //factory.RegisterAttach<Peered::IGameClient, Peered::LIGameClient>();
  }

  ~ServerNodeHelper()
  {
    thread->Stop(true);
    delete thread;
    //delete node;
  }

  StrongMT<NCore::ServerNode> GetStrong()
  {
    if (stage == ConnectionStage::ConnectionFinished)
    {
      return client;
    } 
    event.Wait();
    return client;
  }

  NCore::IServerNode* Get()
  {
    if (stage == ConnectionStage::ConnectionFinished)
    {
      return client.Get();
    } 
    event.Wait();
    return client.Get();
  }

  int Process(const bool& isRunning)
  {
    while (channel->GetStatus() == Network::ConnectionState::Connecting)
    {
      Sleep( 5 );
    }
    if (channel->GetStatus() == Network::ConnectionState::Connected)
    {
      printf("Connected to server\n");
      rpc::SPtrValue<Peered::RSessionConnector> session;
      node->node->Query<Peered::RSessionConnector>("connector", &session, &rpc::SPtrValue<Peered::RSessionConnector>::onCall);
      stage = ConnectionStage::RequestSent;
      rpc::SPtrValue<Peered::RIGameServer> scheduler;
      while (stage != ConnectionStage::ConnectionFinished && channel->GetStatus() == Network::ConnectionState::Connected) 
      {
        if (stage == ConnectionStage::RequestSent)
        {
          if (session.IsSet())
          {
            if (session.result)
            {
              printf("Session connector acquired\n");
              session.result->Connect(&scheduler, &rpc::SPtrValue<Peered::RIGameServer>::onCall);
              stage = ConnectionStage::SessionRecieved;
            } else                                         
            {
              printf("Session connector not acquired, FAIL\n");
              stage = ConnectionStage::ConnectionFinished;
            }
          }
        } else
        if (stage == ConnectionStage::SessionRecieved)
        {
          if (scheduler.IsSet())
          {
            if (scheduler.result)
            {
              printf("Commands scheduler acquired\n");
              client = new NCore::ServerNode(scheduler.result.Get());
              scheduler.result->AddClient("redjack", clientId, client.Get());
              stage = ConnectionStage::SchedulerRecieved;
            }
            else
            {
              printf("Commands scheduler not acquired, FAIL\n");
              stage = ConnectionStage::ConnectionFinished;
            }
          }
        } else
        if (stage == ConnectionStage::SchedulerRecieved)
        {
          if (client->IsStarted())
          {
            stage = ConnectionStage::ConnectionFinished;
          }
        }
        node->Poll();
      }

      if (channel->GetStatus() != Network::ConnectionState::Connected)
      {
        stage = ConnectionStage::ConnectionFinished;
        printf("Server dropped\n");
      }

    }
    else
    {
      stage = ConnectionStage::ConnectionFinished;
      printf("Server aborted, exit\n");
    }

    event.Set();
    return 0;
  }

  bool IsConnected() { return channel->GetStatus() == Network::ConnectionState::Connected; }
private:
  threading::ProcessingThread<ServerNodeHelper>* thread;
  StrongMT<Transport::IChannel> channel;
  WeakMT<rpc::Gate> gate;
  threading::Event event;
  StrongMT<NCore::ServerNode> client;
  int clientId;
  rpc::P2PNode* node;
  rpc::LocalEntityFactory factory;
  ConnectionStage stage;
};
