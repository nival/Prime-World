#include "stdafx.h"
#include "PFClientVotingForSurrender.h"
#include "AdventureScreen.h"
#include "PrecompiledTooltips.h"

namespace NGameX 
{
  ClientVotingForSurrender::ClientVotingForSurrender( PF_Core::WorldObjectRef pWO, NDb::Ptr<NDb::VotingForSurrender> pDb )
    : PFClientObjectBase(pWO)
    , pDb(pDb)
  {
    //Nothing
  }

  void ClientVotingForSurrender::SendUserMsg( NDb::VFSUserMessages msg, const VotingForSurrenderNameMap &map ) const
  {
    NGameX::AdventureScreen *pAdv = NGameX::AdventureScreen::Instance();

    NI_ASSERT( IsValid(pAdv), "" );

    if( pDb->messages[msg].type == NDb::VFSMESSAGETYPE_SHOWMESSAGETOPLAYER )
    {
      NI_ASSERT( IsValid(map.GetPlayer()), "" );

      if( map.GetPlayer() != pAdv->GetPlayer() )
        return;
    }

    if( pDb->messages[msg].type == NDb::VFSMESSAGETYPE_SHOWMESSAGETOCOMMAND )
    {
      if( map.GetTeam() != pAdv->GetPlayer()->GetTeamID() )
        return;
    }


    PrecompiledTooltip tooltip;
    wstring out;

    tooltip.Parse( pDb->messages[msg].text.GetText() );
    tooltip.ResolveVariants( &map );
    tooltip.MakeText( out );

    pAdv->AddMessageToChat( out );
  }
}
