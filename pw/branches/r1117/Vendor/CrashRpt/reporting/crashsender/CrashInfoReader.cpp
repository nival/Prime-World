/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashInfoReader.cpp
// Description: Retrieves crash information passed from CrashRpt.dll in form of XML files.
// Authors: zexspectrum
// Date: 2010

#include "stdafx.h"
#include "CrashRpt.h"
#include "CrashInfoReader.h"
#include "strconv.h"
#include "tinyxml.h"
#include "Utility.h"
#include "SharedMem.h"

#define SEND_RECENT_REPORTS_TIMEOUT 2*24*60*60

BOOL ERIFileItem::GetFileInfo(HICON& hIcon, CString& sTypeName, LONGLONG& lSize)
{
	  hIcon = NULL;
	  sTypeName = _T("Unknown");
	  lSize = 0;
	  SHFILEINFO sfi;
	  HANDLE hFile = INVALID_HANDLE_VALUE;

    SHGetFileInfo(m_sSrcFile, 0, &sfi, sizeof(sfi),
        SHGFI_DISPLAYNAME | SHGFI_ICON | SHGFI_TYPENAME | SHGFI_SMALLICON);

	  hIcon = sfi.hIcon;
	  sTypeName = sfi.szTypeName;

	// Open file for reading
    hFile = CreateFile(m_sSrcFile, 
            GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
    if(hFile!=INVALID_HANDLE_VALUE)
	  {
		    // Get file size
		    LARGE_INTEGER lFileSize;
        BOOL bGetSize = GetFileSizeEx(hFile, &lFileSize);
        if(bGetSize)
        {            
			      lSize = lFileSize.QuadPart; 
        }

		    // Clean up
		    CloseHandle(hFile);
	  }

	  return TRUE;
}

//---------------------------------------------------------------------
// CErrorReportInfo impl
//---------------------------------------------------------------------

CErrorReportInfo::CErrorReportInfo()
{
	// Initialize variables.
    m_bSelected = TRUE;
    m_DeliveryStatus = PENDING;    
    m_dwGuiResources = 0;
    m_dwProcessHandleCount = 0;
    m_dwCpusNumber = 0;
    m_uTotalSize = 0;
	m_dwExceptionAddress = 0;
	m_dwExceptionModuleBase = 0;
}

// Destructor.
CErrorReportInfo::~CErrorReportInfo()
{
	
}

CString CErrorReportInfo::GetErrorReportDirName()
{
	return m_sErrorReportDirName;
}

CString CErrorReportInfo::GetCrashGUID()
{
	return m_sCrashGUID;
}

CString CErrorReportInfo::GetAppName()
{
	return m_sAppName;
}

CString CErrorReportInfo::GetAppVersion()
{
	return m_sAppVersion;
}

CString CErrorReportInfo::GetImageName()
{
	return m_sImageName;
}

CString CErrorReportInfo::GetEmailFrom()
{
	return m_sEmailFrom;
}

CString CErrorReportInfo::GetProblemDescription()
{
	return m_sDescription;
}

CString CErrorReportInfo::GetSystemTimeUTC()
{
	return m_sSystemTimeUTC;
}

ULONG64 CErrorReportInfo::GetTotalSize()
{
	m_uTotalSize = CalcUncompressedReportSize();
	return m_uTotalSize;
}

int CErrorReportInfo::GetFileItemCount()
{
	return (int)m_FileItems.size();
}

int CErrorReportInfo::GetModuleItemCount()
{
  return (int)m_ModuleItems.size();
}

BOOL CErrorReportInfo::IsSelected()
{
	return m_bSelected;
}

void CErrorReportInfo::Select(BOOL bSelect)
{
	m_bSelected = bSelect;
}

DELIVERY_STATUS CErrorReportInfo::GetDeliveryStatus()
{
	return m_DeliveryStatus;
}

void CErrorReportInfo::SetDeliveryStatus(DELIVERY_STATUS status)
{
	m_DeliveryStatus = status;
}

ScreenshotInfo& CErrorReportInfo::GetScreenshotInfo()
{
	return m_ScreenshotInfo;
}

void CErrorReportInfo::SetScreenshotInfo(ScreenshotInfo &si)
{
	m_ScreenshotInfo = si;
}

ULONG64 CErrorReportInfo::GetExceptionAddress()
{
	return m_dwExceptionAddress;
}

CString CErrorReportInfo::GetExceptionModule()
{
	return m_sExceptionModule;
}

void CErrorReportInfo::SetExceptionModule(LPCTSTR szExceptionModule)
{
	m_sExceptionModule = szExceptionModule;
}

ULONG64 CErrorReportInfo::GetExceptionModuleBase()
{
	return m_dwExceptionModuleBase;
}

void CErrorReportInfo::SetExceptionModuleBase(ULONG64 dwExceptionModuleBase)
{
	m_dwExceptionModuleBase = dwExceptionModuleBase;
}

CString CErrorReportInfo::GetExceptionModuleVersion()
{
	return m_sExceptionModuleVersion;
}

void CErrorReportInfo::SetExceptionModuleVersion(LPCTSTR szVer)
{
	m_sExceptionModuleVersion = szVer;
}

CString CErrorReportInfo::GetOSName()
{
	return m_sOSName;
}

BOOL CErrorReportInfo::IsOS64Bit()
{
	return m_bOSIs64Bit;
}

CString CErrorReportInfo::GetGeoLocation()
{
	return m_sGeoLocation;
}

DWORD CErrorReportInfo::GetGuiResourceCount()
{
	return m_dwGuiResources;
}

DWORD CErrorReportInfo::GetProcessHandleCount()
{
	return m_dwProcessHandleCount;
}

DWORD CErrorReportInfo::GetCPUsCount()
{
  return m_dwCpusNumber;
}

CString CErrorReportInfo::GetCPUInfo()
{
  return m_sCpuInfo;
}

CString CErrorReportInfo::GetMemUsage()
{
	return m_sMemUsage;
}

CString CErrorReportInfo::GetVirtualMemUsage()
{
  return m_sVirtualMemUsage;
}

CString CErrorReportInfo::GetTotalMem()
{
  return m_sTotalPhysicalMem;
}

ERIFileItem* CErrorReportInfo::GetFileItemByIndex(int nItem)
{
	if(nItem<0 || nItem>=(int)m_FileItems.size())
		return NULL; // No such item

	// Look for n-th item
	std::map<CString, ERIFileItem>::iterator p = m_FileItems.begin();
	for (int i = 0; i < nItem; i++, p++);
	return &p->second;
}

ERIFileItem* CErrorReportInfo::GetFileItemByName(LPCTSTR szDestFileName)
{
	return &m_FileItems[szDestFileName];
}

ERIModuleItem* CErrorReportInfo::GetModuleItemByIndex(int nItem)
{
  if(nItem<0 || nItem>=(int)m_ModuleItems.size())
    return NULL; // No such item

  // Look for n-th item
  std::map<CString, ERIModuleItem>::iterator p = m_ModuleItems.begin();
  for (int i = 0; i < nItem; i++, p++);
  return &p->second;
}

void CErrorReportInfo::AddFileItem(ERIFileItem* pfi)
{
	m_FileItems[pfi->m_sDestFile] = *pfi;
}

BOOL CErrorReportInfo::DeleteFileItemByIndex(int nItem)
{
	// Look for n-th item
	std::map<CString, ERIFileItem>::iterator p = m_FileItems.begin();
	for (int i = 0; i < nItem; i++, p++);
	if(p==m_FileItems.end())
		return FALSE;

	m_FileItems.erase(p);
	return TRUE;
}

// Returns count of custom properties in error report.
int CErrorReportInfo::GetPropCount()
{
	return (int)m_Props.size();
}

// Method that retrieves a property by zero-based index.
BOOL CErrorReportInfo::GetPropByIndex(int nItem, CString& sName, CString& sVal)
{
	sName.Empty();
	sVal.Empty();

	if(nItem<0 || nItem>=(int)m_Props.size())
		return FALSE; // No such item

	// Look for n-th item
	std::map<CString, CString>::iterator p = m_Props.begin();
	for (int i = 0; i < nItem; i++, p++);
	sName = p->first;
	sVal = p->second;
	return TRUE;
}
	
// Adds/replaces a property in crash report.
void CErrorReportInfo::AddProp(LPCTSTR szName, LPCTSTR szVal)
{
	m_Props[szName] = szVal;
}

LPCTSTR CErrorReportInfo::GetProp(LPCTSTR szName)
{
  std::map<CString, CString>::iterator p = m_Props.find(szName);
  if (p != m_Props.end())
    return p->second;

  return 0;
}

int CErrorReportInfo::GetRegKeyCount()
{
	return (int)m_RegKeys.size();
}

// Method that retrieves a property by zero-based index.
BOOL CErrorReportInfo::GetRegKeyByIndex(int nItem, CString& sKeyName, ERIRegKey& rki)
{
	sKeyName.Empty();
	
	if(nItem<0 || nItem>=(int)m_RegKeys.size())
		return FALSE; // No such item

	// Look for n-th item
	std::map<CString, ERIRegKey>::iterator p = m_RegKeys.begin();
	for (int i = 0; i < nItem; i++, p++);
	sKeyName = p->first;
	rki = p->second;
	return TRUE;
}
	
void CErrorReportInfo::AddRegKey(LPCTSTR szKeyName, ERIRegKey& rki)
{
	m_RegKeys[szKeyName] = rki;
}

// This method calculates the total size of files included into error report
LONG64 CErrorReportInfo::CalcUncompressedReportSize()
{
    LONG64 lTotalSize = 0;    
    HANDLE hFile = INVALID_HANDLE_VALUE;  
    CString sMsg;
    BOOL bGetSize = FALSE;
    LARGE_INTEGER lFileSize;

	// Enumerate files contained in the error report
	int i;
	for(i=0; i<GetFileItemCount(); i++)
    {    
		ERIFileItem* pfi = GetFileItemByIndex(i);
				
		// Get name of the file
        CString sFileName = pfi->m_sSrcFile.GetBuffer(0);
		// Open file for reading
        hFile = CreateFile(sFileName, 
            GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
        if(hFile==INVALID_HANDLE_VALUE)
        {            
            continue;
        }

		// Get file size
        bGetSize = GetFileSizeEx(hFile, &lFileSize);
        if(!bGetSize)
        {
            CloseHandle(hFile);
            continue;
        }

		// Update totals
        lTotalSize += lFileSize.QuadPart;

		// Close file
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }

	// Return total file size
    return lTotalSize;
}


//---------------------------------------------------------------------
// CCrashInfoReader impl
//---------------------------------------------------------------------

CCrashInfoReader::CCrashInfoReader()
{
	// Init internal variables.
	m_nCrashRptVersion = 0;
	m_nSmtpPort = 25;
	m_nSmtpProxyPort = 25;	
	m_bSilentMode = FALSE;
	m_bSendErrorReport = TRUE;
	m_bSendMandatory = FALSE;
	m_bShowAdditionalInfoFields = FALSE;
	m_bAllowAttachMoreFiles = FALSE;
	m_bStoreZIPArchives = FALSE;
	m_bSendRecentReports = FALSE;
  m_bLogEnabled = FALSE;
	m_bAppRestart = FALSE;
	m_uPriorities[CR_HTTP] = 3;
	m_uPriorities[CR_SMTP] = 2;
	m_uPriorities[CR_SMAPI] = 1;
	m_bGenerateMinidump = TRUE;
	m_MinidumpType = MiniDumpNormal;
	m_bAddScreenshot = FALSE;
	m_dwScreenshotFlags = 0;
	m_nJpegQuality = 0;
	m_ptCursorPos = CPoint(0, 0);
	m_rcAppWnd = CRect(0, 0, 0, 0);
	m_bAddVideo = FALSE;
	m_dwVideoFlags = 0;
	m_nVideoDuration = 0;
	m_nVideoFrameInterval = 0;
	m_nVideoQuality = 0;
	m_DesiredFrameSize.cx = 0;
	m_DesiredFrameSize.cy = 0;
	m_hWndVideoParent = NULL;
	m_bClientAppCrashed = FALSE;
	m_bQueueEnabled = FALSE;
	m_dwProcessId = 0;
	m_dwThreadId = 0;
	m_pExInfo = NULL;
	m_nExceptionType = 0;
	m_dwExceptionCode = 0;
	m_uFPESubcode = 0;
	m_uInvParamLine = 0;
	m_pCrashDesc = NULL;
}

int CCrashInfoReader::Init(LPCTSTR szFileMappingName)
{ 
	// This method unpacks crash information from a shared memory (file-mapping)
	// and inits the internal variables.

	strconv_t strconv;
    CErrorReportInfo eri;

	// Init shared memory
	if(!m_SharedMem.IsInitialized())
	{
		// Init shared memory
		BOOL bInitMem = m_SharedMem.Init(szFileMappingName, TRUE, 0);
		if(!bInitMem)
		{
			m_sErrorMsg = _T("Error initializing shared memory.");
			return 1;
		}
	}

	// Unpack crash description from shared memory
    m_pCrashDesc = (CRASH_DESCRIPTION*)m_SharedMem.CreateView(0, sizeof(CRASH_DESCRIPTION));

    int nUnpack = UnpackCrashDescription(eri);
    if(0!=nUnpack)
    {
		m_sErrorMsg = _T("Error unpacking crash description.");
        return 2;
    }
	
	// Create LOCAL_APP_DATA\UnsentCrashReports folder (if doesn't exist yet).
    BOOL bCreateFolder = Utility::CreateFolder(m_sUnsentCrashReportsFolder);
    if(!bCreateFolder)
        return 3;

	// Save path to INI file storing settings
    m_sINIFile = m_sUnsentCrashReportsFolder + _T("\\~CrashRpt.ini");          

    if(!m_bSendRecentReports) // We should send report immediately
    { 
        CollectMiscCrashInfo(eri);

        eri.m_sErrorReportDirName = m_sUnsentCrashReportsFolder + _T("\\") + eri.m_sCrashGUID;
        Utility::CreateFolder(eri.m_sErrorReportDirName);		

        m_Reports.push_back(eri);
    }  
    else // We should look for pending error reports
    {
        // Unblock the parent process
        CString sEventName;
        sEventName.Format(_T("Local\\CrashRptEvent_%s"), eri.m_sCrashGUID);
        HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, sEventName);
        if(hEvent!=NULL)
            SetEvent(hEvent);

        // Look for pending error reports and add them to the list
        CString sSearchPattern = m_sUnsentCrashReportsFolder + _T("\\*");
        CFindFile find;
        BOOL bFound = find.FindFile(sSearchPattern);
        while(bFound)
        {
            if(find.IsDirectory() && !find.IsDots()) // Process directories only
            {
                CString sErrorReportDirName = m_sUnsentCrashReportsFolder + _T("\\") + 
                    find.GetFileName();
                CString sFileName = sErrorReportDirName + _T("\\crashrpt.xml");
                CErrorReportInfo eri2;
                eri2.m_sErrorReportDirName = sErrorReportDirName;
				// Read crash description XML from the directory
                if(0==ParseCrashDescription(sFileName, TRUE, eri2))
                {          
					// Calculate crash report size
                    eri2.m_uTotalSize = GetUncompressedReportSize(eri2);
					// Add report to the list
                    m_Reports.push_back(eri2);
                }
            }

            bFound = find.FindNextFile();
        }
    }

	// Done
    return 0;
}

int CCrashInfoReader::UnpackCrashDescription(CErrorReportInfo& eri)
{
	// This method unpacks crash description data from shared memory.

    if(memcmp(m_pCrashDesc->m_uchMagic, "CRD", 3)!=0)
        return 1; // Invalid magic word

    if(m_pCrashDesc->m_dwCrashRptVer!=CRASHRPT_VER)
        return 2; // Invalid CrashRpt version

    // Unpack process ID, thread ID and exception pointers address.
    m_dwProcessId = m_pCrashDesc->m_dwProcessId;
    m_dwThreadId = m_pCrashDesc->m_dwThreadId;
    m_pExInfo = m_pCrashDesc->m_pExceptionPtrs;  
    m_bSendRecentReports = m_pCrashDesc->m_bSendRecentReports;
    m_nExceptionType = m_pCrashDesc->m_nExceptionType;
    if(m_nExceptionType==CR_SEH_EXCEPTION)
    {
        m_dwExceptionCode = m_pCrashDesc->m_dwExceptionCode;    
    }
    else if(m_nExceptionType==CR_CPP_SIGFPE)
    {
        m_uFPESubcode = m_pCrashDesc->m_uFPESubcode;
    }
    else if(m_nExceptionType==CR_CPP_INVALID_PARAMETER)
    {
        UnpackString(m_pCrashDesc->m_dwInvParamExprOffs, m_sInvParamExpr);  
        UnpackString(m_pCrashDesc->m_dwInvParamFunctionOffs, m_sInvParamFunction);  
        UnpackString(m_pCrashDesc->m_dwInvParamFileOffs, m_sInvParamFile);      
        m_uInvParamLine = m_pCrashDesc->m_uInvParamLine;
    }

    // Unpack other info
    UnpackString(m_pCrashDesc->m_dwAppNameOffs, eri.m_sAppName);
    m_sAppName = eri.m_sAppName;
    UnpackString(m_pCrashDesc->m_dwAppVersionOffs, eri.m_sAppVersion);  
    UnpackString(m_pCrashDesc->m_dwCrashGUIDOffs, eri.m_sCrashGUID);  
    UnpackString(m_pCrashDesc->m_dwImageNameOffs, eri.m_sImageName);  
    // Unpack install flags
    DWORD dwInstallFlags = m_pCrashDesc->m_dwInstallFlags;       
    m_bSilentMode = (dwInstallFlags&CR_INST_NO_GUI)!=0; 
    m_bLogEnabled = (dwInstallFlags&CR_INST_ENABLE_LOGGING)!=0;
    m_bSendErrorReport = (dwInstallFlags&CR_INST_DONT_SEND_REPORT)==0;
  	m_bSendMandatory = (dwInstallFlags&CR_INST_SEND_MANDATORY)!=0;
	  m_bShowAdditionalInfoFields = (dwInstallFlags&CR_INST_SHOW_ADDITIONAL_INFO_FIELDS)!=0;
	  m_bAllowAttachMoreFiles = (dwInstallFlags&CR_INST_ALLOW_ATTACH_MORE_FILES)!=0;
    m_bStoreZIPArchives = (dwInstallFlags&CR_INST_STORE_ZIP_ARCHIVES)!=0;
    m_bAppRestart = (dwInstallFlags&CR_INST_APP_RESTART)!=0;
    m_bGenerateMinidump = (dwInstallFlags&CR_INST_NO_MINIDUMP)==0;
    m_bQueueEnabled = (dwInstallFlags&CR_INST_SEND_QUEUED_REPORTS)!=0;
    m_MinidumpType = m_pCrashDesc->m_MinidumpType;    
    UnpackString(m_pCrashDesc->m_dwRestartCmdLineOffs, m_sRestartCmdLine);
    UnpackString(m_pCrashDesc->m_dwUrlOffs, m_sUrl);
    UnpackString(m_pCrashDesc->m_dwEmailToOffs, m_sEmailTo);  
    m_nSmtpPort = m_pCrashDesc->m_nSmtpPort;
    UnpackString(m_pCrashDesc->m_dwSmtpProxyServerOffs, m_sSmtpProxyServer);
    m_nSmtpProxyPort = m_pCrashDesc->m_nSmtpProxyPort;
    UnpackString(m_pCrashDesc->m_dwEmailSubjectOffs, m_sEmailSubject);
    UnpackString(m_pCrashDesc->m_dwEmailTextOffs, m_sEmailText);  
    memcpy(m_uPriorities, m_pCrashDesc->m_uPriorities, sizeof(UINT)*3);
    UnpackString(m_pCrashDesc->m_dwPrivacyPolicyURLOffs, m_sPrivacyPolicyURL);
    UnpackString(m_pCrashDesc->m_dwLangFileNameOffs, m_sLangFileName);  
    UnpackString(m_pCrashDesc->m_dwPathToDebugHelpDllOffs, m_sDbgHelpPath);
    UnpackString(m_pCrashDesc->m_dwUnsentCrashReportsFolderOffs, m_sUnsentCrashReportsFolder);
    m_bAddScreenshot = m_pCrashDesc->m_bAddScreenshot;
    m_dwScreenshotFlags = m_pCrashDesc->m_dwScreenshotFlags; 
    m_nJpegQuality = m_pCrashDesc->m_nJpegQuality;
    UnpackString(m_pCrashDesc->m_dwCustomSenderIconOffs, m_sCustomSenderIcon);  
	  UnpackString(m_pCrashDesc->m_dwSmtpLoginOffs, m_sSmtpLogin);  
	  UnpackString(m_pCrashDesc->m_dwSmtpPasswordOffs, m_sSmtpPassword);  
	  m_bAddVideo = m_pCrashDesc->m_bAddVideo;
    m_dwVideoFlags = m_pCrashDesc->m_dwVideoFlags; 
	  m_nVideoDuration = m_pCrashDesc->m_nVideoDuration;
	  m_nVideoFrameInterval = m_pCrashDesc->m_nVideoFrameInterval;
    m_DesiredFrameSize = m_pCrashDesc->m_DesiredFrameSize;
	  m_hWndVideoParent = m_pCrashDesc->m_hWndVideoParent;
	  m_bClientAppCrashed = m_pCrashDesc->m_bClientAppCrashed;

    DWORD dwOffs = m_pCrashDesc->m_wSize;
    while(dwOffs<m_pCrashDesc->m_dwTotalSize)
    {
        LPBYTE pView = m_SharedMem.CreateView(dwOffs, sizeof(GENERIC_HEADER));
        GENERIC_HEADER* pHeader = (GENERIC_HEADER*)pView;

        if(memcmp(pHeader->m_uchMagic, "FIL", 3)==0)
        {
            // File item entry
            FILE_ITEM* pFileItem = (FILE_ITEM*)m_SharedMem.CreateView(dwOffs, pHeader->m_wSize);

            ERIFileItem fi;
            UnpackString(pFileItem->m_dwSrcFilePathOffs, fi.m_sSrcFile);
            UnpackString(pFileItem->m_dwDstFileNameOffs, fi.m_sDestFile);
            UnpackString(pFileItem->m_dwDescriptionOffs, fi.m_sDesc);
            fi.m_bMakeCopy = pFileItem->m_bMakeCopy;
			      fi.m_bAllowDelete = pFileItem->m_bAllowDelete;

            eri.m_FileItems[fi.m_sDestFile] = fi;

            m_SharedMem.DestroyView((LPBYTE)pFileItem);
        }
        else if(memcmp(pHeader->m_uchMagic, "MIL", 3)==0)
        {
          // File item entry
          MODULE_ITEM* pItem = (MODULE_ITEM*)m_SharedMem.CreateView(dwOffs, pHeader->m_wSize);

          ERIModuleItem item;
          UnpackString(pItem->m_dwModulePathOffs, item.m_sModulePath);
          UnpackString(pItem->m_dwCodeStartOffs, item.m_sCodeStart);
          UnpackString(pItem->m_dwCodeEndOffs, item.m_sCodeEnd);

          eri.m_ModuleItems[item.m_sModulePath] = item;

          m_SharedMem.DestroyView((LPBYTE)pItem);
        }
        else if(memcmp(pHeader->m_uchMagic, "CPR",3 )==0)
        {
            // Custom prop entry
            CUSTOM_PROP* pProp = (CUSTOM_PROP*)m_SharedMem.CreateView(dwOffs, pHeader->m_wSize);

            CString sName;
            CString sValue;
            UnpackString(pProp->m_dwNameOffs, sName);
            UnpackString(pProp->m_dwValueOffs, sValue);      

            eri.m_Props[sName] = sValue;

            m_SharedMem.DestroyView((LPBYTE)pProp);
        }
        else if(memcmp(pHeader->m_uchMagic, "REG", 3)==0)
        {
            // Reg key entry
            REG_KEY* pKey = (REG_KEY*)m_SharedMem.CreateView(dwOffs, pHeader->m_wSize);

            CString sKeyName;
            ERIRegKey rki;
			      rki.m_bAllowDelete = pKey->m_bAllowDelete!=0;
            UnpackString(pKey->m_dwRegKeyNameOffs, sKeyName);
			      UnpackString(pKey->m_dwDstFileNameOffs, rki.m_sDstFileName);      

            eri.m_RegKeys[sKeyName] = rki;

            m_SharedMem.DestroyView((LPBYTE)pKey);
        }
        else if(memcmp(pHeader->m_uchMagic, "STR", 3)==0)
        {
            // Skip string
        }
        else
        {
            ATLASSERT(0); // Unknown header
            return 1;
        }

        dwOffs += pHeader->m_wSize;

        m_SharedMem.DestroyView(pView);
    }

    // Perform some integrity checks

    if(m_pCrashDesc->m_uFileItems!=eri.m_FileItems.size())
    {
        ATLASSERT(0);
        return 1; 
    }

    if(m_pCrashDesc->m_uModuleItems!=eri.m_ModuleItems.size())
    {
      ATLASSERT(0);
      return 1; 
    }

    if(m_pCrashDesc->m_uCustomProps!=eri.m_Props.size())
    {
        ATLASSERT(0);
        return 1; 
    }

    if(m_pCrashDesc->m_uRegKeyEntries!=eri.m_RegKeys.size())
    {
        ATLASSERT(0);
        return 1; 
    }

    // Success
    return 0;
}

int CCrashInfoReader::UnpackString(DWORD dwOffset, CString& str)
{
    STRING_DESC* pStrDesc = (STRING_DESC*)m_SharedMem.CreateView(dwOffset, sizeof(STRING_DESC));
    if(memcmp(pStrDesc, "STR", 3)!=0)
        return 1;

    WORD wLength = pStrDesc->m_wSize;
    if(wLength<=sizeof(STRING_DESC))
        return 2;

    WORD wStrLen = wLength-sizeof(STRING_DESC);

    m_SharedMem.DestroyView((LPBYTE)pStrDesc);
    LPBYTE pStrData = m_SharedMem.CreateView(dwOffset+sizeof(STRING_DESC), wStrLen);
    str = CString((LPCTSTR)pStrData, wStrLen/sizeof(TCHAR));
    m_SharedMem.DestroyView(pStrData);

    return 0;
}

CErrorReportInfo* CCrashInfoReader::GetReport(int nIndex)
{ 
	if(nIndex>=0 && nIndex<(int)m_Reports.size())
		return &m_Reports[nIndex]; 

	return NULL;
}

int CCrashInfoReader::GetReportCount()
{ 
    return (int)m_Reports.size(); 
}

void CCrashInfoReader::DeleteReport(int nIndex)
{
	ATLASSERT(nIndex>=0 && nIndex<(int)m_Reports.size());

	// Delete report files
	Utility::RecycleFile(m_Reports[nIndex].m_sErrorReportDirName, TRUE);

	// Delete from list
	m_Reports[nIndex].m_DeliveryStatus = DELETED;
}

void CCrashInfoReader::DeleteAllReports()
{
	int i;
	for(i=0; i<(int)m_Reports.size(); i++)
	{
		// Delete report files
		Utility::RecycleFile(m_Reports[i].m_sErrorReportDirName, TRUE);

		m_Reports[i].m_DeliveryStatus = DELETED;
	}	
}

void CCrashInfoReader::CollectMiscCrashInfo(CErrorReportInfo& eri)
{   
    // Get crash time
    Utility::GetSystemTimeUTC(eri.m_sSystemTimeUTC);

    // Open parent process handle
    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, 
        FALSE, 
        m_dwProcessId);
		
    if(hProcess!=NULL)
    {	
		SIZE_T uBytesRead = 0;
		BYTE buff[1024];
		memset(&buff, 0, 1024);
		
		// Read exception information from process memory
		if(m_pExInfo!=NULL)
		{			
			if(ReadProcessMemory(hProcess, m_pExInfo, &buff, sizeof(EXCEPTION_POINTERS), &uBytesRead) &&
				uBytesRead==sizeof(EXCEPTION_POINTERS))
			{
				EXCEPTION_POINTERS* pExcPtrs = (EXCEPTION_POINTERS*)buff;

				if(pExcPtrs->ExceptionRecord!=NULL)
				{
					DWORD64 dwExcRecordAddr = (DWORD64)pExcPtrs->ExceptionRecord;
					if(ReadProcessMemory(hProcess, (LPCVOID)dwExcRecordAddr, &buff, sizeof(EXCEPTION_RECORD), &uBytesRead) &&
						uBytesRead==sizeof(EXCEPTION_RECORD))
					{
						EXCEPTION_RECORD* pExcRec = (EXCEPTION_RECORD*)buff;

						eri.m_dwExceptionAddress = (DWORD64)pExcRec->ExceptionAddress;
					}
				}				
			}
		}
		else
			eri.m_dwExceptionAddress = 0;

        // Get number of GUI resources in use  
        eri.m_dwGuiResources = GetGuiResources(hProcess, GR_GDIOBJECTS);

        // Determine if GetProcessHandleCount function available
        typedef BOOL (WINAPI *LPGETPROCESSHANDLECOUNT)(HANDLE, PDWORD);
        HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
        if(hKernel32!=NULL)
        {
            LPGETPROCESSHANDLECOUNT pfnGetProcessHandleCount = 
                (LPGETPROCESSHANDLECOUNT)GetProcAddress(hKernel32, "GetProcessHandleCount");
            if(pfnGetProcessHandleCount!=NULL)
            {    
                // Get count of opened handles
                DWORD dwHandleCount = 0;
                BOOL bGetHandleCount = pfnGetProcessHandleCount(hProcess, &dwHandleCount);
                if(bGetHandleCount)
                    eri.m_dwProcessHandleCount = dwHandleCount;
                else
                    eri.m_dwProcessHandleCount = 0;
            }

            FreeLibrary(hKernel32);
            hKernel32=NULL;
        }

        //Get CPU Information
        Utility::GetCpuDescription( eri.m_sCpuInfo, eri.m_dwCpusNumber );

        // Get memory usage info
        PROCESS_MEMORY_COUNTERS meminfo;
        BOOL bGetMemInfo = GetProcessMemoryInfo(hProcess, &meminfo, 
            sizeof(PROCESS_MEMORY_COUNTERS));
        if(bGetMemInfo)
        {    
            CString sMemUsage, sVMemUsage;
#ifdef _WIN64
            sMemUsage.Format(_T("%I64u"), meminfo.WorkingSetSize/1024);
            sVMemUsage.Format(_T("%I64u"), meminfo.PagefileUsage/1024);
#else
            sMemUsage.Format(_T("%lu"), meminfo.WorkingSetSize/1024);
            sVMemUsage.Format(_T("%lu"), meminfo.PagefileUsage/1024);
#endif 
            //m_sMemUsage = sMemUsage;
            //m_sVirtualMemUsage = sVMemUsage;
            eri.m_sMemUsage = sMemUsage;
            eri.m_sVirtualMemUsage = sVMemUsage;
        }


        MEMORYSTATUSEX globMemStatus;
        ZeroMemory( &globMemStatus, sizeof( globMemStatus ) );
        globMemStatus.dwLength = sizeof( globMemStatus );
        if ( GlobalMemoryStatusEx( &globMemStatus ) )
        {
#ifdef _WIN64
          eri.m_sTotalPhysicalMem.Format( _T( "%I64u" ), globMemStatus.ullTotalPhys / 1024ul );
#else
          eri.m_sTotalPhysicalMem.Format( _T( "%lu" ), globMemStatus.ullTotalPhys / 1024ul );
#endif 
        }

        // Determine the period of time the process is working.
        FILETIME CreationTime, ExitTime, KernelTime, UserTime;
        /*BOOL bGetTimes = */GetProcessTimes(hProcess, &CreationTime, &ExitTime, &KernelTime, &UserTime);
        /*ATLASSERT(bGetTimes);*/
        SYSTEMTIME AppStartTime;
        FileTimeToSystemTime(&CreationTime, &AppStartTime);

        SYSTEMTIME CurTime;
        GetSystemTime(&CurTime);
        ULONG64 uCurTime = Utility::SystemTimeToULONG64(CurTime);
        ULONG64 uStartTime = Utility::SystemTimeToULONG64(AppStartTime);

        // Check that the application works for at least one minute before crash.
        // This might help to avoid cyclic error report generation when the applciation
        // crashes on startup.
        double dDiffTime = (double)(uCurTime-uStartTime)*10E-08;
        if(dDiffTime<60)
        {
            m_bAppRestart = FALSE; // Disable restart.
        } 
    }

    // Get operating system friendly name from registry.
    Utility::GetOSFriendlyName(eri.m_sOSName);

    // Determine if Windows is 64-bit.
    eri.m_bOSIs64Bit = Utility::IsOS64Bit();

    // Get geographic location.
    Utility::GetGeoLocation(eri.m_sGeoLocation);  
}

