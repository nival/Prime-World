#include "stdafx.h"

#include "PFClientNatureSceneObjectsHolder.h"
#include "../PF_Core/EffectsPool.h"


namespace
{
  bool g_bFreezeNonanimatedMSO = false;
}

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nature Transactions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DoEffect( NScene::SceneObject* pSO, NDb::Ptr<NDb::EffectBase> const& pEffectDesc, NScene::IScene* pScene )
{
  if ( pEffectDesc && pSO->IsVisible() )
    if ( CObj<PF_Core::BasicEffectStandalone> pEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>(pEffectDesc) )
    {
      pEffect->Apply( pSO );
    }
}

bool IsSceneObjectAnimated( NScene::SceneObject* pSO )
{
  struct AnimationChecker : public NScene::FullTraverser, private NonCopyable
  {
    AnimationChecker() : componentsCount(0), animated(false) {}
    // object is animated, if animation length more then zero
    bool IsAnimated() const { return (componentsCount > 1) && animated; }
    void operator()(NScene::SceneComponent* pComponent) {
      componentsCount++;
      if ( pComponent->GetPureAnimLength() > 0.0f )
        animated = true;
    }
    virtual bool IsTraversable(const NScene::SceneComponent*) const { return !IsAnimated(); } //do not travers if already found animation
  private:
    int componentsCount;
    bool animated;
  } checker;
  
  if (pSO)
    pSO->Traverse(checker);
  
  return checker.IsAnimated();
}

//////////////////////////////////////////////////////////////////////////

class NatureTransaction
{
public:
  enum TransactionState
  {
    waiting,  // задержка старта
    started,  // исполняется
    finished,  // закончено
  };
  inline TransactionState GetState() const { return state; }
  inline bool IsFinished() const  {  return GetState() == finished;  }
  inline float GetTimeEstimate()const
  {
    return GetState() == finished ? 0 : startDelay + lifeTime;
  }
  virtual ~NatureTransaction()
  {
    if ( GetState() == started )
      OnStop();
  }
  virtual void Update(float dt)
  {
    switch (state)
    {
    case waiting:
      startDelay-=dt;
      if (startDelay < EPS_VALUE)
        OnStart();
      break;
    case started:
      lifeTime-=dt;
      if (lifeTime < EPS_VALUE)
        OnStop();
      break;
    default:
      NI_ALWAYS_ASSERT("Wrong transaction state!");
    } //case (state)
  }

protected:
  NatureTransaction(NScene::SceneObject* pSceneObject)
    : pSceneObject(pSceneObject)
    , isAnimated( g_bFreezeNonanimatedMSO ? IsSceneObjectAnimated(pSceneObject) : true ) // temporary disabled
    , startDelay(0.0f)
    , lifeTime(0.0f)
    , state(waiting)
  {
  }

  virtual void OnStart()
  {
    startDelay = 0.0f;
    state = started;
  }
  virtual void OnStop()
  {
    startDelay = 0.0f;
    lifeTime = 0.0f;
    state = finished;
		if ( pSceneObject )
		{
			pSceneObject->ResetTrack();
			pSceneObject->Reinit();
		}
  }
  //~~~
  NScene::SceneObject*  pSceneObject;
  TransactionState      state;
  float                 startDelay;
  float                 lifeTime;
  bool                  isAnimated;
};

//////////////////////////////////////////////////////////////////////////

