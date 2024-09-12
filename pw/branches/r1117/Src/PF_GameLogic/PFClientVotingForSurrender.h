#pragma once

#include "PFWorldObjectBase.h"
#include "PFClientObjectBase.h"
#include "AIWorldFacets/VotingForSurrenderLogic.h"

namespace NGameX 
{
  using NWorld::AIWorldFacets::VotingForSurrenderLogic;
  using NWorld::AIWorldFacets::VotingForSurrenderNameMap;

  class ClientVotingForSurrender: public NWorld::PFClientObjectBase
  {
    CLIENT_OBJECT_METHODS( 0x67888C00, ClientVotingForSurrender, VotingForSurrenderLogic )
  public:
    ClientVotingForSurrender( PF_Core::WorldObjectRef pWO, NDb::Ptr<NDb::VotingForSurrender> pDb );

    void SendUserMsg( NDb::VFSUserMessages msg, const VotingForSurrenderNameMap &map ) const;
  protected:
    ClientVotingForSurrender() {}
  private:
    NDb::Ptr<NDb::VotingForSurrender> pDb;
  };
}
