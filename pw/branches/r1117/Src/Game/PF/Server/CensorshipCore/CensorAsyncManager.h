#ifndef CENSORASYNCMANAGER_H_A2715FA5_BF
#define CENSORASYNCMANAGER_H_A2715FA5_BF

#include <System/LockFreeQueue.h>
#include <System/SyncPrimitives.h>
#include <deque>
#include <vector>
#include <map>

//#define USE_LOCK_FREE

namespace CensorFilter
{
  class Censor;

  template< class T >
  class ConcurentDequeue
  {
    threading::Mutex m_mutex;
    std::deque<T> m_queue;

  public:
    bool add(const T& message)
    {
      threading::MutexLock lock(m_mutex);

      m_queue.push_back(message);
      return true;
    }

    bool get(T& message)
    {
      threading::MutexLock lock(m_mutex);
      if (!m_queue.size())
      {
        return false;
      }
      message = m_queue.front();
      m_queue.pop_front();
      return true;
    }
  };

  typedef std::pair<int, std::wstring> TTextData;
#ifdef USE_LOCK_FREE
  typedef nstl::LockFreeQueue< TTextData > TMessagesQueue;
#else
  typedef ConcurentDequeue< TTextData > TMessagesQueue;
#endif
  //

class CensorAsyncManager
{
public:
  CensorAsyncManager(Censor* censorPtr);
  ~CensorAsyncManager();

  int FilterMessageAsync( const std::wstring& message );
  int GetFilteredMessage( int& messageId, wchar_t* text, size_t size );
  
  bool IsRunning() { return isRunning; }
  Censor* GetCensor() { return pCensor; }
  
  TMessagesQueue& GetIncomingQueue() { return incomingMessages; }
  TMessagesQueue& GetFiltered() { return filteredMessages; }

  void Stop();

private:
  Censor*               pCensor;
  TMessagesQueue        incomingMessages;
  TMessagesQueue        filteredMessages;
  volatile bool         isRunning;
  int                   lastId;
  
  std::vector<HANDLE>   workers;

};
}

#endif //#define CENSORASYNCMANAGER_H_A2715FA5_BF