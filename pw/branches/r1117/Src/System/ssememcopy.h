#ifndef _SSEMCOPY_H_
#define _SSEMCOPY_H_

#ifndef BUS_SEGMENT_SIZE
#define BUS_SEGMENT_SIZE 1024
#endif

void CompileTimeCheck();

void GuardedSSEMemCopy(void* _pDestination, void* _pSource, unsigned __int32 _size);

void __stdcall ssememcopy(void* _pDestination, void* _pSource, unsigned __int32 _size);

#endif

