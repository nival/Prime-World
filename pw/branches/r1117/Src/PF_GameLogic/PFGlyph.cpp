#include "stdafx.h"
#include "PFGlyph.h"
#include "PFMaleHero.h"
#include "TileMap.h"
#include "PFAbilityData.h"
#include "PFAIWorld.h"
#include "PFAdvMapObject.h"
#include "PFGlyphManager.h"
#include "PFAIContainer.h"

#include "WarFog.h"

#ifndef VISUAL_CUTTED
#include "PFClientChest.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "../System/RandomGen.h"

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFGlyphSpawner::PFGlyphSpawner( const CPtr<PFWorld>& pWorld, const NDb::AdvMapObject &dbObject )
: PFWorldObjectBase( pWorld, 1 )
, position( dbObject.offset.GetPlace().pos )
, spawnOffset(-1.0f)
, hidden(false)
, lastGlyph(0)
{ 
  pDesc = dynamic_cast<const NDb::GlyphSpawner*>( dbObject.gameObject.GetPtr() );

  if(PFAIWorld const* pAIWorld = pWorld ? pWorld->GetAIWorld() : NULL)
    pManager = pAIWorld->GetGlyphsManager();
  if( !IsValid(pManager) )
  {
    NI_ALWAYS_ASSERT("Failed to retreive glyphs manager!");
    return;
  }

  scriptName = dbObject.scriptName;
  NDb::GlyphSettings const& settings = GetSettings();
  spawnOffset = pWorld->GetRndGen()->Next(settings.minNormalSpawnDelay, settings.maxNormalSpawnDelay);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::GlyphSettings& NWorld::PFGlyphSpawner::GetSettings() const
{
  if ( pDesc->useGlyphManager )
    return pManager->GetSettings();
  return pDesc->settings;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPtr<NWorld::PFGlyph> PFGlyphSpawner::CreateGlyph( CVec3 const& position )
{
  CPtr<NWorld::PFGlyph> glyph;

  if ( pDesc->useGlyphManager )
  {
    glyph = pManager->CreateGlyph( position );
  }
  else 
  {
    const NDb::GlyphsDB* glyphs = pDesc->glyphs;
    if ( !glyphs )
      glyphs = pManager->GetGlyphsDB();

    const NDb::GlyphEntry* pGlyphEntry = 0;

    if ( pDesc->settings.spawnMode == NDb::GLYPHSPAWNMODE_RANDOMWEIGHT )
    {
      struct WeightGetter
      {
        int operator()( const NDb::GlyphEntry& item ) const
        {
          return item.weight;
        }
      } wg;

      pGlyphEntry = &(GetWorld()->GetRndGen()->RollFromContainerByWeight( glyphs->glyphs, wg ));
    }
    else if ( pDesc->settings.spawnMode == NDb::GLYPHSPAWNMODE_ORDERED )
    {
      pGlyphEntry = &(glyphs->glyphs[lastGlyph]);
      lastGlyph = ( lastGlyph + 1 ) % glyphs->glyphs.size();
    }

    NI_DATA_VERIFY( pGlyphEntry && pGlyphEntry->glyph, "Invalid glyph entry", return 0 );

    glyph = new PFGlyph( GetWorld(), pGlyphEntry->glyph, position );
  }

  if ( !glyph )
    return glyph;

  glyph->Hide( hidden );

  if ( !scriptName.empty() )
  {
    string name = scriptName + "_glyph";
    glyph->SetScriptName( name );
    GetWorld()->GetAIContainer()->RegisterObject( glyph, name, "" );
  }

  return glyph;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyphSpawner::Hide(bool hide)
{
  if ( hidden == hide )
    return;
  hidden = hide;
  if ( IsValid(pSpawnedGlyph) )
    pSpawnedGlyph->Hide( hidden );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFGlyphSpawner::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;

  if(IsValid(pManager) && !IsValid(pSpawnedGlyph) )
  {
    NDb::GlyphSettings const& settings = GetSettings();

    if( spawnOffset < 0.0f )
    {
      spawnOffset = pWorld->GetRndGen()->Next(settings.minAfterPickupSpawnDelay, settings.maxAfterPickupSpawnDelay);
    }
    else
    {
      spawnOffset -= dtInSeconds;
      if( spawnOffset < EPS_VALUE)
      {
        if( pSpawnedGlyph = CreateGlyph( position ) )
        {
          spawnOffset = -1.0f;
        }
        else
        {
          spawnOffset = pWorld->GetRndGen()->Next(settings.minNormalSpawnDelay, settings.maxNormalSpawnDelay);
          spawnOffset = max(settings.minNormalSpawnDelay, spawnOffset - settings.spawnAttemptDelayDecrease);   
        }
      } 
    }
  }

  return PFWorldObjectBase::Step(dtInSeconds);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NAMEMAP_BEGIN(PFGlyph)
NAMEMAP_FUNC_RO(name, &PFGlyph::GetName);
NAMEMAP_END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFGlyph::PFGlyph( const CPtr<PFWorld>& pWorld, const NDb::Ptr<NDb::Glyph>& pGlyphDesc, const CVec3& position )
: PFPickupableObjectBase( pWorld, position, pGlyphDesc->gameObject )
, pDesc(pGlyphDesc)
, visUnitID1( -1 )
, visUnitID2( -1 )
, enabled( true )
, hidden( false )
, glyphNumber(-1)
{
  NI_VERIFY( pGlyphDesc->gameObject, "Need gameObject to create Glyph!", return; );
  CreateClientObject<NGameX::PFClientGlyph>( NGameX::PFClientLogicObject::CreatePars(pWorld->GetScene(), BADNODENAME, pGlyphDesc->gameObject.GetPtr()), pGlyphDesc->color );

  const NDb::AdvMapSettings* desc = IsValid(GetWorld()->GetMapDescription()->mapSettings) ? GetWorld()->GetMapDescription()->mapSettings 
                                                                                          : GetWorld()->GetMapDescription()->map->mapSettings;
  if ( desc && IsValid(desc->overrideGlyphSettings) )
  {
    for ( int i = 0; i < desc->overrideGlyphSettings->glyphs->glyphs.size(); i++ )
    {
      if ( pDesc->GetDBID() == desc->overrideGlyphSettings->glyphs->glyphs[i].glyph->GetDBID() )
      {
        glyphNumber = i;
        break;
      }
    }
  }
  else
  {
    NDb::Ptr<NDb::SessionRoot> pRoot = NDb::SessionRoot::GetRoot();
    NDb::Ptr<NDb::GlyphsDB> pDBGlyphs = pRoot->logicRoot->glyphsDB;
    for ( int i = 0; i < pDBGlyphs->glyphs.size(); i++ )
    {
      if ( pDesc->GetDBID() == pDBGlyphs->glyphs[i].glyph->GetDBID() )
      {
        glyphNumber = i;
        break;
      }
    }
  }

  NDb::AdvMapObject dbObject;
  dbObject.gameObject = pGlyphDesc->gameObject;
  dbObject.offset = CPlacement( position, QNULL, CVec3(1.f, 1.f, 1.f));

  vector<SVector> occupiedTiles;

  TileMap * tileMap = GetWorld()->GetTileMap();

  MarkObject(tileMap, dbObject, occupiedTiles);
  tileMap->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);

  float fObjectSize = pGlyphDesc->gameObject->lockMask.tileSize;

  if (fObjectSize <= 0)
  {
    NDb::SingleStateObject const * pSingleStateObject; 
    pSingleStateObject = dynamic_cast<NDb::SingleStateObject const *>(pGlyphDesc->gameObject.GetPtr());
    NI_VERIFY( pSingleStateObject, "Failed to downcast GameObject of Glyph to SingleStateObject!", return; );

    NI_DATA_VERIFY( pSingleStateObject->sceneObject && 
      pSingleStateObject->sceneObject->attached.size() > 0 &&
      pSingleStateObject->sceneObject->attached[0].component &&
      pSingleStateObject->sceneObject->attached[0].component->attached.size() > 0 &&
      pSingleStateObject->sceneObject->attached[0].component->attached[0].component, 
      "Failed to access attached object in SceneObject of Glyph!", return; );

    NDb::DBStaticSceneComponent const * pdbStaticSceneComponent;
    pdbStaticSceneComponent = dynamic_cast<NDb::DBStaticSceneComponent const *>(pSingleStateObject->sceneObject->attached[0].component->attached[0].component.GetPtr());
    NI_VERIFY( pdbStaticSceneComponent, "Failed to downcast attached component of Glyph to DBStaticSceneComponent!", return; );

    NDb::AABB const * pAABB = &pdbStaticSceneComponent->aabb;

    if (pAABB->maxX != -666 && pAABB->minX != 666 && pAABB->maxY != -666 && pAABB->minY != 666)
    {
      fObjectSize = sqrt( fabs2(pAABB->maxX - pAABB->minX) + fabs2(pAABB->maxY - pAABB->minY) );
    }
  }

  const float fTileSize   = tileMap->GetTileSize();

  int objectTileSize    = (fTileSize == 0.0f) ? (0) : (ceil( fObjectSize / fTileSize ));
  int objectDynTileSize = fObjectSize;
  float objectSize      = fObjectSize * fTileSize; // rounded up to tile size

  SetObjectSizes(objectSize, objectTileSize, objectDynTileSize);

  OpenWarFog();
  // Warfog
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyph::Reset()
{
  PFPickupableObjectBase::Reset();
  CreateClientObject<NGameX::PFClientGlyph>( NGameX::PFClientLogicObject::CreatePars(GetWorld()->GetScene(), BADNODENAME, pDesc->gameObject.GetPtr()), pDesc->color );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyph::Hide(bool hide)
{
  if ( hidden == hide )
    return;

  hidden = hide;
  if ( hide )
    CloseWarFog();
  else
    OpenWarFog();

  UpdateHiddenState(!hidden);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyph::OpenWarFog()
{
  if ( pDesc->openWarFogRadius > 0.0f )
  {
    TileMap * tileMap = GetWorld()->GetTileMap();

    SVector pos = tileMap->GetTile(GetPosition().AsVec2D());
    int tileRadius = tileMap->GetLenghtInTiles( pDesc->openWarFogRadius );

    visUnitID1 = GetWorld()->GetFogOfWar()->AddObject(pos, FCTN_A, tileRadius);
    visUnitID2 = GetWorld()->GetFogOfWar()->AddObject(pos, FCTN_B, tileRadius);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyph::CloseWarFog()
{
  if ( visUnitID1 >= 0 )
    GetWorld()->GetFogOfWar()->RemoveObject(visUnitID1);
  if ( visUnitID2 >= 0 )
    GetWorld()->GetFogOfWar()->RemoveObject(visUnitID2);
  visUnitID1 = visUnitID2 = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFGlyph::OnPickedUp( PFBaseUnit* pPicker )
{
  pPicker->OnGlyphPickUp( this );
  PFBaseUnitPickupEvent ev( NDb::BASEUNITEVENT_PICKUP, true, glyphNumber, scriptName );
  pPicker->EventHappened( ev );
  if ( ev.NeedActivate() )
    pPicker->UseExternalAbility( pDesc.GetPtr(), Target(pPicker) );
}

void PFGlyph::OnDie()
{
  CloseWarFog();

  PFLogicObject::OnDie();
}


bool PFGlyph::CanBePickedUpBy( const PFBaseUnit* pPicker ) const
{
  if ( !enabled )
    return false;

  return PFPickupableObjectBase::CanBePickedUpBy( pPicker );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN( PFNatureGlyph )
NAMEMAP_FUNC_RO( name, &PFNatureGlyph::GetName );
NAMEMAP_END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFNatureGlyph::PFNatureGlyph( const CPtr<PFBaseMaleHero>& targetHero, NDb::ERoute routeID, const CPtr<PFWorld>& pWorld, const NDb::Ptr<NDb::GameObject> _gameObject, const CVec3& position ) 
: PFPickupableObjectBase(pWorld, position, _gameObject)
, targetHero(targetHero)
, routeID(routeID)
, bVisible(true)
, gameObject(_gameObject)
{
  NI_VERIFY( gameObject && dynamic_cast<const NDb::SingleStateObject*>(gameObject.GetPtr()), "Game object must be a SingleStateObject", return; );

  NDb::AdvMapObject dbObject;
  dbObject.gameObject = gameObject;
  dbObject.offset     = CPlacement( position, QNULL, CVec3(1.f, 1.f, 1.f));

  vector<SVector> occupiedTiles;
  MarkObject(pWorld->GetTileMap(), dbObject, occupiedTiles);
  pWorld->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);


  if( !IsValid(targetHero) )
  {
    NI_ALWAYS_ASSERT( "Target hero must be valid!");
    return;
  }

  ChangeFaction(targetHero->GetFaction());

  if ( targetHero->IsLocal() )
  {
    NI_VERIFY( gameObject, "Need gameObject to create Glyph!", return; );
    CreateClientObject<NGameX::PFClientChest>( NGameX::PFClientLogicObject::CreatePars(pWorld->GetScene(), BADNODENAME, gameObject) );

    TileMap * tileMap = GetWorld()->GetTileMap();
    SVector pos = tileMap->GetTile(GetPosition().AsVec2D());
    int tileRadius = tileMap->GetLenghtInTiles(GetWorld()->GetAIWorld()->GetAIParameters().expandNatureGlyphsVisibilityRadius);

    visUnitID = GetWorld()->GetFogOfWar()->AddObject(pos, targetHero->GetFaction(), tileRadius);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNatureGlyph::OnPickedUp( const CPtr<PFBaseHero>& pPicker )
{
  NI_ASSERT( targetHero == pPicker, "Picker is not a target hero!" );
  GetWorld()->GetAIWorld()->OnNatureGlyphUsed( routeID, targetHero );
}

void PFNatureGlyph::Destroy()
{
  GetWorld()->GetFogOfWar()->RemoveObject(visUnitID);
  visUnitID = -1;
  Die();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNatureGlyph::SetPosition( const CVec3 newPosition )
{
  position = newPosition;
  if ( IsValid(ClientObject()) ) // client object may be not valid, if targetHero is not local!
    CALL_CLIENT_1ARGS(OnMove, position);

  GetWorld()->GetFogOfWar()->MoveObject(visUnitID, GetWorld()->GetTileMap()->GetTile(position.AsVec2D()));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNatureGlyph::SetVisible( bool newVisible )
{
  if ( bVisible != newVisible )
  {
    bVisible = newVisible;
    UpdateHiddenState(bVisible);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNatureGlyph::Reset()
{
  PFPickupableObjectBase::Reset();
  if( !IsValid(targetHero) )
    return;
  if ( targetHero->IsLocal() )
  {
    CreateClientObject<NGameX::PFClientChest>( NGameX::PFClientLogicObject::CreatePars(GetWorld()->GetScene(), BADNODENAME, gameObject) );

    TileMap * tileMap = GetWorld()->GetTileMap();
    SVector pos = tileMap->GetTile(GetPosition().AsVec2D());
    int tileRadius = tileMap->GetLenghtInTiles(GetWorld()->GetAIWorld()->GetAIParameters().expandNatureGlyphsVisibilityRadius);

    if ( visUnitID > -1 )
      visUnitID = GetWorld()->GetFogOfWar()->AddObject(pos, targetHero->GetFaction(), tileRadius);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFGlyph,           NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFNatureGlyph,     NWorld);
REGISTER_WORLD_OBJECT_NM(PFGlyphSpawner,  NWorld);
