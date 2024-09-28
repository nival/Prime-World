#include "stdafx.h"
#include "FinalScreen.h"
#include "FinalScreenLogic.h"
#include "../Core/CoreFSM.h"
#include "../UI/EditBox.h"
#include "../UI/ImageLabel.h"
#include "../UI/SkinStyles.h"

#include "../Render/TextureManager.h"

namespace UI
{

#pragma warning(push)
#pragma warning(disable:4686)
BEGIN_LUA_TYPEINFO( FinalScreenLogic, ClientScreenUILogicBase )
  LUA_METHOD( Test )
END_LUA_TYPEINFO( FinalScreenLogic )
#pragma warning(pop)

  //////////////////////////////////////////////////////////////////////////
  void FinalScreenLogic::Test()
  {
    NCore::GetGlobalGameFSM()->PushMessageToCore( NCore::GameWonOkMessage::NewGameWonOkMessage() );
  }

  void FinalScreenLogic::SetWinLoseText(wstring const &text)
  {
    if (UI::ImageLabel *pText = dynamic_cast<UI::ImageLabel*>(pBaseWindow->GetChild(0)->GetChild("Text_EndOfGame")))
    {
      pText->SetCaptionTextW(text);
    }
  }
}

using namespace UI;
BASIC_REGISTER_CLASS( FinalScreenLogic )
