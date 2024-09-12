#pragma once

#include "Core/WorldCommand.h"
#include "PFPlayer.h"
#include "PlayerBehaviourTracking.h"
#include "BadBehaviourComplaintCmd.hpp"
#include <locale>
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "Tools/Censor/CensorDll.h"
namespace
{
  bool isLower(wchar_t ch)
  {
    return islower(ch,std::locale(""));
  }


  bool isUpperString(const wstring& s )
  {
    wstring::const_iterator cit = find_if(s.begin(), s.end(), isLower);
    if(cit !=s.end())
      return false;
    else
      return true;
  }

}

namespace PlayerBehaviourTracking
{
  using NWorld::PFWorld;
  using NWorld::PFAIWorld;

  DEFINE_2_PARAM_CMD_CHECK ( 0x59D72340, CmdBadBehaviourChatMessage, CPtr<NWorld::PFPlayer>, sender, wstring, message);

  bool CmdBadBehaviourChatMessage::CanExecute() const
  {
    if (!CheckPlayer(sender, GetId()))
      return false;
    return true;
  }

  void CmdBadBehaviourChatMessage::Execute(NCore::IWorldBase* pWorld)
  {
    CPtr<PFWorld> pPFWorld= dynamic_cast<PFWorld*>(pWorld);
    if (!pPFWorld)
        return; 

    const PFAIWorld* aiWorld = pPFWorld->GetAIWorld();

    const NDb::Ptr<NDb::BehaviourTrackerParams>& params = aiWorld->GetBahaviourTrackerParams();

    NI_DATA_ASSERT(IsValid(params), "Behaviour tracker params must be defined");
    
     //DebugTrace( "CmdBadBehaviourChatMessage::Execute  for message %s", message.c_str() );
    
    if (message.size() >=params->autoMuteMessageLength)
    {
      PlayerBehaviourTracking::DispatchEvent(sender, EPlayerBehaviourEvent::AutoMuteMessageLength);
    }
    
    if (isUpperString(message))
    {
      PlayerBehaviourTracking::DispatchEvent(sender, EPlayerBehaviourEvent::CapsMeessage);
    }
    PlayerBehaviourTracking::DispatchEvent(sender, EPlayerBehaviourEvent::SpamDetected);

    //PlayerBehaviourTracking::DispatchEvent(sender, EPlayerBehaviourEvent::AutoMuteMessage);
    int id;
    wchar_t str[8192];
    wcsncpy ( str, message.c_str(), 8192 );
    while(CensorFilter::GetFilteredAsync(id, str, 8192)){}
    if (message.compare(str)!=0)
    {
        PlayerBehaviourTracking::DispatchEvent(sender, EPlayerBehaviourEvent::MessageInFilter);
    }

    
  }

  static NCore::WorldCommand* CreateBadBehaviourChatMessageCmd(const CPtr<NWorld::PFPlayer>& sender, wstring message)
  {
    return new CmdBadBehaviourChatMessage(sender, message);
  }
}

REGISTER_SAVELOAD_CLASS_NM(CmdBadBehaviourChatMessage, PlayerBehaviourTracking)

