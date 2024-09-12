#include "stdafx.h"

#include "PFAIContainer.h"
#include "PFAIController.h"
#include "PFSeriesAIController.h"
#include "PFMaleHero.h"
#include "PFTalent.h"
#include "AdventureScreen.h"
#include "System/FileSystem/FileUtils.h"
#include "PFMainBuilding.h"
#include "Minimap.h"


namespace NWorld
{

  bool PFAIContainer::CaptureTheFlag(const char *flag, NDb::EFaction faction, bool pickup)
  {
    PFFlagpole* pFlagpole = dynamic_cast<PFFlagpole*>(FindUnit( flag ));
    NI_DATA_VERIFY( IsValid( pFlagpole ), NStr::StrFmt( "Flagpole \"%s\" not found", flag ), return true );

    pFlagpole->Reset();
    PFBaseUnit* pUnit = NULL;

    if(pickup)
    {
        pFlagpole->OnStartRaise( 0, 0.0f );
        pFlagpole->OnRaise(faction, pUnit);
    } 
    else
    {
      pFlagpole->OnCancelRaise();
      pFlagpole->OnDropFlag(pUnit);
    }

    return true;
  }

bool PFAIContainer::Step( float timeDelta )
{
  NI_PROFILE_FUNCTION;

  for( vector<CObj<IPFAIController>>::iterator it = controllers.begin(); it != controllers.end(); ++it )
  {
    (*it)->Step( timeDelta );
  }
  StepScript();
  return true;
}

IPFAIController* PFAIContainer::Find( const PFBaseHero* pUnit ) const
{
  for ( int i = 0; i < controllers.size(); i++ )
  {
    if ( controllers[i]->GetHero() == pUnit )
    {
      return controllers[i];
    }
  }
  return NULL;
}

IPFAIController* PFAIContainer::Add( PFBaseHero* pUnit, int lineNumber )
{
  IPFAIController* ctl = Find( pUnit );
  if ( ctl )
  {
    return ctl;
  }

  // Calculate road's waypoints shift for heroes to go on different parts of the road

  int shift = 0; // No shift by default (apply to first hero on the road and each third)

  // This loop checks if we already have heroes from the same faction on that road and make a shift if needed
  for (int i = 0; i < controllers.size(); i++)
  {
    if (controllers[i]->GetLineNumber() == lineNumber
      && pUnit->GetFaction() == controllers[i]->GetHero()->GetFaction())
    {
      // Calculate shift flag according to the following sequence: 0, 1, -1, 0, 1, -1 ...
      // Where each additional hero on the same road will get the next number from that sequence
      shift = ((shift + 2) % 3) - 1;
    }
  }

  ctl = new PFAIController( pUnit, transceiver, lineNumber, shift );
  controllers.push_back( ctl );
  return ctl;
}
///////////////////////////////////////////////////////////////////////////////
IPFSeriesAIController * PFAIContainer::AddSeriesController( PFBaseHero* pUnit, bool lvlUpAvailable )
{
  IPFAIController* ctl = Find( pUnit );
  if ( ctl )
  {
    if ( IPFSeriesAIController *sctl = dynamic_cast<IPFSeriesAIController*>(ctl) )
      return sctl;
    else 
      Remove( pUnit );
  }
  PFSeriesAIController *sctl = new PFSeriesAIController( pUnit, transceiver, lvlUpAvailable );
  controllers.push_back( sctl );
  return sctl;
}


void PFAIContainer::OnMinimapSignal( PFBaseHero* pSender, PFBaseUnit* pSelected, const Target& target )
{
  PFBaseHero* pSelectedHero = dynamic_cast<PFBaseHero*>(pSelected);
  if ( pSelectedHero && pSelectedHero->GetFaction() == pSender->GetFaction()  )
  {
    if ( IPFAIController* ctl = Find( pSelectedHero ) )
    {
      ctl->OnMinimapSignal( target, true );
      return;
    }
  }
  for ( int i = 0; i < controllers.size(); i++ )
  {
    if ( controllers[i]->GetHero()->GetFaction() != pSender->GetFaction() )
      continue;

    if ( controllers[i]->OnMinimapSignal( target, false ) )
      return;
  }
}


///////////////////////////////////////////////////////////////////////////////
//	PFAIContainer
///////////////////////////////////////////////////////////////////////////////

bool PFAIContainer::Remove( PFBaseHero* pUnit )
{
  for ( int i = 0; i < controllers.size(); i++ )
  {
    if ( controllers[i]->GetHero() == pUnit )
    {
      controllers[i]->StopHero();
      if ( PFFsm *fsm_ctl = dynamic_cast<PFFsm*>(controllers[i].GetPtr()) )
        fsm_ctl->Cleanup(true);

      controllers.eraseByIndex(i);
      return true;
    }
  }
  return false;
}

void PFAIContainer::RemoveAll()
{
  for ( int i = 0; i < controllers.size(); i++ )
  {
    controllers[i]->StopHero();
    
    if ( PFFsm *fsm_ctl = dynamic_cast<PFFsm*>(controllers[i].GetPtr()) )
      fsm_ctl->Cleanup(true);
  }

  controllers.clear();
}


void PFAIContainer::RegisterScriptPath( const string &scriptName, const NDb::ScriptPath* gameObject )
{
  NI_DATA_VERIFY(scriptPaths.find(scriptName) == scriptPaths.end(), NStr::StrFmt("Duplicate script path name found: %s", scriptName ), return );
    
  scriptPaths.insert( TScriptPaths::value_type(scriptName, gameObject->path) );
}
const vector<CVec2>* PFAIContainer::GetScriptPath( const string &scriptName )
{
  TScriptPaths::const_iterator it = scriptPaths.find(scriptName);
  return it == scriptPaths.end() ? NULL : &(it->second);

}

void PFAIContainer::RegisterPolygonArea( string scriptName, const NDb::ScriptPolygonArea* area )
{
  NI_DATA_VERIFY(scriptPolyAreas.find(scriptName) == scriptPolyAreas.end(), NStr::StrFmt("Duplicate script polygon area name found: %s", scriptName ), return );

  scriptPolyAreas.insert( TScriptPolyAreas::value_type(scriptName, area) );
}



PFAIContainer::MinimapIcon::MinimapIcon( NDb::EMinimapIcons _icon, float _x, float _y, NDb::EUnitType _unitType, NDb::EFaction _faction )
: PF_Core::IUpdateable( true ), icon(_icon), x(_x), y(_y), unitType(_unitType), faction(_faction )
{
}

void PFAIContainer::MinimapIcon::Update( float timeDelta )
{
  if (NGameX::AdventureScreen const * pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (NGameX::Minimap *pMinimap = pAdvScreen->GetMinimap())
    {
      pMinimap->AddObject(unitType, faction, CVec3( x, y, 0.0f ), icon );
    }
  }
}

void PFAIContainer::PlaceMinimapIcon( const char* iconName, NDb::EMinimapIcons icon, float x, float y, NDb::EUnitType unitType )
{
  NI_VERIFY( minimapIcons.find( iconName ) == minimapIcons.end(), NStr::StrFmt("Minimap icon \"%s\" already exists", iconName ), return );
  
  minimapIcons[iconName] = new MinimapIcon( icon, x, y, unitType, NDb::FACTION_NEUTRAL );
}

void PFAIContainer::RemoveMinimapIcon( const char* iconName )
{
  TMinimapIcons::iterator it = minimapIcons.find( iconName );
  if ( it != minimapIcons.end() )
  {
    it->second->Unsubscribe();
    minimapIcons.erase( it );
  }
}

///////////////////////////////////////////////////////////////////////////////
//	Console commands
///////////////////////////////////////////////////////////////////////////////

// Helper function
static PFBaseHero *GetObject()
{
  PFBaseHero* selectedObject = NULL;
#ifndef VISUAL_CUTTED
  // based on CheatCommandProxy()
  if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    int localPlayerId = pAdvScreen->GetLocalPlayerID();
    selectedObject = dynamic_cast<NWorld::PFBaseHero*>( pAdvScreen->GetCurrentSelectedObject() );
    if ( !selectedObject )
    {
      NWorld::PFPlayer* pLocalPlayer = pAdvScreen->GetWorld()->GetPlayer( localPlayerId );
      selectedObject = pLocalPlayer ? pLocalPlayer->GetHero() : NULL;
    }
  }
#endif
  return selectedObject;
}

