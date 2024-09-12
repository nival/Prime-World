#ifndef TALENTROLLDATACACHE_H_INCLUDED
#define TALENTROLLDATACACHE_H_INCLUDED

#include "RollTypes.h"
#include <map>

namespace roll
{

class TalentRollDataCache : public BaseObjectST
{
NI_DECLARE_REFCOUNT_CLASS_1( TalentRollDataCache, BaseObjectST );

public:
  TalentRollDataCache( timer::Time now );

  void Put( lobby::TUserId uid, const NCore::TalentRollData & data );
  void GetCorrectData( NCore::TalentRollData & result, const NCore::TalentRollData & newData, lobby::TUserId uid );
  void Poll( timer::Time now );

private:
  struct Entry
  {
    NCore::TalentRollData   data;
    timer::Time             lastAccess;

    Entry() : lastAccess( 0 ) {}
  };

  typedef std::map<lobby::TUserId, Entry> Storage;

  Storage storage;
  timer::Time lastUpdate;
};

} //namespace roll

#endif //TALENTROLLDATACACHE_H_INCLUDED
