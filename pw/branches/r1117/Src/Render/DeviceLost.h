#pragma once
#ifndef _DEVICELOST_H_
#define _DEVICELOST_H_

#include "../System/noncopyable.h"

#ifdef _DEBUG
  #define _CHECK_DLH_WRAPPED_
#endif // _DEBUG

#ifdef _CHECK_DLH_WRAPPED_
  #define SELF_REGISTER DeviceLostHandler::isWrapped = true; DeviceLostHandler::SelfRegister();
  #define DLH_CHECK(arg) arg
#else
  #define SELF_REGISTER DeviceLostHandler::SelfRegister();
  #define DLH_CHECK(arg)
#endif // _CHECK_DLH_WRAPPED_

#define COMMA ,


namespace Render {

struct DeviceLostHandler : NonCopyable
{
  enum HandlerPriority { HANDLERPRIORITY_HIGH, HANDLERPRIORITY_NORMAL, HANDLERPRIORITY_LOW, HANDLERPRIORITY_SUPER_LOW, HANDLERPRIORITY_COUNT };

  virtual void OnDeviceLost() = 0;
  virtual void OnDeviceReset() = 0;

  virtual ~DeviceLostHandler() {
    DLH_CHECK( NI_ASSERT(isWrapped, "All DeviceLostHandler descendants MUST be wrapped with DeviceLostWrapper!") )
  }

protected:
  explicit DeviceLostHandler(HandlerPriority p = HANDLERPRIORITY_NORMAL) : priority(p) DLH_CHECK( COMMA isWrapped(false) ) {}

private:
  seDECLARE_RING(DeviceLostHandler, ringPart, Ring);

  static Ring& GetHandlers(int _priority);

  friend void NotifyDeviceLost();
  friend void NotifyDeviceReset();
  template<class T> friend struct DeviceLostWrapper;

  void SelfRegister();
  void UnRegister();

  HandlerPriority priority;

  DLH_CHECK( bool isWrapped; )

  static bool InitDeviceLostHandler();
};


// specialized version for objects, that are loaded in other thread
struct DeviceLostHandlerLoadable : DeviceLostHandler
{
  class LoaderCS : NonCopyable // Auto-locker (critical section)
  {
    volatile bool& loadFinished;

  public:
    LoaderCS(volatile bool& _loadFinished); // should be called before any D3DPOOL_DEFAULT resources use at load
    ~LoaderCS();   // should be called after load finalization
  };

protected:
  volatile bool loadFinished;

  explicit DeviceLostHandlerLoadable(HandlerPriority p = HANDLERPRIORITY_NORMAL) : DeviceLostHandler(p), loadFinished(false) {}

  friend class LoaderCS;
};


template<class T>
struct DeviceLostWrapper : public T
{
  DeviceLostWrapper() { SELF_REGISTER }

  template<class T1>
  DeviceLostWrapper(T1 *_arg1) : T(_arg1) { SELF_REGISTER }

  template<class T1>
  DeviceLostWrapper(const T1& _arg1) : T(_arg1) { SELF_REGISTER }

  template<class T1, class T2>
  DeviceLostWrapper(T1 *_arg1, const T2& _arg2) : T(_arg1, _arg2) { SELF_REGISTER }

  template<class T1, class T2>
  DeviceLostWrapper(const T1& _arg1, const T2& _arg2) : T(_arg1, _arg2) { SELF_REGISTER }

  template<class T1, class T2, class T3>
  DeviceLostWrapper(const T1& _arg1, const T2& _arg2, const T3& _arg3) : T(_arg1, _arg2, _arg3) { SELF_REGISTER }

  virtual ~DeviceLostWrapper() { DeviceLostHandler::UnRegister(); }
};


typedef char (&DLH_tag)[2];
DLH_tag ClassSelectorFunction(DeviceLostHandler*);

void NotifyDeviceLost();
void NotifyDeviceReset();

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeviceDeleteHandler : NonCopyable
{
  enum HandlerPriority { HANDLERPRIORITY_HIGH, HANDLERPRIORITY_NORMAL, HANDLERPRIORITY_LOW, HANDLERPRIORITY_SUPER_LOW, HANDLERPRIORITY_COUNT };

  explicit DeviceDeleteHandler(HandlerPriority p = HANDLERPRIORITY_NORMAL);
  virtual ~DeviceDeleteHandler();

  virtual void OnDeviceDelete() = 0;
  virtual void OnDeviceCreate() {} // As most resources need special care to create them, it is acceptable to leave this method without override

  seDECLARE_RING(DeviceDeleteHandler, ringPart, Ring);

  // WARNING - unlike DeviceLostHandler, DeviceDeleteHandler processes priorities in FILO order
  static void NotifyDeviceDelete();
  static void NotifyDeviceCreate();

private:
  HandlerPriority priority;
};

} // namespace Render

template<class T> struct CreateHelper<sizeof(Render::DLH_tag), T> : CreateHelpersHelper< Render::DeviceLostWrapper<T> > {};

#endif /* _DEVICELOST_H_ */
