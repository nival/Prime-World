#pragma once

#include "../UI/FSCommandListner.h"
#include "../Core/GameTypes.h"
#include "ChatController.h"
#include "BindsController.h"

namespace UI            
{ 
	class FlashContainer2; 
}

namespace NGameX
{
	class AdventureFlashInterface;
	_interface ISocialConnection;
  _interface IUIEventHandler;
}

namespace NWorld
{
	class PFBaseHero;
}


namespace NGameX
{

	class ComplainController:public UI::IFSCommandListner, public BaseObjectST
	{
		NI_DECLARE_REFCOUNT_CLASS_2( ComplainController, UI::IFSCommandListner, BaseObjectST );
	public:
		ComplainController( UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, ISocialConnection * _socialConnection,  const vector<NCore::PlayerStartInfo> & _playersInfo,ChatUiController* _chatController , BindsController* _bindsController);
		~ComplainController();

		// from UI::IFSCommandListner
		virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );
		void Init(int complaintsToday,int complaintsMax, NCore::TComplaintInfo const&  complaintsInfo);
	private:

		Weak<ISocialConnection>        socialServer;
		Weak<UI::FlashContainer2>              flashWnd;
		Weak<AdventureFlashInterface>          flashInterface;
		vector<NCore::PlayerStartInfo> playerStartInfos;
    Weak<ChatUiController> chatController;
    Weak<BindsController> bindsContoller;
	};

}