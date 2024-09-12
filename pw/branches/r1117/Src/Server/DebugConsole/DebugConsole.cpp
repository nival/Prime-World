#include "stdafx.h"
#include <conio.h>

#include <Server/Network/Initializer.h>
#include <Server/Network/Transport.h>
#include <Server/Network/TransportInitializer.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/ClientTransportSystem.h>
#include <Server/Network/ClientTransportSystem2.h>
#include <Server/Network/AddressTranslator.h>
#include <HybridServer/LPeered.auto.h>
#include <transport/TLTransportModule.h>
#include <Core/Scheduler.h>
#include "Coordinator/LCoordinatorServerIface.auto.h"
#include "DebugConsole.h"

namespace DebugConsole
{
  Client::Client()
    :localid_(0),
    userid_(0),
    stage_(Stage::NONE),
    lastresult_(Result::NONE),
    lastPing_(0),
    bexit_(false)
  {
    pingInterval_ = 10*60000;
  }

  // для нового транспорта (серверного, через CoordinatorClient)
  Client::Client( int localId, 
      StrongMT<Transport::ITransportSystem> transport, 
      StrongMT<Coordinator::CoordinatorClient> coord,
      const NDebug::DebugVarRequesterMap::TScenarioVars& vars_vector,
      const char * service_name ) 
  : localid_(localId),
    userid_(0),
    stage_(Stage::NONE),
    lastresult_(Result::NONE),
    lastPing_(0),
    bexit_(false),
    need_stage_reset_(true),
    coordClient_(coord),
    transportCluster_(transport),
    varService_(service_name)
  {
    gateKeeperCluster_ = new rpc::GateKeeper( transportCluster_, "", Transport::autoAssignClientId );
    varRequester_.AddScenarios( vars_vector );
  }

  Client::~Client()
  {
    gateKeeper_ = 0;
    transport_ = 0;
  }

  void Client::OnNewNode( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node )
  {
  }

  void Client::OnChannelClosed( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node )
  {
    bexit_ = true;
  }

  void Client::OnCorruptData( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node )
  {
    bexit_ = true;
  }

  void Client::OnSetVarReporter(NDebug::RDebugVarReporter* mr)
  {
    mr->GetDebugVar( L"ServerSide_var", this, &Client::OnGetDebugVar );
  }

  void Client::OnGetDebugVar(const wchar_t *ws)
  {
  }