int CCrashInfoReader::ParseFileList(TiXmlHandle& hRoot, CErrorReportInfo& eri)
{
    strconv_t strconv;

    TiXmlHandle fl = hRoot.FirstChild("FileList");
    if(fl.ToElement()==0)
    {    
        return 1;
    }

    TiXmlHandle fi = fl.FirstChild("FileItem");
    while(fi.ToElement()!=0)
    {
        const char* pszDestFile = fi.ToElement()->Attribute("destfile");
        const char* pszSrcFile = fi.ToElement()->Attribute("srcfile");
        const char* pszDesc = fi.ToElement()->Attribute("description");
        const char* pszMakeCopy = fi.ToElement()->Attribute("makecopy");

        if(pszDestFile!=NULL)
        {
            CString sDestFile = strconv.utf82t(pszDestFile);      
            ERIFileItem item;
            item.m_sDestFile = sDestFile;
            if(pszSrcFile)
                item.m_sSrcFile = strconv.utf82t(pszSrcFile);
            if(pszDesc)
                item.m_sDesc = strconv.utf82t(pszDesc);

            if(pszMakeCopy)
            {
                if(strcmp(pszMakeCopy, "1")==0)
                    item.m_bMakeCopy = TRUE;
                else
                    item.m_bMakeCopy = FALSE;
            }
            else
                item.m_bMakeCopy = FALSE;

            eri.m_FileItems[sDestFile] = item;
        }

        fi = fi.ToElement()->NextSibling("FileItem");
    }

    return 0;
}

