#include "StdAfx.h"
#include "FriendsController.h"

#include "AdventureFlashInterface.h"
#include "FlashFSCommands.h"
#include "ISocialConnection.h"

#include "../UI/FlashContainer2.h"


namespace NGameX
{
  FriendsController::FriendsController( UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, ISocialConnection * _socialConnection,
    const vector<NCore::PlayerStartInfo> & _playersInfo, int _ourUserId)
    : flashInterface(_flashInterface)
    , flashWnd(flashContainer)
    , playerStartInfos(_playersInfo)
    , ourUserId(_ourUserId)
    , socialServer (_socialConnection)
  {
    using namespace FlashFSCommands;

    if (!flashInterface || !flashWnd )
      return;

    flashWnd->AddFSListner(ConvertToString(AddToFriends), this);

    DevTrace("my userId %d\n-------------------------", ourUserId);

    if (!socialServer)
      return;

    for (int i = 0; i< playerStartInfos.size(); i++)
    {
       DevTrace("UserInfo userId = %d, slot = %d", playerStartInfos[i].userID, playerStartInfos[i].playerID);

       for (int j = 0; j< playerStartInfos[i].playerInfo.friends.size(); j++)    
       {
         DevTrace("friendId = %d", playerStartInfos[i].playerInfo.friends[j] );
       }

       DevTrace("-----------------------");
    }


    for (int i = 0; i< playerStartInfos.size(); i++)
    {
      const NCore::PlayerStartInfo & myStartInfo = playerStartInfos[i];
      if (myStartInfo.userID != ourUserId)
        continue;

      for (int j = 0; j< myStartInfo.playerInfo.friends.size(); j++)    
      {
        int friendId = myStartInfo.playerInfo.friends[j];
        
        for (int k = 0; k< playerStartInfos.size(); k++)    
        {
           if (playerStartInfos[k].userID == friendId && friendId != ourUserId)   
           {
             DevTrace("SetFriendship for user %d", playerStartInfos[k].playerID);
             flashInterface->SetFriendship(playerStartInfos[k].playerID, true, false);
           }
        }
      }

      break;
    }
  }


  FriendsController::~FriendsController()
  {
    using namespace FlashFSCommands;

    if (!flashWnd)
      return;

    flashWnd->RemoveFSListner(ConvertToString(AddToFriends));
  }


  void FriendsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
  {
    if (!flashInterface || !socialServer)
      return;

    //пока всего один листенер так что без свитча.
    int playerId;
    sscanf_s(args,"%d", &playerId);

    for (int i = 0; i< playerStartInfos.size(); i++)    
    {
      if (playerStartInfos[i].playerID != playerId)   
        continue;

      DevTrace("SentRequest for frienship user %d", playerStartInfos[i].userID );
      if (socialServer->AddFriend( playerStartInfos[i].userID ))
        flashInterface->SetFriendship(playerStartInfos[i].playerID, false, true);

      break;
    }
  }
}

NI_DEFINE_REFCOUNT(NGameX::FriendsController)
