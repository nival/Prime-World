/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

//////////////////////////////////////////////////
//
// NivalLoader class implementation
//
#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#include <atlbase.h>
#include <ATLCONV.h>
#include <ATLCOmcli.h>
#include <shlobj.h>
#include <Shellapi.h>
#include <Shlwapi.h>
#include <exdisp.h>
#include <objbase.h>
#include <comdef.h>
#include <Winhttp.h>
#include <atlstr.h>
#include <tchar.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "ole32.lib")
//#pragma comment(lib, "atl.lib")

#include "resource.h"
#endif

#ifdef XP_MAC
#include <TextEdit.h>
#endif

#ifdef XP_UNIX
#include <string.h>
#endif

#pragma warning(disable: 4996)

#include "process.h"
#include "plugin.h"
#include "npfunctions.h"
#include <System/stdafx.h>
#include <System/ZipFileSystem.h>
#include <System/FilePath.h>

static NPIdentifier sDocument_id;
static NPIdentifier sBody_id;
static NPIdentifier sPluginType_id;
static NPObject *sWindowObj;

class CoInit  
{  
  HRESULT hr;
public:  
  CoInit() { hr = CoInitialize(NULL); }  
  ~CoInit() { if(S_OK == hr) CoUninitialize(); }  
};  

int __cdecl GetMallocs(void)
{
  return 0;
}
/*
// Helper class that can be used to map calls to the NPObject hooks
// into virtual methods on instances of classes that derive from this
// class.
class ScriptablePluginObjectBase : public NPObject
{
public:
  ScriptablePluginObjectBase(NPP npp)
    : mNpp(npp)
  {
  }

  virtual ~ScriptablePluginObjectBase()
  {
  }

  // Virtual NPObject hooks called through this base class. Override
  // as you see fit.
  virtual void Invalidate();
  virtual bool HasMethod(NPIdentifier name);
  virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                      uint32_t argCount, NPVariant *result);
  virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
                             NPVariant *result);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
  virtual bool RemoveProperty(NPIdentifier name);
  virtual bool Enumerate(NPIdentifier **identifier, uint32_t *count);
  virtual bool Construct(const NPVariant *args, uint32_t argCount,
                         NPVariant *result);

public:
  static void _Deallocate(NPObject *npobj);
  static void _Invalidate(NPObject *npobj);
  static bool _HasMethod(NPObject *npobj, NPIdentifier name);
  static bool _Invoke(NPObject *npobj, NPIdentifier name,
                      const NPVariant *args, uint32_t argCount,
                      NPVariant *result);
  static bool _InvokeDefault(NPObject *npobj, const NPVariant *args,
                             uint32_t argCount, NPVariant *result);
  static bool _HasProperty(NPObject * npobj, NPIdentifier name);
  static bool _GetProperty(NPObject *npobj, NPIdentifier name,
                           NPVariant *result);
  static bool _SetProperty(NPObject *npobj, NPIdentifier name,
                           const NPVariant *value);
  static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
  static bool _Enumerate(NPObject *npobj, NPIdentifier **identifier,
                         uint32_t *count);
  static bool _Construct(NPObject *npobj, const NPVariant *args,
                         uint32_t argCount, NPVariant *result);

protected:
  NPP mNpp;
};

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)                        \
static NPClass s##_class##_NPClass = {                                        \
  NP_CLASS_STRUCT_VERSION_CTOR,                                               \
  ctor,                                                                       \
  ScriptablePluginObjectBase::_Deallocate,                                    \
  ScriptablePluginObjectBase::_Invalidate,                                    \
  ScriptablePluginObjectBase::_HasMethod,                                     \
  ScriptablePluginObjectBase::_Invoke,                                        \
  ScriptablePluginObjectBase::_InvokeDefault,                                 \
  ScriptablePluginObjectBase::_HasProperty,                                   \
  ScriptablePluginObjectBase::_GetProperty,                                   \
  ScriptablePluginObjectBase::_SetProperty,                                   \
  ScriptablePluginObjectBase::_RemoveProperty,                                \
  ScriptablePluginObjectBase::_Enumerate,                                     \
  ScriptablePluginObjectBase::_Construct                                      \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass

void
ScriptablePluginObjectBase::Invalidate()
{
}

bool
ScriptablePluginObjectBase::HasMethod(NPIdentifier name)
{
  return false;
}

bool
ScriptablePluginObjectBase::Invoke(NPIdentifier name, const NPVariant *args,
                                   uint32_t argCount, NPVariant *result)
{
  return false;
}

bool
ScriptablePluginObjectBase::InvokeDefault(const NPVariant *args,
                                          uint32_t argCount, NPVariant *result)
{
  return false;
}

bool
ScriptablePluginObjectBase::HasProperty(NPIdentifier name)
{
  return false;
}

bool
ScriptablePluginObjectBase::GetProperty(NPIdentifier name, NPVariant *result)
{
  return false;
}

bool
ScriptablePluginObjectBase::SetProperty(NPIdentifier name,
                                        const NPVariant *value)
{
  if (name == sBar_id) {
    printf ("bar set\n");

    return true;
  }

  return false;
}

bool
ScriptablePluginObjectBase::RemoveProperty(NPIdentifier name)
{
  return false;
}

bool
ScriptablePluginObjectBase::Enumerate(NPIdentifier **identifier,
                                      uint32_t *count)
{
  return false;
}

bool
ScriptablePluginObjectBase::Construct(const NPVariant *args, uint32_t argCount,
                                      NPVariant *result)
{
  return false;
}

// static
void
ScriptablePluginObjectBase::_Deallocate(NPObject *npobj)
{
  // Call the virtual destructor.
  delete (ScriptablePluginObjectBase *)npobj;
}

// static
void
ScriptablePluginObjectBase::_Invalidate(NPObject *npobj)
{
  ((ScriptablePluginObjectBase *)npobj)->Invalidate();
}

// static
bool
ScriptablePluginObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name)
{
  return ((ScriptablePluginObjectBase *)npobj)->HasMethod(name);
}

// static
bool
ScriptablePluginObjectBase::_Invoke(NPObject *npobj, NPIdentifier name,
                                    const NPVariant *args, uint32_t argCount,
                                    NPVariant *result)
{
  return ((ScriptablePluginObjectBase *)npobj)->Invoke(name, args, argCount,
                                                       result);
}

// static
bool
ScriptablePluginObjectBase::_InvokeDefault(NPObject *npobj,
                                           const NPVariant *args,
                                           uint32_t argCount,
                                           NPVariant *result)
{
  return ((ScriptablePluginObjectBase *)npobj)->InvokeDefault(args, argCount,
                                                              result);
}

// static
bool
ScriptablePluginObjectBase::_HasProperty(NPObject * npobj, NPIdentifier name)
{
  return ((ScriptablePluginObjectBase *)npobj)->HasProperty(name);
}

// static
bool
ScriptablePluginObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name,
                                         NPVariant *result)
{
  return ((ScriptablePluginObjectBase *)npobj)->GetProperty(name, result);
}

// static
bool
ScriptablePluginObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name,
                                         const NPVariant *value)
{
  return ((ScriptablePluginObjectBase *)npobj)->SetProperty(name, value);
}

// static
bool
ScriptablePluginObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
  return ((ScriptablePluginObjectBase *)npobj)->RemoveProperty(name);
}

// static
bool
ScriptablePluginObjectBase::_Enumerate(NPObject *npobj,
                                       NPIdentifier **identifier,
                                       uint32_t *count)
{
  return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool
ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args,
                                       uint32_t argCount, NPVariant *result)
{
  return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount,
                                                          result);
}


class ConstructablePluginObject : public ScriptablePluginObjectBase
{
public:
  ConstructablePluginObject(NPP npp)
    : ScriptablePluginObjectBase(npp)
  {
  }

  virtual bool Construct(const NPVariant *args, uint32_t argCount,
                         NPVariant *result);
};

static NPObject * AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
{
  return new ConstructablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject,
                                 AllocateConstructablePluginObject);

bool
ConstructablePluginObject::Construct(const NPVariant *args, uint32_t argCount,
                                     NPVariant *result)
{
  printf("Creating new ConstructablePluginObject!\n");

  NPObject *myobj =
    NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(ConstructablePluginObject));
  if (!myobj)
    return false;

  OBJECT_TO_NPVARIANT(myobj, *result);

  return true;
}

class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
  ScriptablePluginObject(NPP npp)
    : ScriptablePluginObjectBase(npp)
  {
  }

  virtual bool HasMethod(NPIdentifier name);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                      uint32_t argCount, NPVariant *result);
  virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
                             NPVariant *result);
};

static NPObject *
AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
  return new ScriptablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject,
                                 AllocateScriptablePluginObject);

bool
ScriptablePluginObject::HasMethod(NPIdentifier name)
{
  return name == sFoo_id;
}

bool
ScriptablePluginObject::HasProperty(NPIdentifier name)
{
  return (name == sBar_id ||
          name == sPluginType_id);
}

bool
ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
  VOID_TO_NPVARIANT(*result);

  if (name == sBar_id) {
    static int a = 17;

    INT32_TO_NPVARIANT(a, *result);

    a += 5;

    return true;
  }

  if (name == sPluginType_id) {
    NPObject *myobj =
      NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(ConstructablePluginObject));
    if (!myobj) {
      return false;
    }

    OBJECT_TO_NPVARIANT(myobj, *result);

    return true;
  }

  return true;
}

bool
ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args,
                               uint32_t argCount, NPVariant *result)
{
  if (name == sFoo_id) 
  {
    printf ("foo called!\n");

    NPVariant docv;
    NPN_GetProperty(mNpp, sWindowObj, sDocument_id, &docv);

    NPObject *doc = NPVARIANT_TO_OBJECT(docv);

    NPVariant strv;
    STRINGZ_TO_NPVARIANT("div", strv);

    NPVariant divv;
    NPN_Invoke(mNpp, doc, sCreateElement_id, &strv, 1, &divv);

    STRINGZ_TO_NPVARIANT("I'm created by a plugin!", strv);

    NPVariant textv;
    NPN_Invoke(mNpp, doc, sCreateTextNode_id, &strv, 1, &textv);

    NPVariant v;
    NPN_Invoke(mNpp, NPVARIANT_TO_OBJECT(divv), sAppendChild_id, &textv, 1,
               &v);
    NPN_ReleaseVariantValue(&v);

    NPN_ReleaseVariantValue(&textv);

    NPVariant bodyv;
    NPN_GetProperty(mNpp, doc, sBody_id, &bodyv);

    NPN_Invoke(mNpp, NPVARIANT_TO_OBJECT(bodyv), sAppendChild_id, &divv, 1,
               &v);
    NPN_ReleaseVariantValue(&v);

    NPN_ReleaseVariantValue(&divv);
    NPN_ReleaseVariantValue(&bodyv);

    NPN_ReleaseVariantValue(&docv);

    STRINGZ_TO_NPVARIANT(strdup("foo return val"), *result);

    return PR_TRUE;
  }
  
  return PR_FALSE;
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount,
                                      NPVariant *result)
{
  printf ("ScriptablePluginObject default method called!\n");
  char const cp[] = "default method return val";
  char *c  = (char *)GlobalAlloc(GMEM_FIXED, strlen(cp) + 1);
  strcpy(c , cp);
  STRINGZ_TO_NPVARIANT(c, *result);

  return PR_TRUE;
} */

