#include "stdafx.h"
#include "MMakingRequest.h"
#include "MMakingLog.h"
#include "Db/DBServer.auto.h"
#include "System/InlineProfiler.h"


namespace mmaking
{

MmRequest::MmRequest( const NDb::MapMMakingSettings * _dbSett, TRequestUId _requestId, timer::Time _startTime, const SRequestCommonData & _commonData ) :
dbSett( _dbSett ),
requestId( _requestId ),
startTime( _startTime ),
commonData( _commonData ),
ladies( 0 ), gentlemen( 0 ),
totGuardRating( 0 ), avgGuardRating( 0 ),
totPlayerRating( 0 ), avgPlayerRating( 0 ), maxPlayerRating(0),
totHeroRating( 0 ), avgHeroRating( 0 ), maxHeroRating( 0 ),
rankIndex( 0 ),
totalForce( 0 ), avgForce( 0 ), maxForce( 0 ),
partyRatingCompensation( 0 ),
loseStreakRatingCompensation( 0 ), loseStreakForceCompensation( 0 ),
totalWins( 0 ),
locale( 0 ),
basket( EBasket::Undefined ),
inUse( false )

{
}



bool MmRequest::Init( const vector<SRequestMember> & _members, IHeroesTable * _heroes, IRankTable * _ranks, const GeoTable & _locales, const GeoTable & _geolocations, Loger * _loger )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_ASSERT( !_members.empty(), "Empty MM-request!" );

  members.reserve( _members.size() );

  locationPings.resize( _geolocations.Size() );

  int newbiesNumber = 0, guardsNumber = 0, leaversNumber = 0;

  for ( int i = 0; i < _members.size(); ++i )
  {
    const SRequestMember & data = _members[i];

    const SHeroDescription * heroDescr = _heroes->FindDescr( data.heroId );
    if ( !heroDescr )
    {
      _loger->Log( ELogLevel::Critical, "Request from user %d declined: unknown hero id '%s'", data.mmId, data.heroId.c_str() );
      return false;
    }

    TGeoIndex shortLocale = _locales.Find( data.geoInfo.locale, _loger );
    if ( !shortLocale && _locales.Size() )
      shortLocale = _locales.BeginIdx();

    if ( data.basket == EBasket::Newbie )
      ++newbiesNumber;
    else if ( data.basket == EBasket::Leaver )
      leaversNumber++;


    SRequestMemberEx dataEx( data, heroDescr->shortId, shortLocale, heroDescr->sex, heroDescr->classEfficiency );

    dataEx.shortLocationPings.resize( _geolocations.Size(), -1 );
    for ( int j = 0; j < data.geoInfo.pings.size(); ++j )
    {
      TGeoIndex locIdx = _geolocations.Find( data.geoInfo.pings[j].clusterId, _loger );
      if ( locIdx >= _geolocations.BeginIdx() && locIdx <= _geolocations.EndIdx() )
      {
        const size_t idx = locIdx - _geolocations.BeginIdx();
        if ( ( dataEx.shortLocationPings[idx] < 0 ) || ( data.geoInfo.pings[j].ping < dataEx.shortLocationPings[idx] ) )
          dataEx.shortLocationPings[idx] = data.geoInfo.pings[j].ping;
      }
    }

    const RankDescription * rankDescr = ( data.basket == EBasket::Newbie ) ? _ranks->FindRankByIndex( 0 ) : _ranks->FindRank( data.heroRating );
    NI_VERIFY( rankDescr, "", return false );

    Add( dataEx, rankDescr->index, _geolocations, _loger );
  }

  if ( leaversNumber > 0 ) 
    basket = EBasket::Leaver;
  else if ( guardsNumber > 0 )
    basket = EBasket::Normal;
  else if ( newbiesNumber == _members.size() ) // NUM_TASK now any non-newbie player leads his team to a non-newbie basket
    basket = EBasket::Newbie;
  else
    basket = EBasket::Normal;

  FinalizePingInfo();

  return true;
}



