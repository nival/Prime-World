#ifndef __WIN32HELPER_H__
#define __WIN32HELPER_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <float.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWin32Helper
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class com_ptr
{
	T *pData;

	void Assign( T *_pData ) 
  { 
    if ( _pData ) 
    { 
      DebugTrace( "ComPtr: Assign %p INC", (void*)_pData );
      _pData->AddRef(); 
    } 
    pData = _pData; 
  }

	void Free() 
  { 
    if ( pData ) 
    { 
      DebugTrace( "ComPtr: Free %p DEC", (void*)pData );
      pData->Release(); 
    }
    pData = 0; 
  }

public:
	com_ptr( T *_pData = 0 ) 
  { 
    Assign( _pData ); 
  }

	~com_ptr() 
  { 
    Free(); 
  }

	com_ptr( const com_ptr &a ) 
  { 
    Assign( a.pData ); 
  }

	com_ptr& operator=( const com_ptr &a ) 
  { 
    if ( pData == a.pData ) 
      return *this; 
    Free();
    Assign( a.pData ); 
    return *this; 
  }

	com_ptr& operator=( T *pObj ) 
  { 
    if ( pData == pObj ) 
      return *this; 
    Free(); 
    Assign( pObj ); 
    return *this; 
  }

	operator T*() const { return pData; }
	T* operator->() const { return pData; }

	T** GetAddr() 
  { 
    DebugTrace( "ComPtr: GetAddr", (void*)pData );
    Free(); 
    pData = 0; 
    return &pData; 
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CControl87Guard
{
	unsigned int nPrevState;
public:
	CControl87Guard() { nPrevState = _control87( 0, 0 ); }
	~CControl87Guard() { _control87( nPrevState, 0xffffffff ); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPrecisionControl
{
	CControl87Guard guard;
public:
	enum EPrecisionControlMode{ PCM_HIGH = _PC_64, PCM_MEDIUM = _PC_53, PCM_LOW = _PC_24 };
	CPrecisionControl( EPrecisionControlMode mode = PCM_HIGH ) { _control87( mode, _MCW_PC ); }
	void Set( EPrecisionControlMode mode ) { _control87( mode, _MCW_PC ); };
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRoundingControl
{
	CControl87Guard guard;
public:
	enum ERoundingControlMode{ RCM_NEAR = _RC_NEAR, RCM_DOWN = _RC_DOWN, RCM_UP = _RC_UP, RCM_CHOP = _RC_CHOP };
	CRoundingControl( ERoundingControlMode mode = RCM_NEAR ) { _control87( mode, _MCW_RC ); }
	void Set( ERoundingControlMode mode ) { _control87( mode, _MCW_RC ); };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CPUID_MMX_FEATURE_PRESENT = 0x00800000;
const DWORD CPUID_SSE_FEATURE_PRESENT = 0x02000000;
#define GET_CPUID __asm _emit 0x0f __asm _emit 0xa2
inline DWORD GetCPUID()
{
	DWORD dwRes;
	_asm
	{
		pusha															 // keep compiler happy
		pushfd 															// get extended flags
		pop eax 														// store extended flags in eax
		mov ebx, eax 												// save current flags
		xor eax, 200000h 										// toggle bit 21
		push eax 														// put new flags on stack
		popfd 															// flags updated now in flags
		pushfd 															// get extended flags
		pop eax 														// store extended flags in eax
		xor eax, ebx 												// if bit 21 r/w then eax <> 0
		je q																// can't toggle id bit (21) no cpuid here

		mov	eax, 1													// configure eax to retrieve CPUID
		GET_CPUID													 // perform CPUID command
		mov dwRes, edx											// store CPUID in dwRes1
	q:
		popa
	}
	return dwRes;
}
#undef GET_CPUID
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
