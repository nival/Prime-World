#include "stdafx.h"

#include "../Core/Scheduler.h"
#include "libdb/DbResourceCache.h"
#include "PFAIContainer.h"

#include "PFWorld.h"
#include "PFPlayer.h"
#include "AdventureScreen.h"
#include "PFHero.h"
#include "PFMaleHero.h"
#include "PFCheat.h"
#include "HeroActions.h"
#include "PFCreep.h"
#include "PFCommonCreep.h"
#include "PFNeutralCreep.h"
#include "PFMainBuilding.h"
#include "PFSimpleObject.h"
#include "PFRoadFlagPole.h"
#include "PFTree.h"
#include "PFImpulsiveBuffs.h"
#include "Client/MainTimer.h"
#include "System/MainFrame.h"
#include "PFTalent.h"
#include "PFConsumable.h"
#include "PFClientCreep.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename TFunc, int count>
class CommandExecutorWithChecker : public NWorld::PFAIContainer::CommandExecutor
{
  OBJECT_BASIC_METHODS( CommandExecutorWithChecker );

  string error;

protected:
  TObj *obj;
	TFunc func;

  virtual bool Process( const vector<string>& args )
  {
    return true;
  }

  void Fail( const char* message )
  {
    error = message;
  }

  bool FromString( const string& value, int* out )
  {
    *out = 0;
    if ( !NStr::IsFloatNumber( value.c_str() ) || value.find( '.' ) != string::npos )
    {
      Fail( NStr::StrFmt( "\"%s\" is not valid integer number", value.c_str() ) );
      return false;
    }

    *out = NStr::ReadInt( value.c_str(), value.size() );

    return true;
  }

  bool FromString( const string& value, float* out )
  {
    *out = 0;
    if ( !NStr::IsFloatNumber( value.c_str() ) )
    {
      Fail( NStr::StrFmt( "\"%s\" is not valid float number", value.c_str() ) );
      return false;
    }

    *out = NStr::ReadFloat( value.c_str(), value.size() );

    return true;
  }

  bool FromString( const string& value, const char** out )
  {
    *out = value.c_str();
    return true;
  }
public:
	CommandExecutorWithChecker() : obj( 0 ), func( 0 ) {}
	CommandExecutorWithChecker( TFunc _func, TObj *_obj ) : func( _func ), obj( _obj ) { }