int CCrashInfoReader::ParseModuleList(TiXmlHandle& hRoot, CErrorReportInfo& eri)
{
  strconv_t strconv;

  TiXmlHandle fl = hRoot.FirstChild("LoadedModules");
  if(fl.ToElement()==0)
  {    
    return 1;
  }

  TiXmlHandle fi = fl.FirstChild("Module");
  while(fi.ToElement()!=0)
  {
    const char* pszModulePath = fi.ToElement()->Attribute("path");
    const char* pszCodeStart = fi.ToElement()->Attribute("codeStart");
    const char* pszCodeEnd = fi.ToElement()->Attribute("codeEnd");

    if(pszModulePath!=NULL)
    {
      CString sModuleName = strconv.utf82t(pszModulePath);      
      ERIModuleItem item;
      item.m_sModulePath = sModuleName;
      if(pszCodeStart)
        item.m_sCodeStart = strconv.utf82t(pszCodeStart);
      if(pszCodeEnd)
        item.m_sCodeEnd = strconv.utf82t(pszCodeEnd);

      eri.m_ModuleItems[sModuleName] = item;
    }

    fi = fi.ToElement()->NextSibling("Module");
  }

  return 0;
}

int CCrashInfoReader::ParseRegKeyList(TiXmlHandle& hRoot, CErrorReportInfo& eri)
{
    strconv_t strconv;

    TiXmlHandle fl = hRoot.FirstChild("RegKeyList");
    if(fl.ToElement()==0)
    {    
        return 1;
    }

    TiXmlHandle fi = fl.FirstChild("RegKey");
    while(fi.ToElement()!=0)
    {
        const char* pszDestFile = fi.ToElement()->Attribute("destfile");
        const char* pszRegKey = fi.ToElement()->Attribute("name");

        if(pszDestFile!=NULL && pszRegKey!=NULL)
        {
			ERIRegKey rki;
			rki.m_sDstFileName = strconv.utf82t(pszDestFile);      
            CString sRegKey = strconv.utf82t(pszRegKey);

            eri.m_RegKeys[sRegKey] = rki;
        }

        fi = fi.ToElement()->NextSibling("RegKey");
    }

    return 0;
}
static const int PARSE_CRASH_ERR = 1;
static const int PARSE_CRASH_OK = 0;
int CCrashInfoReader::ParseCrashDescription(CString sFileName, BOOL bParseFileItems, CErrorReportInfo& eri)
{
    strconv_t strconv;
    FILE* f = NULL; 

#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));
#endif

    if(f==NULL)
        return PARSE_CRASH_ERR;

    TiXmlDocument doc;
    bool bOpen = doc.LoadFile(f);
    if(!bOpen)
    {
      fclose(f);
      return PARSE_CRASH_ERR;
    }

    TiXmlHandle hRoot = doc.FirstChild("CrashRpt");
    if(hRoot.ToElement()==NULL)
    {
        fclose(f);
        return PARSE_CRASH_ERR;
    }

    {
        TiXmlHandle hCrashGUID = hRoot.FirstChild("CrashGUID");
        if(hCrashGUID.ToElement()!=NULL)
        {
            if(hCrashGUID.FirstChild().ToText()!=NULL)
            {
                const char* szCrashGUID = hCrashGUID.FirstChild().ToText()->Value();
                if(szCrashGUID!=NULL)
                    eri.m_sCrashGUID = strconv.utf82t(szCrashGUID);
            }
        }
    }

    {
        TiXmlHandle hAppName = hRoot.FirstChild("AppName");
        if(hAppName.ToElement()!=NULL)
        {
            const char* szAppName = hAppName.FirstChild().ToText()->Value();
            if(szAppName!=NULL)
                eri.m_sAppName = strconv.utf82t(szAppName);
        }
    }

    {
        TiXmlHandle hAppVersion = hRoot.FirstChild("AppVersion");
        if(hAppVersion.ToElement()!=NULL)
        {
            TiXmlText* pText = hAppVersion.FirstChild().ToText();
            if(pText!=NULL)
            {
                const char* szAppVersion = pText->Value();
                if(szAppVersion!=NULL)
                    eri.m_sAppVersion = strconv.utf82t(szAppVersion);
            }
        }
    }

    {
        TiXmlHandle hImageName = hRoot.FirstChild("ImageName");
        if(hImageName.ToElement()!=NULL)
        {
            TiXmlText* pText = hImageName.FirstChild().ToText();
            if(pText!=NULL)
            {
                const char* szImageName = pText->Value();
                if(szImageName!=NULL)
                    eri.m_sImageName = strconv.utf82t(szImageName);
            }
        }
    }

    {
        TiXmlHandle hSystemTimeUTC = hRoot.FirstChild("SystemTimeUTC");
        if(hSystemTimeUTC.ToElement()!=NULL)
        {
            TiXmlText* pText = hSystemTimeUTC.FirstChild().ToText();
            if(pText!=NULL)
            {
                const char* szSystemTimeUTC = pText->Value();
                if(szSystemTimeUTC!=NULL)
                    eri.m_sSystemTimeUTC = strconv.utf82t(szSystemTimeUTC);
            }
        }
    }

    if(bParseFileItems)
    {
        // Get directory name
        CString sReportDir = sFileName;
        int pos = sFileName.ReverseFind('\\');
        if(pos>=0)
            sReportDir = sFileName.Left(pos);
        if(sReportDir.Right(1)!=_T("\\"))
            sReportDir += _T("\\");

        TiXmlHandle fl = hRoot.FirstChild("FileList");
        if(fl.ToElement()==0)
        {    
            fclose(f);
            return PARSE_CRASH_ERR;
        }

        TiXmlHandle fi = fl.FirstChild("FileItem");
        while(fi.ToElement()!=0)
        {
            const char* pszDestFile = fi.ToElement()->Attribute("name");      
            const char* pszDesc = fi.ToElement()->Attribute("description");      
			      const char* pszOptional = fi.ToElement()->Attribute("optional");      
            //const char* pszMakeCopy = fi.ToElement()->Attribute("makecopy");

            if(pszDestFile!=NULL)
            {
                CString sDestFile = strconv.utf82t(pszDestFile);      
                ERIFileItem item;
                item.m_sDestFile = sDestFile;
                item.m_sSrcFile = sReportDir + sDestFile;
                if(pszDesc)
                    item.m_sDesc = strconv.utf82t(pszDesc);

               /* if(pszMakeCopy && strcmp(pszMakeCopy, "1")==0)
                  item.m_bMakeCopy = TRUE;
                else
                */
                  item.m_bMakeCopy = FALSE;

				        if(pszOptional && strcmp(pszOptional, "1")==0)
					          item.m_bAllowDelete = true;

                // Check that file really exists
                DWORD dwAttrs = GetFileAttributes(item.m_sSrcFile);
                if(dwAttrs!=INVALID_FILE_ATTRIBUTES &&
                    (dwAttrs&FILE_ATTRIBUTE_DIRECTORY)==0)
                {
                    eri.m_FileItems[sDestFile] = item;
                }
            }

            fi = fi.ToElement()->NextSibling("FileItem");
        }    
    }

    ParseModuleList(hRoot, eri);
  
    fclose(f);
    return PARSE_CRASH_OK;
}