bool CommandAttachAI( const char *name, const vector<wstring> &params )
{
  // get unit
  PFBaseHero *pUnit = GetObject();
  if ( !pUnit )
  {
    DebugTrace("You must select unit first!");
    return false;
  }

  // get or create AI container
  PFWorld *pWorld = pUnit->GetWorld();
  PFAIContainer* pCont = pWorld->GetAIContainer();
  NI_ASSERT( pCont, "No AI container present" );

  // check: whether AI object attached to unit
  IPFAIController* pCtl = pCont->Find( pUnit );
  if ( pCtl )
  {
    DebugTrace("Unit already controlled by AI");
    return false;
  }

  // create controller
  int lineNumber = RANDOM_LINE;
  if ( params.size() > 0 )
  {
    lineNumber = (int) NGlobal::VariantValue( params[0] ).GetFloat();
  }
  pCont->Add( pUnit, lineNumber );

  return true;
}

bool CommandDetachAI( const char* name, const vector<wstring> &params )
{
  // get unit
  PFBaseHero* pUnit = GetObject();
  if ( !pUnit )
  {
    DebugTrace( "You must select unit first!" );
    return false;
  }

  // get AI container
  PFWorld* pWorld = pUnit->GetWorld();
  PFAIContainer* pCont = pWorld->GetAIContainer();
  NI_ASSERT( pCont, "No AI container present" );

  // remove controller
  if ( !pCont->Remove( pUnit ) )
  {
    DebugTrace( "Unit not controlled by AI" );
    return false;
  }

  return true;
}

