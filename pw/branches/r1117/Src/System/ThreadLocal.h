#ifndef THREADLOCAL_H_1F14A519_37C9_47B5
#define THREADLOCAL_H_1F14A519_37C9_47B5

#include "Thread.h"
#if defined( NV_LINUX_PLATFORM )
#include <pthread.h>
#endif

#pragma warning(push)
//#pragma warning(disable:4346)

class GetOSClass
{
public:
  enum OSType
  {
    WINXP,
    WIN2000,
    WIN2003,
    VISTA,
    WINME,
    WIN98,
    WIN95,
    WINNT,
    LINUX,
    OS_LAST
  } ;
  GetOSClass();
  unsigned int GetMaxTls() const;
private:
  OSType tType;
};

GetOSClass const *GetOSClassType();

template <typename T>
class ThreadLocal
{
private:

  template<typename _Tp, _Tp __v> struct integral_constant
  {
    static const _Tp                      value = __v;
    typedef _Tp                           value_type;
    typedef integral_constant<_Tp, __v>   type;
  };
  typedef integral_constant<bool, true>     true_type;
  typedef integral_constant<bool, false>    false_type;
  
  template<typename _Tp> struct is_array: public false_type { };
  template<typename _Tp, std::size_t _Size> struct is_array<_Tp[_Size]>: public true_type { };
  template<typename _Tp> struct is_array<_Tp[]>: public true_type { };


  template< typename T2 > struct ThreadBuffer {

    seDECLARE_RING_T(ThreadBuffer, ringPart, Ring);
    T2 *data;
    ThreadBuffer(): data(NULL) {}
    ThreadBuffer(T2 *_data): data(_data) {}
    ~ThreadBuffer() 
    {
      if(data)
      {
        if(is_array< T2 >::value)
        {
          delete [] data;
        }
        else
        {
          delete data;
        }
      }
      data = NULL;
    }
  };

#if defined( NV_WIN_PLATFORM )
  DWORD                           threadLocalIndex;
#elif defined( NV_LINUX_PLATFORM )
  pthread_key_t                   threadLocalIndex;
#endif
  threading::Mutex                section;
  typename ThreadBuffer<T>::Ring  allocatedBuffers;

	ThreadLocal(ThreadLocal const&);

	ThreadBuffer<T> *GetPointer(void)
	{
#if defined( NV_WIN_PLATFORM )
    ThreadBuffer<T> * pBuff = static_cast<ThreadBuffer<T> *>(::TlsGetValue(this->threadLocalIndex));
#elif defined( NV_LINUX_PLATFORM )
    ThreadBuffer<T> * pBuff = static_cast<ThreadBuffer<T> *>(::pthread_getspecific(this->threadLocalIndex));
#endif
		return pBuff;
	}

	void SetPointer(ThreadBuffer<T> *pBuff)
	{
#if defined( NV_WIN_PLATFORM )
		::TlsSetValue(this->threadLocalIndex, static_cast<void *>(pBuff));
#elif defined( NV_LINUX_PLATFORM )
    ::pthread_setspecific(this->threadLocalIndex, static_cast<void *>(pBuff));
#endif
    if(pBuff)
    {
      threading::MutexLock lock(section);
      allocatedBuffers.addLast(pBuff);
    }
	}

public:

	#if !defined( _DEBUG ) && !defined( NV_LINUX_PLATFORM )
		#pragma optimize("", off)
	#endif

	void _cdecl SetValue(const T &value)
	{
		ThreadBuffer<T>* currentPointer = this->GetPointer();
		if (currentPointer == NULL)
		{
      ThreadBuffer<T> *pNewBuf = new ThreadBuffer<T>(new T(value));
			this->SetPointer(pNewBuf);
		}
		else
		{
      T* pP = currentPointer->data;
			*pP = value;
		}
	}

	T& _cdecl GetValue(void)
	{
		ThreadBuffer<T>* currentPointer = this->GetPointer();
		if (currentPointer == NULL)
		{
      ThreadBuffer<T> *pNewBuf = new ThreadBuffer<T>(new T());
			this->SetPointer(pNewBuf);
      NI_ASSERT(this->GetPointer() == pNewBuf, "Logic error");
		}
    T* pP = this->GetPointer()->data;
		return *pP;
	}

	#if !defined( _DEBUG ) && !defined( NV_LINUX_PLATFORM )
		#pragma optimize("", on)
	#endif

	void DeleteValue()
	{
		ThreadBuffer<T>* currentPointer = this->GetPointer();
		if (currentPointer != NULL)
		{
      {
        threading::MutexLock lock(section);
        allocatedBuffers.remove(currentPointer);
      }
			delete currentPointer;
			this->SetPointer(NULL);
		}
	}

	ThreadLocal(const T& value)
	{
    threading::MutexLock lock(section);
    allocatedBuffers.reset();
#if defined( NV_WIN_PLATFORM )
		this->threadLocalIndex = ::TlsAlloc();
#elif defined( NV_LINUX_PLATFORM )
    ( void ) ::pthread_key_create( &this->threadLocalIndex, 0 );
#endif
    NI_ASSERT(this->threadLocalIndex < GetOSClassType()->GetMaxTls(), "Too many TLS indices allocated.");
		this->SetValue(value);
	}

	ThreadLocal()
	{
    threading::MutexLock lock(section);
    allocatedBuffers.reset();
#if defined( NV_WIN_PLATFORM )
		this->threadLocalIndex = ::TlsAlloc();
#elif defined( NV_LINUX_PLATFORM )
    ( void ) ::pthread_key_create( &this->threadLocalIndex, 0 );
#endif
    NI_ASSERT(this->threadLocalIndex < GetOSClassType()->GetMaxTls(), "Too many TLS indices allocated.");
	}

	virtual ~ThreadLocal()
	{
    //delete all values from ring
    threading::MutexLock lock(section);
    ThreadBuffer<T> *const pBufLast = allocatedBuffers.last();
    ThreadBuffer<T> *pCurr;
    for (ThreadBuffer<T> *pBuf = allocatedBuffers.first(); pBuf != pBufLast;)
    {
      pCurr = pBuf;
      //next
      pBuf = ThreadBuffer<T>::Ring::next(pBuf);
      //remove
      delete pCurr;
    }
#if defined( NV_WIN_PLATFORM )
		::TlsFree(this->threadLocalIndex);
#elif defined( NV_LINUX_PLATFORM )
    ( void ) ::pthread_key_delete( this->threadLocalIndex );
#endif
	}

};
#pragma warning(pop)

UINT64 ThreadLocalGetTLSBitmap();
void ClearThreadTLSData();

#endif //#define THREADLOCAL_H_1F14A519_37C9_47B5

