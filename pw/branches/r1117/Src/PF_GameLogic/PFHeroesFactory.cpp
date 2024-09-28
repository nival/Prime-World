#include "stdafx.h"

#include "PFHero.h"
#include "PFMaleHero.h"

#ifndef VISUAL_CUTTED
#include "PFClientHero.h"
#else
#include "../Game/PF/Audit/ClientStubs.h"
#endif

namespace
{
  struct RandomMemoryAllocator : NonCopyable
  {
    enum
    {
      MaxAllocationSize = 16384,
    };

    explicit RandomMemoryAllocator(const std::size_t minAllocationSize)
      : minAllocationSize(minAllocationSize)
      , memory(NULL)
    {
      memory = new char[GetAllocationSize()];
    }

    ~RandomMemoryAllocator()
    {
      delete[] memory;
    }
  private:
    std::size_t GetAllocationSize()
    {
      return static_cast<std::size_t>(std::rand() % MaxAllocationSize) + minAllocationSize;
    }

    RandomMemoryAllocator();

    const std::size_t minAllocationSize;

    char* memory;
  };
}

namespace NWorld
{
  
class PFGenericHero : public PFBaseMaleHero
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C59BC80, PFGenericHero, NGameX::PFBaseClientHero)
  explicit PFGenericHero() {}

	virtual void Reset()
	{
    if ( IsValid( GetMount() ) )
    {
      CALL_CLIENT( OnUnmountSpecial );
    }

    PFBaseMaleHero::Reset();

    if ( !IsDead() )
    {
		  NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_HERO];
		  CreateClientObject<NGameX::PFBaseClientHero>(NGameX::PFBaseClientHero::CreatePars(*GetDbHero(), pAnimSet, GetWorld()->GetScene(), originalFaction, IDLENODE, GetSkinId()));
      ClientAttachToPlayer();

      if ( IsIsolated() ) // beeing in minigame 
      {
        if ( IsLocal() )
        {
          CALL_CLIENT( UnsubscribeMinigameAfterReconnect );
        }
      }

      if ( IsValid( GetMount() ) )
      {
        GetMount()->DoReset();
        CALL_CLIENT_1ARGS( OnMountSpecial, GetMount() );
      }
    }
  }

  virtual void RestoreClientObject()
  {
    if ( !ClientObject() )
    {
      NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_HERO];
      CreateClientObject<NGameX::PFBaseClientHero>(NGameX::PFBaseClientHero::CreatePars(*GetDbHero(), pAnimSet, GetWorld()->GetScene(), originalFaction, REVIVENODE, GetSkinId()));
      ClientAttachToPlayer();
    }
  }

  ZDATA_(PFBaseMaleHero)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMaleHero*)this); return 0; }

  PFGenericHero(PFWorld* pWorld, const PFBaseHero::SpawnInfo &info, NDb::EFaction faction, NDb::EFaction _originalFaction );
};

PFGenericHero::PFGenericHero( PFWorld* pWorld, const PFBaseHero::SpawnInfo &info, NDb::EFaction faction, NDb::EFaction _originalFaction )
: PFBaseMaleHero( pWorld, info, faction, _originalFaction)
{
  NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_HERO];
	nstl::string startNode = info.shouldPlaySummonEffect ? (info.isClone ? SUMMONNODE : REVIVENODE) : IDLENODE;

	CreateClientObject<NGameX::PFBaseClientHero>(NGameX::PFBaseClientHero::CreatePars(*info.pHero, pAnimSet, pWorld->GetScene(), originalFaction, startNode, GetSkinId()));
  InitHero( info.pHero, info.bInitTalents, info.usePlayerInfoTalentSet, info.playerInfo, info.bInitInventory );
  InitBaseAttack(); // need to init BaseAttack after talents being initialized

  CALL_CLIENT_1ARGS( SetRotation, info.placement.rot );
}

PFBaseHero* CreateHero(PFWorld* pWorld, PFBaseHero::SpawnInfo const& info)
{
  NI_PROFILE_FUNCTION_MEM;

  NI_VERIFY(pWorld,     "World must exist!",         return NULL; );
  NI_VERIFY(info.pHero, "Invalid hero description!", return NULL; );

  PFBaseHero* pHero = NULL;
  PFPlayer* pPlayer = NULL;
  NDb::EFaction faction = info.faction;
  NDb::EFaction originalFaction = info.originalFaction;

  bool isDummyPlayer = info.playerId < 0;
  if(!isDummyPlayer)
  {
    pPlayer = pWorld->GetPlayer(info.playerId);
    faction = NWorld::GetFaction(pPlayer);
    originalFaction = NWorld::GetOriginalFaction(pPlayer);
  }
  switch(info.pHero->GetObjectTypeID())
  {
  case NDb::Hero::typeId:
    {
#ifdef _SHIPPING
      // "смещает" объект героя в памяти - таким образом, оффсеты для чита будет сложнее подобрать
      const RandomMemoryAllocator m(sizeof(PFGenericHero));
#endif
      pHero = new PFGenericHero( pWorld, info, faction, originalFaction );
    }
    break;
  }

  if(pHero)
  {
    if(!isDummyPlayer)
      pHero->AttachToPlayer(pPlayer);
    else
      pHero->UpdateClientColor();
  }
  else
  {
    NI_ALWAYS_ASSERT("Unknown type ID for hero");
  }

  return pHero;
}

}

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFGenericHero,   NWorld)