bool GetTalentId( const char* name, const vector<wstring>& params)
{
  if ( params.size() < 1 || params.size() > 2 || params[0].size() != 2 || ( params.size() == 2 && params[1].size() != 2 ) )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << "[<filename>] <leve><slot>" << endl;
    return true;
  }

  NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance();
  if ( !pAdvScreen )
  {
    return false;
  }
  PFWorld* pWorld = pAdvScreen->GetWorld();
  if ( !pWorld )
  {
    return false;
  }

  PFBaseHero* hero = 0;
  if ( params.size() == 2 )
  {
    int n = 0;
    const int team = params[0][0] - L'0';
    const int id = params[0][1] - L'0';
    for( int i = 0; i < pWorld->GetPlayersCount(); ++i )
    {
      PFPlayer* player = pWorld->GetPlayer( i );
      if ( player->GetTeamID() == team )
      {
        if ( n == id )
        {
          hero = player->GetHero();
          break;
        }
        else
          ++n;
      }
    }
    if ( !hero )
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "\"" << params[0] << "\"" << " is not valid hero name" << endl;
      return true;
    }
  }
  else
  {
    hero = dynamic_cast<PFBaseHero*>( pAdvScreen->GetSelectedObject().GetPtr() );
    if ( !hero )
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Currently selected object should be hero" << endl;
      return true;
    }
  }

  const int level = params[params.size() - 1][0] - '0';
  const int slot = params[params.size() - 1][1] - '0';

  PFTalent* talent = hero->GetTalent( level, slot );
  if ( !talent )
  {
    systemLog( NLogg::LEVEL_ASSERT ) << "\"" << params[params.size() - 1] << "\"" << " is not valid talent name" << endl;
    return true;
  }

  systemLog( NLogg::LEVEL_MESSAGE ) << "\"" << talent->GetTalentDesc()->persistentId << "\"" << endl;

  return true;
}


bool RunScript( const char* name, const vector<wstring>& params)
{
  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << "<filename>" << endl;
    return true;
  }

  NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance();
  if ( !pAdvScreen )
  {
    return false;
  }
  PFWorld* pWorld = pAdvScreen->GetWorld();
  if ( !pWorld )
  {
    return false;
  }
  PFAIContainer* pCont = pWorld->GetAIContainer();
  if ( !pCont )
  {
    return false;
  }

  string fileName = NFile::GetFullName( NStr::ToMBCS( params[0] ) );
  CObj<FileStream> stream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_DATA_VERIFY( IsValid( stream ) && stream->IsOk(), NStr::StrFmt( "Cannot open file \"%s\"", fileName ), return true );
  NI_DATA_VERIFY( stream->GetSize() > 0, NStr::StrFmt( "Script file \"%s\" is empty", fileName ), return true );

  string content;
  content.resize( stream->GetSize() );
  stream->Read( &(content[0]), stream->GetSize() );

  vector<string> script;
  NStr::SplitString( content.c_str(), &script, '\n' );

  pCont->LoadScript( script );
  return true;
}