void MmRequest::Add( const SRequestMemberEx & _data, int _rankIndex, const GeoTable & _geolocations, Loger * _loger )
{
  if ( _data.sex == lobby::ESex::Female )
    ++ladies;
  else if ( _data.sex == lobby::ESex::Male )
    ++gentlemen;

  AddPingInfo( _data, _geolocations, _loger );

  if ( members.empty() )
    locale = _data.shortLocale;
  else
    if ( locale )
      if ( locale != _data.shortLocale )
      {
        if ( _loger )
          _loger->Log( ELogLevel::Critical, "Mixed locales in party request. uid=%d", _data.mmId );
        locale = 0;
      }
  
  members.push_back( _data );

  totGuardRating += _data.guardRating;
  avgGuardRating = totGuardRating / members.size();

  totPlayerRating += _data.playerRating;
  maxPlayerRating = Max( maxPlayerRating, _data.playerRating );
  avgPlayerRating = totPlayerRating / members.size();

  totHeroRating += _data.heroRating;
  maxHeroRating = Max( maxHeroRating, _data.heroRating );
  avgHeroRating = totHeroRating / members.size();

  rankIndex = Max( rankIndex, _rankIndex );

  totalForce += _data.force;
  avgForce = totalForce / members.size();
  maxForce = Max((int)_data.force, maxForce);

  totalClassEfficiency.Add( _data.heroClassEff );

  partyRatingCompensation = PartyRatingCompensation( dbSett, members.size() );

  loseStreakRatingCompensation += LoseStreakRatingCompensation( dbSett, _data.loseStreak );
  loseStreakForceCompensation += LoseStreakForceCompensation( dbSett, _data.loseStreak );

  totalWins = Max( totalWins, _data.totalWins );
}



void MmRequest::AddPingInfo( const SRequestMemberEx & _data, const GeoTable & _geolocations, Loger * _loger )
{
  NI_VERIFY( locationPings.size() == _data.shortLocationPings.size(), "", return );
  int minPing = 0, maxPing = 0;
  bool first = true;
  for ( int i = 0; i < _data.shortLocationPings.size(); ++i )
  {
    int ping = _data.shortLocationPings[i];
    if ( ping < 0 ) {
      const char * locId = _geolocations.Find( _geolocations.BeginIdx() + i );
      _loger->Log( ELogLevel::Critical, "Unknown ping to location '%s'! userid=%d, requestid=%d", locId, _data.mmId, requestId );
      continue;
    }
    minPing = first ? ping : Min( minPing, ping );
    maxPing = first ? ping : Max( maxPing, ping );
    first = false;
  }

  for ( int i = 0; i < _data.shortLocationPings.size(); ++i )
  {
    int ping = _data.shortLocationPings[i];
    LocationPingInfo & pings = locationPings[i];
    float q = ( ping < 0 ) ? 1.0f : CalculateRelativePingQuality( ping, minPing, maxPing );
    ++pings.count;
    pings.sumQuality += q;
    pings.avgQuality = pings.sumQuality / pings.count;
  }
}



void MmRequest::FinalizePingInfo()
{
  float minAvg = 0;
  for ( int i = 0; i < locationPings.size(); ++i )
  {
    LocationPingInfo & info = locationPings[i];
    if ( !i || ( info.avgQuality < minAvg ) )
      minAvg = info.avgQuality;
  }

  for ( int i = 0; i < locationPings.size(); ++i )
  {
    LocationPingInfo & info = locationPings[i];
    info.avgQuality -= minAvg;
  }
}



float MmRequest::CalculateRelativePingQuality( int ping, int minPing, int maxPing )
{
  return CalculateRelativePingQuality( ping, minPing, maxPing, dbSett->locationPingSettings.nicePingThreshold, dbSett->locationPingSettings.pingScaleMinFactor );
}



float MmRequest::CalculateRelativePingQuality( int ping, int minPing, int maxPing, int threshold, float minScaleFactor )
{
  int scaleMin = Max( minPing, threshold );
  int scaleMax = Max( maxPing, (int)( scaleMin * minScaleFactor ) );

  float q = ( ping - scaleMin ) / (float)( scaleMax - scaleMin );
  return Max( q, 0.0f );
}



int MmRequest::CountHeroesOfType( THeroShortId _heroId ) const
{
  int count = 0;
  for ( int i = 0; i < members.size(); ++i )
    if ( members[i].shortHeroId == _heroId )
      ++count;
  return count;
}