NivalLoader::NivalLoader(NPP pNPInstance, char const *dllName, char const *commandLine) :
  m_pNPInstance(pNPInstance),
  m_pNPStream(NULL),
  m_bInitialized(FALSE),
  m_pScriptableObject(NULL), 
  m_DllModule(NULL),
  m_pInterface(NULL), 
  m_dllStatus(STATUS_UNLOADED),
  m_hInitThread(NULL),
  m_hInformThread(NULL),
  hLoadThreadCompleted(NULL),
  hLoaderInitCompleted(NULL),
  bWantShutdown(false),
  stopNeeded(false),
  m_hProgressBar(NULL),
  m_hGroupBox(NULL),
  m_hInformationText(NULL), 
  m_bInfHidden(false)
{
#ifdef XP_WIN
  m_hWnd = NULL;
#endif

  if(commandLine)
  {
    m_cmdLine = commandLine;
  }
  if(dllName)
  {
    m_dllURL = dllName;
  }

  hLoadThreadCompleted = CreateEvent(NULL, TRUE, FALSE, NULL);
  hLoaderInitCompleted = CreateEvent(NULL, TRUE, FALSE, NULL);
  
  NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);
  sDocument_id = NPN_GetStringIdentifier("document");
  sBody_id = NPN_GetStringIdentifier("body");
  sPluginType_id = NPN_GetStringIdentifier("PluginType");

  //check for having valid document
  NPIdentifier n = NPN_GetStringIdentifier("document");
  NPVariant    rval;  
  NPVariant    v;  

  if (!NPN_IdentifierIsString(n)) 
  {
    NPString str;
    str.utf8characters = "alert('NPN_IdentifierIsString() test failed!');";
    str.utf8length = strlen(str.utf8characters);

    NPN_Evaluate(m_pNPInstance, sWindowObj, &str, NULL);
  }

  NPObject *doc;

  NPN_GetProperty(m_pNPInstance, sWindowObj, n, &rval);

  if (NPVARIANT_IS_OBJECT(rval) && (doc = NPVARIANT_TO_OBJECT(rval))) {
    n = NPN_GetStringIdentifier("title");

    NPN_GetProperty(m_pNPInstance, doc, n, &rval);

    if (NPVARIANT_IS_STRING(rval)) {
      printf ("title = %s\n", NPVARIANT_TO_STRING(rval).utf8characters);

      NPN_ReleaseVariantValue(&rval);
    }

    n = NPN_GetStringIdentifier("plugindoc");

    OBJECT_TO_NPVARIANT(doc, v);
    NPN_SetProperty(m_pNPInstance, sWindowObj, n, &v);

    NPString str;
    str.utf8characters = "document.getElementById('result').innerHTML += '<p>' + 'NPN_Evaluate() test, document = ' + this + '</p>';";
    str.utf8length = strlen(str.utf8characters);

    NPN_Evaluate(m_pNPInstance, doc, &str, NULL);

    NPN_ReleaseObject(doc);
  }
  
  const char *ua = NPN_UserAgent(m_pNPInstance);
  strcpy(m_String, ua);
}

