#pragma once

#include "../Client/ScreenBase.h"

namespace NGameX { class FinalScreen; }

namespace UI
{
  class FinalScreenLogic : public ClientScreenUILogicBase
  {
  private:
    OBJECT_METHODS( 0xB625401, FinalScreenLogic );
    DECLARE_LUA_TYPEINFO( FinalScreenLogic );

    NGameX::FinalScreen *m_owner;

    // Test
    UI::Window          *m_resizeIt;
    CTPoint<int>        m_resizeSize;
  public:
    FinalScreenLogic() : m_owner(NULL), m_resizeIt(NULL) {}
    void SetOwner(NGameX::FinalScreen *owner) { m_owner = owner; }

    void SetWinLoseText(wstring const &text);

    void Test();

  private :
    void GenerateButtonStyle();
  };
}