#include "stdafx.h"
#include <math.h>
#include "RankMatchmaking.h"
#include "Db/DBServer.auto.h"
#include "MMakingLog.h"
#include "MMakingUniStat.h"
#include "LiveMMakingConfigVars.h"
#include "RankTable.h"
#include "MmQueueIterator.h"
#include "System/InlineProfiler.h"


namespace mmaking
{

  class RankMMakingLogic::TeamDraft
  {
  public:
    typedef std::vector<StrongMT<MmRequest>> TMembers;

    TeamDraft() :
    pop( 0 ),
      totalWaitTime( 0 ), minWaitTime( 0 ), maxWaitTime( 0 ), basket(EBasket::Undefined),  teamFaction(lobby::ETeam::None), avgForce(0), avgPlayerRating(0), diffPlayerRating(0), maxPlayerRating(0)
    {
      members.reserve( 5 );
    }

    void Clear()
    {
      pop = 0;
      totalWaitTime = minWaitTime = maxWaitTime = 0;

      for ( size_t i = 0; i < members.size(); ++i )
        members[i]->Use( false );

      members.clear();
      heroClasses = SHeroClassEfficiency();
      heroCounter.clear();
      teamFaction = lobby::ETeam::None;
      basket = EBasket::Undefined;
      diffPlayerRating = 0;

    }

    const int Pop() const { return pop; }
    const int Size() const { return (int)members.size(); }
    const SHeroClassEfficiency & HeroClasses() const { return heroClasses; }
    EBasket::Enum Basket() const { return basket; }

    const float CountForce() const
    {
      float s = 0;
      for ( size_t i = 0; i < members.size(); ++i )
        s += members[i]->MaxHeroForce() ;
      return s;
    }
    


    const float CountPlayerRating(int minRating, int maxRating) const
    {
      float s = 0;
      for ( size_t i = 0; i < members.size(); ++i )
      {
        int rating = members[i]->MaxPlayerRating();
        rating = Max( Min(rating, maxRating), minRating); 
        s += rating;
      }
      return s;
    }
    const int DiffPlayerRating() const
    {
      return diffPlayerRating;
    }


    const float isFullParty(int fullPartySize) const
    {
      for ( size_t i = 0; i < members.size(); ++i )
        if (members[i]->Size() >= fullPartySize) 
          return true;

      return false; 
    }


    const float PseudoAvgForce(float force, bool isRealAvg = false) const 
    { 
      if (isRealAvg)
        return avgForce;
      else
        return (CountForce() + force)/(members.size() + 1);
    }

    const float PseudoAvgPlayerRating(int rating, int minRating, int maxRating, bool isRealAvg = false) const 
    { 
      if (isRealAvg)
        return avgPlayerRating;
      else
        return (CountPlayerRating(minRating, maxRating) + Max( Min(rating, maxRating), minRating))/(members.size() + 1);
    }



    timer::Time MinWait() const { return minWaitTime; }
    timer::Time MaxWait() const { return maxWaitTime; }
    timer::Time TotalWait() const { return totalWaitTime; }

    const TMembers & Members() const { return members; }
    lobby::ETeam::Enum Faction() const {return teamFaction;} 

    THeroCounter & HeroCounter() { return heroCounter; }

    timer::Time EffectiveWaitTime() const { 
      NI_VERIFY( pop, "", return 0 );
      return ( minWaitTime + maxWaitTime + totalWaitTime ) / ( pop + 2 );
    }

    timer::Time EffectiveWaitTime( timer::Time newReqWait, int newReqSize ) const {
      int newPop = pop + newReqSize;
      NI_VERIFY( newPop, "", return 0 );
      return ( Min( minWaitTime, newReqWait ) + Max( maxWaitTime, newReqWait ) + totalWaitTime + newReqWait ) / ( newPop + 2 );
    }


    EBasket::Enum getTeamBasket() const
    {
      NI_PROFILE_HEAVY_FUNCTION;
      size_t newbie = 0, norm = 0, leavers = 0;
      for ( size_t i = 0; i < members.size(); ++i )
        switch (members[i]->Basket())
      {
        case EBasket::Newbie:
          ++newbie;
          break;
        case EBasket::Leaver:
          ++leavers;
          break;
        default:
          ++norm;
      }

      if (newbie == members.size())
        return EBasket::Newbie;
      else if (leavers == members.size())
        return EBasket::Leaver;
      else 
        return EBasket::Normal;
    }

    void Add( MmRequest * req, timer::Time wait )
    {
      NI_PROFILE_FUNCTION;
      members.push_back( req );
      req->Use( true );

      totalWaitTime += wait * req->Size();
      minWaitTime = pop ? Min( minWaitTime, wait ) : wait;
      maxWaitTime = pop ? Max( maxWaitTime, wait ) : wait;

      pop += req->Size();
      if (!members.empty())
        basket = getTeamBasket();
      teamFaction = req->CommonData().team; // временная фракция, пока собираем команду одной фракции 
      //TODO: Для групп ограничить TotalClassEfficiency() пределами из m_settings->optimalClasses
      heroClasses.Add( req->TotalClassEfficiency() );
      avgForce = CountForce()/members.size();
      avgPlayerRating = CountPlayerRating(1200,2000)/members.size();
      maxPlayerRating = Max(req->MaxPlayerRating(), maxPlayerRating);
      diffPlayerRating = Max(diffPlayerRating, maxPlayerRating - req->MaxPlayerRating());
    }

  private:
    TMembers              members;
    SHeroClassEfficiency  heroClasses;
    int                   pop;
    timer::Time           totalWaitTime, minWaitTime, maxWaitTime;
    THeroCounter          heroCounter;
    lobby::ETeam::Enum    teamFaction;
    EBasket::Enum         basket;
    float                 avgForce;
    float                 avgPlayerRating;
    int maxPlayerRating, diffPlayerRating;
  };



  class RankMMakingLogic::Factions
  {
  public:
    Factions( lobby::ETeam::Enum _f1, lobby::ETeam::Enum _f2 ) : f1( _f1 ), f2( _f2 ) {}

    lobby::ETeam::Enum operator [] ( int _idx ) const { return _idx ? f2 : f1; }

  private:
    lobby::ETeam::Enum f1, f2;
  };



