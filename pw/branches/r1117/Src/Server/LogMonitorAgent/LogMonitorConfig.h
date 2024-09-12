#ifndef LOGMONITORCONFIG_H_INCLUDED
#define LOGMONITORCONFIG_H_INCLUDED

namespace logMonitor
{

struct SConfigData
{
  bool        enabled;
  string      destUrl;
  int         queueLimit;
  int         sendPackSize;
  float       defaultPushPeriod;
  float       maxPushPeriod;

  SConfigData() :
  enabled( false ),
  destUrl( "http://localhost:8080" ),
  queueLimit( 1024 ),
  sendPackSize( 256 ),
  defaultPushPeriod( 0.5f ),
  maxPushPeriod( 60.0f )
  {}
};


class Config : public BaseObjectST, public SConfigData
{
  NI_DECLARE_REFCOUNT_CLASS_1( Config, BaseObjectST );

public:
  explicit Config( const SConfigData & _data ) :
  SConfigData( _data )
  {}
};


Strong<Config> CreateConfigFromStatics();

} //namespace logMonitor

#endif //LOGMONITORCONFIG_H_INCLUDED
