#pragma once

#ifndef _SHIPPING
#include "PFDebug.h"
#endif
#include "PFWorldObjectBase.h"
#include "LuaScript.h"
#include "Scripts/lua.hpp"
#include "PFAIControllerInterfaces.h"

namespace NCore
{
  class ITransceiver;
}

namespace PF_Core
{
  class BasicEffectStandalone;
}

namespace NWorld
{

class PFAIContainer;
interface IPFAIController;
class PFLogicObject;
class PFBaseHero;
class PFBaseMaleHero;
class PFPlayer;
class PFBaseCreep;
class PFCreature;
class PFFlagpole;
class PFBaseUnit;
class PFWorldObjectBase;
class PFQuarters;
class PFMainBuilding;
class PFShop;
class PFBaseUnitEvent;
class PFScriptEventListener;
class Target;
class PFSimpleObject;

struct HeroAlias
{
  string alias;
  string hero;
  HeroAlias( const string _alias, const string _hero ): alias( _alias ), hero( _hero ) { }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAIContainer : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0x1E641B00, PFAIContainer);

  typedef hash_map<NDb::DBID, Placement> TCameraSplines;
  TCameraSplines cameraSplines;

public:
  class CommandExecutor : public CObjectBase
  {
    OBJECT_BASIC_METHODS( CommandExecutor );
  public:
    enum CommandResult
    {
      COMMAND_DONE,
      COMMAND_WAIT,
      COMMAND_FAILED,
    };

    virtual CommandResult Process( const string& command, const vector<string>& args ) { return COMMAND_DONE; }
  };

  PFAIContainer( PFWorld* pWorld, NCore::ITransceiver *pTransceiver );

  bool Step( float timeDelta );

  // Management functions
  IPFAIController* Find( const PFBaseHero* pUnit ) const;
  // Line numbers: >= 0 is real number, -1 is random
  IPFAIController* Add( PFBaseHero* pUnit, int lineNumber = RANDOM_LINE );
  IPFSeriesAIController * AddSeriesController( PFBaseHero* pUnit, bool lvlUpAvailable );

  void OnMinimapSignal( PFBaseHero* pSender, PFBaseUnit* pSelected, const Target& target );

  bool Remove( PFBaseHero* pUnit );
  void RemoveAll();

  void LoadScript( const vector<string>& script );
  bool LoadScript( const string & scriptName, const vector<NDb::ResourceDesc> & res, bool isReconnecting );

  typedef vector<NDb::ScriptArea> TScriptAreas;
  void SetScriptAreas( const TScriptAreas& _scriptAreas ) { scriptAreas = _scriptAreas; }
  const NDb::ScriptArea* GetScriptArea( const char* name );
  void GetScriptAreasByName( const string& name, vector<const NDb::ScriptArea*>& _scriptAreas );

protected:
#ifndef _SHIPPING
  //DECLARE_DEBUG_CB_TABLE()
  void ShowDebug( Render::IDebugRender* pRender ) const;
#endif

private:
  PFAIContainer() {} // need for correct dying
public:  // Public for access from global lua calls
  PFBaseHero* GetLocalHero() const;
  PFBaseHero* FindHero( const char* hero, bool aliasEnabled = true ) const;
  PFCreature* FindCreature( const char* creature ) const;
  PFFlagpole* FindFlag(int roadIndex, int flagIndex) const;
  PFBaseUnit* FindUnit( const char* unit ) const;
  PF_Core::WorldObjectBase* FindObject( const char* obj ) const;
  bool FindTalent( PFBaseHero* hero, const char* persistentId, int* level, int* slot ) const;
  list<CPtr<PF_Core::WorldObjectBase>> * FindGroup( const char * group );
  bool FindDeadObjectName(const char * objectName) const;
  const char* FindObjectGroupName( const PF_Core::WorldObjectBase* object ) const;

