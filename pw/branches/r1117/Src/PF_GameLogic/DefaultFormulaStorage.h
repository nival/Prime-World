/*
 * DefaultFormulaStorage.h
 *
 *  Created on: 13.11.2009
 *      Author: earnol
 */

#ifndef DEFAULTFORMULASTORAGE_H_
#define DEFAULTFORMULASTORAGE_H_
#include "../../Data/GameLogic/FormulaPars.h"

#include "../System/DataExecutor.h"
#include "../PF_GameLogic/FormulaExecutor.h"

class IDefaultFormulaStorage
{
public:
  virtual FormulaExecutor * ConstructFormulaCached(char const *cpStr, char const *cpKey) const = 0;
  virtual ~IDefaultFormulaStorage() {}
};

void CreateFormulaStorage(ScopedPtr<IDefaultFormulaStorage> &pStorage);

#endif /* DEFAULTFORMULASTORAGE_H_ */
