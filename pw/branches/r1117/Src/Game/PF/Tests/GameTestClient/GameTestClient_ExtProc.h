#pragma once

#include "IGameTestClient.h"

namespace gtc
{

class Client_ExtProc : public IGameTestClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Client_ExtProc, IGameTestClient, BaseObjectMT );

public:
  Client_ExtProc( const char * _appPath, const char * _sessionKey );
  ~Client_ExtProc();

  //IGameTestClient
  virtual StepResult MainStep();
  virtual void TerminatePvx();
  virtual int Stage() const { return Stage::GAME; }
  virtual Transport::TClientId UserId() const { return 0; }

  virtual void SetSocialClient( GtcSocial::SocialClient * _socClient ) { socialClient = _socClient; }
  virtual GtcSocial::SocialClient * SocialClient() const { return  socialClient; }

protected:
  enum EState { StInit, StRunning, StFailed, StStopped };

  EState state;
  StrongMT<GtcSocial::SocialClient> socialClient;

  PROCESS_INFORMATION procInfo;

  void Close();
  string FormatWindowError( DWORD err );
};

} //namespace gtc
