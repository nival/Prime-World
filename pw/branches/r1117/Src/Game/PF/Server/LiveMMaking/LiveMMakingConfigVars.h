#pragma once

namespace mmaking
{

struct SMMConfig
{
  int       logLevel;
  float     testManoeuvresWaitThreshold;
  bool      trainingManoeuvres;
  string    localeTable;
  string    geolocationTable;
  bool      mockMatchmaking;
  int       sleepMs;
  bool      checkRevision;
  int       fullDumpLimit;
  float     fullDumpPeriod;
  float     smartDumpTime;
  int       activeRequestLineLength;
  int       activeGameRequestLineLength;
  bool      debugLogging;
  int       threads;
  bool      manoeuvresEnabled;
  bool      international;
  bool      ignorePings;
  string    donorLocale;
  string    isolatedLocales;
  float     mockMinimumUserWait;
  string    disabledHeroes;
  string    disabledBotSkins;
  int enableRandomQueueIterator;
  bool enablePlayerRatingMM;
  int orderTeamFormation;

  SMMConfig();
};



class MMConfig : public BaseObjectMT, public SMMConfig
{
  NI_DECLARE_REFCOUNT_CLASS_1( MMConfig, BaseObjectMT );

public:
  explicit MMConfig( const SMMConfig & _data ) :
  SMMConfig( _data )
  {}
};


StrongMT<MMConfig> CreateConfigFromStatics();

} //namespace mmaking
