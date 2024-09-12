#pragma once

#include "PFPureClientObject.h"
#include "PFAnimController.h"


namespace NGameX
{
  enum ECritterState
  {
    OnBase,
    RunAway,
    Resting,
    Scared,
    ComingToBase
  };

  class PFPureClientCritter : public PFPureClientObject, public PFAnimController, public NScene::ISceneObjectUpdateHook
  {
    OBJECT_METHODS( 0x2B832C00, PFPureClientCritter )

  public:
    PFPureClientCritter( const NDb::AdvMapObject& dbAdvMapObject, NScene::IScene* _pScene );
    bool CanMove()     const { return ( ( moveRadius > 0.0f ) && ( moveSpeed > 0.0f ) ); }
    bool CanBeScared() const { return ( alarmRadius > 0.0f ); }

  protected:
    explicit PFPureClientCritter() { }
    virtual void Update( float timeDiff );
    virtual void Step();
    bool StepTo( const CVec2& targetPos, float timeDiff );
    void LookTo( const CVec2& dir, float timeDiff );
    void DebugDraw();
    void InitAnimation();

    void Idle();
    void Move();
    void Hide();

    virtual bool OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/);
    virtual void OnSceneObjectBecomeInvisible(NScene::SceneObject& sceneObject);

  private:
    ECritterState currentState;
    float moveRadius;
    float alarmRadius;
    float calmDownTime;
    float moveSpeed;

    CVec2 basePosition;

    CVec2 targetPosition;
    CVec2 fearSource;
    bool isHeroNear;

    float timer;
    float restingTimer;
    bool isVisibleUnderWarfog; 

    struct NoticeTwoNearestHeroesInRadius
    {
      NoticeTwoNearestHeroesInRadius( const CVec2& _center, float _radius, nstl::vector<CVec2>* _results, int _faction )
        : center(  _center  )
        , radius(  _radius  )
        , results( _results )
        , faction( _faction )
      { }

      void operator()( NWorld::PFLogicObject& logicObject )
      {
        if ( logicObject.IsVisibleForEnemy( faction ) && logicObject.IsInRange( center, radius ) )
        {
          CVec2 newPos = logicObject.GetPosition().AsVec2D();
          if ( results->size() < 2 )
          {
            results->push_back( newPos );
            if ( results->size() == 2 )
            {
              if ( fabs2( (*results)[0] - center ) > fabs2( (*results)[1] - center ) )
              {
                (*results)[0] = (*results)[0] + (*results)[1];
                (*results)[1] = (*results)[0] - (*results)[1];
                (*results)[0] = (*results)[0] - (*results)[1];
              }
            }
          }
          else
          {
            if ( fabs2( newPos - center ) <= fabs2( (*results)[0] - center ) )
            {
              (*results)[1] = (*results)[0];
              (*results)[0] = newPos;
            }
            else
            {
              if ( fabs2( newPos - center ) <= fabs2( (*results)[1] - center ) )
              {
                (*results)[1] = newPos;
              }
            }
          }
        }
      }

      CVec2 center;
      float radius;
      nstl::vector<CVec2>* results;
      int faction;
    };

    bool CanMoveToBase();
    const CVec2 FixPoint( const CVec2& point ) const;
  };

} // namespace NGameX