BOOL CCrashInfoReader::UpdateUserInfo(CString sEmail, CString sDesc)
{
	// This method validates user-provided Email and problem description
	// and (if valid) uptdates internal fields.
	BOOL bResult = TRUE;

	// If an email address was entered, verify that
    // it [1] contains a @ and [2] the last . comes
    // after the @.
    
    if (sEmail.GetLength()!=0 &&
        (sEmail.Find(_T('@')) < 0 ||
        sEmail.ReverseFind(_T('.')) < 
        sEmail.Find(_T('@'))))
    {
        // Invalid email            
		bResult = FALSE;
    }
	else
	{
		// Update email
		GetReport(0)->m_sEmailFrom = sEmail;
	}

	// Update problem description
	GetReport(0)->m_sDescription = sDesc;	

    // Write user email and problem description to XML
    AddUserInfoToCrashDescriptionXML(
        GetReport(0)->m_sEmailFrom, 
        GetReport(0)->m_sDescription);

	// Save E-mail entered by user to INI file for later reuse.
	SetPersistentUserEmail(sEmail);

	return bResult;
}

BOOL CCrashInfoReader::AddUserInfoToCrashDescriptionXML(CString sEmail, CString sDesc)
{ 
    strconv_t strconv;

    TiXmlDocument doc;

    CString sFileName = m_Reports[0].m_sErrorReportDirName + _T("\\crashrpt.xml");

    FILE* f = NULL; 
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));
#endif

    if(f==NULL)
        return FALSE;

    bool bLoad = doc.LoadFile(f);
    fclose(f);
    if(!bLoad)
    {    
        return FALSE;
    }

    TiXmlNode* root = doc.FirstChild("CrashRpt");
    if(!root)
    {    
        return FALSE;
    }

    // Write user e-mail

    TiXmlHandle hEmail = NULL;
	
	hEmail = root->FirstChild("UserEmail");
	if(hEmail.ToElement()==NULL)
	{
		hEmail = new TiXmlElement("UserEmail");
		root->LinkEndChild(hEmail.ToElement());		
	}
		
	TiXmlText* email_text = NULL;
	if(hEmail.FirstChild().ToText()!=NULL)
	{
		email_text = hEmail.FirstChild().ToText();
		email_text->SetValue(strconv.w2utf8(sEmail));
	}
	else
	{
		email_text = new TiXmlText(strconv.t2utf8(sEmail));
		hEmail.ToElement()->LinkEndChild(email_text);              
	}
	
    // Write problem description

    TiXmlHandle hDesc = NULL;
	
	hDesc = root->FirstChild("ProblemDescription");
	if(hDesc.ToElement()==NULL)
	{
		hDesc = new TiXmlElement("ProblemDescription");
		root->LinkEndChild(hDesc.ToElement());
	}

    TiXmlText* desc_text = NULL;
	if(hDesc.FirstChild().ToText()!=NULL)
	{
		desc_text = hDesc.FirstChild().ToText();
		desc_text->SetValue(strconv.w2utf8(sDesc));
	}
	else
	{
		desc_text = new TiXmlText(strconv.t2utf8(sDesc));
		hDesc.ToElement()->LinkEndChild(desc_text);              
	}

