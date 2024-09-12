#include "stdafx.h"
#include "EaselPaintBlastBallView.h"

#include "DBEasel.h"

#include "../Scene/SceneObject.h"
#include "../PF_Core/BasicEffect.h"

#include "Easel.h"
#include "EaselView.h"
#include "EaselViewEffects.h"
#include "EaselWorld.h"
#include "EaselEventSounds.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselPainBlastBallView::EaselPainBlastBallView() :
  exploded(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPainBlastBallView::OnDestroyContents()
{
  CheckExploded();
  ShowEffect( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselPainBlastBallView::Init(Easel& _easel, LuxBall* ball, BallCoordsConverter* _converter)
{
	NI_VERIFY( IsValid( ball ), "", return false );

	easel = &_easel;
	logicBall = ball;

  // initializing lerp object 
  lerpBallPos = new LuxViewBallLerp(ball,_converter);

  return true;
}

void EaselPainBlastBallView::ShowEffect( bool show )
{
  if ( show )
  {
    if ( effect )
      return;

    NDb::Ptr<NDb::BasicEffectStandalone> blastBall;

    if ( logicBall->State() == BALL_STATE_FIRED )
    {
      blastBall = easel->GetData()->commonParams->balls.paintBlastBallFlying;
      NI_VERIFY( IsValid( blastBall ), "", return );
    }
    else
    {
      blastBall = easel->GetData()->commonParams->balls.paintBlastBall;
      NI_VERIFY( IsValid( blastBall ), "", return );
    }

    effect = easel->GetClient().CreateStandaloneEffect( blastBall, true );

    if ( !effect )
      return;

    effect->AddToScene( easel->GetScene() );
    effect->SetPosition( easel->GetPlacement() );
  }
  else
  {
    if ( effect )
    {
      if ( IsValid( easel ) )
        easel->GetClient().ReleaseEffect( effect );

      effect = 0;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPainBlastBallView::Update(float deltaTime, bool gameOnPause)
{
	NI_VERIFY( IsValid( easel ), "", return );
  NI_VERIFY( IsValid( logicBall ), "", return );

  // need to increment delta timer
  lerpBallPos->IncrementElapsedTime(deltaTime);

  // calculating ball position based on interpolated data ...
  Placement newPlacement;
  if(!lerpBallPos->vLerp(newPlacement))  // object is not visible at all
  {
    SetVisible(false);
  }
  else
  {
    SetVisible(true);

    if ( effect )
    {
      Placement placement = effect->GetSceneObject()->GetPosition();
      placement.pos = newPlacement.pos;
      effect->SetPosition( placement );
    }
  }

  CheckExploded();

	MinigameClientObject::Update( deltaTime, gameOnPause );
}

void EaselPainBlastBallView::CheckExploded()
{
  if ( logicBall->State() == BALL_STATE_EXPLODED && !exploded )
  {
    easel->GetView()->GetEffects()->OnPaintBlastBallExplosion( logicBall->Position() );
    easel->GetWorld()->GetSound()->PlaySound( NDb::EASELSOUNDTYPE_BOOST_PAINTBLAST_EXPLOSION );

    exploded = true;
  }
}

void EaselPainBlastBallView::SetVisible( bool _visible )
{
  ShowEffect( _visible );
}

} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselPainBlastBallView );