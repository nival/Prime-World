#ifndef MMQUEUEITERATOR_H_INCLUDED
#define MMQUEUEITERATOR_H_INCLUDED

#include "ProdMmLogicBase.h"
#include <ctime>
#include <algorithm>

namespace NDb
{
  struct MMakingScale;
}


namespace mmaking
{
typedef vector<TGeoIndex> TGeoindexVector;

struct GeolocationConstraints
{
  TGeoIndex       sidesLocale[2];
  bool            multipleLocales;
  TGeoIndex       donorSide, recipientSide;
  TGeoIndex       location;

  GeolocationConstraints() :
  multipleLocales( false ),
  donorSide( -1 ), recipientSide( -1 ),
  location( 0 )
  {
    sidesLocale[0] = 0;
    sidesLocale[1] = 0;
  }

  GeolocationConstraints( TGeoIndex _locale1, TGeoIndex _locale2, TGeoIndex _location ) :
  multipleLocales( false ),
  donorSide( -1 ), recipientSide( -1 ),
  location( _location )
  {
    sidesLocale[0] = _locale1;
    sidesLocale[1] = _locale2;
  }
};



struct QueueIteratorCtx
{
  timer::Time   waitTime;
  bool          pingIsGood;

  QueueIteratorCtx() :
  waitTime( 0 ),
  pingIsGood( false )
  {}
};



class QueueIterator : public NonCopyable
{
public:
  enum EFlags
  {
    F_RatingSortMode          = 1,
    F_IgnoreLocaleAndPing     = 2
  };

  QueueIterator( const BaseMMaking::TRequestMap & _requests, int _revision, EBasket::Enum _basket, const TGeoindexVector& _sidesLocale, TGeoIndex _donorLocale, TGeoIndex _geolocation, timer::Time _now, unsigned _flags, const NDb::MapMMakingSettings * _sett, MMConfig * _config, const GeoTable & _locales, bool _isRandomChoise=false ) :
  requests( _requests ),
  revision( _revision ),
  basket( _basket ),
  sidesLocale( _sidesLocale ), donorLocale( _donorLocale ),
  geolocation( _geolocation ),
  now( _now ),
  flags( _flags ),
  settings( _sett ),
  config( _config ),
  locales( _locales ),
  current( requests.begin() ),
  isRandomChoise(_isRandomChoise)
  {
    
    if (isRandomChoise)
    { 
      BaseMMaking::TRequestMap::const_iterator it= requests.begin();
      for (; it!=requests.end(); ++it)
        key_requests.push_back(it->first);
      current_key = key_requests.begin();
      std::srand ( unsigned ( std::time(0) ) );
      std::random_shuffle ( key_requests.begin(), key_requests.end() );
    }
  }

  MmRequest * NextRequest( QueueIteratorCtx & ctx );

private:
  std::vector<mmaking::TRequestUId> key_requests;
  const BaseMMaking::TRequestMap &  requests;
  const int                         revision;
  const EBasket::Enum               basket;
  const TGeoindexVector             sidesLocale;
  const TGeoIndex                   donorLocale;
  TGeoIndex                         geolocation;
  const timer::Time                 now;
  const unsigned                           flags;
  NDb::Ptr<NDb::MapMMakingSettings>        settings;
  StrongMT<MMConfig>                       config;
  const GeoTable &                         locales;
  BaseMMaking::TRequestMap::const_iterator current;
  std::vector<TRequestUId>::const_iterator current_key;
  bool                                     isRandomChoise;

  bool FilterPresampleByLocale( MmRequest * _req, timer::Time _waitTime, timer::Time & _waitTimePenalty, const TGeoIndex& primaryLocale );
  bool FilterPresampleByPing( MmRequest * _req, timer::Time _waitTime, timer::Time & _waitTimePenalty, bool & _pingIsGood );
  MmRequest * NextRandomRequest(QueueIteratorCtx & ctx );
  bool checkRequest(MmRequest* req, QueueIteratorCtx & ctx);
};

} //namespace mmaking

#endif //MMQUEUEITERATOR_H_INCLUDED
