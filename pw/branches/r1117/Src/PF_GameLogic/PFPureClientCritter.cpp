#include "stdafx.h"

#include "PFPureClientCritter.h"
#include "PFAIWorld.h"
#include "PFLogicObject.h"
#include "AdventureScreen.h"
#include "../System/InlineProfiler.h"
#include "../Core/Scheduler.h"
#include "PFClientObjectHelpers.h"

namespace
{
  const float g_maxRotSpeed = 10.0f;
#ifndef _SHIPPING
  bool g_debugDrawRadiuses = false;
  const bool g_debugDrawPositions = false;

  REGISTER_DEV_VAR( "draw_critters_radiuses", g_debugDrawRadiuses, STORAGE_NONE );
#endif // _SHIPPING
}

namespace NGameX
{
  PFPureClientCritter::PFPureClientCritter( const NDb::AdvMapObject& dbAdvMapObject, NScene::IScene* _pScene )
    : PFPureClientObject( dbAdvMapObject, _pScene )
    , moveRadius( 0.0f )
    , alarmRadius( 0.0f )
    , calmDownTime( 0.0f )
    , moveSpeed( 0.0f )
    , timer( _pScene->GetStepLengthInSeconds() )
    , currentState( OnBase )
    , fearSource( -1.0f, -1.0f )
    , isHeroNear( false )
    , isVisibleUnderWarfog( false )
  {
    if ( dbAdvMapObject.gameObject->GetObjectTypeID() == NDb::Critter::typeId )
    {
      const NDb::Critter* pDBDesc = static_cast<const NDb::Critter*>( dbAdvMapObject.gameObject.GetPtr() );
      moveRadius   = pDBDesc->moveRadius;
      alarmRadius  = pDBDesc->alarmRadius;
      calmDownTime = pDBDesc->calmDownTime;
      moveSpeed    = pDBDesc->moveSpeed;
      restingTimer = calmDownTime;
      SetPosition( GetPosition().AsVec2D() );
      isVisibleUnderWarfog = pDBDesc->isVisibleUnderWarfog;
    }
    else
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "%s: critter type expected!", dbAdvMapObject.gameObject->GetDBID().GetFormatted().c_str() ) );
    }

    basePosition = GetPosition().AsVec2D();
    targetPosition = basePosition;

    InitAnimation();
  }

  void PFPureClientCritter::InitAnimation()
  {
    if( PFAnimController::Initialize( GetSceneObject(), false ) )
    {
      NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CRITTER];

      const int setId = RegisterAnimSet( pAnimSet );
      if( setId < 0 )
      {
        NI_ALWAYS_ASSERT( "Failed to register animSet!" );
      }

      ActivateAnimSet( setId );

      SetSurfaceSpeedMultiplier( moveSpeed / GetSurfaceSpeed( NDb::ANIMSTATES_MOVE ) );

      Idle();

      GetSceneObject()->SetUpdateHook( this );
    }
  }

  void PFPureClientCritter::Idle()
  {
    if ( GetCurrentStateId() != GetStateId( NDb::ANIMSTATES_IDLE ) )
    {
      SetAnimState( NDb::ANIMSTATES_IDLE, GetStatePlayMode( NDb::ANIMSTATES_IDLE ) );
    }
  }

  void PFPureClientCritter::Move()
  {
    if ( GetCurrentStateId() != GetStateId( NDb::ANIMSTATES_MOVE ) )
    {
      SetAnimState( NDb::ANIMSTATES_MOVE, GetStatePlayMode( NDb::ANIMSTATES_MOVE ) );
    }
  }

  void PFPureClientCritter::Hide()
  {
    if ( GetCurrentStateId() != GetStateId( NDb::ANIMSTATES_HIDE ) )
    {
      SetAnimState( NDb::ANIMSTATES_HIDE, GetStatePlayMode( NDb::ANIMSTATES_HIDE ) );
    }
  }

