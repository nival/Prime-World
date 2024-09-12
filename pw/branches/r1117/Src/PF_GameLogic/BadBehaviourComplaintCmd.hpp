#pragma once

#include "Core/WorldCommand.h"
#include "PFPlayer.h"
#include "PlayerBehaviourTracking.h"

// NOTE: hardcode. полагаемся на то, что оператор настроит список жалоб правильно. см. NUM_TASK
#define BAD_BEHAVIOUR_REPORT_ITEM_ID 1
#define INSULT_REPORT_ITEM_ID 2

namespace
{
  inline bool CheckPlayer(const CPtr<NWorld::PFPlayer>& player)
  {
    if (IsValid(player))
      return true;

    return false;
  }

  inline bool CheckPlayer(const CPtr<NWorld::PFPlayer>& player, const int userId)
  {
    if (IsValid(player))
      if (player->GetUserID() == userId)
        return true;

    NI_ALWAYS_ASSERT(NStr::StrFmt("Wrong player received in command (uid=%d)", userId));

    return false;
  }
}

namespace PlayerBehaviourTracking
{
  DEFINE_3_PARAM_CMD_CHECK ( 0x15C653C0, CmdBadBehaviourComplaint, CPtr<NWorld::PFPlayer>, sender, CPtr<NWorld::PFPlayer>, receiver, int, reportItemId );

  bool CmdBadBehaviourComplaint::CanExecute() const
  {
    if (!CheckPlayer(sender, GetId()))
      return false;
    if (!CheckPlayer(receiver))
      return false;

    // NOTE: такое не может случиться при нормальных условиях
    if (sender == receiver)
    {
      ErrorTrace("CmdBadBehaviourComplaint: reported self (uid=%d)", sender->GetUserID());
      return false;
    }

    /*if (sender->GetTeamID() != receiver->GetTeamID())
    {
      DevTrace("CmdBadBehaviourComplaint: reported enemy (sender uid=%d, reported uid=%d)", sender->GetUserID(), receiver->GetUserID());
      return false;
    }*/
    if(reportItemId!= BAD_BEHAVIOUR_REPORT_ITEM_ID && reportItemId!= INSULT_REPORT_ITEM_ID)
    {
      DevTrace("CmdBadBehaviourComplaint: Bad reportItemId (sender uid=%d, reported uid=%d, reportItemId=%d)", sender->GetUserID(), receiver->GetUserID(), reportItemId);
      return false;
    }
    return true;
  }

  void CmdBadBehaviourComplaint::Execute(NCore::IWorldBase*)
  {
    if (reportItemId == BAD_BEHAVIOUR_REPORT_ITEM_ID)
        PlayerBehaviourTracking::DispatchEvent(receiver, EPlayerBehaviourEvent::GotBadBehaviourComplaint);
    else if(reportItemId == INSULT_REPORT_ITEM_ID) 
      PlayerBehaviourTracking::DispatchEvent(receiver, EPlayerBehaviourEvent::GotToxicPlayerComplaint);
  }

  static NCore::WorldCommand* CreateBadBehaviourComplaintCmd(const CPtr<NWorld::PFPlayer>& sender, const CPtr<NWorld::PFPlayer>& receiver, const int reportItemId)
  {
    return new CmdBadBehaviourComplaint(sender, receiver, reportItemId);
  }
}

REGISTER_SAVELOAD_CLASS_NM(CmdBadBehaviourComplaint, PlayerBehaviourTracking)

