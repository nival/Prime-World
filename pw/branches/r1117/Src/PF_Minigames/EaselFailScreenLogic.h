#pragma once

#include "../Client/ScreenUILogicBase.h"

namespace PF_Minigames
{

class Minigames;

//////////////////////////////////////////////////////////////////////////
//
// Fail screen logic
//
//////////////////////////////////////////////////////////////////////////
class EaselFailScreenLogic : public UI::ClientScreenUILogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( EaselFailScreenLogic, UI::ClientScreenUILogicBase );
  DECLARE_LUA_TYPEINFO( EaselFailScreenLogic );

public:
  EaselFailScreenLogic();
  virtual ~EaselFailScreenLogic();

  void Init( PF_Minigames::Minigames* minigames );
  void InitLayout();

  void Step( float deltaTime );

  // function called from lua
  void Exit();

private:
  EaselFailScreenLogic(const EaselFailScreenLogic &rhs);
  EaselFailScreenLogic& operator=(const EaselFailScreenLogic &rhs);

  bool fIsInit;

  // minigames object
  CPtr<PF_Minigames::Minigames> associatedMinigames;

protected:

};


}