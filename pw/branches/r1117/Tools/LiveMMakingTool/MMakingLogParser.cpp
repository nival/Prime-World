#include "stdafx.h"
#include "MMakingLogParser.h"
#include "Db/DBServer.auto.h"
#include <io.h>
#include "System/InlineProfiler.h"

namespace mm_test
{


LogParser::LogParser( ILogParserCb * cb, ELogVersion::Enum logVersion ) :
_cb( cb ), _logVersion( logVersion )
{
}


void LogParser::AddFile( const char * name )
{
  string text;
  ReadFile( text, name );
  AddText( text.c_str(), name );
}



void LogParser::AddText( const char * text, const char * filename )
{
  try {
    Ctx ctx( text );
    ParseFile( ctx );
  }
  catch( const Excep & ex ) {
    Excep newex( ex );
    newex.SetFile( filename );
    throw newex;
  }
}



void LogParser::ReadFile( string & text, const char * name )
{
  NI_PROFILE_FUNCTION_MEM;

  FILE * f = fopen( name, "rb" );
  if ( !f )
    throw ExcepFile( "Could not open file", name );

  size_t sz = _filelength( _fileno( f ) );
  if ( !sz ) {
    fclose( f );
    throw ExcepFile( "File is empty", name );
  }

  text.resize( sz + 1, 0 );
  int n = fread( (char *)text.c_str(), 1, sz, f );
  if ( n != (int)sz ) {
    fclose( f );
    throw ExcepFile( "Could not read file", name );
  }
  fclose( f );
}



void LogParser::ParseFile( Ctx & ctx )
{
  SkipUtcMarker( ctx );

  while ( true )
  {
    //NI_PROFILE_BLOCK( "Iteration" );

    size_t offs = ctx.ptr - ctx.text.c_str();
    _cb->OnProgress( ( 100ull * (unsigned long long)offs ) / (unsigned long long)ctx.text.size());

    //HACK: To speed up sscanf we have to limit input string length
    const size_t Limit = 4096;
    size_t symbolsLeft = ctx.text.length() - offs;
    size_t hackedSymbolOffs = 0;
    char hackedSymbolBackup = 0;
    if ( symbolsLeft > Limit ) {
      hackedSymbolOffs = offs + Limit;
      hackedSymbolBackup = ctx.text.c_str()[hackedSymbolOffs];
      const_cast<char*>(ctx.text.c_str())[hackedSymbolOffs] = 0;
    }

    if ( !*ctx.ptr )
      break;

    Timestamp ts;
    GetTimestamp( ctx, ts );

    string words;
    GetKeywords( ctx, words );

    if (
      !stricmp( words.c_str(), "Matchmaking thread started" ) ||
      !stricmp( words.c_str(), "Request added" ) ||
      !stricmp( words.c_str(), "Line statistics" ) ||
      !stricmp( words.c_str(), "Line statistics brief" ) ||
      !stricmp( words.c_str(), "Line statistics aux" ) ||
      !stricmp( words.c_str(), "Dumping request" ) ||
      !stricmp( words.c_str(), "Dumping request " ) ||
      !stricmp( words.c_str(), "Attention" ) ||
      !stricmp( words.c_str(), "Unknown request to remove" ) ||
      !stricmp( words.c_str(), "Full Dump" ) ||
      !stricmp( words.c_str(), "Game details" ) ||
      !stricmp( words.c_str(), "Map id" ) ||
      !stricmp( words.c_str(), "Team size" ) ||
      !stricmp( words.c_str(), "Geo zone " ) ) {
      SkipToTheEol( ctx );
    }
    else if ( !stricmp( words.c_str(), "Request queued" ) ) {
      GetRequest( ctx, ts );
    }
    else if ( !stricmp( words.c_str(), "Request removed" ) ) {
      GetRequestRemoval( ctx, ts );
    }
    else if ( !stricmp( words.c_str(), "Pushing game" ) || !stricmp( words.c_str(), "Game popped" ) ) {
      GetGame( ctx, ts );
    }
    else
      throw ExcepText( ctx.ptr, NI_STRFMT( "Unknown keywords '%s'", words ) );

    if ( hackedSymbolOffs )
      const_cast<char*>(ctx.text.c_str())[hackedSymbolOffs] = hackedSymbolBackup;
  }
}



bool LogParser::GetToTheEol( Ctx & ctx, string & line )
{
  NI_PROFILE_FUNCTION;

  size_t off = strcspn( ctx.ptr, "\r\n" );
  const char * end = ctx.ptr + off;

  if ( !*end && !off )
    return false;

  line.resize( off );
  copy( ctx.ptr, end, line.begin() );

  ctx.Advance( off );

  if ( ctx.ptr[0] == '\r' && ctx.ptr[1] == '\n' )
    ++ctx.ptr;
  if ( ctx.ptr[0] == '\n' )
    ++ctx.ptr;

  return true;
}



void LogParser::SkipUtcMarker( Ctx & ctx )
{
  if ( _logVersion < ELogVersion::v923 )
    return;

  int endOffset = 0;
  int h = 0, m = 0;
  int scanRes = sscanf( ctx.ptr, "Local time: %d:%u UTC%n", &h, &m, &endOffset );

  if ( ( scanRes != 2 ) || !endOffset )
    throw ExcepText( ctx.ptr, "UTC time marker expected" );
  
  ctx.Advance( endOffset );

  DebugTrace( "UTC time marker parsed: %d:%d", h, m );
}



void LogParser::GetTimestamp( Ctx & ctx, Timestamp & ts )
{
  NI_PROFILE_FUNCTION;

  int endOffset = 0;
  Timestamp t;
  t.date.year = 2012;
  int ss = 0;

  int scanRes = 0;
  if ( _logVersion < ELogVersion::v903 )
  {
    scanRes = sscanf( ctx.ptr, "%d/%d %d:%d:%d.%d %n", &t.date.day, &t.date.mon, &t.time.hour, &t.time.minute, &t.time.sec, &ss, &endOffset );
    if ( ( scanRes != 6 ) || !endOffset )
      throw ExcepText( ctx.ptr, "Timestamp expected" );
  }
  else //9.0.3
  {
    double simTime = 0;
    scanRes = sscanf( ctx.ptr, "%d/%d %d:%d:%d.%d %f %n", &t.date.day, &t.date.mon, &t.time.hour, &t.time.minute, &t.time.sec, &ss, &simTime, &endOffset );
    if ( ( scanRes != 7 ) || !endOffset )
      throw ExcepText( ctx.ptr, "Timestamp expected" );
  }


  if ( !t.IsValid() )
    throw ExcepText( ctx.ptr, "Invalid timestamp" );

  ts = t;
  ts.time.ms = ss * 10;

  ctx.Advance( endOffset );
}



void LogParser::GetKeywords( Ctx & ctx, string & words )
{
  NI_PROFILE_FUNCTION;

  int endOffset = 0;
  char buf[256] = "";
  int scanRes = sscanf( ctx.ptr, "%255[a-zA-Z ] %n", buf, &endOffset );
  if ( ( scanRes != 1 ) || !endOffset )
    throw ExcepText( ctx.ptr, "Keywords expected" );

  words = buf;

  ctx.Advance( endOffset );
}



inline mmaking::EBasket::Enum ParseBasket( const char * s )
{
  if ( !stricmp( s, "Newbie" ) )
    return mmaking::EBasket::Newbie;
  if ( !stricmp( s, "Normal" ) )
    return mmaking::EBasket::Normal;
  if ( !stricmp( s, "Leaver" ) )
    return mmaking::EBasket::Leaver;

  return mmaking::EBasket::Undefined;
}



void LogParser::GetRequest( Ctx & ctx, const Timestamp & ts )
{
  //NI_PROFILE_FUNCTION;

  int endOffset = 0;
  int reqId = 0, team = 0, rev = 0;
  float wait = 0;
  mmaking::EBasket::Enum basket = mmaking::EBasket::Undefined; //unused for now
  bool manvrs = false;

  bool ok = false;
  switch ( _logVersion )
  {
    default:
      throw ExcepText( ctx.ptr, "Not supported yet" );
      break;

    case ELogVersion::trunk:
    case ELogVersion::v82x:
    case ELogVersion::v902:
    case ELogVersion::v903:
    case ELogVersion::v911:
      if ( 4 == sscanf( ctx.ptr, ": id %d ( wait %f ), Team Team%d, rev %d, %n", &reqId, &wait, &team, &rev, &endOffset ) )
        if ( endOffset )
          ok = true;
      break;

    case ELogVersion::v914:
    case ELogVersion::v923:
    {
      char manvrsTxt[8] = "";
      if ( 5 == sscanf( ctx.ptr, ": id %d ( wait %f ), Team Team%d, rev %d, manvrs %7s %n", &reqId, &wait, &team, &rev, manvrsTxt, &endOffset ) )
        if ( endOffset )
          if ( !stricmp( manvrsTxt, "yes" ) || !stricmp( manvrsTxt, "no" ) )
            ok = true;
      manvrs = !stricmp( manvrsTxt, "yes" );
      break;
    }

    case ELogVersion::v932:
    case ELogVersion::v940:
    case ELogVersion::v941:
    case ELogVersion::v942:
    {
      char manvrsTxt[8] = "", basketTxt[16] = "";
      if ( 6 == sscanf( ctx.ptr, ": id %d ( wait %f ), Team Team%d, rev %d, manvrs %7[a-zA-Z], basket %15[a-zA-Z] %n", &reqId, &wait, &team, &rev, manvrsTxt, basketTxt, &endOffset ) )
        if ( endOffset )
          if ( !stricmp( manvrsTxt, "yes" ) || !stricmp( manvrsTxt, "no" ) )
            if ( ParseBasket( basketTxt ) != mmaking::EBasket::Undefined )
              ok = true;
      manvrs = !stricmp( manvrsTxt, "yes" );
      basket = ParseBasket( basketTxt );
      break;
    }
  }

  if ( !ok )
    throw ExcepText( ctx.ptr, "Request data expected" );
  ctx.Advance( endOffset );

  mmaking::SRequestCommonData cmn;
  cmn.clientRevision = rev;
  if ( team == 1 )
    cmn.team = lobby::ETeam::Team1;
  else if ( team == 2 )
    cmn.team = lobby::ETeam::Team2;
  else
    throw ExcepText( ctx.ptr, "Wrong team index" );

  vector<mmaking::SRequestMember> memebers;
  while ( true )
    if ( !GetRequestMemeber( ctx, memebers ) )
      break;

  if ( !memebers.size() )
    throw ExcepText( ctx.ptr, "No request members" );

  _cb->OnAddRequest( ts, (mmaking::TRequestUId)reqId, cmn, memebers, wait );
}



lobby::ESex::Enum LogParser::StringToSex( Ctx & ctx, const char * s )
{
  if ( !stricmp( s, "male" ) )
    return lobby::ESex::Male;
  else if ( !stricmp( s, "female" ) )
    return lobby::ESex::Female;
  else
    throw ExcepText( ctx.ptr, NI_STRFMT( "Wrong sex id '%s'", s ) );
}



inline void FakePingsByLocation( mmaking::SGeoInfo & geoInfo, const char * locale, const char * location, ELogVersion::Enum ver )
{
  geoInfo.locale = locale;

  if ( ver >= ELogVersion::v941 )
    geoInfo.pings.push_back( mmaking::SLocationPing( location, 50 ) );
  else
    geoInfo.pings.push_back( mmaking::SLocationPing( locale, 50 ) );
}



bool LogParser::GetRequestMemeber( Ctx & ctx, vector<mmaking::SRequestMember> & memebers )
{
  NI_PROFILE_FUNCTION;

  int endOffset = 0;
  sscanf( ctx.ptr, " ( %n", &endOffset );
  if ( !endOffset )
    return false;

  int mmId = 0, heroId = 0, rating = 0, playerRating = 0, guardRating = 0;
  float force = 0;
  char sex[16]="", hero[64]="", loc[16]="", geo[16]="", basket[16]="";
  int loses=0, wins=0, fame=0;
  endOffset = 0;
  bool ok = false;
  if ( _logVersion == ELogVersion::v82x )
  {
    if ( 5 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), rating %d) %n", &mmId, sex, hero, &heroId, &rating, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v902 ) {
    if ( 6 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), rating %d, loc '%15[a-zA-Z]') %n", &mmId, sex, hero, &heroId, &rating, loc, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( ( _logVersion == ELogVersion::v903 ) || ( _logVersion == ELogVersion::v911 ) || ( _logVersion == ELogVersion::v914 ) ) {
    if ( 7 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), rating %d, force %f, loc '%15[a-zA-Z]') %n", &mmId, sex, hero, &heroId, &rating, &force, loc, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v923 ) {
    if ( 8 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), rating %d, force %f, loc '%15[a-zA-Z]', loses %d) %n", &mmId, sex, hero, &heroId, &rating, &force, loc, &loses, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v932 ) {
    if ( 12 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), basket %15[a-zA-Z], hrating %d, prating %d, force %f, loc '%15[a-zA-Z]', loses %d, wins %d, fame %d) %n", &mmId, sex, hero, &heroId, basket, &rating, &playerRating, &force, loc, &loses, &wins, &fame, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v940 ) {
    if ( 13 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), basket %15[a-zA-Z], grating %d, prating %d, hrating %d, force %f, loc '%15[a-zA-Z]', loses %d, wins %d, fame %d) %n", &mmId, sex, hero, &heroId, basket, &guardRating, &playerRating, &rating, &force, loc, &loses, &wins, &fame, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v941 || _logVersion == ELogVersion::v942 ) {
    if ( 14 == sscanf( ctx.ptr, " ( mmId %d, sex '%15[a-zA-Z]', hero '%63[a-zA-Z]' (%d), basket %15[a-zA-Z], grating %d, prating %d, hrating %d, force %f, loses %d, wins %d, fame %d, loc '%15[a-zA-Z0-9]/%15[a-zA-Z0-9]') %n", &mmId, sex, hero, &heroId, basket, &guardRating, &playerRating, &rating, &force, &loses, &wins, &fame, loc, geo, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::trunk ) {
    NI_ALWAYS_ASSERT( "Not impemented" );
  }
  if( !ok )
    throw ExcepText( ctx.ptr, "Request member data expected" );
  ctx.Advance( endOffset );

  mmaking::SRequestMember m;
  m.mmId = mmId;
  m.sex = StringToSex( ctx, sex );
  m.heroId = hero;

  if ( _logVersion <= ELogVersion::v903 )
    m.playerRating = rating;
  else if ( _logVersion < ELogVersion::v932 )
    m.playerRating = (int)( rating - force * 6.0 ); //magic
  else if ( _logVersion == ELogVersion::v932 )
    m.playerRating = rating;
  else
    m.playerRating = playerRating;

  m.heroRating = rating;

  m.guardRating = rating;

  if ( _logVersion == ELogVersion::v940 || _logVersion == ELogVersion::v941 || _logVersion == ELogVersion::v942 ) {
    m.playerRating = playerRating;
    m.heroRating = rating;
    m.guardRating = guardRating;
  }

  m.force = force;
  FakePingsByLocation( m.geoInfo, loc, geo, _logVersion );
  m.loseStreak = loses;
  m.totalWins = wins;
  m.fameLevel = fame;

  if ( basket[0] )
    m.basket = ParseBasket( basket ); //Это будет иметь смысл только для логов с версии 9.4.0

  if ( _logVersion <= ELogVersion::v932 )
    m.basket = DetermineMemberBasket( m );

  if ( *ctx.ptr == ',' )
    ++ctx.ptr;

  memebers.push_back( m );
  return true;
}