#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("w"));
#else
    _tfopen_s(&f, sFileName, _T("w"));
#endif

    if(f==NULL)
        return FALSE;

    bool bSave = doc.SaveFile(f); 
    fclose(f);
    if(!bSave)
        return FALSE;
    return TRUE;
}

BOOL CCrashInfoReader::AddFilesToCrashReport(int nReport, std::vector<ERIFileItem> FilesToAdd)
{   
    strconv_t strconv;

    TiXmlDocument doc;

    CString sFileName = m_Reports[nReport].m_sErrorReportDirName + _T("\\crashrpt.xml");

    FILE* f = NULL; 
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));
#endif

    if(f==NULL)
    {    
        return FALSE;
    }

    bool bLoad = doc.LoadFile(f);  
    fclose(f);
    if(!bLoad)
    { 
        return FALSE;
    }

    TiXmlNode* root = doc.FirstChild("CrashRpt");
    if(!root)
    { 
        return FALSE;
    }

    TiXmlHandle hFileItems = root->FirstChild("FileList");
    if(hFileItems.ToElement()==NULL)
    {
        hFileItems = new TiXmlElement("FileList");
        root->LinkEndChild(hFileItems.ToNode());
    }

    unsigned i;
    for(i=0; i<FilesToAdd.size(); i++)
    { 
        if(m_Reports[0].m_FileItems.find(FilesToAdd[i].m_sDestFile)!=m_Reports[0].m_FileItems.end())
            continue; // Such file item already exists, skip

        TiXmlHandle hFileItem = new TiXmlElement("FileItem");
        hFileItem.ToElement()->SetAttribute("name", strconv.t2utf8(FilesToAdd[i].m_sDestFile));
        hFileItem.ToElement()->SetAttribute("description", strconv.t2utf8(FilesToAdd[i].m_sDesc));
		    if(FilesToAdd[i].m_bAllowDelete)
			    hFileItem.ToElement()->SetAttribute("optional", "1");
        hFileItems.ToElement()->LinkEndChild(hFileItem.ToNode());              

        m_Reports[nReport].m_FileItems[FilesToAdd[i].m_sDestFile] = FilesToAdd[i];

		if(FilesToAdd[i].m_bMakeCopy)
		{
			CString sDestPath = m_Reports[nReport].m_sErrorReportDirName + _T("\\") + FilesToAdd[i].m_sDestFile;
			CopyFile(FilesToAdd[i].m_sSrcFile, sDestPath, TRUE);
			m_Reports[nReport].m_FileItems[FilesToAdd[i].m_sDestFile].m_sSrcFile = sDestPath;
		}
    }