  virtual CommandResult Process( const string& command, const vector<string>& args )
  {
    NI_DATA_VERIFY( args.size() == count, NStr::StrFmt( "Invalid number of arguments (\"%s\")", command.c_str() ), return COMMAND_FAILED );
    bool result = Process( args );
    NI_DATA_VERIFY( error.empty(), NStr::StrFmt( "%s (\"%s\")", error.c_str(), command.c_str() ), return COMMAND_FAILED );
    
    return result ? COMMAND_DONE : COMMAND_WAIT;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj>
class CommandExecutor0 : public CommandExecutorWithChecker<TObj, bool (TObj::*)(), 0>
{
  OBJECT_BASIC_METHODS( CommandExecutor0 );
public:
  CommandExecutor0() {}
	CommandExecutor0( bool (TObj::*func)(), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    return (obj->*func)();
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1>
class CommandExecutor1 : public CommandExecutorWithChecker<TObj, bool (TObj::*)( const T1 p1 ), 1>
{
  OBJECT_BASIC_METHODS( CommandExecutor1 );
public:
  CommandExecutor1() {}
	CommandExecutor1( bool (TObj::*func)( const T1 p1 ), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    T1 p1; if ( !FromString( params[0], &p1 ) ) return false;
    return (obj->*func)( p1 );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2>
class CommandExecutor2 : public CommandExecutorWithChecker<TObj, bool (TObj::*)( const T1 p1, const T2 p2 ), 2>
{
  OBJECT_BASIC_METHODS( CommandExecutor2 );
public:
  CommandExecutor2() {}
	CommandExecutor2( bool (TObj::*func)( const T1 p1, const T2 p2 ), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    T1 p1; if ( !FromString( params[0], &p1 ) ) return false;
    T2 p2; if ( !FromString( params[1], &p2 ) ) return false;
    return (obj->*func)( p1, p2 );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3>
class CommandExecutor3 : public CommandExecutorWithChecker<TObj, bool (TObj::*)( const T1 p1, const T2 p2, const T3 p3 ), 3>
{
  OBJECT_BASIC_METHODS( CommandExecutor3 );
public:
  CommandExecutor3() {}
	CommandExecutor3( bool (TObj::*func)( const T1 p1, const T2 p2, const T3 p3 ), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    T1 p1; if ( !FromString( params[0], &p1 ) ) return false;
    T2 p2; if ( !FromString( params[1], &p2 ) ) return false;
    T3 p3; if ( !FromString( params[2], &p3 ) ) return false;
    return (obj->*func)( p1, p2, p3 );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3, typename T4>
class CommandExecutor4 : public CommandExecutorWithChecker<TObj, bool (TObj::*)( const T1 p1, const T2 p2, const T3 p3, const T4 p4 ), 4>
{
  OBJECT_BASIC_METHODS( CommandExecutor4 );
public:
  CommandExecutor4() {}
	CommandExecutor4( bool (TObj::*func)( const T1 p1, const T2 p2, const T3 p3, const T4 p4 ), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    T1 p1; if ( !FromString( params[0], &p1 ) ) return false;
    T2 p2; if ( !FromString( params[1], &p2 ) ) return false;
    T3 p3; if ( !FromString( params[2], &p3 ) ) return false;
    T4 p4; if ( !FromString( params[3], &p4 ) ) return false;
    return (obj->*func)( p1, p2, p3, p4 );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5>
class CommandExecutor5 : public CommandExecutorWithChecker<TObj, bool (TObj::*)( const T1 p1, const T2 p2, const T3 p3, const T4 p4, const T5 p5 ), 5>
{
  OBJECT_BASIC_METHODS( CommandExecutor5 );
public:
  CommandExecutor5() {}
	CommandExecutor5( bool (TObj::*func)( const T1 p1, const T2 p2, const T3 p3, const T4 p4, const T5 p5 ), TObj *obj ) : CommandExecutorWithChecker( func, obj ) { }

protected:
  virtual bool Process( const vector<string>& params )
  {
    T1 p1; if ( !FromString( params[0], &p1 ) ) return false;
    T2 p2; if ( !FromString( params[1], &p2 ) ) return false;
    T3 p3; if ( !FromString( params[2], &p3 ) ) return false;
    T4 p4; if ( !FromString( params[3], &p4 ) ) return false;
    T5 p5; if ( !FromString( params[4], &p5 ) ) return false;
    return (obj->*func)( p1, p2, p3, p4, p5 );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAIContainer::PFAIContainer( PFWorld* pWorld, NCore::ITransceiver *pTransceiver ) 
: PFWorldObjectBase( pWorld, 0 )
, transceiver( pTransceiver )
, currentLine( 0 )
, waitStep( 0 )
, logScriptEvents(false)
{
#ifndef _SHIPPING
  RegisterScriptCommands();
#endif
  
  luaScript = new PFScript(this);
  PFAIContainer::s_luaScript = luaScript;
  if (lua_State * L = luaScript->GetState())
  {
    // This is a bit long but right way to load library (not by direct call to luaopen_table)
    lua_pushcfunction(L, luaopen_table);
    lua_pushstring(L, "");
    lua_call(L, 1, 0);
#ifndef _SHIPPING
    lua_pushcfunction(L, luaopen_io);
    lua_pushstring(L, "");
    lua_call(L, 1, 0);
#endif
  }
  scriptSerializer.Init( luaScript );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::LoadScript( const vector<string>& _script )
{
  script = _script;
  currentLine = 0;
  waitStep = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseHero* PFAIContainer::GetLocalHero() const
{
	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !advScreen )
		return 0;

	PFWorld* world = advScreen->GetWorld();
  if ( !world )
    return 0;

  NWorld::PFPlayer* player = world->GetPlayer( advScreen->GetLocalPlayerID() );
  if ( !player )
    return 0;

  return player->GetHero();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseHero* PFAIContainer::FindHero( const char* hero, bool aliasEnabled /* = true */ ) const
{
  if ( !hero )
    return 0;

  if ( strcmp( "local", hero ) == 0 )
    return GetLocalHero();

  if ( aliasEnabled )
  {
    for ( vector<HeroAlias>::const_iterator iter = heroesAliases.begin(); iter != heroesAliases.end(); ++iter )
    {
      if ( iter->alias == string( hero ) )
      {
        return FindHero( iter->hero.c_str() );
      }
    }
  }

  if ( strlen( hero ) != 2 )
    return 0;

	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !advScreen )
		return 0;

	PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return 0;

  int n = 0;
  const int team = hero[0] - '0';
  const int id = hero[1] - '0';
  for( int i = 0; i < world->GetPlayersCount(); ++i )
  {
    PFPlayer* player = world->GetPlayer( i );
    if ( player->GetTeamID() == team )
    {
      if ( n == id )
        return player->GetHero();
      else
        ++n;
    }
  }

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFCreature* PFAIContainer::FindCreature( const char* creature ) const
{
  TCreeps::const_iterator pos = creeps.find( creature );
  if ( pos != creeps.end() )
  {
    return pos->second;
  }

  vector<string> parts;
  NStr::SplitString( creature, &parts, '_' );
  if ( parts[0] == "summon" && parts.size() == 3 && NStr::IsDecNumber( parts[2] ) )
  {
    PFBaseHero* hero = FindHero( parts[1].c_str() );
    NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Cannot find hero \"%s\"", parts[1].c_str() ), return 0 );
    int number = NStr::ToInt( parts[2] );
    PFBehaviourGroup* group = hero->GetSummonedGroup( NDb::SUMMONTYPE_PRIMARY );
    if ( number >= group->GetSize() )
    {
      number -= group->GetSize();
      group = hero->GetSummonedGroup( NDb::SUMMONTYPE_SECONDARY );
    }

    NI_DATA_VERIFY( number < group->GetSize(), NStr::StrFmt( "Hero \"%s\" has only %d summoned unit, %d is out of range",
      parts[0].c_str(), hero->GetSummonedGroup( NDb::SUMMONTYPE_PRIMARY )->GetSize() + hero->GetSummonedGroup( NDb::SUMMONTYPE_SECONDARY )->GetSize(),
      NStr::ToInt( parts[2] ) ), return 0 );

    struct GetNthFromRingFunctor
    {
      int number;
      PFSummonBehaviour* behaviour;
      GetNthFromRingFunctor( int _number ) : number( _number ), behaviour( 0 ) { }
      void operator()( PFSummonBehaviour* _behaviour )
      {
        if ( number == 0 )
        {
          behaviour = _behaviour;
        }
        --number;
      }
    } f( number );
    group->ForAllBehaviour( f );

    if ( IsValid( f.behaviour ) )
    {
      PFCreature* pCreature = dynamic_cast<PFCreature*>( f.behaviour->GetUnit().GetPtr() );
      return pCreature;
    }
  }

  return FindHero( creature );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFFlagpole* PFAIContainer::FindFlag(int roadIndex, int flagIndex) const
{
  NI_DATA_VERIFY( roadIndex >= 0, "Road index shouldn't be negative", return 0 );
  NI_DATA_VERIFY( flagIndex >= 0, "Flag index shouldn't be negative", return 0 );

  int numRoads = PFRoadFlagpole::GetNumRoads();
  NI_DATA_VERIFY( roadIndex < numRoads, 
    NStr::StrFmt( "Current map has only %d roads (0-%d), %d is out of range", 
      numRoads, numRoads - 1, roadIndex ), return 0 );

  PFFlagpole* pFlag  = PFRoadFlagpole::GetFirstFlagpole( NDb::FACTION_FREEZE, (NDb::ENatureRoad)roadIndex );

  if (pFlag)
  {
    for ( int i = 0; i < flagIndex; ++i )
    {
      NI_DATA_VERIFY( pFlag != 0, 
        NStr::StrFmt( "Current map has only %d flagpoles (0-%d) on road %d, %d is out of range", 
          i + 1, i, roadIndex, flagIndex ), return 0 );

      pFlag = pFlag->GetNextFlagpole( NDb::FACTION_FREEZE );
    }
  }

  return pFlag;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit* PFAIContainer::FindUnit( const char* unit ) const
{
  TUnits::const_iterator pos = units.find( unit );
  if ( pos != units.end() )
    return pos->second;

	vector<string> parts;
	NStr::SplitString( unit, &parts, '_' );
	if ( ( parts.size() == 2 ) && ( parts[1].length() == 2 ) )
	{
    if ( !NStr::IsDecDigit( parts[1][0] ) || !NStr::IsDecDigit( parts[1][1] ) )
    {
      return 0;
    }

    int roadIndex = parts[1][0] - '0';
    int index     = parts[1][1] - '0';

    if ( parts[0] == "flag" )
    {
      return FindFlag(roadIndex, index);
    }
    else if ( parts[0] == "tower" )
    {
      NI_DATA_VERIFY( index >= 0, "Tower index shouldn't be negative", return 0 );

      NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
      if ( !advScreen )
      {
        return 0;
      }
      PFWorld* world = advScreen->GetWorld();
      if ( !world )
      {
        return 0;
      }

      vector<PFAIWorld::BuildingsRoute>::iterator iFreezeRoute = world->GetAIWorld()->GetRoute( NDb::FACTION_FREEZE, (NDb::ERoute) roadIndex );
      vector<PFAIWorld::BuildingsRoute>::iterator iBurnRoute   = world->GetAIWorld()->GetRoute( NDb::FACTION_BURN,   (NDb::ERoute) roadIndex );

      int freezeTowersNum = 0;
      for ( int i = 0; i < iFreezeRoute->levels.size(); ++i )
      {
        freezeTowersNum += iFreezeRoute->levels[i].towersIDs.size();
      }

      int burnTowersNum = 0;
      for ( int i = 0; i < iBurnRoute->levels.size(); ++i )
      {
        burnTowersNum += iBurnRoute->levels[i].towersIDs.size();
      }

      const int towersNum = freezeTowersNum + burnTowersNum;
      NI_DATA_VERIFY( index < towersNum,
        NStr::StrFmt( "Current map has only %d towers (0-%d) on road %d, %d is out of range", towersNum, towersNum - 1, roadIndex, index ), return 0 );

      vector<PFAIWorld::BuildingsRoute>::iterator iRoute = ( index < freezeTowersNum ) ? iFreezeRoute : iBurnRoute;

      int towerIndex = ( index < freezeTowersNum ) ? index : burnTowersNum - ( index - freezeTowersNum ) - 1;

      CObjectBase* pObjectBase = world->GetObject( iRoute->GetTowerIDByIndex( towerIndex ) );
      NI_VERIFY( pObjectBase->GetTypeId() == PFTower::typeId, "Can't find tower", return 0 );
      return static_cast<PFTower*>( pObjectBase );
    }
  }

	return FindCreature( unit );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PF_Core::WorldObjectBase* PFAIContainer::FindObject( const char* obj ) const
{
  TObjects::const_iterator it = objects.find( obj );
  if ( it != objects.end() )
    return it->second;

  return FindUnit( obj );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::FindTalent( PFBaseHero* hero, const char* persistentId, int* level, int* slot ) const
{
  if ( strlen( persistentId ) == 2 && persistentId[0] >= '0' && persistentId[0] <= '9' && persistentId[1] >= '0' && persistentId[1] <= '9' )
  {
    *level = persistentId[0] - '0';
    *slot = persistentId[1] - '0';
    return hero->GetTalent( *level, *slot ) != 0;
  }

  *level = -1;
  *slot = -1;
  
  const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
  const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

  for ( int i = 0; i < levels; i++ )
  {
    for ( int j = 0; j < slots; j++ )
    {
      PFTalent* talent = hero->GetTalent( i, j );
      if ( talent && NStr::Cmp( talent->GetTalentDesc()->persistentId.c_str(), persistentId ) == 0 )
      {
        *level = i;
        *slot = j;
        return true;
      }
    }
  }

  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::BuildIdNameMap()
{
  objectIdToName.clear();

  for ( TCreeps::const_iterator it = creeps.begin(); it != creeps.end(); ++it )
  {
    PFBaseCreep* object = it->second.GetPtr();
    objectIdToName.insert( make_pair( object->GetWOID(), it->first ) );
  }

  for ( TUnits::const_iterator it = units.begin(); it != units.end(); ++it )
  {
    PFBaseUnit* object = it->second.GetPtr();
    objectIdToName.insert( make_pair( object->GetWOID(), it->first ) );
  }
  for ( TObjects::const_iterator it = objects.begin(); it != objects.end(); ++it )
  {
    PF_Core::WorldObjectBase* object = it->second.GetPtr();
    objectIdToName.insert( make_pair( object->GetObjectId(), it->first ) );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::FindObjectName( string& name, PF_Core::WorldObjectBase* object )
{
  name.clear();
  if (!object)
    return false;

  if ( PFBaseCreep* pCreep = dynamic_cast<PFBaseCreep*>(object) )
  {
    if ( pCreep->GetMasterUnit() )
    {
      object = pCreep->GetMasterUnit();
      name = "summon_";
    }
  }
  if ( PFBaseHero* pHero = dynamic_cast<PFBaseHero*>(object) )
  {
    if ( pHero->IsClone() && pHero->GetMasterUnit()->IsTrueHero() )
      object = pHero->GetMasterUnit();

    char pid[2] = {0,0};
    for( int i = 0; i < GetWorld()->GetPlayersCount(); ++i )
    {
      PFPlayer* player = GetWorld()->GetPlayer( i );
      int team = player->GetTeamID();
      if ( team < 0 )
        continue;
      if ( player->GetHero() == object )
      {
        name.resize(2,'\0');
        name[0] =( '0' + team );
        name[1]= ( '0' + pid[team] );
        return true;
      }
      ++pid[team];
    }
    return false;
  }

  int woid = object->GetObjectId();
  TObjectNames::iterator it = objectIdToName.find( woid );
  if ( it != objectIdToName.end() )
  {
    name += it->second;
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseConsumable( const char* hero, const char* item, 
                                  const char* unit /*= 0*/, float x /*= -1.0f*/, float y /*= -1.0f*/ )
{
  PFBaseHero* pHero = FindHero( hero );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero %s not found!", hero ), return false; );

  NDb::Ptr<NDb::Consumable> pDbConsumable = NDb::Get<NDb::Consumable>( NDb::DBID( item ) );
  NI_DATA_VERIFY( IsValid( pDbConsumable ), NStr::StrFmt( "Consumable \"%s\" not found!", item ), return false; );

  CObj<NWorld::PFConsumable> pConsumable = new NWorld::PFConsumable( pHero->GetWorld(), pHero, pDbConsumable );

  NWorld::Target target;
  if (unit)
  {
    if (PFBaseUnit * pUnit = FindUnit( unit ) )
    {
      target.SetUnit( pUnit );
    }
    else
    {
      return false;
    }
  }
  else if (x != -1.0f && y != -1.0f)
  {
    target.SetPosition( CVec3( x, y, 0.0f ) );
  }
  else
  {
    target.SetUnit( pHero );
  }

  pHero->UseConsumable( pConsumable, target, pHero->IsLocal() );

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::StepScript()
{
  NI_PROFILE_FUNCTION

  if ( luaScript )
    luaScript->Step();

  RemoveInvalidUnits();

  while ( currentLine < script.size() )
  {
    string line = script[currentLine];
    NStr::TrimBoth( line );

    bool inString = false;
    for( int i = 0; i < line.size(); ++i )
    {
      if ( line[i] == '"' )
      {
        inString = !inString;
        line.erase( i, 1 );
        --i;
      }
      else if ( inString && ( line[i] == ' '  ) )
      {
        line[i] = '©';
      }
    }

    vector<string> args;
    NStr::SplitString( line, &args, ' ' );
    string command = args[0];
    args.erase( args.begin() );

    for( int i = 0; i < args.size(); ++i )
    {
      NStr::ReplaceAllChars( &args[i], '©', ' ' );
    }

    if ( line.find( "//" ) != 0 && !line.empty() )
    {
      hash_map<string, CObj<CommandExecutor>>::iterator executor = commands.find( command );
      NI_DATA_VERIFY( executor != commands.end(), NStr::StrFmt( "Command \"%s\" not found (\"%s\")", command.c_str(), line.c_str() ), { script.clear(); currentLine = 0; waitStep = 0; return; } );

      switch ( executor->second->Process( line, args ) )
      {
      case CommandExecutor::COMMAND_WAIT:
        return;
      case CommandExecutor::COMMAND_FAILED:
        script.clear();
        currentLine = 0;
        waitStep = 0;
        return;
      }
    }

    ++currentLine;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::RemoveInvalidUnits()
{
  for( TCreeps::iterator it = creeps.begin(); it != creeps.end(); )
  {
    if ( IsUnitValid( it->second ) )
    {
      ++it;
    }
    else
    {
      deadObjectNames.insert( it->first );
      it = creeps.erase( it );
    }
  }

  for( TUnits::iterator it = units.begin(); it != units.end(); )
  {
    if ( IsUnitValid( it->second ) )
    {
      ++it;
    }
    else
    {
      deadObjectNames.insert( it->first );
      it = units.erase( it );
    }
  }

  for( TObjects::iterator it = objects.begin(); it != objects.end(); )
  {
    if ( IsValid( it->second ) )
    {
      ++it;
    }
    else
    {
      deadObjectNames.insert( it->first );
      it = objects.erase( it );
    }
  }

  for( TSimpleObjects::iterator it = simpleObjects.begin(); it != simpleObjects.end(); )
  {
    if ( IsValid( it->second ) )
    {
      ++it;
    }
    else
    {
      if(deadObjectNames.find(it->first) == deadObjectNames.end())
        deadObjectNames.insert( it->first );

      it = simpleObjects.erase( it );
    }
  }

  for( TObjectGroups::iterator it = objectGroups.begin(); it != objectGroups.end(); )
  {
    for( TObjectGroup::iterator itList = it->second.begin(); itList != it->second.end(); )
    {
      if (IsValid(*itList))
        ++itList;
      else
        itList = it->second.erase(itList);
    }

    if ( it->second.size() > 0 )
      ++it;
    else
      it = objectGroups.erase( it );
  }

  for ( TObjectNames::iterator it = objectIdToName.begin(); it != objectIdToName.end(); )
  {
    if ( IsValid( pWorld->GetObjectById(it->first) ) )
      ++it;
    else
      it = objectIdToName.erase( it );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( void ) )
{
  commands[command] = new CommandExecutor0<TObj>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( T1 p1 ) )
{
  commands[command] = new CommandExecutor1<TObj, T1>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2 ) )
{
  commands[command] = new CommandExecutor2<TObj, T1, T2>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3 ) )
{
  commands[command] = new CommandExecutor3<TObj, T1, T2, T3>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3, typename T4>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3, T4 p4 ) )
{
  commands[command] = new CommandExecutor4<TObj, T1, T2, T3, T4>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5>
void PFAIContainer::RegisterCommand( const char* command, bool (TObj::*func)( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 ) )
{
  commands[command] = new CommandExecutor5<TObj, T1, T2, T3, T4, T5>( func, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// script function ant theirs registration
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _SHIPPING

void PFAIContainer::RegisterScriptCommands()
{
  RegisterCommand( "debug_break",        &PFAIContainer::DebugBreak       );
  RegisterCommand( "exit",               &PFAIContainer::Exit             );
  RegisterCommand( "goto",               &PFAIContainer::Goto             );
  RegisterCommand( "wait_steps",         &PFAIContainer::WaitSteps        );
  RegisterCommand( "add_gold",           &PFAIContainer::AddGold          );
  RegisterCommand( "add_health",         &PFAIContainer::AddHealth        );
  RegisterCommand( "add_mana",           &PFAIContainer::AddMana          );
  RegisterCommand( "unit_stat",          &PFAIContainer::UnitStat         );
  RegisterCommand( "move_to",            &PFAIContainer::WorldScriptMoveTo);
  RegisterCommand( "teleport_to",        &PFAIContainer::TeleportTo       );
  RegisterCommand( "activate_talent",    &PFAIContainer::ActivateTalent   );
  RegisterCommand( "use_talent",         &PFAIContainer::UseTalent        );
  RegisterCommand( "use_talent_pos",     &PFAIContainer::UseTalentPos     );
  RegisterCommand( "use_talent_unit",    &PFAIContainer::UseTalentUnit    );
  RegisterCommand( "refresh_cd",         &PFAIContainer::RefreshCooldown  );
  RegisterCommand( "spawn_creep",        &PFAIContainer::SpawnCreep       );
  RegisterCommand( "kill_unit",          &PFAIContainer::KillUnit         );
  RegisterCommand( "kill_main_building", &PFAIContainer::KillMainBuilding );
  RegisterCommand( "timescale",          &PFAIContainer::SetTimeScale     );
  RegisterCommand( "attack_unit",        &PFAIContainer::AttackUnit       );
  RegisterCommand( "create_object",      &PFAIContainer::CreateObject     );
  RegisterCommand( "set_alias",          &PFAIContainer::SetHeroAlias     );
  RegisterCommand( "resurrect_hero",     &PFAIContainer::ResurrectHero    );
  RegisterCommand( "echo",               &PFAIContainer::SendMessage      );
  RegisterCommand( "suggest_buff",       &PFAIContainer::SuggestBuff      );
  RegisterCommand( "use_buff",           &PFAIContainer::UseBuff          );
  RegisterCommand( "use_item",           &PFAIContainer::UseItem          );
  RegisterCommand( "use_item_pos",       &PFAIContainer::UseItemPos       );
  RegisterCommand( "use_item_unit",      &PFAIContainer::UseItemUnit      );
  RegisterCommand( "portal_to",          &PFAIContainer::UsePortalTo      );
  RegisterCommand( "load_talents",       &PFAIContainer::LoadTalents      );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::DebugBreak()
{
  if ( IsDebuggerPresent() )
    __debugbreak();

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::Exit()
{
  NMainFrame::Exit();

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::Goto( const int line )
{
  NI_DATA_VERIFY( 0 <= line && line < script.size(), NStr::StrFmt( "Ivalid line in goto %d (total %d lines in script)", line, script.size() ), return true );
  currentLine = line;

  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::WaitSteps( const int step )
{
  if ( waitStep == 0 )
    waitStep = step;
  else
    --waitStep;
  return waitStep == 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::AddGold( const char* _hero, const int amount )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = hero;

  NGameX::CreateCheatCmd( "add_gold", NStr::IntToStr( amount ), data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::AddHealth( const char* _unit, const int amount )
{
  PFBaseUnit* unit = FindUnit( _unit );
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = unit;

  NGameX::CreateCheatCmd( "add_health", NStr::IntToStr( amount ), data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::AddMana( const char* _unit, const int amount )
{
  PFBaseUnit* unit = FindCreature( _unit );
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = unit;

  NGameX::CreateCheatCmd( "add_mana", NStr::IntToStr( amount ), data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::ResurrectHero( const char* _hero )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero \"%s\" not found", _hero ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = hero;

  NGameX::CreateCheatCmd( "resurrect_hero", data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::SuggestBuff( const char* buff_id )
{
  string buffId( buff_id );
  vector<wstring> params;
  params.push_back( NStr::ToUnicode( buffId ) );
  NWorld::ForceImpulsiveBuff( "suggest_buff", params );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseBuff()
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    advScreen->ActivateImpulsiveBuff();
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UnitStat( const char* _unit, const int stat, const int value )
{
  PFBaseUnit* unit = FindUnit( _unit );
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = unit;

  NGameX::CreateCheatCmd( "unit_stat", NStr::IntToStr( stat ), NStr::IntToStr( value ), data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::TeleportTo( const char* _unit, const float x, const float y )
{
  PFBaseUnit* unit = FindUnit( _unit );
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = unit;
  data.pickedPosition = CVec3( x, y, 0 );

  NGameX::CreateCheatCmd( "teleport_unit", data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::ActivateTalent( const char* _hero, const char* talent )
{
  PFBaseMaleHero* hero = dynamic_cast<PFBaseMaleHero*>( FindHero( _hero ) );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );
  NI_DATA_VERIFY( IsUnitValid( hero ), NStr::StrFmt( "Hero %s is dead", _hero ), return true );

  int _level, _slot;
  if ( !FindTalent( hero, talent, &_level, &_slot ) )
  {
    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Talent \"%s\" not found for hero \"%s\"", talent, _hero ) );
    return true;
  }

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = hero;
  NGameX::CreateCheatCmd( "add_gold", NStr::IntToStr( 99999 ), data );

  ActivateTalentImpl( hero, _level, _slot, false );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalent( const char* _hero, const char* talent )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );

  int level, slot;
  if ( !FindTalent( hero, talent, &level, &slot ) )
  {
    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Talent \"%s\" not found for hero \"%s\"", talent, _hero ) );
    return true;
  }

  UseTalentImpl(dynamic_cast<PFBaseMaleHero*>( hero ), level, slot);

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalentPos( const char* _hero, const char* talent, const float x, const float y )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Player %s not found", _hero ), return true );

  int level, slot;
  if ( !FindTalent( hero, talent, &level, &slot ) )
  {
    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Talent \"%s\" not found for hero \"%s\"", talent, _hero ) );
    return true;
  }

  UseTalentPosImpl(dynamic_cast<PFBaseMaleHero*>( hero ), level, slot, x, y);
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalentUnit( const char* _hero, const char* talent, const char* _unit )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );

  int level, slot;
  if ( !FindTalent( hero, talent, &level, &slot ) )
  {
    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Talent \"%s\" not found for hero \"%s\"", talent, _hero ) );
    return true;
  }

  PFBaseUnit* unit = FindUnit( _unit );
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit %s not found", _unit ), return true );

  UseTalentUnitImpl(dynamic_cast<PFBaseMaleHero*>( hero ), level, slot, unit);
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseItem( const char* hero, const char* item )
{
  PFBaseHero* pHero = FindHero( hero );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero %s not found", hero ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = pHero;
  data.pickedObject = pHero;

  NGameX::CreateCheatCmd( "use_consumable", item, data );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseItemPos( const char* hero, const char* item, const float x, const float y )
{
  PFBaseHero* pHero = FindHero( hero );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero %s not found", hero ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = pHero;
  data.pickedPosition = CVec3( x, y, 0.0f );

  NGameX::CreateCheatCmd( "use_consumable", item, data );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseItemUnit( const char* hero, const char* item, const char* unit )
{
  PFBaseHero* pHero = FindHero( hero );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero %s not found", hero ), return true );

  PFBaseUnit* pUnit = FindCreature( unit );
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit %s not found", unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = pHero;
  data.pickedObject = pUnit;

  NGameX::CreateCheatCmd( "use_consumable", item, data );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::KillUnit( const char* _unit )
{
  PFBaseUnit* unit = FindUnit( _unit );
  if ( !IsValid( unit ) )
    return true;
  //NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.pickedObject = unit;

  NGameX::CreateCheatCmd( "kill_unit", data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::KillMainBuilding( const int team )
{
  struct UnitCollectorFaction : NonCopyable
  {
	  UnitCollectorFaction( const NDb::EFaction _faction )
	  : faction( _faction )
	  {}

	  void operator()( PFLogicObject &obj )
	  {
      if ( obj.GetFaction() != faction || IsValid( result ) )
        return;

		  CDynamicCast<PFMainBuilding> building = &obj;
      if ( !IsValid( building ) )
        return;

      result = building;
	  }

	  NDb::EFaction faction;
	  CPtr<PFMainBuilding> result;
  } collector( (NDb::EFaction)team );

	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !advScreen )
		return 0;

	PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return 0;

  world->GetAIWorld()->ForAllUnits( collector );
  NI_DATA_VERIFY( IsValid( collector.result ), NStr::StrFmt( "Cannot find main building for faction %d", team ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.pickedObject = collector.result;

  NGameX::CreateCheatCmd( "kill_unit", data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::RefreshCooldown( const char* _hero )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );

  NGameX::CheatData data;
  data.cheater = GetLocalHero();
  data.selectedObject = hero;

  NGameX::CreateCheatCmd( "refresh_cd", data );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::SetHeroAlias( const char* _hero, const char* _alias )
{
  string alias( _alias );
  NI_DATA_VERIFY( ( alias.length() != 2 ) || !NStr::IsDecNumber( alias ), NStr::StrFmt( "%s is inappropriate alias for hero!", alias ), return true );

  string hero( _hero );
  NI_DATA_VERIFY( IsValid( FindHero( hero.c_str(), false ) ), NStr::StrFmt( "Hero %s not found", hero ), return true );

  for ( vector<HeroAlias>::iterator iter = heroesAliases.begin(); iter != heroesAliases.end(); ++iter )
  {
    if ( iter->alias == alias )
    {
      iter->hero = hero;
      return true;
    }
  }

  heroesAliases.push_back( HeroAlias( alias, hero ) );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::SetTimeScale( const float scale )
{
  NMainLoop::SetTimeScale( scale );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::CreateObject( const char* name, const char* dbid, const float x, const float y )
{
	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !advScreen )
		return false;

	PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return false;

  NI_DATA_VERIFY( units.find( name ) == units.end(), NStr::StrFmt( "Unit \"%s\" already registred", name ), return true );

  NDb::Ptr<NDb::GameObject> gameObj = NDb::Get<NDb::GameObject>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( gameObj ), NStr::StrFmt( "Object \"%s\" not found", dbid ), return true );

	NDb::AdvMapObject mapObj;
	mapObj.gameObject = gameObj;
	mapObj.offset = CVec3( x, y, 0.0f );

  CObj<PFLogicObject> obj;

	switch ( gameObj->GetObjectTypeID() )
	{
  case NDb::Tower::typeId:
    obj = new PFTower( world, mapObj);
    break;
  case NDb::Quarter::typeId:
    obj = new PFQuarters( world, mapObj );
    break;
  case NDb::MainBuilding::typeId:
    obj = new PFMainBuilding( world, mapObj );
    break;
  case NDb::Fountain::typeId:
    obj = new PFFountain( world, mapObj );
    break;
  case NDb::Shop::typeId:
    obj = new PFShop( world, mapObj );
    break;
  case NDb::Building::typeId:
    obj = new PFSimpleBuilding( world, mapObj );
    break;
	case NDb::MultiStateObject::typeId:
		obj = new PFMultiStateObject( world, mapObj );
		break;
	case NDb::TreeObject::typeId:
		obj = new PFTree( world, mapObj );
		break;
	default:
		NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Cannot create object with type \"%s\" from \"%s\"", gameObj->GetTypeName(), dbid ) );
		return true;
	}

	PFBaseUnit* unit = dynamic_cast<PFBaseUnit*>( obj.GetPtr() );
	if ( unit )
  {
    unit->SetVulnerable( true );
    units[name] = unit;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::LoadTalents( const char* _unit, const char* _talent_set_file )
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return true;
  if( PFBaseMaleHero* pMaleHero = dynamic_cast<PFBaseMaleHero*>(FindHero( _unit )) )
  {
    bool oldValue = NDb::GetDbResourceCache().EnableAssertionLoadingFiles( false );

    pMaleHero->LoadTalents(_talent_set_file);
    advScreen->SetLogicHero( advScreen->GetHero() );

    NDb::GetDbResourceCache().EnableAssertionLoadingFiles( oldValue );
  }
  return true;
}

#endif // #ifndef _SHIPPING


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalentImpl( PFBaseMaleHero* hero, int level, int slot )
{
  if ( !hero )
    return false;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  advScreen->SendGameCommand( CreateCmdUseTalent( hero, level, slot, NWorld::Target( hero, hero->GetPosition() ), true ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalentPosImpl( PFBaseMaleHero* hero, int level, int slot, float x, float y )
{
  if ( !hero )
    return false;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  advScreen->SendGameCommand( CreateCmdUseTalent( hero, level, slot, NWorld::Target( CVec3( x, y, 0 ) ), true ) );

  return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UseTalentUnitImpl( PFBaseMaleHero* hero, int level, int slot, PFBaseUnit* unit )
{
  if ( !hero || !unit)
    return false;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  advScreen->SendGameCommand( CreateCmdUseTalent( hero, level, slot, NWorld::Target( CPtr<PFBaseUnit>( unit ) ), true ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::ActivateTalentImpl( PFBaseMaleHero* hero, int _level, int _slot, bool addGold /*= true*/, bool activatePrevious /*= true*/ )
{
  if ( !hero )
    return false;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  PFTalent* desiredTalent = hero->GetTalent( _level, _slot );
  if ( !desiredTalent || desiredTalent->IsActivated() )
  {
    return false;
  }

  int gold = 0;
  vector<pair<int, int>> talents;

  if (activatePrevious)
  { 
    int devPoints = hero->GetDevPoints();
    for( int level = hero->GetTalentsSet()->GetLevelOfDevelopment(); level < NDb::KnownEnum<NDb::ETalentLevel>::sizeOf && level < _level; ++level )
    {
      for( int slot = 0; slot < NDb::KnownEnum<NDb::ETalentSlot>::sizeOf; ++slot )
      {
        PFTalent* talent = hero->GetTalent( level, slot );
        if ( !talent || talent->IsActivated() )
          continue;

        gold += talent->GetNaftaCost();
        talents.push_back( make_pair<int, int>( level, slot ) );
        devPoints += talent->GetDevPoints();
        if ( devPoints / NDb::TALENTS_POINTS_PER_LEVEL > level )
          break;
      }
    }
  }

  gold += desiredTalent->GetNaftaCost();
  talents.push_back( make_pair<int, int>( _level, _slot ) );

  if (addGold)
  {
    CPtr<PFBaseUnit> pSender = 0;
    hero->OnAddGold(pSender, gold, false);
  }

  for( vector<pair<int, int>>::const_iterator it = talents.begin(); it != talents.end(); ++it )
    advScreen->SendGameCommand( CreateCmdActivateTalent( hero, it->first, it->second ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::SpawnCreep( const char* name, const char* dbid, const float x, const float y, const int faction )
{
  return SpawnCreep( name, dbid, x, y, faction, 0 );
}

bool PFAIContainer::SpawnCreep( const char* name, const char* dbid, const float x, const float y, const int faction, const float yaw )
{
	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !advScreen )
		return 0;

	PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return 0;

  NI_DATA_VERIFY( creeps.find( name ) == creeps.end(), NStr::StrFmt( "Creep \"%s\" already registred", name ), return true );

  NDb::Ptr<NDb::AdvMapCreep> creepDb = NDb::Get<NDb::AdvMapCreep>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( creepDb ), NStr::StrFmt( "Creep \"%s\" not found", dbid ), return true );

  CObj<PFBaseCreep> creep;
  CQuat rot;
  rot.FromEulerAngles( yaw, 0, 0 );

  if ( faction == 0 )
    creep = new PFNeutralCreep( world, *creepDb, Placement( CVec3( x, y, 0 ), rot, CVec3( 1, 1, 1 ) ), false, -1.0f, 0, vector<CVec2>() );
  else
    creep = new PFCommonCreep( world, *creepDb, (NDb::EFaction)faction, Placement( CVec3( x, y, 0 ), rot, CVec3( 1, 1, 1 ) ), vector<CVec2>() );
  creeps[name] = creep;

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::ReplaceCreep( const char* name, const char* dbid, const int faction )
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return false;

  TCreeps::iterator oldIt = creeps.find( name );
  NI_DATA_VERIFY( oldIt != creeps.end(), NStr::StrFmt( "Creep \"%s\" is not registered", name ), return true );

  NDb::Ptr<NDb::AdvMapCreep> creepDb = NDb::Get<NDb::AdvMapCreep>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( creepDb ), NStr::StrFmt( "Creep \"%s\" not found", dbid ), return true );

  CPtr<PFBaseCreep> oldCreep = oldIt->second;
  
  Render::HDRColor recolor;
  if ( oldCreep->ClientObject() )
    recolor = oldCreep->ClientObject()->GetRecolor();
  Placement place;
  place.pos = oldCreep->GetPosition();
  place.rot = CQuat( CVec3(oldCreep->GetMoveDirection(), 0 ), true );

  PFBaseCreep* newCreep;
  if( PFCommonCreep* oldCreepCommon = dynamic_cast<PFCommonCreep*>(oldCreep.GetPtr()) )
  {
    PFCreepSpawner* spawner = oldCreepCommon->GetSpawner();
    newCreep = new PFCommonCreep( world, *creepDb, (NDb::EFaction)faction, place, vector<CVec2>(), 0, 0, spawner );
    spawner->InitializeCreep((PFCommonCreep*)newCreep, recolor);
  }
  else if (PFNeutralCreep* oldCreepNeutral = dynamic_cast<PFNeutralCreep*>(oldCreep.GetPtr()) ) 
  {
    PFNeutralCreepSpawner* spawner = oldCreepNeutral->GetSpawner();
    const vector<CVec2>* pPath = oldCreepNeutral->GetWaypoints();
    vector<CVec2> waypoints( pPath ? pPath->begin() : 0, pPath ? pPath->end() : 0 );
    newCreep = new PFNeutralCreep( world, *creepDb, place, false, oldCreepNeutral->GetWalkLimit(), spawner, waypoints );
    spawner->InitializeCreep((PFNeutralCreep*)newCreep, recolor);
    newCreep->Behaviour()->SetFaction( (NDb::EFaction)faction );
    newCreep->ChangeFaction( (NDb::EFaction)faction );
  }
  else 
    return false;

  newCreep->CopyFlagsFrom( oldCreep, true );

  newCreep->DoLevelups( oldCreep->GetNaftaLevel() - newCreep->GetNaftaLevel() );

  string groupName;
  if ( const char* gname =  FindObjectGroupName( oldCreep ) )
    groupName = string( gname );

  oldCreep->KillUnit( NULL, PFBaseUnit::UNITDIEFLAGS_FORCEREMOVECORPSE);
  RemoveInvalidUnits();

  RegisterObject( newCreep, name, groupName );
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::SendMessage( const char* message )
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    string str( message );
    str = "[script] " + str;
    wstring wstr = NStr::ToUnicode( str );
    advScreen->AddMessageToChat( wstr );
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::AttackUnit( const char* _hero, const char* _unit )
{
  PFBaseHero* hero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( hero ), NStr::StrFmt( "Hero %s not found", _hero ), return true );

  PFBaseUnit* unit = FindUnit( _unit );
  if ( !IsValid( unit ) )
    return true;
  NI_DATA_VERIFY( IsValid( unit ), NStr::StrFmt( "Unit \"%s\" not found", _unit ), return true );

	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( advScreen )
    advScreen->SendGameCommand( CreateCmdAttackTarget( hero, unit, true ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::AttackUnitToUnit( const char* _creature, const char* _target )
{
  PFCreature* creature = FindCreature( _creature );
  NI_DATA_VERIFY( IsValid( creature ), NStr::StrFmt( "Unit %s not found", _creature ), return true );

  PFBaseUnit* target = FindUnit( _target );
  NI_DATA_VERIFY( IsValid( target ), NStr::StrFmt( "Unit \"%s\" not found", _target ), return true );

  PushAttackState( creature, creature, target, true, false );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::WorldScriptMoveTo( const char* _unit, const float x, const float y )
{
  return MoveTo( _unit, x, y, 0.0f );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::MoveTo( const char* _unit, const float x, const float y, const float dist )
{
	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return true;

  if ( PFBaseHero* hero = FindHero( _unit ) )
    advScreen->SendGameCommand( CreateCmdMoveHero( hero, CVec2( x, y ), true ) );
  else if ( PFCreature* pCreature = FindCreature( _unit ) )
    pCreature->MoveTo( CVec2( x, y ), dist );
  else
  {
    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Unit \"%s\" not found", _unit ) );
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::UsePortalTo( const char* _unit, const float x, const float y )
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return true;

  if( PFBaseMaleHero* pMaleHero = dynamic_cast<PFBaseMaleHero*>(FindHero( _unit )) )
  {
    if (NWorld::PFTalent *pTalent = pMaleHero->GetPortal())
    {
      if (pTalent->IsActivated() && pTalent->CanBeUsed())
      {
        advScreen->SendGameCommand( CreateCmdUsePortal( pMaleHero, Target( CVec3( x, y, 0 ) ), true ) );
      }
    }
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::HeroRaiseFlag( const char* _hero, const char* _flag )
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  PFBaseHero* pHero = FindHero( _hero );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero\"%s\" not found", _hero ), return true );

  PFFlagpole* pFlagpole = dynamic_cast<PFFlagpole*>(FindUnit( _flag ));
  NI_DATA_VERIFY( IsValid( pFlagpole ), NStr::StrFmt( "Flagpole \"%s\" not found", _flag ), return true );

  advScreen->SendGameCommand( CreateCmdRaiseFlag( pHero, pFlagpole, true ) );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld
