#include "stdafx.h"

#include "../System/RandomGen.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/RecolorableTexture.h"
#include "PFBaseUnit.h"
#include "PFClientBaseUnit.h"
#include "PFClientDispatch.h"
#include "libdb/ClonedPtr.h"
#ifndef VISUAL_CUTTED
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "../Render/debugrenderer.h"

#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"

using namespace PF_Core;

namespace NGameX
{

  bool IsEffectEnabled(NDb::Ptr<NDb::EffectBase> effect, const NWorld::PFDispatch* dispatch)
  {
    bool isEnable = true;

    if(IsValid(effect) && !effect->enableCondition.IsEmpty()){

      IUnitFormulaPars* pFirst = dispatch->GetSender();
      IUnitFormulaPars* pSecond = NULL;
      IMiscFormulaPars* pMisc = (IMiscFormulaPars*)dispatch->GetAbility()->GetData();

      if(dispatch->GetTarget().IsUnit())
        pSecond = dispatch->GetTarget().GetUnit();

      isEnable = effect->enableCondition->condition(pFirst,pSecond, pMisc, isEnable);
    }

    return isEnable;
  }

  namespace
  {

    float const s_rotYawSpeed = 10.f;
    float const s_rotPitchSpeed = 10.f;
    float const s_predictDistance = 10.f;

    inline float GetYaw( const CVec2& at )
    {
      float yaw = FP_PI2 + atan2( at.y, at.x );

      if ( yaw > FP_PI )
      {
        yaw -= FP_2PI;
      }

      return yaw;
    }