NivalLoader::~NivalLoader()
{
  if(m_hInformThread != NULL)
  {
    WaitForSingleObject(m_hInformThread, INFINITE);
    m_hInformThread = NULL;
  }
  WaitForSingleObject(hLoadThreadCompleted, INFINITE);
  if(m_pInterface)
  {
    if(m_dllStatus != STATUS_ERROR)
    {
      assert(m_dllStatus == STATUS_INITTED);
    }
    m_pInterface->Release();
    m_pInterface = NULL;
  }
  if(m_DllModule)
  {
    FreeLibrary(m_DllModule);
    m_DllModule = NULL;
  }
  if (sWindowObj)
    NPN_ReleaseObject(sWindowObj);
  if (m_pScriptableObject)
    NPN_ReleaseObject(m_pScriptableObject);

  CloseHandle(hLoadThreadCompleted); hLoadThreadCompleted = NULL;
  CloseHandle(hLoaderInitCompleted); hLoaderInitCompleted = NULL;
  sWindowObj = 0;
}

#ifdef XP_WIN
static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
static WNDPROC lpOldProc = NULL;
#endif

unsigned __stdcall NivalLoader::StatusUpdateThread(void* pArguments)
{
  NivalLoader *pThis = (NivalLoader *)pArguments;
  HANDLE waits[2] = {pThis->hLoaderInitCompleted, pThis->hLoadThreadCompleted};
  while(pThis != NULL && pThis->m_hWnd != NULL && !pThis->bWantShutdown)
  {
    TCHAR *cp = pThis->BuildUserMessage();
    if(cp != NULL)
    {
      SendMessage(pThis->m_hInformationText, WM_SETTEXT, 0, (LPARAM)cp);
      delete [] cp;
    }

    DWORD waitRes = WaitForMultipleObjects(2, waits, FALSE, 150);
    if(WAIT_TIMEOUT != waitRes)
    {
      TCHAR *cp = pThis->BuildUserMessage();
      if(cp != NULL)
      {
        SendMessage(pThis->m_hInformationText, WM_SETTEXT, 0, (LPARAM)cp);
        delete [] cp;
      }
      break;
    }
  }
  _endthreadex(0);
  return 0;
}