void LogParser::GetRequestRemoval( Ctx & ctx, const Timestamp & ts )
{
  //NI_PROFILE_FUNCTION;

  int endOffset = 0;
  int reqId = 0;
  int scanRes = sscanf( ctx.ptr, ": %d %n", &reqId, &endOffset );
  if ( ( scanRes != 1 ) || !endOffset )
    throw ExcepText( ctx.ptr, "Request removal data expected" );
  ctx.Advance( endOffset );

  _cb->OnRemoveRequest( ts, (mmaking::TRequestUId)reqId );
}



void LogParser::GetGame( Ctx & ctx, const Timestamp & ts )
{
  //NI_PROFILE_FUNCTION;

  int endOffset = 0;
  char type[32] = "", map[256] = "", basket[16] = "";
  int r1=0, ra1=0, r2=0, ra2=0;
  int f1=0, f2=0;

  bool ok = false;

  if ( _logVersion == ELogVersion::v82x ) {
    if ( !ok )
      if ( 4 == sscanf( ctx.ptr, ": Type %31[a-zA-Z], map '%255[^']' Team1: Rating %d | Team2: Rating %d %n", type, map, &r1, &r2, &endOffset ) )
        if ( endOffset )
          ok = true;
  }
  else if ( ( _logVersion == ELogVersion::v902 ) || ( _logVersion == ELogVersion::v903 ) ) {
    if ( 6 == sscanf( ctx.ptr, ": Type %31[a-zA-Z], map '%255[^']' Team1: Rating %d (-%d) | Team2: Rating %d (-%d) %n", type, map, &r1, &ra1, &r2, &ra2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( ( _logVersion == ELogVersion::v911 ) || ( _logVersion == ELogVersion::v914 ) ) {
    if ( 6 == sscanf( ctx.ptr, 
          ": Type %31[a-zA-Z], map '%255[^']' "
          "Team1: Rating %d, Force %d | Team2: Rating %d, Force %d "
          "UserId ReqId Sex Hero Rating Force Loc Wait | UserId ReqId Sex Hero Rating Force Loc Wait %n",
          type, map, &r1, &f1, &r2, &f2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v923 ) {
    if ( 6 == sscanf( ctx.ptr, 
          ": Type %31[a-zA-Z], map '%255[^']' "
          "Team1: Rating %d, Force %d | Team2: Rating %d, Force %d "
          "UserId ReqId Sex Hero Rating Force Loc Wait Loses | UserId ReqId Sex Hero Rating Force Loc Wait Loses %n",
          type, map, &r1, &f1, &r2, &f2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v932 ) {
    if ( 7 == sscanf( ctx.ptr, 
          ": Type %31[a-zA-Z], map '%255[^']', basket %15[a-zA-Z] "
          "Team1: Rating %d, Force %d | Team2: Rating %d, Force %d "
          "UserId ReqId Sex Hero Basket HRating PRating Force Loc Wait Loses Wins Fame | UserId ReqId Sex Hero Basket HRating PRating Force Loc Wait Loses Wins Fame %n",
          type, map, basket, &r1, &f1, &r2, &f2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v940 ) {
    if ( 5 == sscanf( ctx.ptr, 
          ": Type %31[a-zA-Z], map '%255[^']', basket %15[a-zA-Z] "
          "Team1: Force %d | Team2: Force %d "
          "UserId ReqId Sex Hero Basket GRating PRating HRating Force Loc Wait Loses Wins Fame | UserId ReqId Sex Hero Basket GRating PRating HRating Force Loc Wait Loses Wins Fame %n",
          type, map, basket, &f1, &f2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::v941 || _logVersion == ELogVersion::v942 ) {
    if ( 5 == sscanf( ctx.ptr, 
          ": Type %31[a-zA-Z], map '%255[^']', basket %15[a-zA-Z] "
          "Team1: Force %d | Team2: Force %d "
          "UserId ReqId Sex Hero Basket GRating PRating HRating Force Wait Loses Wins Fame Loc Geo | UserId ReqId Sex  Hero Basket GRating PRating HRating Force Wait Loses Wins Fame Loc Geo %n",
          type, map, basket, &f1, &f2, &endOffset ) )
      if ( endOffset )
        ok = true;
  }
  else if ( _logVersion == ELogVersion::trunk ) {
    NI_ALWAYS_ASSERT( "Not impemented" );
  }

  if ( !ok )
    throw ExcepText( ctx.ptr, "Game data expected" );
  ctx.Advance( endOffset );

  mmaking::SGame game;

  if ( !stricmp( type, "PvP" ) )
    game.mapType = NDb::MAPTYPE_PVP;
  else if ( !stricmp( type, "Test1x1" ) )
    game.mapType = NDb::MAPTYPE_PVP;
  else if ( !stricmp( type, "Test2x2" ) )
    game.mapType = NDb::MAPTYPE_PVP;
  else if ( !stricmp( type, "Training" ) )
    game.mapType = NDb::MAPTYPE_TRAINING;
  else
    throw ExcepText( ctx.ptr, "Wrong game type" );

  game.mapId = map;

  while ( true )
  {
    bool first = GetGameMember( ctx, game, true );
    bool second = GetGameMember( ctx, game, false );
    if ( !first && !second )
      break;
  }

  if ( _logVersion >= ELogVersion::v932 )
    game.basket = DetermineGameBasket( game );

  _cb->OnGame( ts, game );
}



bool LogParser::GetGameMember( Ctx & ctx, mmaking::SGame & game, bool first )
{
  NI_PROFILE_FUNCTION;

  int endOffset = 0;
  char hero[64] = "";
  if ( sscanf( ctx.ptr, "bot %63[a-zA-Z] %n", hero, &endOffset ) == 1 ) {
    ctx.Advance( endOffset );
    game.bots.push_back( mmaking::SBotGameMember( first ? lobby::ETeam::Team1 : lobby::ETeam::Team2, hero, "" ) );
  }
  else
  {
    endOffset = 0;
    hero[0] = 0;
    int reqId = 0;
    int mmId = 0;
    char sex[16] = "";
    char basket[16] = "";
    int r = 0, pr = 0, gr = 0;
    float f = 0;
    char loc[16] = "";
    char geo[16] = "";
    float wait = 0;
    int loses=0, wins=0, leaves=0;
    int fame=0;

    if ( _logVersion < ELogVersion::v911  ) {
      if ( 6 != sscanf( ctx.ptr, "%d %15[a-zA-Z] %63[a-zA-Z] %d %15[a-zA-Z] %f %n", &mmId, sex, hero, &r, loc, &wait, &endOffset ) )
        return false;
    } else if ( ( _logVersion == ELogVersion::v911 ) || ( _logVersion == ELogVersion::v914 ) ) {
      if ( 8 != sscanf( ctx.ptr, "%d %d %15[a-zA-Z] %63[a-zA-Z] %d %f %15[a-zA-Z] %f %n", &mmId, &reqId, sex, hero, &r, &f, loc, &wait, &endOffset ) )
        return false;
    } else if ( _logVersion == ELogVersion::v923 ) {
      if ( 9 != sscanf( ctx.ptr, "%d %d %15[a-zA-Z] %63[a-zA-Z] %d %f %15[a-zA-Z] %f %d %n", &mmId, &reqId, sex, hero, &r, &f, loc, &wait, &loses, &endOffset ) )
        return false;
    } else if ( _logVersion == ELogVersion::v932 ) {
      if ( 13 != sscanf( ctx.ptr, "%d %d %15[a-zA-Z] %63[a-zA-Z] %15[a-zA-Z] %d %d %f %15[a-zA-Z] %f %d %d %d %n", &mmId, &reqId, sex, hero, basket, &r, &pr, &f, loc, &wait, &loses, &wins, &fame, &endOffset ) )
        return false;
    } else if ( _logVersion == ELogVersion::v940 ) {
      if ( 14 != sscanf( ctx.ptr, "%d %d %15[a-zA-Z] %63[a-zA-Z] %15[a-zA-Z] %d %d %d %f %15[a-zA-Z] %f %d %d %d %n", &mmId, &reqId, sex, hero, basket, &gr, &pr, &r, &f, loc, &wait, &loses, &wins, &fame, &endOffset ) )
        return false;
    } else if ( _logVersion >= ELogVersion::v941 ) {
      if ( 15 != sscanf( ctx.ptr, "%d %d %15[a-zA-Z] %63[a-zA-Z] %15[a-zA-Z] %d %d %d %f %f %d %d %d %15[a-zA-Z0-9] %15[a-zA-Z0-9] %n", &mmId, &reqId, sex, hero, basket, &gr, &pr, &r, &f, &wait, &loses, &wins, &fame, loc, geo, &endOffset ) )
        return false;
    }

    ctx.Advance( endOffset );

    if ( _logVersion < ELogVersion::v903 )
      r = (int)( r - f * 6.0f + 0.5f ); //magic

    if ( !pr )
      pr = r;

    mmaking::EBasket::Enum ebasket = ( _logVersion >= ELogVersion::v940 ) ? ParseBasket( basket ) : mmaking::EBasket::Normal;

    mmaking::SGeoInfo geoInfo;
    FakePingsByLocation( geoInfo, loc, geo, _logVersion );
    mmaking::SRequestMember memb( mmId, hero, StringToSex( ctx, sex ), ebasket, r, pr, r, f, geoInfo, loses, wins, fame, lobby::ETeam::None, leaves);

    if ( _logVersion < ELogVersion::v940 )
      memb.basket = DetermineMemberBasket( memb );

    mmaking::SGameParty * party = 0;
    if ( reqId )
      for ( int i = 0; i < game.humans.size(); ++i )
        if ( game.humans[i].requestUId == reqId ) {
          party = &game.humans[i];
          break;
        }

    if ( !party ) {
      game.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( first ? lobby::ETeam::Team1 : lobby::ETeam::Team2, 0 ), wait, reqId ) );
      party = &game.humans.back();
    }

    party->members.push_back( memb );
  }

  if ( first ) {
    endOffset = 0;
    sscanf( ctx.ptr, "|%n", &endOffset );
    if ( !endOffset )
      throw ExcepText( ctx.ptr, "'|' expected" );
    ctx.Advance( endOffset );
  }

  return true;
}



mmaking::EBasket::Enum LogParser::DetermineMemberBasket( const mmaking::SRequestMember & memb )
{
  if ( ( memb.totalWins < 10 ) && ( _logVersion == ELogVersion::v932 ) )
    return mmaking::EBasket::Newbie;

  if ( memb.totalLeaves > 2  )
    return mmaking::EBasket::Leaver;


  return mmaking::EBasket::Normal;
}



mmaking::EBasket::Enum LogParser::DetermineGameBasket( const mmaking::SGame & game )
{
  int  noobz = 0, total = 0, leavers = 0;
  for ( int pi = 0; pi < game.humans.size(); ++pi )
  {
    const mmaking::SGameParty & party = game.humans[pi];
    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      ++total;
      const mmaking::SRequestMember & memb = party.members[mi];
      if ( memb.basket == mmaking::EBasket::Newbie )
        ++noobz;
      else if ( memb.basket == mmaking::EBasket::Leaver )
        ++leavers;

    }
  }

  if ( noobz == total )
    return mmaking::EBasket::Newbie;

  if ( leavers == total )
    return mmaking::EBasket::Leaver;

  return mmaking::EBasket::Normal;
}

} //namespace mm_test
