#include "stdafx.h"
#include "ssememcopy.h"

void CompileTimeCheck()
{
	NI_STATIC_ASSERT( BUS_SEGMENT_SIZE > 128, BUS_SEGMENT_SIZE_SHOULD_BE_MORE_THAN_128 );
	NI_STATIC_ASSERT( !( BUS_SEGMENT_SIZE & (BUS_SEGMENT_SIZE-1) ), BUS_SEGMENT_SIZE_SHOULD_BE_POWER_OF_TWO );
}

void GuardedSSEMemCopy(void* _pDestination, void* _pSource, unsigned __int32 _size)
{
	NI_ASSERT( !((unsigned __int32) _pDestination & 0xF), "destination memory is NOT 16-byte aligned" );
	NI_ASSERT( !((unsigned __int32) _pSource & 0xF), "source memory is NOT 16-byte aligned" );
	NI_ASSERT( _size > BUS_SEGMENT_SIZE, "size should be more than BUS_SEGMENT_SIZE" );
	NI_ASSERT( !(_size % BUS_SEGMENT_SIZE), "size should be divisible by BUS_SEGMENT_SIZE" );	
	ssememcopy(_pDestination, _pSource, _size);
}

__declspec(naked) void __stdcall ssememcopy(void* _pDestination, void* _pSource, unsigned __int32 _size)
{
	__asm
	{
		push edx
		push esi
		push edi
		push ecx
		///
		mov edi, [esp+20]
		mov esi, [esp+24]
		mov edx, [esp+28]
		align 16
main_loop:
		xor ecx, ecx
		align 16
prefetch_loop:
		movaps xmm0, [esi+ecx]
		movaps xmm0, [esi+ecx+64]
		add ecx, 128
		cmp ecx, BUS_SEGMENT_SIZE
		jne prefetch_loop
		xor ecx, ecx
		align 16
copy_loop:
		movdqa xmm0, [esi+ecx+0]//movntdqa
		movdqa xmm1, [esi+ecx+16]
		movdqa xmm2, [esi+ecx+32]
		movdqa xmm3, [esi+ecx+48]
		movdqa xmm4, [esi+ecx+64]
		movdqa xmm5, [esi+ecx+80]
		movdqa xmm6, [esi+ecx+96]
		movdqa xmm7, [esi+ecx+112]
		movntdq [edi+ecx+0], xmm0
		movntdq [edi+ecx+16], xmm1
		movntdq [edi+ecx+32], xmm2
		movntdq [edi+ecx+48], xmm3
		movntdq [edi+ecx+64], xmm4
		movntdq [edi+ecx+80], xmm5
		movntdq [edi+ecx+96], xmm6
		movntdq [edi+ecx+112], xmm7
		add ecx, 128
		cmp ecx, BUS_SEGMENT_SIZE
		jne copy_loop
		add esi, ecx
		add edi, ecx
		sub edx, ecx
		jnz main_loop
		sfence
		///
		pop ecx
		pop edi
		pop esi
		pop edx
		ret 12
	}
}

