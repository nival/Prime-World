#pragma once

#include "PFFlagpole.h"
#include "DBAdvMap.h"

namespace NDb
{
  struct Flagpole;
}

namespace NGameX
{
  class PFClientFlagpole;
}

namespace NWorld
{
  class PFRoadFlagpole;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class OwnerListener : public PFBaseUnitEventListener, public PFWorldObjectBase
  {
    WORLD_OBJECT_METHODS(0x8D823C00, OwnerListener);

    ZDATA_(PFWorldObjectBase)
    ZNOPARENT(PFBaseUnitEventListener)
    CPtr<PFRoadFlagpole> listener;
    CPtr<PFBaseUnit> owner;
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&listener); f.Add(3,&owner); return 0; }
  protected:
    OwnerListener() { }

  public:
    OwnerListener( PFRoadFlagpole* _listener, PFBaseUnit* _owner ) : PFWorldObjectBase( _owner->GetWorld(), 0 )
    {
      listener = _listener;
      _owner->AddEventListener( this );
      owner = _owner;
    }

    void Unregister()
    {
      if ( IsValid( owner ) )
        owner->RemoveEventListener( this );
    }

    virtual unsigned int OnEvent( const PFBaseUnitEvent *event );
  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFRoadFlagpole : public PFFlagpole
  {
    WORLD_OBJECT_METHODS(0x9A9B9C40,PFRoadFlagpole);
    PFRoadFlagpole() {}

  public:
    PFRoadFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject);

    virtual void Reset();

    virtual bool CanRaise( NDb::EFaction _faction ) const;

    virtual void OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised);
    virtual void OnDropFlag(PFBaseUnit * unitWhoDropped);
    void OnEvent( const PFBaseUnitEvent *event );

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
    void FindOwners();
    NDb::EFaction GetOwnersFaction() const;

    seDECLARE_CPTRRING(PFRoadFlagpole, roadRingPart, RoadRing);
    enum { NUM_ROADS = NDb::KnownEnum<NDb::ENatureRoad>::sizeOf };
    static StaticArray<RoadRing, NUM_ROADS> s_roads;

    ZDATA_(PFFlagpole)
    vector<CObj<OwnerListener> > listeners;
    NDb::ENatureRoad natureRoad;
    int natureSegment;
    bool needFindOwners;
    vector<CPtr<PFBaseUnit> > owners;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFFlagpole*)this); f.Add(2,&listeners); f.Add(3,&natureRoad); f.Add(4,&natureSegment); f.Add(5,&needFindOwners); f.Add(6,&owners); return 0; }

  public:
    static PFFlagpole* GetFirstFlagpole( const NDb::EFaction _faction, const NDb::ENatureRoad _natureRoad );
    static PFFlagpole* GetLastFlagpole(  const NDb::EFaction _faction, const NDb::ENatureRoad _natureRoad );
    static void Attack( NDb::EFaction _faction, NDb::ENatureRoad _natureRoad, int count );
    static int GetNumRoads() { return NDb::KnownEnum<NDb::ENatureRoad>::sizeOf; }
    static void PushAll( vector<PFFlagpole*>* pFlagpoles );
#ifndef _SHIPPING
  protected:
    virtual CObj<NDebug::DebugObject> CreateDebugObject();
  private:
    friend class PFFlagpoleDebug;
#endif
  }; // End of PFFlagpole
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}