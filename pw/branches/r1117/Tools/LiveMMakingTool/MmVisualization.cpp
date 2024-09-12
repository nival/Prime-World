#include "stdafx.h"
#include "MmVisualization.h"
#include "atlimage.h"
#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/MMakingRequest.h"


namespace mm_test
{

class RatingScale : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( RatingScale, BaseObjectST );

public:
  struct Item {
    int count[2];
    Item() { count[0] = count[1] = 0; }
    int & operator [] ( int i ) { return count[i]; }
    const int & operator [] ( int i ) const { return count[i]; }
  };

  RatingScale( int _minRating, int _maxRating, int _step ) :
  minRating( _minRating ), maxRating( _maxRating ), step( _step )
  {
    int size = ( maxRating - minRating + step - 1 ) / step;
    histo.resize( size );
  }

  void Add( lobby::ETeam::Enum _faction, int rating, int count ) {
    size_t idx = ( rating - minRating ) / step;
    if ( idx < 0 || idx >= histo.size() )
      return;
    int tidx = lobby::ETeam::Index( _faction );
    histo[idx][tidx] += count;
  }

  int Step() const { return step; }

  const std::vector<Item> & Histo() const { return histo; }

  int GetRange( int idx ) const { return minRating + idx * step; }

private:
  const int         minRating, maxRating, step;
  std::vector<Item> histo;
};








class Visualization::Timeslice : public Visualization::ITimeslice, public BaseObjectST {
  NI_DECLARE_REFCOUNT_CLASS_2( Timeslice, ITimeslice, BaseObjectST );
public:
  Timeslice( Visualization * _owner, const Timestamp & _ts ) :
  owner( _owner ), ts( _ts )
  {
    totals[0] = totals[1] = 0;

    const vector<int> & scalesSteps = _owner->sett.scalesSteps;
    scales.resize( scalesSteps.size() );
    for ( int i = 0; i < scales.size(); ++i ) {
      scales[i] = new RatingScale( _owner->sett.minRating, _owner->sett.maxRating, _owner->sett.scalesSteps[i] );
    }
  }

  virtual void Add( lobby::ETeam::Enum _faction, int _rating, int _count ) {
    for ( int i = 0; i < scales.size(); ++i )
      scales[i]->Add( _faction, _rating, _count );

    totals[lobby::ETeam::Index(_faction)] += _count;
  }

  virtual void Close() {
    NI_VERIFY( owner.Valid(), "", return );
    owner->CloseTimeslice( this );
  }

  const Timestamp & Ts() const { return ts; }

  const int ( &Totals() const)[2] { return totals; }

  RatingScale * Scale( int idx ) { return scales[idx]; }

private:
  Weak<Visualization>         owner;
  const Timestamp             ts;
  vector<Strong<RatingScale>> scales;
  int                         totals[2];
};





struct Visualization::Request : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Request, BaseObjectST );

  Timestamp             ts;
  lobby::ETeam::Enum    faction;
  int                   effRating;
  int                   size;

  Request( const Timestamp & _ts, lobby::ETeam::Enum f, int r, int s ) :
  ts( _ts ), faction( f ), effRating( r ), size( s ) {}
};





struct Visualization::Game : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Game, BaseObjectST );

  Timestamp             ts;
  int                   minRating, maxRating;

  Game( const Timestamp & _ts, int minr, int maxr ) :
  ts( _ts ), minRating( minr ), maxRating( maxr ) {}
};







Visualization::Visualization( MmData * _mmData, const VisualizationSettings & _sett ) :
mmData( _mmData ),
sett( _sett )
{
  timeline.reserve( 4096 );
}



Strong<Visualization::ITimeslice> Visualization::OpenTimeslice( const Timestamp & ts )
{
  return new Timeslice( this, ts );
}



void Visualization::CloseTimeslice( Timeslice * slice )
{
  timeline.push_back( slice );
}



