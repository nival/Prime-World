#include "stdafx.h"
#include "LoginServerBase.h"
#ifdef NV_WIN_PLATFORM
#include <comutil.h>
#endif
#include "LoginCompatibleClientVersion.h"

namespace Login
{

static unsigned int g_MajorClientVersion = LOGIN_COMPATIBLE_MAJOR_CLIENT_VERSION;
static unsigned int g_MinorClientVersion = LOGIN_COMPATIBLE_MINOR_CLIENT_VERSION;
static unsigned int g_PatchClientVersion = 0;
static unsigned int g_RevisionClientVersion = 0;
static bool         g_AcceptDevClientVersion = true;
static bool         g_StrictClientVersionCheck = false;

REGISTER_VAR( "login_major_client_version", g_MajorClientVersion, STORAGE_NONE );
REGISTER_VAR( "login_minor_client_version", g_MinorClientVersion, STORAGE_NONE );
REGISTER_VAR( "login_patch_client_version", g_PatchClientVersion, STORAGE_NONE );
REGISTER_VAR( "login_revision_client_version", g_RevisionClientVersion, STORAGE_NONE );
REGISTER_VAR( "login_accept_dev_version", g_AcceptDevClientVersion, STORAGE_NONE );
REGISTER_VAR( "login_client_version_strict_check", g_StrictClientVersionCheck, STORAGE_NONE );




LoginServerBase::LoginServerBase( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams, const Network::NetAddress& _loginServerAddress ) :
Transport::BaseService( _svcParams, _customParams ),
handler( _svcParams.driver, _loginServerAddress )
{
  LOG_M( LOGIN_CHNL ) << "Starting Login server, listening on " << _loginServerAddress;

  compatibleClientVersion.major_ = static_cast<ushort>(g_MajorClientVersion);
  compatibleClientVersion.minor_ = static_cast<ushort>(g_MinorClientVersion);
  compatibleClientVersion.patch_ = g_PatchClientVersion;
  compatibleClientVersion.revision_ = g_RevisionClientVersion;
}



ELoginResult::Enum LoginServerBase::checkClientVersion(Login::ClientVersion const & cv)
{
  if (g_AcceptDevClientVersion && cv.isEmpty())
    return ELoginResult::Success;

  int compatible = 0;
  if (g_StrictClientVersionCheck)
    compatible = compatibleClientVersion.compare(cv);
  else
    compatible = compatibleClientVersion.checkCompatibility(cv);

  ELoginResult::Enum res = ELoginResult::Success;
  if (compatible > 0)
    res = ELoginResult::ServerOutdated;
  else
  if (compatible < 0)
    res = ELoginResult::ClientOutdated;

  return res;
}



void LoginServerBase::SendReply( SLoginContext * context )
{
  LoginRequestMessage & req = context->request;
  LoginResultMessage & resp = context->response;

  if ( ELoginResult::Success == resp.loginResult )
  {
    ::GUID guid;
    ::CoCreateGuid( &guid );
    NStr::GUID2String( &resp.sessionId, guid );

    OnNewLoginSuccess( resp ); // синхронный Login здесь может отправить свой ILoginProcessor::NewClientLoggedIn()

    AutoPerfCounterRate( "users_inc_login_succ", 1 );

    LOG_M( LOGIN_CHNL ) << "user " << req.login << "/" << resp.userId 
      << " logged in. Client version " << 
      req.majorVer << "." << 
      req.minorVer << "." << 
      req.patchVer << "." << 
      req.revisionVer << endl;
  }
  else
  {
    LOG_W( LOGIN_CHNL ) << "user("<< req.login << ") login FAILED. " 
      << ELoginResult::ToString( resp.loginResult ) 
      << ". Client version "
      << req.majorVer << "."
      << req.minorVer << "."
      << req.patchVer << "."
      << req.revisionVer << endl;

    if (ELoginResult::ServerOutdated == resp.loginResult ||
        ELoginResult::ClientOutdated == resp.loginResult)
    {
      if (g_StrictClientVersionCheck)
      {
        LOG_M( LOGIN_CHNL ) << "strict version check ON. "
          << "Compatible version "
          << compatibleClientVersion.major_ << "."
          << compatibleClientVersion.minor_ << "."
          << compatibleClientVersion.patch_ << "."
          << compatibleClientVersion.revision_ << endl;
      }
      else
      {
        LOG_M( LOGIN_CHNL ) << "compatible version "
          << compatibleClientVersion.major_ << "."
          << compatibleClientVersion.minor_ << endl;
      }
    }

    resp.relayAddress.clear();
    resp.userId = -1;
  }

  SendMessageHelper( context->connection, resp );
}



bool LoginServerBase::ProcessPacket(Stream* stream, Network::IConnection *conn)
{
  AutoPerfCounterRate( "users_inc_login", 1 );

  bool res = true;

  StrongMT<SLoginContext> context = new SLoginContext( conn );
  if ( context )
  {
    LoginRequestMessage & req = context->request;
    LoginResultMessage & resp = context->response;

    CObj<IBinSaver> saver = CreateChunklessSaver( (MemoryStream*)stream, 0, true, 0, Network::MAX_MESSAGE_SIZE );
    req & (*saver);
    if (IBinSaver::BINSAVER_ERR_OK == saver->GetError())
    {
      if (req.protocolVersion != PROTOCOL_VERSION)
      {
        //  just detect old unversioned clients
        LOG_W( LOGIN_CHNL ) << "unversioned client try log in(u=" << req.login << ")" << endl;
      }

      Login::ClientVersion cv(req.majorVer, req.minorVer, req.patchVer, req.revisionVer);
      resp.loginResult = checkClientVersion(cv); //ELoginResult::Enum checkResult = checkClientVersion(cv);
      if ( ELoginResult::Success == resp.loginResult )
      {
        res = ProcessNewContext( context ); // own virtual
      }
      else
      {
        // failed клиентам в любом случае отвечаем сразу
        SendReply( context );
      }
    }
    else
    {
      LOG_E(LOGIN_CHNL).Trace("Incorrect incoming packet detected (remoteAddr=%s:%d)", conn->GetRemoteAddress().GetIp(), conn->GetRemoteAddress().GetPort());
    }
  }
  else
  {
    LOG_C(LOGIN_CHNL).Trace("Can't allocate login context!");
  }

  return res; // true: drop connection pls (prolly out of memory)
}



void LoginServerBase::StepLogin()
{
  handler.Step( this ); // получили новые connections, дропнули старые
}

} // namespace Login
