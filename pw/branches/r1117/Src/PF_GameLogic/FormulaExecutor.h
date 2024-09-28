/*
 * DataExecutor.h
 *
 *  Created on: 19.01.2009
 *      Author: earnol
 */

#ifndef FORMULAEXECUTOR_H_
#define FORMULAEXECUTOR_H_
#include "../../Data/GameLogic/FormulaPars.h"

#include "../System/DataExecutor.h"



class FormulaExecutor: public DataExecutor, public CObjectBase
{
  OBJECT_METHODS(0x11621CF2, FormulaExecutor);
public:

  FormulaExecutor(unsigned char const *dataBuffer, unsigned int nBufferSize);
  FormulaExecutor(char const *cpBase64String);
  FormulaExecutor(): DataExecutor(0, NULL){;}

  template <typename T>  
  T Execute(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc) const
  {
    return DataExecutor::Execute<T>((void const *)pFirst, (void const *)pSecond, (void const *)pMisc);
  }
  
  template <typename T> 
  T Execute(IUnitFormulaPars const *pFirst, ICustomFormulaPars const *pSecond, IMiscFormulaPars const *pMisc) const
  {
    return DataExecutor::Execute<T>((void const *)pFirst, (void const *)pSecond, (void const *)pMisc);
  }
};
#endif /* FORMULAEXECUTOR_H_ */
