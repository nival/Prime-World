#include "stdafx.h"

#include <conio.h> 

#include "System/StdOutDumper.h"

#include <Network/Network.h>
#include <Network/Initializer.h>
#include <Network/StreamAllocator.h>
#include "System/ThreadHelpers.h"
#include "System/FileUtils.h"
#include "System/ProfileManager.h"
#include "System/ConfigFiles.h"

struct TestServerThread
{
  CObj<Network::INetworkDriver> netDriver;
  int delay;
  nstl::string listenAddr;

  int messagesSent;
  int messagesReceived;

  int Process( const bool& isRunning )
  {
    vector<CObj<Network::IConnection>> connections;
    connections.reserve( 1000 );
    messagesSent = 0;
    messagesReceived = 0;

    CObj<Network::IConnectionsManager> listener = netDriver->CreateConnectionListener( listenAddr, false);

    while( isRunning )
    {
      vector<CPtr<Network::IConnection>> newConnections;
      listener->GetNewConnections( newConnections );

      for( int i = 0; i < newConnections.size(); ++i )
      {
        connections.push_back( newConnections[i] );
      }

      for( int i = 0; i < connections.size(); ++i )
      {
        int maxReceives = 20;
        while (--maxReceives > 0 )
        {
          CObj<Stream> pMsg = connections[i]->Receive();
          if ( !pMsg )
            break;

          CObj<Network::IConnection> pconn = connections[i];
          nstl::string sin;
          pMsg->ReadString(sin);
          if (sin == "CLOSE")
          {
            pconn->AsyncClose();
          }
          else
          {
            CObj<Stream> ostrm = pconn->GetBufferToSend();
            pMsg->Seek(0, SEEKORIGIN_BEGIN);
            ostrm->CopyFrom(pMsg);
            pconn->ReleaseReceived(pMsg);
            connections[i]->Send(ostrm);
          }
        }
      }

      Sleep( delay );
    }

    return 0;
  }
};

int main(int argc, const char argv[])
{      
  NLogg::CStdOutDumper g_stdoutDumper( &GetSystemLog());
  GetSystemLog().SetFileAndLevel(NLogg::LEVEL_DEBUG, "server.old.log", 0xFFFFFFFF);

  TestServerThread procs;
  procs.netDriver = Network::Initialize();
  procs.netDriver->SetStreamAllocator( new Network::StreamAllocator() );
  procs.delay = 10;
  procs.listenAddr = "localhost:35001";

  threading::ProcessingThread<TestServerThread> testThread( procs, true );

  int ch = 0;
  while ((ch = _getch()) != 'Q');

  testThread.Stop( true, 5000 );

  return 0;
}

