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

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "npapi.h"
#include "npruntime.h"
#include "../Common/BrowserInterface.h"
#include "HTTPDownloader.h"
#include <string>

class NivalLoader
{
public:
  enum DllStatus
  {
    STATUS_UNLOADED,
    STATUS_DOWNLOADING,
    STATUS_LOADED,
    STATUS_INIALIZING,
    STATUS_INITTED,
    STATUS_STARTED,
    STATUS_ERROR,
  };

private:
  NPP m_pNPInstance;

#ifdef XP_WIN
  HWND m_hWnd; 
#endif

  NPWindow * m_Window;
  NPStream * m_pNPStream;
  NPBool     m_bInitialized;
  NPObject * m_pScriptableObject; //needed if we want to control us via java script

  HMODULE  m_DllModule; 
  IBrowserInterface *m_pInterface;
  DllStatus          m_dllStatus;
  HANDLE             m_hInitThread;  
  HANDLE             m_hInformThread;  
  HANDLE             hLoadThreadCompleted;
  HANDLE             hLoaderInitCompleted;
  bool               bWantShutdown;
  bool               stopNeeded;
  HWND               m_hProgressBar; 
  HWND               m_hGroupBox; 
  HWND               m_hInformationText; 
  bool               m_bInfHidden;
  std::string  m_cmdLine;  
  std::string  m_dllURL;  

  //downloaded interface
  std::wstring   m_dllPath; 
  HTTPDownloader m_downloader;

  enum FOP_Flags
  {
    FOP_MOVE = 1,
    FOP_COPY = 2,
    FOP_ZIPWORKAROUND = 4,
  };

public:
  char m_String[128];

public:
  NivalLoader(NPP pNPInstance, char const *dllName, char const *commandLine);
  ~NivalLoader();

  std::wstring &GetDownloaderPath(HWND hwnd, char const *url);

  NPBool init(NPWindow* pNPWindow);
  void   shut();
  NPBool isInitialized();
  
  int16 handleEvent(void* event);
  void  resize(HWND hwnd); 
  void  setWindow(HWND hwnd); 

  void showVersion();
  void Redraw(bool erase);
  void clear();
  void getVersion(char* *aVersion);
  void DllLoader();
  void MoveShowWindows(bool showProgress);
  void ShowShowWindows(int nCmdShow = SW_SHOWNORMAL, bool bShowProgress = false);
  void HideShowWindows(bool bShowProgress){ ShowShowWindows(SW_HIDE, bShowProgress);}
  bool PreparePath(const TCHAR * path);
  WCHAR *BuildUserMessage();
  bool PerformFileOperation(WCHAR const *zipFile, WCHAR const *dstDir, unsigned flags);  
  bool RemoveDirectory(WCHAR const *dir);  
  bool RemoveDirectoryContent(WCHAR const *dir);



  NPObject *GetScriptableObject();
  static HMODULE GetPluginModuleHandle();
  static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  static unsigned __stdcall DllLoaderThread(void* pArguments);
  static unsigned __stdcall StatusUpdateThread(void* pArguments);
};


#endif // __PLUGIN_H__