int MmRequest::EffectiveRating( const NDb::MapMMakingSettings * _clampSettings ) const
{
  const int r = maxHeroRating + loseStreakRatingCompensation / members.size();

  if ( _clampSettings )
    return Clamp( r, _clampSettings->ratingScale.low, _clampSettings->ratingScale.high );
  else
    return r;
}



int MmRequest::EffectiveForce( const NDb::MapMMakingSettings * _clampSettings ) const
{
  if ( _clampSettings )
    return Clamp( avgForce, _clampSettings->forceScale.low, _clampSettings->forceScale.high );
  else
    return avgForce;
}



string MmRequest::FormatAllMmIds() const
{
  string tmp;
  for ( int i = 0; i < members.size(); ++i )
  {
    if ( i )
      tmp += ", ";
    tmp += NI_STRFMT( "%d", members[i].mmId );
  }
  return tmp;
}



string MmRequest::FormatAll() const
{
  string tmp;
  tmp.reserve( 256 );
  tmp = NI_STRFMT( "Team %s, rev %d, basket %s, pings (", lobby::ETeam::ToString( commonData.team ), commonData.clientRevision, EBasket::ToString( basket ) );

  for ( int i = 0; i < locationPings.size(); ++i )
    tmp += NI_STRFMT( "%s%.2f", i ? ", " : "", locationPings[i].avgQuality );
  tmp += ") ";

  for ( int i = 0; i < members.size(); ++i )
  {
    if ( i )
      tmp += ", ";
    const SRequestMemberEx & memb = members[i];
    tmp += NI_STRFMT( "(mmId %d, sex '%s', hero '%s' (%d), basket %s, ", memb.mmId, lobby::ESex::ToString( memb.sex ), memb.heroId, memb.shortHeroId, EBasket::ToString( memb.basket ) );
    tmp += NI_STRFMT( "grating %d, prating %d, hrating %d, force %.2f, loses %d, wins %d, fame %d, loc %s, ping %s)", memb.guardRating, memb.playerRating, memb.heroRating, memb.force, memb.loseStreak, memb.totalWins, memb.fameLevel, memb.geoInfo.locale, memb.geoInfo.FmtPings() );
  }

  return tmp;
}



string MmRequest::FormatAllJson() const
{
  string tmp;
  tmp.reserve( 2048 );
  tmp = NI_STRFMT( "\"team\": %d, \"rev\": %d, \"basket\": %d, \"members\": [ ", (int)commonData.team, commonData.clientRevision, (int)basket );
  for ( int i = 0; i < members.size(); ++i )
  {
    if ( i )
      tmp += ", ";
    const SRequestMemberEx & memb = members[i];
    tmp += NI_STRFMT( "{ \"mmId\": %d, \"sex\": %d, \"heroId\": \"%s\", \"shortHeroId\": %d, \"basket\": %d, ", 
                                        memb.mmId, (int)memb.sex, memb.heroId, memb.shortHeroId, (int)memb.basket );
    tmp += NI_STRFMT( "\"grating\": %d, \"prating\": %d, \"hrating\": %d, \"force\": %.2f, \"loses\": %d, \"wins\": %d, \"fame\": %d, ", 
            memb.guardRating, memb.playerRating, memb.heroRating, memb.force, memb.loseStreak, memb.totalWins, memb.fameLevel );

    tmp += NI_STRFMT( "\"loc\": \"%s\", \"pings\":", memb.geoInfo.locale );
    FormatPingsIntoJson( tmp, memb.geoInfo );

    tmp += " }";
  }
  tmp += " ]";
  return tmp;
}



void MmRequest::FormatPingsIntoJson( string & _buffer, const SGeoInfo & _info )
{
  _buffer += "[";
  for ( int k = 0; k < _info.pings.size(); ++k )
    _buffer += NI_STRFMT( "%s{\"%s\":%d}", k ? "," : "" ,_info.pings[k].clusterId, _info.pings[k].ping );
  _buffer += "]";
}



