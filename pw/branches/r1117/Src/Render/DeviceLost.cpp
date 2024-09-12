#include "stdafx.h"
#include "DeviceLost.h"
#include "smartrenderer.h"
#include "System/MultiReaderLock.h"

namespace Render {

static threading::Mutex* mutexes = NULL;

static bool s_threaded_loading = true;

static volatile bool s_reset_requested = false;
static threading::MultiReaderLock s_reset_mutex;
static const int WAIT_TICKS = 10000;


inline DeviceLostHandler::Ring& DeviceLostHandler::GetHandlers(int _priority)
{
  static Ring theHandlers[DeviceLostHandler::HANDLERPRIORITY_COUNT];
  return theHandlers[_priority];
}


bool DeviceLostHandler::InitDeviceLostHandler()
{
  static threading::Mutex theMutexes[DeviceLostHandler::HANDLERPRIORITY_COUNT];

  mutexes = theMutexes;
  s_threaded_loading = NGlobal::GetVar( "render_threadsafe", 1 ).GetInt64();
  return true;
}

// This class do locks only when threaded loading is enabled
class LoadingMutexLock : public NonCopyable
{
  const threading::Mutex * mutex;

public:
  LoadingMutexLock(const threading::Mutex & _mutex)
  {
    if(s_threaded_loading)
    {
      mutex = &_mutex;
      mutex->Lock();
    }
    else
      mutex = 0;
  }

  ~LoadingMutexLock()
  {
    if(mutex)
      mutex->Unlock();
  }
};


void DeviceLostHandler::SelfRegister()
{
  static bool inited = InitDeviceLostHandler();

#ifdef _DEBUG
  static DWORD threadId = GetCurrentThreadId();
  if( threadId != GetCurrentThreadId() )
    threadId = threadId; // set breakpoint here if desirable
#endif // _DEBUG

  LoadingMutexLock lock(mutexes[priority]);
  GetHandlers(priority).addLast(this);
}

void DeviceLostHandler::UnRegister()
{
  LoadingMutexLock lock(mutexes[priority]);
  DeviceLostHandler::Ring::remove(this);
}


DeviceLostHandlerLoadable::LoaderCS::LoaderCS(volatile bool& _loadFinished)
: loadFinished(_loadFinished)
{
  //int i = WAIT_TICKS;
  //while(s_reset_requested) {
  //  if(--i < 0)
  //    break; // don't wait infinitely
  //  Sleep(0);
  //}

  s_reset_mutex.LockForRead();
}


DeviceLostHandlerLoadable::LoaderCS::~LoaderCS()
{
  s_reset_mutex.UnlockAfterRead();
  loadFinished = true;
}


void NotifyDeviceLost()
{
  DebugTrace("NotifyDeviceLost");
  
  s_reset_requested = true;
  threading::WriteLockGuard guard( s_reset_mutex );

  SmartRenderer::NullThePointers();

  for (int i = 0; i < DeviceLostHandler::HANDLERPRIORITY_COUNT; i++)
  {
    LoadingMutexLock lock(mutexes[i]);
    for(ring::Range<DeviceLostHandler::Ring> it(DeviceLostHandler::GetHandlers(i)); it; ++it)
      it->OnDeviceLost();
  }
}

void NotifyDeviceReset()
{
  {
    DebugTrace("NotifyDeviceReset");
    
    threading::WriteLockGuard guard( s_reset_mutex );
  
    for (int i = 0; i < DeviceLostHandler::HANDLERPRIORITY_COUNT; i++)
    {
      LoadingMutexLock lock(mutexes[i]);
      for(ring::Range<DeviceLostHandler::Ring> it(DeviceLostHandler::GetHandlers(i)); it; ++it)
      {
        ASSERT(it.operator->());
        it->OnDeviceReset();
      }
    }
  }
  s_reset_requested = false;
}

//////////////////////////////////////////////////////////////////////////

static DeviceDeleteHandler::Ring* ddHandlers = NULL;
static threading::Mutex* ddMutexes = NULL;

bool InitDeviceDeleteHandler()
{
  static DeviceDeleteHandler::Ring theHandlers[DeviceLostHandler::HANDLERPRIORITY_COUNT];
  static threading::Mutex theMutexes[DeviceLostHandler::HANDLERPRIORITY_COUNT];

  ddHandlers = theHandlers;
  ddMutexes = theMutexes;
  s_threaded_loading = NGlobal::GetVar( "render_threadsafe", 1 ).GetInt64();
  return true;
}

DeviceDeleteHandler::DeviceDeleteHandler(HandlerPriority p /*= HANDLERPRIORITY_NORMAL*/)
: priority(p)
{
  static bool inited = InitDeviceDeleteHandler();

  LoadingMutexLock lock(ddMutexes[p]);
  ddHandlers[p].addLast(this);
}

DeviceDeleteHandler::~DeviceDeleteHandler()
{
  LoadingMutexLock lock(ddMutexes[priority]);
  DeviceDeleteHandler::Ring::remove(this);
}

void DeviceDeleteHandler::NotifyDeviceCreate()
{
  DebugTrace("NotifyDeviceCreate");
  
  for(int i = 0; i < DeviceDeleteHandler::HANDLERPRIORITY_COUNT; i++)
  {
    LoadingMutexLock lock(ddMutexes[i]);
    for(ring::Range<DeviceDeleteHandler::Ring> it( ddHandlers[i] ); it; ++it)
      it->OnDeviceCreate();
  }
}

void DeviceDeleteHandler::NotifyDeviceDelete()
{
  DebugTrace("NotifyDeviceDelete");
  
  for(int i = DeviceDeleteHandler::HANDLERPRIORITY_COUNT; --i >= 0;)
  {
    LoadingMutexLock lock(ddMutexes[i]);
    for(ring::Range<DeviceDeleteHandler::Ring> it( ddHandlers[i] ); it; ++it)
      it->OnDeviceDelete();
  }
}

} // namespace Render

// end of DeviceLost.cpp
