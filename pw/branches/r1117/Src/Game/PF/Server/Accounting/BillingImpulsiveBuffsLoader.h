#pragma once
#include "Db/DBServer.auto.h"

namespace NDb
{
  struct CommonBuffsContainer;
}

namespace Lobby
{
  class LobbyAccounting;

  _interface ILobbyAccountingPricesLoader
  {
    virtual ~ILobbyAccountingPricesLoader() {}
    virtual int Load( LobbyAccounting* accounting ) = 0;
  };

  ILobbyAccountingPricesLoader* CreateLobbyAccountingPricesLoader( const NDb::BuyServicesContainer * settings ); 

} // Lobby