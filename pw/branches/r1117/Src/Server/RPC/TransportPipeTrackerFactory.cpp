#include "stdafx.h"
#include "TransportPipeTrafficTracker.h"
#include "TransportPipeTrackerFactory.h"

namespace rpc
{

TransportPipeTrafficTrackerFactory::TransportPipeTrafficTrackerFactory(Transport::TServiceId const & tracksvcls, 
                                                                       Transport::TServiceId const & homesvcid,
                                                                       unsigned int trackGameSessionRpcClass,
                                                                       int trackGameSessionRpcMethodIdx,
                                                                       unsigned int trackGameSessionStepPeriodThreshold)
  :tracksvcls_(tracksvcls),
  homesvcid_(homesvcid),
  trackGameSessionRpcClass_(trackGameSessionRpcClass),
  trackGameSessionRpcMethodIdx_(trackGameSessionRpcMethodIdx),
  trackGameSessionStepPeriodThreshold_(trackGameSessionStepPeriodThreshold)
{
}

TransportPipeTrafficTrackerFactory::~TransportPipeTrafficTrackerFactory()
{
}

StrongMT<TransportPipeTrafficTracker> TransportPipeTrafficTrackerFactory::CreateTrafficTracker()
{
  if (!trackGameSessionStepPeriodThreshold_)
    return 0;

  if (!logholder_)
    return 0;

  StrongMT<TransportPipeTrafficTracker> tt(new TransportPipeTrafficTracker(logholder_, 
    trackGameSessionRpcClass_, trackGameSessionRpcMethodIdx_, trackGameSessionStepPeriodThreshold_));
  return tt;
}

void TransportPipeTrafficTrackerFactory::DestroyTrafficTracker(StrongMT<TransportPipeTrafficTracker> const & itt)
{
}

StrongMT<TransportPipeTrafficTrackerFactory> TransportPipeTrafficTrackerFactory::CloneFactory(Transport::TServiceId const & tracksvcid)
{
  if (!trackGameSessionStepPeriodThreshold_)
    return 0;

  int idx = Transport::GetServerIndex(tracksvcid);
  if (idx < 0)
  {
    return 0;
  }

  Transport::TServiceId svcls;
  Transport::GetServiceClass(tracksvcid, svcls);

  if (svcls != tracksvcls_)
  {
    return 0;
  }

  StrongMT<TransportPipeTrafficTrackerFactory> ttf = new TransportPipeTrafficTrackerFactory(tracksvcls_, homesvcid_,
    trackGameSessionRpcClass_, trackGameSessionRpcMethodIdx_, trackGameSessionStepPeriodThreshold_);
  ttf->cloneInit_(ttf, idx);
  return ttf;
}

int TransportPipeTrafficTrackerFactory::cloneInit_( TransportPipeTrafficTrackerFactory * ttf, int tracksvcidx)
{
  ttf->tracksvcidx_ = tracksvcidx;

  //  init logging
  Transport::TServiceId homesvcls;
  Transport::GetServiceClass(homesvcid_, homesvcls);
  int homesvcidx = Transport::GetServerIndex(homesvcid_);
  nstl::string logFilePostfix;
  logFilePostfix.assign(NStr::StrFmt("%s_%d_%s_%d", homesvcls.c_str(), homesvcidx, tracksvcls_.c_str(), tracksvcidx));

  NLogg::CChannelLogger* logStream = new NLogg::CChannelLogger( logFilePostfix.c_str() );
  StrongMT<NLogg::BasicTextFileDumper> logDumper = NLogg::BasicTextFileDumper::New( logStream, logFilePostfix.c_str() );
  ttf->logholder_ = new NLogg::StreamHolder(logStream, logDumper);

  return 0;
}

}
