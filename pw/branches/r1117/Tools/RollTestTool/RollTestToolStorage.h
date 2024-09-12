#ifndef _ROLL_STORAGE_H_
#define _ROLL_STORAGE_H_

#include "Server/Roll/RollLog.h"
#include "Server/Roll/RollLogic.h"
#include "Server/Roll/RollConfig.h"

const int MEMORY_BUFFER_SIZE = 1<<16;

struct RollTestToolUserAwards
{
  RollTestToolUserAwards(){};
  RollTestToolUserAwards(roll::UserId userId, NCore::TalentRollData talentRollData)
    :userId(userId), talentRollData(talentRollData){}

  ZDATA
  roll::UserId                userId;
  NCore::TalentRollData talentRollData;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userId); f.Add(3,&talentRollData); return 0; }
};

struct RollTestToolStorageEntry{
  //SERIALIZE_ID();

  ZDATA
  string mapDesc;
  int userAwardsCount;
  nstl::vector<RollTestToolUserAwards> userAwards;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mapDesc); f.Add(3,&userAwardsCount); f.Add(4,&userAwards); return 0; }

  RollTestToolStorageEntry() 
    : userAwardsCount(0)
  {
    userAwards.clear();
  }

  void fromSUserAwards(const vector<roll::SUserAward>& rollResult)
  {
    userAwards.clear();

    for(int i = 0; i < rollResult.size(); ++i)
    {
      RollTestToolUserAwards& award = userAwards.push_back();
      award.userId = rollResult[i].userId;
      award.talentRollData = rollResult[i].talentRollData;
      
    }

    userAwardsCount = userAwards.size();
  }

  void toSUserAwards(vector<roll::SUserAward>& rollResult)
  {
    rollResult.clear();
    for(int i = 0; i < userAwards.size(); ++i)
    {
     roll::SUserAward& award = rollResult.push_back();
     award.userId = userAwards[i].userId;
     award.talentRollData = userAwards[i].talentRollData;
    }
  }
};

enum RollTestToolStorageFlags
{
  ROLLTESTTOOLSTORAGEFLAGS_OK = 0,
  ROLLTESTTOOLSTORAGEFLAGS_ERROR = 1,
  ROLLTESTTOOLSTORAGEFLAGS_EMPTY = 2,
  ROLLTESTTOOLSTORAGEFLAGS_DATAERROR = 3
};

class RollTestToolStorage /*:public CObjectBase*/
{
  //OBJECT_BASIC_METHODS(RollTestToolStorage)
public:
  RollTestToolStorage();
  ~RollTestToolStorage(void);

  bool Init(const nstl::string &fileName);
  int GetSize();
  int GetLastFlag();

  void GetRollResultForMap( vector<roll::SUserAward>& prevRollResult, nstl::string mapDesc );
  void AddRollResultForMap( vector<roll::SUserAward>& rollResult, nstl::string mapDesc );

  void Flush();
  bool IsOk();
  bool IsDataError();

  void SaveToFile(const nstl::string &fileName);
  void LoadFromFile(const nstl::string &fileName);

private:
  void FindEntityByMapDescription(RollTestToolStorageEntry* rttsEntry, string mapDesc);

private:
  nstl::string storageFileName;
  vector<RollTestToolStorageEntry> entries;
  RollTestToolStorageFlags lastflag;
};

#endif//_ROLL_STORAGE_H_