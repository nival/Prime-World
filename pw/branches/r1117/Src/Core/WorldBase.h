#pragma once
_interface IPointerHolder;

namespace lobby { class  AccountingGadget; }

namespace NCore
{
  class WorldCommand;
  class PackedWorldCommand;
  struct ClientStatus;

  typedef vector<CObj<PackedWorldCommand> > TPackedCommands;
  typedef nstl::vector<ClientStatus> TStatuses;

  // NOTE: probably shouldn't be here
  struct ProtectionResult
  {
    int step;
    int magic;
  };

  _interface IWorldBase : public virtual CObjectBase
  {
    virtual void ExecuteCommand( WorldCommand* pCommand ) = 0;
    virtual IPointerHolder *GetPointerSerialization() = 0;
    virtual void UpdatePlayerStatuses(const NCore::TStatuses & statuses) = 0;
    virtual void ExecuteCommands(const NCore::TPackedCommands & commands) = 0;
    virtual bool Step(float dtInSeconds, float dtLocal) = 0;

    virtual int GetStepLength() const = 0;
    virtual float GetStepLengthInSeconds() const = 0;

    virtual void CalcCRC( IBinSaver &f, bool fast ) = 0;

    virtual int GetStepNumber() const = 0;

    virtual void SetAccounting( lobby::AccountingGadget* accounting ) = 0;

    virtual void SetPause( bool paused, int playerId ) = 0;
    virtual bool IsPaused() const = 0;

    virtual void SetSlowdownHint( float hintValue ) = 0;
    virtual float GetSlowdownHint() const = 0;

    virtual void Save() const = 0;
    virtual void Load() = 0;

    virtual bool HasProtection() const = 0;
    virtual bool PollProtectionResult(ProtectionResult& result) = 0;
    virtual void SetProtectionUpdateFrequency(const int offset, const int frequency) = 0;
  };
} //namespace NCore

