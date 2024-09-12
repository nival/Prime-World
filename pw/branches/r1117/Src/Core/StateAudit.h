#pragma once

#include "CoreFSMState.h"

namespace NCore
{

class Transceiver;
class CGameCmd;
class CGameNode;

struct AuditGameStarted;
struct AuditStartInfo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CStateAudit
  : public CoreFSMState
{
  OBJECT_METHODS( 0xF646B80, CStateAudit );
  CStateAudit() {}
  ~CStateAudit();

  void OnAuditGameStarted( const AuditGameStarted& msg );
  void OnAuditStartInfo( const AuditStartInfo& msg );
  void OnMapLoaded( const struct MapLoaded& msg );

  // NCore::CoreFSMState overrides
  virtual void SubscribeUpdates();
  virtual IBaseFSMState* Step(float);

  struct TransceiverHolder;
  friend class LocalNode;

  enum { maxPlayers = 10 };
  typedef StaticArray<AutoPtr<TransceiverHolder>, maxPlayers> Transievers;
  
  enum AuditStage
  {
    eStartingAudit,
    eWaitingStartInfo,
    eStartingGames,
    eGaming,
  };
  AuditStage    stage;
  int           playersCount;
  Transievers   m_holders;
  
public:
  CStateAudit( CoreFSM *pContext );
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CStateAudit::TransceiverHolder
{
  TransceiverHolder(int nodesCount, int clientId);
  bool                    started;
  AutoPtr<Transceiver>    transceiver;
  vector<CObj<CGameNode>> nodes;
};


} //namespace NCore