int MmRequest::PartyRatingCompensation( const NDb::MapMMakingSettings * dbMapSett, int partySize )
{
  if ( dbMapSett->partySkillCompensation.empty() )
    return 0;

  int index = Clamp( partySize - 1, 0, (int)dbMapSett->partySkillCompensation.size() - 1 );
  return dbMapSett->partySkillCompensation[index];
}



int MmRequest::LoseStreakRatingCompensation( const NDb::MapMMakingSettings * dbSett, int loseStreak )
{
  const int minStreak = dbSett->loseStreakCorrection.minStreak;
  if ( loseStreak < minStreak )
    return 0;

  return -(int)( 0.5f + dbSett->loseStreakCorrection.ratingPenalty * ( loseStreak - minStreak + 1 ) );
}



int MmRequest::LoseStreakForceCompensation( const NDb::MapMMakingSettings * dbSett, int loseStreak )
{
  const int minStreak = dbSett->loseStreakCorrection.minStreak;
  if ( loseStreak < minStreak )
    return 0;

  return -(int)( 0.5f + dbSett->loseStreakCorrection.forcePenalty * ( loseStreak - minStreak + 1 ) );
}






GeoTable::GeoTable( const string & _spaceSeparatedList, const string &  _donorId, const string & _isolatedList )
{
  string donorId( _donorId );
  NStr::ToLower( &donorId );

  vector<string> list;
  NStr::SplitString( _spaceSeparatedList, &list, ' ' );

  vector<string> isolatedList0;
  NStr::SplitString( _isolatedList, &isolatedList0, ' ' );
  set<string> isolatedList;
  for ( int i = 0; i < isolatedList0.size(); ++i ) {
    string item = isolatedList0[i];
    NStr::TrimBoth( item );
    NStr::ToLower( &item );
    isolatedList.insert( item );
  }

  dict.resize( list.size() );
  for ( int i = 0; i < list.size(); ++i ) {
    string zone = list[i];
    NStr::TrimBoth( zone );
    NStr::ToLower( &zone );
    dict[i].idx = i + 1;
    dict[i].id = zone;
    if ( zone == donorId )
      dict[i].donor = true;
    if ( isolatedList.find( zone ) != isolatedList.end() )
      dict[i].isolated = true;
  }
}



bool GeoTable::LocationsIdEqual( const char * _one, const char * _another )
{
  for ( const char *o = _one, *a = _another; ; ++o, ++a )
  {
    const bool fin_o = ( *o == '_' ) || isdigit( *o ) || !*o;
    const bool fin_a = ( *a == '_' ) || isdigit( *a ) || !*a;

    if ( fin_o && fin_a )
      return true;

    if ( !fin_o && !fin_a )
    {
      if ( *o != *a )
        return false;
      continue;
    }
    return false;
  }
}



TGeoIndex GeoTable::Find( const string & zone, Loger * loger ) const
{
  if ( zone.empty() )
    return 0;

  for ( size_t i = 0; i < dict.size(); ++i )
    if ( LocationsIdEqual( dict[i].id.c_str(), zone.c_str() ) )
      return dict[i].idx;

  if ( loger )
    loger->Log( ELogLevel::Critical, "Geo zone '%s' is unknown", zone.c_str() );
  return 0;
}



const char * GeoTable::Find( TGeoIndex index, Loger * loger ) const
{
  if ( index < 1 || index > (int)dict.size() ) {
    if ( loger )
      loger->Log( ELogLevel::Critical, "Geo zone %d is unknown", index );
    return "";
  }

  return dict[index - 1].id.c_str();
}



bool GeoTable::IsDonor( TGeoIndex index, Loger * loger ) const
{
  if ( index < 1 || index > (int)dict.size() ) {
    if ( loger )
      loger->Log( ELogLevel::Critical, "Geo zone %d is unknown", index );
    return false;
  }

  return dict[index - 1].donor;
}



bool GeoTable::Isolated( TGeoIndex index, Loger * loger ) const
{
  if ( index < 1 || index > (int)dict.size() ) {
    if ( loger )
      loger->Log( ELogLevel::Critical, "Geo zone %d is unknown", index );
    return false;
  }

  return dict[index - 1].isolated;
}

} //namespace mmaking
