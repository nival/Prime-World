#pragma once

#include "Interfaces.h"

namespace rpc
{

struct Stack
{
  Stack(int initialSize=256)
  {
    buffer.resize(initialSize);
    Reset();
  }

  int Stop()
  {
    char* v = EnsureSize(sizeof(VArgList));
    if (v)
    {
#if defined( NV_WIN_PLATFORM )
      va_end(v);
#endif
    } 
    else
    {
      result = false;
    }
    return size;
  }


  template <typename T>
  void Push(const T& value)
  {
    char* v = EnsureSize(sizeof(T));
    if (v)
    {
      VArgList d = VArgList(v);
      _mng_va_arg(d, T) = value;
      size += ((char*)d-v);
    } 
    else
    {
      result = false;
    }
  }

  void Push(const void* data, int dsize)
  {
    char* v = EnsureSize(dsize);
    if (v)
    {
      crt::memcpy(v, buffer.size()-size, data, dsize);  
      size += dsize;
    } else
    {
      result = false;
    }
  }

  template <typename P> 
  void Push()
  {
    char* v = EnsureSize(sizeof(P));
    if (v)
    {
      crt::memset(v, 0, sizeof(P));
    } 
    else
    {
      result = false;
    }
  }

  bool IsOk() const { return result; } 

  template <typename T>
  T& Pop()
  {
    char* stack = buffer.begin()+index;;
    T& result = _mng_va_arg(stack, T);
    index += (stack-buffer.begin());
    return result;
  }
  
  void Reset()
  {
    crt::memset(&buffer[0], 0, buffer.size());
    size = 0;
    result = true;
    index = 0;
  }

  VArgList GetStack()
  {
    return VArgList(&buffer[0]); 
  }
private:
  char* EnsureSize(int asize)
  {
    int delta = size+asize-buffer.size();
    if (delta > 0)
    {
      static const int MAX_STACK_SIZE = 64*1024;
      int newSize = buffer.size()+delta;
      if (newSize <= MAX_STACK_SIZE)
      {
        buffer.resize(newSize);
      }
      else
      {
        return 0;
      }
    }
    return &buffer[size];
  }
  int index;
  bool result;
  int size;
  nstl::vector<char> buffer;
};


struct MethodCallStack
{
  VArgList buffer;
  int size;
  bool isValid;
  uint methodCode;
};

MethodCallStack FillStack(const MethodCallHeader& call, rpc::Arguments& args, const byte* paramsData, uint _paramsSize, const rpc::MethodInfo& minfo);

template <class T, class R, class P0>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0 p ), bool& result) 
{
  if (stack.size < sizeof(P0))
  {
    result = false;
  }

  return (object->*func)(_mng_va_arg(stack.buffer, P0));
}

template <class T, class R, class P0, class P1>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  return (object->*func)(p0, p1);
}

template <class T, class R>
R VCall(MethodCallStack& stack, T* object, R (T::*func) () const , bool& result)
{
  if (stack.size > 0)
  {
    result = false;
  }
  return (object->*func)();
}


template <class T, class R>
R VCall(MethodCallStack& stack, T* object, R (T::*func)(), bool& result)
{
  if (stack.size > 0)
  {
    result = false;
  }
  return (object->*func)();
}


template <typename T, class R, typename P0, typename P1, typename P2>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  return (object->*func)(p0, p1, p2);
}

template <typename T, class R, typename P0, typename P1, typename P2, typename P3>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2, P3 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2)+sizeof(P3))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  P3 p3 = _mng_va_arg(stack.buffer, P3);
  return (object->*func)(p0, p1, p2, p3);
}

template <typename T, class R, typename P0, typename P1, typename P2, typename P3, typename P4>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2, P3, P4 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2)+sizeof(P3)+sizeof(P4))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  P3 p3 = _mng_va_arg(stack.buffer, P3);
  P4 p4 = _mng_va_arg(stack.buffer, P4);
  return (object->*func)(p0, p1, p2, p3, p4);
}

template <typename T, class R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2, P3, P4, P5 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2)+sizeof(P3)+sizeof(P4)+sizeof(P5))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  P3 p3 = _mng_va_arg(stack.buffer, P3);
  P4 p4 = _mng_va_arg(stack.buffer, P4);
  P5 p5 = _mng_va_arg(stack.buffer, P5);
  return (object->*func)(p0, p1, p2, p3, p4, p5);
}

template <typename T, class R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2, P3, P4, P5, P6 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2)+sizeof(P3)+sizeof(P4)+sizeof(P5)+sizeof(P6))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  P3 p3 = _mng_va_arg(stack.buffer, P3);
  P4 p4 = _mng_va_arg(stack.buffer, P4);
  P5 p5 = _mng_va_arg(stack.buffer, P5);
  P6 p6 = _mng_va_arg(stack.buffer, P6);
  return (object->*func)(p0, p1, p2, p3, p4, p5, p6);
}

template <typename T, class R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
R VCall(MethodCallStack& stack, T* object, R (T::*func)( P0, P1, P2, P3, P4, P5, P6, P7 ), bool& result)
{
  if (stack.size < sizeof(P0)+sizeof(P1)+sizeof(P2)+sizeof(P3)+sizeof(P4)+sizeof(P5)+sizeof(P6)+sizeof(P7))
  {
    result = false;
  }
  P0 p0 = _mng_va_arg(stack.buffer, P0);
  P1 p1 = _mng_va_arg(stack.buffer, P1);
  P2 p2 = _mng_va_arg(stack.buffer, P2);
  P3 p3 = _mng_va_arg(stack.buffer, P3);
  P4 p4 = _mng_va_arg(stack.buffer, P4);
  P5 p5 = _mng_va_arg(stack.buffer, P5);
  P6 p6 = _mng_va_arg(stack.buffer, P6);
  P7 p7 = _mng_va_arg(stack.buffer, P7);
  return (object->*func)(p0, p1, p2, p3, p4, p5, p6, p7);
}

_interface CppCallRoutine : public ICallRoutine
{
  virtual bool Process(const char* stack, int newSize)=0;
  virtual bool ProcessReturnValue(const MethodCallHeader& methodCall, const byte* paramsData, int _paramsSize, rpc::Arguments& args);
};

class SyncCallRoutine : public CppCallRoutine
{
public:
  SyncCallRoutine():
  event(false, false)
  {
  }

  virtual bool Process(const char* stack, int newSize)
  {
    if (newSize > data.size()) 
    {
      data.resize(newSize);
    }
    crt::memcpy(get(), size, stack, newSize);
    event.Set();
    return true;
  }

  void OnFailure(rpc::CallStatus status) {}

  virtual VArgList Wait()
  {
    event.Wait();
    VArgList v = VArgList(get());
    return v;
  }

  threading::Event& getEvent() { return event; }
private:
  char* get() { return &data[0]; } 

  nstl::vector<char> data;
  uint size;
  threading::Event event;
};

class AsyncCallRoutine : public CppCallRoutine
{
public:

  AsyncCallRoutine(IFunctor* functor):
  functor(functor)
  {
  }
  ~AsyncCallRoutine()
  {
    delete functor;
    functor = 0;
  }

  virtual bool Process(const char* stack, int /*newSize*/)
  {
    bool result = functor->Call(VArgList(stack));
    delete functor;
    functor = 0;
    return result;
  }

  void OnFailure(rpc::CallStatus status)
  {
    functor->OnFailure(status);
  }
private:
  IFunctor* functor;
};

} // rpc