class FadeInTransaction : public NatureTransaction
{
public:
  FadeInTransaction( NScene::IScene* pScene, NScene::SceneObject* pSceneObject, float fadeInTime, float fadeInOffset, NDb::Ptr<NDb::EffectBase> const& pEffectDesc, bool forced )
    : NatureTransaction(pSceneObject)
    , pScene(pScene)
    , pEffectDesc(pEffectDesc)
    , fOpacity(0.0f)
    , fadeInTime(fadeInTime)
  {
    startDelay = fadeInOffset;
    
    if (forced)
    {
			pSceneObject->ResetTrack();
			pSceneObject->Reinit();
			pSceneObject->UpdateForced(lifeTime);

			if (!isAnimated)
        pSceneObject->SetFreeze(false);
      
      if ( !pSceneObject->IsInScene() )
        pSceneObject->AddToScene(pScene);
			pSceneObject->Reinit();
      
      if (!isAnimated)
        pSceneObject->SetFreeze(true);
      
      pSceneObject->UpdateForced(lifeTime);

      NatureTransaction::OnStop();
    }
  }
  virtual void OnStart()
  {
    if (pSceneObject)
    {
			pSceneObject->Reinit();
      lifeTime = pSceneObject->ApplyTrack("fadeIn");

      pSceneObject->UpdateForced();
      if ( !pSceneObject->IsInScene() )
        pSceneObject->AddToScene(pScene);
      if (!isAnimated)
        pSceneObject->SetFreeze(false);
      DoEffect(pSceneObject, pEffectDesc, pScene);
    }
    NatureTransaction::OnStart();
  }
  virtual void OnStop()
  {
    if ( pSceneObject )
    {
      if (!isAnimated)
        pSceneObject->SetFreeze(true);
    }

    NatureTransaction::OnStop();
  }
private:
  NScene::IScene* pScene;
  NDb::Ptr<NDb::EffectBase> pEffectDesc;
  float fadeInTime;
  float fOpacity;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FadeOutTransaction : public NatureTransaction
{
public:
  FadeOutTransaction( NScene::SceneObject* pSceneObject, float fadeOutTime, NDb::Ptr<NDb::EffectBase> const& pEffectDesc, AutoPtr<NatureTransaction>& fadeInTrans_, bool forced )
    : NatureTransaction(pSceneObject)
    , pEffectDesc(pEffectDesc)
    , pScene(pSceneObject ? pSceneObject->GetScene() : NULL)
    , fOpacity(1.0f)
    , fadeOutTime(fadeOutTime)
{
    if (fadeInTrans_)
    {
      if ( fadeInTrans_->GetState() == started )
      {
        startDelay = fadeInTrans_->GetTimeEstimate();
        fadeInTrans = fadeInTrans_;
      }
      else
      {
        ::Reset(fadeInTrans_);
      }
    }
    if ( forced )
    {
      if ( pSceneObject )
      {
        if (!isAnimated)
          pSceneObject->SetFreeze(false);
        pSceneObject->RemoveFromScene();
      }
      NatureTransaction::OnStop();
    }
  }
  virtual void Update(float dt)
  {
    NatureTransaction::Update(dt);
    
    if ( fadeInTrans && fadeInTrans->GetState() == started )
    {
      // update fadeInTransaction
      fadeInTrans->Update(dt);
      if (fadeInTrans->GetState() == finished)
        ::Reset(fadeInTrans); // fade in finished
    }
  }
private:
  virtual void OnStart()
  {
    if ( pSceneObject )
    {
      lifeTime = pSceneObject->ApplyTrack("fadeOut");

      if ( !isAnimated )
        pSceneObject->SetFreeze(false);

      DoEffect(pSceneObject, pEffectDesc, pScene);
    }
    NatureTransaction::OnStart();
  }
  virtual void OnStop()
  {
    if ( pSceneObject && pSceneObject->IsInScene() )
    {
      if (!isAnimated)
        pSceneObject->SetFreeze(true);
      pSceneObject->RemoveFromScene();
    }
    NatureTransaction::OnStop();
  }
  
  NScene::IScene*           pScene;
  NDb::Ptr<NDb::EffectBase> pEffectDesc;
  AutoPtr<NatureTransaction> fadeInTrans;
  float fadeOutTime;
  float fOpacity;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DropTreeTransaction : public NatureTransaction
{
public:
  DropTreeTransaction( NScene::SceneObject* pSceneObject, const CVec2& _dropDirection, const NDb::Ptr<NDb::EffectBase>& _pEffectDesc, 
    AutoPtr<NatureTransaction>& _fadeInTrans, float _lifeTime )
    : NatureTransaction( pSceneObject )
    , pEffectDesc( _pEffectDesc )
    , initialPlace( pSceneObject->GetPosition() )
    , startOffset( 0.0f )
    , dropDirection( _dropDirection )
    , fadeInTrans( _fadeInTrans )
  {
    Normalize( &dropDirection );
    lifeTime = _lifeTime;
  }
private:
  void OnStart()
  {
    NatureTransaction::OnStart();
    if ( pSceneObject )
    {
      pSceneObject->ApplyTrack( "drop" );

      Placement newBasePlacement = NULLPLACEMENT;
      Placement currentPlacement = pSceneObject->GetPosition();

      CVec3 defaultDir( 0.0f, 1.0f, 0.0f );
      CVec3 currentDir = currentPlacement.rot.GetDirection();
      newBasePlacement.rot.FromToRotation( currentDir, defaultDir );

      CVec3 newDir = newBasePlacement.rot.Rotate( CVec3( dropDirection, 0.0f ) );

      pSceneObject->SetTrackDirection( newDir );
    }
  }

  void OnStop()
  {
    pSceneObject->SetPlacement( initialPlace );
    pSceneObject->UpdateForced();
    pSceneObject->RemoveFromScene();
    NatureTransaction::OnStop();
  }
protected:
  AutoPtr<NatureTransaction>  fadeInTrans;
  NDb::Ptr<NDb::EffectBase>   pEffectDesc;
  Placement                   initialPlace;
  float                       startOffset;
  CVec2                       dropDirection;
};

static inline int GetOppositeDayNightObjectIndex(const int index)
{
  if (index < NDb::KnownEnum<NDb::ENatureType>::SizeOf())
    return index + NDb::KnownEnum<NDb::ENatureType>::SizeOf();
  else
    return index - NDb::KnownEnum<NDb::ENatureType>::SizeOf();
}

static inline void SetTransaction(AutoPtr<NatureTransaction>& p, NatureTransaction* const transaction)
{
  AutoPtr<NatureTransaction> holder(transaction);

  if (transaction->IsFinished())
    ::Reset(p);
  else
    ::Swap(p, holder);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nature Scene Objects Holder
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureSceneObjectsHolder::InitInstance(NatureSceneObjectsHolder* const instance, const NDb::MultiStateObject* const mso)
{
  instance->InternalSelectActiveObject();

  const Entry& entry = instance->entries[instance->activeObjectInternal];

  if (entry.sceneObject)
    entry.sceneObject->AddToScene(instance->pScene);
}

NatureSceneObjectsHolder* NatureSceneObjectsHolder::Create(NScene::IScene* const pScene, NScene::ISceneObjectUpdateHook* const pHook, const Placement& place, const int worldObjectId, const NDb::MultiStateObject* const mso)
{
  NI_DATA_ASSERT((mso->sceneObjects.size() + mso->nightSceneObjects.size()) == SceneObjectCount, "Unexpected data!");

  NatureSceneObjectsHolder* const instance = new NatureSceneObjectsHolder(pScene, mso->distinct, mso->fadeInOffset, mso->dropTime);

  {
    const int offset = 0 * NDb::KnownEnum<NDb::ENatureType>::SizeOf();

    const NDb::Ptr<NDb::MSOTransactions>& effects = mso->effects;
    const vector<NDb::Ptr<NDb::DBSceneObject>>& sceneObjects = mso->sceneObjects;

    if (IsValid(effects))
    {
      for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
      {
        Entry& entry = instance->entries[offset + i];

        switch (i)
        {
        case NDb::NATURETYPE_N:
          entry.dbEffectIn  = effects->effectN.effectIn;
          entry.dbEffectOut = effects->effectN.effectOut;
          break;
        case NDb::NATURETYPE_A:
          entry.dbEffectIn  = effects->effectA.effectIn;
          entry.dbEffectOut = effects->effectA.effectOut;
          break;
        case NDb::NATURETYPE_B:
          entry.dbEffectIn  = effects->effectB.effectIn;
          entry.dbEffectOut = effects->effectB.effectOut;
          break;
        default:
          NI_ALWAYS_ASSERT("Invalid nature type!");
        }
      }
    }

    for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
    {
      if (!IsValid(sceneObjects[i]))
        continue;

      NScene::SceneObjectRef sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, sceneObjects[i], BADNODENAME );

      sceneObject->SetOwnerID(worldObjectId);
      sceneObject->SetPlacement(place);
      sceneObject->UpdateForced(); // recalculate OOBB
      sceneObject->SetUpdateHook(pHook); // Set hook after update

      Entry& entry = instance->entries[offset + i];

      entry.sceneObject = sceneObject;
    }
  }

  {
    const int offset = 1 * NDb::KnownEnum<NDb::ENatureType>::SizeOf();

    const NDb::Ptr<NDb::MSOTransactions>& effects = mso->nightEffects;
    const vector<NDb::Ptr<NDb::DBSceneObject>>& sceneObjects = mso->nightSceneObjects;

    if (IsValid(effects))
    {
      for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
      {
        Entry& entry = instance->entries[offset + i];

        switch (i)
        {
        case NDb::NATURETYPE_N:
          entry.dbEffectIn  = effects->effectN.effectIn;
          entry.dbEffectOut = effects->effectN.effectOut;
          break;
        case NDb::NATURETYPE_A:
          entry.dbEffectIn  = effects->effectA.effectIn;
          entry.dbEffectOut = effects->effectA.effectOut;
          break;
        case NDb::NATURETYPE_B:
          entry.dbEffectIn  = effects->effectB.effectIn;
          entry.dbEffectOut = effects->effectB.effectOut;
          break;
        default:
          NI_ALWAYS_ASSERT("Invalid nature type!");
        }
      }
    }

    for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
    {
      if (!IsValid(sceneObjects[i]))
        continue;

      NScene::SceneObjectRef sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, sceneObjects[i], BADNODENAME );

      sceneObject->SetOwnerID(worldObjectId);
      sceneObject->SetPlacement(place);
      sceneObject->UpdateForced(); // recalculate OOBB
      sceneObject->SetUpdateHook(pHook); // Set hook after update

      Entry& entry = instance->entries[offset + i];

      entry.sceneObject = sceneObject;
    }
  }

  InitInstance(instance, mso);

  return instance;
}

NatureSceneObjectsHolder* NatureSceneObjectsHolder::CreateWithTreeStubs(NScene::IScene* const pScene, NScene::ISceneObjectUpdateHook* const pHook, const Placement& place, const int worldObjectId, const NDb::TreeObject* const mso)
{
  NI_DATA_ASSERT((mso->stubsSceneObjects.size() + mso->nightStubsSceneObjects.size()) == SceneObjectCount, "Unexpected data!");

  NatureSceneObjectsHolder* const instance = new NatureSceneObjectsHolder(pScene, mso->distinct, mso->fadeInOffset, mso->dropTime);

  {
    const int offset = 0 * NDb::KnownEnum<NDb::ENatureType>::SizeOf();

    const vector<NDb::Ptr<NDb::DBSceneObject>>& sceneObjects = mso->stubsSceneObjects;

    for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
    {
      if (!IsValid(sceneObjects[i]))
        continue;

      NScene::SceneObjectRef sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, sceneObjects[i], BADNODENAME );

      sceneObject->SetOwnerID(worldObjectId);
      sceneObject->SetPlacement(place);
      sceneObject->UpdateForced(); // recalculate OOBB
      sceneObject->SetUpdateHook(pHook); // Set hook after update

      Entry& entry = instance->entries[offset + i];

      entry.sceneObject = sceneObject;
    }
  }

