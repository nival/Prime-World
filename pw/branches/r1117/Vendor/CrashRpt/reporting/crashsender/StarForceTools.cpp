#include "stdafx.h"
#include "StarForceTools.h"

#include "CrashHandler.h"
#include "Utility.h"
#include "SharedMem.h"
#include <iosfwd>

using namespace Utility;

namespace cr_starforce
{
  CSharedMem* m_pTmpSharedMem;
  CRASH_DESCRIPTION* m_pTmpCrashDesc;
  CString sCrashGUID;
  CString sfReportFilename;
  CString sPrivacyPolicyURL;
  CString sPathToExe;
  CString sCrashServerUrl;
  CSharedMem tmpSharedMem;    

  std::vector<CString> sfReportLines;
  void ParseReport( const CString& sfReportFilename )
  {
    TCHAR szBuffer[8192]= _T("");
    TCHAR* szLine = NULL;
    FILE* f = NULL;
    _wfopen_s(&f, sfReportFilename, _T("r, ccs=UNICODE"));

    while ( !feof(f) )
    {
      szLine = fgetws(szBuffer, 255, f);
      if (szBuffer == NULL)
        break;

      sfReportLines.push_back( CString(szLine) );
    }

    fclose(f);
  }

  CString GetValueInReport( const CString& sTag )
  {
    CString res;
    std::vector<CString>::iterator line = sfReportLines.begin();
    for ( ; line != sfReportLines.end(); ++line )
    {
      const CString& sLine = *line;
      int idx = sLine.Find( sTag );
      if ( idx >= 0 )
      {
        res = sLine.Mid( idx + sTag.GetLength() + 1 );
        res.TrimRight( _T("\n\t ") );
        break;
      }
    }
    

    return res;
  }



  // Packs a string to shared memory
  DWORD PackString(CString str)
  {
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    int nStrLen = str.GetLength()*sizeof(TCHAR);
    WORD wLength = (WORD)(sizeof(STRING_DESC)+nStrLen);

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);  
    STRING_DESC* pStrDesc = (STRING_DESC*)pView;
    memcpy(pStrDesc->m_uchMagic, "STR", 3);
    pStrDesc->m_wSize = wLength;
    memcpy(pView+sizeof(STRING_DESC), str.GetBuffer(0), nStrLen); 

