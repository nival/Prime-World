#ifndef MMAKINGREQUEST_H_INCLUDED
#define MMAKINGREQUEST_H_INCLUDED

#include "LiveMMakingTypes.h"
#include "IMMakingLogic.h"
#include <vector>

namespace NDb
{
  struct MapMMakingSettings;
}


namespace mmaking
{

class Loger;

typedef int TGeoIndex;

class GeoTable
{
public:
  GeoTable( const string & _spaceSeparatedList, const string & _donorId, const string & _isolatedList );

  static bool LocationsIdEqual( const char * _one, const char * _another );

  TGeoIndex Find( const string & zone, Loger * loger = 0 ) const;
  const char * Find( TGeoIndex index, Loger * loger = 0 ) const;
  bool IsDonor( TGeoIndex index, Loger * loger = 0 ) const;
  bool Isolated( TGeoIndex index, Loger * loger = 0 ) const;
  TGeoIndex BeginIdx() const { return 1; }
  TGeoIndex EndIdx() const { return dict.size() + 1; }
  size_t Size() const { return dict.size(); }

private:
  struct Slot {
    TGeoIndex idx;
    string    id;
    bool      donor;
    bool      isolated;
    Slot() : idx( 0 ), donor( false ), isolated( false ) {}
  };

  std::vector<Slot> dict;
};



struct SRequestMemberEx : public SRequestMember
{
  THeroShortId  shortHeroId;
  TGeoIndex     shortLocale;
  vector<int>   shortLocationPings;
  lobby::ESex::Enum heroSex;
  SHeroClassEfficiency heroClassEff;

  SRequestMemberEx() : shortHeroId( 0 ), shortLocale( 0 ), heroSex( lobby::ESex::Undefined ) {}
  SRequestMemberEx( const SRequestMember & _req ) : SRequestMember( _req ), shortHeroId( 0 ), heroSex( lobby::ESex::Undefined ) {}
  SRequestMemberEx( const SRequestMember & _req, THeroShortId _shortHeroId, TGeoIndex _shortLocale, lobby::ESex::Enum _heroSex, const SHeroClassEfficiency & _heroClassEff ) :
  SRequestMember( _req ), shortHeroId( _shortHeroId ), shortLocale( _shortLocale ), heroSex( _heroSex ), heroClassEff( _heroClassEff ) {}
};



struct LocationPingInfo
{
  int               minPing, maxPing;
  int               count;
  float             sumQuality, avgQuality; // 0 is ze best, 100 - worst

  LocationPingInfo() :
  minPing( 0 ), maxPing( 0 ),
  count( 0 ),
  sumQuality( 0.0f ), avgQuality( 0.0f )
  {}
};



class MmRequest : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( MmRequest, BaseObjectMT )

public:
  MmRequest( const NDb::MapMMakingSettings * _dbSett, TRequestUId _requestId, timer::Time _startTime, const SRequestCommonData & _commonData );

  bool Init( const vector<SRequestMember> & _members, IHeroesTable * _heroes, IRankTable * _ranks, const GeoTable & _locales, const GeoTable & _geolocations, Loger * _loger );

  TRequestUId RequestId() const { return requestId; }

  void SetStartTime( timer::Time t ) { startTime = t; }
  timer::Time StartTime() const { return startTime; }

  const SRequestCommonData & CommonData() const { return commonData; }

  int Size() const { return members.size(); }
  const SRequestMemberEx & Member( int _index ) const { return members[_index]; }
  SRequestMemberEx & Member( int _index ) { return members[_index]; }

  int CountHeroesOfType( THeroShortId _heroId ) const;
  int Ladies() const { return ladies; }
  int Gentlemen() const { return gentlemen; }
  int AvgGuardRating() const { return avgGuardRating; }
  int AvgPlayerRating() const { return avgPlayerRating; }
  int AvgHeroRating() const { return avgHeroRating; }
  int MaxHeroRating() const { return maxHeroRating; }
  int MaxPlayerRating() const { return maxPlayerRating; }
  int MaxHeroForce() const { return maxForce; }
  int EffectiveRating( const NDb::MapMMakingSettings * _clampSettings ) const;
  int EffectiveForce( const NDb::MapMMakingSettings * _clampSettings ) const;
  int RankIndex() const { return rankIndex; }
  const SHeroClassEfficiency & TotalClassEfficiency() const { return totalClassEfficiency; }
  //int PartyRatingCompensation() const {  return partyRatingCompensation; }
  int LoseStreakRatingCompensation() const { return loseStreakRatingCompensation; }
  //int LoseStreakForceCompensation() const { return loseStreakForceCompensation; }
  TGeoIndex Locale() const { return locale; }
  const LocationPingInfo * LocationPing( TGeoIndex index ) const { NI_VERIFY( index >= 1 && index <= locationPings.size(), "", return 0 ); return &locationPings[index - 1]; }
  EBasket::Enum Basket() const { return basket; }
  int TotalWins() const { return totalWins; }

  string FormatAllMmIds() const;
  string FormatAll() const;
  string FormatAllJson() const;

  static void FormatPingsIntoJson( string & _buffer, const SGeoInfo & _info );

  bool InUse() const { return inUse; }
  void Use( bool use ) { inUse = use; }

  float CalculateRelativePingQuality( int ping, int minPing, int maxPing );
  static float CalculateRelativePingQuality( int ping, int minPing, int maxPing, int threshold, float minScaleFactor );
  static int LoseStreakRatingCompensation( const NDb::MapMMakingSettings * dbSett, int loseStreak );
private:
  //Unused now:
  static int PartyRatingCompensation( const NDb::MapMMakingSettings * dbSett, int partySize );
  static int LoseStreakForceCompensation( const NDb::MapMMakingSettings * dbSett, int loseStreak );

private:
  NDb::Ptr<NDb::MapMMakingSettings> dbSett;
  const TRequestUId   requestId;
  timer::Time         startTime;
  SRequestCommonData  commonData;
  vector<SRequestMemberEx> members;
  int                 ladies, gentlemen;
  int                 totGuardRating, avgGuardRating;
  int                 totPlayerRating, avgPlayerRating, maxPlayerRating;
  int                 totHeroRating, avgHeroRating, maxHeroRating;
  int                 rankIndex;
  int                 totalForce, avgForce, maxForce;
  SHeroClassEfficiency totalClassEfficiency;
  int                 partyRatingCompensation;
  int                 loseStreakRatingCompensation, loseStreakForceCompensation;
  int                 totalWins;
  TGeoIndex           locale;
  vector<LocationPingInfo> locationPings;
  EBasket::Enum       basket;
  bool                guardOnly;

  bool                inUse;

  void Add( const SRequestMemberEx & _data, int _rankIndex, const GeoTable & _geolocations, Loger * _loger );
  void AddPingInfo( const SRequestMemberEx & _data, const GeoTable & _geolocations, Loger * _loger );
  void FinalizePingInfo();
};

} //namespace mmaking

#endif //MMAKINGREQUEST_H_INCLUDED
