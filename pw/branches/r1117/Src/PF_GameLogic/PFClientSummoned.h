#pragma once

#include "../PF_Core/ClientObject.h"

#include "PFClientSummoned.h"
#include "PFClientCreep.h"

#include "PFSummoned.h"

namespace NGameX
{

class PFClientSummoned : public PFCreep
{
  CLIENT_OBJECT_METHODS(  0xB199CB00, PFClientSummoned, NWorld::PFBaseSummonedUnit )
public:

  struct CreatePars : public PFCreep::CreatePars
  {
    CreatePars(const NDb::Summoned &unit, NDb::AnimSet const* pAnimSet, NScene::IScene *pS, NDb::EFaction _faction, const nstl::string& nodeName, bool bStartIdleAnim, const nstl::string& skinId)
      : PFClientCreature::CreatePars(SelectSceneObj(unit, skinId), pAnimSet, pS, nodeName, bStartIdleAnim)
      , faction(_faction)
      , pDesc(&unit)
    {}

    NDb::Ptr<NDb::DBSceneObject> const& SelectSceneObj(const NDb::Summoned &unit, const nstl::string& skinId ) const
    {
      if (!skinId.empty() && skinId != "default")
      {
        vector<NDb::Ptr<NDb::CreepSkin>>::const_iterator it = unit.creepSkins.begin();
        for ( ; it != unit.creepSkins.end(); ++it )
        {
          if ((*it)->heroPersistentId == skinId)
          {
            return (*it)->sceneObject;  
          }
        }  
      }

      return unit.sceneObject;
    }

    NDb::Summoned const* pDesc;
    NDb::EFaction faction;
  };

	PFClientSummoned(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp);
  static void PrepareExcludedResourcesList(const NDb::Summoned* pDBPtr, const nstl::string& summonerSkinId, nstl::list<const NDb::DbResource*> &excludes );

protected:
  explicit PFClientSummoned() {}

private:
  
};


} // namespace NGameX