  void ConsoleCmdHelp()
  {
    printf( 
      "\n========================================================================================================="
      "\nSupported commands:"
      "\n  !service_name      -- connect to specified 'service.var' reporter (inside cluster)"
      "\n  !!service!ip:port  -- connect to specified ip:port reporter (any outside-cluster IP, statistic server)"
      "\n  +var_name:period   -- add specified var_name to request list (period=0 to update once)" 
      "\n  -var_name          -- remove specified var_name from request list" 
      "\n  --                 -- remove all vars from request list" 
      "\n  /cmd_line          -- add remote command to request list (REGISTER_CMD, config commands etc.)"
      "\n  //cmd_line         -- run remote command immediately (REGISTER_CMD, config commands etc.)"
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

  void Client::PrintCompletions()
  {
    string listServices = "<this feature was cut off>";
    printf ( "\nActive services: ", listServices.c_str() );

    wstring listVars;
    varRequester_.ListScenarios( listVars );
    printf ( "\nCurrent vars: %ls", listVars.c_str() );
  }

  bool Client::StepVarUpdate_Cluster()
  {
    //Transport::TServiceId serviceId( "chatx" );
    switch(stage_)
    {
    case Stage::NONE:
      {
        if( !varImmediateIP_.empty() && coordClient_ )
        {// грязными руками добавляем в routeMap указанный внешний адрес
          coordClient_->RemoveRoute( varService_ ); // на случай если такой сервис уже был (мало ли сколько у нас этих кластеров и статистик-серверов)
          coordClient_->AddRoute( varService_, varImmediateIP_ );
        }
        
        rpc::Node* rpcNode = gateKeeperCluster_->RequestNode( varService_ );
        if ( rpcNode )
        {
          Transport::TServiceId serviceId ( varService_ );
          serviceId += NDebug::VarPathSuffix;
          varRequester_.RemoveRequester( 1 );
          varRequester_.QueryRequester( 1, rpcNode, serviceId );
          stage_ = Stage::LOOP;
        }
        else
        {
          printf( "service name not found (%s), please set valid name with '!service_name' command", varService_.c_str() );
          stage_ = Stage::INPUT; // stop looping, and wait for keypress
          NextInput(); 
        }
      }
      break;

    case Stage::LOOP:
      varRequester_.UpdateStep();
      gateKeeperCluster_->Poll();
      Sleep( 100 ); // max. 10 steps per sec

      if ( _kbhit() )
      {
        getch(); // no echo: on any keystroke just stop & go to INPUT mode
        stage_ = Stage::INPUT; // stop looping, and wait for keypress
        need_stage_reset_ = false; // если не будет изменений сервиса/переменных, продолжим loop со старым requester'ом
        ConsoleCmdHelp();
        PrintCompletions();
        NextInput(); 
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
                printf("\nQUIT: stopping application...\n");
                return false;

              case '/':
                {
                  string cmd = input_.substr(1);
                  if ( cmd.length() && cmd[0] == '/' )
                  {// если начинается с двух слэшей, запускаем исполнение сразу
                    cmd = cmd.substr(1);
                    printf("\n//: run remote cmd (IMMEDIATE)");
                    stage_ = Stage::LOOP;
                  }
                  else
                    printf("\n/: run remote cmd");

                  wchar_t buf[256];
                  NStr::ToWString<char const*>( cmd.c_str(), buf, 256 );

                  // ну нафиг, не надо пихать одноразовые команды в "общий сценарий" varRequester_.AddScenario( buf, -1 );
                  varRequester_.AddImmediate( 1, buf ); // Immediate не будет добавлять в общий сценарий, только в один реквестер 
                }
                break;

              case '+':
                {
                  printf("\n+: add var");
                  NDebug::SScenarioVar svar;
                  string pair = input_.substr(1);
                  if ( svar.Parse( pair ) )
                  {
                    varRequester_.AddScenario( svar.wsName, svar.updPeriod );
                    need_stage_reset_ = true;
                  }
                  else
                    printf("\nformat should be 'var_name<string>:update_period_seconds<float>', ex. 'var1:0', 'var2:5.0'");
                }
                break;

              case '-':
                if ( input_.length() == 2 && input_[1] == '-' )
                {// "--"
                  printf("\n--: remove ALL vars");
                  varRequester_.ClearScenarios();
                  need_stage_reset_ = true;
                }
                else
                {
                  printf("\n-: remove var");
                  wchar_t buf[256];
                  NStr::ToWString<char const*>( input_.substr(1).c_str(), buf, 256 );
                  if ( varRequester_.RemoveScenario( buf ) )
                  {
                    printf("\nvar removed");
                    need_stage_reset_ = true;
                  }
                  else
                    printf("\nno such var");
                }
                break;

              case '!':
                if ( input_.length() >= 2 && input_[1] == '!' )
                {// "!!", !!service!addr:port
                  string line = input_.substr( 2 );
                  vector<string> words;
                  NStr::SplitString( line, &words, "!" );
                  if( words.size() == 2 )
                  {
                    varService_ = Transport::TServiceId( words[0].c_str() );
                    varImmediateIP_ = words[1];
                    printf("\n!!: switch target to service '%s', direct addr '%s'", varService_.c_str(), varImmediateIP_.c_str() );
                    need_stage_reset_ = true;
                    stage_ = Stage::NONE; // run IMMEDIATE
                  }
                  else
                  {
                    printf("\nformat should be '!!service_name!ip:port', ex. '!!stat!192.168.0.1:40002'");
                  }
                }
                else
                {
                  varService_ = Transport::TServiceId( input_.substr( 1 ).c_str() );
                  varImmediateIP_.clear();
                  printf("\n!: switch target service to '%s'", varService_.c_str() );
                  need_stage_reset_ = true;
                  stage_ = Stage::NONE; // run IMMEDIATE
                }
                break;


              default:
                ConsoleCmdHelp();
                break;
              }
              NextInput(); 
            }
            else
            {// просто ENTER: возобновляем работу цикла
              printf( "\nENTER: resume operation...\n" );
              stage_ =  need_stage_reset_ ? Stage::NONE : Stage::LOOP;
            }
          }
        }
      }
      break;
    }

    return true;
  }
} // namespace DebugConsole