#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("w"));
#else
    _tfopen_s(&f, sFileName, _T("w"));
#endif

    if(f==NULL)
        return FALSE;

    bool bSave = doc.SaveFile(f); 
    if(!bSave)
        return FALSE;
    fclose(f);
    return TRUE;
}

BOOL CCrashInfoReader::RemoveFilesFromCrashReport(int nReport, std::vector<CString> FilesToRemove)
{   
    strconv_t strconv;

    TiXmlDocument doc;

    CString sFileName = m_Reports[nReport].m_sErrorReportDirName + _T("\\crashrpt.xml");

    FILE* f = NULL; 
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));
#endif

    if(f==NULL)
    {    
        return FALSE;
    }

    bool bLoad = doc.LoadFile(f);  
    fclose(f);
    if(!bLoad)
    { 
        return FALSE;
    }

    TiXmlNode* root = doc.FirstChild("CrashRpt");
    if(!root)
    { 
        return FALSE;
    }

    TiXmlHandle hFileItems = root->FirstChild("FileList");
    if(hFileItems.ToElement()==NULL)
    {
        hFileItems = new TiXmlElement("FileList");
        root->LinkEndChild(hFileItems.ToNode());
    }

    unsigned i;
    for(i=0; i<FilesToRemove.size(); i++)
    { 
		std::map<CString, ERIFileItem>::iterator it = 
			m_Reports[nReport].m_FileItems.find(FilesToRemove[i]);
		if(it==m_Reports[nReport].m_FileItems.end())
            continue; // Such file item name does not exist, skip
		
		strconv_t strconv;
		TiXmlHandle hElem = hFileItems.ToElement()->FirstChild("FileItem");
		while(hElem.ToElement()!=NULL)
		{
			const char* szName = hElem.ToElement()->Attribute("name");
			if(szName!=NULL && strcmp(strconv.t2a(FilesToRemove[i]), szName)==0)
			{
				hFileItems.ToElement()->RemoveChild(hElem.ToElement());              
				break;
			}
			hElem = hElem.ToElement()->NextSibling();
		}
		
		// Remove the file from error report directory
		Utility::RecycleFile(m_Reports[nReport].m_sErrorReportDirName + _T("\\") + it->second.m_sDestFile, TRUE);
		
		m_Reports[nReport].m_FileItems.erase(it);
    }

