/*
* StringExecutor.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include "stdafx.h"

#include "FormulaExecutor.h"
#include "StringExecutor.h"  
#include "../System/ScopedArray.h"
#include "../libdb/XmlChunkSaver.h"
#include "../libdb/XMLReader.h"

typedef __int32 (__stdcall * CompileCallType)(char const *, char *, int , char const *) ;
ScopedPtr<IDefaultFormulaStorage> ExecutableString::formulaCache;

ExecutableString::ExecutableString()
{
  sString        = "";
  compiledString = "";
  pExecutor      = NULL;
}

int ExecutableString::operator&(IBinSaver &saver)
{
  saver.Add(2, &sString       );
  saver.Add(3, &compiledString);
  saver.Add(4, &returnType    );  
  if(saver.IsReading() && !compiledString.empty())
  {
    if(!formulaCache)
    {
      CreateFormulaStorage(formulaCache); 
    }
    pExecutor = formulaCache->ConstructFormulaCached(compiledString.c_str(), sString.c_str());
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExecutableString::operator&(IXmlSaver &saver)
{
  saver.Add("sString"       , &sString);
  saver.Add("compiledString", &compiledString);
  saver.Add("returnType"    , &returnType    );  
  if(saver.IsReading())
  {
    if(!formulaCache)
    {
      CreateFormulaStorage(formulaCache); 
    }
    pExecutor = formulaCache->ConstructFormulaCached(compiledString.c_str(), sString.c_str());
  }

  CDynamicCast<XmlChunkSaver> pChunkSaver(&saver);
  if (pChunkSaver != NULL && !(pExecutor && ((DataExecutor *)pExecutor)->IsValid()) )
  {
    nstl::string sMsg = NStr::StrFmt("Formula \"%s\" is not compiled properly. In File \"%s\" with ID \"%s\",\n", sString.c_str(), pChunkSaver->GetSourceFileName().c_str(), pChunkSaver->GetSourceId().c_str());
    sMsg += "Current node path:\n";
    for(vector<const NXml::CXmlNode*>::const_iterator it = pChunkSaver->GetChunkLevels().begin(); it <= pChunkSaver->GetChunkLevels().begin() + pChunkSaver->GetCurChunkLevel(); it++)
    {
      sMsg += NStr::StrFmt("Node name: %s.\n", (*it)->GetName().ToString().c_str());
    }
    NI_DATA_ALWAYS_ASSERT(sMsg.c_str());
  }

  return 0;
}

ExecutableString& ExecutableString::operator=( ExecutableString const& other)
{
  sString = other.sString;
  pExecutor = other.pExecutor;
  return *this;
}

bool ExecutableString::GetVariantValue( NScript::VariantValue & value, const char *key ) const
{
  return false;
}





