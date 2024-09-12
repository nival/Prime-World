#include "CensorAsyncManager.h"
#include "Censor.h"
#include <process.h>
#include <System/sleep.h>

#define WORKERS_COUNT 4

namespace CensorFilter
{

  static void WorkThread(void* manager)
  {
    CensorAsyncManager* pManager = (CensorAsyncManager*)manager;

    TTextData message;
    TMessagesQueue& messagesQueue = pManager->GetIncomingQueue();
    TMessagesQueue& filteredQueue = pManager->GetFiltered();
    Censor* pCensor = pManager->GetCensor();

    while(pManager->IsRunning())
    {
#ifdef USE_LOCK_FREE
      if (messagesQueue.dequeue(message))
#else
      if (messagesQueue.get(message))
#endif
      {
        pCensor->FilterThreadSafe(&message.second[0]);
#ifdef USE_LOCK_FREE
        filteredQueue.enqueue( std::make_pair(message.first, message.second) );
#else
        filteredQueue.add( std::make_pair(message.first, message.second) );
#endif
      }

      nival::sleep(20);
    }
  }

  CensorAsyncManager::CensorAsyncManager( Censor* censorPtr ) : 
    pCensor(censorPtr), 
    isRunning(true),
    lastId(0)
  {
    for(int numWorkers = 0; numWorkers < WORKERS_COUNT; numWorkers++)
      workers.push_back( (HANDLE)_beginthread( &WorkThread, 0, this ) );
  }

  CensorAsyncManager::~CensorAsyncManager()
  {
  }

  int CensorAsyncManager::FilterMessageAsync( const std::wstring& message )
  {
    lastId++;
#ifdef USE_LOCK_FREE
    incomingMessages.enqueue( std::make_pair(lastId, message) );
#else
    incomingMessages.add( std::make_pair(lastId, message) );
#endif
    return lastId;
  }

  int CensorAsyncManager::GetFilteredMessage( int& messageId, wchar_t* text, size_t size  )
  {
    TTextData message;
#ifdef USE_LOCK_FREE
    bool res = filteredMessages.dequeue(message);
#else
    bool res = filteredMessages.get(message);
#endif
    if (res)
    {
      messageId = message.first;
      size_t _size = message.second.size();
      _size = size > _size ? _size : size-1;
      wmemcpy(text, message.second.c_str(), _size);
      text[_size] = 0;
      return _size;
    }

    return 0;
  }

  void CensorAsyncManager::Stop()
  {
    isRunning = false; 


    for ( std::vector<HANDLE>::iterator it = workers.begin(); it != workers.end(); ++it )
    {
      if ( WaitForSingleObject(*it,1000) != WAIT_OBJECT_0 )
        TerminateThread(*it, 0);
    }
  }


}