  {
    const int offset = 1 * NDb::KnownEnum<NDb::ENatureType>::SizeOf();

    const vector<NDb::Ptr<NDb::DBSceneObject>>& sceneObjects = mso->nightStubsSceneObjects;

    for (int i = 0, count = NDb::KnownEnum<NDb::ENatureType>::SizeOf(); i < count; ++i)
    {
      if (!IsValid(sceneObjects[i]))
        continue;

      NScene::SceneObjectRef sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, sceneObjects[i], BADNODENAME );

      sceneObject->SetOwnerID(worldObjectId);
      sceneObject->SetPlacement(place);
      sceneObject->UpdateForced(); // recalculate OOBB
      sceneObject->SetUpdateHook(pHook); // Set hook after update

      Entry& entry = instance->entries[offset + i];

      entry.sceneObject = sceneObject;
    }
  }

  InitInstance(instance, mso);

  return instance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NatureSceneObjectsHolder::NatureSceneObjectsHolder(NScene::IScene* const pScene, const bool distinct, const float fadeInOffset, const float dropTime)
  : pScene(pScene)
  , distinct(distinct)
  , fadeInOffset(fadeInOffset)
  , dropTime(dropTime)
  , enabled(true)
  , activeObject(0)
  , activeObjectInternal(0)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NatureSceneObjectsHolder::~NatureSceneObjectsHolder()
{
  ::Reset(fadeInTrans);
  ::Reset(fadeOutTrans);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::SetActive(int index, bool visible)
{
  NI_VERIFY( index >= 0, "Wrong index!", return );
  NI_VERIFY( index < GetCount(), "Wrong index!", return );

  if (index == activeObject)
    return;

  activeObject = index;

  if (!distinct)
  {
    const int ia = activeObjectInternal;
    const int ib = GetOppositeDayNightObjectIndex(activeObjectInternal);

    if (index == ia || index == ib)
      return;
  }

  if (enabled && GetSceneObject(activeObjectInternal))
  {
    //транзакцию затухания перегружаем, только если она ещё не стартовала
    if (!fadeOutTrans)
    {
      SetTransaction(fadeOutTrans, new FadeOutTransaction(::Get(GetSceneObject(activeObjectInternal)), GetTransFadeOutTime(), GetTransEffect(activeObjectInternal, false), fadeInTrans, !visible));
    }
  }

  InternalSelectActiveObject();

  if (enabled && GetSceneObject(activeObjectInternal))
  {
    {
      SetTransaction(fadeInTrans, new FadeInTransaction(pScene, ::Get(GetSceneObject(activeObjectInternal)), GetTransFadeInTime(), fadeInOffset, GetTransEffect(activeObjectInternal, true), !visible));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::DropTree( const CVec2& direction, const NDb::Ptr<NDb::TreeObject>& pDBDesc )
{
  if( enabled && !fadeOutTrans )
  {
    ::Reset( fadeOutTrans, new DropTreeTransaction( ::Get( GetSceneObject(activeObjectInternal) ), direction, NULL, fadeInTrans, dropTime ) );
  }
  else
  {
    ::Reset( fadeInTrans ); // cancel delayed fadeIn transaction, if exist
  }

	enabled = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::Enable(bool bEnable, bool forced)
{
  // Если не forced, объект будет поставлен/удален со сцены через транзакции.
  // Однако при этом будет проиграна только анимация и не будет проигран эффект

  if (bEnable == enabled)
    return;

  enabled = bEnable;

  NScene::SceneObjectRef& sceneObject = GetSceneObject(activeObjectInternal);

  if (!sceneObject)
    return;

  if (forced)
  {
    ::Reset(fadeInTrans);
    ::Reset(fadeOutTrans);

    if (enabled)
      sceneObject->AddToScene(pScene);
    else
      sceneObject->RemoveFromScene();

    return;
  }

  if (enabled)
  {
    {
      SetTransaction(fadeInTrans, new FadeInTransaction(pScene, ::Get(sceneObject), 0, fadeInOffset, NDb::Ptr<NDb::EffectBase>(), false));
    }
  }
  else
  {
    //транзакцию затухания перегружаем, только если она ещё не стартовала
    if (!fadeOutTrans)
    {
      SetTransaction(fadeOutTrans, new FadeOutTransaction(::Get(sceneObject), 0, NDb::Ptr<NDb::EffectBase>(), fadeInTrans, false));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::Reset()
{
  Enable(false);

  for ( int i = 0; i < SceneObjectCount; ++i )
    ::Reset(entries[i].sceneObject);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::Update(float dt)
{
  if ( fadeOutTrans )
  {
    fadeOutTrans->Update(dt);
    if ( fadeOutTrans->IsFinished() )
      ::Reset(fadeOutTrans);
  }
  if ( fadeInTrans )
  {
    fadeInTrans->Update(dt);
    if ( fadeInTrans->IsFinished() )
      ::Reset(fadeInTrans);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NatureSceneObjectsHolder::NeedUpdateTransactions() const
{
  return fadeInTrans || fadeOutTrans;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::EffectBase> const& NatureSceneObjectsHolder::GetTransEffect( int natureIndex, bool fadeInEffect )
{
  static const NDb::Ptr<NDb::EffectBase> noEffect(NULL);

  if (natureIndex < 0)
    return noEffect;
  if (natureIndex >= GetCount())
    return noEffect;

  return fadeInEffect ? entries[natureIndex].dbEffectIn : entries[natureIndex].dbEffectOut;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float NatureSceneObjectsHolder::GetTransFadeInTime() const
{
  return fadeInOffset;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float NatureSceneObjectsHolder::GetTransFadeOutTime() const
{
  return fadeInOffset;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureSceneObjectsHolder::InternalSelectActiveObject()
{
  activeObjectInternal = activeObject;

  if (distinct)
    return;
  if (GetSceneObject(activeObjectInternal))
    return;

  const int opposite = GetOppositeDayNightObjectIndex(activeObject);

  if (GetSceneObject(opposite))
    activeObjectInternal = opposite;
}

} //namespace NGameX

REGISTER_DEV_VAR("mso_freeze", g_bFreezeNonanimatedMSO, STORAGE_NONE);