void Visualization::AddRequestMark( const Timestamp & ts, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members )
{
  NI_VERIFY( !members.empty(), "", return );

  int r = 0;
  for ( int i = 0; i < members.size(); ++i ) {
    r += members[i].heroRating;
    if ( members[i].basket == mmaking::EBasket::Normal )
      r += mmaking::MmRequest::LoseStreakRatingCompensation( mmData->db, members[i].loseStreak );
  }
  r /= members.size();

  //r += mmaking::MmRequest::PartyRatingCompensation( mmData->db, members.size() );

  requestsLog.push_back( new Request( ts, commonData.team, r, members.size() ) );
}



void Visualization::AddGameMark( const Timestamp & ts, const mmaking::SGame & game )
{
  int minr = -1, maxr = -1;
  for ( int pi = 0; pi < game.humans.size(); ++pi ) {
    int r = 0;
    const mmaking::SGameParty & party = game.humans[pi];
    for ( int i = 0; i < party.members.size(); ++i )
    {
      r += party.members[i].heroRating;
      if ( party.members[i].basket == mmaking::EBasket::Normal )
        r += mmaking::MmRequest::LoseStreakRatingCompensation( mmData->db, party.members[i].loseStreak );
    }
    r /= party.members.size();

    //r += mmaking::MmRequest::PartyRatingCompensation( mmData->db, party.members.size() );

    if ( ( minr < 0 ) || ( r < minr ) )
      minr = r;
    if ( ( maxr < 0 ) || ( r > maxr ) )
      maxr = r;
  }

  gamesLog.push_back( new Game( ts, minr, maxr ) );
}




static const int fontHeight = 12;
static const int mainMargin = 25;
static const int graphHeight = 300;
static const int tenMinuteMark = 4;

static const int halfTeamSize = 5;
static const int colorGrades = 15;
static const int maxTotalTeams = 200;
static const int highColorHits = 20;


static COLORREF LerpColor( COLORREF from, COLORREF to, int percent ) {
  percent = Clamp( percent, 0, 100 );
  int r = ( GetRValue( from ) * ( 100 - percent ) + GetRValue( to ) * percent + 50 ) / 100;
  int g = ( GetGValue( from ) * ( 100 - percent ) + GetGValue( to ) * percent + 50 ) / 100;
  int b = ( GetBValue( from ) * ( 100 - percent ) + GetBValue( to ) * percent + 50 ) / 100;
  return RGB( r, g, b );
}


static void Line( HDC dc, int x0, int y0, int x1, int y1 ) {
  MoveToEx( dc, x0, y0, NULL );
  LineTo( dc, x1, y1 );
}


static void Cross( HDC dc, int x, int y, int sz ) {
  if ( sz == 1 )
    Line( dc, x, y, x + 1, y );
  else {
    Line( dc, x - sz, y, x + sz, y );
    Line( dc, x, y - sz, x, y + sz );
  }
}


static void DrawGridTimeLine( HDC dc, int x, int ymin, int ymax, const Timestamp & ts, bool drawText )
{
  Line( dc, x, ymin, x, ymax );

  if ( drawText ) {
    RECT R;
    SetRect( &R, x, ymax, x + 1, ymax );
    DrawText( dc, NI_STRFMT( "%d:%02d", ts.time.hour, ts.time.minute ), -1, &R, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOCLIP );
  }
}



