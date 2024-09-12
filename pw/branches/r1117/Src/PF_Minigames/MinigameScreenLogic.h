#ifndef MINIGAMESCREENLOGIC_H_INCLUDED
#define MINIGAMESCREENLOGIC_H_INCLUDED

#include "../Client/BaseOvertipsScreenLogic.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigameScreenLogic : public UI::BaseOvertipsScreenLogic
{
  NI_DECLARE_REFCOUNT_CLASS_1( MinigameScreenLogic, UI::BaseOvertipsScreenLogic );

public:
  MinigameScreenLogic();

public:
  virtual void ExitGame() {}
};

} //namespace PF_Minigames

#endif //MINIGAMESCREENLOGIC_H_INCLUDED
