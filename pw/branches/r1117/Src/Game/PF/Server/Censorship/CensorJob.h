#ifndef CENSORJOB_H_INCLUDED
#define CENSORJOB_H_INCLUDED

#include "ICensorClient.h"
#include "Server/WebClient/WebClient.h"


namespace censorship
{

class CheckJob : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( CheckJob, BaseObjectMT );

public:
  CheckJob( Settings * _sett, timer::Time _now, TRequestId _reqId, TAuxId _auxId, ICensorClientCallback * _callback, const wstring & _text ) :
  sett( _sett ),
  creationTime( _now ),
  requestId( _reqId ),
  auxId( _auxId ),
  callback( _callback ),
  sourceText( _text ),
  result( ECheckResult::SvcFailure ),
  triesNumber( 0 )
  {}

  timer::Time CreationTime() const { return creationTime; }
  TRequestId RequestId() const { return requestId; }
  TAuxId AuxId() const { return auxId; }
  const wstring & NewText() const { return newText; }
  ECheckResult::Enum Result() const { return result; }
  unsigned TriesNumber() const { return triesNumber; }

  bool Perform( webClient::IHttpClient * httpClient );

  void Finish();

private:
  StrongMT<Settings>  sett;
  const timer::Time   creationTime;
  const TRequestId    requestId;

  const TAuxId        auxId;
  WeakMT<ICensorClientCallback> callback;
  wstring             sourceText;
  wstring             newText;
  ECheckResult::Enum  result;
  unsigned            triesNumber;
};

} //namespace censorship

#endif //CENSORJOB_H_INCLUDED
