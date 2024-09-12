#ifndef RATINGSORTMMWORKER_H_INCLUDED
#define RATINGSORTMMWORKER_H_INCLUDED

#include "RatingSortMmJob.h"
#include "System/JobThread.h"
#include <vector>


namespace mmaking
{


/////////
//AHTUNG: It is supposed that this class will be interfaced from SINGLE THREAD ONLY
/////////
class RatingSortWorker : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RatingSortWorker, BaseObjectMT );

public:
  RatingSortWorker( unsigned threadsNumber );
  ~RatingSortWorker();

  size_t SlotsNumber() const { return workerThreads.size(); }

  void Start();
  void AddJob( RatingSortJob * job );
  bool WaitAll( unsigned timeout );

private:
  class WorkerThread;
  enum EMode { ModeIdle, ModeWorking, ModeWaiting };

  EMode                                         mode;
  std::vector<StrongMT<threading::JobThread>>   threadObjects;
  std::vector<StrongMT<WorkerThread>>           workerThreads;
  std::vector<HANDLE>                           completeEvents;
  size_t                                        activeJobNumber;
};

} //namespace mmaking

#endif //RATINGSORTMMWORKER_H_INCLUDED
