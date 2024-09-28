#include "stdafx.h"

#include "Network/Network.h"
#include "Network/Transport.h"
#include "Server/ZZima/ZZimaService.h"
#include "ZZimaLoginProcessor.h"
#include "System/StrUtils.h"
#include "System/sleep.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UGLY: лог-каналы (пока не хочется тащить в log-header'ы с ребилдом всего)

namespace Login {

static int g_ZZima_Worker_Threads = 8; // количество рабочих ниток в пуле ZZima-логина
REGISTER_VAR( "login_zzima_worker_threads", g_ZZima_Worker_Threads, STORAGE_NONE );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ZZimaLoginProcessor::ZZimaLoginProcessor( const ConnectionInfo& connectionInfo_ ) :
ServerLoginProcessorBase(),
connectionInfo( connectionInfo_ )
{
  // заводим worker threads
  for( int i=0; i<max(1, g_ZZima_Worker_Threads); i++ )
  {
    ZZimaWorkerThread* thread = new ZZimaWorkerThread( (IRequestQueue*)this, connectionInfo_ );
    if( thread )
    {
      threads[ thread->Id() ] = thread; // если что, можно будет найти "виноватый" thread по id и прибить (and/or spawn new)
      thread->Resume(); // побежали
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ZZimaLoginProcessor::~ZZimaLoginProcessor()
{ 
  // сделать что-нибудь такое graceful с нашим thread pool? ...да ну, сами помрут
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ZZimaWorkerThread::ZZimaWorkerThread( IRequestQueue* requestSource_, const ConnectionInfo& connectionInfo )
  : threading::AutostopThread()
  , requestSource( requestSource_ )
{
  NI_ASSERT( requestSource, "ZZimaWorkerThread: bad request source" );

  // машинерия для выполнения web-XML (раньше жила в едином zzima login processor)
  invoker = new ZZima::Invoker(connectionInfo.authServer.c_str(), connectionInfo.serviceName.c_str(), connectionInfo.servicePassword.c_str(), false);
  invokerOld = new ZZima::InvokerOld(connectionInfo.socNetServer.c_str(), connectionInfo.socNetKey.c_str(), connectionInfo.socNetSecret.c_str());
  authAutoSubscribe = connectionInfo.authAutoSubscribe;
  authStats.Reset();
  socnetStats.Reset();

  if (!invoker->IsOk())
    LOG_C( 0 ) << "ZZimaWorkerThread: Invoker is not OK!" << endl;

  // здесь логаем в global, потому что канал ZZima создается вместе с Login (и вместе с LoginServer*, на шаг позже нас)
  LOG_M( 0 ).Trace("ZZima auth \"%s\" \"%s\" \"%s\" %d", connectionInfo.authServer.c_str(), connectionInfo.serviceName.c_str(), connectionInfo.servicePassword.c_str(), connectionInfo.authAutoSubscribe);
  LOG_M( 0 ).Trace("ZZima socnet \"%s\" \"%s\" \"%s\"", connectionInfo.socNetServer.c_str(), connectionInfo.socNetKey.c_str(), connectionInfo.socNetSecret.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ZZimaWorkerThread::~ZZimaWorkerThread()
{
  SAFE_DELETE(invoker);
  SAFE_DELETE(invokerOld);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned ZZimaWorkerThread::Work()
{
  char buf[64];
  NStr::Printf( buf, sizeof(buf), "ZZimaWorkerThread_%d", Id() ); 
  threading::SetDebugThreadName( buf );

  while( isRunning )
  {
    SZZimaLoginRequest* request = requestSource->GetNextRequest( Id() );
    if( request )
    {
      bool success = false;
      try {
        if ( PerformSynchroLogin( request->login, request->password, request->context->resultData ) > 0 )
          request->context->response.loginResult = ELoginResult::AsyncSuccess;
      }
      catch(...) { // в случае любых ошибок, надо все равно вернуть наружу результат (типа "unknown fail")
        LOG_A( LOGIN_CHNL ) << "web login EXCEPTION, login=" << request->login;
      }
      request->context->isLoginChecked = true; // снаружи SynchroLogin, когда все изменения resultData уже финализированы
      request->status = SZZimaLoginRequest::READY; 
    }
    else
      nival::sleep( 10 );
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ZZimaWorkerThread::PerformSynchroLogin( const string & login, const string & _password, Login::LoginResultData & result )
{
  int userId = -1;
  if (!invoker->IsOk())
  {
    LOG_E( LOGIN_CHNL ) << "Invoker is not OK!" << endl;
    return userId;
  }
  int authTime;
  int socnetTime;
  ZZima::ErrorCode code = ZZima::E_OK;

  authStats.Start();
  if (authAutoSubscribe)
  {
    code = ZZima::SubscribeService(*invoker, login.c_str(), invoker->GetServiceName());
    if (ZZima::E_OK == code)
    {
      LOG_M( LOGIN_CHNL ).Trace("user %s subscribed successfully", login.c_str());
    }
    else
    if (ZZima::E_ALREADY_SUBSCRIBED == code)
    {
      LOG_M( LOGIN_CHNL ).Trace("user %s already subscribed", login.c_str());
    }
  }
  if (code == ZZima::E_OK || code == ZZima::E_ALREADY_SUBSCRIBED)
  {
    if( result.nUserID == 0 ) // ненулевой nUserID == признак SessionLogin
    {// авторизуем только при нулевом nUserID (при ненулевом подразумеваем SessionLogin)
      code = ZZima::Authorize(*invoker, login.c_str(), _password.c_str(), userId);
    }
    else
    {
      LOG_M( LOGIN_CHNL ).Trace("skipping ZZima::Authorize for user %s: nUserID=%d (must be ServiceLogin)", login.c_str(), result.nUserID);
      code = ZZima::E_OK; // уже прошли SessionLogin, не надо лезть в ZZima authorize
      userId = result.nUserID;
    }
  } else
  {
    LOG_M( LOGIN_CHNL ).Trace("subscribe user %s to service failed, error: %s", login.c_str(), ZZima::GetErrorText(code));
  }
  authTime = NHPTimer::Time2Milliseconds(authStats.Stop());

  socnetStats.Start();
  if (ZZima::E_OK == code)
  {
    char buffer[64];
#if defined( NV_WIN_PLATFORM )
    _itoa_s(userId, buffer, 64, 10);
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buffer, 64, "%d", userId );
#endif
    ZZima::UserInfo info;
    code = ZZima::GetUserInfo(*invokerOld, std::string(buffer), info);
    if (ZZima::E_OK == code)
    {
      //We dont wanna zzima auth anymore
      //Antire ZZima-auth mechamizm should be removed
      //result.gender = info.sex;
    }
    else
    {
      LOG_E( LOGIN_CHNL ).Trace("can't get user info (user=%s code=%d text=%s)", 
        login.c_str(), (int)code, ZZima::GetErrorText(code));
    }
    LOG_M( LOGIN_CHNL ).Trace("user authorized (login=%s zzima authorise id=%d)", login.c_str(), userId );
  }
  else
  {
    LOG_M( LOGIN_CHNL ).Trace("user authorization failed (user=%s code=%d text='%s').", 
      login.c_str(), (int)code, ZZima::GetErrorText(code));
  }
  socnetTime = NHPTimer::Time2Milliseconds(socnetStats.Stop());

  if( result.nUserID == 0 ) // ненулевой nUserID == признак того, что трогать его не надо (SessionLogin)
    result.nUserID = userId;

  result.nErrorCode = int(code);
  //result.sErrorString = ZZima::GetErrorText(code);
  result.username = NStr::ToUnicode( login );
  LOG_D( LOGIN_CHNL ).Trace("authTime:%d socnetTime:%d", authTime, socnetTime); 
  return result.nUserID;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SZZimaLoginRequest::SZZimaLoginRequest( string const & login_, string const & pwd_, const StrongMT<Login::SLoginContext> & context_ )
  : login( login_ )
  , password( pwd_ )
  , context( context_ )
  , status( Login::SZZimaLoginRequest::NEW )
{}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ZZimaLoginProcessor::AsyncLoginRequest( string const & login, string const & pwd, const StrongMT<Login::SLoginContext> & context )
{// добавляем заявку в requests
  threading::MutexLock lock( mutexRequests );
  SZZimaLoginRequest *request = new SZZimaLoginRequest( login, pwd, context );
  if( request )
    requests.push_back( request );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ZZimaLoginProcessor::AsyncStep()
{
  // здесь будем удалять заявки из очереди (пусть это будет синхронный момент: 
  //  именно здесь могут удаляться неотработанные context-ы, для которых например web-операция завершилась рассыпанием или timeout)
  threading::MutexLock lock( mutexRequests );

  // выкидываем из очереди обработанные запросы
  for ( TWebLoginRequests::iterator it = requests.begin(); it != requests.end(); )
  {
    SZZimaLoginRequest *request = *it;

    // только здесь будем "забывать context" на уже исполненных заявках (что, в принципе, может привести к удалению context) 
    //  чтобы исключить какие-либо проблемы с асинхронностью удаления login-context'ов
    if ( request->status == SZZimaLoginRequest::READY )
    {
      request->context = 0; // сразу отвязываемся от логин-контекста, можете его удалять
      request->status = SZZimaLoginRequest::ERASED; // для дебаггера, в случае чего

      delete request;
      it = requests.erase( it );
    }
    else
      ++it;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ZZimaLoginProcessor::PerformLoginCheck( string const &, string const &, Network::IConnection *, Login::LoginResultData * result )
{
  // связываемся асинхронно, поэтому только добавляем себе таск, и сразу же возвращаем error code "ждите ответа"
  result->nErrorCode = ZZima::E_ASYNC_WAIT;
  return false;
}

SZZimaLoginRequest* ZZimaLoginProcessor::GetNextRequest( unsigned getterId )
{
  threading::MutexLock lock( mutexRequests );

  // берем следующий необработанный request из очереди; 
  //  сразу ставим туда threadId и status=TAKEN
  for ( TWebLoginRequests::iterator it = requests.begin(); it != requests.end(); ++it )
    if ( (*it)->status == SZZimaLoginRequest::NEW )
    {
      (*it)->status = SZZimaLoginRequest::TAKEN;
      (*it)->workerId = getterId;
      return (*it);
    }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Login