void Visualization::Draw( const string & filename, lobby::ETeam::Enum faction, bool drawRequests, bool drawGames ) const
{
  MessageTrace( "Drawing overview map '%s'...", filename );

  NI_VERIFY( timeline.size() >= 2, "Too few data!", return );

  Timestamp from = timeline.front()->Ts();
  Timestamp to = timeline.back()->Ts();

  int width = timeline.size();

  int teamsMax = 0;
  for ( size_t index = 0; index < timeline.size(); ++index )
    teamsMax = Min( maxTotalTeams, Max( teamsMax, Max( timeline[index]->Totals()[0], timeline[index]->Totals()[1] ) ) );

  NI_VERIFY( teamsMax > 0, "Too few data!", return );

  MessageTrace( "Image size: %d x %d", width, sett.height );

  CImage img;
  BOOL crResult = img.Create( width, sett.height, 24 );
  NI_VERIFY( crResult, "CImage::Create() failed!", return );

  HDC dc = img.GetDC();
  NI_VERIFY( dc, "CImage::GetDC() failed!", return );

  HBRUSH backBrush = CreateSolidBrush( RGB( 255, 255, 255 ) );

  HPEN nullPen = CreatePen( PS_NULL, 0, 0 );
  HPEN blackPen = CreatePen( PS_SOLID, 0, RGB( 0, 0, 0 ) );
  HPEN teamPen[2] = { CreatePen( PS_SOLID, 0, RGB( 0, 0, 255 ) ), CreatePen( PS_SOLID, 0, RGB( 255, 0, 0 ) ) };
  HPEN dotPen = CreatePen( PS_DOT, 0, RGB( 0, 0, 0 ) );

  HPEN colorGradeLow[colorGrades], colorGradeHi[colorGrades];
  for ( int i = 0; i < colorGrades; ++i ) {
    COLORREF clrLo = LerpColor( RGB( 255, 255, 255 ), RGB( 100, 100, 100 ), 100 * i / ( colorGrades - 1 ) );
    colorGradeLow[i] = CreatePen( PS_SOLID, 0, clrLo );
    COLORREF clrHi = LerpColor( RGB( 0, 160, 0 ), RGB( 255, 255, 0 ), 100 * i / ( colorGrades - 1 ) );
    colorGradeHi[i] = CreatePen( PS_SOLID, 0, clrHi );
  }

  HFONT font = ::CreateFont( fontHeight, fontHeight/2, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, "Arial" );

  HGDIOBJ prevPen = SelectObject( dc, nullPen );

  //Draw background
  HGDIOBJ prevBrush = SelectObject( dc, backBrush );
  Rectangle( dc, 0, 0, width, sett.height );

  SelectObject( dc, blackPen );

  SetBkMode( dc, TRANSPARENT );

  HGDIOBJ prevFont = SelectObject( dc, font );

  SetTextColor( dc, RGB( 0, 0, 0 ) );

  { //Draw totals graph axis
    SelectObject( dc, blackPen );
    Line( dc, 0, graphHeight, width, graphHeight );

    int y = graphHeight - graphHeight * halfTeamSize / teamsMax;
    SelectObject( dc, dotPen );
    Line( dc, 0, y, width, y );
  }

  //Draw faction totals graph
  for ( size_t i = 0; i + 1 < timeline.size(); ++i )
    for ( int t = 0; t < 2; ++t ) {
      int t0 = timeline[i]->Totals()[t], t1 = timeline[i + 1]->Totals()[t];
      if ( t0 > maxTotalTeams || t1 > maxTotalTeams )
        continue;
      int y0 = graphHeight - graphHeight * t0 / teamsMax, y1 = graphHeight - graphHeight * t1 / teamsMax;
      SelectObject( dc, teamPen[t] );
      Line( dc, i, y0, i + 1, y1 );
    }

  //Data draw
  const int scaleHeight = ( sett.height - graphHeight - mainMargin ) / sett.scalesSteps.size() - mainMargin;
  const int ratinRange = sett.maxRating - sett.minRating;
  for ( size_t i = 0; i < timeline.size(); ++i )
  {
    Strong<Timeslice> slice = timeline[i];

    for ( int j = 0; j < sett.scalesSteps.size(); ++j )
    {
      Strong<RatingScale> scale = slice->Scale( j );

      int ymin = graphHeight + ( scaleHeight + mainMargin ) * j + mainMargin, ymax = ymin + scaleHeight;

      int step = scale->Step();
      for ( int k = -1; k < (int)scale->Histo().size(); ++k )
      {
        int r0 = ( k >= 0 ) ? ( scale->GetRange( k ) + step / 2 ) : sett.minRating;
        int r1 = ( k + 1 < (int)scale->Histo().size() ) ? ( scale->GetRange( k + 1 ) + step / 2 ) : sett.maxRating;

        RatingScale::Item nullHits;
        const RatingScale::Item & hits0 = ( k >= 0 ) ? scale->Histo()[k] : nullHits;
        const RatingScale::Item & hits1 = ( k + 1 < (int)scale->Histo().size() ) ? scale->Histo()[k + 1] : nullHits;

        int hits = 0;
        switch ( faction ) {
          default:
          case lobby::ETeam::None:
            hits = Min( hits0[0] + hits1[0], hits0[1] + hits1[1] );
            break;
          case lobby::ETeam::Team1:
            hits = hits0[0] + hits1[0];
            break;
          case lobby::ETeam::Team2:
            hits = hits0[1] + hits1[1];
            break;
        }

        HPEN pen = NULL;
        if ( hits < halfTeamSize ) {
          int pidx = ( ( colorGrades - 1 ) * hits + halfTeamSize/2 ) / ( halfTeamSize - 1 );
          NI_ASSERT( pidx>=0 && pidx < colorGrades, "" );
          pen = colorGradeLow[pidx];
        }
        else {
          int deltaMax = highColorHits - halfTeamSize;
          int delta = Clamp( hits - halfTeamSize, 0, deltaMax );
          int pidx = ( ( colorGrades - 1 ) * delta + deltaMax/2 ) / deltaMax;
          NI_ASSERT( pidx>=0 && pidx < colorGrades, "" );
          pen = colorGradeHi[pidx];
        }
        SelectObject( dc, pen );

        int y0 = ymax - ( scaleHeight * ( r0 - sett.minRating ) + ratinRange/2 ) / ratinRange;
        int y1 = ymax - ( scaleHeight * ( r1 - sett.minRating ) + ratinRange/2 ) / ratinRange;
        Line( dc, i, y0, i, y1 );
      }
    }
  }

  DrawEvents( dc, from, to, width, scaleHeight, teamPen, blackPen, drawRequests, drawGames );

  DrawTimeGrid( dc, blackPen, scaleHeight );
  DrawRatingGrid( dc, blackPen, dotPen, width, scaleHeight );

  RECT R;
  SetRect( &R, 0, 0, 1, 1 );
  DrawText( dc, NI_STRFMT( "%d", teamsMax ), -1, &R, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOCLIP );

  //restore GDI objects
  SelectObject( dc, prevBrush );
  SelectObject( dc, prevPen );
  SelectObject( dc, prevFont );

  //Cleanup
  DeleteObject( backBrush );
  DeleteObject( font );

  DeleteObject( nullPen );
  DeleteObject( blackPen );
  DeleteObject( teamPen[0] );
  DeleteObject( teamPen[1] );
  DeleteObject( dotPen );

  for ( int i = 0; i < colorGrades; ++i ) {
    DeleteObject( colorGradeLow[i] );
    DeleteObject( colorGradeHi[i] );
  }

  img.ReleaseDC();
  img.Save( filename.c_str(), Gdiplus::ImageFormatPNG );
}



