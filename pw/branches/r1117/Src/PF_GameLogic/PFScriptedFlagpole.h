#pragma once

#include "PFFlagpole.h"
#include "DBAdvMap.h"

namespace NWorld
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFScriptedFlagpole : public PFFlagpole
  {
    WORLD_OBJECT_METHODS(0x9A9BA380,PFScriptedFlagpole);
    PFScriptedFlagpole() {}

  public:
    PFScriptedFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject);

    virtual void Reset();

    virtual bool CanRaise( NDb::EFaction _faction ) const;

    virtual void OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised);
    virtual void OnDropFlag(PFBaseUnit * unitWhoDropped);

    virtual bool IsOutermost( const NDb::EFaction _faction ) const;
    virtual bool IsProtectedByTower( const NDb::EFaction _faction ) const;
    virtual bool IsProtectedByNext() const;

    virtual PFFlagpole* GetPrevFlagpole( const NDb::EFaction _faction );
    virtual PFFlagpole* GetNextFlagpole( const NDb::EFaction _faction );

  protected:
    virtual bool   Step(float dtInSeconds);
    virtual void   OnDestroyContents();

    virtual void LogFlagEvent(NDb::EFaction _faction, PFBaseUnit * unit, bool raised);
  private:
    void TryAddIntoGroups();

    seDECLARE_CPTRRING(PFScriptedFlagpole, roadRingPart, GroupRing);
    typedef hash_map<string, vector<CPtr<PFScriptedFlagpole>>> TGroups;
    static TGroups s_groups;
    ZDATA_(PFFlagpole)
    string group;
    int indexInGroup;
    bool isProtected;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFFlagpole*)this); f.Add(2,&group); f.Add(3,&indexInGroup); f.Add(4,&isProtected); return 0; }

  static void CreateGroup( const vector<PFScriptedFlagpole*>& flagpoles, const string& name );
  static int GetRaisedCountInGroup( const string& name );
  static void SetRaisedCountInGroup( const string& name, int count, PFBaseUnit* pWho );
  static void PushAll( vector<PFFlagpole*>* pFlagpoles );
#ifndef _SHIPPING
  protected:
    virtual CObj<NDebug::DebugObject> CreateDebugObject();
  private:
    friend class PFScriptedFlagpoleDebug;
#endif
  }; // End of PFFlagpole
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}