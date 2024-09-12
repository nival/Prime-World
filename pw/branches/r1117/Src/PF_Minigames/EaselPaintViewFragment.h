#pragma once

#include "MinigameClientObject.h"

#include "PaintPoint.h"
#include "PaintFragment.h"
#include "EaselPaintLayerSceneComponent.h"

namespace NDb
{
	struct DBFragment;  
  struct BasicEffectStandalone;
  enum   EColor;
}

namespace NScene
{
  class EaselPaintLayerSceneComponent;
}

namespace PF_Core
{
  class BasicEffectStandalone;
}

namespace PF_Minigames
{

class Easel;
class Minigames;

class EaselPaintViewFragment : public MinigameClientObject
{
	OBJECT_METHODS(0x9963D341, EaselPaintViewFragment);
public:

  enum 
  {
    MAX_PAINT_POINTS_PER_FRAGMENT = Render::PaintMesh::MAX_PAINT_POINTS_PER_FRAGMENT,
  };

	EaselPaintViewFragment() :
      fIsInit(false)
    , fIsHidden(false)
    , colorCapacity(0)
    , complete(false)
    , remainFillTime(0.0f)
  {
    memset(colorPointCapacity, 0, sizeof(colorPointCapacity));
    memset(colorPointAmount, 0, sizeof(colorPointAmount));
    memset(colorPointColor,0,sizeof(colorPointColor));
    memset(colorPointPos,0,sizeof(colorPointPos));
  }

  virtual void OnDestroyContents(); 

  bool Init(Easel& _easel, const CObj<NScene::EaselPaintSceneComponent>& _paint,
            CPaintFragment* fragment, const NDb::DBFragment* dbFragment);

  void ShowFragment();
  void HideFragment();

  // check logic fragment for color modifications and update self state correspondingly
  void UpdateState();

	virtual void Update(float deltaTime, bool gameOnPause);

private:
  
  void UpdatePointState(int point);

  void AddDraftFadeWaitInterval(int _exceptThisOne, float _duration);
  void AddDraftFade(float _fade, float _waitInterval);

  void UpdateFragments();
  void KillEffects();

  void AddEffect( const NDb::BasicEffectStandalone* dbEffect, CObj<PF_Core::BasicEffectStandalone>& effect, CPainterPoint* _point );
  void RemoveEffect( CObj<PF_Core::BasicEffectStandalone>& effect );

  CObj<PF_Core::BasicEffectStandalone> magnetHighlight[MAX_PAINT_POINTS_PER_FRAGMENT];
  CObj<PF_Core::BasicEffectStandalone> magnetPreselect;
  CObj<PF_Core::BasicEffectStandalone> magnet[MAX_PAINT_POINTS_PER_FRAGMENT];

  bool fIsInit;   // initialization flag
  bool fIsHidden; // hidden fragment flag

	CPtr<Easel> easel;

	CPtr<CPaintFragment> logicFragment;
  NDb::EColor fragmentColor;
  
  int colorCapacity;
  int colorPointAmount[MAX_PAINT_POINTS_PER_FRAGMENT];
  int colorPointCapacity[MAX_PAINT_POINTS_PER_FRAGMENT];
  
  NDb::EColor colorPointColor[MAX_PAINT_POINTS_PER_FRAGMENT];
  CVec3       colorPointPos[MAX_PAINT_POINTS_PER_FRAGMENT];
  
  float remainFillTime;
  
  bool complete;

  CObj<NScene::EaselPaintSceneComponent> paint;


  // scene components
  CObj<NScene::EaselPaintLayerSceneComponent> draftLayer[MAX_PAINT_POINTS_PER_FRAGMENT];
  CObj<NScene::EaselPaintLayerSceneComponent> completeLayer;
  CObj<NScene::EaselPaintLayerSceneComponent> completeEffectLayer;
};

} // PF_Minigames