void Visualization::DrawTimeGrid( HDC dc, HPEN pen, int scaleHeight ) const
{
  SelectObject( dc, pen );
  int lastHourGrid = timeline.front()->Ts().time.hour, last10thMinuteGrid = timeline.front()->Ts().time.minute / 10;
  for ( size_t i = 0; i < timeline.size(); ++i )
  {
    const Timestamp & ts = timeline[i]->Ts();

    int min10 = ts.time.minute / 10;

    bool drawGrid = false;
    bool drawText = false;
    if ( lastHourGrid != ts.time.hour ) {
      lastHourGrid = ts.time.hour;
      last10thMinuteGrid = min10;
      drawGrid = true;
      drawText = true;
    }

    if ( last10thMinuteGrid != min10 ) {
      last10thMinuteGrid = min10;
      drawGrid = true;
    }

    if ( !drawGrid )
      continue;
    DrawGridTimeLine( dc, i, drawText ? 0 : graphHeight - tenMinuteMark, graphHeight, ts, drawText );
    for ( int j = 0; j < sett.scalesSteps.size(); ++j ) {
      int ymin = graphHeight + ( scaleHeight + mainMargin ) * j + mainMargin;
      DrawGridTimeLine( dc, i, drawText ? ymin : ( ymin + scaleHeight - tenMinuteMark ), ymin + scaleHeight, ts, false );
    }
  }
}



