#pragma once


namespace NCore
{
  namespace ETeam
  {
    enum Enum;
  }
}

namespace NDb
{
  enum EFaction;
  struct HeroesDB;
  struct AdvMapDescription;
}

namespace Game
{


class LoadingFlashInterface;
class LoadingHero;
struct HeroInfo;

NDb::EFaction ConvertToFaction(NCore::ETeam::Enum team);

class LoadingHeroes: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoadingHeroes, BaseObjectST);
public:

  LoadingHeroes(LoadingFlashInterface * _flashInterface,  NDb::Ptr<NDb::HeroesDB> _heroDb);

  void SetOurUserId(int userId, NCore::ETeam::Enum team, NCore::ETeam::Enum manoeuvreTeam);
  void AddUser(int userId, const wstring & playerName, 
    bool isMale, NCore::ETeam::Enum team, NCore::ETeam::Enum manoeuvresTeam, const HeroInfo& heroInfo, string & flagIcon, wstring & flagTooltip);
  void SetPlayerProgress( int userId, float pro );

  void AddBot(int userId);
  void SetMyProgress(float progress );
  void DisconnectUser( int userId );
  void ReconnectUser( int userId );
  void SetShowAllHeroes( bool show = true ) { showAllHeros = show; }
  void SetMapDescription( const NDb::AdvMapDescription* _advMapDescription ) {_advMapDescription = advMapDescription;}

private:
  NDb::Ptr<NDb::HeroesDB>   heroDb;
  NDb::Ptr<NDb::AdvMapDescription>  advMapDescription;
  Weak<LoadingFlashInterface>   flashInterface;
  int ourUserId;

  hash_map<int, Strong<LoadingHero>> loadingHeroes;
  list<int> bots;
  bool showAllHeros;
};


class LoadingHero: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoadingHero, BaseObjectST);
public:
  LoadingHero(LoadingFlashInterface * _flashInterface, int _userId, const wstring & playerName,  
    const char * heroIconPath, NDb::EFaction faction, bool isMale, const char * classIcon, uint partyId, string & flagIcon, wstring & flagTooltip,
    bool isAnimaterAvatar, int leagueIndex);

  void SetProgress(float progress);
  void DisconnectUser();
  void ReconnectUser();
private:
  float cacheProgress;
  bool isLeftGame;
  int userId;  
  uint partyId;
  Weak<LoadingFlashInterface>  flashInterface;
};

}