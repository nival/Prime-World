#include "stdafx.h"
#include "renderer.h"
#include "DxResourcesControl.h"
#include "DebugLocks.h"
#include <MemoryLib/UserMessage.h>
#include <PF_GameLogic/DBSessionMessages.h>

namespace Render
{

  struct ErrorMessages {
    wstring title;
    wstring errorMessage;
    wstring lowMemoryMessage;
    wstring lowVidMemMessage;
    ErrorMessages(LPCWSTR _title, LPCWSTR _errorMessage, LPCWSTR _lowMemoryMessage, LPCWSTR _lowVidMemMessage)
      : errorMessage(_errorMessage), lowMemoryMessage(_lowMemoryMessage), lowVidMemMessage(_lowVidMemMessage)
    {}
  } s_errorMessages(L"Prime World: The application will be terminated now.",
                    L"Internal error. Restart application.",
                    L"Insufficient memory. Try to free some memory and restart application.",
                    L"Insufficient video-memory. Try to free some video-memory and restart application.");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetErrorMessage(HRESULT hr, const wstring &msg)
{
  switch(hr) {
  case 0:
    s_errorMessages.title = msg;
    break;
  case D3DERR_INVALIDCALL:
    s_errorMessages.errorMessage = msg;
    break;
  case E_OUTOFMEMORY:
    s_errorMessages.lowMemoryMessage = msg;
    break;
  case D3DERR_OUTOFVIDEOMEMORY:
    s_errorMessages.lowVidMemMessage = msg;
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowErrorMessageAndTerminate(HRESULT hr)
{
  //NI_DATA_VERIFY(NDb::SessionRoot::GetRoot()->sessionMessages, "Session.ROOT.sessionMessages is empty!");
  nstl::wstring errorMessage;

  switch(hr) {
  case D3DERR_INVALIDCALL:
  case D3DERR_DEVICEREMOVED:
    errorMessage = s_errorMessages.errorMessage;
  	break;
  case E_OUTOFMEMORY:
    errorMessage = s_errorMessages.lowMemoryMessage;
    break;
  case D3DERR_OUTOFVIDEOMEMORY:
    errorMessage = s_errorMessages.lowVidMemMessage;
    break;
  }

  UserMessage::ShowMessageAndTerminate( EXCEPTION_BREAKPOINT, s_errorMessages.title.c_str(), errorMessage.c_str() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int D3DFormatNumBits(D3DFORMAT format)
{
  switch(format)
  {
    case D3DFMT_UNKNOWN        : return 0;

    case D3DFMT_R8G8B8         : return 24;
    case D3DFMT_A8R8G8B8       : return 32;
    case D3DFMT_X8R8G8B8       : return 32;
    case D3DFMT_R5G6B5         : return 16;
    case D3DFMT_X1R5G5B5       : return 16;
    case D3DFMT_A1R5G5B5       : return 16;
    case D3DFMT_A4R4G4B4       : return 16;
    case D3DFMT_R3G3B2         : return 8;
    case D3DFMT_A8             : return 8;
    case D3DFMT_A8R3G3B2       : return 16;
    case D3DFMT_X4R4G4B4       : return 16;
    case D3DFMT_A2B10G10R10    : return 32;
    case D3DFMT_A8B8G8R8       : return 32;
    case D3DFMT_X8B8G8R8       : return 32;
    case D3DFMT_G16R16         : return 32;
    case D3DFMT_A2R10G10B10    : return 32;
    case D3DFMT_A16B16G16R16   : return 64;

    case D3DFMT_A8P8           : return 16;
    case D3DFMT_P8             : return 8;

    case D3DFMT_L8             : return 8;
    case D3DFMT_A8L8           : return 16;
    case D3DFMT_A4L4           : return 8;

    case D3DFMT_V8U8           : return 16;
    case D3DFMT_L6V5U5         : return 16;
    case D3DFMT_X8L8V8U8       : return 32;
    case D3DFMT_Q8W8V8U8       : return 32;
    case D3DFMT_V16U16         : return 32;
    case D3DFMT_A2W10V10U10    : return 32;

    case D3DFMT_UYVY           : return 0;
    case D3DFMT_R8G8_B8G8      : return 0;
    case D3DFMT_YUY2           : return 0;
    case D3DFMT_G8R8_G8B8      : return 0;
    case D3DFMT_DXT1           : return 4;
    case D3DFMT_DXT2           : return 4;
    case D3DFMT_DXT3           : return 4;
    case D3DFMT_DXT4           : return 8;
    case D3DFMT_DXT5           : return 8;

    case D3DFMT_D16_LOCKABLE   : return 16;
    case D3DFMT_D32            : return 32;
    case D3DFMT_D15S1          : return 16;
    case D3DFMT_D24S8          : return 32;
    case D3DFMT_D24X8          : return 32;
    case D3DFMT_D24X4S4        : return 32;
    case D3DFMT_D16            : return 16;

    case D3DFMT_D32F_LOCKABLE  : return 32;
    case D3DFMT_D24FS8         : return 32;

    case D3DFMT_L16            : return 16;

    case D3DFMT_VERTEXDATA     : return 0;
    case D3DFMT_INDEX16        : return 16;
    case D3DFMT_INDEX32        : return 32;

    case D3DFMT_Q16W16V16U16   : return 64;

    case D3DFMT_MULTI2_ARGB8   : return 64;

    // s10e5 formats
    case D3DFMT_R16F           : return 16;
    case D3DFMT_G16R16F        : return 32;
    case D3DFMT_A16B16G16R16F  : return 64;

    // IEEE s23e8 format
    case D3DFMT_R32F           : return 32;
    case D3DFMT_G32R32F        : return 64;
    case D3DFMT_A32B32G32R32F  : return 128;

    case D3DFMT_CxV8U8         : return 0;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetD3DPoolAndUsagesParamaters(DWORD& usage, D3DPOOL& pool, PoolType poolType)
{
	if (poolType == RENDER_POOL_MANAGED)
	{
		usage = 0;
		pool = D3DPOOL_MANAGED;
	}
	else if (poolType == RENDER_POOL_DEFAULT)
	{
// 		usage = D3DUSAGE_WRITEONLY;
    usage = 0;
		pool = D3DPOOL_DEFAULT;
	}
	else if (poolType == RENDER_POOL_DYNAMIC)
	{
		usage = D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC;
		pool = D3DPOOL_DEFAULT;
	}
	else if (poolType == RENDER_POOL_TEX_DYNAMIC)
	{
		usage = D3DUSAGE_DYNAMIC;
		pool = D3DPOOL_DEFAULT;
	}
	else if (poolType == RENDER_POOL_SYSMEM) {
		usage = 0;
		pool = D3DPOOL_SYSTEMMEM;
	}
  else if (poolType == RENDER_POOL_SYSMEM_DYNAMIC) {
    usage = D3DUSAGE_DYNAMIC;
    pool = D3DPOOL_SYSTEMMEM;
  }
	else NI_ALWAYS_ASSERT("Invalid pool type!");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static IDirect3DVertexBuffer9* CreateVBInternal(int size, PoolType type, void const *pData = 0)
{
  DWORD usage;
  D3DPOOL pool;
  GetD3DPoolAndUsagesParamaters(usage, pool, type);

  IDirect3DVertexBuffer9* d3dvb = 0;
  HRESULT hr = GetDevice()->CreateVertexBuffer(size, usage, 0, pool, &d3dvb, 0);
  NI_DX_THROW_CRITICAL( hr, NStr::StrFmt("CreateVB(%d bytes)", size) );
  if (pData && d3dvb)
    FillVB(d3dvb, size, pData);
  return d3dvb;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DXVertexBufferRef CreateVB(int size, PoolType type, void const *pData /*= 0*/)
{
  NI_ASSERT(type != RENDER_POOL_DEFAULT && type != RENDER_POOL_DYNAMIC, "Use CreateVBDynamic() instead to manage lost device correctly");
  IDirect3DVertexBuffer9* d3dvb = CreateVBInternal(size, type, pData);
  return DXVertexBufferRef(d3dvb, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillVB(IDirect3DVertexBuffer9 *pBuff, int size, void const *pData, unsigned int lockFlags)
{
	void *pDst = LockVB(pBuff, lockFlags, size);
	if (pDst)
	{
		memcpy(pDst, pData, size);
		pBuff->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG_LOCKS

static hash_map<void*, uint> lockCalls;
uint GetLockCall(void* _pBuff) { return Render::lockCalls[(void*)_pBuff]; }

#endif // _DEBUG_LOCKS


void* LockVB(IDirect3DVertexBuffer9 *pBuff, unsigned int flags, int size)
{
  ASSERT(pBuff);
  DEBUG_LOCKS(static uint callNmb = 0;)
  void *pData = NULL;
  HRESULT hr = pBuff->Lock(0, size, &pData, flags);
  NI_DX_THROW( hr, "Lock vertex buffer failed" );
  DEBUG_LOCKS(lockCalls[pBuff] = callNmb++;)
  return pData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
static IDirect3DIndexBuffer9* CreateIBInternal(int size, PoolType type, T const *pData = 0)
{
	DWORD usage;
	D3DPOOL pool;
	GetD3DPoolAndUsagesParamaters(usage, pool, type);
  NI_STATIC_ASSERT((sizeof(T) == 4) || (sizeof(T) == 2), UnsupportedIndexSize);

	IDirect3DIndexBuffer9* d3dib = 0;
  HRESULT hr = GetDevice()->CreateIndexBuffer(size, usage, sizeof(T) == 4 ? D3DFMT_INDEX32 : D3DFMT_INDEX16, pool, &d3dib, 0);
	NI_DX_THROW_CRITICAL( hr, NStr::StrFmt("CreateIB(%d bytes)", size) );
  if (pData  && d3dib)
    FillIB(d3dib, size, pData, 0);
	return d3dib;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DXIndexBufferRef CreateIB(int size, PoolType type, UINT const *pData /*= 0*/)
{
  NI_ASSERT(type != RENDER_POOL_DEFAULT && type != RENDER_POOL_DYNAMIC, "Use CreateIBDynamic() instead to manage lost device correctly");
  IDirect3DIndexBuffer9* d3dib = CreateIBInternal(size, type, pData);
  return DXIndexBufferRef(d3dib, false);
}

DXIndexBufferRef CreateIB16(int size, PoolType type, WORD const *pData /*= 0*/)
{
  NI_ASSERT(type != RENDER_POOL_DEFAULT && type != RENDER_POOL_DYNAMIC, "Use CreateIBDynamic() instead to manage lost device correctly");
  IDirect3DIndexBuffer9* d3dib = CreateIBInternal(size, type, pData);
  return DXIndexBufferRef(d3dib, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int* LockIB(IDirect3DIndexBuffer9 *pBuff, unsigned int flags, int size)
{
  ASSERT(pBuff);
	void *pData = NULL;
	HRESULT hr = pBuff->Lock(0, size, &pData, flags);
	NI_DX_THROW( hr, "Lock index buffer failed" );
	return reinterpret_cast<unsigned int*>(pData);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillIB(IDirect3DIndexBuffer9 *pBuff, int size, void const *pData, unsigned int lockFlags)
{
	void *pDst = LockIB(pBuff, lockFlags, size);
	if (pDst)
	{
		memcpy(pDst, pData, size);
		pBuff->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class SharedD3DBufferST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _DynBuffer>
void SharedD3DBufferST<_DynBuffer>::QuerySize(UINT _size)
{
  if( 0 == _size )
    Reset();
  else {
    if( _size > GetSize() || _size < UINT(minSizeScale * GetSize()) )
    {
      Resize(_size);
      DebugTrace( "SharedD3DBufferST resized to %d bytes\n", GetSize() );
    }
  }
}

// Explicit instantiation
INTERMODULE_EXPORT void SharedD3DBufferST<DXVertexBufferDynamicRef>::QuerySize(UINT _size);
INTERMODULE_EXPORT void SharedD3DBufferST<DXIndexBufferDynamicRef>::QuerySize(UINT _size);
INTERMODULE_EXPORT void SharedD3DBufferST<DXIndexBufferDynamicRef16>::QuerySize(UINT _size);


template<class _DynBuffer>
bool SharedD3DBufferST<_DynBuffer>::Resize(int _size)
{
  Reset();
  const int oldSize = GetSize();
  if( _DynBuffer::Resize(_size) )
    return true;
  _DynBuffer::Resize(oldSize);
  return false;
}

// Explicit instantiation
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXVertexBufferDynamicRef>::Resize(int _size);
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXIndexBufferDynamicRef>::Resize(int _size);
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXIndexBufferDynamicRef16>::Resize(int _size);


template<class _DynBuffer>
bool SharedD3DBufferST<_DynBuffer>::Lock() // returns false if Lock didn't succeed
{
  if( !IsSameThread() )
    return false;

  if(isLocked)
    return true;

  if( GetSize() && !Get(*this) )
    _DynBuffer::OnDeviceReset();

  if( Get(*this) ) {
    if(ptr) {
      if( FAILED((*this)->Lock(position, GetSize() - position, &ptr, LOCKFLAGS_APPEND)) )
        return false;
    }
    else { // flash requested
      QuerySize(sizeRequested);
      sizeRequested = 0;
      if( FAILED((*this)->Lock(0, GetSize(), &ptr, LOCKFLAGS_FLUSH)) )
        return false;
      ++timeStamp;
    }
    positionAtLock = position;
    isLocked = true;
  }
  return isLocked;
}

// Explicit instantiation
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXVertexBufferDynamicRef>::Lock();
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXIndexBufferDynamicRef>::Lock();
template INTERMODULE_EXPORT bool SharedD3DBufferST<DXIndexBufferDynamicRef16>::Lock();


template<class _DynBuffer>
typename SharedD3DBufferST<_DynBuffer>::Ring& SharedD3DBufferST<_DynBuffer>::GetRing()
{
  static Ring theRing;
  return theRing;
}

// Explicit instantiation
template INTERMODULE_EXPORT SharedD3DBufferST<DXVertexBufferDynamicRef>::Ring& SharedD3DBufferST<DXVertexBufferDynamicRef>::GetRing();
template INTERMODULE_EXPORT SharedD3DBufferST<DXIndexBufferDynamicRef>::Ring& SharedD3DBufferST<DXIndexBufferDynamicRef>::GetRing();
template INTERMODULE_EXPORT SharedD3DBufferST<DXIndexBufferDynamicRef16>::Ring& SharedD3DBufferST<DXIndexBufferDynamicRef16>::GetRing();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
bool SpaceHolder::AcquireSpace_(DWORD _size, T& _buffer)
{
  if( UINT_MAX == (position = _buffer.AcquireSpace(_size)) )
    return false;

  timeStamp = _buffer.GetTimeStamp();
  size = _size;
  return true;
}

// Explicit instantiation
template INTERMODULE_EXPORT bool SpaceHolder::AcquireSpace_<SharedVB>(DWORD _size, SharedVB& _buffer);
template INTERMODULE_EXPORT bool SpaceHolder::AcquireSpace_<SharedIB>(DWORD _size, SharedIB& _buffer);


template<class T>
bool SpaceHolder::IsValid_(const T& _buffer, const NDb::DBID& _id/* = *(NDb::DBID*)(0)*/) const
{
  //NI_ASSERT( _holder.timeStamp == _buffer.timeStamp, "SpaceHolder expired!");
  if( timeStamp != _buffer.GetTimeStamp() ) {
    //if(0 != &_id)
    //  DebugTrace( "Particle system %s attempts to draw without update! Buffer timeStamp: %d, holder timeStamp: %d,\n",
    //              NDb::GetFormattedDbId(_id).c_str(), _buffer.GetTimeStamp(), timeStamp );
    return false;
  }
  return UINT_MAX > position;
}

// Explicit instantiation
template INTERMODULE_EXPORT bool SpaceHolder::IsValid_<SharedVB>(const SharedVB& _buffer, const NDb::DBID& _id) const;
template INTERMODULE_EXPORT bool SpaceHolder::IsValid_<SharedIB>(const SharedIB& _buffer, const NDb::DBID& _id) const;

} // namespace Render

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DXVertexBufferDynamicRef::Resize(int _size, bool nullOnLostDevice /*= false*/)
{
  const bool clear = nullOnLostDevice && Render::GetRenderer()->DeviceIsLost();
  pDXBuffer.Attach( clear ? 0 : Render::CreateVBInternal(_size, Render::RENDER_POOL_DYNAMIC, 0) );
  size = pDXBuffer ? _size : 0;

  return pDXBuffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DXVertexBufferDynamicRef::OnDeviceReset()
{
	if (size == 0)
		return;

  pDXBuffer.Attach( Render::CreateVBInternal(size, Render::RENDER_POOL_DYNAMIC) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
bool DXIndexBufferDynamicRef_<32>::Resize(int _size)
{
  pDXBuffer.Attach( Render::CreateIBInternal<UINT>(_size, Render::RENDER_POOL_DYNAMIC) );
  size = pDXBuffer ? _size : 0;
  return pDXBuffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
bool DXIndexBufferDynamicRef_<16>::Resize(int _size)
{
  pDXBuffer.Attach( Render::CreateIBInternal<WORD>(_size, Render::RENDER_POOL_DYNAMIC) );
  size = pDXBuffer ? _size : 0;
  return pDXBuffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void DXIndexBufferDynamicRef_<32>::OnDeviceReset()
{
	if (size == 0)
		return;

	pDXBuffer.Attach( Render::CreateIBInternal<UINT>(size, Render::RENDER_POOL_DYNAMIC) );
}

template<>
void DXIndexBufferDynamicRef_<16>::OnDeviceReset()
{
  if (size == 0)
    return;

  pDXBuffer.Attach( Render::CreateIBInternal<WORD>(size, Render::RENDER_POOL_DYNAMIC) );
}