  // not hash_set<PFBaseCreep*> because of indeterminate order of elements in hash set of pointers
  void GetCreepNames( const hash_set<int>& objectIds, vector<const char*>* pObjectNames );
  bool FindObjectName( string& name, PF_Core::WorldObjectBase* object );
  void GetHeroName( PFBaseHero* pHero, string &name );

  void RemoveStandaloneEffect( const char* effectName );
  void PlaceStandaloneEffect( const char* effectName, const char* dbid, float x, float y );
  void PlaceAttachedEffect( const char* name, const char* dbid, const char* parentName );
  void PlaceClientEffect( const char* dbid, float x, float y );

  void PlaceSimpleObject( const char* name, const char* dbid, float x, float y, float z );
  void PlaceSimpleObject( const char* name, const char* dbid, float x, float y, float z, float roll, float pitch, float yaw );
  void RemoveSimpleObject( const char* name );
  void ShowSimpleObject( const char* name );
  void HideSimpleObject( const char* name );

  bool UseConsumable( const char* hero, const char* item, const char* unit = 0, float x = -1.0f, float y = -1.0f );

  void PlaceMinimapIcon( const char* iconName, NDb::EMinimapIcons icon, float x, float y, NDb::EUnitType _unitType );
  void RemoveMinimapIcon( const char* iconName );

  void OnReconnect();

  void RegisterEventScriptHandler( const char* name, NDb::EBaseUnitEvent eventType, const char* callbackFunctionName );
  void UnregisterEventScriptHandler( const char* name, NDb::EBaseUnitEvent eventType );
  void InvokeEventCallback( const string& name, const string& callbackFunctionName, const PFBaseUnitEvent *pEvent );

  bool CreateZombie( PFCreature const* pCreature, const char* dbid, const NDb::EFaction faction );

  const char* GetFileNameByKey(const char* key);

  bool CaptureTheFlag(const char *unitScripName, NDb::EFaction faction, bool pickup);

#ifndef _SHIPPING
  void RegisterScriptCommands();

  bool DebugBreak();
  bool Exit();
  bool Goto( const int line );
  bool WaitSteps( const int step );
  bool AddGold( const char* hero, const int amount );
  bool AddHealth( const char* unit, const int amount );
  bool AddMana( const char* unit, const int amount );
  bool UnitStat( const char* hero, const int stat, const int value );
  bool TeleportTo( const char* unit, const float x, const float y );
  bool ActivateTalent( const char* hero, const char* talent );
  bool UseTalent( const char* hero, const char* talent );
  bool UseTalentPos( const char* hero, const char* talent, const float x, const float y );
  bool UseTalentUnit( const char* hero, const char* talent, const char* unit );
  bool UseItem( const char* hero, const char* item );
  bool UseItemPos( const char* hero, const char* item, const float x, const float y );
  bool UseItemUnit( const char* hero, const char* item, const char* unit );
  bool KillUnit( const char* unit );
  bool KillMainBuilding( const int team );
  bool RefreshCooldown( const char* hero );
  bool SetHeroAlias( const char* _hero, const char* _alias );
  bool SetTimeScale( const float scale );
  bool ResurrectHero( const char* hero );
  bool SuggestBuff( const char* buff_id );
  bool UseBuff();
  bool CreateObject( const char* name, const char* dbid, const float x, const float y );
  bool LoadTalents( const char* _unit, const char* _talent_set_file );
#endif // #ifndef _SHIPPING

