#ifndef MMAKINGVISUALIZATION_H_INCLUDED
#define MMAKINGVISUALIZATION_H_INCLUDED

#include "MMakingLogParser.h"
#include "MmData.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include <vector>
#include <list>


namespace NDb
{
  struct MMakingSettings;
}


namespace mm_test
{

struct VisualizationSettings
{
  int           minRating, maxRating;
  float         step;
  vector<int>   scalesSteps;
  int           height;

  VisualizationSettings() :
  minRating( 1100 ),
  maxRating( 2600 ),
  step( 5.0 ),
  height( 1200 )
  {
    scalesSteps.push_back( 50 );
    scalesSteps.push_back( 100 );
    scalesSteps.push_back( 200 );
  }
};



class Visualization : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Visualization, BaseObjectST );

public:
  class ITimeslice : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( ITimeslice, IBaseInterfaceST );
  public:
    virtual void Add( lobby::ETeam::Enum faction, int rating, int count ) = 0;
    virtual void Close() = 0;
  };

  Visualization( MmData * _mmData, const VisualizationSettings & _sett );

  const VisualizationSettings & Sett() const { return sett; }

  Strong<ITimeslice> OpenTimeslice( const Timestamp & ts );

  void AddRequestMark( const Timestamp & ts, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members );
  void AddGameMark( const Timestamp & ts, const mmaking::SGame & game );

  void Draw( const string & filename, lobby::ETeam::Enum faction, bool drawRequests, bool drawGames ) const;
  void DrawBunch( const string & prefix ) const;

private:
  class Timeslice;
  struct Request;
  struct Game;

  typedef std::vector<Strong<Timeslice>> TTimeline;
  typedef std::list<Strong<Request>> TRequests;
  typedef std::list<Strong<Game>> TGames;

  Strong<MmData> mmData;
  const VisualizationSettings sett;
  TTimeline         timeline;
  TRequests         requestsLog;
  TGames            gamesLog;

  void CloseTimeslice( Timeslice * slice );

  void DrawTimeGrid( HDC dc, HPEN pen, int scaleHeight ) const;
  void DrawRatingGrid( HDC dc, HPEN solidPen, HPEN dotPen, int width, int scaleHeight ) const;
  void DrawEvents( HDC dc, const Timestamp & from, const Timestamp & to, int width, int scaleHeight, HPEN teamPen[2], HPEN solidPen, bool drawRequests, bool drawGames ) const;
};

} //namespace mm_test

#endif //MMAKINGVISUALIZATION_H_INCLUDED
