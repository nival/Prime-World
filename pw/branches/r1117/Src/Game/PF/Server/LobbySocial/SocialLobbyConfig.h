#ifndef SOCIALLOBBYCONFIG_H_INCLUDED
#define SOCIALLOBBYCONFIG_H_INCLUDED

namespace socialLobby
{

namespace EVerbosity
{
  enum { Silent = 0, Normal = 1, Verbose = 2 };
}


struct SConfig
{
  float     acceptTimeout;
  float     guardLobbyTimeout;
  float     reconnectTimeout;
  float     backupTimeoutShort, backupTimeoutLong;
  int       mmWaitTimeLineLength;
  float     mmWaitTimeFactor;
  float     mmWaitTimeLimit;
  bool      debugInfoOnPing;
  float     partyMembersTimeout;
  float     connectionLostTimeout;
  int       officerLobbyRating;
  int       verbosityLevel;
  float     mmLogicSetupTimeout;
  int       pingScaleThreshold;
  float     pingScaleFactor;
  float     pvxDisconnectTimeout;
  string    clientRevisionsMerge;
  int       maxSpectators;
  string    pinnedLocations;
  string    pinnedLocationsPriority;
  int       pinnedLocationsThreshold;

  SConfig() :
  acceptTimeout( 60.0f ),
  guardLobbyTimeout( 60.0f ),
  reconnectTimeout( 180.0f ),
  backupTimeoutShort( 10.0f ), backupTimeoutLong( 240.0f ),
  mmWaitTimeLineLength( 10 ),
  mmWaitTimeFactor( 0.5f ),
  mmWaitTimeLimit( 600.0f ),
  debugInfoOnPing( true ),
  partyMembersTimeout( 30.0f ),
  connectionLostTimeout( 180.0f ),
  officerLobbyRating( 1600 ),
  verbosityLevel( EVerbosity::Normal ),
  mmLogicSetupTimeout( 30.0f ),
  pingScaleThreshold( 50 ),
  pingScaleFactor( 2.0f ),
  pvxDisconnectTimeout( 60.0f ),
  clientRevisionsMerge( "" ),
  maxSpectators( 2 ),
  pinnedLocationsThreshold( 1 )
  {}
};



class Config : public BaseObjectST, public SConfig
{
  NI_DECLARE_REFCOUNT_CLASS_1( Config, BaseObjectST );

public:
  explicit Config( const SConfig & _cfg ) :
  SConfig( _cfg )
  {}
};



Strong<Config> CreateConfigFromStatics();

} //namespace socialLobby

#endif //SOCIALLOBBYCONFIG_H_INCLUDED
