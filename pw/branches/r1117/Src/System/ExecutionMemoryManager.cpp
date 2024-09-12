/*
* DataExecutor.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include "stdafx.h"

#include "ExecutionMemoryManager.h"
#include "../System/Base64.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExecutionMemoryManager::LinkTableEntry ExecutionMemoryManager::pLinkTable[] =
{
  //Keep number of elements in this table even! Just add dummy entry is needed.
  {"_sin", (double (*)(double))sin},
  {"_cos", (double (*)(double))cos},
  {"_sqrt", (double (*)(double))sqrt},
  {"_pow",  (double (*)(double, double))pow},
  {"_fmod", (double (*)(double, double))fmod},
  {"_fabs", (double (*)(double))fabs},
  {"_floor", (double (*)(double))floor},
  {"_ceil", (double (*)(double))ceil}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//returning offset is always negative because it is relative to the end of FarJumpTable
int ExecutionMemoryManager::GetSymbolOffset(char const *cpName)
{
  int nIdx;
  LinkTableEntry const* pEntry = GetEntryByName(cpName , nIdx);
  if(pEntry != NULL)
  {
    //use index 
    return (nIdx - DIM(pLinkTable))* GetLinkSize();
  }
  return invalidSymbolOffset;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExecutionMemoryManager::LinkTableEntry const* ExecutionMemoryManager::GetEntryByName(char const *cpName, int &nIndex)
{
  for(int nI = 0; nI < DIM(pLinkTable); nI++)
  {
    if(strcmp(cpName, pLinkTable[nI].cpSymbolName) == 0)
    {
      nIndex = nI;
      return &pLinkTable[nI];
    }
  }
  return NULL;
}

int  ExecutionMemoryManager::GetLinkCount() 
{
  return DIM(pLinkTable);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ExecutionMemoryManager::ExecutionMemoryManager(unsigned int nStartSize, unsigned int nIncrementSize):
startBlockSize(nStartSize)
,addtionalBlockSize(nIncrementSize)
,freeMem(0)
,pCurrBlock(NULL)
,pageSize(0)
{
  SYSTEM_INFO sysInfo;
  GetSystemInfo(&sysInfo);
  pageSize = sysInfo.dwPageSize;

  //correct sizes
  if(startBlockSize % pageSize != 0)
  {
    startBlockSize =  (startBlockSize / pageSize  + 1) * pageSize;
  }
  if(addtionalBlockSize % pageSize != 0)
  {
    addtionalBlockSize =  (addtionalBlockSize / pageSize  + 1) * pageSize;
  }
  
  //allocate start block
  allocInternal(startBlockSize); 

  //make link table
  fillLinkTable();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExecutionMemoryManager::~ExecutionMemoryManager()
{
  for(BlockList::iterator it = blocksList.begin(); it != blocksList.end(); )
  {
    VirtualFree(*it, 0, MEM_RELEASE);
    *it = NULL;
    BlockList::iterator itDel = it;
    it++;
    blocksList.erase(itDel);
    if(blocksList.size() == 0)
      break;
  }
  NI_ASSERT(blocksList.empty(), "Should be empty at this point");
  blocksList.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExecutionMemoryManager::AllocBlockType ExecutionMemoryManager::allocInternal(unsigned int blockSize)
{
  NI_ASSERT(blockSize % pageSize == 0, "Should be aligned");

  void *pBinaryCode = (void *)VirtualAlloc( 0, blockSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

  blocksList.push_back((AllocBlockType)pBinaryCode);

  //init state
  freeMem    = blockSize;
  pCurrBlock = (AllocBlockType)pBinaryCode;
  return pCurrBlock;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExecutionMemoryManager::fillLinkTable()
{
  int nI;

  //init
  linkJumpTable = (JumpAbsoluteFar *)Alloc(GetLinkSize() * GetLinkCount()); 

  //perform dynamic link blindly: just copy all link entries
  for(nI = 0; nI < DIM(pLinkTable); nI++)
  {
    new (linkJumpTable + nI) JumpAbsoluteFar(pLinkTable[nI].pAddress);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * ExecutionMemoryManager::Alloc(unsigned int nFormulaSize)
{
  AllocBlockType pRetAddr = NULL;
  unsigned int   nAllocSize = nFormulaSize;

  //make sure formula is 16 bit aligned (needed for strange compiler tricks)
  if((nAllocSize & 0xF) != 0)
  {
    nAllocSize = (nAllocSize | 0xF) + 1;
  }

  if((int)nAllocSize < freeMem)
  {
    //alloc
    pRetAddr = pCurrBlock;
    //next
    freeMem    -= nAllocSize;
    pCurrBlock += nAllocSize;
  }
  else
  {
    allocInternal(addtionalBlockSize);
    //we need to alloc more
    return Alloc(nAllocSize);
  }
  //NOP entire area
  memset(pRetAddr, 0x90, nAllocSize);
  return pRetAddr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExecutionMemoryManager::Free(void *dataPointer)
{
  return;
}

