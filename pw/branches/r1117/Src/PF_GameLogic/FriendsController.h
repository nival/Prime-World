#pragma once

#include "../UI/FSCommandListner.h"
#include "../Core/GameTypes.h"

namespace UI            
{ 
  class FlashContainer2; 
}

namespace NGameX
{
  class AdventureFlashInterface;
  _interface ISocialConnection;
}

namespace NWorld
{
  class PFBaseHero;
}


namespace NGameX
{

class FriendsController:public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( FriendsController, UI::IFSCommandListner, BaseObjectST );
public:
  FriendsController( UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, ISocialConnection * _socialConnection,  const vector<NCore::PlayerStartInfo> & _playersInfo, int _ourUserId);
  ~FriendsController();

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );
private:

  Weak<ISocialConnection>        socialServer;
  Weak<UI::FlashContainer2>              flashWnd;
  Weak<AdventureFlashInterface>          flashInterface;

  vector<NCore::PlayerStartInfo> playerStartInfos;
  int ourUserId;

};

}