unsigned __stdcall NivalLoader::DllLoaderThread(void* pArguments)
{
  NivalLoader *pThis = (NivalLoader *)pArguments;
  pThis->DllLoader();
  _endthreadex(0);
  return 0;
}

static bool IsFolderEmpty(WCHAR const *dirName)
{
  TCHAR *cpNormalized = new TCHAR[MAX_PATH + 1];
  PathCanonicalize(cpNormalized, dirName);
  BOOL bREs = PathIsDirectoryEmpty(cpNormalized);
  delete [] cpNormalized;
  return bREs == TRUE;
}

bool NivalLoader::RemoveDirectoryContent(WCHAR const *dir)
{
  std::wstring wild(dir);
  wild += _T("*.*.");
  wild[wild.length() - 1] = _T('\0');
  SHFILEOPSTRUCT shfo = {0};
  shfo.hwnd  = m_hWnd;
  shfo.wFunc = FO_DELETE;
  shfo.pFrom = wild.c_str();
  shfo.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
  shfo.fAnyOperationsAborted = false;
  shfo.hNameMappings = NULL;
  shfo.lpszProgressTitle = NULL;
  return 0 == SHFileOperation(&shfo);
}

bool NivalLoader::RemoveDirectory(WCHAR const *dir)
{
  RemoveDirectoryContent(dir);
  return 0 != ::RemoveDirectory(dir);
}

