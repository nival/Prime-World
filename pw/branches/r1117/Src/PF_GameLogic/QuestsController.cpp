#include "stdafx.h"
#include "QuestsController.h"


#include "AdventureScreen.h"
#include "Minimap.h"
#include "FlashFSCommands.h"
#include "../ui/FlashContainer2.h"


namespace NGameX
{

QuestsController::QuestsController( UI::FlashContainer2* flashContainer, NDb::Ptr<NDb::SessionQuestsCollection> const& _questsCollection )
: flashWnd(flashContainer)
{
  using namespace FlashFSCommands;

  questsCollection = _questsCollection;
	flashWnd->AddFSListner(ConvertToString(QuestClicked), this);
}

QuestsController::~QuestsController()
{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(QuestClicked));

  for ( TQuestsSignal::iterator it = signals.begin(); it != signals.end(); ++it )
    it->second.clear();

  signals.clear();
}

void QuestsController::SessionQuestRemoveSignal( string idQuest, string idSignal )
{
  TQuestsSignal::iterator it = signals.find(idQuest);

  if( it != signals.end() )
    it->second.erase(idSignal);
}

void QuestsController::SessionQuestUpdateSignal( string idQuest, string idSignal, float x, float y )
{
  TQuestsSignal::iterator it = signals.find(idQuest);

  if( it != signals.end() )
    it->second[idSignal] = UI::Point( x, y );
  else
  {
    TSignals signal;
    signal[idSignal] = UI::Point( x, y );
    signals[idQuest] = signal;
  }
}

void QuestsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  NI_DATA_VERIFY( questsCollection, "No quests for the map", return )
  NI_ASSERT( FlashFSCommands::ConvertToFSCommand(listenerID) == FlashFSCommands::QuestClicked, "bad command")
  NI_ASSERT( argsW, "bad id string")

  const NGameX::AdventureScreen* adventureScreen = NGameX::AdventureScreen::Instance();

  long id = _wtol(argsW);
  
  NDb::SessionQuest const* pDBSessionQuest = 0;
  // find quest by id
  for ( TQuests::const_iterator it = questsCollection->quests.begin(); it != questsCollection->quests.end(); ++it )
  {
    if ( (long)Crc32Checksum().AddString(it->id.c_str()).Get() == id )
    {
      pDBSessionQuest = it;
      break;
    }
  }

  NI_DATA_VERIFY( pDBSessionQuest, NStr::StrFmt( "Quest with id = '%s' not found", id ), return );

  if ( NGameX::Minimap *pMinimap = adventureScreen->GetMinimap() )
  {
    TQuestsSignal::const_iterator signal = signals.find(pDBSessionQuest->id);

    if( signal != signals.end() )
    {
      for ( TSignals::const_iterator it = signal->second.begin(); it != signal->second.end(); ++it )
      {
        pMinimap->AddSignal( CVec3( it->second.x, it->second.y, 0 ),  adventureScreen->GetPlayerFaction() );
      }
    }
  }
}

}; //namespace NGameX

NI_DEFINE_REFCOUNT(NGameX::QuestsController)
