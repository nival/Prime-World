#ifndef MINIGAMES_H_INCLUDED
#define MINIGAMES_H_INCLUDED

#include "MinigamesBase.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	_interface IScene;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

class MinigameCameraController;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Minigames : public MinigamesBase
{
  OBJECT_METHODS( 0x9D632B40, Minigames )

public:

	Minigames( NWorld::PFWorld * _pWorld );
	virtual ~Minigames();

  // IMinigames:
  virtual bool    StartMinigame( NWorld::PFMinigamePlace * place );
  virtual void    LeaveMinigame();

  //Client part of IMinigames
  virtual void    UpdateM( float deltaTime );
  virtual void    SetPlacement( const Placement& _placement);
  virtual float   GetMinigamePlaceOpacity() const;
  virtual bool    DoFade() const;
  
  void  SetCameraController( MinigameCameraController* _cameraController ) { cameraController = _cameraController; }
	const CPtr<MinigameCameraController>& GetCameraController() const { return cameraController; }

  const Placement& GetPlacement() const  { return placement; }

  virtual void  InitGames();
  
private:
  Minigames() {}
	CPtr<MinigameCameraController> cameraController;

  Placement placement;
  float fadeTime;
  float currentFadeTime;
  bool doFade;
  bool fadeEnabled;
  bool fadeIn;

  ZDATA_(MinigamesBase)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigamesBase*)this); return 0; }
};

} // namespace PF_Minigames

#endif //MINIGAMES_H_INCLUDED