bool NivalLoader::PerformFileOperation(WCHAR const *zipFile, WCHAR const *dstDirName, unsigned flags)  
{  
  nstl::string path = NStr::ToMBCS(zipFile);
  nstl::string dstPath = NStr::ToMBCS(dstDirName);
  ZipFileSystem fs(path.c_str());
  nstl::vector<nstl::string> files;
  int filesCount = fs.GetFiles(&files, "", "*.*");
  for (int i=0;i<files.size();++i)
  {
    nstl::string _fileName = NFile::Combine(dstPath, files[i], '/');
    CObj<Stream> f = fs.OpenFile(files[i], FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
    if (f && f->IsOk())
    {
      FileStream newFile(_fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
      if (newFile.IsOk())
      {
        const int bufferSize = 100*1024;
        byte* buffer = new byte[bufferSize];
        while (true)
        {
          int readSize = f->Read(buffer, bufferSize);
          if (readSize > 0)
          {
            newFile.Write(buffer, readSize);
          } else
          {
            break;
          }
        }
        delete [] buffer;
      }
    } else
    {
      return false;
    }
  }
  return true;
/*
  try  
  { 
    CComPtr<IShellDispatch> shell;
    shell.CoCreateInstance(CLSID_Shell);
    CComPtr<Folder> srcZip;
    CComVariant srcFile(zipFile);
    shell->NameSpace(srcFile, &srcZip);
    if(!srcZip)  
    {
      return false;  
    }                  
    CComVariant varDst(dstDirName);
    CComPtr<Folder> dstDir;
    shell->NameSpace(varDst, &dstDir);
    if(!dstDir)  
    {
      return false;  
    }         
    CComPtr<FolderItems> items;
    srcZip->Items(&items);
    if(!items)  
    {
      return false;  
    }
    //clear target
    RemoveDirectoryContent(dstDirName);
    if(IsFolderEmpty(dstDirName) || ((flags & FOP_ZIPWORKAROUND) == 0))
    {
      //directly unpack to destination
      CComVariant varOptions(16|512);
      CComVariant dstItems(items);
      if((flags & FOP_COPY) == FOP_COPY)
      {
        if(dstDir->CopyHere(dstItems, varOptions) != S_OK) 
        {
          return false;  
        }
      }
      else
      {
        assert((flags & FOP_MOVE) == FOP_MOVE);
        if(dstDir->MoveHere(dstItems, varOptions) != S_OK) 
        {
          return false;  
        }
      }
    }
    else
    {
      // do more work

      // find nearest empty folder
      TCHAR const *cpPattern = _T("%s%04d%s");
      std::wstring dstPatternBegin(dstDirName);
      std::wstring dstPatternEnd(dstDirName);
      size_t nTrySize = dstPatternBegin.length() + 10;
      int nTry = 0;
      TCHAR *cpTryPath = new TCHAR[nTrySize];
      dstPatternBegin.erase(dstPatternBegin.length() - 2);
      dstPatternEnd.erase(0, dstPatternEnd.length() - 1);
      do
      {
        _stprintf_s(cpTryPath, nTrySize - 1, cpPattern, dstPatternBegin.c_str(), nTry, dstPatternEnd.c_str());
        PreparePath(cpTryPath);
        nTry ++;
      }while(!IsFolderEmpty(cpTryPath));
      std::wstring dstEmpty(cpTryPath);
      delete [] cpTryPath; cpTryPath = NULL;
      // unpack to it
      PreparePath(dstEmpty.c_str());
      if(PerformFileOperation(zipFile, dstEmpty.c_str(), flags & ~FOP_ZIPWORKAROUND))
      {
        // move from it to destination
        PerformFileOperation(dstEmpty.c_str(), dstDirName, FOP_MOVE);
      }
      // delete what we unpacked
      RemoveDirectory(dstEmpty.c_str());
    }
   return true;  
  }  
  catch(const _com_error &e)  
  {  
    _tprintf(_T("%s\n"), e.ErrorMessage());  
    return false;  
  }  */
}  

void NivalLoader::DllLoader()
{
  CoInit comInitter; // for this thread
  if(m_DllModule == NULL && !bWantShutdown)
  {
    m_dllStatus = STATUS_DOWNLOADING;
    m_downloader.Reset();
    HTTPDownloader::DownloadStatus status =  m_downloader.DownloadFileIfNeeded(m_dllURL.c_str(), GetDownloaderPath(m_hWnd, m_dllURL.c_str()).c_str());
    if(status == HTTPDownloader::DL_COMPLETED || status == HTTPDownloader::DL_NOTREQUIRED)
    {
      //path length
      size_t nLen = m_dllPath.length();   
      //check for last 3 symbols
      if(nLen >= 3 && 0 == _tcsicmp(m_dllPath.substr(nLen - 3, 3).c_str(),_T("zip")))
      {
        TCHAR *cpFName = PathFindFileName(m_dllPath.c_str());
        TCHAR *cpFExt  = PathFindExtension(m_dllPath.c_str());
        std::wstring fname(cpFName, cpFExt - cpFName);
        std::wstring newPath(m_dllPath);
        newPath += _T("unp\\");
        if(PreparePath(newPath.c_str()) && PerformFileOperation(m_dllPath.c_str(), newPath.c_str(), FOP_COPY | FOP_ZIPWORKAROUND))
        {
          newPath += fname;       
          newPath += _T(".dll");
          std::wstring dllPath(newPath.c_str(), PathFindFileName(newPath.c_str()));
          SetDllDirectoryW(dllPath.c_str());
          m_DllModule = LoadLibrary(newPath.c_str());
          m_dllStatus = STATUS_LOADED;
        }
        else
        {
          m_DllModule = NULL;
          m_dllStatus = STATUS_ERROR;
        }
      }
      else
      {
        std::wstring dllPath(m_dllPath.c_str(), PathFindFileName(m_dllPath.c_str()));
        SetDllDirectoryW(dllPath.c_str());
        m_DllModule = LoadLibrary(m_dllPath.c_str());
        DWORD nErr = GetLastError();
        m_dllStatus = STATUS_LOADED;
      }
      if(m_DllModule && !bWantShutdown)
      {
        FARPROC pItf = GetProcAddress(m_DllModule, ITF_NAME_S);
        m_pInterface = ((IBrowserInterface * (*)())pItf)();
        if(m_pInterface && !bWantShutdown)
        {
          m_dllStatus = STATUS_INIALIZING;
          m_dllStatus = (m_pInterface->Init(m_cmdLine.c_str()))?STATUS_INITTED:STATUS_ERROR;
          SetEvent(hLoaderInitCompleted);
        }
      }
    }
  }


  if(m_pInterface && m_dllStatus == STATUS_INITTED && !bWantShutdown)
  {
    if(!m_pInterface->Start(m_hWnd))
    {
      m_dllStatus = STATUS_ERROR;
    }
    else
    {
      m_dllStatus = STATUS_STARTED;
      stopNeeded = true;
    }
  }
  else
  {
    m_dllStatus = STATUS_ERROR;
  }
  SetEvent(hLoaderInitCompleted);
  SetEvent(hLoadThreadCompleted);
}


NPBool NivalLoader::init(NPWindow* pNPWindow)
{
  unsigned threadID;

  ResetEvent(hLoadThreadCompleted);
  ResetEvent(hLoaderInitCompleted);
  bWantShutdown = false;

  if(pNPWindow == NULL)
    return FALSE;

#ifdef XP_WIN
  m_hWnd = (HWND)pNPWindow->window;
  if(m_hWnd == NULL)
    return FALSE;

  // subclass window so we can intercept window messages and
  // do our drawing to it
  lpOldProc = SubclassWindow(m_hWnd, (WNDPROC)PluginWinProc);

  // associate window with our NivalLoader object so we can access 
  // it in the window procedure
  SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
#endif

  m_hInitThread   = (HANDLE)_beginthreadex(NULL, 0, &DllLoaderThread, this, 0, &threadID);
  m_hInformThread = (HANDLE)_beginthreadex(NULL, 0, &StatusUpdateThread, this, 0, &threadID);

  m_Window = pNPWindow;

  RECT rcClient;  // Client area of parent window 
  int cyVScroll, cxVScroll;  // Height of scroll bar arrow 
  GetClientRect(m_hWnd, &rcClient); 
  cyVScroll = GetSystemMetrics(SM_CYCURSOR) + GetSystemMetrics(SM_CYEDGE); 
  cxVScroll = GetSystemMetrics(SM_CXVSCROLL); 

  m_hGroupBox    = CreateWindowEx(WS_EX_CLIENTEDGE, _T("STATIC") ,  (LPTSTR) NULL, SS_LEFT | WS_CHILD | WS_VISIBLE, //BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
    rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, m_hWnd, (HMENU)0, GetPluginModuleHandle(), NULL);
  GetClientRect(m_hGroupBox, &rcClient); 
  m_hInformationText = CreateWindowEx(0, _T("STATIC"),  (LPTSTR) NULL, SS_CENTER | WS_CHILD | WS_VISIBLE,
    rcClient.left + cxVScroll, (rcClient.bottom + rcClient.top) / 2 - 3 * cyVScroll / 2, rcClient.right - 2 * cxVScroll, cyVScroll, m_hGroupBox, (HMENU)0, GetPluginModuleHandle(), NULL);
  m_hProgressBar = CreateWindowEx(WS_EX_CLIENTEDGE, PROGRESS_CLASS,  (LPTSTR) NULL, WS_CHILD | WS_VISIBLE,
    rcClient.left + cxVScroll, (rcClient.bottom + rcClient.top) / 2 + 1 * cyVScroll / 2, rcClient.right - 2 * cxVScroll, cyVScroll, m_hGroupBox, (HMENU)0, GetPluginModuleHandle(), NULL);
  SendMessage(m_hProgressBar, PBM_SETRANGE, 0,  MAKELPARAM(0, 1000));

  m_bInitialized = TRUE;
  return TRUE;
}

void NivalLoader::shut()
{
  bWantShutdown = true;
  if(m_hInformThread != NULL)
  {
    WaitForSingleObject(m_hInformThread, INFINITE);
    m_hInformThread = NULL;
  }

  WaitForSingleObject(hLoadThreadCompleted, INFINITE);
  if(m_pInterface && m_dllStatus == STATUS_STARTED)
  {
    if(!m_pInterface->Stop())
    {
      m_dllStatus = STATUS_ERROR;
    }
    else
    {
      m_dllStatus = (DllStatus)((int)m_dllStatus - 1);
      assert(m_dllStatus == STATUS_INITTED);
    }
    stopNeeded = false;
  }
  else if(m_pInterface && stopNeeded)
  {
    m_pInterface->Stop();
    stopNeeded = false;
  }
#ifdef XP_WIN
  // subclass it back
  SubclassWindow(m_hWnd, lpOldProc);
  m_hWnd = NULL;
#endif

  if(m_pInterface)
  {
    if(m_dllStatus != STATUS_ERROR)
    {
      assert(m_dllStatus == STATUS_INITTED);
    }
    m_pInterface->Release();
    m_pInterface = NULL;
  }
  if(m_DllModule)
  {
    FreeLibrary(m_DllModule);
    m_DllModule = NULL;
  }

  m_bInitialized = FALSE;
}

NPBool NivalLoader::isInitialized()
{
  return m_bInitialized;
}

void  NivalLoader::resize(HWND hwnd)
{
  if(m_pInterface && m_dllStatus == STATUS_STARTED)
  {
    if(hwnd == m_hWnd)
    {
      if(!m_pInterface->Resize(hwnd))
        m_dllStatus = STATUS_ERROR;
    }
    else
    {
      setWindow(hwnd);
    }
  }
}

void  NivalLoader::setWindow(HWND hwnd)
{
  if(m_pInterface && m_dllStatus == STATUS_STARTED)
  {
    m_dllStatus = (m_pInterface->SetWindow(hwnd))? STATUS_STARTED:STATUS_ERROR;
  }
}

int16 NivalLoader::handleEvent(void* event)
{
#ifdef XP_MAC
  NPEvent* ev = (NPEvent*)event;
  if (m_Window) {
    Rect box = { m_Window->y, m_Window->x,
                 m_Window->y + m_Window->height, m_Window->x + m_Window->width };
    if (ev->what == updateEvt) {
      ::TETextBox(m_String, strlen(m_String), &box, teJustCenter);
    }
  }
#endif
  return 0;
}

void NivalLoader::Redraw(bool erase)
{
#ifdef XP_WIN
  InvalidateRect(m_hWnd, NULL, (erase)?TRUE:FALSE);
  UpdateWindow(m_hWnd);
#endif

  if (m_Window) 
  {
    NPRect r =
    {
      (uint16)m_Window->y, (uint16)m_Window->x,
      (uint16)(m_Window->y + m_Window->height),
      (uint16)(m_Window->x + m_Window->width)
    };

    NPN_InvalidateRect(m_pNPInstance, &r);
  }
} 
// this will force to draw a version string in the plugin window
void NivalLoader::showVersion()
{
  const char *ua = NPN_UserAgent(m_pNPInstance);
  strcpy(m_String, ua);

}

// this will clean the plugin window
void NivalLoader::clear()
{
  strcpy(m_String, "");

#ifdef XP_WIN
  InvalidateRect(m_hWnd, NULL, TRUE);
  UpdateWindow(m_hWnd);
#endif
}

void NivalLoader::getVersion(char* *aVersion)
{
  const char *ua = NPN_UserAgent(m_pNPInstance);
  char*& version = *aVersion;
  version = (char*)NPN_MemAlloc(1 + strlen(ua));
  if (version)
    strcpy(version, ua);
}

NPObject * NivalLoader::GetScriptableObject()
{
  /*
  if (!m_pScriptableObject) 
  {
    m_pScriptableObject =
      NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
  }

  if (m_pScriptableObject) 
  {
    NPN_RetainObject(m_pScriptableObject);
  }

  return m_pScriptableObject;*/
  return NULL; 
}

std::wstring &NivalLoader::GetDownloaderPath(HWND hwnd, char const *url)
{
  TCHAR szPath[MAX_PATH];
  USES_CONVERSION;
  if(!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath)))
  {
    return m_dllPath = A2W(url);
  }
  //check should we download something
  if(!PathIsURLA(url))
  {
    return m_dllPath = A2W(url);
  }

  //get dll name
  char const *cpName = NULL;
  for(cpName = url + strlen(url); cpName >= url; cpName--) 
  {
    if(*cpName == '/' || *cpName == '\\')
    {
      cpName += 1;
      break;
    }
    if(cpName == url)
    {
      break;
    }
  }
  m_dllPath = szPath;
  m_dllPath += L"\\Nival\\NivalDownloader\\";
  PreparePath(m_dllPath.c_str());
  m_dllPath += A2W(cpName);
  //
  return m_dllPath;
}

