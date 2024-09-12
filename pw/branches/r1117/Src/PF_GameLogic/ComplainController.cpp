#include "StdAfx.h"
#include "ComplainController.h"

#include "AdventureFlashInterface.h"
#include "FlashFSCommands.h"
#include "ISocialConnection.h"
#include "../UI/FlashContainer2.h"
#include "AdventureScreen.h"
#include "ChatController.h"
#include "DBStats.h"

// NOTE: hardcode. полагаемся на то, что оператор настроит список жалоб правильно. см. NUM_TASK
#define BAD_BEHAVIOUR_REPORT_ITEM_ID 1
#define INSULT_REPORT_ITEM_ID 2

namespace
{
  inline bool IsBadBehaviourComplaint(const int reportItemId)
  {
    return (reportItemId == BAD_BEHAVIOUR_REPORT_ITEM_ID);
  }

  inline bool IsInsultComplaint(const int reportItemId)
  {
    return (reportItemId == INSULT_REPORT_ITEM_ID);
  }

}

namespace NGameX
{
  ComplainController::ComplainController( UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, ISocialConnection * _socialConnection,
    const vector<NCore::PlayerStartInfo> & _playersInfo, ChatUiController* _chatController, BindsController* _bindsContoller )
    : flashInterface(_flashInterface)
    , flashWnd(flashContainer)
    , playerStartInfos(_playersInfo)
    , socialServer (_socialConnection)
    , chatController(_chatController)
    , bindsContoller(_bindsContoller)
  {
    using namespace FlashFSCommands;

    if (!flashInterface || !flashWnd )
      return;

    flashWnd->AddFSListner(ConvertToString(SendReportOnUser), this);
    flashWnd->AddFSListner(ConvertToString(ReportWindowOpened), this);
  }


  ComplainController::~ComplainController()
  {
    using namespace FlashFSCommands;

    if (!flashWnd)
      return;

    flashWnd->RemoveFSListner(ConvertToString(SendReportOnUser));
    flashWnd->RemoveFSListner(ConvertToString(ReportWindowOpened));
  }


  void ComplainController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
  {
    struct Local
    {
      typedef Weak<ISocialConnection> SocialConnectionPtr;

      static int FindPlayerUserId(const NCore::TPlayersStartInfo& psi_list, const int playerId)
      {
        for (int i = 0; i < psi_list.size(); ++i)
        {
          const NCore::PlayerStartInfo& psi = psi_list[i];

          if (psi.playerID == playerId)
            return psi.userID;
        }

        return -1;
      }

      static const NWorld::PFPlayer* FindPlayer(const int userId)
      {
        if (AdventureScreen* const advScreen = AdventureScreen::Instance())
        {
          if (const NWorld::PFWorld* const world = advScreen->GetWorld())
          {
            return world->GetPlayerByUID(userId);
          }
        }

        return NULL;
      }

      static void AddPlayerToComplaintsList(const NWorld::PFPlayer* const player)
      {
        if (!player)
          return;

        if (AdventureScreen* const advScreen = AdventureScreen::Instance())
        {
          // NOTE: const_cast обусловлен стремлением к чистому интерфейсу этой обертки
          const CPtr<NWorld::PFPlayer> player_ptr(const_cast<NWorld::PFPlayer*>(player));

          advScreen->AddToComplList(player_ptr);
        }
      }

      static void NotifyBadBehaviourComplaintCreated(const int playerUserId, const int reportItemId)
      {
        if (!playerUserId)
          return;

        if (AdventureScreen* const advScreen = AdventureScreen::Instance())
        {
          advScreen->OnBadBehaviourComplaint(playerUserId, reportItemId);
        }
      }
    };

    using namespace FlashFSCommands;

    if (!flashInterface )
      return;

    switch (ConvertToFSCommand(listenerID))
    {
    case SendReportOnUser:
      {
        const wchar_t* const p0 = argsW;
        const wchar_t* const p1 = wcschr(p0, L' ') + 1;
        const wchar_t* const p2 = wcschr(p1, L' ') + 1;

        int playerId;
        int reportItemId;

        swscanf_s(p0, L"%d", &playerId);
        swscanf_s(p1, L"%d", &reportItemId);

        const int playerUserId = Local::FindPlayerUserId(playerStartInfos, playerId);

        if (IsValid(socialServer))
        {
          const wstring message(p2);

          wstring chatLog;

          typedef vector<gamechat::ChatMessage> TChatMessages;

          const TChatMessages& chatMessages = chatController->GetChatMessages();

          TChatMessages::const_iterator it = chatMessages.begin();
          TChatMessages::const_iterator it_end = chatMessages.end();
          for (; it != it_end; ++it)
          {
            chatLog.append(NStr::StrFmtW(L"type %d channel %d userName %s message %s \r\n", it->messageType, static_cast<int>(it->channel), it->nickname.c_str(), it->message.c_str()));
          }

          int kills = 0;
          int deaths = 0;
          int assists = 0;
          int points = 0;
          int prime = 0;
          int leave = 0;
          int distance = 0;
          int afks = 0;

          if (const NWorld::PFPlayer* const player = Local::FindPlayer(playerUserId))
          {
            Local::AddPlayerToComplaintsList(player);

            if (const NWorld::PFBaseHero* const hero = player->GetHero())
            {
              if (const NWorld::PFHeroStatistics* stat = hero->GetHeroStatistics())
              {
                kills = stat->GetTotalNumHeroKills();
                deaths = stat->GetNumDeaths();
                assists = stat->GetTotalNumHeroAssists();
                prime = stat->GetMoney();
                points = stat->GetGrandScore();
                distance = static_cast<int>(floor(stat->GetDistanceTraveled()));
                afks = stat->GetAfks();
                leave = stat->GetLeaveStatus();
              }
            }
          }

          socialServer->CreateComplaint(playerUserId, reportItemId, message, chatLog, kills, deaths, assists, points, prime, leave, distance, afks);
        }

        if (IsBadBehaviourComplaint(reportItemId) || IsInsultComplaint(reportItemId))
        {
          Local::NotifyBadBehaviourComplaintCreated(playerUserId, reportItemId);
        }
      }
    case ReportWindowOpened:
      {
        if (!IsValid(bindsContoller))
          return;
        int isReportOpened;
        sscanf_s(args,"%d", &isReportOpened);

        bindsContoller ->SetEnabled(BindsController::ReportWindow,!isReportOpened);
      }
    }
  }

  void ComplainController::Init(int complaintsToday, int complaintsMax, NCore::TComplaintInfo const&  complaintsInfo)
  {
    NI_VERIFY(flashInterface, "invalid flashinterface data", return);

    for(NCore::TComplaintInfo::iterator itr = complaintsInfo.begin(); itr != complaintsInfo.end(); ++itr)
    {
      wstring s;
      NStr::ToUnicode( &s, itr->second );
      flashInterface->SetComplainsItem( itr->first, s );
    }
    DebugTrace( "complaintsToday %d complaintsMax %d", complaintsToday,complaintsMax );
    flashInterface->SetComplainsCount(complaintsToday,complaintsMax);
  }
}

NI_DEFINE_REFCOUNT(NGameX::ComplainController)