#ifndef _SHIPPING
  void PFPureClientCritter::DebugDraw()
  {
    const CVec3 basePosition3D( basePosition, 0.0f );
    if ( g_debugDrawRadiuses )
    {
      Render::DebugRenderer::DrawCircle3D( basePosition3D, moveRadius,  32, Render::Color( 192, 192,   0 ), false );
      Render::DebugRenderer::DrawCircle3D( GetPosition(),  alarmRadius, 32, Render::Color(   0, 192, 192 ), false );
    }

    if ( g_debugDrawPositions )
    {
      Render::DebugRenderer::DrawPoint3D( basePosition3D, 0.2f, Render::Color( 192, 192, 0 ), false );

      if ( isHeroNear )
      {
        const CVec3 fearSource3D( fearSource, 0.0f );
        const CVec3 targetPosition3D( targetPosition, 0.0f );

        Render::DebugRenderer::DrawPoint3D( fearSource3D,     0.2f, Render::Color( 128,   0, 0 ), false );
        Render::DebugRenderer::DrawPoint3D( targetPosition3D, 0.2f, Render::Color(   0, 192, 0 ), false );

        Render::DebugRenderer::DrawLine3D( basePosition3D,   targetPosition3D, Render::Color( 192, 192, 0 ), Render::Color(   0, 192, 0 ), false );
        Render::DebugRenderer::DrawLine3D( basePosition3D,   fearSource3D,     Render::Color( 192, 192, 0 ), Render::Color( 128,   0, 0 ), false );
        Render::DebugRenderer::DrawLine3D( targetPosition3D, fearSource3D,     Render::Color(   0, 192, 0 ), Render::Color( 128,   0, 0 ), false );
      }
    }
  }