#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("w"));
#else
    _tfopen_s(&f, sFileName, _T("w"));
#endif

    if(f==NULL)
        return FALSE;

    bool bSave = doc.SaveFile(f); 
    if(!bSave)
        return FALSE;
    fclose(f);
    return TRUE;
}

BOOL CCrashInfoReader::GetLastRemindDate(SYSTEMTIME& LastDate)
{  
    CString sDate = Utility::GetINIString(m_sINIFile, _T("General"), _T("LastRemindDate"));
    if(sDate.IsEmpty())
        return FALSE;

    Utility::UTC2SystemTime(sDate, LastDate);
    return TRUE;
}

BOOL CCrashInfoReader::SetLastRemindDateToday()
{
    // Get current time
    CString sTime;
    Utility::GetSystemTimeUTC(sTime);

    // Write it to INI  
    Utility::SetINIString(m_sINIFile, _T("General"), _T("LastRemindDate"), sTime);

    return TRUE;
}

REMIND_POLICY CCrashInfoReader::GetRemindPolicy()
{  
    CString sPolicy = Utility::GetINIString(m_sINIFile, _T("General"), _T("RemindPolicy"));

    if(sPolicy.Compare(_T("RemindLater"))==0)
        return REMIND_LATER;
    else if(sPolicy.Compare(_T("NeverRemind"))==0)
        return NEVER_REMIND;

    Utility::SetINIString(m_sINIFile, _T("General"), _T("RemindPolicy"), _T("RemindLater"));
    return REMIND_LATER;
}

