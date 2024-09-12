#include "stdafx.h"
#include "RpcThreadPool.h"
#include "RpcNode.h"


namespace rpc 
{

uint WorkerThreadProcessor::Process(volatile bool& isRunning)
{
  threading::SetDebugThreadName( "RPC Worker" );

  while (isRunning)
  {
    info.Wait();
    Node* node = 0;
    if (info.RetrieveNode(node))
    {
      info.FinishProcessing(node, node->Poll());
    }
  }
  return 0;
}



ThreadPool::ThreadPool(int _threadCount):
dataRecieved(0x0FFFFFFF),
processingFinished(0x0FFFFFFF)
{
  for (int i=0;i<_threadCount;++i)
  {
    XWorkerThread* t = new XWorkerThread(dataRecieved, processingFinished, queue, corruptedNodes);
    threads.push_back(t);
  }
}



ThreadPool::~ThreadPool()
{
  for (int i=0;i<threads.size();++i)
  {
    threads[i]->Stop(false);
  }
  dataRecieved.Signal(threads.size());
  for (int i=0;i<threads.size();++i)
  {
    threads[i]->Stop(true);
    delete threads[i];
  }
}

} // rpc
