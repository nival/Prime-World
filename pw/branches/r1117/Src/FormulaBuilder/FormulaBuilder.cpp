/*
 * FormulaBuilder.cpp
 *
 *  Created on: 20.01.2009
 *      Author: earnol
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include <shlwapi.h>
#using <mscorlib.dll>
#using <System.dll>

#pragma warning(push)
#pragma warning(disable: 4996 4251 4815 4793)
#include "FormulaBuilder.h"
#include "../../Data/GameLogic/FormulaPars.h"
#include "../System/MemoryStream.h"
#include "../System/Base64.h"

using namespace System;
using namespace System::Text::RegularExpressions;
using namespace System::Text;


const char * const FormulaBuilder::cpToolkitPath      = "/../Tools/CCompiler";
static char * const _cpEntryPointNames[] = {
  "?abilityFunctor@@YAMPBUIUnitFormulaPars@@0PBUIMiscFormulaPars@@@Z",
  "?abilityFunctor@@YAHPBUIUnitFormulaPars@@0PBUIMiscFormulaPars@@@Z",
  "?abilityFunctor@@YA_NPBUIUnitFormulaPars@@0PBUIMiscFormulaPars@@@Z",
  "?abilityFunctor@@YA_NPBUIUnitFormulaPars@@PBUICustomFormulaPars@@PBUIMiscFormulaPars@@@Z"
};

class RegExMatcher
{
  public:
  static char *ReplaceText(char const *cpText, char const *cpPattern, char const *cpReplace) 
  {
    System::String ^sText    = ASCIIZ2String(cpText);
    System::String ^sPattern = ASCIIZ2String(cpPattern);
    System::String ^sReplace = ASCIIZ2String(cpReplace);
    return ReplaceText(sText, sPattern, sReplace);
  }

  static char *ReplaceText(char const *cpText, char const *cpPattern, MatchEvaluator ^replaceEval) 
  {
    System::String ^sText    = ASCIIZ2String(cpText);
    System::String ^sPattern = ASCIIZ2String(cpPattern);
    return ReplaceText(sText, sPattern, replaceEval);
  }

  static char *ReplaceText(System::String ^sText, System::String ^sPattern, System::String ^sReplace) 
  {
    System::String^ tResult = gcnew System::String(sText);
    System::String^ result;
    do 
    {
      result = Regex::Replace(tResult, sPattern, sReplace);
      if(tResult == result)
        break;
      tResult = gcnew System::String(result);
    } while (1);
    return String2ASCIIZ(result);
  }

  static char *ReplaceText(System::String ^sText, System::String ^sPattern, MatchEvaluator ^eval) 
  {
    System::String^ tResult = gcnew System::String(sText);
    System::String^ result;
    do 
    {
      result = Regex::Replace(tResult, sPattern, eval);
      if(tResult == result)
        break;
      tResult = gcnew System::String(result);
    } while (1);
    return String2ASCIIZ(result);
  }

  static System::String^ ASCIIZ2String(char const *cpText)
  {
    StringBuilder ^sRet = gcnew StringBuilder();
    
    char const *cpEnd = cpText + strlen(cpText);
    for(char const *cp = cpText; cp < cpEnd; cp++)
    {
      wchar_t c = *cp;
      sRet = sRet->Append(c);
    }
    return sRet->ToString();
  }
  static char *String2ASCIIZ(String ^sStr)
  {
    System::Int32 nLen = sStr->Length;
    TCHAR* lpName = new char[nLen + 1];
    Int32 nI;
    for(nI = 0; nI < nLen; nI++)
    {
      lpName[nI] = sStr->default[nI];
    }
    lpName[nI] = char('\0');
    return lpName;
  }

  static System::String^ GetObjectNameEvaluator( Match^ m )
  {
    System::String^ matched = m->Value;
    System::String^ firstChar = matched->Substring(0, 1);
    firstChar = firstChar->ToUpper();
    matched = matched->Remove(0, 1);
    matched = Regex::Replace(matched, "\\.", "");
    matched = "GetObject" + firstChar + matched + "()->";
    return matched;
  }

};


FormulaBuilder::FormulaBuilder(char const *cpFormula, char const *cpReturnType, char const *cpCExecPath, bool altSecond = false)
{
  static string sGuardFormula = "";
  string sExecPath;
  if(cpCExecPath == NULL)
  {
    char curdir[MAX_PATH];
    _getcwd(curdir, MAX_PATH - 1);
    sExecPath = curdir;
    if(sExecPath[0] != '\"')
    {
      sExecPath = "\""; 
      sExecPath += curdir;
      sExecPath += "\""; 
    }
    sExecPath.erase(sExecPath.begin() + sExecPath.length() - 1);
    sExecPath += cpToolkitPath;
    sExecPath += "/cl.exe\"";
  }
  else
  {
    sExecPath = cpCExecPath;
  }
  char *templ  = "tcf";
  char *result;

  result = _tempnam(getenv("TEMP"), templ);
  sCppFileName = result;
  sObjFileName = sCppFileName;
  sCppFileName += ".cpp";
  sObjFileName += ".obj";

  sFormula = cpFormula;
  bool bShowWarning = true;
  if(sGuardFormula == cpFormula)
  {
    bShowWarning = false;
  }

  HANDLE hCompileMutex;
  while(NULL == (hCompileMutex = CreateMutex(0, TRUE, "FormulaCompileMutex")) && (GetLastError() == ERROR_ALREADY_EXISTS))
  {
    Sleep(10);
  }
  
  sGuardFormula = cpFormula;
  bool bOk = PrepareCFile(cpFormula, cpReturnType, altSecond);
  NI_VERIFY(bOk, "Unable to generare cpp file for compiler.", CloseHandle(hCompileMutex); return;);
  bOk = CompileObjFile(sExecPath.c_str(), bShowWarning);
  NI_VERIFY(bOk, "Unable to compile cpp file.", CloseHandle(hCompileMutex); return;);
  bOk = ExtractCodeFromFile(sObjFileName.c_str());
  NI_VERIFY(bOk, "Unable to parse obj file.", CloseHandle(hCompileMutex); return;);
  CloseHandle(hCompileMutex); 
}

template <typename T>
nstl::string FormulaBuilder::GetReplaceString(char const *cpFormula, char const *cpPattern, T cpWhat)
{
  char *cp = RegExMatcher::ReplaceText(cpFormula, cpPattern, cpWhat);
  nstl::string sRet(cp);
  delete [] cp;
  return sRet;
}
void FormulaBuilder::WriteCpp(FILE *fp, char const *cp)
{
  fprintf(fp, cp);
  sCppContent += cp;
}

bool FormulaBuilder::PrepareCFile(char const *cpFormula, char const *cpReturnType, bool altSecond)
{
  FILE *fp;
  fopen_s(&fp, sCppFileName.c_str(), "wt");
  if(fp == NULL)
  {
    return false;
  }
  WriteCpp(fp, "#include <math.h>\n#include \"FormulaPars.h\"\n    \n");
  WriteCpp(fp, NStr::StrFmt("%s", cpReturnType));
  if(altSecond)
    WriteCpp(fp, " abilityFunctor(IUnitFormulaPars const *pFirst, ICustomFormulaPars const *pSecond, IMiscFormulaPars const *pMisc)\n{\n  return ");
  else
    WriteCpp(fp, " abilityFunctor(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc)\n{\n  return ");

  string sConvertedFormula;

  //
  sConvertedFormula = GetReplaceString(cpFormula                , "(?:(?<=[^A-Za-z_])|(?<=^))sFlag\\(([A-Z0-9]\\w*)\\)", "pFirst->GetFlag($1)");
  if(!altSecond)
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))rFlag\\(([A-Z0-9]\\w*)\\)", "pSecond->GetFlag($1)");

  ////simple interface: Is...
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))sIs([A-Z]\\w*)", "pFirst->Is$1()");
  if(!altSecond)
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))rIs([A-Z]\\w*)", "pSecond->Is$1()");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))mIs([A-Z]\\w*)", "pMisc->Is$1()");

  //simple interface: Get...
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))s([A-Z]\\w*)", "pFirst->Get$1()");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))r([A-Z]\\w*)", "pSecond->Get$1()");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))m([A-Z]\\w*)", "pMisc->Get$1()");

  //constant
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))r\\(", "SwitchByAbilityRank(pMisc->GetRank(),");
  if(!altSecond)
  {
    sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))c([A-Z]\\w*)", "pMisc->GetConstant(\"$1\", pFirst, pSecond)");
    sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))ut_hero\\(", "SwitchByBool(pSecond->UnitCheck(UNITCHECKID_ISHERO),");
	  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))ut_bldg\\(", "SwitchByBool(pSecond->UnitCheck(UNITCHECKID_ISBUILDING),");
  }
	sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))s\\(", "SwitchByBool(");
	sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_])|(?<=^))roll\\(([A-Za-z_0-9->\\(\\)]+)", "SwitchByBool(pMisc->Roll($1)");

  //convert new syntax
  // - object root
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_\\.])|(?<=^))sender\\.(.*)", "pFirst->$1");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_\\.])|(?<=^))receiver\\.(.*)", "pSecond->$1");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=[^A-Za-z_\\.])|(?<=^))appl\\.(.*)", "pMisc->$1");


  //applXXX(YYY) --> FindApplicator("XXX", pMisc, YYY);
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))appl([A-Z][A-Za-z_0-9]*)\\(([A-Za-z_0-9]+)\\)\\.(?:(?=[A-Za-z_0-9]+)|(?=$))", "FindApplicator(\"$1\", pMisc, $2)->");
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))appl([A-Z][A-Za-z_0-9]*)\\(([A-Za-z_0-9]+)\\)(?:(?=[\\s\\+\\-\\?\\\\\\/\\*><=\\),\\.])|(?=$))", "FindApplicator(\"$1\", pMisc, $2)");

  //vName -> GetVariable("Name")
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))v([A-Z][A-Za-z_0-9]*)(?:(?=[\\s\\+\\-\\?\\\\\\/\\*><=\\),])|(?=$))", "GetVariable(\"$1\")");
  //cName -> GetConstant("Name")
  if(!altSecond)
    sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))c([A-Z][A-Za-z_0-9]*)(?:(?=[\\s\\+\\-\\?\\\\\\/\\*><=\\),])|(?=$))", "GetConstant(\"$1\", pFirst, pSecond)");
  //oName -> GetObject("Name")
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))o([A-Z][A-Za-z_0-9]*)\\.", "GetObject(\"$1\")->");
  //Name -> GetName() (варианты: Life, Energy, LifeRegen, etc)
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->)|(?<=\\.))([A-Z][A-Za-z_0-9]*)(?:(?=[\\s\\+\\-\\?\\\\\\/\\*><=\\),])|(?=$))", "Get$1()");
  //name -> GetObjectName() (варианты: master, favorite, target)
  sConvertedFormula = GetReplaceString(sConvertedFormula.c_str(), "(?:(?<=\\->))([a-z]+?)\\.", gcnew MatchEvaluator( &RegExMatcher::GetObjectNameEvaluator));


  WriteCpp(fp, NStr::StrFmt("%s;\n}\n\n", sConvertedFormula.c_str()));
  fclose(fp);
  return true;
}

bool FormulaBuilder::CompileObjFile(char const *cpExecPath, bool bShowWarning)
{
  STARTUPINFO         si;
  PROCESS_INFORMATION pi;
  SECURITY_ATTRIBUTES sa;
  HANDLE              hReadOut;  
  HANDLE              hReadErr;  
  HANDLE              hWriteIn;
  HANDLE              hWriteOut, hReadIn, hWriteErr;

  string sCmdLine(cpExecPath);

  const char *cpIncludePrefix = " -I\"";
  const char *cpInclude1      = "/../Data/GameLogic\"";
  const char *cpInclude2      = cpToolkitPath;

  char curdir[MAX_PATH];
  _getcwd(curdir, MAX_PATH - 1);

  sCmdLine += " ";
  sCmdLine += cpIncludePrefix;
  sCmdLine += curdir;
  sCmdLine += cpInclude1;
  sCmdLine += cpIncludePrefix;
  sCmdLine += curdir;
  sCmdLine += cpInclude2;
  sCmdLine += "\" -c ";
  sCmdLine += sCppFileName;
  
  chdir(getenv("TEMP"));
  //WinExec(sCmdLine.c_str(), SW_HIDE);

  // Prepare security attributes for pipes.
  memset(&sa, 0, sizeof(sa));
  sa.nLength              = sizeof(sa);
  sa.bInheritHandle       = TRUE;
  sa.lpSecurityDescriptor = NULL;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  si.wShowWindow = SW_HIDE;
  ZeroMemory(&pi, sizeof(pi));

  // Create pipe for output redirection
  BOOL bRes;
  bRes = CreatePipe(&hReadOut, &hWriteOut, &sa, 0);
  NI_VERIFY(bRes, NStr::StrFmt("Pipe creation failed."), return false;);
  // Create pipe for input redirection.
  bRes = CreatePipe(&hReadIn, &hWriteIn, &sa, 0);
  NI_VERIFY(bRes, NStr::StrFmt("Pipe creation failed."), return false;);

  // Create pipe for input redirection.
  bRes = CreatePipe(&hReadErr, &hWriteErr, &sa, 0);
  NI_VERIFY(bRes, NStr::StrFmt("Pipe creation failed."), return false;);

  si.hStdInput   = hReadIn;
  si.hStdOutput  = hWriteOut;
  si.hStdError   = hWriteErr;

  // Start the child process. 
  if(!CreateProcess(NULL, (LPSTR)sCmdLine.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) 
  {
    NI_ALWAYS_ASSERT(NStr::StrFmt("CreateProcess for %s failed (%d).\n", sCmdLine.c_str(), GetLastError()));
    return false;
  }
  CloseHandle(hWriteOut);  // child process will write here
  CloseHandle(hWriteErr);  // child process will write here
  CloseHandle(hReadIn  );  // child process will read here

  MemoryStream sErrorOutput;
  char         cpFileBuff[255];
  DWORD        nActuallyRead;       
  while(TRUE) 
  {
    if(!ReadFile(hReadOut, cpFileBuff, sizeof(cpFileBuff) - 1, &nActuallyRead, NULL )) 
    {
      break;
    }
    // Test for the "normal" end of the output
    if(0 == nActuallyRead) 
    {
      break;   // nothing to read, child process has closed the output
    }
    // Write all data from redirected stdout to our own stdout.
    cpFileBuff[nActuallyRead] = '\0';
    sErrorOutput.Write(cpFileBuff, strlen(cpFileBuff));
  }
  cpFileBuff[0] = '\0';
  sErrorOutput.Write(&cpFileBuff[0], 1);

  // Wait until child process exits.
  WaitForSingleObject(pi.hProcess, INFINITE);

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread );
  CloseHandle(   hReadOut);
  CloseHandle(   hReadErr);
  CloseHandle(   hWriteIn);

  chdir(curdir);
  _unlink(sCppFileName.c_str());

  struct __stat64 buf;
  int result= _stat64(sObjFileName.c_str(), &buf);
  if(result != 0 && bShowWarning)
  {
		MessageBox(FindWindow(NULL, "PF - Editor"), NStr::StrFmt("Compilation of formula \"%s\" failed due to the following reason:\n %s\nFile content:\n%s", sFormula.c_str(), sErrorOutput.GetBuffer(), sCppContent.c_str()), "Compilation error", MB_OK | MB_TASKMODAL);
    return false;
  }
  return (result == 0);
}

bool FormulaBuilder::ExtractCodeFromFile(char const *cpObjFile)
{
  CoffImage image;

  MemoryStream      buffer;
  MemoryStream      result;
  vector<LinkEntry> relocations; 
  vector<LinkEntry> backPatch; 
  vector<LinkEntry> extBackPatch; 
  vector<int>       sectionsOffsets;
  image.Read(cpObjFile);

  //now get all non-communal sections sections with
  for(int nI = 0; nI < image.pHdr->nSectionsCount; nI++)
  {
    CoffImage::CoffSection *pSection = &image.pSections[nI];
    sectionsOffsets.push_back(buffer.GetPosition());
    if((pSection->nFlags & IMAGE_SCN_CNT_CODE) == 0 && (pSection->nFlags & IMAGE_SCN_CNT_INITIALIZED_DATA) == 0)
    {
      //section does not contain code
      continue;
    }
    if(strncmp(pSection->szName, ".debug", 6) == 0)
    {
      //section contains debug: not sure we need it
      continue;
    }
    if((pSection->nFlags & IMAGE_SCN_LNK_COMDAT) != 0)
    {
      //skip communal data
      //continue;
    }
    for(int nJ = 0; nJ < pSection->nNumberOfRelocations; nJ++)
    {
      CoffImage::CoffRelocation *pReloc = &pSection->pRelocations[nJ];
      LinkEntry entry;
      entry.pSymbol  = GetName(&image, pReloc->nSymbol);
      entry.nOffset  = buffer.GetPosition() + pReloc->dwOffset;
      if(pReloc->type == IMAGE_REL_I386_DIR32)
      {
        entry.nType    = EXT_DIRECT;
      }
      else if(pReloc->type == IMAGE_REL_I386_REL32)
      {
        entry.nType    = EXT_RELATIVE;
      }
      else
        NI_ALWAYS_ASSERT("Not supported.");
      relocations.push_back(entry);
    }
    
    //copy data
    buffer.Write(pSection->pRawData, pSection->nSizeOfRawData);
  }
  //backup for future use directs
  for(int nJ = relocations.size() - 1; nJ >= 0; nJ--)
  {
    if(relocations[nJ].nType == EXT_DIRECT)
    {
      backPatch.push_back(relocations[nJ]);
    }
  }

  //now link internally whatever we can
  int nSection;
  for(int nJ = relocations.size() - 1; nJ >= 0; nJ--)
  {
    char const *pSymbol = relocations[nJ].pSymbol;
    int nOffset = GetSymbolSectionOffset(&image, pSymbol, nSection);
    if(nOffset >= 0)
    {
      int nSectionOffset = sectionsOffsets[nSection - 1];
      //symbol can be resolved locally
      if(relocations[nJ].nType == EXT_DIRECT)
      {
        *(int *)(buffer.GetBuffer() + relocations[nJ].nOffset) = nSectionOffset + nOffset;
      }
      else if(relocations[nJ].nType == EXT_RELATIVE)
      {
        //now make it relative
        int nRelAddress = nSectionOffset + nOffset - (relocations[nJ].nOffset + 4);
        *(int *)(buffer.GetBuffer() + relocations[nJ].nOffset) = nRelAddress;
      }
      else
      {
        NI_ALWAYS_ASSERT("Unsupported relocation?");
      }
      relocations.erase(relocations.begin() + nJ);
    }
  }

  //now solve all external one
  for(int nJ = relocations.size() - 1; nJ >= 0; nJ--)
  {
    int nOffset = ExecutionMemoryManager::GetSymbolOffset(relocations[nJ].pSymbol);
    NI_VERIFY(nOffset != ExecutionMemoryManager::invalidSymbolOffset, NStr::StrFmt("Symbol %s could not be dynamically linked. It must present in DataExecutor::pLinkTable", relocations[nJ].pSymbol), {MessageBox(FindWindow(NULL, "PF - Editor"), NStr::StrFmt("Linking of formula \"%s\" failed due to unresolved symbol:\n %s", sFormula.c_str(), relocations[nJ].pSymbol), "Link error", MB_OK); return false;});
    if(relocations[nJ].nType == EXT_DIRECT)
    {
      *(int *)(buffer.GetBuffer() + relocations[nJ].nOffset) = nOffset;
      NI_ALWAYS_ASSERT("Need additional testing. Not yet supported.");
    }
    else if(relocations[nJ].nType == EXT_RELATIVE)
    {
      nOffset -= relocations[nJ].nOffset + 4;
      //make offset relative
      *(int *)(buffer.GetBuffer() + relocations[nJ].nOffset) = nOffset;
      //remember external alloc
      extBackPatch.push_back(relocations[nJ]);
    }
    relocations.erase(relocations.begin() + nJ);
  }

  NI_VERIFY(relocations.size() == 0, "Still have unlinked entries", return false;);

  //look foe entry point
  int nEntryPointOffset = -1;
      nSection          = 0; 
  for(int nJ = 0; nJ < DIM(_cpEntryPointNames); nJ++)
  {
    nEntryPointOffset = GetSymbolSectionOffset(&image, _cpEntryPointNames[nJ], nSection);
    if(nEntryPointOffset >= 0)
      break;
  }
  NI_VERIFY(nEntryPointOffset >= 0, "Entry point: function float __cdecl abilityFunctor(struct IUnitFormulaPars const *,struct IUnitFormulaPars const *,struct IMiscFormulaPars *) not found in compiled snippet.", return false;);
  //and fix it
  nEntryPointOffset += sectionsOffsets[nSection - 1];

  //fill header
  DataExecutor::FormulaHeader formHeader;
  //write version
  formHeader.version          = FORMULA_VERSION;
  formHeader.entryPointOffset = nEntryPointOffset;
  formHeader.relocsNum        = backPatch.size();
  formHeader.extRelocsNum     = extBackPatch.size();  
  //write header
  result.Write(&formHeader, sizeof(formHeader));
  for(int nJ = backPatch.size() - 1; nJ >= 0; nJ--)
  {
    result.Write(&backPatch[nJ].nOffset, sizeof(backPatch[nJ].nOffset));
  }
  for(int nJ = extBackPatch.size() - 1; nJ >= 0; nJ--)
  {
    result.Write(&extBackPatch[nJ].nOffset, sizeof(extBackPatch[nJ].nOffset));
  }
  _unlink(cpObjFile);

  //add compiled code to header
  result.Write(buffer.GetBuffer(), buffer.GetSize());

  //store in class
  result.Seek(0, SEEKORIGIN_BEGIN);
  sBinaryData = result;
  sBinaryData.Seek(0, SEEKORIGIN_BEGIN);
  return true;
}

int FormulaBuilder::GetSymbolSectionOffset(CoffImage const *image, char const *cpSymbol, int &nSect)
{
  for(int k = 0; k < (int)image->pHdr->nSymbols; k += image->pSymbols[k].nAuxSymbols + 1 )
  {
    CoffImage::CoffSymbol &symb = image->pSymbols[k];
    int nSection = symb.nSection & 0xFFFF;
    if(nSection > 0 && (symb.nStorageClass == IMAGE_SYM_CLASS_EXTERNAL || symb.nStorageClass == IMAGE_SYM_CLASS_LABEL ||
       (symb.nStorageClass == IMAGE_SYM_CLASS_STATIC && symb.nValue >= 0))) //section is valid
    {
      // function
      if(strcmp(GetName(*image, symb.szName), cpSymbol) == 0)
      {
        nSect = nSection;
        return symb.nValue;
      }
    }
  }
  return -1;
}

string FormulaBuilder::GetPrecompiledDataBase64()
{
  MemoryStream src(GetPrecompiledDataBinary());
  MemoryStream base64;
  src.Seek(0, SEEKORIGIN_BEGIN);
  Base64::Encode(src, base64);
  string str;
  str.reserve(base64.GetSize() + 1);
  str.append(base64.GetBuffer(), base64.GetBuffer() + base64.GetSize());
  return str;
}

struct FormulaBuilderExecutor
{
  static float Execute(DataExecutor const*pExecutor, void const *pFirst, void const *pSecond, void *pMisc)
  {
    __asm nop         //force native code generation
    return pExecutor->Execute<float>(pFirst, pSecond, pMisc);
  }
};
float FormulaBuilder::Execute(void const *pFirst, void const *pSecond, void *pMisc)
{
  ScopedPtr<DataExecutor> pExecutor(new DataExecutor(FORMULA_VERSION, GetPrecompiledDataBase64().c_str()));
  
  float f = FormulaBuilderExecutor::Execute(Get(pExecutor), pFirst, pSecond, pMisc);
  return f;               
}


extern "C"
{
__declspec(dllexport) __int32 __stdcall BuildFormula(char const * cpFormula, char* cpBase64Code, int nEncodeBufferSize, char const * cpReturnType, int altSecond);
}

int __stdcall BuildFormula(char const *cpFormula, char *cpBase64Code, int nEncodeBufferSize, char const *cpReturnType, int altSecond)
{
  FormulaBuilder builder(cpFormula, cpReturnType, NULL, (bool)altSecond);
  //test execute
  //builder.Execute(NULL, NULL, NULL);
  

  if(builder.GetPrecompiledDataBinary().GetSize() == 0)
    return -1;
  string str = builder.GetPrecompiledDataBase64();
  if((str.length() + 1) >= nEncodeBufferSize)
  {
    return 0;
  }
  else
  {
    strncpy(cpBase64Code, str.c_str(), str.length() + 1);
    return 1;
  }
}


#pragma warning(pop)