#ifdef XP_WIN
static void* GetAddressOfThisFunction()
{
  return (void *)((ULONG_PTR)GetAddressOfThisFunction);
}

bool NivalLoader::PreparePath(const TCHAR * path)
{
  CComPtr<IWebBrowser2> webBrowser2;
  webBrowser2.CoCreateInstance(CLSID_WebBrowser);
  CComQIPtr<IOleInPlaceActiveObject> pAO(webBrowser2);
  return S_OK == SHPathPrepareForWrite(m_hWnd, pAO, path, SHPPFW_DIRCREATE);
}

void NivalLoader::ShowShowWindows(int nCmdShow, bool bShowProgress)
{
  m_bInfHidden = (nCmdShow == SW_HIDE);
  ShowWindow(m_hGroupBox, nCmdShow);
  ShowWindow(m_hInformationText, nCmdShow);
  ShowWindow(m_hProgressBar, (bShowProgress)?nCmdShow:SW_HIDE);
}

void NivalLoader::MoveShowWindows(bool showProgress)
{
  if(m_hWnd == NULL)
  {
    return;
  }

  RECT rcClient;  // Client area of parent window 
  int cyVScroll, cxVScroll;  // Height of scroll bar arrow 
  GetClientRect(m_hWnd, &rcClient); 
  cyVScroll = GetSystemMetrics(SM_CYCURSOR) + GetSystemMetrics(SM_CYEDGE);//2 * GetSystemMetrics(SM_CYVSCROLL); 
  cxVScroll = GetSystemMetrics(SM_CXVSCROLL); 

  MoveWindow(m_hGroupBox, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, TRUE);
  GetClientRect(m_hGroupBox, &rcClient); 
  MoveWindow(m_hInformationText, rcClient.left + cxVScroll, (rcClient.bottom + rcClient.top) / 2 - 3 * cyVScroll / 2, rcClient.right - 2 * cxVScroll, cyVScroll, TRUE);
  MoveWindow(m_hProgressBar, rcClient.left + cxVScroll, (rcClient.bottom + rcClient.top) / 2 + 1 * cyVScroll / 2, rcClient.right - 2 * cxVScroll, cyVScroll, TRUE);
}

