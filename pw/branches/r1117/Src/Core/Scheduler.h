#pragma once

static const int DEFAULT_GAME_STEP_LENGTH = 100;

namespace NCore
{

class PackedWorldCommand;
class WorldCommand;
_interface IWorldBase;

struct MapStartInfo;
struct StepsDelaySettings;

struct ClientStatus
{
  uint clientId;
  int status;
  int step;
};

struct StepsDelaySettings
{
  int stepsDelayMin;
  int stepsDelayMax;
  int stepsDelayFrame;

  StepsDelaySettings() : stepsDelayMin(1), stepsDelayMax(1), stepsDelayFrame(0) {}
};

_interface IServerNode : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IServerNode, IBaseInterfaceMT);
  typedef nstl::vector<CObj<Stream> > TMessageList;
  typedef nstl::vector<ClientStatus> TStatusList;

  virtual void ClientReady() = 0;
  virtual int GetStartedStep() const = 0; // INVALID_STEP (-1) if none

  virtual bool IsReconnecting() const = 0;

  virtual void SendMessage( Stream *pMsg, bool isPlayerCommand ) = 0;

  virtual int GetServerSegment( TMessageList &segment, TStatusList & statuses ) = 0; // INVALID_STEP (-1) if none

  virtual void SendCRC( int step, DWORD crcValue ) = 0;
  virtual void SendCrcData( int step, unsigned char * data, int size) = 0;
  virtual int GetAsyncStep() const = 0; // INVALID_STEP (-1) if none
  virtual int GetProtectionAsyncStep() const = 0; // INVALID_STEP (-1) if none
  virtual int GetLastConfirmedStep() const = 0; // INVALID_STEP (-1) if none
  virtual int PopCrcRequestStep() = 0; // INVALID_STEP (-1) if none

  virtual const StepsDelaySettings & GetStepsDelaySettings() = 0;
  virtual bool IsCrcDataEnabled() const = 0;

  virtual void SendProtectionMagic(int step, uint magic) = 0;
  virtual int GetProtectionMagicConfirmFrequency() const = 0;
};


struct SyncSegment : public CObjectBase
{
  OBJECT_BASIC_METHODS( SyncSegment )
public:
  SyncSegment() : step( 0xFFFFFFFF ) { }
  SyncSegment( uint _step ) : step( _step ) { }

  typedef vector<CObj<PackedWorldCommand> > TCmdVector;
  typedef nstl::vector<ClientStatus> TStatuses;

  ZDATA
    ZNOPARENT(CObjectBase)
    TCmdVector commands;
    TStatuses statuses;
    uint step;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&commands); f.Add(3,&statuses); f.Add(4,&step); return 0; }
};


_interface ISessionRunner;

class ICommandScheduler : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ICommandScheduler, IBaseInterfaceMT);
public:
  virtual void Reinit( IServerNode * _server, ISessionRunner * _asyncProcessor ) = 0;

  virtual void SendMessage( CObjectBase *pMsg, bool isPlayerCommand ) = 0;

  virtual CObj<SyncSegment> GetSyncSegment() = 0;
  virtual int GetNextStep( bool warnIfNoSegments ) const = 0; // INVALID_STEP (-1) if none

  virtual void SendCRC( int step, DWORD crcValue ) = 0;
  virtual void SendCrcData( int step, unsigned char * data, int size) = 0;
  virtual int GetStartedStep() = 0; // INVALID_STEP (-1) if none
  virtual int GetAsyncStep() = 0; // INVALID_STEP (-1) if none
  virtual int GetProtectionAsyncStep() = 0; // INVALID_STEP (-1) if none
  virtual int GetLastConfirmedStep() = 0; // INVALID_STEP (-1) if none
  virtual int PopCrcRequestStep() = 0; // INVALID_STEP (-1) if none

  virtual bool IsAllClientsReady() = 0;

  virtual void Step( float dt ) = 0; // 'dt' is in seconds, of course

  virtual int GetMyClientID() const = 0;

  virtual const StepsDelaySettings & GetStepsDelaySettings() = 0;
  virtual bool IsCrcDataEnabled() = 0;

  virtual void SendProtectionMagic(int step, uint magic) = 0;
  virtual int GetProtectionMagicConfirmFrequency() = 0;
}; //ICommandScheduler



class ITransceiver : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( ITransceiver, IBaseInterfaceST );

public:
  virtual void Reinit( ICommandScheduler * scheduler ) = 0;
  virtual void Step( float dt ) = 0; // 'dt' is in MILLISECONDS!

  virtual void SendCommand( WorldCommand *pCmd, bool isPlayerCommand ) = 0;

  virtual void SetWorld( IWorldBase * world ) = 0;
  virtual IWorldBase * GetWorld() = 0;

  virtual void RecordMapStart( const MapStartInfo & info ) = 0;

  virtual bool IsPaused() const = 0;
  virtual bool IsAsynced() const = 0;

  virtual int GetNextStep() const = 0;
  virtual void SetNextStep( int _nextStep ) = 0;

  virtual void SetPrecalcCrcOnce( bool _precalcCrcOnce ) = 0;

  virtual bool GetNoData() const = 0;

  virtual int GetWorldStep() const = 0;
  virtual int GetBufferLimit() const = 0;

  virtual ~ITransceiver() = 0 {};
}; //ITransceiver

} //namespace NCore
