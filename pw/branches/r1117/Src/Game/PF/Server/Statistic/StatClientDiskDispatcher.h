#ifndef STATCLIENTDISKDISPATCHER_H_INCLUDED
#define STATCLIENTDISKDISPATCHER_H_INCLUDED

#include "StatClientHttpDispatcher.h"

namespace StatisticService
{

class ClientDiskDispatcher : public ClientHttpDispatcher
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClientDiskDispatcher, ClientHttpDispatcher );

public:
  ClientDiskDispatcher();

protected:
  //IStatDataDispatcher
  virtual bool DispatchChunk( const TMessageData & _data, unsigned _msgNumber );

private:
  string destFolder;
};

} //namespace StatisticService

#endif STATCLIENTDISKDISPATCHER_H_INCLUDED
