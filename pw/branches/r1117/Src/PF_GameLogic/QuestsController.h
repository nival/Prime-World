#pragma  once

#include "../UI/FSCommandListner.h"
#include "../UI/Defines.h"

namespace UI
{ 
	class FlashContainer2;
}

namespace NGameX
{
class QuestsController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( QuestsController, UI::IFSCommandListner, BaseObjectST );

public:
	QuestsController( UI::FlashContainer2* flashContainer, NDb::Ptr<NDb::SessionQuestsCollection> const& _questsCollection );
  ~QuestsController();

	// from UI::IFSCommandListner
	virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  void SessionQuestRemoveSignal( string idQuest, string idSignal );
  void SessionQuestUpdateSignal( string idQuest, string idSignal, float x, float y );

private:

  typedef vector<NDb::SessionQuest> TQuests;

  Weak<UI::FlashContainer2> flashWnd;

  typedef hash_map<string, UI::Point> TSignals;
  typedef hash_map<string, TSignals> TQuestsSignal;
  TQuestsSignal signals;

	// Quests Collection
	NDb::Ptr<NDb::SessionQuestsCollection> questsCollection;

};

};//namespace NGameX

