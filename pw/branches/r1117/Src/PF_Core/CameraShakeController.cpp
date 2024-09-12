#include "stdafx.h"
#include "../Scene/SceneComponent.h"
#include "CameraShakeSceneComponent.h"
#include "CameraShakeController.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Core
{

CameraShakeController::CameraShakeController(NDb::AnimatedPlacement const &displacement, CameraShakeSceneComponent *pSource, float range)
  : displacement(&displacement)
  , bActive(true)
  , pSource(pSource)
  , range(range)
  , componentLastUpdateFrame(0)
{
  if (pSource)
  {
    componentLastUpdateFrame = pSource->GetLastUpdateFrame();
  }
}


void CameraShakeController::Update( 
  NScene::SCameraPosition	*pWantedPos,
  const NScene::SCameraPosition &currentPos,
  const NScene::SCameraPosition &wantedPos,
  NScene::Time timeDiff
  )
{
  *pWantedPos = wantedPos;

  if (bActive)
  {
    if (pSource)
    {
      if(pSource->GetLastUpdateFrame() == componentLastUpdateFrame)
      {
        // component hasn't been updated since last camera shake update
        // turn off camera shake
        bActive = false;
        pSource->StopShake();
        return;
      }

      componentLastUpdateFrame = pSource->GetLastUpdateFrame();
      totalTime = pSource->GetAnimatedTime();
    }
    else
    {
      totalTime += timeDiff;
    }

    if (displacement)
    {
      float strength = 1.f;

      // calculate strength of effect based on distance from source
      if (pSource)
      {
        if (range == 0.f)
        {
          strength = 0.f;
        }
        else
        {
          strength = fabs(currentPos.vAnchor - pSource->GetWorldPlacement().pos) / range; 
          strength = 1.f - min(strength, 1.f);
        }
      }

      // apply translation
      pWantedPos->vAnchor += strength * displacement->pos.GetValue(totalTime);
      
      // apply rotation
      float yaw = 0.f, pitch = 0.f, roll = 0.f;
      displacement->rot.GetValue(totalTime).DecompEulerAngles(&yaw, &pitch, &roll);
      pWantedPos->fYaw   += strength * yaw;
      pWantedPos->fPitch += strength * pitch;
      pWantedPos->fRoll  += strength * roll;
    }
  }
}

}
