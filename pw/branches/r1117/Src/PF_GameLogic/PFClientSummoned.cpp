#include "stdafx.h"

#include "PFClientSummoned.h"

#include "Minimap.h"

#include "PFClientBaseUnit.h"
#include "PFSummoned.h"

#include "../PF_Core/ClientObject.h"
#include "../PF_Core/EffectsPool.h"
#include "../System/InlineProfiler.h"

#include "AdventureScreen.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientSummoned::PFClientSummoned(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp)
  : PFCreep(pWO, cp)
{
/*
  const NWorld::PFBaseSummonedUnit* pWorldObject = WorldObject();
  NI_ASSERT(pScene && pWorldObject, "Invalid initialization of client object");
*/

  
}

void PFClientSummoned::PrepareExcludedResourcesList(const NDb::Summoned* pDBPtr, const nstl::string& summonerSkinId, nstl::list<const NDb::DbResource*> &excludes )
{
  if (!summonerSkinId.empty() && summonerSkinId != "default")
  {
    // exclude others  creature skins
    vector<NDb::Ptr<NDb::CreepSkin>>::const_iterator it = pDBPtr->creepSkins.begin();
    for ( ; it != pDBPtr->creepSkins.end(); ++it )
    {
      if ((*it)->heroPersistentId == summonerSkinId)
      {
        continue;
      }

      excludes.push_back(*it);
    }
  }
}

}
