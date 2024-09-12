#include "stdafx.h"

#include "Network/Network.h"
#include "Network/Transport.h"
#include "Server/AppFramework/Interfaces.h"
#include "Coordinator/LoginProcessorBase.h"

#include "System/ThreadHelpers.h"

namespace ZZima
{
struct Invoker;
class InvokerOld;
}

namespace Login {
  
// заявка для thread-pool очереди
struct SZZimaLoginRequest
{
  enum TStatus {
    NEW = 0,
    TAKEN, // забрали и начали исполнять over web
    READY, // web-запрос готов
    ERASED // обработан, и даже по идее удален (debug)
  };
  TStatus status; 
  unsigned int workerId; // id worker thread, который забрал нашу заявку на исполнение
  string login;
  string password;
  // weak ссылка: пусть себе удаляется, нам понадобится только context->result для вписывания ответа (if still alive)
  StrongMT<Login::SLoginContext> context; 
  Login::LoginResultData resultData;

  SZZimaLoginRequest( string const & login_, string const & pwd_, const StrongMT<Login::SLoginContext> & context_ );
};

typedef nstl::vector<SZZimaLoginRequest*> TWebLoginRequests;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// через этот интерфейс worker threads будут забирать заявки из ZZimaLoginProcessor::requests[]
struct IRequestQueue
{
  virtual SZZimaLoginRequest* GetNextRequest( unsigned getterId ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ConnectionInfo
{
  string authServer;
  string serviceName;
  string servicePassword;
  string socNetServer;
  string socNetKey;
  string socNetSecret;
  bool authAutoSubscribe;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// worker thread:
// - забирает заявку из requests 
// - исполняет PerformSynchroLogin( request )
// ! всегда готовы к тому, что worker прибьется по timeout
class ZZimaWorkerThread: public threading::AutostopThread // Thread и так NonCopyable
{
  IRequestQueue* requestSource;

public:
  ZZimaWorkerThread( IRequestQueue* requestSource_, const ConnectionInfo& connectionInfo );
  virtual ~ZZimaWorkerThread();

protected:
  virtual unsigned Work();
  int PerformSynchroLogin( const string & login, const string & _password, Login::LoginResultData & result );

private:
  // машинерия для выполнения web-XML: (раньше жила в едином zzima login processor)
  ZZima::Invoker* invoker;
  ZZima::InvokerOld* invokerOld;
  bool authAutoSubscribe;
  AppFramework::InstanceStatistics authStats;
  AppFramework::InstanceStatistics socnetStats;
};

typedef nstl::map<int, ZZimaWorkerThread*> TZZimaWorkerThreads;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ZZimaLoginProcessor : public Login::ServerLoginProcessorBase, public IRequestQueue
{
  ZZimaLoginProcessor( const ConnectionInfo& connectionInfo );
  virtual ~ZZimaLoginProcessor();

protected:
  // ILoginProcessor
  virtual bool PerformLoginCheck( string const &login, string const &password, Network::IConnection *connection, Login::LoginResultData* result );
  virtual void AsyncLoginRequest( string const & login, string const & pwd, const StrongMT<Login::SLoginContext> & context );
  virtual void AsyncStep(); // здесь финализируем запросы, выкидываем исполненные, сигналим таймауты, и т.п.

  // IRequestQueue:
  SZZimaLoginRequest* GetNextRequest( unsigned getterId ); 

private:
  ConnectionInfo connectionInfo; // если захотим respawn'ить worker threads, им надо будет подпихивать это info
  TZZimaWorkerThreads threads;

  threading::Mutex mutexRequests;
  TWebLoginRequests requests; // заявки на web-логин (обращения к ZZima), сюда будут ломиться worker threads
};

} // namespace Login