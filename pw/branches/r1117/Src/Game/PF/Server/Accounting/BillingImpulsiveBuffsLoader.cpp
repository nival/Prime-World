#include "stdafx.h"
#include "BillingImpulsiveBuffsLoader.h"
#include "Db/DBServer.auto.h"

#include "LobbyAccounting.h"

namespace Lobby
{
  class LobbyAccountingPricesLoader : public ILobbyAccountingPricesLoader
  {

    NDb::Ptr<NDb::BuyServicesContainer> settings;

  public:
    LobbyAccountingPricesLoader( const NDb::BuyServicesContainer * _settings ) : settings(_settings) {}

    virtual int Load( LobbyAccounting* accounting )
    {
      if ( !settings || !accounting )
      {
        return 0;
      }

      //this is not the best code. not that general services like ZZBoost are located right after impulses buffs
      int id = 0;

      for ( int i = 0; i < settings->buffs.size(); ++i, ++id )
        accounting->SetPrice( id, settings->buffs[i].goldCost );

      for ( int i = 0; i < settings->services.size(); ++i, ++id )
        accounting->SetPrice( id, settings->services[i].goldCost );

      for ( int i = 0; i < settings->rewards.size(); ++i )
        accounting->SetupReward( i, NDb::BILLINGSERVICESSTART_REWARDS + i, settings->rewards[i].goldCost );

      return 0;
    }
  };

  ILobbyAccountingPricesLoader* CreateLobbyAccountingPricesLoader( const NDb::BuyServicesContainer * settings )
  {
    return new LobbyAccountingPricesLoader( settings );
  }
}
