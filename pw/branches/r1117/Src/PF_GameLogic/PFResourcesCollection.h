#ifndef PFRESOURCESCOLLECTION_H_CCCFDC0F
#define PFRESOURCESCOLLECTION_H_CCCFDC0F

#include "ResourcesCollection.h"
#include "System/Crc32Checksum.h"


namespace NDb
{
  struct Talent;
  struct Consumable;
  struct MarketingEventRollItem;
}

namespace NWorld
{

  // этот класс является так же используется серверной RollLogic
  // при этом хидер общий, а имплементация серверная находится в PFResources.cpp
  class PFResourcesCollection : public CObjectBase
  {
    OBJECT_BASIC_METHODS( PFResourcesCollection );
  public:
    typedef nstl::map<uint, NDb::Ptr<NDb::Talent>> TalentMap;
    typedef nstl::map<uint, NDb::Ptr<NDb::Consumable>> ConsumablesMap;
    typedef nstl::map<uint, NDb::Ptr<NDb::MarketingEventRollItem>> MarketingItemMap;


    PFResourcesCollection() {}

    void OnDestroyContents()
    {
      CObjectBase::OnDestroyContents();

      DebugTrace("[ResourceCollection] destroyed");
    }

    void CollectTalents()
    {
      DebugTrace("[ResourceCollection] collect talents");
      CollectResources( "Items\\", "*.TALENT.xdb", talents, hashedTalents );
    }

    void CollectMarketingItems()
    {
      DebugTrace("[ResourceCollection] collect marketingItems");
      CollectResources( "Items\\", "*.ROLLITEM.xdb", marketingItems, hashedMarketingItems );
    }

    void CollectConsumables();

    NDb::Ptr<NDb::Talent> FindTalentById(const string& persistentId) const
    {
      int id = Crc32Checksum().AddString(persistentId.c_str()).Get();
      return FindTalentById(id);
    }


    NDb::Ptr<NDb::Talent> FindTalentById(uint id) const
    {
      TalentMap::iterator it = hashedTalents.find(id);
      if (it != hashedTalents.end())
      {
        return it->second;
      }
      return NDb::Ptr<NDb::Talent>();
    }

    NDb::Ptr<NDb::MarketingEventRollItem> FindMarketingById(uint id) const
    {
      MarketingItemMap::iterator it = hashedMarketingItems.find(id);
      if (it != hashedMarketingItems.end())
      {
        return it->second;
      }
      return NDb::Ptr<NDb::MarketingEventRollItem>();
    }

    NDb::Ptr<NDb::Consumable> FindConsumableById(uint id) const
    {
      ConsumablesMap::iterator it = hashedConsumables.find(id);
      if (it != hashedConsumables.end())
      {
        return it->second;
      }
      return NDb::Ptr<NDb::Consumable>();
    }

    const TalentMap& GetTalents() const { return hashedTalents; }
    const ConsumablesMap& GetConsumables() const { return hashedConsumables; }
    const MarketingItemMap& GetMarketingItems() const { return hashedMarketingItems; }
  private:
    template<class T, class H>
    void CollectResources( const char* folder, const char* mask, ResourcesCollection<T>& resources, nstl::map<uint, H>& hashedRes )
    {
      resources.Scan( folder, mask );
      for (int i=0;i<resources.size();++i)
      {
        string s = resources[i]->persistentId;
        if (resources[i]->persistentId.length() > 0)
        {
          int id = Crc32Checksum().AddString(resources[i]->persistentId.c_str()).Get();
          nstl::map<uint, H>::iterator it = hashedRes.find(id);
          NI_ASSERT(it == hashedRes.end(), NStr::StrFmt( "Dublicate collected resource found \"%s\" in \"%s\"", resources[i]->persistentId.c_str(), GetFormattedDbId( resources[i]->GetDBID())));
          hashedRes[id] = resources[i];
        }
      }
    }

    ResourcesCollection<NDb::Talent> talents;
    ResourcesCollection<NDb::MarketingEventRollItem> marketingItems;
    ResourcesCollection<NDb::Consumable> consumables;
    TalentMap hashedTalents;
    ConsumablesMap hashedConsumables;
    MarketingItemMap hashedMarketingItems;
  };

} //namespace NWorld

#endif //#define PFRESOURCESCOLLECTION_H_CCCFDC0F