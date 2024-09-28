#pragma once

#include "../Client/DefaultScreenBase.h"
#include "../Core/MessagesLogin.h"
#include "../Core/MessagesInGame.h"

#include "FinalScreenLogic.h"

namespace NGameX
{

class FinalScreen : public NMainLoop::DefaultScreenBase
{
private:
  OBJECT_METHODS( 0xB625400, FinalScreen );

  virtual void SubscribeUpdates();
  CObj<UI::FinalScreenLogic> pLogic;
  int loserFaction;

public:
  FinalScreen() : loserFaction( -1 ) {}
  FinalScreen( int _loserFaction ) : loserFaction( _loserFaction ) {}
  virtual ~FinalScreen();

  virtual bool Init( UI::User * uiUser ); 

  bool IsModal() const { return false; }
  bool IsTransparent() const { return false; }

  void CloseScreen();
  void ShowFinalMessage( const NCore::GameShowWonMessage& message );
};

} // End of namespace NGameX
