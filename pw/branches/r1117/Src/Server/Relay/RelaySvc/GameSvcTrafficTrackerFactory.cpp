#include "stdafx.h"
#include "GameSvcTrafficTracker.h"
#include "GameSvcTrafficTrackerFactory.h"
#include "RelayServer2Cfg.h"

namespace Relay
{

GameSvcTrafficTrackerFactory::GameSvcTrafficTrackerFactory(Transport::TServiceId const & tracksvcls, 
                                                           Transport::TServiceId const & relaysvcid)
  :tracksvcls_(tracksvcls),
  relaysvcid_(relaysvcid)
{
}

GameSvcTrafficTrackerFactory::~GameSvcTrafficTrackerFactory()
{
}

StrongMT<ITrafficTracker> GameSvcTrafficTrackerFactory::CreateTrafficTracker()
{
  if (!logholder_)
    return 0;

  StrongMT<GameSvcTrafficTracker> tt(new GameSvcTrafficTracker(logholder_, 
    RelayServer2Cfg::GetTrackGameSessionRpcClass(), RelayServer2Cfg::GetTrackGameSessionRpcMethodIdx(),
    RelayServer2Cfg::GetTrackGameSessionStepPeriodThreshold()));
  return StrongMT<ITrafficTracker>(tt);
}

void GameSvcTrafficTrackerFactory::DestroyTrafficTracker(StrongMT<ITrafficTracker> const & itt)
{
}

StrongMT<ITrafficTrackerFactory> GameSvcTrafficTrackerFactory::CloneFactory(Transport::TServiceId const & tracksvcid)
{
  int idx = Transport::GetServerIndex(tracksvcid);
  if (idx < 0)
  {
    return 0;
  }

  Transport::TServiceId svcls;
  Transport::GetServiceClass(tracksvcid, svcls);
  NI_ASSERT(svcls == tracksvcls_.c_str(), "");
  if (svcls != tracksvcls_)
  {
    return 0;
  }

  StrongMT<GameSvcTrafficTrackerFactory> ttf = new GameSvcTrafficTrackerFactory(tracksvcls_, relaysvcid_);
  ttf->cloneInit_(ttf, idx);

  return StrongMT<ITrafficTrackerFactory>(ttf);
}

int GameSvcTrafficTrackerFactory::cloneInit_(StrongMT<GameSvcTrafficTrackerFactory> const & ttf, int tracksvcidx)
{
  ttf->tracksvcidx_ = tracksvcidx;

  //  init logging
  int relaysvcidx = Transport::GetServerIndex(relaysvcid_);
  nstl::string logFilePostfix;
  logFilePostfix.assign(NStr::StrFmt("%s_%d_%s_%d", "relay", relaysvcidx, tracksvcls_.c_str(), tracksvcidx));

  NLogg::CChannelLogger* logStream = new NLogg::CChannelLogger( logFilePostfix.c_str() );
  NLogg::BasicTextFileDumper* logDumper = NLogg::BasicTextFileDumper::New( logStream, logFilePostfix.c_str() );

  ttf->logholder_ = new NLogg::StreamHolder(logStream, logDumper);

  return 0;
}

}
