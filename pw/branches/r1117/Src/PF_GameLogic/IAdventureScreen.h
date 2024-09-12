#pragma once


namespace NCore 
{ 
class WorldCommandQueue;
}

namespace NDb
{
  class DbResource;
  enum EErrorMessageType;
}

namespace SessionEventType
{
  enum EventType;
}
  
namespace NWorld
{
  class PFBaseHero;
  class ImpulsiveBuffsManager;
  class PFBuilding;
  class PFBaseUnit;
  class PFPlayer;
}

namespace NDb
{
  enum EFaction;
	enum ERoute;
}

namespace StatisticService
{
  namespace RPC
  {
    struct SessionEventInfo;
  }
}

namespace NGameX
{
  class PFPureClientObject;

_interface INaftaInfoProvider;

enum EPauseMode
{
  PAUSE_OFF,
  PAUSE_PLAYER,
  PAUSE_HARD,
  PAUSE_CINEMATIC,
};
_interface IAdventureScreen : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IAdventureScreen, IBaseInterfaceST );


  virtual void NotifyPushedLine(const NWorld::PFBuilding * quarter, const NWorld::PFBaseUnit * killer ) = 0;//NDb::EFaction faction, NDb::ERoute routeId ) = 0;
  virtual void NotifyOfSimpleUIEvent( NWorld::PFBaseHero * hero, NDb::EErrorMessageType msg) = 0;
  virtual void NotifySoldiersFirstSpawned() = 0;

  virtual void ProcessGamePause(EPauseMode pauseMode, int playerWhoPressedPause) = 0;
  virtual void SendGameCommand( NCore::WorldCommand* commands, bool isPlayerCommand ) = 0;

  virtual void SetTimeScale(float timescale) = 0;
  virtual void OnTimeScaleChanged(float timescale) = 0;

  virtual CArray2D<float> const& GetHeightsAsFloat() const = 0;

  virtual wstring const& GetPlayerName(int playerId) const = 0;

  virtual NDb::EFaction GetPlayerFaction() const = 0;

	virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName ) = 0;
  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const NDb::DbResource * excludePart ) = 0;
  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes ) = 0;
  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes, const nstl::string& skinId ) = 0;

  virtual bool CanCreateClients() = 0;

  virtual void SetDebugMessage(nstl::string const & msg) = 0;

  virtual void LogSessionEvent(NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params) = 0;
  virtual void LogWorldSessionEvent(SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params) = 0;
  
  virtual void OnVictory( NDb::EFaction _failedFaction, int _surrenderVotes ) = 0;
  virtual void DumpState( const char* stateClass, const char* state ) = 0;

  virtual NWorld::ImpulsiveBuffsManager * GetImpulseBuffsManager() = 0;

  virtual void  SetNaftaInfoProvider(INaftaInfoProvider * _naftaInfoProvider) = 0;

  virtual void DisableRenderWarFog(NWorld::PFBaseHero const * hero, bool disable) = 0;

  virtual void OnHeroDamaged(NWorld::PFBaseHero const * hero) = 0;

  virtual void ReservePureClientObjects( unsigned int n ) = 0;
  virtual void PushPureClientObject( PFPureClientObject* pPureClientObject ) = 0;

  virtual void OnClientStatusChange( int userId, int newStatus, int step, NWorld::PFPlayer * player = 0 ) = 0;
  virtual void OnPlayerDisconnected(NWorld::PFPlayer * player, int lastStep) = 0;
  virtual void OnStartAiForPlayer( NWorld::PFPlayer * player ) = 0;
  virtual void OnProtectionError() = 0;

  virtual void OnReplayEnded() = 0;
  // TODO: remove when normal UI for replays will be implemented
  virtual void ShowReplaySpeed(float speed) = 0;
  virtual void ShowReplayPause() = 0;
  virtual void HideReplayMsg() = 0;

  virtual bool IsCustomSessionType() = 0;

  virtual bool IsSpectator() const = 0;
};

}//NGameX