HMODULE NivalLoader::GetPluginModuleHandle()
{
  HMODULE hThis = NULL;
  BOOL bRet  = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)(void *)GetAddressOfThisFunction, &hThis);
  return hThis;
}
WCHAR * NivalLoader::BuildUserMessage()
{
  UINT nCode = IDS_UNSPECIFIEDERROR;
  HMODULE hThis = GetPluginModuleHandle();
  const unsigned int msgSize = 800;
  WCHAR *cp = new WCHAR[msgSize];

  if(cp == NULL)
  {
    return NULL;
  }
  cp[msgSize - 1] = L'\0';

  switch(m_dllStatus)
  {
    case STATUS_UNLOADED:
    {
      nCode = IDS_STATUS_UNLOADED;
      break;
    }
    case STATUS_DOWNLOADING:
    {
      nCode = m_downloader.GetStringMessage(m_downloader.GetStatus());
      break;
    }
    case STATUS_LOADED:
    {
      nCode = IDS_STATUS_LOADED;
      break;
    }
    case STATUS_INIALIZING:
    {
      nCode = IDS_STATUS_INIALIZING;
      break;
    }
    case STATUS_INITTED:
    {
      nCode = IDS_STATUS_INITTED;
      break;
    }
    case STATUS_STARTED:
    {
      nCode = IDS_STATUS_STARTED;
      break;
    }
    case STATUS_ERROR:
    {
      if(m_DllModule == NULL)
      {
        if(m_downloader.GetStatus() == HTTPDownloader::DL_NOTACTIVE || m_downloader.GetStatus() == HTTPDownloader::DL_COMPLETED || m_downloader.GetStatus() == HTTPDownloader::DL_NOTREQUIRED)
        {
          nCode = IDS_COULDNOTLOAD;
        }
        else
          nCode = m_downloader.GetStringMessage(m_downloader.GetStatus());
      }
      else if(m_pInterface == NULL)
      {
        nCode = IDS_NOINTERFACE;
      }
      else if(m_dllStatus == STATUS_ERROR)
      {
        nCode = IDS_STATUS_ERROR;
      }
      break;
    }
  }
  int nStrLen = LoadStringW(hThis, nCode, cp, msgSize - 1);
  if(nStrLen == 0)
  {
    delete [] cp;
    return NULL;
  }
  if(nCode == IDS_DL_RECIEVING) //needs more to do
  {
    WCHAR *cpp = new WCHAR[msgSize];
    _stprintf_s(cpp, msgSize - 1, cp, m_downloader.GetRecievedSize(), m_downloader.GetContentSize());
    delete [] cp;
    SendMessage(m_hProgressBar, PBM_SETPOS, (WPARAM)(int) ((int64)m_downloader.GetRecievedSize() * (int64)1000 / (int64)m_downloader.GetContentSize()),  0L);

    ShowShowWindows(SW_SHOW, true);
    MoveShowWindows(true);
    return cpp;
  }
  else
  {
    ShowShowWindows(SW_SHOW, false);
    MoveShowWindows(false);
  }
  return cp;
}

LRESULT CALLBACK NivalLoader::PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  NivalLoader * pThis = (NivalLoader *)GetWindowLong(hWnd, GWL_USERDATA);

  if(pThis)
  {
    if(pThis->m_pInterface && pThis->m_dllStatus == STATUS_STARTED)
    {
      pThis->HideShowWindows(false);
      return pThis->m_pInterface->CallWindowProc(hWnd, msg, wParam, lParam);
    }
  }
  switch (msg) 
  {
    case WM_PAINT:
    {          
      // draw a frame and display the string
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      RECT rc;
      GetClientRect(hWnd, &rc);
      SelectObject(hdc, GetSysColorBrush(COLOR_3DFACE));
      Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

      WCHAR *cp = NULL;
      size_t nStrLen = 0;
      if(pThis)
        cp = pThis->BuildUserMessage();
      if(cp == NULL || (nStrLen = _tcslen(cp)) <= 0 || pThis->m_hInformationText == NULL)
      {
        DrawTextA(hdc, "General Error.", strlen("General Error."), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      }
      if(cp != NULL) delete [] cp;
      EndPaint(hWnd, &ps);
    }
    break;
  default:
    break;
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}
#endif
