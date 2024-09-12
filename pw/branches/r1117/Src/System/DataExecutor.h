/*
 * DataExecutor.h
 *
 *  Created on: 19.01.2009
 *      Author: earnol
 */

#ifndef DATAEXECUTOR_H_
#define DATAEXECUTOR_H_

#include "ExecutionMemoryManager.h"
#include "StarForce\StarForce.h"

#ifndef DIM
  #define DIM(a) (sizeof(a)/sizeof(*a))
#endif

//#define USE_FREE_EXECUTOR  //define for maximum performance

class FormulaBuilder;

class DataExecutor
{
  //template black magic to have something like isFloat
  template<typename _Tp, _Tp __v> struct integral_constant
  {
    static const _Tp                      value = __v;
    typedef _Tp                           value_type;
    typedef integral_constant<_Tp, __v>   type;
  };
  typedef integral_constant<bool, true>     true_type;
  typedef integral_constant<bool, false>    false_type;
  template<typename _Tp> struct is_float: public false_type { };
  template<> struct is_float<float>: public true_type { };
  template<typename _Tp> struct is_bool: public false_type { };
  template<> struct is_bool<bool>: public true_type { };

#pragma pack(push, 1)
#pragma warning(push)
#pragma warning(disable: 4200)
  struct FormulaHeader
  {
    unsigned char  version;
    unsigned int   entryPointOffset;
    unsigned short relocsNum;
    unsigned short extRelocsNum;
  private:
    unsigned int   relocations[0];
  public:
    FormulaHeader(): version(0), entryPointOffset(0), relocsNum(0), extRelocsNum(0) {}
    unsigned int  GetSize() {return sizeof(*this) + relocsNum * sizeof(relocations[0]) + extRelocsNum * sizeof(relocations[0]);}
    unsigned int  *GetRelocations() { return relocations;}
    unsigned int  *GetExtRelocations() { return relocations + relocsNum;}
  };
#pragma warning(pop)
#pragma pack(pop)
  
  static ScopedPtr<ExecutionMemoryManager> memoryManager;
  static int             nLastExecutionStatus;    

  void          *pBinaryCode;
  unsigned int   nEntryPointOffset;

  void fixDirectRelocs(unsigned int const nBase, unsigned int const nShift, unsigned int const *npOffsetTable, unsigned int nTableSize);
  void fixDirectRelocs(unsigned int const nBase, unsigned int const *npOffsetTable, unsigned int nTableSize);
  void initClass(unsigned char expectedVersion, unsigned char const *dataBuffer, unsigned int nBufferSize);
  static bool CheckFPUStack();
  void __cdecl ExecuteFreeStackless() const;    //do not call this function unless you understand how the whole thing work!!!

public:

  DataExecutor(unsigned char expectedVersion, unsigned char const *dataBuffer, unsigned int nBufferSize);
  DataExecutor(unsigned char expectedVersion, char const *cpBase64String);
  ~DataExecutor();
  bool IsValid() { return pBinaryCode != NULL;}           
  static int GetLastExecutionStatus();
  #ifndef _DEBUG
    #pragma optimize("", off)
    #pragma warning(push)
    #pragma warning(disable: 4731)
  #endif
  template <typename T>  
  T __cdecl ExecuteFree(...) const
  {
    //compiler is the way too silly to get the big idea following asm, but it force it to always generate prologue
    __asm
    {
      xchg ebp,esp
      xchg ebp,esp
    }
    ExecuteFreeStackless();
    //will never reach this spot
    return T(0.0f);
  }
  #ifndef _DEBUG
     #pragma warning(pop)
     #pragma optimize("", on)
  #endif

  void Execute(char const retType, char const *argsType, ...) const;
  void ExecuteV(char const retType, unsigned int const stackSize, ...) const;
  template <typename T>  
  T Execute(void const *pFirst, void const *pSecond, void const *pMisc) const
  {
    NI_VERIFY(pBinaryCode != NULL, "Formula not allocated!", return (T)0;);
    __try
    {
      #ifndef USE_FREE_EXECUTOR
      if(is_float<T>::value)
      {                      
        float retVal = 0;
        ExecuteV('F', 12, &retVal, pFirst, pSecond, pMisc);
        return T(retVal);
      }
      else if(is_bool<T>::value)
      {
        unsigned int retVal = 0;
        // we are too smart to use  Execute('I', "PPP", &retVal, pFirst, pSecond, pMisc); so calculate stack in mind ^_^
        ExecuteV('I', 12, &retVal, pFirst, pSecond, pMisc);
        return T(retVal & 0xFF);
      }
      else
      {
        int retVal = 0;
        // we are too smart to use  Execute('I', "PPP", &retVal, pFirst, pSecond, pMisc); so calculate stack in mind ^_^
        ExecuteV('I', 12, &retVal, pFirst, pSecond, pMisc);
        return T(retVal);
      }
      #else
      return ExecuteFree<T>(pFirst, pSecond, pMisc); //change to this line if max speed is needed
      #endif
    }
    __except(EXCEPTION_EXECUTE_HANDLER) 
    {
      NI_ALWAYS_ASSERT("Compiled code could not be executed correctly. Please check your code or passed parameters.");
      return (T)0; 
    }
  }
  friend FormulaBuilder;
};

#endif /* DATAEXECUTOR_H_ */
