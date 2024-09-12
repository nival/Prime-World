#include "stdafx.h"
#include <conio.h>

#include <Server/Network/Initializer.h>
#include <Server/Network/Transport.h>
#include <Server/Network/TransportInitializer.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/ClientTransportSystem2.h>
#include <Server/Network/AddressTranslator.h>
#include <transport/TLTransportModule.h>

#include "AdminConsole.h"

const int CLUSTER_CONNECT_TIMEOUT_SECONDS = 10; 

namespace AdminConsole
{
  Client::Client()
    : stage_(Stage::NONE)
    , lastresult_(Result::NONE)
    , transport_(0)
    , gateKeeper_(0)
    , factory_(0)
    , clusterAdmin(0)
    , rpcNode_(0)
    , bexit_(false)
  {
  }

  // для нового транспорта (серверного, через CoordinatorClient)
  Client::Client( int localId, 
      StrongMT<Transport::ITransportSystem> transport, 
      nstl::string loginAddr ) 
    : stage_(Stage::NONE)
    , lastresult_(Result::NONE)
    , transport_(transport)
    , gateKeeper_(0)
    , factory_(0)
    , clusterAdmin(0)
    , rpcNode_(0)
    , bexit_(false)
    , need_stage_reset_(true)
    , loginAddr_(loginAddr)
  {
    gateKeeper_ = new rpc::GateKeeper( transport_, "", Transport::autoAssignClientId, this );
  }

  Client::~Client()
  {
    SAFE_DELETE(factory_)
    gateKeeper_ = 0;
    transport_ = 0;
    rpcNode_ = 0;
  }

  void Client::OnNewNode( Transport::IChannel* channel,  rpc::Node* node )
  {
  }

  void Client::OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node )
  {
    clusterAdmin = 0; // канал у нас один, так что любой разрыв связи -- повод для реконнекта
    printf("\n");
    LOG_W(0) << "DISCONNECTED from ClusterAdmin";
  }

  void Client::OnCorruptData( Transport::IChannel* channel, rpc::Node* node )
  {
  }

  
  void ConsoleCmdHelp()
  {
    printf( 
      "\n========================================================================================================="
      "\nSupported commands:"
      "\n  list               -- TODO: list cluster services"
      "\n  start              -- TODO: start all services"
      "\n  shutdown           -- shutdown all services"
      "\n  q                  -- quit application"
      "\n  <Enter>(no input)  -- resume request loop"
      "\n  any other input    -- this help screen" 
      "\n=========================================================================================================");
  }

  void Client::NextInput()
  {
    input_ = "";
    printf ("\nCMD >");
  }

  void Client::NoConnectWarning()
  {
    printf("\n");
    LOG_W(0) << "NOT CONNECTED to ClusterAdmin";
    rpcNode_ = 0;
    clusterAdmin = 0;
  }

  void Client::PrintCompletions()
  {
    string listServices = "TODO";
    printf ( "\nActive services: %s", listServices.c_str() );

    if( !clusterAdmin )
    {
      NoConnectWarning();
    }
  }

  void Client::OnClusterAdminPtr( ClusterAdmin::RIClusterAdmin* ptr )
  {
    clusterAdmin = ptr;
    printf("\n");
    if( ptr )
      LOG_M(0) << "Connected to ClusterAdmin: ptr=" << ptr;
    else
      LOG_W(0) << "CANNOT CONNECT to ClusterAdmin, received ptr=" << ptr;
    rpcNode_ = 0;

    SwitchToInput();
  }

  void Client::SwitchToInput()
  {
    need_stage_reset_ = false; 
    stage_ = Stage::INPUT; // stop looping, and wait for keypress
    ConsoleCmdHelp();
    PrintCompletions();
    NextInput(); 
  }
  
  bool Client::StepVarUpdate_Cluster()
  {
    gateKeeper_->Poll();

    if( rpcNode_ && (GetTime() - timeConnectStarted_ > CLUSTER_CONNECT_TIMEOUT_SECONDS) )
      NoConnectWarning();

    switch(stage_)
    {
    case Stage::NONE:
      {
        rpcNode_ = gateKeeper_->RequestNode( ClusterAdmin::ServiceInterfaceId ); // честно говоря, пофиг; все равно у нас dummy resolver
        if ( rpcNode_ )
        {
          rpcNode_->Query<ClusterAdmin::RIClusterAdmin>( ClusterAdmin::RpcServiceInterfaceId, this, &Client::OnClusterAdminPtr); 
          timeConnectStarted_ = GetTime();
        }
        else
        {
          LOG_A(0) << "CLUSTER ADMIN node not found, please set valid logon address:port";
          NextInput();
        }
        stage_ = Stage::LOOP; 
      }
      break;

    case Stage::LOOP:
      if ( _kbhit() )
      {
        getch(); // no echo: on any keystroke just stop & go to INPUT mode
        SwitchToInput();
      }
      break;

    case Stage::INPUT: 
      {
        char buf[2] = ""; // для сравнения с множеством допустимых символов (пунктуация и т.п.)
        if( _kbhit() )
        {
          char c = getch();
          if ( c == 0 || ((unsigned char)c) == 0xE0 ) // escape codes, skip next char
          {
            getch();
            break;
          }
          else if ( c == VK_ESCAPE ) // ESC -- cancel, очистим строчку и перейдем на следующую
          {
            NextInput(); 
            break;
          }
          else if ( c == VK_BACK ) // BACKSPACE, прибить пред.символ
          {
            if( input_.length() )
            {
              input_.erase( input_.length()-1 );
              putch(c);
              putch(' '); // стираем букву и на экране консоли (OMGWTF cant believe I'm writing this sh*(*$*^%$ -- in 21st century!)
              putch(c);
              break;
            }
          }

          if ( c != '\r' ) 
          {// accept & echo printable chars (latin alpha-num, and a few others (+- и т.п.)
            buf[0] = c;
            if (  ( c >= 'a' && c <= 'z' ) || 
                  ( c >= 'A' && c <= 'Z' ) ||
                  ( c >= '0' && c <= '9' ) ||
                  ( strcspn( buf, "_.+-!:/ =" ) == 0 )
               )
            {
              putch( c );
              input_ += c;
            }
          }
          else
          {
            if ( input_.length() )
            {
              switch ( input_[0] )
              {
              case 'q':
                if( "q" == input_ || "quit" == input_ )
                {
                  printf("\nQUIT: stopping application...\n");
                  return false;
                }

              default:
                if( HandleInput() )
                  return true;

                // не смогли обработать команду: 
                ConsoleCmdHelp();
                break;
              }
              NextInput(); 
            }
            else
            {// просто ENTER: возобновляем работу цикла
              printf( "\nENTER: resume operation...\n" );
              stage_ =  need_stage_reset_ || (!clusterAdmin) ? Stage::NONE : Stage::LOOP;
            }
          }
        }
      }
      break;
    }

    return true;
  }


  bool Client::HandleInput()
  {
    bool res = false;

    if( clusterAdmin )
    {
      if( "list" == input_ )
      {
        // TODO
        res = true;
      }
      else if( "shutdown" == input_ )
      {
        clusterAdmin->Shutdown( 1 );
        res = true;
      }
      else if( "start" == input_ )
      {
        // TODO
        res = true;
      }

      NextInput();
    }
    else
    {
      NoConnectWarning();
      need_stage_reset_ = true;
    }

    return res;
  }

} // namespace AdminConsole
