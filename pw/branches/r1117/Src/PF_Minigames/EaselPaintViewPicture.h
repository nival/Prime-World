#pragma once

#include "MinigameClientObject.h"
#include "EaselPaintLayerSceneComponent.h"

namespace PF_Minigames
{

class Easel;

class EaselPaintViewPicture : public MinigameClientObject
{
	OBJECT_METHODS(0xC8681A00, EaselPaintViewPicture);
public:

	EaselPaintViewPicture()
  : fIsHidden(false)
  , fIsInit(false)
  {

  }

  bool Init(Easel& _easel );

	virtual void Update(float deltaTime, bool gameOnPause);

  const CObj<NScene::EaselPaintSceneComponent>& GetPaint() {return paint;}

  void Show();
  void Hide();

private:

  bool fIsHidden;
  bool fIsInit;

  CObj<NScene::EaselPaintSceneComponent> paint;
};

} // PF_Minigames
