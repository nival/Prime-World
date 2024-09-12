#pragma once

namespace NWorld
{
  class PFBaseUnit;
  class PFBaseHero;
  class PFAchievBase;
}

namespace NGameX
{

struct AnnouncementParams //: public BaseObjectST
{
   //NI_DECLARE_REFCOUNT_CLASS_1( AnnouncementParams, BaseObjectST );
public:

  ConstPtr<NWorld::PFBaseUnit> killer;
  ConstPtr<NWorld::PFBaseUnit> victim;
  //ConstPtr<NWorld::PFBaseHero> hero;
  ConstPtr<NWorld::PFAchievBase> achiev;
};

}