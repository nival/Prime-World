#pragma once

#include "System/ThreadNames.h"
#include <System/ThreadHelpers.h>

namespace rpc
{

class Node;

struct WorkingNodes
{
  int size() const { return nodes.size(); }
  Node* operator [] (int index) { return nodes[index]; }
  void push_back(Node* node)
  {
    threading::MutexLock lock (m);
    nodes.push_back(node);
  }
  void clear()
  {
    nodes.clear();
  }
  nstl::vector<Node*> nodes;
  threading::Mutex m;
};



template <typename T>
struct Queue
{
  Queue(int maxSize=0)
  {
    items.reserve(maxSize);
  }
  void enqueue(const T& value)
  {
    threading::MutexLock lock(m);
    items.push_back(value);
  }
  int size() const 
  {
    threading::MutexLock lock(m);
    return items.size();
  }

  bool dequeue(T& value)
  {
    threading::MutexLock lock(m);
    if (items.size() > 0)
    {
      value = items[0];
      items.erase(items.begin());
      return true;
    }
    return false;
  }
  threading::Mutex m;
  nstl::vector<T> items;
};



typedef Queue<Node*> NodesQueue;



struct WorkerInfo : NonCopyable
{
  WorkerInfo(
    threading::Semaphore& _dataRecieved, 
    threading::Semaphore& _processingFinished,
    NodesQueue& _queue,    
    WorkingNodes& _corruptedNodes):
  dataRecieved(_dataRecieved),
  processingFinished(_processingFinished),
  queue(_queue),
  corruptedNodes(_corruptedNodes)
  {
  }

  void Wait() 
  { 
    dataRecieved.Wait();
  }

  void FinishProcessing(rpc::Node* node, bool _result)  
  {
    nodeResult = _result;
    if (!nodeResult)
    {
      corruptedNodes.push_back(node);
    }
    processingFinished.Signal();
  }
  bool GetResult() const { return  nodeResult; }
  bool RetrieveNode(Node*& t) { return queue.dequeue(t); }
private:
  bool nodeResult;
  threading::Semaphore& dataRecieved;
  threading::Semaphore& processingFinished;
  WorkingNodes& corruptedNodes;
  NodesQueue& queue;    
};



struct WorkerThreadProcessor : NonCopyable
{
  WorkerThreadProcessor(WorkerInfo& _info):
  info(_info)
  {
  }

  virtual uint Process(volatile bool& isRunning);

private:
  WorkerInfo& info;
};



typedef threading::ProcessingThread<WorkerThreadProcessor> ProcessingWorkerThread;
class XWorkerThread
{
public:
  XWorkerThread(threading::Semaphore& _dataRecieved, threading::Semaphore& _processingFinished, NodesQueue& queue, WorkingNodes& _corruptedNodes):
  info(_dataRecieved, _processingFinished, queue, _corruptedNodes),
  wt(info),
  t(wt)
  {
    t.Resume();
  }

  void Stop(bool waitForStop)
  {
    t.Stop(waitForStop);
  }

  WorkerInfo info;
  WorkerThreadProcessor wt;
  ProcessingWorkerThread t;
};



class ThreadPool
{
public:
  ThreadPool(int threadsCount);
  ~ThreadPool();

  threading::Semaphore dataRecieved;
  threading::Semaphore processingFinished;
  nstl::vector<XWorkerThread*> threads;
  WorkingNodes corruptedNodes;
  NodesQueue queue;
};

} // rpc