  bool UseTalentImpl( PFBaseMaleHero* hero, int level, int slot );
  bool UseTalentPosImpl( PFBaseMaleHero* hero, int level, int slot, float x, float y );
  bool UseTalentUnitImpl( PFBaseMaleHero* hero, int level, int slot, PFBaseUnit* unit );
  bool ActivateTalentImpl( PFBaseMaleHero* hero, int level, int slot, bool addGold = true, bool activatePrevious = true );
  bool SpawnCreep( const char* name, const char* dbid, const float x, const float y, const int faction );
  bool SpawnCreep( const char* name, const char* dbid, const float x, const float y, const int faction, const float yaw );
  bool ReplaceCreep( const char* name, const char* dbid, const int faction );
  bool SendMessage( const char* message );
  bool AttackUnit( const char* player, const char* unit );
  bool AttackUnitToUnit( const char* _creature, const char* _target );
  bool MoveTo( const char* unit, const float x, const float y, const float dist );
  bool WorldScriptMoveTo( const char* _unit, const float x, const float y );
  bool UsePortalTo( const char* _unit, const float x, const float y );
  bool ChangeNatureMap( const float x, const float y, const float radius, NDb::ENatureType from, NDb::ENatureType to);
  bool HeroRaiseFlag( const char* _hero, const char* _flag );
  void StepScript();

  void RemoveInvalidUnits();
  void BuildIdNameMap();

  template<typename TObj>
  void RegisterCommand( const char* command, bool (TObj::*func)( void ) );

  template<typename TObj, typename T1>
  void RegisterCommand( const char* command, bool (TObj::*func)( T1 p1 ) );

  template<typename TObj, typename T1, typename T2>
  void RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2 ) );

  template<typename TObj, typename T1, typename T2, typename T3>
  void RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3 ) );

  template<typename TObj, typename T1, typename T2, typename T3, typename T4>
  void RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3, T4 p4 ) );

  template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5>
  void RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 ) );

  void RegisterObject(PF_Core::WorldObjectBase* pObject, nstl::string scriptName, nstl::string scriptGroupName );

  void RegisterCameraSpline( const NDb::DBID& dbid, const Placement& placement ) { cameraSplines[dbid] = placement; }
  const Placement& GetPlacementCameraSpline( const NDb::DBID& dbid ) { return( cameraSplines[dbid] ); }

  void RegisterScriptPath( const string &scriptName, const NDb::ScriptPath* gameObject );
  const vector<CVec2>* GetScriptPath( const string &scriptName );

  void RegisterPolygonArea( string scriptName, const NDb::ScriptPolygonArea* area );
  template <typename TFunc>
  bool ForAllPartsInPolygonArea( const string& scriptName, const string& partSelector, TFunc &func ) const;

  const Strong<PFScript> & GetLuaScript() const { return luaScript; };

  bool GetLogScriptEvents() const { return logScriptEvents; }
  void SetLogScriptEvents(bool _logScriptEvents) { logScriptEvents = _logScriptEvents; }

  // data fields
  vector<CObj<IPFAIController> > controllers;
  Weak<NCore::ITransceiver> transceiver;
  // "macros" support
  hash_map<string, CObj<CommandExecutor>> commands;
  vector<string> script;
  vector<HeroAlias> heroesAliases;
  int currentLine;

  int waitStep;

