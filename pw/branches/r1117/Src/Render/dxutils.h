#pragma once

#include "Vendor/DirectX/Include/d3d9.h"
#include "Vendor/DirectX/Include/d3dx9.h"

#include "DxIntrusivePtr.h"
#include "DeviceLost.h"

template<typename T>
T* Get(T* &p)
{
  return p;
}

class DXVertexBufferDynamicRef : public Render::DeviceLostHandler
{
  DXVertexBufferRef pDXBuffer;
  UINT size;

protected:
  DXVertexBufferDynamicRef() : size(0) {}
  explicit DXVertexBufferDynamicRef(UINT size_) : size(size_) {}

public:
  typedef IDirect3DVertexBuffer9 Iface;
  typedef Render::DeviceLostWrapper<DXVertexBufferDynamicRef> Wrapped;

  bool Resize(int size, bool nullOnLostDevice = false);
  UINT GetSize() const { return size; }

  void Reset() { pDXBuffer.Attach(0); size = 0; }

  IDirect3DVertexBuffer9* operator->() const { return Get(pDXBuffer); }
  IDirect3DVertexBuffer9* __gEt__() const { return Get(pDXBuffer); }

  // Handle lost device
  virtual void OnDeviceLost() 
	{ 
		NI_ASSERT( size > 0 || !pDXBuffer, "Invalid dynamic VB size"); 
		pDXBuffer = 0; 
	}
  virtual void OnDeviceReset();
};

inline IDirect3DVertexBuffer9* Get(DXVertexBufferDynamicRef const& sp)
{
  return sp.__gEt__();
}

template<UINT elemSize>
class DXIndexBufferDynamicRef_ : public Render::DeviceLostHandler
{
  DXIndexBufferRef pDXBuffer;
  UINT size;

protected:
  DXIndexBufferDynamicRef_() : size(0) {}
  explicit DXIndexBufferDynamicRef_(UINT size_) : size(size_) {}
  DXIndexBufferDynamicRef_(IDirect3DIndexBuffer9* pBuffer, UINT size_) : pDXBuffer(pBuffer, false), size(size_) {}

public:
  typedef IDirect3DIndexBuffer9 Iface;
  typedef Render::DeviceLostWrapper<DXIndexBufferDynamicRef_> Wrapped;

  bool Resize(int _size);
  UINT GetSize() const { return size; }

  void Reset() { pDXBuffer.Attach(0); size = 0; }

  IDirect3DIndexBuffer9* operator->() const { return Get(pDXBuffer); }
  IDirect3DIndexBuffer9* __gEt__() const { return Get(pDXBuffer); }

  // Handle lost device
  virtual void OnDeviceLost()
	{ 
		NI_ASSERT( size > 0 || !pDXBuffer, "Invalid dynamic IB size"); 
		pDXBuffer = 0; 
	}

  virtual void OnDeviceReset();
};

typedef DXIndexBufferDynamicRef_<32> DXIndexBufferDynamicRef;
typedef DXIndexBufferDynamicRef_<16> DXIndexBufferDynamicRef16;