void Visualization::DrawRatingGrid( HDC dc, HPEN solidPen, HPEN dotPen, int width, int scaleHeight ) const
{
  const int ratinRange = sett.maxRating - sett.minRating;

  for ( int j = 0; j < sett.scalesSteps.size(); ++j )
  {
    SelectObject( dc, dotPen );
    const int rstep = 250;
    int ymin = graphHeight + ( scaleHeight + mainMargin ) * j + mainMargin, ymax = ymin + scaleHeight;
    int r = ( sett.minRating / 250 + 1 ) * 250;
    for ( ; r <= sett.maxRating; r += rstep ) {
      int y = ymax - scaleHeight * ( r - sett.minRating ) / ratinRange;
      Line( dc, 0, y, width, y );
    }

    SelectObject( dc, solidPen );
    Line( dc, 0, ymax, width, ymax );

    RECT R;
    SetRect( &R, 0, ymin, 1, ymin + 1 );
    DrawText( dc, NI_STRFMT( "%d", sett.maxRating ), -1, &R, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOCLIP );
    SetRect( &R, 0, ymax, 1, ymax + 1 );
    DrawText( dc, NI_STRFMT( "%d", sett.minRating ), -1, &R, DT_LEFT | DT_BOTTOM | DT_SINGLELINE | DT_NOCLIP );
  }
}



void Visualization::DrawEvents( HDC dc, const Timestamp & from, const Timestamp & to, int width, int scaleHeight, HPEN teamPen[2], HPEN solidPen, bool drawRequests, bool drawGames ) const
{
  const timer::Time span = TimeDiff( to, from );
  const int ratinRange = sett.maxRating - sett.minRating;

  if ( drawRequests )
    for ( TRequests::const_iterator it = requestsLog.begin(); it != requestsLog.end(); ++it ) {
      Strong<Request> req = *it;
      
      timer::Time dt = TimeDiff( req->ts, from );
      if ( dt < 0 || dt > span )
        continue;

      if ( req->effRating < sett.minRating || req->effRating > sett.maxRating )
        continue;

      int x = (int)( width * dt / span + 0.5 );

      SelectObject( dc, teamPen[lobby::ETeam::Index( req->faction )] );

      for ( int j = 0; j < sett.scalesSteps.size(); ++j ) {
        int ymax = graphHeight + ( scaleHeight + mainMargin ) * j + mainMargin + scaleHeight;
        int y = ymax - scaleHeight * ( req->effRating - sett.minRating ) / ratinRange;

        Cross( dc, x, y, req->size );
      }
    }

  if ( drawGames ) {
    SelectObject( dc, solidPen );
    for ( TGames::const_iterator it = gamesLog.begin(); it != gamesLog.end(); ++it ) {
      Strong<Game> game = *it;
      
      timer::Time dt = TimeDiff( game->ts, from );
      if ( dt < 0 || dt > span )
        continue;

      if ( game->minRating < sett.minRating || game->maxRating > sett.maxRating )
        continue;

      int x = (int)( width * dt / span + 0.5 );

      for ( int j = 0; j < sett.scalesSteps.size(); ++j ) {
        int ymax = graphHeight + ( scaleHeight + mainMargin ) * j + mainMargin + scaleHeight;
        int y0 = ymax - scaleHeight * ( game->minRating - sett.minRating ) / ratinRange;
        int y1 = ymax - scaleHeight * ( game->maxRating - sett.minRating ) / ratinRange;

        Line( dc, x, y0, x, y1 );
        Line( dc, x - 1, y0, x + 1, y0 );
        Line( dc, x - 1, y1, x + 1, y1 );
      }
    }
  }
}



void Visualization::DrawBunch( const string & prefix ) const
{
  Draw( prefix + "map.png", lobby::ETeam::None, false, false );
  Draw( prefix + "map_t1.png", lobby::ETeam::Team1, false, false );
  Draw( prefix + "map_t2.png", lobby::ETeam::Team2, false, false );

  Draw( prefix + "map_reqs.png", lobby::ETeam::None, true, false );
  Draw( prefix + "map_t1_reqs.png", lobby::ETeam::Team1, true, false );
  Draw( prefix + "map_t2_reqs.png", lobby::ETeam::Team2, true, false );

  Draw( prefix + "map_reqs_games.png", lobby::ETeam::None, true, true );
  Draw( prefix + "map_t1_reqs_games.png", lobby::ETeam::Team1, true, true );
  Draw( prefix + "map_t2_reqs_games.png", lobby::ETeam::Team2, true, true );
}

} //namespace mm_test
