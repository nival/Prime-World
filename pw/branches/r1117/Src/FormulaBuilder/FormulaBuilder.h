/*
 * FormulaBuilder.h
 *
 *  Created on: 20.01.2009
 *      Author: earnol
*/

#ifndef FORMULABUILDER_H_
#define FORMULABUILDER_H_


#include "../System/systemStdAfx.h"
#include "../System/DataExecutor.h"
#include "../System/ScopedPtr.h"
#include "../System/MemoryStream.h"
#include "CoffFile.h"

#ifdef FORMULABUILDER_EXPORT
  #define DLL_CLASS __declspec(dllexport)
#else
  #define DLL_CLASS __declspec(dllimport)
#endif

class DLL_CLASS FormulaBuilder
{
public:
  FormulaBuilder(char const *cpFormula, char const *cpReturnType, char const *cpCExecPath, bool altSecond);
  MemoryStream const &GetPrecompiledDataBinary() const {return sBinaryData;}
  string GetPrecompiledDataBase64();
  float  Execute(void const *pFirst, void const *pSecond, void *pMisc);

private:
  string                  sCppFileName;
  string                  sObjFileName;
  string                  sFormula;
  string                  sCppContent;
  bool PrepareCFile(char const *cpFormula, char const *cpReturnType, bool altSecond);
  bool CompileObjFile(char const *cpExecPath, bool bShowWarning);
  bool ExtractCodeFromFile(char const *cpObjFile);
  template <typename T> string GetReplaceString(char const *cpFormula, char const *cpPattern, T cpWhat);
  void   WriteCpp(FILE *fp, char const * cp);
  MemoryStream            sBinaryData;

  enum LinkEntryType
  {
     EXT_DIRECT,
     EXT_RELATIVE,
     DEF_FUN,
     DEF_EXTERN,
  };
  struct LinkEntry
  {
    char const *  pSymbol;
    DWORD         nOffset;
    LinkEntryType nType;
  };
  int FormulaBuilder::GetSymbolSectionOffset(CoffImage const *image, char const *cpSymbol, int &nSection);

  static const char * const cpToolkitPath;

};

#endif /* FORMULABUILDER_H_ */
