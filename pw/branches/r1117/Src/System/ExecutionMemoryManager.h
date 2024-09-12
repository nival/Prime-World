/*
 * DataExecutor.h
 *
 *  Created on: 19.01.2009
 *      Author: earnol
 */

#ifndef EXECUTIONMEMORYMANAGER_H_
#define EXECUTIONMEMORYMANAGER_H_
#include "../System/nlist.h"

#ifndef DIM
  #define DIM(a) (sizeof(a)/sizeof(*a))
#endif

class ExecutionMemoryManager
{
public:
#pragma pack(push, 1)
  struct JumpAbsoluteFar
  {
    unsigned char instr_push;  //push opcode
    unsigned int  arg;         //push argument
    unsigned char instr_ret;   //ret code
    JumpAbsoluteFar(): instr_push(0x68), arg(0), instr_ret(0xC3) {}
    JumpAbsoluteFar(void const *addr): instr_push(0x68), arg((unsigned int)addr), instr_ret(0xC3) {}
  };
#pragma pack(pop)
private:
  typedef char * AllocBlockType;
  typedef nstl::list<AllocBlockType> BlockList;
  //initial
  unsigned int startBlockSize;
  unsigned int addtionalBlockSize;
  unsigned int pageSize;
  
  //list executable memory blocks
   BlockList blocksList;

  //free size of current block
  int             freeMem;
  AllocBlockType  pCurrBlock;

  JumpAbsoluteFar *linkJumpTable;

  struct LinkTableEntry
  {
    char const * cpSymbolName;
    void const * pAddress;
  };
  typedef LinkTableEntry * LinkTable;
  static LinkTableEntry  pLinkTable[];

  AllocBlockType allocInternal(unsigned int nStartSize);
  void           fillLinkTable(); 

public:

  ExecutionMemoryManager(unsigned int nStartSize, unsigned int nIncrementSize);
  ~ExecutionMemoryManager();
  void * Alloc(unsigned int nFormulaSize);
  void   Free(void *dataPointer);

  //link table stuff
  static LinkTableEntry const* GetEntryByName(char const *cpName, int &nIndex);
  static int GetSymbolOffset(char const *cpName);
  static int GetLinkSize() {return sizeof(JumpAbsoluteFar);}
  static int GetLinkCount();
  JumpAbsoluteFar *GetLinkJumpTable() { return linkJumpTable;}

  static unsigned int const invalidSymbolOffset = 0x80000000;
};

#endif /* EXECUTIONMEMORYMANAGER_H_ */