    m_pTmpCrashDesc->m_dwTotalSize += wLength;

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
  }

  // Packs file item to shared memory
  DWORD PackFileItem(FileItem& fi)
  {
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(FILE_ITEM);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uFileItems++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    FILE_ITEM* pFileItem = (FILE_ITEM*)pView;

    memcpy(pFileItem->m_uchMagic, "FIL", 3);  
    pFileItem->m_dwSrcFilePathOffs = PackString(fi.m_sSrcFilePath);
    pFileItem->m_dwDstFileNameOffs = PackString(fi.m_sDstFileName);
    pFileItem->m_dwDescriptionOffs = PackString(fi.m_sDescription);
    pFileItem->m_bMakeCopy = fi.m_bMakeCopy;
    pFileItem->m_bAllowDelete = fi.m_bAllowDelete;
    pFileItem->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
  }

  // Packs custom property to shared memory
  DWORD PackProperty(CString sName, CString sValue)
  {
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(CUSTOM_PROP);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uCustomProps++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    CUSTOM_PROP* pProp = (CUSTOM_PROP*)pView;

    memcpy(pProp->m_uchMagic, "CPR", 3); 
    pProp->m_dwNameOffs = PackString(sName);
    pProp->m_dwValueOffs = PackString(sValue);
    pProp->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
  }

  // Packs registry key to shared memory
  DWORD PackRegKey(CString sKeyName, RegKeyInfo& rki)
  {
    DWORD dwTotalSize = m_pTmpCrashDesc->m_dwTotalSize;
    WORD wLength = sizeof(REG_KEY);
    m_pTmpCrashDesc->m_dwTotalSize += wLength;
    m_pTmpCrashDesc->m_uRegKeyEntries++;

    LPBYTE pView = m_pTmpSharedMem->CreateView(dwTotalSize, wLength);    
    REG_KEY* pKey = (REG_KEY*)pView;

    memcpy(pKey->m_uchMagic, "REG", 3); 
    pKey->m_bAllowDelete = rki.m_bAllowDelete;
    pKey->m_dwRegKeyNameOffs = PackString(sKeyName);
    pKey->m_dwDstFileNameOffs = PackString(rki.m_sDstFileName);
    pKey->m_wSize = (WORD)(m_pTmpCrashDesc->m_dwTotalSize-dwTotalSize);

    m_pTmpSharedMem->DestroyView(pView);
    return dwTotalSize;
  }

  // Packs config info to shared mem.
  CRASH_DESCRIPTION* PackCrashInfoIntoSharedMem(CSharedMem* pSharedMem, BOOL bTempMem)
  {
    m_pTmpSharedMem = pSharedMem;

    CString sSharedMemName;
    if(bTempMem)
      sSharedMemName.Format(_T("%s-tmp"), sCrashGUID);    
    else 
      sSharedMemName = sCrashGUID;

    if(!pSharedMem->IsInitialized())
    {
      // Initialize shared memory.
      BOOL bSharedMem = pSharedMem->Init(sSharedMemName, FALSE, SHARED_MEM_MAX_SIZE);
      if(!bSharedMem)
      {
        ATLASSERT(0);
        ATLTRACE(_T("Couldn't initialize shared memory."));
        return NULL; 
      }
    }

    // Create memory view.
    m_pTmpCrashDesc = 
      (CRASH_DESCRIPTION*)pSharedMem->CreateView(0, sizeof(CRASH_DESCRIPTION));  
    if(m_pTmpCrashDesc==NULL)
    {
      ATLASSERT(0);
      ATLTRACE(_T("Couldn't create shared memory view."));
      return NULL; 
    }


    DWORD dwFlags = 0;
    dwFlags |= CR_INST_ENABLE_LOGGING;
    dwFlags |= CR_INST_HTTP_BINARY_ENCODING;
    dwFlags |= CR_INST_NO_MINIDUMP;

    // Add LangFileName tag
    CString sLangFileName = sPathToExe + ("\\crashrpt_lang.ini");

/*
    // Write operating system friendly name  
    fprintf(pfCrashRptXml, "  <OperatingSystem>%s</OperatingSystem>\n", 
      XmlEncodeStr( GetValueInReport("OS Name") ).c_str());

    fprintf( pfCrashRptXml, "  <CrashedModule>Starforce</CrashedModule>\n" );

    // Write OSIs64Bit tag
    BOOL bOSIs64Bit = GetValueInReport("System Type").Find( _T("64") ) >=0 ? 1 : 0;
    fprintf(pfCrashRptXml, "  <OSIs64Bit>%d</OSIs64Bit>\n", bOSIs64Bit);  

    fprintf(pfCrashRptXml, "  <CPUInfo>%s</CPUInfo>\n", 
      XmlEncodeStr( GetValueInReport("Processor") ).c_str());

    int memTotal = atof(XmlEncodeStr(GetValueInReport("Total Physical Memory")).c_str())*1024*1024;
    fprintf(pfCrashRptXml, "  <TotalPhysicalMemoryKbytes>%d</TotalPhysicalMemoryKbytes>\n", memTotal);  

    int memUsage = memTotal - atof(XmlEncodeStr(GetValueInReport("Available Physical Memory")).c_str())*1024*1024;
    fprintf(pfCrashRptXml, "  <MemoryUsageKbytes>%d</MemoryUsageKbytes>\n", memUsage);  
*/
    //if(lpcszErrorReportSaveDir==NULL)
    
    CString sProductName = GetValueInReport("ProductName =");
    CString sAppVersion = GetValueInReport("BuildInfo =");
    
    CString m_sUnsentCrashReportsFolder;
    // Create %LOCAL_APPDATA%\CrashRpt\UnsentCrashReports\AppName_AppVer folder.
    CString sLocalAppDataFolder;
    DWORD dwCSIDL = CSIDL_LOCAL_APPDATA;
    Utility::GetSpecialFolder(dwCSIDL, sLocalAppDataFolder);
    m_sUnsentCrashReportsFolder.Format(_T("%s\\CrashRpt\\UnsentCrashReports\\%s_%s"), sLocalAppDataFolder, sProductName, sAppVersion);
    
    // Write list of custom user-added properties

    UINT uPriorities[5];
    uPriorities[CR_SMTP] = CR_NEGATIVE_PRIORITY;
    uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;
    uPriorities[CR_HTTP] = 1;

    // Pack config information to shared memory
    memset(m_pTmpCrashDesc, 0, sizeof(CRASH_DESCRIPTION));
    memcpy(m_pTmpCrashDesc->m_uchMagic, "CRD", 3);  
    m_pTmpCrashDesc->m_wSize = sizeof(CRASH_DESCRIPTION);
    m_pTmpCrashDesc->m_dwTotalSize = sizeof(CRASH_DESCRIPTION);  
    m_pTmpCrashDesc->m_dwCrashRptVer = CRASHRPT_VER;
    m_pTmpCrashDesc->m_dwInstallFlags = dwFlags;
    m_pTmpCrashDesc->m_MinidumpType = MiniDumpNormal;
    m_pTmpCrashDesc->m_nSmtpPort = 0;
    m_pTmpCrashDesc->m_nSmtpProxyPort = 0;
    m_pTmpCrashDesc->m_bAddScreenshot = false;
    m_pTmpCrashDesc->m_dwScreenshotFlags = 0;      
    memcpy(m_pTmpCrashDesc->m_uPriorities, uPriorities, sizeof(UINT)*3);
    m_pTmpCrashDesc->m_bAddVideo = false;
    m_pTmpCrashDesc->m_hWndVideoParent = 0;
    m_pTmpCrashDesc->m_dwProcessId = GetCurrentProcessId();
    m_pTmpCrashDesc->m_bClientAppCrashed = FALSE;

    m_pTmpCrashDesc->m_dwAppNameOffs = PackString(sProductName);
    m_pTmpCrashDesc->m_dwAppVersionOffs = PackString(sAppVersion);
    m_pTmpCrashDesc->m_dwCrashGUIDOffs = PackString(sCrashGUID);
    m_pTmpCrashDesc->m_dwImageNameOffs = PackString(sPathToExe);
    m_pTmpCrashDesc->m_dwLangFileNameOffs = PackString(sLangFileName);
    //m_pTmpCrashDesc->m_dwPathToDebugHelpDllOffs = PackString(m_sPathToDebugHelpDll);
    //m_pTmpCrashDesc->m_dwRestartCmdLineOffs = PackString(m_sRestartCmdLine);
    m_pTmpCrashDesc->m_dwPrivacyPolicyURLOffs = PackString(sPrivacyPolicyURL);
    m_pTmpCrashDesc->m_dwUnsentCrashReportsFolderOffs = PackString(m_sUnsentCrashReportsFolder);  
    //m_pTmpCrashDesc->m_dwCustomSenderIconOffs = PackString(m_sCustomSenderIcon);
    m_pTmpCrashDesc->m_dwUrlOffs = PackString(sCrashServerUrl);    
    /*m_pTmpCrashDesc->m_dwEmailToOffs = PackString("");
    m_pTmpCrashDesc->m_dwEmailSubjectOffs = PackString("");
    m_pTmpCrashDesc->m_dwEmailTextOffs = PackString("");  
    m_pTmpCrashDesc->m_dwSmtpProxyServerOffs = PackString("");    
    m_pTmpCrashDesc->m_dwSmtpLoginOffs = PackString("");    
    m_pTmpCrashDesc->m_dwSmtpPasswordOffs = PackString("");    
*/

    // Pack file items
    CString sDestFileName = Utility::GetFileName(sfReportFilename);//sfReportFilename.Mid(sfReportFilename.ReverseFind('\\'));
    FileItem fi;
    fi.m_bMakeCopy = TRUE;
    fi.m_sDstFileName = sDestFileName; 
    fi.m_sSrcFilePath = sfReportFilename; 
    fi.m_sDescription = "Starforce Crash Report"; 

    PackFileItem(fi);

    /*fprintf(pfInternalXml, "    <FileItem destfile=\"%s\" srcfile=\"%s\" description=\"%s\" makecopy=\"%d\" />\n",
      XmlEncodeStr(Utility::GetFileName(sRptDescFile)).c_str(), 
      XmlEncodeStr(sRptDescFile).c_str(), 
      XmlEncodeStr(CString("Crash Log")).c_str(), 
      false
      );*/

   		
    // Pack this prop into shared mem.
    CString sCompName = GetValueInReport("System Name:");
    if (sCompName.IsEmpty())
      sCompName = GetValueInReport(_T("Имя системы:"));

    CString sVideoAdapterInfo = GetValueInReport("Adapter Description:");


    PackProperty("ComputerName", sCompName);
    if (!sVideoAdapterInfo.IsEmpty())
      PackProperty("DisplayDescription", sVideoAdapterInfo);
    PackProperty("IsStarforceCrash", "True");
    
/*    // Pack reg keys
    std::map<CString, RegKeyInfo>::iterator rit;
    for(rit=m_RegKeys.begin(); rit!=m_RegKeys.end(); rit++)
    {		
      RegKeyInfo& rki = rit->second;

      // Pack this reg key into shared mem.
      PackRegKey(rit->first, rki);
    }
*/
    return m_pTmpCrashDesc;
  }



  CString CreateReports( const CString& _sfReportFilename, const CString& _sUrl, const CString& _sPrivacyPolicyURL )
  {
    sfReportFilename = _sfReportFilename;

    sCrashServerUrl = _sUrl;
    sPrivacyPolicyURL = _sPrivacyPolicyURL;

    ParseReport(sfReportFilename);

    sPathToExe = GetModulePath( NULL );
    
    Utility::GenerateGUID(sCrashGUID);

    // Create temporary shared mem.
    
    CRASH_DESCRIPTION* pCrashDesc = PackCrashInfoIntoSharedMem(&tmpSharedMem, TRUE);
    if (!pCrashDesc)
      return "";

    return tmpSharedMem.GetName();

  }

}