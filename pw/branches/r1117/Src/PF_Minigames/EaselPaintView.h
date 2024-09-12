#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

class MinigameClientObject;

class Easel;
class EaselPaintViewFragment;

class EaselPaintViewBackground;
class EaselPaintViewPath;
class EaselPaintViewPicture;

class LuxGameLogic;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class represents view logic for paint part. It listens for luxor logic notifications and acts correspondingly
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselPaintView : public CObjectBase
{
	OBJECT_METHODS(0x9963D340, EaselPaintView);
public:

	EaselPaintView();

	void ReleasePicture( LuxGameLogic* _gameLogic );
  void InitPicture( LuxGameLogic* _gameLogic );

  void Update( float deltaTime, LuxGameLogic* _gameLogic );

  void CreateAll( LuxGameLogic* _gameLogic );
  void DestroyAll( LuxGameLogic* _gameLogic );

private:
	
	typedef nstl::map<void* , CPtr<EaselPaintViewFragment> > FragmentClientObjects;
  FragmentClientObjects fragmentObjects;

  CPtr<EaselPaintViewPicture>    picture;

  bool hidden;
};

} // PF_Minigames
