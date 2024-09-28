/*
* FormulaExecutor.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include "stdafx.h"

#include "DefaultFormulaStorage.h"
#include "System/Base64.h"
#include "stdafx.h"


class DefaultFormulaStorage: public IDefaultFormulaStorage
{
  typedef hash_map<string, CObj<FormulaExecutor>> FormulaHash;          
  FormulaHash                         formulaHash;
  FormulaHash                         altHash;
  template <typename T> void StoreVectorToCache(vector<T> const & vec);

public:
  DefaultFormulaStorage();

  FormulaExecutor * ConstructFormulaCached(char const *cpStr, char const *cpKey) const;
  void LoadCache();
};                          

DefaultFormulaStorage::DefaultFormulaStorage()
{
}

FormulaExecutor *DefaultFormulaStorage::ConstructFormulaCached(char const *cpStr, char const *cpKey) const 
{
  FormulaHash::const_iterator formula;
  if(cpStr != NULL && *cpStr != '\0')
  {
    formula = formulaHash.find(cpStr);
    if(formula != formulaHash.end())
    {
      return formula->second;
    }

		return new FormulaExecutor(cpStr);
  }
	else
	{
		formula = altHash.find(cpKey);
		if(formula != altHash.end())
		{
			return formula->second;
		}

		return 0;
	}
}

template <typename T> void DefaultFormulaStorage::StoreVectorToCache(vector<T> const & vec)
{
  for(vector<T>::const_iterator it = vec.begin(); it != vec.end(); it++)
  {
    NI_DATA_VERIFY(it->compiledString.length() > 0, "Compiled string is empty!", continue;);
    NI_DATA_VERIFY(altHash.find(it->sString.c_str()) == altHash.end(), "Already exists in cache!", continue;);
    CObj<FormulaExecutor> executor(new FormulaExecutor(it->compiledString.c_str()));
    if (formulaHash.find(it->compiledString.c_str()) == formulaHash.end())
    {
      bool ret = formulaHash.insertUnique(it->compiledString.c_str(), executor);
      NI_ASSERT(ret, "Insert failed" );
    }
    bool ret = altHash.insertUnique(it->sString.c_str(), executor);
    NI_ASSERT(ret, "Insert failed" );
  }
}

void DefaultFormulaStorage::LoadCache()
{
  //get root
  NDb::Ptr<NDb::DefaultFormulas> pFormulas = NDb::Precache<NDb::DefaultFormulas>( NDb::DBID("GameLogic/DefaultFormulas.DFSC"), 0 );

  if(!pFormulas)
    return;

  StoreVectorToCache<ExecutableFloatString>(pFormulas->floatFormulas);
  StoreVectorToCache<ExecutableBoolString>(pFormulas->boolFormulas);
  StoreVectorToCache<ExecutableIntString>(pFormulas->intFormulas);
}

void CreateFormulaStorage(ScopedPtr<IDefaultFormulaStorage> &pStorage)
{
  Reset(pStorage, new DefaultFormulaStorage());
  DefaultFormulaStorage *pThis = (DefaultFormulaStorage *)Get(pStorage);;
  pThis->LoadCache();
}

