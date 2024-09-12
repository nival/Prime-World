/*
* DataExecutor.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include "stdafx.h"

#include "DataExecutor.h"
#include "ExecutionMemoryManager.h"
#include "../System/Base64.h"
#include "../System/nvector.h"
#include "../System/nhash_map.h"
#include "../System/Ring.h"
#include "../System/ThreadLocal.h"

#pragma warning(push)
#pragma warning(disable: 4740)

int DataExecutor::nLastExecutionStatus = 0;

ScopedPtr<ExecutionMemoryManager> DataExecutor::memoryManager(NULL);

int DataExecutor::GetLastExecutionStatus() 
{
  return nLastExecutionStatus;
}


__forceinline void DataExecutor::fixDirectRelocs(unsigned int const nBase, unsigned int const nShift, unsigned int const *npOffsetTable, unsigned int nTableSize)
{
  unsigned int const *npLastTableElem;
  unsigned int const *npCurrElem;

  for(npLastTableElem = npOffsetTable + nTableSize - 1, npCurrElem = npOffsetTable; npCurrElem <= npLastTableElem; npCurrElem++)
  {
    //tune all zero-ed pointer to actual memory loading address
    *((unsigned int  *)(nBase + *npCurrElem)) += nShift;
  }
}

__forceinline void DataExecutor::fixDirectRelocs( unsigned int const nBase, unsigned int const *npOffsetTable, unsigned int nTableSize )
{
  fixDirectRelocs(nBase, nBase, npOffsetTable, nTableSize);
}

void DataExecutor::initClass(unsigned char expectedVersion, unsigned char const *dataBuffer, unsigned int nBufferSize)
{
  //once in life init
  if(memoryManager == NULL)
  {
    Reset(memoryManager, new ExecutionMemoryManager(1024 * 1024, 512 * 1024));
  }

  FormulaHeader *pHeader    = (FormulaHeader *)dataBuffer;
  DWORD          nReqSize;
  int            nHeaderSize  = pHeader->GetSize();

  NI_VERIFY(nBufferSize >= sizeof(FormulaHeader), "Required compiled stream header is absent", return;);
  NI_VERIFY( pHeader->version == expectedVersion, NStr::StrFmt( "Formula version mismatch: got %d, %d expected ", (int)pHeader->version, (int)expectedVersion ), return );

  nEntryPointOffset = pHeader->entryPointOffset;

  nReqSize = nBufferSize - nHeaderSize;
  NI_VERIFY((nBufferSize - nHeaderSize) >= 0, "Check logic.", return;);

  //allocate buffer
  pBinaryCode = memoryManager->Alloc(nReqSize);

  NI_VERIFY(pBinaryCode != NULL, "Memory commit failed!", return;);
  char *pNewOrigin  = (char *)pBinaryCode;
  memcpy(pNewOrigin, dataBuffer + nHeaderSize, nBufferSize - nHeaderSize);

  //now patch relocations
  fixDirectRelocs((unsigned int)pNewOrigin, pHeader->GetRelocations(), pHeader->relocsNum);

  unsigned int distance = (unsigned int)(memoryManager->GetLinkJumpTable() + memoryManager->GetLinkCount()) - (unsigned int)pNewOrigin;
  //now patch external relocations
  fixDirectRelocs((unsigned int)pNewOrigin, distance, pHeader->GetExtRelocations(), pHeader->extRelocsNum);
}

DataExecutor::DataExecutor(unsigned char expectedVersion, char const *cpBase64String)
{
  MemoryStream str;
  MemoryStream out;
  str.Write(cpBase64String, strlen(cpBase64String));
  unsigned short int nCRLF = 0x0A0D;
  str.Write(&nCRLF, 2);
  str.Seek(0, SEEKORIGIN_BEGIN);
  Base64::Decode(str, out);
  initClass(expectedVersion, (unsigned char const *)out.GetBuffer(), out.GetSize());
}

DataExecutor::DataExecutor(unsigned char expectedVersion, unsigned char const *dataBuffer, unsigned int nBufferSize)
{
  initClass(expectedVersion, dataBuffer, nBufferSize);
}

DataExecutor::~DataExecutor()
{
  if(pBinaryCode != NULL)
  {
    memoryManager->Free(pBinaryCode);
    pBinaryCode = NULL;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static ThreadLocal<unsigned int> originalRetAddr(0);
static void __declspec(naked) ExecuteFreeStackless_Epilogue()
{
  __asm 
  {
    //just in case function returns int128
    push ecx
    push eax 
    push edx 
    //check stack here
    fstsw ax
    fwait
    and ax, 0x3800  // can be 0 or 1 value on FPU stack
    jz ToNext
    cmp ax, 0x3800 
    jz ToNext
    int 3
  }
ToNext:
  __asm
  {
    //get true return
    lea  eax, originalRetAddr
    push eax 
    call ThreadLocal<unsigned int>::GetValue //now eax has correct pointer to return addr
    add esp, 4  
    mov  eax, dword ptr [eax]  //now eax has correct return addr

    //restore regs
    pop edx 
 
    // do not NOT align stack since we have unaligned this THIS we have forcefully killed on prologue, it is not this anymore but we do not care
    xchg eax, dword ptr [esp] //push true return address for return
    //restore ecx
    mov  ecx, dword ptr [esp + 4] 
    ret
  }
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __declspec(naked) __cdecl DataExecutor::ExecuteFreeStackless() const
{
  //the stack here is: ret_addr(ExecuteFreeStackless), this, epb, ret_addr(ExecuteFree), this, desired stack
  //we want stack like: ret_addr(ExecuteFree), desired stack and we need to calculate call address
  static unsigned const binaryCode       =  offsetof(DataExecutor, pBinaryCode);
  static unsigned const entryPointOffset =  offsetof(DataExecutor, nEntryPointOffset);
  //call address is binaryCode + entryPointOffset
  __asm 
  {
    mov nLastExecutionStatus, 0 //init
    //save return address
    mov eax, esp
    add eax, 12
    push eax         // pointer to ret_addr(ExecuteFree)
    lea  eax, originalRetAddr
    push eax 
    call ThreadLocal<unsigned int>::SetValue
    add esp, 8
    //find call address
    mov ecx , dword ptr [esp + 4] //this
    mov eax , binaryCode
    mov eax , dword ptr [ecx + eax] 
    mov edx , entryPointOffset
    mov edx , dword ptr [ecx + edx] 
    add eax , edx                    //eax now have call address
    //modify stack to have our epilogue called
    mov edx, ExecuteFreeStackless_Epilogue         
    mov dword ptr [esp + 16], edx
    //restore ebp, we still have it from previous call
    mov ebp, dword ptr [esp + 8]
    //move sp
    add esp, 16
    //make jmp to absolute address
    push eax
    ret
  }
}

bool DataExecutor::CheckFPUStack()
{
	WORD stst;
	__asm 
	{
		fstsw stst
		fwait
	}
	return (stst & 0x3800) == 0;
}

static unsigned int GetArgumentSize(char const c)
{
  switch(c)
  {
    case 'I': return sizeof(int);
    case 'F': return sizeof(float);
    case 'D': return sizeof(double);
    case 'C': return sizeof(char);
    case 'P': return sizeof(void *);
  }
  NI_ALWAYS_ASSERT("Wrong type");
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function uses following format for return type and arguments (based on Cosimo Streppone <cosimo@cpan.org>)
//
//I: value is an integer (int)
//F: value is a floating point number (float)
//D: value is a double precision number (double)
//C: value is a char (char)
//P: value is a pointer (to a string, structure, etc...) 
//V: value is a void, can be used for return value
//first untyped argument is pointer to return value is return is not void. Return value should be always 4 byte
void __declspec(naked) DataExecutor::Execute(char const retType, char const *argsType, ...) const
{ 
  __asm
  {
    push ebx
    xor edx, edx
    mov ebx, dword ptr[esp + 16]      //normally it esp +8 but we have this as first parameter, so....
  }
next:
  __asm
  {
    //scan string and invoke classifier
    movzx ecx, byte ptr [ebx]
    jecxz endofscan
    push ebx
    push edx
    push ecx
    call GetArgumentSize         //invoke
    add esp, 4
    pop edx
    pop ebx
    add edx, eax
    inc ebx
    jmp next
  }
endofscan:
  __asm
  {
    pop  ebx
    mov  dword ptr[esp + 12], edx //patch it in the stack
    mov  ecx, dword ptr[esp + 4] //restore this
    jmp  DataExecutor::ExecuteV
  }
}
void DataExecutor::ExecuteV(char const retType, unsigned int const stackSize, ...) const
{
  //init
  nLastExecutionStatus = 0;
  unsigned int tailSize = stackSize / sizeof(int);
  NI_ASSERT(stackSize % sizeof(int) == 0, "Basically stack size should be miltiplier of sizeof(int). If it is not so ivetigation required.");
  void *returnPointer = NULL;
  void *firstArg      = (char *)&stackSize + sizeof(stackSize);
  if(retType != 'V')
  {
    returnPointer = *(void **)((char *)&stackSize + sizeof(stackSize));
    firstArg      = (char *)firstArg + sizeof(void *);
    //initialize return
    *(int *)returnPointer = 0; //return null either pointer or float or char
  }
  void *pEntryPoint = (void *)((char *)pBinaryCode + nEntryPointOffset);
  try
  {
    NI_ASSERT(CheckFPUStack(), "Entry FPU stack corrupted!");
    __asm
    {
      //copy stack
      cld
      mov ecx, tailSize
      sub esp, stackSize
      mov edi, esp
      mov esi, firstArg
      rep movsd
      //invoke
      call pEntryPoint
      //deal with return
      mov ecx, returnPointer
      jecxz retIMM
      mov edx, ecx
      mov dword ptr[ecx], eax
      xor ecx, ecx
      mov cl, retType
      sub cl, 'F'
      jecxz processFloat
      jmp retIMM
    }
processFloat:
    __asm
    {
      fstp dword ptr[edx]
    }
retIMM:
    __asm 
    {
      //restore stack before invoking c++ code
      add esp, stackSize
    }
    NI_ASSERT(CheckFPUStack(), "FPU stack corrupted! Check formula version.");
  }
  catch (...)
  {
    nLastExecutionStatus = 1;
    NI_ALWAYS_ASSERT("Compiled code could not be executed correctly. Please check your code or passed parameters.");
  }
  return;
}
#pragma warning(pop) 

