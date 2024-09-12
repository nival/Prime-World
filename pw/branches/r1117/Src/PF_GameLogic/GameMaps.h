#ifndef GAMEMAPS_H_INCLUDED
#define GAMEMAPS_H_INCLUDED

#include "Core/GameTypes.h"
#include "Game/PF/Server/LobbyPvx/CommonTypes.h" //FIXME: Move "CommonTypes.h" & cpp from PW_Client project to PF_GameLogic ?

#include "PF_GameLogic/DbMapList.h"

namespace Peered
{
  struct ClientInfo;
}

namespace NWorld
{

class IMapLoader : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMapLoader, IBaseInterfaceMT );
public:

  virtual const char * GetMapDbId() const = 0;
  virtual bool FillMapStartInfo( NCore::MapStartInfo & _mapStartInfo, const lobby::TGameLineUp & _gameLineup, const lobby::SGameParameters & _randomSeed ) = 0;
  virtual bool FillPlayersInfo( NCore::MapStartInfo & _mapStartInfo, const vector<Peered::ClientInfo> & clientInfos, bool assertIfNoInfo = false ) = 0;
  virtual int GetMaxPlayersPerTeam() = 0;
  virtual const char* GetMapDescName() = 0;
};


class IMapCollection : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMapCollection, IBaseInterfaceMT );
public:

  virtual int MapsListSize() const = 0;
  virtual const char * MapId( int index ) const = 0;
  virtual const char * MapDescId( int index ) const = 0;
  virtual const wchar_t * MapTitle( int index ) const = 0;
  virtual const wchar_t * MapDescription( int index ) const = 0;
  virtual int FindMapById( const char * id ) const = 0;
  virtual IMapLoader * CreateMapLoader( const char * id ) = 0;
  virtual const char * CustomDescId( int index ) const = 0;
  virtual const wchar_t * CustomTitle( int index ) const = 0;
  virtual const wchar_t * CustomDescription( int index ) const = 0;
  virtual void InitCustomList( const NDb::Ptr<NDb::MapList> list ) = 0;
};

} //namespace NWorld

#endif //GAMEMAPS_H_INCLUDED