  RankMMakingLogic::RankMMakingLogic( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
  ProdLogicBase( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
    m_totalGames( 0 ), m_fullPartyGames( 0 ), m_fullPartyMixedGames( 0 ), m_donorGames( 0 )
  {
    NI_VERIFY( m_settings->optimalClasses.size() == HeroClassesNumber + 1, "", return );
  }



  RankMMakingLogic::~RankMMakingLogic()
  {
  }




  void RankMMakingLogic::PickUpNewRequest( MmRequest * newReq, IMMakingLogicCallback * callback )
  {
    NI_PROFILE_FUNCTION;
    ProdLogicBase::PickUpNewRequest(newReq, callback);
    const RankDescription * rankCurr = m_ranks->FindRankByIndex( newReq->RankIndex() );

    std::pair< TRequestMap::iterator, bool > rByReqId = m_rrequests[rankCurr->mergedIndex ].insert(TRequestMap::value_type( newReq->RequestId(), newReq ) );
    if (!rByReqId.second )
      return; 
    TMergedRankLineCountMap::const_iterator it = m_MergedRankRequestsCount.find(rankCurr->mergedIndex);
    if (it != m_MergedRankRequestsCount.end())
      m_MergedRankRequestsCount[rankCurr->mergedIndex] += newReq->Size();
    else
      m_MergedRankRequestsCount[rankCurr->mergedIndex] = newReq->Size();
  }


  void RankMMakingLogic::RunIteration( int mostPopularRevision, volatile bool & isRunning )
  {
    NI_PROFILE_FUNCTION_MEM;

    for ( int rank = 0; rank < m_ranks->RanksNumber(); ++rank )
    {

      const RankDescription * rankIn = m_ranks->FindRankByIndex( rank );
      {
        TRankRequestMap::const_iterator cit1 = m_rrequests.find(rankIn->mergedIndex);
        if (cit1!= m_rrequests.end())
        {
          if(!cit1->second.empty() && m_MergedRankRequestsCount[rankIn->mergedIndex]>= 2 * m_teamSize)
            SearchRank( mostPopularRevision,rankIn );
          //m_loger->Log( ELogLevel::Normal, NI_STRFMT("Rank requests size %d rank %s, from %.1f - to %.1f,", m_rcrequests[rankIn->mergedIndex], rankIn->name, rankIn->from, rankIn->to));
        }
      }

    }

  }

  void RankMMakingLogic::ClearInUse(const RankDescription * targetRank)
  {
    NI_PROFILE_FUNCTION;

    TRankRequestMap::iterator cit = m_rrequests.find(targetRank->mergedIndex);
    if( cit != m_rrequests.end())
      for ( TRequestMap::iterator it = cit->second.begin(); it != cit->second.end() ; ++it )
        it->second->Use( false );
  }


  void RankMMakingLogic::OnSmartDump()
  {
    m_loger->Log( ELogLevel::Normal, "Tech info: total_games=%d, full_party=%d, full_party_mixed=%d, donor=%d",
      m_totalGames,  m_fullPartyGames, m_fullPartyMixedGames, m_donorGames );
  }



  void RankMMakingLogic::SearchRank( int mostPopularRevision, const RankDescription * targetRank )
  {
    NI_PROFILE_FUNCTION;

    for ( TGeoIndex locale1 = m_locales.BeginIdx(); locale1 < m_locales.EndIdx(); ++locale1 )
      for ( TGeoIndex locale2 = m_locales.BeginIdx(); locale2 < m_locales.EndIdx(); ++locale2 )
      {
        GeolocationConstraints geo;

        if ( !CheckAndSetupLocalePair( geo, locale1, locale2 ) )
          continue;

        for ( TGeoIndex location = m_locations.BeginIdx(); location < m_locations.EndIdx(); ++location )
        {
          NI_PROFILE_BLOCK( "Inner Loop" );

          geo.location = location;

          for ( int fullParty = 0; fullParty < 2; ++fullParty )
          {
            switch(m_enableRandomQueueIterator )
            {
            case 0:
              SearchForGame( mostPopularRevision, targetRank, geo, fullParty, false); // обычный перебор очереди
              break;
            case 1:
              SearchForGame( mostPopularRevision, targetRank, geo, fullParty, true); //обход очереди случайным образом
              break;
            case 2:
              SearchForGame( mostPopularRevision, targetRank, geo, fullParty, false); // обычный перебор очереди
              SearchForGame( mostPopularRevision, targetRank, geo, fullParty, true); //обход очереди случайным образом
              break;

            }

          }
        }
      }
  }


  void RankMMakingLogic::SearchForGame( int mostPopularRevision, const RankDescription * targetRank, const GeolocationConstraints & geo, bool fullParty, bool isRandomIter )
  {
    NI_PROFILE_FUNCTION;

    ClearInUse(targetRank);

    TeamDraft teams[2];

    //const RankDescription * teamRanks[2] = { targetRank, targetRank };

    if ( fullParty )
      if ( !SearchForFullParty( teams, mostPopularRevision, targetRank, geo, isRandomIter ) )
        return;

    TGeoindexVector sidesLocale;
    sidesLocale.push_back(geo.sidesLocale[0]);
    sidesLocale.push_back(geo.sidesLocale[1]);
    for ( int stage = 0; stage < ESweepStage::EndMarker; ++stage )
      BasicSweep( teams[0], teams[1], (ESweepStage::Enum)stage, mostPopularRevision, targetRank, sidesLocale, geo.location, isRandomIter);

    for ( int ti = 0; ti < 2; ++ti )
      if ( geo.multipleLocales && ( ti == geo.recipientSide ) )
      {
        TGeoindexVector donorLocale;
        donorLocale.push_back(geo.sidesLocale[geo.donorSide]);

        for ( int stage = 0; stage < ESweepStage::EndMarker; ++stage )
          BasicSweep( teams[0], teams[1], (ESweepStage::Enum)stage, mostPopularRevision, targetRank, donorLocale, geo.location, isRandomIter);
      }

      if ( ( teams[0].Pop() != m_teamSize ) || ( teams[1].Pop() != m_teamSize ) )
        return;

      for ( int ti = 0; ti < 2; ++ti )
        if ( teams[ti].Size() > 1 ) //We dont check full party for hero classes
          if ( !CheckHeroClassesLowLimit( teams[ti] ) )
            return;

      if ( !targetRank->highRating )
        if ( !CheckDonorConditions( teams, geo ) )
          return;

      // чтобы не мейкать нормалов ливеров с нормалами не ливерами 
      if (!CheckLeaverBasket(teams))
        return ;

      ChangeSide(teams);
      OutputGame( teams, targetRank->basket, fullParty, targetRank, geo );


  }


  bool RankMMakingLogic::SearchForFullParty( TeamDraft teams[2], int mostPopularRevision, const RankDescription * targetRank, const GeolocationConstraints & geo, bool isRandomIter)
  {
    NI_PROFILE_FUNCTION;

    TGeoindexVector sidesLocale;
    sidesLocale.push_back(geo.sidesLocale[0]);
    sidesLocale.push_back(geo.sidesLocale[1]);

    SweepForFullParty( teams[0], teams[1], mostPopularRevision,  targetRank, sidesLocale, geo.location, isRandomIter );

    for ( int ti = 0; ti < 2; ++ti )
    {
      if ( geo.multipleLocales && ( ti == geo.recipientSide ) )
      {
        TGeoindexVector donorLocale;
        donorLocale.push_back(geo.sidesLocale[geo.donorSide]);
        SweepForFullParty( teams[0], teams[1], mostPopularRevision, targetRank, donorLocale, geo.location, isRandomIter );
      }
    }

    if ( !teams[0].Size() && !teams[1].Size() )
      return false;

    //Проверим время ожидания для случая фулка vs рандом
    if ( targetRank->basket != EBasket::Newbie )
      for (int ti = 0; ti <2; ++ti  )
      {
        if (!teams[ti].Size())
        {
          if ( teams[ti ? 0: 1].MinWait() < m_settings->fullPartyVsRandomTimeThreshold )
            return false;
        }
      }

      //попробуем добить неполные фулки рандомом того же звания 
      for ( int ti = 0; ti < 2; ++ti )
        if ( teams[ti].Pop() && ( teams[ti].Pop() < m_teamSize ) )
        {

          for ( int stage = 0; stage < ESweepStage::EndMarker; ++stage )
            BasicSweep( teams[0], teams[1], (ESweepStage::Enum)stage, mostPopularRevision,  targetRank, sidesLocale, geo.location, isRandomIter );


          if ( geo.multipleLocales && ( ti == geo.recipientSide ))
          { 
            TGeoindexVector donorLocale;
            donorLocale.push_back(geo.sidesLocale[geo.donorSide]);
            for ( int stage = 0; stage < ESweepStage::EndMarker; ++stage )
              BasicSweep( teams[0], teams[1], (ESweepStage::Enum)stage, mostPopularRevision, targetRank, donorLocale, geo.location, isRandomIter);
          }
        }

        //Если добить не получилось, то очистим недоделанные команды
        for ( int ti = 0; ti < 2; ++ti )
          if ( teams[ti].Pop() && ( teams[ti].Pop() < m_teamSize ) )
            teams[ti].Clear();

        // чтобы не мейкать нормалов ливеров с нормалами не ливерами 
        if (!CheckLeaverBasket(teams)){
          //m_loger->Log( ELogLevel::Normal, "CheckLeaverBasket: return false" );
          return false;
        }
        //m_loger->Log( ELogLevel::Normal, "CheckLeaverBasket: return true" );

        if ( !teams[0].Size() && !teams[1].Size() )
          return false;

        return true;
  }



  void RankMMakingLogic::BasicSweep( TeamDraft& team1, TeamDraft& team2, ESweepStage::Enum stage, int mostPopularRevision, const RankDescription * targetRank, const TGeoindexVector& sidesLocale, TGeoIndex geolocation, bool isRandomIter)
  {
    NI_PROFILE_FUNCTION;

    unsigned iteratorFlags = 0;
    if ( targetRank->highRating )
      iteratorFlags |= QueueIterator::F_IgnoreLocaleAndPing;

    EBasket::Enum basket = targetRank->basket;
    for ( QueueIterator it( m_rrequests[targetRank->mergedIndex], mostPopularRevision, basket, sidesLocale, 0, geolocation, m_now, iteratorFlags, m_settings, m_config, m_locales, isRandomIter ); ; )
    {
      if ( team2.Pop() >= m_teamSize && team1.Pop() >= m_teamSize )
        return;

      QueueIteratorCtx itCtx;
      StrongMT<MmRequest> req = it.NextRequest( itCtx );
      if ( !req )
        break;

      if ( req->InUse() )
        continue;

      if ( req->Size() >= m_settings->fullPartySize )
        continue;
      
      if (m_config->orderTeamFormation == 1)
      {
        if (targetRank->usePlayerRatingMM)
          ProcessRequestWithForce(team1, team2, stage, mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
        else
          ProcessRequest(team1, team2, stage, mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);

      }
      else
      {
        if (targetRank->useForceMM)
          ProcessRequestWithForce(team1, team2, stage, mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
        else
          ProcessRequest(team1, team2, stage, mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
      }
    }
  }

  void RankMMakingLogic::ProcessRequestWithForce(TeamDraft& team1, TeamDraft& team2, ESweepStage::Enum stage, int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale)
  {

    timer::Time waitTimePenalty = 0;
    if (!CheckRequestGeneral(team1, team2, req, targetRank, itCtx.waitTime, iteratorFlags, sidesLocale, waitTimePenalty ))
      return;
    
    //TeamDraft & team =team1;
    int flag = EForceRequestPriority::NOBODY;
    timer::Time correctedWaitTime = 0; 
    int res = EForceRequestPriority::NOBODY;
    if (m_config->orderTeamFormation == 1)
      res = CheckPlayerRating(EForceRequestPriority::BOTH, team1, team2, stage, req, itCtx.waitTime);
    else
      res = CheckHeroForce(EForceRequestPriority::BOTH, team1, team2, stage, req, itCtx.waitTime);

    switch(res) 
    {
    case EForceRequestPriority::TEAM1:
      {
        if ( team1.Pop() >= m_teamSize )
          return ;

        flag = EForceRequestPriority::TEAM1;
        if (!CheckRequestForTeam(team1, req, targetRank, itCtx, basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale), waitTimePenalty ))
          return ;
      }
      break;

    case EForceRequestPriority::TEAM2:
      {
        if ( team2.Pop() >= m_teamSize )
          return ;

        flag = EForceRequestPriority::TEAM2;
        if (!CheckRequestForTeam(team2, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale), waitTimePenalty ))
          return ;
      }
      break;

    case EForceRequestPriority::BOTH:
      {
        if ( team1.Pop() < m_teamSize )
        {
          if (!CheckRequestForTeam(team1, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale), waitTimePenalty ))
          {
            if ( team2.Pop() < m_teamSize )
              if (!CheckRequestForTeam(team2, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale), waitTimePenalty ))
                return;
              else 
                flag = EForceRequestPriority::TEAM2;
          }else 
            flag = EForceRequestPriority::TEAM1;
        }
        else if ( team2.Pop() < m_teamSize )
        {
          if (!CheckRequestForTeam(team2, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale), waitTimePenalty ))
            return ;
          else
            flag = EForceRequestPriority::TEAM2;
        }
        else
          return ;
      }
      break;

    case EForceRequestPriority::NOBODY:

    default:

      return ;
    }
    
    if (flag == EForceRequestPriority::NOBODY)
      return;

    if (m_config->orderTeamFormation == 1)
    {
      if (targetRank->useForceMM )
        flag = CheckHeroForce((EForceRequestPriority::Enum)flag, team1, team2, stage, req, itCtx.waitTime);

    }
    else
    {
    if (m_config->enablePlayerRatingMM && targetRank->usePlayerRatingMM)
      flag = CheckPlayerRating((EForceRequestPriority::Enum)flag, team1, team2, stage, req, itCtx.waitTime);
    }
    if (flag != EForceRequestPriority::NOBODY)
      AddToTeam(flag,team1, team2,req, correctedWaitTime);
  }