///////////////////////////////////////////////////////////////////////////////
//	Debugging
///////////////////////////////////////////////////////////////////////////////

#ifndef _SHIPPING

static int g_showLabels = 0;
// Values: 1=show all, 2=show selected
REGISTER_VAR( "ai_labels", g_showLabels, STORAGE_NONE );

//BEGIN_DEBUG_CB_TABLE(PFAIContainer)
//	DEBUG_CB_ON_VARIABLE_NOT_VALUE(&g_showLabels, 0, &PFAIContainer::ShowDebug)
//END_DEBUG_CB_TABLE()

void PFAIContainer::ShowDebug( Render::IDebugRender* pRender ) const
{
  PFBaseHero* pSelected = GetObject();
  for ( int i = 0; i < controllers.size(); i++ )
  {
    IPFAIController* ctl = controllers[i];
    if ( !IsValid( ctl->GetHero() ) )
    {
      continue;
    }

    const PFBaseHero* pUnit = ctl->GetHero();
    if ( g_showLabels == 2 && pUnit != pSelected )
    {
      continue;
    }

    char buf[256];
    strcpy_s( buf, pUnit->GetDebugDescription() );
    char *s = strrchr( buf, '/' );
    if ( s )
    {
      *s = 0;
    }
    s = strrchr( buf, '/' );
    s = s ? s+1 : buf;

    const char* stateName = ctl->GetCurrentStateName();
    pRender->DrawText3D( NStr::StrFmt(
      "%s (%s)\nstate[%d]=%s\nwarFront=%.1f", 
      s, NDb::EnumToString( pUnit->GetFaction() ),
      ctl->GetStackSize(),
      stateName ? stateName : "<unknown>",
      0 /*ctl->warFrontTimeDist*/ ),
      pUnit->GetVisualPosition3D() + CVec3(0,0,8), 14, Render::Color( 255,255,255 )
      );
  }
}
#endif // _SHIPPING

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// objects finders
template<class UnitType>
struct UnitCollectorFaction : NonCopyable
{
  UnitCollectorFaction( vector<UnitType*>& _objects, NDb::EFaction _faction )
    : objects( _objects )
    , faction( _faction )
  {}

  void operator()( PFLogicObject &baseUnit )
  {
    CDynamicCast<UnitType> unit = &baseUnit;
    if ( IsValid( unit ) && unit->GetFaction() == faction )	// and faction
    {
      objects.push_back( unit );
    }
  }

  NDb::EFaction      faction;
  vector<UnitType*>& objects;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FindQuarters( PFWorld* pWorld, NDb::EFaction faction, vector<PFQuarters*>& objects )
{
  UnitCollectorFaction<PFQuarters> collector( objects, faction );
  pWorld->GetAIWorld()->ForAllUnits( collector );
  return objects.size() > 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FindMainBuildings( PFWorld* pWorld, NDb::EFaction faction, vector<PFMainBuilding*>& objects )
{
  UnitCollectorFaction<PFMainBuilding> collector( objects, faction );
  pWorld->GetAIWorld()->ForAllUnits( collector );
  return objects.size() > 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FindShop( PFWorld* pWorld, NDb::EFaction faction, vector<PFShop*>& objects )
{
  UnitCollectorFaction<PFShop> collector( objects, faction );
  pWorld->GetAIWorld()->ForAllUnits( collector );
  return objects.size() > 0;
}

} // namespace

REGISTER_WORLD_OBJECT_NM(PFAIContainer, NWorld)

REGISTER_DEV_CMD( run_script, NWorld::RunScript );
REGISTER_DEV_CMD( get_talentid, NWorld::GetTalentId );

REGISTER_DEV_CMD( attach_ai, NWorld::CommandAttachAI );
REGISTER_DEV_CMD( detach_ai, NWorld::CommandDetachAI );