#endif // _SHIPPING

  bool PFPureClientCritter::StepTo( const CVec2& targetPos, float timeDiff )
  {
    if ( !CanMove() )
    {
      return false;
    }

    const CVec2 curPos = GetPosition().AsVec2D();
    if ( curPos == targetPos )
    {
      return true;
    }

    const CVec2 deltaPos = targetPos - curPos;
    const float dist = fabs( deltaPos );
    const float toMove = moveSpeed * timeDiff;
    bool isTargetReached = false;
    if ( dist > toMove )
    {
      SetPosition( curPos + deltaPos * toMove / dist );
    }
    else
    {
      SetPosition( targetPos );
      isTargetReached = true;
    }

    LookTo( deltaPos, timeDiff );
    return isTargetReached;
  }

  bool PFPureClientCritter::CanMoveToBase()
  {
    NWorld::PFAIWorld* pAIWorld = AdventureScreen::Instance()->GetWorld()->GetAIWorld();
    //Listen for heroes
    nstl::vector<CVec2> heroesPos;

    const float radiusPreventMoving = 1.f; // радиус в добавок к alarmRadius для предотвращения ошибочного движения обратно на базу

    const CVec2 curPos = GetPosition().AsVec2D();

    const CVec2 deltaPos = basePosition - curPos;
    const float dist = fabs( deltaPos );

    if ( dist > radiusPreventMoving )
    {
      NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusA( curPos + deltaPos * radiusPreventMoving / dist, alarmRadius, &heroesPos, NDb::FACTION_FREEZE );
      NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusB( curPos + deltaPos * radiusPreventMoving / dist, alarmRadius, &heroesPos, NDb::FACTION_BURN );

      pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusA, NDb::FACTION_FREEZE );
      pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusB, NDb::FACTION_BURN );

    }
    else
    {
      NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusA( basePosition, alarmRadius, &heroesPos, NDb::FACTION_FREEZE );
      NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusB( basePosition, alarmRadius, &heroesPos, NDb::FACTION_BURN );

      pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusA, NDb::FACTION_FREEZE );
      pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusB, NDb::FACTION_BURN );
    }

    return heroesPos.empty();
  }

  void PFPureClientCritter::LookTo( const CVec2& dir, float timeDiff )
  {
    if ( fabs2( dir ) <= fabs2( 0.02f ) )
    {
      return;
    }
    const float newAngle = atan2( dir.x, -dir.y );

    // get current rotation
    float curAngle = 0;
    float tmpPitch = 0;
    float tmpRoll  = 0;
    GetRotation().DecompEulerAngles( &curAngle, &tmpPitch, &tmpRoll );

    // get angle delta
    float rotDelta  = NormalizeAngle( newAngle  - curAngle );

    // compute rotation speed
    float rotSpeed = Min( g_maxRotSpeed, fabs( rotDelta ) / timeDiff );
    rotSpeed *= rotDelta  < 0.0f ? -1 : 1;

    if ( fabs( rotDelta  ) > EPS_VALUE )
    {
      float toRotate  = rotSpeed * timeDiff;

      if ( fabs( rotDelta ) > fabs( toRotate ) )
      {
        curAngle += toRotate;
      }
      else
      {
        curAngle = newAngle;	// stop rotation
      }
      curAngle = NormalizeAngle( curAngle );
      CQuat newRot;
      newRot.FromEulerAngles( curAngle, 0, 0 );
      SetRotation( newRot );
    }
  }


  void PFPureClientCritter::Step()
  {
    NWorld::PFAIWorld* pAIWorld = AdventureScreen::Instance()->GetWorld()->GetAIWorld();

    CVec2 prevTargetPosition = targetPosition;

    isHeroNear = false;

    if ( !CanMove() )
    {
      struct FindHeroInRadius
      {
        FindHeroInRadius( const CVec2& _center, float _radius, bool* _result, int _faction )
          : center( _center )
          , radius( _radius )
          , result( _result )
          , faction( _faction )
        { }

        void operator()( NWorld::PFLogicObject& logicObject )
        {
          if ( !(*result) && logicObject.IsVisibleForEnemy( faction ) && logicObject.IsInRange( center, radius ) )
          {
            *result = true;
          }
        }

        CVec2 center;
        float radius;
        bool* result;
        int faction;
      };
      FindHeroInRadius findHeroInRadiusA( GetPosition().AsVec2D(), alarmRadius, &isHeroNear, NDb::FACTION_FREEZE );
      FindHeroInRadius findHeroInRadiusB( GetPosition().AsVec2D(), alarmRadius, &isHeroNear, NDb::FACTION_BURN );

      pAIWorld->ForAllHeroes( findHeroInRadiusA, NDb::FACTION_FREEZE );
      pAIWorld->ForAllHeroes( findHeroInRadiusB, NDb::FACTION_BURN );

      return;
    }

    //Listen for heroes
    nstl::vector<CVec2> heroesPos;

    NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusA( GetPosition().AsVec2D(), alarmRadius, &heroesPos, NDb::FACTION_FREEZE );
    NoticeTwoNearestHeroesInRadius noticeTwoNearestHeroesInRadiusB( GetPosition().AsVec2D(), alarmRadius, &heroesPos, NDb::FACTION_BURN );

    pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusA, NDb::FACTION_FREEZE );
    pAIWorld->ForAllHeroes( noticeTwoNearestHeroesInRadiusB, NDb::FACTION_BURN );

    isHeroNear = !heroesPos.empty();

    if ( !isHeroNear )
    {
      return;
    }

    CVec2 prevFearSource = fearSource;

    switch ( heroesPos.size() )
    {
    case 0:
      NI_ALWAYS_ASSERT( "Vector of heroes positions shouldn't be empty!" );
      break;
    case 1:
      fearSource = heroesPos[0];
      break;
    case 2:
      fearSource = ( heroesPos[0] + heroesPos[1] ) * 0.5;
      break;
    default:
      NI_ALWAYS_ASSERT( "Vector of heroes positions shouldn't be onger then 2!" );
      break;
    }

    if ( prevFearSource == fearSource )
    {
      return;
    }

    const CVec2 curPos = GetPosition().AsVec2D();
    const CCircle moveArea( basePosition, moveRadius );
    CLine2 lineToIntercept;
    int rootsCount;
    CVec2 p1, p2;

    if ( fearSource != curPos )
    {
      lineToIntercept = CLine2( fearSource, curPos );

      rootsCount = GetLineCircleIntersection( lineToIntercept, moveArea, p1, p2 );

      NI_VERIFY( rootsCount > 0,
        NStr::StrFmt( "Can't intersect line ( [%.2f, %.2f], [%.2f, %.2f] ) with circle ( center: [%.2f, %.2f], radius = %.2f )!",
          p1.x, p1.y, p2.x, p2.y, moveArea.center.x, moveArea.center.y, moveArea.r ), return );

      if ( rootsCount == 1 )
      {
        targetPosition = curPos;
        return;
      }

      float dot1 = ( fearSource - curPos ).Dot( p1 - curPos );
      float dot2 = ( fearSource - curPos ).Dot( p2 - curPos );

      if ( fabs2( p1 - curPos ) <= 0.01 )
      {
        if ( dot2 < 0 )
        {
          targetPosition = FixPoint( p2 );
        }
        return;
      }

      if ( fabs2( p2 - curPos ) <= 0.01 )
      {
        if ( dot1 < 0 )
        {
          targetPosition = FixPoint( p1 );
        }
        return;
      }

      if ( dot1 > dot2 )
      {
        dot1 = dot1 + dot2;
        dot2 = dot1 - dot2;
        dot1 = dot1 - dot2;

        p1 = p1 + p2;
        p2 = p1 - p2;
        p1 = p1 - p2;
      }

      NI_VERIFY( ( ( dot1 < 0 ) && ( dot2 > 0 ) ),
        NStr::StrFmt( "Points [%.2f, %.2f] and [%.2f, %.2f] should be on different sides of [%.2f, %.2f]!",
          p1.x, p1.y, p2.x, p2.y, curPos.x, curPos.y ), return );

      targetPosition = FixPoint( p1 );
    }
    else
    {
      if ( heroesPos.size() == 1 )
      {
        if ( curPos != basePosition )
        {
          lineToIntercept = CLine2( basePosition, curPos );

          rootsCount = GetLineCircleIntersection( lineToIntercept, moveArea, p1, p2 );

          NI_VERIFY( rootsCount == 2,
            NStr::StrFmt( "Wrong interception: line ( [%.2f, %.2f], [%.2f, %.2f] ) with circle ( center: [%.2f, %.2f], radius = %.2f )! Roots count is %d, 2 expected.",
              p1.x, p1.y, p2.x, p2.y, moveArea.center.x, moveArea.center.y, moveArea.r, rootsCount ), return );

          targetPosition = FixPoint( p1 );

          const float sqrDist1 = fabs2( curPos - p1 );
          const float sqrDist2 = fabs2( curPos - p2 );

          NI_VERIFY( ( sqrDist1 != sqrDist2 ), NStr::StrFmt( "Point [%.2f, %.2f] should not be in circle center!",  curPos.x, curPos.y ), return );

          if ( sqrDist2 > sqrDist1 )
          {
            targetPosition = FixPoint( p2 );
          }
        }
        else
        {
          const float angle = NRandom::Random( 0.0f, FP_2PI );
          targetPosition = basePosition + moveRadius * CVec2( sin( angle ), cos( angle ) );
        }
      }
      else
      {
        //Intercept circle with perpendicular to [ heroesPos[0], heroesPos[1] ]
        lineToIntercept = *( CLine2( heroesPos[0], heroesPos[1] ).GetPerpendicularByPoint( curPos ) );

        rootsCount = GetLineCircleIntersection( lineToIntercept, moveArea, p1, p2 );

        NI_VERIFY( rootsCount == 2,
          NStr::StrFmt( "Wrong interception: line ( [%.2f, %.2f], [%.2f, %.2f] ) with circle ( center: [%.2f, %.2f], radius = %.2f )! Roots count is %d, 2 expected.",
          p1.x, p1.y, p2.x, p2.y, moveArea.center.x, moveArea.center.y, moveArea.r, rootsCount ), return );

        targetPosition = FixPoint( p1 );

        const float sqrDist1 = fabs2( curPos - p1 );
        const float sqrDist2 = fabs2( curPos - p2 );

        if ( sqrDist2 > sqrDist1 )
        {
          targetPosition = FixPoint( p2 );
        }
      }
    }
  }

  const CVec2 PFPureClientCritter::FixPoint( const CVec2& point ) const
  {
    CVec2 movingVector = point - basePosition;

    if( fabs( movingVector ) > moveRadius )
    {
        Normalize( &movingVector );

        return( basePosition + movingVector * (moveRadius - 0.5f) );
    }

    return point;
  }


  void PFPureClientCritter::Update( float timeDiff )
  {
    NI_PROFILE_FUNCTION

    PFPureClientObject::Update( timeDiff );

    if ( isVisibleUnderWarfog )
    {
      if ( !IsVisible() )
      {
        FreezeAG();
        NScene::SceneObject* so = GetSceneObject();
        if ( so && !so->IsFrozen() )
          so->SetFreeze( true );
        SetVisibility( true );
      }
      else
      {
        NScene::SceneObject* so = GetSceneObject();
        if ( so && so->IsFrozen() )
          so->SetFreeze( false );
        UnFreezeAG();
      }
    }

#ifndef _SHIPPING
    if ( g_debugDrawRadiuses || g_debugDrawPositions )
    {
      DebugDraw();
    }
#endif // _SHIPPING

    if ( !CanBeScared() )
    {
      return;
    }

    timer -= timeDiff;

    if ( timer <= 0.0f )
    {
      Step();
      timer += GetScene()->GetStepLengthInSeconds();
    }

    switch ( currentState )
    {
    case OnBase:
      if ( isHeroNear )
      {
        if ( CanMove() )
        {
          currentState = RunAway;
          Move();
        }
        else
        {
          currentState = Scared;
          Hide();
        }
      }
      break;

    case RunAway:
      if ( isHeroNear )
      {
        if ( StepTo( targetPosition, timeDiff ) )
        {
          currentState = Scared;
          Hide();
          restingTimer = calmDownTime;
        }
      }
      else
      {
        currentState = Resting;
        Idle();
        restingTimer = calmDownTime;
      }
      break;

    case Resting:
      if ( isHeroNear )
      {
        currentState = RunAway;
        Move();
      }
      else
      {
        restingTimer -= timeDiff;
        if ( restingTimer < 0.0f )
        {
          if( CanMoveToBase() )
          {
            currentState = ComingToBase;
            Move();
          }
          else
            restingTimer = calmDownTime;
        }
      }
      break;

    case Scared:
      if ( isHeroNear && ( restingTimer < calmDownTime ) )
      {
        restingTimer = calmDownTime;
      }
      else
      {
        restingTimer -= timeDiff;
        if ( restingTimer < 0.0f )
        {
          currentState = CanMove() ? (Move(), ComingToBase) : (Idle(), OnBase);
        }
      }
      break;

    case ComingToBase:
      if ( isHeroNear )
      {
        currentState = RunAway;
        Move();
      }
      else
      {
        if ( StepTo( basePosition, timeDiff ) )
        {
          currentState = OnBase;
          Idle();
        }
      }
      break;
    }
  }

  bool PFPureClientCritter::OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/)
  {
    Freeze(false, sceneObject, IsVisible() );
    return true;
  }

  void PFPureClientCritter::OnSceneObjectBecomeInvisible(NScene::SceneObject& sceneObject)
  {
    Freeze(true, sceneObject);
  }

} // namespace NGameX