  void RankMMakingLogic::ProcessRequest(TeamDraft& team1, TeamDraft& team2, ESweepStage::Enum stage, int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale)
  {
    timer::Time waitTimePenalty = 0;
    if (!CheckRequestGeneral(team1, team2, req, targetRank, itCtx.waitTime, iteratorFlags, sidesLocale, waitTimePenalty ))
      return;

    timer::Time correctedWaitTime = 0; 
    int flag  = EForceRequestPriority::NOBODY;
    if ( team1.Pop() < m_teamSize )
    {
      if (!CheckRequestForTeam(team1, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale), waitTimePenalty ))
      {
        if ( team2.Pop() >= m_teamSize )
         return;
          
          if (!CheckRequestForTeam(team2, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale), waitTimePenalty ))
            return;
          else
            flag = EForceRequestPriority::TEAM2;


      } else
             flag = EForceRequestPriority::TEAM1;
    }
    else {

      if ( team2.Pop() >= m_teamSize )
        return ;

      if (!CheckRequestForTeam(team2, req, targetRank, itCtx,basket, stage, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale), waitTimePenalty ))
        return ;
      else
        flag = EForceRequestPriority::TEAM2;
   
    }

    if (flag == EForceRequestPriority::NOBODY)
      return;


    if (m_config->orderTeamFormation == 1)
    {
      if (targetRank->useForceMM)
        flag = CheckHeroForce((EForceRequestPriority::Enum)flag, team1, team2, stage, req, itCtx.waitTime);
    }
    else{
      if (m_config->enablePlayerRatingMM && targetRank->usePlayerRatingMM)
        flag = CheckPlayerRating((EForceRequestPriority::Enum)flag, team1, team2, stage, req, itCtx.waitTime);
    }

    if (flag != EForceRequestPriority::NOBODY)
      AddToTeam(flag,team1, team2,req, correctedWaitTime);
  }

  bool RankMMakingLogic::CheckRequestGeneral(TeamDraft& team1, TeamDraft& team2, MmRequest * req, const RankDescription * targetRank, float waitTime, unsigned iteratorFlags, const TGeoindexVector& sidesLocales, timer::Time& waitTimePenalty )
  {
    if (!CheckLocale(req, sidesLocales[0], iteratorFlags) && !CheckLocale(req, sidesLocales[1], iteratorFlags))
      return false; 

    if ( !CommonRequestCheckList( req, waitTime, targetRank, waitTimePenalty ) )
      return false;

    if ( !CheckRankDiff( team1, team2, req ) )
      return false;

    return true;
  }

  bool RankMMakingLogic::CheckRequestForTeam(TeamDraft& team, MmRequest * req, const RankDescription * targetRank, QueueIteratorCtx& itCtx, EBasket::Enum basket, 
    ESweepStage::Enum stage, timer::Time& correctedWaitTime, unsigned iteratorFlags, const TGeoIndex primaryLocale, timer::Time waitTimePenalty)
  {
    if (!CheckLocale(req, primaryLocale, iteratorFlags))
      return false;

    if ( team.Pop() + req->Size() > m_teamSize )
      return false;

    if (!CheckRequestSide(team, req, itCtx.waitTime))
      return false;
    
    if ( !CheckRequestLeaverTeam(  team, req, itCtx.waitTime ) )
      return false;

    if ( !CheckHeroesLimit( team.HeroCounter(), req, basket ) )
      return false;

    correctedWaitTime = Max( 0.0, itCtx.waitTime - waitTimePenalty );

    if ( !CheckHeroClasses( team, stage, req, correctedWaitTime ) )
      return false;

    return true;
  }

  bool RankMMakingLogic::CheckLocale(MmRequest * req, const TGeoIndex primaryLocale, unsigned iteratorFlags ) const
  {
    const TGeoIndex requestLoc = req->Locale();

    if ( !requestLoc ) //Unknown locale is compatible with everything
      return true;

    if ( requestLoc != primaryLocale )
      if ( m_locales.Isolated( requestLoc ) || m_locales.Isolated( primaryLocale ) )
        return false;

    if ( iteratorFlags  & QueueIterator::F_IgnoreLocaleAndPing )
      return true;

    if ( requestLoc != primaryLocale )
      return false ;

    return true;
  }

  void RankMMakingLogic::SweepForFullParty( TeamDraft& team1, TeamDraft& team2, int mostPopularRevision, const RankDescription * targetRank, const TGeoindexVector& sidesLocale, TGeoIndex geolocation, bool isRandomIter)
  {
    NI_PROFILE_FUNCTION;

    unsigned iteratorFlags = 0;
    if ( targetRank->highRating )
      iteratorFlags |= QueueIterator::F_IgnoreLocaleAndPing;

    EBasket::Enum basket = targetRank->basket;
    for ( QueueIterator it( m_rrequests[targetRank->mergedIndex], mostPopularRevision, basket, sidesLocale, 0, geolocation, m_now, iteratorFlags, m_settings, m_config, m_locales, isRandomIter ); ; )
    {
      if ( team2.Pop() >= m_teamSize && team1.Pop() >= m_teamSize )
        return;

      QueueIteratorCtx itCtx;
      StrongMT<MmRequest> req = it.NextRequest( itCtx );
      if ( !req )
        break;

      if ( req->InUse() )
        continue;

      if ( req->Size() < m_settings->fullPartySize )
        continue;
      if (m_config->orderTeamFormation == 1)
      {
        if (targetRank->usePlayerRatingMM)
            ProcessFullPartyRequestWithForce(team1, team2,  mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
          else 
            ProcessFullPartyRequest(team1, team2,  mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
      }
      else
      {
        if (targetRank->useForceMM)
          ProcessFullPartyRequestWithForce(team1, team2,  mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
        else 
          ProcessFullPartyRequest(team1, team2,  mostPopularRevision, targetRank, req, basket, itCtx, iteratorFlags, sidesLocale);
      }
    }
  }

  bool RankMMakingLogic::CheckRankDiff(TeamDraft& team1, TeamDraft& team2, MmRequest * req)
  {
    NI_PROFILE_FUNCTION;
    const RankDescription * rank = m_ranks->FindRankByIndex( req->RankIndex() );

    TeamDraft* teams[2] = {&team1, &team2};
    
    for (int i=0; i<2; i++)
    {
      TeamDraft::TMembers members = teams[i]->Members();
      for(TeamDraft::TMembers::const_iterator it = members.begin(); it != members.end(); ++it)
      {
        MmRequest* memReq = (*it);
        const RankDescription * targetRank = m_ranks->FindRankByIndex( memReq->RankIndex() );
        const int rankDiff = abs( rank->index - targetRank->index );
        const int allowedRankDiff =  max(0, min(rank->mergeRanksCount, targetRank->mergeRanksCount));
        if (rankDiff > allowedRankDiff)
          return false;
      }
    }

    return true;
  }

  void RankMMakingLogic::ProcessFullPartyRequestWithForce(TeamDraft& team1, TeamDraft& team2,int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale)
  {
    if (!CheckRankDiff(team1, team2, req))
      return;

    //TeamDraft & team =team1;
    int flag = EForceRequestPriority::NOBODY;
    timer::Time correctedWaitTime = 0; 
    int res = EForceRequestPriority::NOBODY;

    if (m_config->orderTeamFormation == 1)
      res = CheckPlayerRating(EForceRequestPriority::BOTH, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);
    else
      res = CheckHeroForce(EForceRequestPriority::BOTH, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);

    switch(res) 
    {
    case EForceRequestPriority::TEAM1:
      {
        if ( team1.Pop() >= m_teamSize )
          return ;

        flag = EForceRequestPriority::TEAM1;
        if (!CheckFullPartyRequest(team1, req, targetRank, itCtx, basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale)))
          return ;
      }
      break;

    case EForceRequestPriority::TEAM2:
      {
        if ( team2.Pop() >= m_teamSize )
          return ;

        flag = EForceRequestPriority::TEAM2;
        if (!CheckFullPartyRequest(team2, req, targetRank, itCtx,basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale) ))
          return ;
      }
      break;

    case EForceRequestPriority::BOTH:
      {
        if ( team1.Pop() < m_teamSize )
        {
          if (!CheckFullPartyRequest(team1, req, targetRank, itCtx,basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale) ))
          {
            if ( team2.Pop() < m_teamSize )
              if (!CheckFullPartyRequest(team2, req, targetRank, itCtx,basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale)))
                return;
              else 
                flag = EForceRequestPriority::TEAM2;
          } else 
            flag = EForceRequestPriority::TEAM1;
        }
        else if ( team2.Pop() < m_teamSize )
          if (!CheckFullPartyRequest(team2, req, targetRank, itCtx,basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale) ))
            return ;
          else
            flag = EForceRequestPriority::TEAM2;
        else
          return;
      }
      break;

    case EForceRequestPriority::NOBODY:

    default:

      return ;
    }

     if (m_config->orderTeamFormation == 1)
    {
      if (targetRank->useForceMM && flag != EForceRequestPriority::NOBODY)
        flag = CheckHeroForce((EForceRequestPriority::Enum)flag, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);
    }
    else{
    if (m_config->enablePlayerRatingMM && targetRank->usePlayerRatingMM && flag != EForceRequestPriority::NOBODY)
      flag = CheckPlayerRating((EForceRequestPriority::Enum)flag, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);
    }
    if (flag != EForceRequestPriority::NOBODY)
       AddToTeam(flag,team1, team2,req, correctedWaitTime);

  }

  const TGeoIndex RankMMakingLogic::GetPrimaryLocale(int flag,  const TGeoindexVector& sidesLocale ) const
  {

    if (sidesLocale.size() == 2)
    {
      return sidesLocale[flag];
    }
    else if (sidesLocale.size() == 1)
    {
      return sidesLocale[0];
    }
    return -1; 
  }

  void RankMMakingLogic::ProcessFullPartyRequest(TeamDraft& team1, TeamDraft& team2,int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale)
  {

    if (!CheckRankDiff(team1, team2, req))
      return;

    timer::Time correctedWaitTime = 0; 
    int flag  = EForceRequestPriority::NOBODY;
    if ( team1.Pop() < m_teamSize )
    {
      if (!CheckFullPartyRequest(team1, req, targetRank, itCtx, basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM1, sidesLocale) ))
      {
        if ( team2.Pop() >= m_teamSize )
          return;

          if (!CheckFullPartyRequest(team2, req, targetRank, itCtx, basket,  correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale)))
            return;
          else 
            flag = EForceRequestPriority::TEAM2;
      } 
      else 
          flag = EForceRequestPriority::TEAM1;
    }
    else 
    { 
      if ( team2.Pop() >= m_teamSize )
        return; 
    
      if (!CheckFullPartyRequest(team2, req, targetRank, itCtx, basket, correctedWaitTime, iteratorFlags, GetPrimaryLocale(EForceRequestPriority::TEAM2, sidesLocale) ))
        return ;
      else
        flag = EForceRequestPriority::TEAM2;
      
    }


    if (m_config->orderTeamFormation == 1)
    {
      if (targetRank->useForceMM && flag != EForceRequestPriority::NOBODY)
        flag = CheckHeroForce((EForceRequestPriority::Enum)flag, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);
    }
    else{
      if (m_config->enablePlayerRatingMM && targetRank->usePlayerRatingMM && flag != EForceRequestPriority::NOBODY)
        flag = CheckPlayerRating((EForceRequestPriority::Enum)flag, team1, team2, (ESweepStage::Enum)0, req, itCtx.waitTime);
    }

    if (flag != EForceRequestPriority::NOBODY)
      AddToTeam(flag,team1, team2,req, correctedWaitTime);


  }

  void RankMMakingLogic::AddToTeam(const int flag, TeamDraft& team1, TeamDraft& team2, MmRequest * req, timer::Time& correctedWaitTime)
  {
    switch (flag)
    {
    case EForceRequestPriority::TEAM1:
      CountHeroes( team1.HeroCounter(), req, m_heroes );
      team1.Add( req, correctedWaitTime );
      return ;

    case EForceRequestPriority::TEAM2:
      CountHeroes( team2.HeroCounter(), req, m_heroes );
      team2.Add( req, correctedWaitTime );
      return ;

    }

  }

  bool RankMMakingLogic::CheckFullPartyRequest(TeamDraft& team, MmRequest * req, const RankDescription * targetRank, QueueIteratorCtx& itCtx, EBasket::Enum basket, timer::Time& correctedWaitTime, unsigned iteratorFlags, const TGeoIndex primaryLocale )
  {
  
    timer::Time waitTimePenalty = 0;
    if (!CheckLocale(req,primaryLocale, iteratorFlags))
      return false; 

    if ( team.Pop() + req->Size() > m_teamSize )
      return false;

    if (!CheckRequestSide(team, req, itCtx.waitTime))
      return false;

    if ( !CheckRequestLeaverTeam(  team, req, itCtx.waitTime ) )
      return false;

    if ( !CheckHeroesLimit( team.HeroCounter(), req, basket ) )
      return false;
    
    if (!CommonRequestCheckList( req, itCtx.waitTime, targetRank, waitTimePenalty ))
      return false;
    correctedWaitTime = Max( 0.0, itCtx.waitTime - waitTimePenalty );

    return true;
  }


  bool RankMMakingLogic::CommonRequestCheckList( const MmRequest * req, timer::Time waitTime, const RankDescription * targetRank, timer::Time & waitTimePenalty )
  {
    NI_PROFILE_FUNCTION;
    const RankDescription * rank = m_ranks->FindRankByIndex( req->RankIndex() );

    if ( rank->mergedIndex != targetRank->mergedIndex )
      return false;

    const int rankDiff = abs( rank->index - targetRank->index );
    waitTimePenalty = m_settings->rankDifferenceTimePenalty * rankDiff;

    if ( waitTime < waitTimePenalty )
      return false;

    return true;
  }

  bool RankMMakingLogic::checkPR( const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime)
  {

    float premium = 0.f;
    int index = team1.Pop(); 
    index = m_teamSize - 1 - index;
    if (waitTime >= m_settings->recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold)
    { 
      float koeff = 1 + (waitTime - m_settings->recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold)/60;
      premium = koeff * m_settings->recessionTableForPlayerRatingMM.recessionPremiumTable[index];
    }
    int maxPlayerRating = m_settings->recessionTableForPlayerRatingMM.recessionMaxPlayerRating;
    int minPlayerRating = m_settings->recessionTableForPlayerRatingMM.recessionMinPlayerRating;

    return (fabs(team1.PseudoAvgPlayerRating(req->MaxPlayerRating(),minPlayerRating, maxPlayerRating) - team2.PseudoAvgPlayerRating(0, minPlayerRating, maxPlayerRating, true)) <= (m_settings->recessionTableForPlayerRatingMM.recessionTable[stage].recessionTable[index] + premium) ); 
  }
  
  int  RankMMakingLogic::CheckPlayerRating(EForceRequestPriority::Enum priority, const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime)
  {
    NI_PROFILE_HEAVY_FUNCTION;
    int diff = 0, playerDiff = 0;

    if (m_settings->playerDiff != -1)
      playerDiff = m_settings->playerDiff;

    if (m_settings->recessionTableForPlayerRatingMM.recessionSideDiff != -1)
      diff = m_settings->recessionTableForPlayerRatingMM.recessionSideDiff;
    
    if (priority == EForceRequestPriority::NOBODY)
      return EForceRequestPriority::NOBODY;

    if (!team1.Pop() && !team2.Pop())
      return priority;

    int fTeam2 = EForceRequestPriority::NOBODY, fTeam1 = EForceRequestPriority::NOBODY;

    if ( team2.Pop() < m_teamSize && checkPR(team2, team1, stage, req, waitTime)) 
      fTeam2 = EForceRequestPriority::TEAM2;

    if ( team1.Pop() < m_teamSize && checkPR(team1, team2, stage, req, waitTime )) 
      fTeam1 = EForceRequestPriority::TEAM1;



    if ( (team1.Pop() - team2.Pop() <= playerDiff) && (team1.DiffPlayerRating() <= diff) && fTeam1 == EForceRequestPriority::TEAM1 && (priority == EForceRequestPriority::TEAM1  || priority == EForceRequestPriority::BOTH) )
      return EForceRequestPriority::TEAM1;
    else if ( (team2.Pop() - team1.Pop() <= playerDiff) && (team2.DiffPlayerRating() <= diff) && fTeam2 == EForceRequestPriority::TEAM2 && (priority == EForceRequestPriority::TEAM2  || priority == EForceRequestPriority::BOTH) )
      return EForceRequestPriority::TEAM2;
    else 
    {
        return chooseTeam(priority, fTeam1, fTeam2);
    } 
  }

  bool RankMMakingLogic::checkForce(const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime, bool isParty )
  {
    float premium = 0.f;
    int index = team1.Pop(); 
    if (isParty)
    {
      index = m_teamSize - 1 - index;
      if (waitTime >= m_settings->recessionPremiumTimeThreshold)
      { 
        float koeff = 1 + (waitTime - m_settings->recessionPremiumTimeThreshold)/60;
        premium = koeff * m_settings->recessionFullPartyTableForForceMM.recessionPremium[index];
      }
      /*
      m_loger->Log( ELogLevel::Normal, "Party checkForce index %d; team2 (%d) PseudoAvgForce: %f; team1(%d) AvgForce: %f; diff %0.f; premium %f; db %f ",
      stage,
      team1.Pop(),
      team1.PseudoAvgForce(req->MaxHeroForce()),
      team2.Pop(),
      team2.PseudoAvgForce(0, true),
      fabs(team1.PseudoAvgForce(req->MaxHeroForce()) - team2.PseudoAvgForce(0, true)),
      premium,
      m_settings->recessionFullPartyTableForForceMM.recessionTable[index]);
      */
      return (fabs(team1.PseudoAvgForce(req->MaxHeroForce()) - team2.PseudoAvgForce(0, true)) <= (m_settings->recessionFullPartyTableForForceMM.recessionTable[index] + premium) ); 

    }
    else
    { 
      if (waitTime >= m_settings->recessionPremiumTimeThreshold)
      { 
        float koeff = 1 + (waitTime - m_settings->recessionPremiumTimeThreshold)/60;
        premium = koeff * m_settings->recessionPremiumTable[index];
      }
      /*
      m_loger->Log( ELogLevel::Normal, "checkForce stage %d; team2 (%d) PseudoAvgForce: %f; team1(%d) AvgForce: %f; diff %0.f; premium %f; db %f ",
      stage,
      team1.Pop(),
      team1.PseudoAvgForce(req->MaxHeroForce()),
      team2.Pop(),
      team2.PseudoAvgForce(0, true),
      fabs(team1.PseudoAvgForce(req->MaxHeroForce()) - team2.PseudoAvgForce(0, true)),
      premium,
      m_settings->recessionTableForForceMM[stage].recessionTable[index]);
      */
      return (fabs(team1.PseudoAvgForce(req->MaxHeroForce()) - team2.PseudoAvgForce(0, true)) <= (m_settings->recessionTableForForceMM[stage].recessionTable[index] + premium) ); 
    }
  }

  int RankMMakingLogic::CheckHeroForce(EForceRequestPriority::Enum priority, const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime, bool isParty )
  {
    NI_PROFILE_HEAVY_FUNCTION;
    int diff = m_teamSize;

    if (m_settings->playerDiff != -1)
      diff = m_settings->playerDiff;
    
    if (priority == EForceRequestPriority::NOBODY)
        return EForceRequestPriority::NOBODY;

    if (!team1.Pop() && !team2.Pop())
      return priority;

    int fTeam2 = EForceRequestPriority::NOBODY, fTeam1 = EForceRequestPriority::NOBODY;

    if ( team2.Pop() < m_teamSize && checkForce(team2, team1, stage, req, waitTime, isParty )) 
      fTeam2 = EForceRequestPriority::TEAM2;

    if ( team1.Pop() < m_teamSize && checkForce(team1, team2, stage, req, waitTime, isParty  )) 
      fTeam1 = EForceRequestPriority::TEAM1;



    if ( /*(team1.Pop() - team2.Pop() >= diff) &&*/ fTeam1 == EForceRequestPriority::TEAM1  && (priority == EForceRequestPriority::TEAM1 || priority == EForceRequestPriority::BOTH) )
      return EForceRequestPriority::TEAM1;
    else if (/*(team2.Pop() - team1.Pop() >= diff) && */fTeam2 == EForceRequestPriority::TEAM2  && (priority == EForceRequestPriority::TEAM2 || priority == EForceRequestPriority::BOTH)  )
      return EForceRequestPriority::TEAM2;
    else 
    {
      return chooseTeam(priority, fTeam1, fTeam2);
    } 

    //return EForceRequestPriority::NOBODY;
  }

  inline int RankMMakingLogic::chooseTeam(EForceRequestPriority::Enum priority, int fTeam1, int fTeam2 )
  {
    if (fTeam1 == EForceRequestPriority::TEAM1 && fTeam2 == EForceRequestPriority::TEAM2)
    {
      if (priority == EForceRequestPriority::BOTH)
        return priority;
      else if (fTeam1 == priority)
        return fTeam1; 
      else if (fTeam2 == priority)
        return fTeam2; 

    }  
    else if (fTeam1 == EForceRequestPriority::TEAM1 && fTeam2 == EForceRequestPriority::NOBODY && (priority == EForceRequestPriority::TEAM1  || priority == EForceRequestPriority::BOTH) )
      return EForceRequestPriority::TEAM1;
    else if (fTeam2 == EForceRequestPriority::TEAM2 && fTeam1 == EForceRequestPriority::NOBODY  && (priority == EForceRequestPriority::TEAM2  || priority == EForceRequestPriority::BOTH))
      return EForceRequestPriority::TEAM2;
    else 
      return EForceRequestPriority::NOBODY;

    return EForceRequestPriority::NOBODY;
  }


  bool RankMMakingLogic::CheckHeroClasses( const TeamDraft & team, ESweepStage::Enum stage, MmRequest * req, timer::Time correctedWaitTime )
  {
    NI_PROFILE_HEAVY_FUNCTION;

    for ( int i = 0; i < HeroClassesNumber; ++i )
    {
      const int minEff = (int)( 100 * m_settings->optimalClasses[i + 1].minEfficiency );
      const int maxEff = (int)( 100 * m_settings->optimalClasses[i + 1].maxEfficiency );

      const int teamEff = team.HeroClasses().classes[i];
      const int reqEff = req->TotalClassEfficiency().classes[i];
      const int predictedEff = teamEff + reqEff;

      switch ( stage )
      {
      default:
        break;

      case ESweepStage::LowerLimit:
        if ( ( teamEff > minEff ) && ( reqEff > 0 ) )
          return false;
        break;

      case ESweepStage::UpperLimit:
        if ( predictedEff > maxEff )
          return false;
        break;

      case ESweepStage::WidenedLimits:
        if ( predictedEff > maxEff )
        {
          timer::Time effectiveWaitTime = team.EffectiveWaitTime( correctedWaitTime, req->Size() );
          const int excess = predictedEff - maxEff;
          int limitAtten = 100 * ( effectiveWaitTime / m_settings->heroClassLimitsAttenuationTime );
          if ( excess > limitAtten )
            return false;
        }
        break;
      }
    }

    return true;
  }



  bool RankMMakingLogic::CheckHeroClassesLowLimit( const TeamDraft & team )
  {
    NI_PROFILE_HEAVY_FUNCTION;

    for ( int i = 0; i < HeroClassesNumber; ++i )
    {
      const int minEff = (int)( 100 * m_settings->optimalClasses[i + 1].minEfficiency );
      const int teamEff = team.HeroClasses().classes[i];

      if ( teamEff >= minEff )
        continue;

      const int lack = minEff - teamEff;
      int limitAtten = 100 * ( team.EffectiveWaitTime() / m_settings->heroClassLimitsAttenuationTime );
      if ( lack > limitAtten )
        return false;
    }

    return true;
  }

  bool RankMMakingLogic::CheckLeaverBasket( TeamDraft teams[2])
  {
    NI_PROFILE_FUNCTION;

    if ( teams[0].Basket() != teams[1].Basket() )
      if ( teams[0].Basket() == EBasket::Leaver && teams[0].MinWait() >= m_settings->gameLeaversTimeTrashold) 
        return true;
      else if ( teams[1].Basket() == EBasket::Leaver && teams[1].MinWait() >= m_settings->gameLeaversTimeTrashold) 
        return true;
      else 
      { 
        if(teams[0].Basket() == EBasket::Undefined || teams[1].Basket() == EBasket::Undefined) 
          return true;

        return false;
      }
    else 
      return true; 

  }

  bool RankMMakingLogic::CheckRequestLeaverTeam( const TeamDraft& team, const MmRequest * req, timer::Time waitTime )
  {

    NI_PROFILE_FUNCTION;

    //Если корзина EBasket::Undefined видимо это первый запрос в эту команду
    if(team.Basket() == EBasket::Undefined) 
      return true;

    if ( req->Basket() == EBasket::Leaver) 
    {
      if (waitTime < m_settings->teamLeaversTimeTrashold )
      {
        if (team.Basket() == EBasket::Leaver)
          return true;
        else 
          return false;
      }
      else return true;
    }
    else if ( team.Basket() != EBasket::Leaver )
      return true;
    else return false;
  }

  bool RankMMakingLogic::CheckDonorConditions( TeamDraft teams[2], const GeolocationConstraints & geo )
  {
    NI_PROFILE_FUNCTION;
    if ( !geo.multipleLocales )
      return true;

    NI_ASSERT( geo.recipientSide >= 0, "" );

    const RankMMakingLogic::TeamDraft::TMembers & members = teams[geo.recipientSide].Members();
    timer::Time minWait = 0;
    int recipients = 0;
    for ( size_t i = 0; i < members.size(); ++i )
      if ( members[i]->Locale() == geo.sidesLocale[geo.recipientSide] )
      {
        timer::Time wait = m_now - members[i]->StartTime();
        if ( !recipients || ( wait < minWait ) )
          minWait = wait;
        recipients += members[i]->Size();
      }

      if ( !recipients )
        return false;

      NI_VERIFY( !m_settings->delayPerDonorLocalePlayer.empty(), "", return false );

      const int requiredDonors = m_teamSize - recipients;

      float delay = 0;
      if ( requiredDonors >= m_settings->delayPerDonorLocalePlayer.size() )
        delay = m_settings->delayPerDonorLocalePlayer.back();
      else
        delay = m_settings->delayPerDonorLocalePlayer[requiredDonors];

      return ( delay < minWait );
  }

  bool RankMMakingLogic::CheckRequestSide(  const TeamDraft & team, const MmRequest * req, timer::Time waitTime )
  {
    NI_PROFILE_FUNCTION;

    if (team.Faction() == lobby::ETeam::None)
      return true;

    if ( team.Faction() != req->CommonData().team) 
    {
      if (waitTime < m_settings->TeamSideTimeTreshold)
        return false;
      else
        return true;
    }
    else return true;
  }

  void RankMMakingLogic::ChangeSide(TeamDraft (&teams)[2])
  {
    NI_PROFILE_HEAVY_FUNCTION;
    int team1_players[2],team2_players[2];
    team1_players[0] = 0;
    team1_players[1] = 0;
    team2_players[0] = 0;
    team2_players[1] = 0;

    for (int i=0; i<2; i++)
    {
      TeamDraft::TMembers members = teams[i].Members();
      for(TeamDraft::TMembers::const_iterator it = members.begin(); it != members.end(); ++it)
      {
        MmRequest* req = (*it);
        switch (req->CommonData().team)
        {
        case lobby::ETeam::Team1:
          team1_players[i]+=req->Size();
          break;
        case lobby::ETeam::Team2:
          team2_players[i]+=req->Size();
          break;
        }
      }
      m_loger->Log( ELogLevel::Normal, "Team%d count (Faction 1, Faction 2): (%d,%d)",i+1,team1_players[i], team2_players[i]);
    }
    int ok_side = team1_players[0] + team2_players[1],
      bad_side = team2_players[0] + team1_players[1]; 
    if (ok_side < bad_side )
    {
      m_loger->Log( ELogLevel::Normal, "Sides are changed. Sides are OK for %d players, bad side for %d players", ok_side, bad_side );
      TeamDraft temp = teams[0];
      teams[0] = teams[1];
      teams[1] = temp;
    } 
    else
      m_loger->Log( ELogLevel::Normal, "Sides aren't changed. Sides are OK for %d players, bad side for %d players", ok_side, bad_side);

  }

  void RankMMakingLogic::OutputGame( const TeamDraft (&teams)[2], EBasket::Enum basket, bool dbgFullParty, const RankDescription * targetRank, const GeolocationConstraints & dbgGeo )
  {
    NI_PROFILE_FUNCTION;

    MMakingDraftGame game;
    game.Init( m_teamSize, basket, m_heroes );

    const char * fullPartyTag = "none";
    ++m_totalGames;
    if ( dbgFullParty )
      if ( ( teams[0].Size() == 1 ) && ( teams[1].Size() == 1 ) )
      {
        fullPartyTag = "full";
        ++m_fullPartyGames;
      }
      else
      {
        fullPartyTag = "mixed";
        ++m_fullPartyMixedGames;
      }

      if ( dbgGeo.multipleLocales )
        ++m_donorGames;

      for ( int t = 0; t < 2; ++t )
      {
        SHeroClassEfficiency classes;
        for ( size_t i = 0; i < teams[t].Members().size(); ++i )
        {
          StrongMT<MmRequest> req = teams[t].Members()[i];
          classes.Add( req->TotalClassEfficiency() );
          
          lobby::ETeam::Enum faction = lobby::ETeam::Index( (int)t );
          /*lobby::ETeam::Enum factionOverride = ( manoeuvresFaction == lobby::ETeam::None ) ? lobby::ETeam::None : faction;*/
          game.AddMembers( req, faction );
        }
        m_loger->Log( ELogLevel::Normal, "Team%d target rank '%s', hero classes %s", t + 1, targetRank->name.c_str(), classes.ToString().c_str() );
      }

      m_loger->Log( ELogLevel::Normal, "Game data.full_party=%s, locales=[%s%s, %s%s], location=%s", 
        fullPartyTag, 
        m_locales.Find( dbgGeo.sidesLocale[0] ), dbgGeo.multipleLocales ? ( dbgGeo.donorSide ? "(recipient)" : "(donor)" ) : "",
        m_locales.Find( dbgGeo.sidesLocale[1] ), dbgGeo.multipleLocales ? ( dbgGeo.donorSide ? "(donor)" : "(recipient)" ) : "",
        m_locations.Find( dbgGeo.location ) );

      game.AssignAutoHeroes();
      game.Check( m_mapType );

      PushResultingGame( game, mmaking::EDebugGameType::Normal );

      for ( int t = 0; t < 2; ++t )
      {
        for ( size_t i = 0; i < teams[t].Members().size(); ++i )
        {
          StrongMT<MmRequest> req = teams[t].Members()[i];
          DeleteRequest( req->RequestId() );
        }
      }
  }

  bool RankMMakingLogic::DeleteRequest( TRequestUId requestId  )
  {
    bool res = ProdLogicBase::DeleteRequest(requestId );

    if (res)
    {
      TRankRequestMap::iterator cit = m_rrequests.begin();

      for( ; cit!= m_rrequests.end(); ++cit  )
      {

        if (!cit->second.empty())
        {
          TRequestMap::iterator it = cit->second.find(requestId);
          if (it != cit->second.end())
          {
            m_MergedRankRequestsCount[cit->first] -= it->second->Size();
            cit->second.erase(it);
            return true;
          }
        }
      } 

      return false;
    }

    return res;
  }

} //namespace mmaking
