#include "stdafx.h"

#include "PFClientHero.h"

#include "PFClientObjectHelpers.h"
#include "PFAIWorld.h"
#include "PFWorldNatureMap.h"
#include "DBSound.h"
#include "../PF_Core/EffectsPool.h"
#include "../Render/debugrenderer.h"
#include "../System/InlineProfiler.h"

#include "AdventureScreen.h"
#include "Minimap.h"
#include "PFHeroStates.h"

#include "ClientVisibilityHelper.h"

namespace 
{
  DEV_VAR_STATIC float g_fAGCommandQueueDepth    = 5.0f;
  DEV_VAR_STATIC bool  g_debugShowLinePosition   = false;
  DEV_VAR_STATIC bool  g_debugShowObjectPosition = false;
  DEV_VAR_STATIC bool  g_debugShowObjectDirection = false;
  

  Render::Color white( 255, 255, 255, 255 );
  Render::Color red( 255, 0, 0, 255 );
  Render::Color green( 0, 255, 0, 255 );

  typedef vector<NDb::Ptr<NDb::DBSoundSceneComponent> > TDBFMODEventInstance;
}

namespace NGameX
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseClientHero::PFBaseClientHero( PF_Core::WorldObjectRef pWO, const CreatePars &cp )
: PFClientCreature(pWO, cp)
, lastHealthPercent(-1.0f)
, minimapIconId(-1)
, unsubscribeMinigameAfterReconnect(false)
, unsubscribeMinigameWorldStep(0)
, timerBattleSound(-1.f)
, timerIdle(-1.f)
{    
	const NWorld::PFBaseHero* pWorldObject = WorldObject();
	NI_ASSERT(pScene && pWorldObject, "Invalid initialization of client object");

  SetCommandQueueDepth(g_fAGCommandQueueDepth);
  {

    AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance();

    if (pAdvScreen)
    {
      if (!pWorldObject->IsClone())
      {
        DebugTrace("Start preloading hero's (%s) resources", pWorldObject->GetPlayerName().c_str());
        pAdvScreen->PreloadEffectsInResourceTree( cp.pDesc, cp.nodeName, pWorldObject->GetExcludedResourcesList(), pWorldObject->GetSkinId() );
      }

      if ( Minimap * minimap = pAdvScreen->GetMinimap() )
        minimapIconId = minimap->AddHeroIcon( pWorldObject->GetUiMinimapImage() );
    }   
  }

  if( false == PFClientCreature::Initialize(GetSceneObject(), &cp.pAnimSet, 1, false, 0, true ) ) 
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Failed to initialize anim controller!" << endl;
  }

  Restart( cp.nodeName );

  AttachGlowEffect();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseClientHero::~PFBaseClientHero()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnBecameLocal(bool isLocal)
{
  ResetControlledEffect( isLocal );

  if (!isLocal)
  {
    // Reset last health - needed for support of changing hero during the session
    lastHealthPercent = -1.0f;
  }

  // Re-initialize asks (2d for local, 3d otherwise)
  InitializeAsks(isLocal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::UnsubscribeMinigameAfterReconnect() 
{ 
  unsubscribeMinigameAfterReconnect = true; 
  unsubscribeMinigameWorldStep = WorldObject()->GetWorld()->GetStepNumber(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION;

  PFClientCreature::Update(timeDiff);

  // Update heartbeat sound effect state if needed
  UpdateHeartbeating();

  UpdateAsks(timeDiff);

  //TODO: SimonK remove this to a better place like easelPlayerClientObject or so
  if ( const_cast<NWorld::PFBaseMaleHero*>(WorldObject())->GetMinigames() )
    const_cast<NWorld::PFBaseMaleHero*>(WorldObject())->GetMinigames()->UpdateM( timeDiff );

  if ( unsubscribeMinigameAfterReconnect && 
    ( ( unsubscribeMinigameWorldStep + 1 ) < WorldObject()->GetWorld()->GetStepNumber() ) )
  {
    const_cast<NWorld::PFBaseMaleHero*>(WorldObject())->ForceLeaveMinigame();
    unsubscribeMinigameAfterReconnect = false;
  }
}

void PFBaseClientHero::RenderDebug()
{
  if( g_debugShowLinePosition )
  {
    CVec3 pos = GetPosition().pos;
    pos.z += 6.0f;

    NWorld::PFWorldNatureMap const* pNature = WorldObject()->GetWorld()->GetNatureMap();

    float distance = 0.0f;
    NDb::ERoute route = WorldObject()->GetNearestRoute( &distance );

    Render::DebugRenderer::DrawText3D( 
      NStr::StrFmt("pos: {x = %.1f, y = %.1f}\n atBase = %i \n nearest route: %s, distance: %.1f", 
        pos.x, pos.y, 
        pNature->IsAtBase(pos.x, pos.y),
        NDb::EnumToString( route ), 
        distance),
        pos, 20, white);

    GetSceneObject()->GetScene()->GetHeightsController().GetHeight(pos.x, pos.y, 0,  &pos.z, NULL);

    for (int iRoute = 0; iRoute < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf; ++iRoute)
    {
      {
        vector<CVec2> const& road = pNature->GetLogicRoad((NDb::ENatureRoad)iRoute);
        vector<CVec2>::const_iterator route_begin = road.begin();
        vector<CVec2>::const_iterator route_end   = road.end();

        vector<CVec2>::const_iterator begin = route_begin, end = route_begin;
        advance(end, 1);

        for(; end != route_end; ++begin, ++end)
          Render::DebugRenderer::DrawLine3D( CVec3(*begin, 3.0f), CVec3(*end, 3.0f), red, red, false);
      }
    }    
  }

  if( g_debugShowObjectPosition )
  {
    NScene::SceneObject* pSO = GetSceneObject();

    CVec3 const worldPos  = WorldObject()->GetPosition();
    CVec3 const clientPos = GetPosition().pos;
       
    Render::DebugRenderer::DrawText3D( 
      NStr::StrFmt( "worldPos:  {x = %.1f, y = %.1f, z = %.1f}\n "
                    "clientPos: {x = %.1f, y = %.1f, z = %.1f}\n "
                    "isVisible: %i", 
                    worldPos.x,  worldPos.y,  worldPos.z,
                    clientPos.x, clientPos.y, clientPos.z,
                    pSO->IsVisible()
                  ),
      CVec3(clientPos.x, clientPos.y, clientPos.z + 6.0f), 20, white);
  }

  if( g_debugShowObjectDirection )
  {
    NScene::SceneObject* pSO = GetSceneObject();
    CVec3 const dir = pSO->GetPosition().rot.Rotate( CVec3( 0.0f, -1.0f, 0.0f ) );
    CVec2  worldDir  = WorldObject()->GetMoveDirection();

    CVec2 const clientPos = GetPosition().pos.AsVec2D();
    float dbgCursorLength = 2.f;
    
    CVec3 begin = CVec3(clientPos, dbgCursorLength);
    CVec3 end = begin + dir * dbgCursorLength;

    //Matrix43 m(CVec3(-0.5, 0.0, 0.0));
    //begin = Transform(begin, m);
    //end = Transform(end, m);

    Render::DebugRenderer::DrawLine3D( begin, end, red, red, false);

    CVec3 beginW = CVec3(clientPos, dbgCursorLength);
    CVec3 endW = begin + CVec3(worldDir * dbgCursorLength, 0.0);

    Matrix43 mW(CVec3(0.5, 0.0, 0.0));
    beginW = Transform(beginW, mW);
    endW = Transform(endW, mW);

    Render::DebugRenderer::DrawLine3D( beginW, endW, green, green, false);

  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::UpdateMinimap() const
{
  static DI_WEAK(NGameX::Minimap) minimap;
  static DI_WEAK(NGameX::AdventureScreen) advScreen;

  if (!minimap)
    return;
  if (!advScreen)
    return;

  if (!bVisible)
    return;

  const NWorld::PFBaseHero *pWorldUnit = WorldObject();

  if (!pWorldUnit)
    return;
  if (pWorldUnit->IsDead())
    return;

  // TRAP: bVisible <-> ClientVisibilityHelper::IsVisibleForPlayer(pWorldUnit)
  if (!ClientVisibilityHelper::IsVisibleForPlayer(pWorldUnit))
    return;

  if (pWorldUnit->IsMounted())
  {
    if (IsValid(pWorldUnit->GetMount()) && pWorldUnit->GetMount()->IsHero())
      return;
  }

  // TODO: зачем здесь IsHero() ?
  const bool clone = pWorldUnit->IsClone();
  const bool hero = pWorldUnit->IsHero();
  const bool ally = (pWorldUnit->GetFaction() == advScreen->GetPlayerFaction());

  // For allies only show clones as creeps
  // Or in case object doesn't pretend to be a hero
  // TODO: условие не очень-то соответствует комментарию выше
  if (clone && (ally || !hero))
    minimap->AddObject(NDb::UNITTYPE_CREEP, pWorldUnit->GetFaction(), GetPosition().pos, -1);
  else
    minimap->AddObject(pWorldUnit, minimapIconId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::UpdateAsks( float timeDiff )
{
  for (unsigned int i = 0; i < soundsData.capacity(); ++i)
  {
    for (int j = 0; j < soundsData[i].size(); ++j)
    {
      if (soundsData[i][j].cooldownTimer > 0.0f)
      {
        soundsData[i][j].cooldownTimer -= timeDiff;
      }
    }
  }

  bool isIdle = NWorld::IsUnitValid( WorldObject() ) && WorldObject()->IsIdle() ;

  if( isIdle )
  {
    if( timerIdle < 0 )
      timerIdle = NDb::SoundRoot::GetRoot()->timerHeroAskIdle;  

    timerIdle -= timeDiff;

    if( timerIdle <= 0 && !WorldObject()->GetWorld()->GetAIWorld()->WasGameFinished() && !NGameX::AdventureScreen::Instance()->IsPlayingMinigame() ) 
      PlayAskSound( NDb::ASKSOUNDS_IDLE );
  }
  else
    timerIdle  = -1.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnDamage(float health, float damage)
{
  PFClientCreature::OnDamage(health, damage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnUnitDie()
{
  ActivateSound( NDb::SOUNDSCENE_DEAD );

  // Detach 3d asks needed, because dead hero's SceneObject is 
  // released and new one attached after resurrection, which need to be reattached then.
  Detach3dAsks();

  PFClientCreature::OnUnitDie();

  PlayAskSound(NDb::ASKSOUNDS_DEATH, NULL, 10 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnResurrect()
{
  PFClientCreature::Resurrect();

  AttachGlowEffect();
  
  Attach3dAsks();

  PlayAskSound(NDb::ASKSOUNDS_REVIVE);

  if ( NWorld::PFBaseHero const * pWorldUnit = WorldObject() )
  {
    if( pWorldUnit->GetWorld()->GetAIWorld()->IsTutorial() )
    {
      if (pWorldUnit->GetFaction() == NDb::FACTION_FREEZE)
        ActivateSound( NDb::SOUNDSCENE_TUTORIALA );
      else
        ActivateSound( NDb::SOUNDSCENE_TUTORIALB );
    }
    else
    {
      if (pWorldUnit->GetFaction() == NDb::FACTION_FREEZE)
        ActivateSound( NDb::SOUNDSCENE_SESSIONA );
      else
        ActivateSound( NDb::SOUNDSCENE_SESSIONB );
    }

    ResetControlledEffect( pWorldUnit->IsLocal() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Updates heartbeating sound effect according to hero's state. Set effect parameter according to hero's life percent and
// starts or stops the effect if hero became alive or dead correspondingly.
void PFBaseClientHero::UpdateHeartbeating()
{
  if (const NWorld::PFBaseHero * pHero = WorldObject())
  {
    if (pHero->IsLocal())
    {
      float healthPercent = pHero->GetHealthPercent();

      // Update only if changed
      if (healthPercent != lastHealthPercent)
      {
        // First of all - update event's life parameter
        NSoundScene::UpdateHeartBeat(healthPercent*100.0f);

        // Now decide if it should be started or stoped
        if (healthPercent == 0.0f && lastHealthPercent != -1.0f)
        {
          // Stop heartbeating if hero die and he was alive before
          NSoundScene::PlayHeartBeat(false);
        }
        else if (healthPercent > 0.0f && (lastHealthPercent == 0.0f || lastHealthPercent == -1.0f))
        {
          // Start heartbeating if hero became alive and he was dead or just created before
          NSoundScene::PlayHeartBeat(true);
        }

        lastHealthPercent = healthPercent;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initializes hero's asks. 2d for local hero and 3d for non-local. It creates, initializes/attaches 
// needed type of asks and destroy the unneeded, if was created.
void PFBaseClientHero::InitializeAsks(bool isLocal)
{
  NWorld::PFBaseHero const* pWorldObject = WorldObject();

  NI_VERIFY(pWorldObject, "Failed to get hero's WorldObject!", return);

  if( pWorldObject->IsClone() )	// Clones do not speak
    return;

  NDb::BaseHero const* pDbHero = pWorldObject->GetDbHero();

  NI_VERIFY(pDbHero, "Failed to get hero's DB descriptor!", return);

  const NDb::AskSounds* heroAsks = pWorldObject->GetHeroAsks(EHeroState::First);
  if (!heroAsks)
    return;

  // This one can be empty. So we dont check it here.
  const NDb::AskSounds* heroAsksSecondSate = pWorldObject->GetHeroAsks(EHeroState::Second);

  InitializeAsksData(heroAsks, EHeroState::First);
  InitializeAsksData(heroAsksSecondSate, EHeroState::Second);

  if (isLocal)
  {
    Create2dAsks(heroAsks, EHeroState::First);
    Create2dAsks(heroAsksSecondSate, EHeroState::Second);
  }
  else
  {
    Destroy2dAsks();
  }

  // We destroy/create 3D asks in any case, because they may be played either 
  // for the local player's hero or non-local, depending on hero asks settings
  Destroy3dAsks();
  Create3dAsks(heroAsks, EHeroState::First, isLocal);
  Create3dAsks(heroAsksSecondSate, EHeroState::Second, isLocal);

  // Do not try to attach 3D asks to a dead hero. He will get them on resurrect.
  if (!pWorldObject->IsDead())
  {
    Attach3dAsks();
  }

  lastHitSound = new NSound::AskCommands();
  lastHitSound->Init( NDb::SoundRoot::GetRoot()->lastHit );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::InitializeAsksData(const NDb::AskSounds* heroAsks, EHeroState::Enum forHeroState)
{
  TAsksData & asksData = soundsData[forHeroState];

  if (!heroAsks)
  {
    asksData.resize(0);
  }
  else
  {
    int asksCount = NDb::KnownEnum<NDb::EAskSounds>::SizeOf();
    asksData.resize(asksCount);

    for (int i = 0; i < asksCount; ++i)
    {
      asksData[i].minInterval = heroAsks->settings[i].minInterval;
      asksData[i].cooldownTimer = 0.0f;
      asksData[i].ask3dRecipient = heroAsks->settings[i].ask3dRecipient;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creates and initializes 2d asks
void PFBaseClientHero::Create2dAsks(NDb::AskSounds const* pHeroAsks, EHeroState::Enum forHeroState)
{
  TAsks & asks2d = soundsCommands[forHeroState];

  if (!pHeroAsks)
  {
    asks2d.resize(0);
    return;
  }

  asks2d.resize(NDb::KnownEnum<NDb::EAskSounds>::SizeOf());

  for (int i = 0; i < asks2d.size(); ++i)
  {
    asks2d[i]= new NSound::AskCommands();
  }

  int id = 0;

  for (TDBFMODEventInstance::const_iterator ask_it = pHeroAsks->sounds.begin(), 
                                                end = pHeroAsks->sounds.end(); ask_it != end; ++ask_it, ++id)
  {
    if (!*ask_it)
      continue;

    if (!(*ask_it)->desc.projectName.length() || !(*ask_it)->desc.eventName.length())
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Hero " << WorldObject()->GetDbHero()->GetDBID().GetFileName() 
                                          << " has ask-sound #" << id << " with empty project/event description" << endl;
      continue;
    }

    asks2d[id]->Init((*ask_it)->desc);
    NSoundScene::PreCacheGroup( (*ask_it)->desc.groupName, true );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creates 3d asks (SounSceneComponents), but does not attach them to the scene hierarchy
void PFBaseClientHero::Create3dAsks(NDb::AskSounds const* pHeroAsks, EHeroState::Enum forHeroState, bool isLocal)
{
  TAsks3d & asks3d = sounds3dCommands[forHeroState];

  if (!pHeroAsks)
  {
    asks3d.resize(0);
    return;
  }

  asks3d.resize(NDb::KnownEnum<NDb::EAskSounds>::SizeOf());

  TAsksData const & asksData = soundsData[forHeroState];

  int id = 0;

  for (TDBFMODEventInstance::const_iterator ask_it = pHeroAsks->sounds3d.begin(), 
                                                end = pHeroAsks->sounds3d.end(); ask_it != end; ++ask_it, ++id)
  {
    if (!*ask_it || !(*ask_it)->desc.projectName.length() || !(*ask_it)->desc.eventName.length())
    {
      // Lack of 3d ask is a normal case, so we just resume to the next one here
      continue;
    }

    // Initialize only if there is any chance, that it will be used
    if (isLocal && asksData[id].ask3dRecipient != NDb::ASKRECIPIENT_ENEMIES
        || !isLocal && asksData[id].ask3dRecipient != NDb::ASKRECIPIENT_SELF)
      asks3d[id] = new NScene::SoundSceneComponent((*ask_it), NULL, NULLPLACEMENT);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Attaches 3d asks (SoundSceneComponents) to the scene hierarchy, so they will receive owner hero placement updates
void PFBaseClientHero::Attach3dAsks()
{
  NScene::SceneObject* pSO = GetSceneObject();
  NI_VERIFY(pSO, "Failed to get SceneObject of PFBaseClientHero!", return;);

  for (unsigned int i = 0; i < sounds3dCommands.capacity(); ++i)
  {
    TAsks3d & asks3d = sounds3dCommands[i];
    for (int j = 0; j < asks3d.size(); ++j)
    {
      if (asks3d[j])
      {
        pSO->AttachTo(asks3d[j]);
        asks3d[j]->DisableStrong( true );
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Detaches 3d asks (SoundSceneComponents) from the scene hierarchy, in case of death or disabling of 3d asks
void PFBaseClientHero::Detach3dAsks()
{
  NScene::SceneObject* pSO = GetSceneObject();
  NI_VERIFY(pSO, "Failed to get SceneObject of PFBaseClientHero!", return;);

  for (unsigned int i = 0; i < sounds3dCommands.capacity(); ++i)
  {
    TAsks3d & asks3d = sounds3dCommands[i];
    for (int j = 0; j < asks3d.size(); ++j)
    {
      if (asks3d[j])
      {
        asks3d[j]->DisableStrong(true);
        pSO->Detach(asks3d[j]);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::Destroy2dAsks()
{
  soundsCommands[EHeroState::First].clear();
  soundsCommands[EHeroState::Second].clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::Destroy3dAsks()
{
  Detach3dAsks();
  sounds3dCommands[EHeroState::First].clear();
  sounds3dCommands[EHeroState::Second].clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnKill( CPtr<NWorld::PFBaseUnit> const& pVictim, bool lastHit )
{
  NI_VERIFY( IsValid(pVictim), "Victim object must be valid", return; );

  const PFBaseClientHero* pHeroVictim = dynamic_cast<const PFBaseClientHero*>( pVictim->ClientObject() );

  if ( pHeroVictim && ( pHeroVictim != this ) )
  {
    PlayAskSound( NDb::ASKSOUNDS_KILL, NULL, 10 );
  }

  if( pVictim->GetUnitType() == NDb::UNITTYPE_FACTIONCHAMPION )
  {
    PlayAskSound( NDb::ASKSOUNDS_KILLCHAMPION, NULL, 10 );
  }

  const NWorld::PFBaseHero* pHero = WorldObject();
  NI_VERIFY(pHero, "Failed to get PFBaseHero of PFBaseClientHero!", return; );

  if ( lastHit && pHero->IsLocal() && !pHero->IsClone() )
  {
    if ( !lastHitSound->IsAllreadyPlayed() )
    {
      lastHitSound->PlaySound();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnAddGold( CPtr<NWorld::PFBaseUnit> const& pSender, const float gold )
{
	if (WorldObject()->IsLocal())
		PFClientCreature::OnAddGold(pSender, gold);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseClientHero::PlayAskSound(int id, NWorld::PFBaseHero const * pTarget /*= 0*/, int announcePriority /*= -1*/ )
{
  if ( AdventureScreen::Instance()->IsSpectator() 
      || !AdventureScreen::Instance()->IsDialogFinished( 0 ))
    return true;

  NWorld::PFBaseHero const * pHero = WorldObject();
  NI_VERIFY(pHero, "Failed to get PFBaseHero of PFBaseClientHero!", return false; );

  if( pHero->IsClone() )	// Clones do not speak
    return true;

  NI_VERIFY(id >= 0 && id < NDb::KnownEnum<NDb::EAskSounds>::SizeOf(), "Wrong ask-sound id!", return false);

  EHeroState::Enum heroState = pHero->GetHeroState();
  TAsksData & asksData = soundsData[heroState];

  if (id >= asksData.size() || asksData[id].cooldownTimer > 0.0f)
      return true;

  bool isLocal = pHero->IsLocal();
  TAsks const & asks2d = soundsCommands[heroState];

  if (isLocal && id < asks2d.size())
  {
    for (int i = 0; i < NDb::KnownEnum<NDb::EAskSounds>::SizeOf(); ++i)
    {
      if (asks2d[i]->IsAllreadyPlayed())
      {
        // stop all sounds if hero dies
        if (NDb::ASKSOUNDS_DEATH == id)
          asks2d[i]->Stop(true);
        else
          return true;
      }
    }

    asksData[id].cooldownTimer = asksData[id].minInterval;

    if ( announcePriority > -1 )
    {
      if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
      {
        pAdvScreen->PlaceAskToAnnouncementQueue( asks2d[id], announcePriority );
      }
    }
    else
    {
      asks2d[id]->PlaySound();
    }
  }

  TAsks3d const & asks3d = sounds3dCommands[heroState];

  if (id < asks3d.size() && asks3d[id])
  {
    NWorld::PFBaseHero const * pLocalHero = 0;

    if (isLocal)
      pLocalHero = pHero;
    else if (AdventureScreen const * pAdvScreen = AdventureScreen::Instance())
      pLocalHero = pAdvScreen->GetHero();

    NI_VERIFY(pLocalHero, "Failed to get local hero for 3D ask verifications!", return false)

    // Check ask recipient flag and allowing conditions
    switch (asksData[id].ask3dRecipient)
    {
    case NDb::ASKRECIPIENT_SELF:
      if (!isLocal)
        return true;
      break;

    case NDb::ASKRECIPIENT_TARGET:
      if (pTarget != pLocalHero)
        return true;
      break;

    case NDb::ASKRECIPIENT_ALLIES:
      if (!isLocal && pHero->GetFaction() != pLocalHero->GetFaction())
        return true;
      break;

    case NDb::ASKRECIPIENT_ENEMIES:
      if (pHero->GetFaction() == pLocalHero->GetFaction())
        return true;
      break;
    }

    if (NDb::ASKSOUNDS_DEATH != id)
    {
      // This will stop the previous play (if was)
      asks3d[id]->DisableStrong(true);
      // This will play the sound
      asks3d[id]->DisableStrong(false);
    }
    else
    {
      // If hero is dead - the SoundSceneComponent is no longer attached to the scene hierarchy 
      // and will not receive update and play the sound. Threfore the "brut force" is needed here.
      asks3d[id]->ForceSoundPlay();
    }

    asksData[id].cooldownTimer = asksData[id].minInterval;

    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnBecameActive(bool bActive)
{
  if( bActive )
  {
    Subscribe();
  }
  else
  {
    SetVisibilityAsObject(false);
    Unsubscribe();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseClientHero::OnLevelUp(int level)
{
  if( WorldObject()->IsClone() ) // do not play levelup effects for "hero clones"
    return true;

  if( PFClientCreature::OnLevelUp(level) )
  {
    if ( GetLifeState() == Living )
    {
      CObj<PF_Core::BasicEffect> pTemp = PF_Core::EffectsPool::Get()->Retrieve(NDb::EFFECTS_LEVELUP);
      pTemp->Apply(this);
    }

    // insert levelup sound here
    return true;
  }
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnMountSpecial( CPtr<NWorld::PFBaseMovingUnit> const& pMount )
{
  SynchronizeVisualPosition();
  if( NGameX::PFClientBaseMovingUnit* pClient = pMount->ClientObject() )
  {
    if( NScene::SceneObject* pObj2AttachOn = pClient->GetSceneObject() )
    { 
      if ( IsValid( pAttacher ) )
      {
        pAttacher->Detach();
        pAttacher = 0;
      }

      pAttacher = new NScene::AttacherSceneComponent<PFClientLogicObjectAttacherPolicy>( this );
      pAttacher->SetParentTransformUsageFlags(NDb::ATTACHFLAGS_USEPARENTROTATION);
      pObj2AttachOn->AttachToByLocator( pObj2AttachOn->FindLocator("Seat") ? "Seat" : "Above", pAttacher );
    }
  }

  ForceIdle();

  ProcessEffectsOnMount( true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnUnmountSpecial()
{
  ForceIdle(); // force all animation to be stopped!

  if( NScene::SceneObject* pSO = GetSceneObject() )
  {
    if ( IsValid ( pAttacher ) )
    {
      pAttacher->Detach();
      pAttacher = 0;
    }
  }

  ForceIdle();

  ProcessEffectsOnMount( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void PFBaseClientHero::UpdateBattleSound( float time, bool force/* = false*/ )
//{
//  const float timerLimit = 5.f;
//
//  const NWorld::PFBaseMaleHero* hero = WorldObject();
//
//  const float radius = hero->GetVisibilityRange();
//
//  if( hero->IsLocal() && !hero->IsDead() )
//  {
//    if( force )
//    {
//      timerBattleSound = timerLimit;
//      ActivateSound( NDb::SOUNDSCENE_BATTLE );
//      return;
//    }
//
//    UnitBattleFunctor func( hero->GetPos(), radius, hero->GetFaction() );
//
//    hero->GetWorld()->GetAIWorld()->ForAllInRange( CVec3(hero->GetPos(), 0.0f), radius + hero->GetWorld()->GetAIWorld()->GetMaxObjectSize() * 0.5f, func );
//
//    if( timerBattleSound > 0 )
//      timerBattleSound -= time;
//
//    if( func.InBattle() )
//    {
//      timerBattleSound = timerLimit;
//      ActivateSound( NDb::SOUNDSCENE_BATTLE );
//    }
//    else
//    {
//      if( timerBattleSound < 0 ) 
//      {
//        if( hero->GetWorld()->GetAIWorld()->IsTutorial() )
//        {
//          if (hero->GetFaction() == NDb::FACTION_FREEZE)
//            ActivateSound( NDb::SOUNDSCENE_TUTORIALA );
//          else
//            ActivateSound( NDb::SOUNDSCENE_TUTORIALB );
//        }
//        else
//        {
//          if (hero->GetFaction() == NDb::FACTION_FREEZE)
//            ActivateSound( NDb::SOUNDSCENE_SESSIONA );
//          else
//            ActivateSound( NDb::SOUNDSCENE_SESSIONB );
//        }
//      }
//    }
//  }
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::ProcessEffectsOnMount(bool mounted)
{
  struct EffectsSwitcher : public NScene::FullTraverser
  {
    bool enable;
		int  flags;
    EffectsSwitcher(bool enable_, int flags_) : enable(enable_), flags(flags_) {}
    void operator() (NScene::SceneComponent *sc) 
		{ 
			if ((sc->GetGroupFlags() & flags) != 0 )
				sc->EnableWeak( enable ); 
		}
  } f( false == mounted, NScene::SceneComponent::GROUPFLAGS_GROUND_ATTACH );
  
  GetSceneObject()->Traverse( f );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseClientHero::OnEffectAttach(PF_Core::BasicEffectAttached *pEffect)
{
	// Mark ground object
  if (pEffect->GetDBEffect().attachType != NDb::EnumToString( NDb::EFFECTATTACHTYPE_GROUND ) )
		return;

	NScene::SceneComponent *pSC = pEffect->GetRootComponent();
	if (!pSC)
		return;

  pSC->SetGroupFlags( pSC->GetGroupFlags() | NScene::SceneComponent::GROUPFLAGS_GROUND_ATTACH );
	if (WorldObject()->IsMounted()) // Enable if appearing on mounted
		pSC->EnableWeak(false);
}

void PFBaseClientHero::ActivateSound( int soundScene )
{
  NWorld::PFBaseHero const * hero = WorldObject();
  NI_VERIFY(hero, "Failed to get PFBaseHero of PFBaseClientHero!", return; );

  if( hero->IsClone() )	// Clones do not speak
    return;

  if (hero->IsLocal())
  {
    NSoundScene::SetGlobalPitchCoeff( 1.0f );
    NSoundScene::ActivateSoundScene( soundScene, false );
  }
}

void PFBaseClientHero::ResetControlledEffect( bool isLocal )
{
  if ( pControlledEffect )
  {
    pControlledEffect->Die();
    pControlledEffect = NULL;
  }

  if ( isLocal )
  {
    pControlledEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>(NDb::EFFECTS_CONTROLLEDHEROAURA);

    NScene::SceneObject* pSO    = GetSceneObject();
    pControlledEffect->SetDeathType(NDb::EFFECTDEATHTYPE_MANUAL);
    pControlledEffect->Attach(pSO);
  }
}

void PFBaseClientHero::SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc )
{
  PFClientCreature::SetSceneObject( sceneObjectDesc );

  ResetControlledEffect( WorldObject()->IsLocal() );
}

void PFBaseClientHero::OnScrollReceived()
{
  if ( CObj<PF_Core::BasicEffectAttached> pScrollGivenEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>( NDb::EFFECTS_MINIGAMESCROLLGIVEN ) )
  {
    pScrollGivenEffect->Apply( this );
  }
}

void PFBaseClientHero::SetCinematicPause( bool pause )
{
  if ( pAttacher )
    return;
  PFClientCreature::SetCinematicPause( pause );
}
}

REGISTER_DEV_VAR("anim_commandQueueDepth",   g_fAGCommandQueueDepth,  STORAGE_NONE)
REGISTER_DEV_VAR("debug_showLinePostion" ,   g_debugShowLinePosition, STORAGE_NONE)
REGISTER_DEV_VAR("debug_showObjectPostion" , g_debugShowObjectPosition, STORAGE_NONE)
REGISTER_DEV_VAR("debug_showObjectDirection" , g_debugShowObjectDirection, STORAGE_NONE)