BOOL CCrashInfoReader::SetRemindPolicy(REMIND_POLICY Policy)
{
    CString sPolicy;
    if(Policy==REMIND_LATER)
        sPolicy = _T("RemindLater");
    else if(Policy==NEVER_REMIND)
        sPolicy = _T("NeverRemind");

    Utility::SetINIString(m_sINIFile, _T("General"), _T("RemindPolicy"), sPolicy);

    return TRUE;
}

BOOL CCrashInfoReader::IsRemindNowOK()
{
    if(GetRemindPolicy()!=REMIND_LATER)
        return FALSE; // User doesn want us to remind him

    // Get last remind date
    SYSTEMTIME LastRemind;
    if(!GetLastRemindDate(LastRemind))
    {   
		// We never reminded user - its time to remind now!
        return TRUE;
    }

    // Determine the period of time elapsed since the last remind.
    SYSTEMTIME CurTimeUTC, CurTimeLocal;
    GetSystemTime(&CurTimeUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &CurTimeUTC, &CurTimeLocal);
    ULONG64 uCurTime = Utility::SystemTimeToULONG64(CurTimeLocal);
    ULONG64 uLastRemindTime = Utility::SystemTimeToULONG64(LastRemind);

    // Check that at lease one week elapsed
    double dDiffTime = (double)(uCurTime-uLastRemindTime)*10E-08;
    if(dDiffTime < SEND_RECENT_REPORTS_TIMEOUT) //каждые два дня напоминаем
    {
		// Now, wait more time
        return FALSE;
    }

	// Remind now
    return TRUE;
}

LONG64 CCrashInfoReader::GetUncompressedReportSize(CErrorReportInfo& eri)
{
	// Calculate summary size of all files included into crash report

    LONG64 lTotalSize = 0;
    std::map<CString, ERIFileItem>::iterator it;
    HANDLE hFile = INVALID_HANDLE_VALUE;  
    CString sMsg;
    BOOL bGetSize = FALSE;
    LARGE_INTEGER lFileSize;

	// Walk through all files in the crash report
    for(it=eri.m_FileItems.begin(); it!=eri.m_FileItems.end(); it++)
    {   
		// Get file name
        CString sFileName = it->second.m_sSrcFile.GetBuffer(0);
		// Check file exists
        hFile = CreateFile(sFileName, 
            GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
        if(hFile==INVALID_HANDLE_VALUE)
            continue; // File does not exist

		// Get file size
        bGetSize = GetFileSizeEx(hFile, &lFileSize);
        if(!bGetSize)
        {
            CloseHandle(hFile);
            continue;
        }

        if ( lFileSize.QuadPart > CR_AF_MAX_FILE_SIZE )
          lFileSize.QuadPart = CR_AF_MAX_FILE_SIZE;

		// Add to the sum
        lTotalSize += lFileSize.QuadPart;

		// Clean up
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }

	// Return summary size
    return lTotalSize;
}

HICON CCrashInfoReader::GetCustomIcon()
{
	// This method extracts custom icon from the specified resource file.
	// If the custom icon not specified, NULL is returned.

    if(!m_sCustomSenderIcon.IsEmpty())
    {
		// First parse the path (the path is in form of <filename>[,<icon_index>])
        CString sResourceFile;
        CString sIconIndex;
        int nIconIndex = 0;

		// Get position of comma
        int nComma = m_sCustomSenderIcon.ReverseFind(',');    
        if(nComma>=0)
        {
			// Split resource file path and icon index
            sResourceFile = m_sCustomSenderIcon.Left(nComma);      
            sIconIndex = m_sCustomSenderIcon.Mid(nComma+1);
            sIconIndex.TrimLeft();
            sIconIndex.TrimRight();
            nIconIndex = _ttoi(sIconIndex);      
        }
        else
        {
			// There is no icon index, just resource file path
            sResourceFile = m_sCustomSenderIcon;
        }

        sResourceFile.TrimRight();        

        if(nIconIndex==-1)
        {      
            return NULL;
        }

        // Check that custom icon can be loaded
        HICON hIcon = ExtractIcon(NULL, sResourceFile, nIconIndex);
        if(hIcon==NULL || hIcon==(HICON)1)
        { 
			// Failure
            return NULL;
        }

		// Return icon handle
        return hIcon;
    }

	// Return NULL to indicate custom icon not specified
    return NULL;
}

// Returns last error message.
CString CCrashInfoReader::GetErrorMsg()
{
	return m_sErrorMsg;
}

CString CCrashInfoReader::GetPersistentUserEmail()
{
	// Read the E-mail last entered by user and stored in INI file.
	return Utility::GetINIString(m_sINIFile, _T("General"), _T("EmailFrom"));
}

void CCrashInfoReader::SetPersistentUserEmail(LPCTSTR szEmail)
{
	// Save user's E-mail to INI file for later reuse.
	Utility::SetINIString(m_sINIFile, _T("General"), _T("EmailFrom"), szEmail);
}