public:

  struct ScriptEffect
  {
    CObj<PF_Core::BasicEffect> pEffect;
    ZDATA
    NDb::DBID dbid;
    float x;
    float y;
    CPtr<PFLogicObject> pObject;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&dbid); f.Add(3,&x); f.Add(4,&y); f.Add(5,&pObject); return 0; }
    ScriptEffect()
    :x(0.f),y(0.f) {}
    ScriptEffect( const NDb::DBID& _dbid, float _x, float _y )
    :dbid(_dbid),x(_x),y(_y) {}
    ScriptEffect( const NDb::DBID& _dbid, PFLogicObject* _pObject )
      :dbid(_dbid),x(0.f),y(0.f),pObject(_pObject) {}
    bool Create( NScene::IScene* pScene );
    void Remove();
  };

  class MinimapIcon : public PF_Core::IUpdateable
  {
    OBJECT_METHODS( 0x9AA22CC0, MinimapIcon );
  public:
    MinimapIcon( NDb::EMinimapIcons _icon, float _x, float _y, NDb::EUnitType _unitType, NDb::EFaction _faction  );
    virtual void Update(float timeDelta);
  private:
    MinimapIcon(){}

    NDb::EMinimapIcons icon;
    float x;
    float y;
    NDb::EUnitType unitType;
    NDb::EFaction faction;
  };


  typedef hash_map<string, CPtr<PFBaseCreep>>                    TCreeps;
  typedef hash_map<string, CPtr<PFBaseUnit>>                     TUnits;
  typedef hash_map<string, CPtr<PF_Core::WorldObjectBase>>       TObjects;
  typedef list<CPtr<PF_Core::WorldObjectBase>>                   TObjectGroup;
  typedef hash_map<string, TObjectGroup>                         TObjectGroups;
  typedef set<string>                                            TNames;
  typedef hash_map<string, ScriptEffect>                         TScriptEffects;
  typedef hash_map<string, vector<CVec2>>                        TScriptPaths;
  typedef hash_map<string, NDb::Ptr<NDb::ScriptPolygonArea>>     TScriptPolyAreas;
  typedef hash_map<int, string>                                  TObjectNames;
  typedef hash_map<string, CObj<MinimapIcon>>                    TMinimapIcons;
  typedef hash_map<string, CPtr<PFSimpleObject>>                 TSimpleObjects;

  static Weak<PFScript> s_luaScript;

private:
  TScriptAreas       scriptAreas;
  Strong<PFScript>   luaScript;
  typedef hash_map<string, string> ScriptResources;
  ScriptResources resources;
  TScriptPaths scriptPaths;
  TScriptPolyAreas scriptPolyAreas;
  TObjectNames       objectIdToName;
  TMinimapIcons      minimapIcons;
  bool               logScriptEvents;

  ZDATA_(PFWorldObjectBase)
  TCreeps            creeps;
  TUnits             units;
  TObjects           objects;
  TObjectGroups      objectGroups;
  TNames             deadObjectNames;
  TScriptEffects     scriptEffects;
  PFScriptSerializer scriptSerializer;
  TSimpleObjects     simpleObjects;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&creeps); f.Add(3,&units); f.Add(4,&objects); f.Add(5,&objectGroups); f.Add(6,&deadObjectNames); f.Add(7,&scriptEffects); f.Add(8,&scriptSerializer); f.Add(9,&simpleObjects); return 0; }
};

template <typename TFunc>
bool PFAIContainer::ForAllPartsInPolygonArea( const string& scriptName, const string& partSelector, TFunc &func ) const
{
  TScriptPolyAreas::const_iterator ita = scriptPolyAreas.find(scriptName);
  if ( ita == scriptPolyAreas.end() )
    return false;

  bool res = false;
  const NDb::ScriptPolygonArea *pA = ita->second;
  for( vector<NDb::ScriptPolygonAreaPolygon>::const_iterator it = pA->polygons.begin(); it != pA->polygons.end(); ++it )
  {
    if ( !partSelector.empty() && it->name != partSelector )
      continue;

    vector<CVec2> polygon;
    for ( int i = 0; i < it->indexes.size(); ++i )
    {
      NI_DATA_VERIFY( it->indexes[i] >= 0 && it->indexes[i] < pA->points.size(), NStr::StrFmt("Invalid polygon found in %s : %s", scriptName.c_str(),  it->name.c_str() ), continue );
      polygon.push_back( pA->points[it->indexes[i] ] );
    }
    NI_DATA_VERIFY( polygon.size() > 2, NStr::StrFmt("Not enough points in polygon %s : %s", scriptName.c_str(), it->name.c_str() ), continue ); 
    func( polygon );
    res = true;
  }
  return res;
}

bool FindQuarters( PFWorld* pWorld, NDb::EFaction faction, vector<PFQuarters*>& objects );
bool FindMainBuildings( PFWorld* pWorld, NDb::EFaction faction, vector<PFMainBuilding*>& objects );
bool FindShop( PFWorld* pWorld, NDb::EFaction faction, vector<PFShop*>& objects );

} // namespace