    float Approach_(float from, float to, float maxStep)
    {
      NI_ASSERT(maxStep >= 0.f, "Strange");
      float dist = fabs(to - from);

      if (dist <= maxStep)
      {
        return to;
      }

      if (from > to)
        maxStep = -maxStep;

      if (dist > FP_PI)
        maxStep = -maxStep;

      float res = from + maxStep;

      if (res > FP_PI)
      {
        res -= FP_2PI;
      }
      else if (res < -FP_PI)
      {
        res += FP_2PI;
      }

      return res;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    NDb::EffectBase const *GetDispatchEffectDB(const NWorld::PFDispatch* dispatch)
    {
      if (!IsValid(dispatch))
      {
        return NULL;
      }

      int teamID = dispatch->GetSender()->GetOriginalTeamId();
      if (teamID == -1)
      {
        teamID = NDb::TEAMID_A;
      }

      const NDb::Ptr<NDb::Dispatch>& dbPrt = dispatch->GetDBBase();

      if ( dbPrt->dispatchEffect[teamID].IsEmpty() )
      {
        teamID = teamID == NDb::TEAMID_B ? NDb::TEAMID_A : NDb::TEAMID_B;
      }

      dbPrt->dispatchEffect[teamID].ChangeState(dispatch->GetSender()->GetSkinId());

      return dbPrt->dispatchEffect[teamID];
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    NDb::EffectBase const *GetApplyEffectDB(CPtr<NWorld::PFDispatch> dispatch)
    {
      if (!IsValid(dispatch))
      {
        return NULL;
      }

      int teamID = dispatch->GetSender()->GetOriginalTeamId();
      if (teamID == -1)
      {
        teamID = NDb::TEAMID_A;
      }

      const NDb::Ptr<NDb::Dispatch>& dbPrt = dispatch->GetDBBase();

      if ( dbPrt->applyEffect[teamID].IsEmpty() )
      {
        teamID = teamID == NDb::TEAMID_B ? NDb::TEAMID_A : NDb::TEAMID_B;
      }

      dbPrt->applyEffect[teamID].ChangeState(dispatch->GetSender()->GetSkinId());

      return dbPrt->applyEffect[teamID];
    }

    bool inline ApplyEffectWillBeVisible(CPtr<NWorld::PFDispatch> dispatch, CVec3 const &pos)
    {
      AdventureScreen * screen = AdventureScreen::Instance();

      if ( dispatch->GetSender() && (dispatch->GetSender()->GetFaction() == screen->GetPlayerFaction())) 
      {
        return true;
      }
      else
      {
        return screen->GetClientVisibilityMap()->IsPointVisible(pos.AsVec2D());
      }
    }  
  }

  void PFDispatchPlayEffectCollection(NDb::EffectBase const *applyEffect, float height, CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target)
  {
    if (!IsEffectEnabled(applyEffect, dispatch))
      return;

    if (applyEffect->GetObjectTypeID() != NDb::EffectList::typeId )
    {
      NDb::EffectList const *applyEffectList = static_cast<NDb::EffectList const *>(applyEffect);
      EffectListEntries::const_iterator iter = applyEffectList->effects.begin();

      while(iter !=  applyEffectList->effects.end())
      {
        PFDispatchPlayEffect(*iter++, height, dispatch, pWorld, target);
      }
    }
    else{
      PFDispatchPlayEffect(applyEffect, height, dispatch, pWorld, target);
    }
  }

  void PFDispatchPlayEffect(NDb::EffectBase const *applyEffect, float height, CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target)
  {

    if (!IsEffectEnabled(applyEffect, dispatch))
      return;

    CObj<BasicEffect> pBasicEffect;
    NDb::Ptr<NDb::Dispatch> dbDispatch = dispatch->GetDBBase();

    if (target.IsObject() && IsValid(target.GetObject()))
    {
      NI_VERIFY(target.GetObject()->ClientObject(), 
        "Client object should present", return;);

      if ( !dbDispatch->applyEffectIgnoreVisibility && 
        !target.IsVisibleForFaction( pWorld, AdventureScreen::Instance()->GetPlayerFaction() ) )
        return;

      pBasicEffect = EffectsPool::Get()->Retrieve(applyEffect);

      if (!pBasicEffect)
        return;

      CPtr<ClientObjectBase> pClientObject(target.GetObject()->ClientObject());
      
      pBasicEffect->SetEnableCallback( dispatch );
      pBasicEffect->Apply( pClientObject );

      if ( height > 0.0f )
      {
        bool isLocatorGeneral = false;
        if ( applyEffect->GetObjectTypeID() == NDb::BasicEffectAttached::typeId )
        {
          const NDb::BasicEffectAttached* pBasicEffectAttached = static_cast<const NDb::BasicEffectAttached*>( applyEffect );
          if ( pBasicEffectAttached->attachType ==  NDb::EnumToString( NDb::EFFECTATTACHTYPE_GENERAL ) )
          {
            isLocatorGeneral = true;
          }
        }

        if ( isLocatorGeneral )
        {
          pBasicEffect->SetHeightAboveLocator( height );
        }
        else
        {
          Placement placement;
          placement.pos.z = height;
          pBasicEffect->AddLocator( placement );
        }
      }
    }
    else
    {
      if (applyEffect->GetObjectTypeID() != NDb::BasicEffectStandalone::typeId && applyEffect->GetObjectTypeID() != NDb::EffectSwitcher::typeId )
        return;

      // don't show apply effect on invisible position
      if (!ApplyEffectWillBeVisible(dispatch, target.GetPosition()))
        return;

      CObj<BasicEffectStandalone> pEffect = RetrieveStandaloneEffect(applyEffect, dispatch->GetSender().GetPtr() );
      if (!pEffect)
        return;

      CVec3 pos = target.AcquirePosition();
      pWorld->GetScene()->GetHeightsController().GetHeight( pos.x, pos.y, 1, &pos.z, 0 );

      if ( height > 0.0f )
      {
        pos.z += height;
      }

      pEffect->SetPosition(pos);
      pEffect->AddToScene(pWorld->GetScene());

      pBasicEffect = pEffect;
    }

    // set orientation
    if ( dbDispatch->applyEffectOrientation != NDb::APPLYEFFECTORIENTATION_DEFAULT )
    {
      CQuat rot = QNULL;

      switch (dbDispatch->applyEffectOrientation)
      {
      case NDb::APPLYEFFECTORIENTATION_RANDOM:
        {
          float angle = 0.f;
          if (dbDispatch->applyEffectRandomAnglePoints > 0)
          {
            angle = NRandom::Random(dbDispatch->applyEffectRandomAnglePoints) * FP_2PI / dbDispatch->applyEffectRandomAnglePoints;
          }
          else
          {
            angle = NRandom::Random(0.f, FP_2PI);
          }
          rot.FromEulerAngles(angle, 0.f, 0.f);
          break;
        }

      case NDb::APPLYEFFECTORIENTATION_MOTION:
        {
          PFDispatchUniformLinearMove *pLinearDispatch = dynamic_cast<PFDispatchUniformLinearMove*>( dispatch->ClientObject() );
          NI_ASSERT(pLinearDispatch, "Can't find source dispatch");
          if (pLinearDispatch)
          {
            pLinearDispatch->ForceFinish(); // ensure dispatch placement is correct
            rot.FromEulerAngles(pLinearDispatch->GetCurYaw() + FP_PI, 0.f, 0.f);
            NI_ASSERT(rot.IsFinite(), "Invalid rotation");
          }
          break;
        }

      case NDb::APPLYEFFECTORIENTATION_LOGICALDIRECTION:
        {
          CVec3 dir = CVec3( dispatch->GetCurrentPosition().AsVec2D() - dispatch->GetSource().AcquirePosition().AsVec2D(), 0.0f );
          rot.FromDirection( dir, true );
          NI_ASSERT(rot.IsFinite(), "Invalid rotation");
          break;
        }
      }

      pBasicEffect->SetRotation(rot);
    }

  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchPlayApplyEffect(CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target)
  {
    float height = 0.0f;
    NDb::Ptr<NDb::Dispatch> dbDispatch = dispatch->GetDBBase();
    NDb::EffectBase const *applyEffect = GetApplyEffectDB(dispatch);

    if (!applyEffect)
      return;

    NWorld::PFDispatchUniformLinearMove* pDispatchUniformLinearMove =
      dynamic_cast<NWorld::PFDispatchUniformLinearMove*>( dispatch.GetPtr() );


    if ( pDispatchUniformLinearMove )
    {
      height = pDispatchUniformLinearMove->GetDB().height;
    }

    if(applyEffect->GetObjectTypeID() == NDb::EffectList::typeId)
    {
      NDb::EffectList const *applyEffectList = static_cast<NDb::EffectList const *>(applyEffect);
      EffectListEntries::const_iterator iter = applyEffectList->effects.begin();

      while(iter !=  applyEffectList->effects.end())
      {
        PFDispatchPlayEffect(*iter++, height, dispatch, pWorld, target);
      }
    }
    else
    {
      PFDispatchPlayEffect(applyEffect, height, dispatch, pWorld, target);
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFDispatchUniformLinearMove::PFDispatchUniformLinearMove(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis, float startDelay)
    : NWorld::PFClientObjectBase(pWO)
    , pScene(pScene)
    , curYaw(0.f), curPitch(0.f), desiredYaw(0.f), desiredPitch(0.f)
    , bAlignToAxis(bAlignToAxis)
    , curHeight(0.f)
    , curveTg(0.f)
    , dest(VNULL3)
    , currentPos(VNULL3)
    , startMatrix(QNULL, VNULL3)
    , travelledDistance(0.f)
    , bStarted(false)
    , bArrived(false)
    , startDelay(startDelay)
    , curWorldPos(0.0f, 0.0f)
    , speedModifier(1.0f)
    , prevDest(VNULL3)
    , isUnitBeforeMount(false)
  {
    bool bOk = GetStartPos(currentPos, startMatrix);
    NI_ASSERT(bOk, NStr::StrFmt("Failed to retrieve dispatch start pos for %s !", GetFormattedDbId(WorldObject()->GetDB().GetDBID()).c_str()) );

    if( startDelay < EPS_VALUE )
    {
      Start();
    }
    else
    {
      SubscribeAfterScene();
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFDispatchUniformLinearMove::GetStartPos( CVec3& result, Matrix43& matrix ) const
  {
    const NWorld::PFDispatchUniformLinearMove* pWorldObject = WorldObject();
    if( NULL == pWorldObject )
      return false;

    CPtr<NWorld::PFBaseUnit> const pSender = pWorldObject->GetSender();
    if( !IsValid( pSender ) )
      return false;

    if ( pWorldObject->GetSource().IsPosition() )
    {
      result = pWorldObject->GetSource().GetPosition();
      return true;
    }

    CPtr<NWorld::PFBaseUnit> const pSource = pWorldObject->GetSource().GetUnit();
    if( !IsValid( pSource ) )
      return false;

    PFClientLogicObject* pClient = pSource->ClientObject();
    if( NULL == pClient)
    {
      // Here we do not return false, because in current reconnect implementation
      // it is possible, that no client object created for pSource unit if it is dead.
      result = pSource->GetPosition();
      return true;
    }

    NScene::SceneObject *pSO = pClient->GetSceneObject();
    if ( NULL == pSO )
      return false;

    result = pSO->GetPosition().pos;
    if ( NScene::Locator const* pL = pSO->FindLocator( pWorldObject->GetDB().fromLocator.c_str() ) )
    {
      matrix = Matrix43(QNULL, result);
      pSO->CalculateLocatorWorldMatrix(*pL, matrix, pClient->IsVisible() );
      result.Set(matrix._14, matrix._24, matrix._34);
      const NWorld::Target& target = WorldObject()->GetTarget();
      if ( target.IsPosition() )
      {
        if ( fabs(pSO->GetPosition().pos - target.GetPosition()) < fabs(pSO->GetPosition().pos - result) )
        {
          result = pSO->GetPosition().pos;
        }
      }
    }

    NI_ASSERT( result.IsFinite(), NStr::StrFmt("Invalid dispatch start pos. Retrieved from %s !", pSO->FormatDescription()) );
    NI_ASSERT( matrix.IsFinite(), NStr::StrFmt("Invalid dispatch start matrix. Retrieved from %s !", pSO->FormatDescription()) );

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::Start()
  {
    bStarted = true;
    isUnitBeforeMount = false;

    const NWorld::PFDispatchUniformLinearMove *pWorldObject = WorldObject();

    flyMode = pWorldObject->GetDB().flyMode;

    NDb::EffectBase const *dispatchEffect = GetDispatchEffectDB(pWorldObject);

    // removed asserts and verifies because NUM_TASK
    GetStartPos(currentPos, startMatrix);

    RetrieveTargetCoords();
    InitCurve();

    if (fabs((dest - currentPos).AsVec2D()) < 0.00001f)
    {
      // too close
      return;
    }

    UpdateDesiredAngles();
    curYaw = desiredYaw;
    curPitch = desiredPitch;

    // determine start angles
    if (bAlignToAxis)
    {
      CVec3 at(0.f, -1.f, 0.f);
      at = Rotate( at, startMatrix );
      CVec2 const at2d = at.AsVec2D();

      curYaw = GetYaw(at2d);
      curPitch = asin(Clamp(at.z, -1.f, 1.f));
    }

    if ( !dispatchEffect)
      return;

    Placement placement;
    placement.pos = currentPos;
    placement.rot.FromEulerAngles(curYaw, curPitch, 0.f);

    if(dispatchEffect->GetObjectTypeID()== NDb::EffectList::typeId)
    {
      const NDb::EffectList * effectList = static_cast<const NDb::EffectList *>(dispatchEffect);
      EffectListEntries::const_iterator iter = effectList->effects.begin();

      for(;iter !=  effectList->effects.end();++iter)
      {
        if(!IsEffectEnabled(*iter, pWorldObject))
          continue;

        CObj<PF_Core::BasicEffectStandalone> pEffect = RetrieveStandaloneEffect( *iter, pWorldObject->GetSender().GetPtr() );

        if (!pEffect)
          return;

        pEffect->SetPosition(placement);
        pEffect->AddToScene(pScene);
        InitVisibility( GetSceneObject(pEffect) );

        if (pEffect->GetSceneObject() &&
          IsValid(WorldObject()->GetSender()->ClientObject()))
        {
          PF_Core::RecolorSceneObject(*pEffect->GetSceneObject(), WorldObject()->GetSender()->ClientObject()->GetRecolor());
        }

        pEffects.push_back(pEffect);
      }
    }
    else
    {
      if(IsEffectEnabled(dispatchEffect, pWorldObject))
      {

        CObj<PF_Core::BasicEffectStandalone> pEffect = RetrieveStandaloneEffect( dispatchEffect, pWorldObject->GetSender().GetPtr() );
        if (!pEffect)
          return;

        pEffect->SetPosition(placement);
        pEffect->AddToScene(pScene);
        InitVisibility( GetSceneObject(pEffect) );

        if (pEffect->GetSceneObject() &&
          IsValid(WorldObject()->GetSender()->ClientObject()))
        {
          PF_Core::RecolorSceneObject(*pEffect->GetSceneObject(), WorldObject()->GetSender()->ClientObject()->GetRecolor());
        }

        pEffects.push_back(pEffect);

      }
    }

    EffectsBucket::const_iterator iter = pEffects.begin();
    while(iter !=  pEffects.end())
    {
      const PFDispatchEffectHolder *effect = iter++;
      UpdateVisibility( effect->GetSceneObject(), this );
    }

    // Subscribe for updates
    Subscribe();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float PFDispatchUniformLinearMove::GetTerrainHeight( NScene::IScene* scene, const CVec2& pos )
  {
    float terrainHeight = 0.0f;
    bool heightTaken = scene->GetHeightsController().GetHeight( pos.x, pos.y, 1, &terrainHeight, 0 );
    NI_ASSERT( heightTaken, "Could not get height!" );
    return terrainHeight;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::UpdateAfterScene(float timeDelta)
  {
    startDelay -= timeDelta;
    if( startDelay < EPS_VALUE )
    {
      Start();
      UnsubscribeAfterScene();
    }
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::Update( float timeDelta )
  {
    if ( pEffects.size() == 0 )
    {
      return;
    }

    if ( bArrived )
    {
      // if both world & client object have arrived AND we're still updating
      // then we should keep our position in sync with the target
      if ( WorldObject() && WorldObject()->HasArrived() )
      {
        EffectsBucket::iterator iter = pEffects.begin();
        while(iter != pEffects.end())
        {
          if(iter->GetEffect())
          {
            Placement pl = iter->GetSceneObject()->GetPosition();
            pl.pos = MakeTargetingPos();
            iter->SetPosition( pl );
          }
          iter++;
        }
      }
      return;
    }

    if ( WorldObject()->IsSuspended() )
    {
      return;
    }

    RetrieveTargetCoords();

    // линейный диспатч теперь умеет плавно летать по горкам
    CVec3 newTarget;
    float dist4SpeedCorrection = 0.0f;
    if( flyMode == NDb::DISPATCHFLYMODE_LINEAR )
    {
      CalcEffectsMaxAABBZ();

      if (PredictTerrain( newTarget, maxAABBZ ))
      {
        dist4SpeedCorrection = fabs( dest.AsVec2D() - currentPos.AsVec2D() );
        dest = newTarget;
        UpdateTarget();
      }
    }

    const CVec2 delta2d = ( dest - currentPos ).AsVec2D();
    const float dist2d = fabs( delta2d );

    float maxDistance = WorldObject()->GetDB().maxDistance;
    if ( maxDistance < 0.0f )
    {
      maxDistance = 1e5f;
    }

    float speed = WorldObject()->GetSpeed();

    // Need to get client dispatch movement more synchronized with world one.
    // So we calculating client distance to world distance ratio and multiplying speed by it.
    // Ratio is calculated every world step.
    CVec2 worldPos = WorldObject()->GetCurPos();
    if ( curWorldPos != worldPos )
    {
      curWorldPos = worldPos;
      CVec2 worldDir = worldPos - WorldObject()->GetTarget().AcquirePosition().AsVec2D(); // maybe more precise calculation required
      if ( worldDir != VNULL2 ) // supposed that client dispatch is already very close to its target in this case
      {
        float worldDist = fabs( worldDir );
        speedModifier = ( dist4SpeedCorrection == 0.0f ? dist2d : dist4SpeedCorrection ) / worldDist;
      }
    }
    speed *= speedModifier;

    float desiredMove = timeDelta * speed;

    const bool bCloseToTarget = ( desiredMove >= dist2d );
    const bool bHasReachedMaxDist = ( ( travelledDistance + desiredMove ) >= maxDistance );

    desiredMove = Min( desiredMove, Min( dist2d, maxDistance - travelledDistance ) );

    travelledDistance += desiredMove;

    if ( !bCloseToTarget || bHasReachedMaxDist )
    {
      // target is not reached yet
      if ( desiredMove > 0.0f )
      {
        CVec2 moveDir = delta2d;
        Normalize( &moveDir );
        currentPos += CVec3( moveDir * desiredMove, 0.0f );
      }
    }
    else
    {
      currentPos = dest;
    }

    StepCurve( desiredMove );
    currentPos.z = curHeight;

    // check if we're too close to the ground
    float terrainHeight = GetTerrainHeight( pScene, currentPos.AsVec2D() );
    if ( currentPos.z < terrainHeight )
    {
      CalcEffectsMaxAABBZ();

      currentPos.z = terrainHeight + maxAABBZ.z;

      if ( flyMode == NDb::DISPATCHFLYMODE_LINEAR )
      {
        CalcEffectsMaxPositionZ();
        curveTg = ( currentPos.z - maxPosZ.z ) / desiredMove;
      }
    }

    Placement placement;
    placement.pos = currentPos;

    UpdateDesiredAngles();

    if ( WorldObject()->GetSpeed() < 0.0001f )
    {
      curYaw = Approach_(curYaw, curYaw, timeDelta * s_rotYawSpeed);
      curPitch = Approach_(curPitch, curPitch, timeDelta * s_rotPitchSpeed);
    }
    else
    {
      curYaw = Approach_(curYaw, desiredYaw, timeDelta * s_rotYawSpeed);
      curPitch = Approach_(curPitch, desiredPitch, timeDelta * s_rotPitchSpeed);
    }
    placement.rot.FromEulerAngles(curYaw, 0.f, -curPitch); // our pitch (rotation about X axis) is called "roll" in the outer world

    //update effects position
    
    EffectsBucket::iterator iter = pEffects.begin();
    while(iter != pEffects.end())
    {
      if(iter->HasValidEffectObj()){
        iter->SetPosition(placement);
      }
      iter++;
    }

    //check is arrived

    if (bHasReachedMaxDist || bCloseToTarget)
    {
      // flight is over
      OnArrive();
    }
  }

  bool eh_compare_aabb_z(PFDispatchEffectHolder& l_effect, PFDispatchEffectHolder& r_effect)
  {
    if (!l_effect.HasValidEffectObj() || !r_effect.HasValidEffectObj()) return false;

    CVec3 l_halfSize = CVec3(0,0,0);
    CVec3 r_halfSize = CVec3(0,0,0);

    NScene::SceneObject * l_scene = l_effect.GetSceneObject();

    if(l_scene->GetWorldAABB().IsValid())
      l_halfSize = l_scene->GetWorldAABB().halfSize;

    NScene::SceneObject * r_scene = r_effect.GetSceneObject();

    if( r_scene->GetWorldAABB().IsValid() )
      r_halfSize = r_scene->GetWorldAABB().halfSize;

    if(l_halfSize.z < r_halfSize.z)
      return true;

    return false;

  };

  bool eh_compare_pos_z(PFDispatchEffectHolder& l_effect, PFDispatchEffectHolder& r_effect)
  {
    if (!r_effect.HasValidEffectObj() || !l_effect.HasValidEffectObj()) return false;

    CVec3 l_pos = CVec3(0,0,0);
    CVec3 r_pos = CVec3(0,0,0);

    NScene::SceneObject * l_scene = l_effect.GetSceneObject();

    if( l_scene )
      l_pos = l_scene->GetPosition().pos;

    NScene::SceneObject * r_scene = r_effect.GetSceneObject();

    if( r_scene )
      r_pos = r_scene->GetPosition().pos;

    if(l_pos.z < r_pos.z)
      return true;

    return false;
  };

  void PFDispatchUniformLinearMove::CalcEffectsMaxAABBZ()
  {
    maxAABBZ = CVec3(0,0,0);

    if(pEffects.size() > 1)
    {
      EffectsBucket::iterator iter = nstl::max_element(pEffects.begin(), pEffects.end(), eh_compare_aabb_z);
      if(iter != pEffects.end())
        maxAABBZ = iter->GetSceneObject()->GetWorldAABB().halfSize;
    }
    else if (pEffects.size() == 1)
      if(pEffects[0].GetSceneObject())
        maxAABBZ = pEffects[0].GetSceneObject()->GetWorldAABB().halfSize;
  }

  void PFDispatchUniformLinearMove::CalcEffectsMaxPositionZ()
  {
    maxPosZ = CVec3(0,0,0);

    if(pEffects.size() > 1)
    {
      EffectsBucket::iterator iter = nstl::max_element(pEffects.begin(), pEffects.end(), eh_compare_pos_z);
      maxPosZ = iter->GetSceneObject()->GetPosition().pos;
    }
    else if(pEffects.size() == 1)
      if(pEffects[0].GetSceneObject())
        maxPosZ = pEffects[0].GetSceneObject()->GetPosition().pos;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFDispatchUniformLinearMove::PredictTerrain( CVec3& target, CVec3& effectsMaxAABBZ )
  {
    NI_PROFILE_FUNCTION

    const float predictStep = 0.5f;

    CVec3 direction = dest - currentPos;

    float distance = Min( fabs( direction ), s_predictDistance );
    Normalize( &direction );

    for( float d = 0.f; d < distance; d += predictStep )
    {
      target = currentPos +  d * direction;
      float terrainHeight = GetTerrainHeight(pScene, target.AsVec2D());
      if ( target.z < terrainHeight )
      {
        target.z = terrainHeight + maxAABBZ.z;
        return true;
      }
    }

    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::ForceFinish()
  {
    // start dispatch if still not started
    if (!bStarted)
    {
      Start();
    }

    if ( WorldObject()->GetDB().speed < 0.0001f )
    {
      OnArrive();
      return;
    }

    // update with enough time to reach target
    Update( targetClientFinalDist / WorldObject()->GetDB().speed );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::OnArrive()
  {
    bArrived = true;

    EffectsBucket::iterator iter = pEffects.begin();

    while(iter != pEffects.end())
    {
      NGameX::PFDispatchEffectHolder* effect = iter++;

      if ( WorldObject()->GetDB().killEffect && effect->GetEffect() )
      {
        effect->GetEffect()->Die();
        effect->SetEffect(NULL);
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::UpdateDesiredAngles()
  {
    const CVec3 delta3d = dest - currentPos;
    const CVec2 delta2d = delta3d.AsVec2D();
    const float dist2d  = fabs( delta2d );

    if ( dist2d > 1e-5f )
    {
      desiredYaw   = GetYaw( delta2d );
      desiredPitch = atan( curveTg ); // asin(delta3d.z / fabs(delta3d));
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::OnWorldObjectDie()
  {
    OnArrive();
    pEffects.clear();

    UnsubscribeAfterScene();
    PFClientObjectBase::OnWorldObjectDie();

  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::RetrieveTargetCoords()
  {
    NI_ASSERT( IsValid( WorldObject() ), "World dispatch should be valid" );
    
    dest = MakeTargetingPos();
    
    bool isUnit = WorldObject()->GetTarget().IsUnit();
    bool isMountedUnit = WorldObject()->GetTarget().IsUnitMounted();

    if(isUnit && !isMountedUnit)
    {
      prevDest = dest;
      isUnitBeforeMount = true;
    }
    
    if(!isUnit && isUnitBeforeMount)
    {
      dest = prevDest;
    }

    UpdateTarget();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::UpdateTarget()
  {
    targetClientFinalDist = fabs( dest.AsVec2D() - currentPos.AsVec2D() );
    targetHeight = dest.z;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::InitCurve()
  {
    NI_ASSERT( currentPos.IsFinite(), "Invalid start pos" );
    curHeight = currentPos.z;

    switch ( flyMode )
    {
    case NDb::DISPATCHFLYMODE_PARABOLIC:
      {
        float t = 0.f;
        if (WorldObject()->GetSender()->GetRange() > 0.f)
        {
          t = min(targetClientFinalDist / WorldObject()->GetSender()->GetRange(), 1.f);
        }

        // calculate parabola height
        //      float const rise = WorldObject()->GetDB().minRise + t * (WorldObject()->GetDB().maxRise - WorldObject()->GetDB().minRise); // linear
        float const rise = WorldObject()->GetDB().minRise + t * t * (WorldObject()->GetDB().maxRise - WorldObject()->GetDB().minRise); // quadratic

        float const maxH = max(curHeight, targetHeight) + rise - curHeight;
        if (maxH < 1e-5f || targetClientFinalDist < 1e-5f )
        {
          curveTg = 0.f;
        }
        else
        {
          float d = (targetHeight - curHeight) / maxH;
          NI_ASSERT(d < 1.f + 1e-5f, "Can't solve for parabola parameters");
          d = min(d, 1.f);
          curveTg = 2.f * maxH * ( 1.f + sqrtf(1.f - d) ) / targetClientFinalDist;
        }
        break;
      }
    case NDb::DISPATCHFLYMODE_LINEAR:
      {
        if ( targetClientFinalDist > 1e-5f )
          curveTg = (targetHeight - curHeight) / targetClientFinalDist;
        else
          curveTg = 0.0f;
        break;
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchUniformLinearMove::StepCurve( float deltaX )
  {
    if ( targetClientFinalDist < 1e-5f )
    {
      curHeight = targetHeight;
      return;
    }

    switch ( flyMode )
    {
    case NDb::DISPATCHFLYMODE_PARABOLIC:
      {
        float const a = (targetHeight - curHeight - curveTg * targetClientFinalDist) / (targetClientFinalDist * targetClientFinalDist);
        curHeight += a * deltaX * deltaX + curveTg * deltaX;
        float const newCurveTg = curveTg + 2 * a * deltaX;

        if (curveTg < 0.f && newCurveTg > curveTg)
        {
          // We are bending parabola back up which is, well, weird. Better have linear trajectory.
          flyMode = NDb::DISPATCHFLYMODE_LINEAR;
        }

        curveTg = newCurveTg;
        break;
      }
    case NDb::DISPATCHFLYMODE_LINEAR:
      {
        curveTg = ( targetHeight - currentPos.z ) / targetClientFinalDist;
        curHeight = currentPos.z + curveTg * deltaX;
        break;
      }
    }
  }

  //-------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------

  PFDispatchWithLink::PFDispatchWithLink(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis, float startDelay)
    : PFDispatchUniformLinearMove(pWO, pScene, bAlignToAxis, startDelay)
  {
    if ( !WorldObject()->GetTarget().IsVisibleForFaction( WorldObject()->GetWorld(), AdventureScreen::Instance()->GetPlayerFaction() )
      && !WorldObject()->GetSender()->IsVisibleForFaction( AdventureScreen::Instance()->GetPlayerFaction() ) )
    {
      return;
    }

    for (int i = 0; i < WorldObject()->GetDB().links.size(); ++i)
    {
      NDb::LightningLink const &l = WorldObject()->GetDB().links[i];

      int teamID = WorldObject()->GetSender()->GetOriginalTeamId();
      if (teamID == -1)
      {
        teamID = NDb::TEAMID_A;
      }
      if ( l.effect[teamID].IsEmpty() )
      {
        teamID = teamID == NDb::TEAMID_B ? NDb::TEAMID_A : NDb::TEAMID_B;
      }

      CObj<PF_Core::LightningEffect> lightning = NGameX::CreateLightningEffect( l.effect[teamID], WorldObject()->GetSender()->GetSkinId() );
      lightning->Apply(WorldObject()->GetSender()->ClientObject(), this);

      lightningLinks.push_back(lightning);
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFDispatchWithLink::~PFDispatchWithLink()
  {
    for (int i = 0; i < lightningLinks.size(); ++i)
    {
      if ( IsValid( lightningLinks[i] ) )
      {
        NGameX::KillEffect(lightningLinks[i]);
      }
    }
  }

  //-------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFDispatchByTime::PFDispatchByTime(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene)
    : NWorld::PFClientObjectBase(pWO)
    , pScene(pScene)
  {}

  // Dispatch effect death callback
  void PFDispatchByTime::operator()(const BasicEffect &effect)
  {
    //BasicEffect &ef = const_cast<BasicEffect&>(effect);
    //ef.SetDeathCallback(0);
  }

  void PFDispatchByTime::Start()
  {
    const NWorld::PFDispatchByTime *pWorldObject = WorldObject();
    NDb::EffectBase const *dispatchEffect = GetDispatchEffectDB(pWorldObject);

    if (!dispatchEffect)
      return;

    if(NGameX::IsEffectEnabled(dispatchEffect, pWorldObject))
    {
      StartInternal(dispatchEffect, pWorldObject);
    }

    // Subscribe for updates
    Subscribe();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchByTime::StartInternal(NDb::EffectBase const *dispatchEffect, const NWorld::PFDispatchByTime *pWorldObject)
  {
    if (!dispatchEffect)
      return;

    StandaloneEffectsVector effectList;
    RetrieveStandaloneEffectCollection(&effectList, dispatchEffect, WorldObject()->GetSender().GetPtr(), this );
    
    if(effectList.size() == 0) return;

    StandaloneEffectsVector::iterator iter = effectList.begin();

    while(iter != effectList.end())
    {

      CObj<PF_Core::BasicEffectStandalone> pEffect = *iter++;

      if (!pEffect || (pEffect && pEffect->IsDead()) )
        return;

      if(!CheckEffectEnabled(*(pEffect.GetPtr())))
      {
        DevTrace("Effect %s was disabled by condition", pEffect->GetDBDesc()->GetDBID().GetFileName());
        continue;
      }

      InitVisibility( GetSceneObject(pEffect) );
      pEffect->AddToScene(pScene);

      Placement placement;
      placement.pos = pWorldObject->GetDestination();

      bool ok = pScene->GetHeightsController().GetHeight( placement.pos.x, placement.pos.y, 1, &placement.pos.z, 0 );
      NI_ASSERT( ok, NStr::StrFmt( "Failed to retrieve height for %s!", GetFormattedDbId( WorldObject()->GetDB().GetDBID() ).c_str() ) );

      // Rotate dispatch to direction
      CVec3 dir = CVec3( pWorldObject->GetCurrentPosition().AsVec2D() - pWorldObject->GetSource().AcquirePosition().AsVec2D(), 0.0f );
      if ( dir.Length() > EPS_VALUE )
      {
        placement.rot.FromDirection( dir, true );
      }

      pEffect->SetPosition( placement );
      UpdateVisibility( GetSceneObject(pEffect), this );

      pEffects.push_back(pEffect);

    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchByTime::Update(float timeDelta)
  {
    EffectsBucket::const_iterator iter = pEffects.begin();

    while(iter != pEffects.end())
    {
      const PFDispatchEffectHolder* effect = iter++;
      if ( effect->GetSceneObject() )
        UpdateVisibility( effect->GetSceneObject(), this );
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDispatchByTime::OnWorldObjectDie()
  {
    pEffects.clear();
    PFClientObjectBase::OnWorldObjectDie();
  }

  bool PFDispatchByTime::CheckEffectEnabled( const PF_Core::BasicEffect &effect )
  {
    bool bEnable = true;

    if(effect.GetDBDesc() && !effect.GetDBDesc()->enableCondition.IsEmpty())
    {
      const NWorld::PFDispatchByTime *pWorldObject = WorldObject();
      IUnitFormulaPars* pFirst = pWorldObject->GetSender();
      IUnitFormulaPars* pSecond = NULL;
      IMiscFormulaPars* pMisc = (IMiscFormulaPars*)pWorldObject->GetAbility()->GetData();

      if(pWorldObject->GetTarget().IsUnit())
        pSecond = pWorldObject->GetTarget().GetUnit();

      bEnable = effect.GetDBDesc()->enableCondition->condition(pFirst,pSecond, pMisc, bEnable);
   }

    return bEnable;
  }

}