template<UINT elemSize>
inline IDirect3DIndexBuffer9* Get(DXIndexBufferDynamicRef_<elemSize> const& sp)
{
  return sp.__gEt__();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Render
{

void SetErrorMessage(HRESULT hr, const wstring &msg); // Set localized messages for DXERR_*** cracker.
void ShowErrorMessageAndTerminate(HRESULT hr);     // Cracker for DXERR_*** codes. Terminates app.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Single-threaded shared D3D buffer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
//#define CHECK_FOR_ST
#endif // _SHIPPING

template<class _DynBuffer>
class SharedD3DBufferST : protected _DynBuffer
{
  seDECLARE_RING_T(SharedD3DBufferST, m_part, Ring);

  static Ring& GetRing();

  void* ptr;
  DWORD position;
  DWORD positionAtLock;
  DWORD sizeRequested;
  DWORD timeStamp;
  const DWORD threadID;
  float minSizeScale;
  bool  isLocked;

  enum LOCK_FLAGS
  {
    LOCKFLAGS_FLUSH  = D3DLOCK_DISCARD,
    LOCKFLAGS_APPEND = D3DLOCK_NOOVERWRITE
  };

  void Init() // Call this ONCE in constructor
  {
    ptr = 0; position = 0; timeStamp = 0;
    isLocked = false;
    GetRing().addLast(this);
  }

  bool IsSameThread() const { return ::GetCurrentThreadId() == threadID; }
#ifdef CHECK_FOR_ST
  void CheckForST() const { NI_ASSERT(IsSameThread(), "SharedD3DBufferST should be used from single thread only!"); }
#else
  #define CheckForST()
#endif

  INTERMODULE_EXPORT void QuerySize(UINT _size);
  INTERMODULE_EXPORT bool Resize(int _size); // Returns true on success. If false, size may be null or not changed.

protected :
  SharedD3DBufferST() : minSizeScale(), threadID( ::GetCurrentThreadId() ) { Init(); }

  explicit SharedD3DBufferST(DWORD _size, float _minSizeScale = 0.0f)
    : _DynBuffer(_size), minSizeScale(_minSizeScale), threadID( ::GetCurrentThreadId() )
  { Init(); }

  ~SharedD3DBufferST()
  {
    Clear();
    Ring::remove(this);
  }

public :
  typedef typename _DynBuffer::Iface Iface;

  void Clear() { CheckForST(); Reset(); _DynBuffer::Reset(); }

  virtual void OnDeviceLost()  { CheckForST(); Reset(); _DynBuffer::OnDeviceLost(); }
  virtual void OnDeviceReset() { CheckForST(); _DynBuffer::OnDeviceReset(); }

  UINT GetSize()  const  { CheckForST(); return _DynBuffer::GetSize(); }
  UINT GetTimeStamp() const { CheckForST(); return timeStamp; }

  void* GetPointer(UINT _pos) const
  {
    CheckForST();
    NI_ASSERT(isLocked && _pos >= positionAtLock, "SharedD3DBufferST::GetPointer() - wrong position");
    return PBYTE(ptr) + _pos - positionAtLock;
  }
  Iface* GetBuffer() const { CheckForST(); return Get(*this); }

  bool IsLocked() { CheckForST(); return isLocked; }

  UINT AcquireSpace(DWORD _size)
  {
    CheckForST();
    NI_VERIFY(isLocked, NStr::StrFmt("SharedD3DBufferST::AcquireSpace called while buffer is unlocked"), return UINT_MAX);

    sizeRequested += _size;
    // Ensure there is enough space for this data
    if( position + _size > GetSize() )
      return UINT_MAX;

    UINT pos = position;
    position += _size;
    return pos;
  }

  INTERMODULE_EXPORT bool Lock(); // returns false if Lock didn't succeed
  void Unlock()
  {
    CheckForST();
    if(isLocked) {
      (*this)->Unlock();
      isLocked = false;
    }
  }

  static void UnlockAll()
  {
    for(ring::Range<Ring> it( GetRing() ); it; ++it)
      it->Unlock();
  }

  void Reset()
  {
    ptr = 0;
    position = 0;
    Unlock();
  }

  static void ResetAll()
  {
    for(ring::Range<Ring> it( GetRing() ); it; ++it)
      it->Reset();
  }
};  // class SharedD3DBufferST

// DeviceLostWrapper MUST be terminal class! Don't inherit from SharedVB, only from SharedD3DBufferST!
typedef DeviceLostWrapper< SharedD3DBufferST<DXVertexBufferDynamicRef> > SharedVB;
typedef DeviceLostWrapper< SharedD3DBufferST<DXIndexBufferDynamicRef> >  SharedIB;


//==== SharedD3DBufferST helper - holds info about acquired buffer space ====================================

class SpaceHolder
{
  UINT position;
  UINT size;
  UINT timeStamp; // there is no need to initialize this

  typedef class NDb::DBID NDBID;

  template<class T> bool AcquireSpace_(DWORD _size, T& _buffer);
  template<class T> bool IsValid_(const T& _buffer, const NDBID& _id) const;

public:
  bool AcquireSpace(DWORD _size, SharedVB& _buffer) { return AcquireSpace_(_size, _buffer); }
  bool AcquireSpace(DWORD _size, SharedIB& _buffer) { return AcquireSpace_(_size, _buffer); }

  SpaceHolder() : position(UINT_MAX), size() {}

  bool IsValid(const SharedVB& _buffer, const NDBID& _id = *(NDBID*)0) const { return IsValid_(_buffer, _id); }
  bool IsValid(const SharedIB& _buffer, const NDBID& _id = *(NDBID*)0) const { return IsValid_(_buffer, _id); }

  UINT GetSize() const { return size; }
  UINT GetPosition() const { return position; }

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum PoolType
{
	RENDER_POOL_DEFAULT,
	RENDER_POOL_MANAGED,
	RENDER_POOL_DYNAMIC,
	RENDER_POOL_TEX_DYNAMIC,
	RENDER_POOL_SYSMEM,
  RENDER_POOL_SYSMEM_DYNAMIC,
};

void GetD3DPoolAndUsagesParamaters(DWORD& usage, D3DPOOL& pool, PoolType poolType);

DXVertexBufferRef CreateVB(int size, PoolType type, void const *pData = 0);
void* LockVB(IDirect3DVertexBuffer9 *pBuff, unsigned int flags, int size = 0);
void FillVB(IDirect3DVertexBuffer9 *pBuff, int size, void const *pData, unsigned int lockFlags = 0);

template <typename T>
T* LockVB(IDirect3DVertexBuffer9 *pBuff, unsigned int flags, int size = 0)
{
	return reinterpret_cast<T*>( LockVB(pBuff, flags, size) );
}

DXIndexBufferRef CreateIB(int size, PoolType poolType, UINT const *pData = 0);
DXIndexBufferRef CreateIB16(int size, PoolType poolType, WORD const *pData = 0);
unsigned int* LockIB(IDirect3DIndexBuffer9 *pBuff, unsigned int flags, int size = 0);
void FillIB(IDirect3DIndexBuffer9 *pBuff, int size, void const *pData, unsigned int lockFlags);

int D3DFormatNumBits(D3DFORMAT format);

namespace Shims
{

  template<typename T>
  struct PointedType
  {
  };

  template<typename T, class REF_POLICY>
  struct PointedType< IntrusivePtr<T, REF_POLICY> >
  {
    typedef typename IntrusivePtr<T, REF_POLICY>::Element type;
    typedef type* pointer;
  };

  template<typename T>
  struct PointedType<T*>
  {
    typedef T type;
    typedef type* pointer;
  };

//////////////////////////////////////////////////////////////////////////
  template<class T>
  void Delete(T &p) { p = 0; }

  template<class T>
  void Delete(T* &p) { delete p; p = 0; }

//////////////////////////////////////////////////////////////////////////
  template<typename T, class REF_POLICY>
  void Attach(IntrusivePtr<T, REF_POLICY> &p, T* val ) { p.Attach(val); }

  template<typename T>
  void Attach(T* &p, T* val)
  {
    delete p;
    p = val;
  }

//////////////////////////////////////////////////////////////////////////
  template<typename T, class REF_POLICY>
  T* Detach(IntrusivePtr<T, REF_POLICY> &p) { return p.Detach(); }

  template<typename T>
  T* Detach(T* val) { return val; }

};

class RefCountST
{
  long rc;

public:
  RefCountST() : rc() {}
  long AddRef()  { return ++rc; }
  long Release() { return --rc; }
};

class RefCountMT
{
  volatile long rc;

public:
  RefCountMT() : rc() {}
  long AddRef()  { return InterlockedIncrement(&rc); }
  long Release() { return InterlockedDecrement(&rc); }
};


template<class T, class RC = RefCountST>
class SharedBuffer
{
  T p;
  size_t size;
  RC refCount;

public:
  SharedBuffer() : p(), size(), refCount()  {}

  long AddRef()
  {
    if(p)
      return refCount.AddRef();
    else
      return INT_MIN;
  }
  long Release()
  {
    if(!p)
      return INT_MIN;
    const long rc = refCount.Release();
    if(!rc)
      Shims::Delete(p);

    return rc;
  }

  typedef T SharedBuffer::*unspecified_bool_type;

  operator unspecified_bool_type () const
  {
    return p ? &SharedBuffer::p : 0;
  }

  typename Shims::PointedType<T>::type& operator*()  const { return *p; }
  typename Shims::PointedType<T>::type* operator->() const { return &*p; }

  size_t  GetSize() const { return size; }
  const T& GetPtr() const { return p; }
  void     SetPtr(const T& _src, size_t _size)
  {
    if(p)
      Shims::Delete(p);
    p = _src;
    size = _size;
  }
};

// Single-threaded holder for resources listening for OnDeviceDelete
// Initializer class must provide Delete(Initializer::Type &p) and Init(Initializer::Type &p)
template<class Initializer>
struct ManagedResource : public Initializer, public DeviceDeleteHandler
{
  typedef typename Initializer::Type Type;
  typedef typename Shims::PointedType<Type>::pointer Pointer;

  ManagedResource() : p() {}
  ManagedResource(const Initializer& _initializer) : Initializer(_initializer), p() {}
  ~ManagedResource() { Initializer::Delete(p); }

  virtual void OnDeviceDelete()
  {
    Initializer::Delete(p);
  }

  Pointer Get()
  {
    if(p) // static branch prediction assumes that forward-pointing branches will not be taken
      return ::Get(p);

    Initializer::Init(p);

    return ::Get(p);
  }

private:
  Type p;
};

// holder for resources listening for OnDeviceLost
// Initializer class must provide Delete(Initializer::Type &p) and Init(Initializer::Type &p)
template<class Initializer>
struct DefPoolResource : public Initializer, public DeviceLostHandler
{
  typedef typename Initializer::Type Type;
  typedef typename Shims::PointedType<Type>::pointer Pointer;

  DefPoolResource() : p() {}
  DefPoolResource(const Initializer& _initializer) : Initializer(_initializer), p() {}
  ~DefPoolResource() { Initializer::Delete(p); }

  virtual void OnDeviceLost()
  {
    Initializer::Delete(p);
  }

  Pointer Get()
  {
    if(p) // static branch prediction assumes that forward-pointing branches will not be taken
      return ::Get(p);

    Initializer::Init(p);

    return ::Get(p);
  }

private:
  Type p;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct IntrusivePtrDeleter
{
  template<typename T, class REF_POLICY>
  static void Delete(IntrusivePtr<T, REF_POLICY> &p)
  {
    p = 0;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct SimpleInitializer
{
  typedef T* Type;

  static void Init(T*& _p)
  {
    _p = new T();
  }

  static void Delete(T*& _p)
  {
    delete _p;
    _p = 0;
  }
}; // struct Initializer

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct MaterialInit
{
  typedef T* Type;

  static void Init(T*& _p)
  {
    _p = static_cast<T*>( CreateRenderMaterial( T::typeId ) );
  }

  static void Delete(T*& _p)
  {
    delete _p;
    _p = 0;
  }
};

}