#include "stdafx.h"
#include "AdventureScreen.h"
#include "PFWorld.h"
#include "PF_Core\World.hpp"
#include "PFHero.h"
#include "HeroActions.h"


namespace PF_Core
{
  void MakeTrueAsyncForTest( World *pWorld )
  {
    ++pWorld->lastUsedId;
  }
}

namespace NWorld
{
  void MakeTrueAsyncForTest( PFBaseHero *pHero )
  {
    pHero->health = 0.12345f;
  }
}


bool MakeTrueAsyncForTest( const char *name, const vector<wstring> &params )
{
  using namespace NGameX;
  using namespace NWorld;
  
  AdventureScreen * const pAdv = AdventureScreen::Instance(); 
  
  PF_Core::MakeTrueAsyncForTest( pAdv->GetWorld() ); 
  NWorld::MakeTrueAsyncForTest( pAdv->GetHero() );
  
  return true;
}

bool MakeProtocolCheatForTest( const char *name, const vector<wstring> &params )
{
  if (NGameX::AdventureScreen * pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (NWorld::PFBaseHero * pHero = pAdvScreen->GetHero())
    {
      CVec2 pos(0.0f, 0.0f);
      for (int i = 0; i < 5000; ++i)
      {
        pAdvScreen->SendGameCommand( CreateCmdMoveHero( pHero, pos, false ) );
      }
    }
  }

  return true;
}

bool MakeLag( const char *name, const vector<wstring> &params )
{
  if (params.size() != 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " seconds" << endl;
    return true;
  }

  float seconds = NGlobal::VariantValue(params[0]).GetFloat();

  seconds *= 1000.0f;

  Sleep( seconds );

  return true;
}

REGISTER_DEV_CMD( make_true_async, MakeTrueAsyncForTest );
REGISTER_DEV_CMD( make_protocol_cheat, MakeProtocolCheatForTest );
REGISTER_DEV_CMD( make_lag, MakeLag );
