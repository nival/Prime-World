#include "stdafx.h"
#include "FemaleMaleAssistEffect.h"
#include "./../PFBaseUnit.h"
#include "./../PFTower.h"
#include "./../PFHero.h"
#include "./PF_Core/EffectsPool.h"
#include "./PF_Core/BasicEffect.h"
#include "./../AdventureScreen.h"
#include "./../PFAIWorld.h"
#include "./UI/Resolution.h"
#include "./../Scene/Camera.h"

namespace NWorld { 
namespace AIWorldFacets
{

struct IFemaleMaleAssistEffectFlashConnection
{
  virtual ~IFemaleMaleAssistEffectFlashConnection() {}
  virtual void CreateEffect( int effectId ) = 0;
  virtual void UpdatePosition( int effectId, const UI::Point &pos ) = 0;
  virtual void DestroyEffect( int effectId ) = 0;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DumyFemaleMaleAssistEffectFlashConnection: IFemaleMaleAssistEffectFlashConnection
{
  virtual ~DumyFemaleMaleAssistEffectFlashConnection() { DebugTrace("~DumyFemaleMaleAssistEffectFlashConnection()"); }
  virtual void CreateEffect( int effectId ) { DebugTrace("CreateEffect(%d)", effectId); }
  virtual void UpdatePosition( int effectId, const UI::Point &pos ){ /*DebugTrace("UpdatePosition(%d, {%g, %g})", effectId, pos.x, pos.y);*/ }
  virtual void DestroyEffect( int effectId ) { DebugTrace("DestroyEffect(%d)", effectId); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class FemaleMaleAssistEffect::ClientObject
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FemaleMaleAssistEffect::ClientObject: public PF_Core::IUpdateable 
{
  OBJECT_METHODS(0x678673C1, ClientObject)

public:
  ClientObject( CPtr<PFBaseUnit> pKiller, CPtr<PFBaseUnit> pAssistant, 
                IFemaleMaleAssistEffectFlashConnection *pFlashConnection ); 

private:
  typedef void (ClientObject::*NextStepFnc)();

  struct StateDsc;  
  struct SceneObjectPosType;
  struct StaticPosType;

private:
  ClientObject() {}
  
  void FillStatesData();
  virtual void Update( float timeDelta );
  
  NDb::Ptr<NDb::EffectBase> GetEffectId( NDb::EFemaleMaleAssistEffectSate num );

  template<class PosType>
  CObj<PF_Core::BasicEffect> CreateEffect( NDb::Ptr<NDb::EffectBase> effectId, PosType pos );
  void ApplyOrientation( CObj<PF_Core::BasicEffect> pEff, const CVec3 &from, const CVec3 &to );
  CVec3 CalcMiddlePos( const CVec3 &pos1, const CVec3 &pos2 ) const;
  void UpdateFlashEffectPos();
  
private: //Состояния NextStepFnc
  void StartEffectFromHeroesToMiddle();
  void StartEffectFromMiddleToHeroes();
  void StartEffectInMiddle();
  void StartEffectInFlash();
  void SelfDestroy();

private:
  CObj<ClientObject> pThis;
  vector<StateDsc> states;
  int curState;
  float curTime;
  CPtr<PFBaseUnit> assistants[2]; 
  NScene::IScene *pScene;
  CVec3 middlePos;
  IFemaleMaleAssistEffectFlashConnection *pFlashConnection;
  unsigned int curFlashEffectNum;
  static unsigned int totalFlashEffectsCount;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FemaleMaleAssistEffect::ClientObject::StateDsc
{
  float startTime;
  NextStepFnc stepFnc;

  StateDsc( float startTime, NextStepFnc stepFnc ):
  startTime(startTime), 
    stepFnc(stepFnc) 
  {}  
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FemaleMaleAssistEffect::ClientObject::SceneObjectPosType
{
  SceneObjectPosType( NScene::SceneObject *pObj ): pObj(pObj)
  {
    NI_ASSERT( pObj != 0, "Internal error" );
  }

  NScene::SceneObject *GetClientSceneObject() const { return pObj; }
  const Placement &GetVisualPosition3D() const { return pObj->GetPosition(); }
  bool PrefferDirectPos() const { return false; }

private:
  NScene::SceneObject *pObj; 
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FemaleMaleAssistEffect::ClientObject::StaticPosType
{
  StaticPosType( CVec3 pos ): pos(pos) { }

  NScene::SceneObject *GetClientSceneObject() const { NI_ALWAYS_ASSERT( "Can't get scene object from static position" ); return 0; }
  const Placement &GetVisualPosition3D() const { return pos; }
  bool PrefferDirectPos() const { return true; }

private:
  Placement pos; 
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int FemaleMaleAssistEffect::ClientObject::totalFlashEffectsCount = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CVec3 FemaleMaleAssistEffect::ClientObject::CalcMiddlePos( const CVec3 &pos1, const CVec3 &pos2 ) const
{
  CVec3 ret = (pos1 + pos2) / 2;
  pScene->GetHeightsController().GetHeight(ret.x, ret.y, 1, &ret.z, NULL);
  ret.z += NDb::SessionRoot::GetRoot()->visualRoot->femaleMaleAssistEffect.middlePosHeight;
  
  return ret;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

FemaleMaleAssistEffect::ClientObject::ClientObject( 
  CPtr<PFBaseUnit> pKiller, CPtr<PFBaseUnit> pAssistant,
  IFemaleMaleAssistEffectFlashConnection *pFlashConnection 
): 
  IUpdateable(true),
  pThis(this), curState(0), curTime(0), 
  pScene( pKiller->GetWorld()->GetScene() ),
  pFlashConnection(pFlashConnection),
  curFlashEffectNum(0) 
{
  assistants[0] = pKiller;
  assistants[1] = pAssistant;

  middlePos = CalcMiddlePos( pKiller->GetVisualPosition3D(), pAssistant->GetVisualPosition3D() );
  
  FillStatesData();
  Update(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::FillStatesData()
{
  typedef FemaleMaleAssistEffect::ClientObject ThisT;

  static const NextStepFnc statesFuncList[] = { 
    &ThisT::StartEffectFromHeroesToMiddle, &ThisT::StartEffectFromMiddleToHeroes, 
    &ThisT::StartEffectInMiddle, &ThisT::StartEffectInFlash, &ThisT::SelfDestroy
  };

  float totalTime = 0; 

  for( int i = 0; i < ARRAY_SIZE(statesFuncList); ++i )
  {
    const float deltaTime = NDb::SessionRoot::GetRoot()->visualRoot->
      femaleMaleAssistEffect.effectsWithDelay[i].deltaTime;

    states.push_back( StateDsc(totalTime + deltaTime, statesFuncList[i]) );
    totalTime += deltaTime; 
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::Update( float timeDelta )
{
  curTime += timeDelta;
  
  for(;;)
  {
    NI_ASSERT( curState < states.size(), "Internal error" );
  
    if( curTime < states[curState].startTime )
      break;
  
    //Вызов stepFnc может сделать delete this, а после этого к curState
    //запрещено получать доступ 
    const bool isFinishState = curState + 1 == states.size();
  
    (this->*states[curState].stepFnc)();
      
    if( isFinishState )  
      return; 
      
    ++curState;
  }
  
  UpdateFlashEffectPos();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class PosType>
CObj<PF_Core::BasicEffect> FemaleMaleAssistEffect::ClientObject::CreateEffect( NDb::Ptr<NDb::EffectBase> effectId, PosType pos )
{
  if( !IsValid(effectId) )
    return 0;                 
    
  const CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->Retrieve( effectId );

  if ( pEffect != 0 )
  {
    typedef PF_Core::BasicEffectAttached EffAtt;
    typedef PF_Core::BasicEffectStandalone EffStn;
  
    if( EffAtt *const pEffAtt = dynamic_cast<EffAtt *>(pEffect.GetPtr()) )
    {
      pEffAtt->Attach( pos.GetClientSceneObject() );
    }
    else if( EffStn *const pEffStn = dynamic_cast<EffStn *>(pEffect.GetPtr()) )
    {    
      if( !pos.PrefferDirectPos() )
        pEffStn->Apply( pos.GetClientSceneObject() );
      else
      {
        pEffStn->SetPosition( pos.GetVisualPosition3D() );
        pEffStn->AddToScene( pScene );
      }
    } 
    else
      NI_ALWAYS_ASSERT( "Unknown effect type" );  
  }
  else
    NI_ALWAYS_ASSERT( NStr::StrFmt("Can't get resource %s", effectId->GetDBID().GetFormatted().c_str()) );
   
   return pEffect;      
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::ApplyOrientation( CObj<PF_Core::BasicEffect> pEff, const CVec3 &from, const CVec3 &to )
{
  if( IsValid(pEff) )
    pEff->SetRotation( CQuat(to - from) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NDb::Ptr<NDb::EffectBase> FemaleMaleAssistEffect::ClientObject::GetEffectId( NDb::EFemaleMaleAssistEffectSate num )
{
  return NDb::SessionRoot::GetRoot()->visualRoot->
    femaleMaleAssistEffect.effectsWithDelay[num].effect;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void FemaleMaleAssistEffect::ClientObject::StartEffectFromHeroesToMiddle()
{
  for( int i = 0; i < ARRAY_SIZE(assistants); ++i )
    if( IsValid(assistants[i]) )
    {
      CObj<PF_Core::BasicEffect> pEff = CreateEffect( 
        GetEffectId(NDb::FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE), 
        SceneObjectPosType(assistants[i]->GetClientSceneObject()) 
      );
      ApplyOrientation( pEff, assistants[i]->GetVisualPosition3D(), middlePos );
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::StartEffectFromMiddleToHeroes()
{
  for( int i = 0; i < ARRAY_SIZE(assistants); ++i )
    if( IsValid(assistants[i]) )
    {
      CObj<PF_Core::BasicEffect> pEff = CreateEffect( 
        GetEffectId(NDb::FEMALEMALEASSISTEFFECTSATE_MIDDLETOHERO), 
        StaticPosType(middlePos) 
      );
        
      ApplyOrientation( pEff, middlePos, assistants[i]->GetVisualPosition3D() );
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::StartEffectInMiddle()
{
  CObj<PF_Core::BasicEffect> pEff = CreateEffect( 
    GetEffectId(NDb::FEMALEMALEASSISTEFFECTSATE_SINGLEATMIDLE), 
    StaticPosType(middlePos) 
  );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::StartEffectInFlash()
{
  curFlashEffectNum = ++totalFlashEffectsCount;
  pFlashConnection->CreateEffect( curFlashEffectNum );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::SelfDestroy()
{
  pFlashConnection->DestroyEffect( curFlashEffectNum );
  Unsubscribe();
  pThis = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::ClientObject::UpdateFlashEffectPos()
{
  if( curFlashEffectNum == 0 )
    return;
    
  const SHMatrix mtx = pScene->GetCamera()->GetProjectiveMatrix() * pScene->GetCamera()->GetViewMatrix();

  UI::Point uiPoint;
  UI::GetWindowPlacement( &uiPoint, 0, middlePos, 0, mtx );
  
  pFlashConnection->UpdatePosition( curFlashEffectNum, uiPoint );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class FemaleMaleAssistEffect
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FemaleMaleAssistEffect::FemaleMaleAssistEffect()
{
  Reset( pFlashConnection, new DumyFemaleMaleAssistEffectFlashConnection() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FemaleMaleAssistEffect::~FemaleMaleAssistEffect()
{
  //Nothing
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool isMaleFemale( const PFBaseUnit &u1, const PFBaseUnit &u2 )
{
  return 
    u1.IsMale() && u1.GetZZimaSex() == ZZSEX_MALE &&  
    !u2.IsMale() && u2.GetZZimaSex() == ZZSEX_FEMALE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool isHeterosexuals( const PFBaseUnit &u1, const PFBaseUnit &u2 )
{
  return isMaleFemale(u1, u2) || isMaleFemale(u2, u1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float DistanceSquared( const CVec3 &v1, const CVec3 &v2 )
{
  const CVec3 diff( v1 - v2 );
  return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                  
void FemaleMaleAssistEffect::OnUnitDie( CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller, const HeroesCont &assistants ) const
{
  //Убили героя или башню
  if( !IsValid(pVictim) || 
      !( dynamic_cast<PFTower *>(pVictim.GetPtr()) != 0 || pVictim->IsTrueHero() ) )
    return;
    
  //Герой убийца жив на момент начала визуализации
  if( !IsValid(pKiller) || pKiller->IsDead() || !pKiller->IsHero() )
    return;
     
  float maxDistanceSquared = NDb::SessionRoot::GetRoot()->visualRoot->femaleMaleAssistEffect.minDistanceBetweenHeroes;
  maxDistanceSquared = maxDistanceSquared * maxDistanceSquared;
  
  //Выбираем наиболее близкую друг к другу пару
  float bestDistance = FLT_MAX;
  PFBaseHero *pPairForKiller = 0;
                                         
  for( HeroesCont::const_iterator it = assistants.begin(); it != assistants.end(); ++it )
  {
    //Герой поддержки жив на момент начала визуализации
    if( !IsValid(*it) || (*it)->IsDead() || !(*it)->IsHero() )
      continue;
    
    //Герой убийца и герой поддержки разного пола
    if( !isHeterosexuals( *pKiller, **it ) )
      continue;   
      
    //Расстояние между героями при совершении убийства не более чем N метра
    const float distance = DistanceSquared( pKiller->GetPosition(), (*it)->GetPosition() );
    
    if( distance > maxDistanceSquared )
      continue; 
      
    if( distance < bestDistance )
    {
      pPairForKiller = *it;
      bestDistance = distance; 
    }
  } 
  
  if( pPairForKiller != 0 ) 
    PlayEffect( pKiller,  pPairForKiller ); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FemaleMaleAssistEffect::PlayEffect( CPtr<PFBaseUnit> pKiller, CPtr<PFBaseUnit> pAssistant ) const
{
  #ifndef VISUAL_CUTTED
    //Играем эффект только для локальных игроков
    PFBaseHero * const pLocalHero = NGameX::AdventureScreen::Instance()->GetHero();
    
    if( pLocalHero == pKiller || pLocalHero == pAssistant )   
      new ClientObject( pKiller, pAssistant, &*pFlashConnection );
  #endif     
}

} //namespace AIWorldFacets
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TestFemaleMaleAssistEffect( const char *name, const vector<wstring> &params )
{
  NGameX::AdventureScreen *const pAS = NGameX::AdventureScreen::Instance();
  NWorld::PFWorld *const pWorld = pAS->GetWorld();

  CPtr<PFBaseUnit> pVictim;
  CPtr<PFBaseUnit> pKiller;
  AIWorldFacets::FemaleMaleAssistEffect::HeroesCont assistants;

  for( int i = 0; i < pWorld->GetPlayersCount(); ++i )
  {
    PFBaseHero * const pCurHero = pWorld->GetPlayer(i)->GetHero();

    if( !IsValid(pCurHero) )
      continue;

    if( pCurHero == pAS->GetHero() )
      pKiller = pCurHero;
    else if( pCurHero->GetFaction() != pAS->GetHero()->GetFaction() )
      pVictim = pCurHero;
    else 
      assistants.push_back( pCurHero );
  } 
  
  pWorld->GetAIWorld()->femaleMaleAssistEffect.OnUnitDie( pVictim, pKiller, assistants ); 
  
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_DEV_CMD( test_heterosexual_interaction, TestFemaleMaleAssistEffect);

} //namespace NWorld 
 
REGISTER_SAVELOAD_CLASS_NM( FemaleMaleAssistEffect, NWorld::AIWorldFacets )