/*
 * DataExecutor.h
 *
 *  Created on: 19.01.2009
 *      Author: earnol
 */

#ifndef STRINGEXECUTOR_H_
#define STRINGEXECUTOR_H_

#include "FormulaExecutor.h"
#include "../Scripts/Script.h"
#include "DefaultFormulaStorage.h"

struct ExecutableString
{
private:
  static ScopedPtr<IDefaultFormulaStorage> formulaCache;
  CObj<FormulaExecutor> pExecutor; 
protected:
  template <typename T>
  T operator()(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, T defaultValue) const
  {
    if (pExecutor)         
		{
			// Executor present
      T ret = pExecutor->Execute<T>(pFirst, pSecond, pMisc); 
      NI_ASSERT(pExecutor->GetLastExecutionStatus() == 0, NStr::StrFmt("Formula \"%s\" with return type \"%s\" caused exception during execution.", sString.c_str(), returnType.c_str()));
			return ret;
		}
		else
		{
			// Executor doesn't present
			NI_DATA_ASSERT(sString.size() == 0, "String executor is not compiled");
			return defaultValue;
		}
  }

  template <typename T>
  T operator()(IUnitFormulaPars const *pFirst, ICustomFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, T defaultValue) const
  {
    if (pExecutor)         
    {
      // Executor present
      T ret = pExecutor->Execute<T>(pFirst, pSecond, pMisc); 
      NI_ASSERT(pExecutor->GetLastExecutionStatus() == 0, NStr::StrFmt("Formula \"%s\" with return type \"%s\" caused exception during execution.", sString.c_str(), returnType.c_str()));
      return ret;
    }
    else
    {
      // Executor doesn't present
      NI_DATA_ASSERT(sString.size() == 0, "String executor is not compiled");
      return defaultValue;
    }
  }

	template <typename T>
	T Execute(T defaultValue) const
	{
		if (pExecutor)
		{
      T ret = pExecutor->Execute<T>(0, 0, 0);
      NI_ASSERT(pExecutor->GetLastExecutionStatus() == 0, NStr::StrFmt("Formula \"%s\" with return type \"%s\" caused exception during execution. No parameters were passed.", sString.c_str(), returnType.c_str()));
      // Executor present
			return ret;
		}
		else
		{
			// Executor doesn't present
			NI_DATA_ASSERT(sString.size() == 0, "String executor is not compiled");
			return defaultValue;
		}
	}
public:

  string sString;
  string compiledString;
  string returnType;
  ExecutableString();

  int operator&(IBinSaver &saver);
  int operator&(IXmlSaver &saver);

  DWORD CalcCheckSum() const { return 0; }
    
  virtual bool GetVariantValue( NScript::VariantValue & value, const char *key ) const;
  ExecutableString& operator =(const ExecutableString &other);
};

struct ExecutableFloatString: public ExecutableString
{
public:
  int operator&(IBinSaver &saver) {return ExecutableString::operator &(saver);}
  int operator&(IXmlSaver &saver) {return ExecutableString::operator &(saver);}
  float operator()(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, float defaultValue = 0.0f) const
  {
    return ExecutableString::operator()<float>(pFirst, pSecond, pMisc, defaultValue);
  }
  
	/*
	operator float() const
  {
    return ExecutableString::Execute<float>(0.0f);
  } */
};

struct ExecutableBoolString: public ExecutableString
{
public:
  int operator&(IBinSaver &saver) {return ExecutableString::operator &(saver);}
  int operator&(IXmlSaver &saver) {return ExecutableString::operator &(saver);}
  bool operator()(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, bool defaultValue = false) const
  {
    return ExecutableString::operator()<bool>(pFirst, pSecond, pMisc, defaultValue);
  }
	/*
  operator bool() const
  {
		return ExecutableString::Execute<bool>(false);
  } */
};

struct ExecutableBooleanString: public ExecutableString
{
public:
  int operator&(IBinSaver &saver) {return ExecutableString::operator &(saver);}
  int operator&(IXmlSaver &saver) {return ExecutableString::operator &(saver);}
  bool operator()(IUnitFormulaPars const *pFirst, ICustomFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, bool defaultValue = false) const
  {
    return ExecutableString::operator()<bool>(pFirst, pSecond, pMisc, defaultValue);
  }
};


struct ExecutableIntString: public ExecutableString
{
public:
  int operator&(IBinSaver &saver) {return ExecutableString::operator &(saver);}
  int operator&(IXmlSaver &saver) {return ExecutableString::operator &(saver);}
  int operator()(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc, int defaultValue = 0) const
  {
    return ExecutableString::operator()<int>(pFirst, pSecond, pMisc, defaultValue);
  }
	/*
  operator int() const
  {
		return ExecutableString::Execute<int>(0);
  } */
};


#endif /* STRINGEXECUTOR_H_ */
