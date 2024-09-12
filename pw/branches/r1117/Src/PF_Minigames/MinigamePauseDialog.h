#pragma once

#include "../Client/MessageDialog.h"
#include "MinigameScreenLogic.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
	class MinigameBase;
};



namespace PF_Minigames
{

class MinigamePauseDialog : public NMainLoop::IMessageScreenCallback, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( MinigamePauseDialog, NMainLoop::IMessageScreenCallback, BaseObjectST );

public:
  MinigamePauseDialog() {}

  void Set( PF_Minigames::MinigameBase * _game, MinigameScreenLogic * _logic )
  {
    game = _game;
    logic = _logic;
  }

  void PopUp();

protected:
  //IMessageScreenCallback
  virtual void SetupMessageWindow( UI::Window * pScreenBaseWindow ) {}
  virtual void OnYesButton(); //Соответствующая кнопка интерфейса называется "Продолжить"
  virtual void OnNoButton(); //Соответствующая кнопка интерфейса называется "Выход"
  virtual bool OnEscapeKey(); //Клавиша "Escape"

private:
  CPtr<PF_Minigames::MinigameBase>   game;
  Weak<MinigameScreenLogic>   logic;
};

}; //namespace PF_Minigames
