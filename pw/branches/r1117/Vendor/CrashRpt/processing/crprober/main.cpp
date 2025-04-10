/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: main.cpp
// Description: crprober application.
// Authors: zexspectrum
// Date: 2010

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <assert.h>
#include "CrashRptProbe.h"

// Character set independent string type
typedef std::basic_string<TCHAR> tstring;

// The following macros are used for parsing the command line
#define args_left() (argc-cur_arg)
#define arg_exists() (cur_arg<argc && argv[cur_arg]!=NULL)
#define get_arg() ( arg_exists() ? argv[cur_arg]:NULL )
#define skip_arg() cur_arg++
#define cmp_arg(val) (arg_exists() && (0==_tcscmp(argv[cur_arg], val)))

// Return codes
enum ReturnCode 
{
    SUCCESS     = 0, // OK
    UNEXPECTED  = 1,  // Unexpected error
    INVALIDARG  = 2, // Invalid argument
    INVALIDMD5  = 3, // Integrity check failed
    EXTRACTERR  = 4  // File extraction error   
};

// Function prototypes
int process_report(LPTSTR szInput, LPTSTR szInputMD5, LPTSTR szOutput, 
                   LPTSTR szSymSearchPath, LPTSTR szExtractPath, LPTSTR szTableId, LPTSTR szColumnId, LPTSTR szRowId);
int get_prop(CrpHandle hReport, LPCTSTR table_id, LPCTSTR column_id, tstring& str, int row_id=0);
int output_document(CrpHandle hReport, FILE* f);
int extract_files(CrpHandle hReport, LPCTSTR pszExtractPath);

// We want to use secure version of _stprintf function when possible
int __STPRINTF_S(TCHAR* buffer, size_t sizeOfBuffer, const TCHAR* format, ... )
{
    va_list args; 
    va_start(args, format);

#if _MSC_VER<1400
    UNREFERENCED_PARAMETER(sizeOfBuffer);
    return _vstprintf(buffer, format, args);
#else
    return _vstprintf_s(buffer, sizeOfBuffer, format, args);
#endif
}

// We want to use secure version of _tfopen when possible
#if _MSC_VER<1400
#define _TFOPEN_S(_File, _Filename, _Mode) _File = _tfopen(_Filename, _Mode);
#else
#define _TFOPEN_S(_File, _Filename, _Mode) _tfopen_s(&(_File), _Filename, _Mode);
#endif

// Prints usage
void print_usage()
{
    _tprintf(_T("Usage:\n"));
    _tprintf(_T("crprober /? Prints this usage help\n"));
    _tprintf(_T("crprober <arg> [arg ...]\n"));
    _tprintf(_T("  where the argument may be any of the following:\n"));
    _tprintf(_T("   /f <input_file>          Required. Absolute or relative path to input ZIP file name.\n"));
    _tprintf(_T("   /fmd5 <md5_file_or_dir>  Optional. Path to .md5 file containing MD5 hash for the <input_file> ")\
             _T("or directory name where to search for the .md5 file. If this parameter is omitted, the .md5 file is searched "\)
             _T("in the directory where <input_file> is located.\n"));
    _tprintf(_T("   /o <out_file_or_dir>     Optional. Output file name or directory name. Or use empty name \"\" ")\
             _T("to direct output to terminal. If this parameter is omitted, output is not generated.\n"));
    _tprintf(_T("   /sym <sym_search_dirs>   Optional. Symbol files search directory or list of directories ")\
             _T("separated with semicolon. If this parameter is omitted, symbol files are searched using the default search sequence.\n"));  
    _tprintf(_T("   /ext <extract_dir>       Optional. Specifies the directory where to extract all files contained in error report. ")\
             _T("If this parameter is omitted, files are not extracted.\n"));    
    _tprintf(_T("   /get <table_id> <column_id> <row_id> Optional. Specifies the table ID, column ID and row index of the property to retrieve. ")\
             _T("If this parameter specified, the property is written to the output file or to terminal, as defined by /o parameter.\n"));    
}

// COutputter
// This class is used for generating the content of the resulting file.
// Currently text format is supported.
class COutputter
{
public:

    void Init(FILE* f)
    {
        assert(f!=NULL);
        m_fOut = f;    
    }

    void BeginDocument(LPCTSTR pszTitle)
    {
        _ftprintf(m_fOut, _T("= %s = \n\n"), pszTitle);    
    }

    void EndDocument()
    {    
        _ftprintf(m_fOut, _T("\n== END ==\n"));
    }

    void BeginSection(LPCTSTR pszTitle)
    {
        _ftprintf(m_fOut, _T("== %s ==\n\n"), pszTitle);
    }

    void EndSection()
    {
        _ftprintf(m_fOut, _T("\n\n"));
    }

    void PutRecord(LPCTSTR pszName, LPCTSTR pszValue)
    {
        _ftprintf(m_fOut, _T("%s = %s\n"), pszName, pszValue);
    }

    void PutTableCell(LPCTSTR pszValue, int width, bool bLastInRow)
    {
        TCHAR szFormat[32];
        __STPRINTF_S(szFormat, 32, _T("%%-%ds%s"), width, bLastInRow?_T("\n"):_T(" "));
        _ftprintf(m_fOut, szFormat, pszValue);
    }

private:

    FILE* m_fOut;
};

#include <atldef.h>

// Program entry point
int _tmain(int argc, TCHAR** argv)
{
    int result = INVALIDARG; // Return code
    int cur_arg = 1; // Current cmdline argument being processed

    TCHAR* szInput = NULL; // Input file       
    TCHAR* szInputMD5 = NULL; // Input MD5 file or dir
    TCHAR* szOutput = NULL;   // Output file 
    TCHAR* szSymSearchPath = NULL; // Symbol search path   
    TCHAR* szExtractPath = NULL;   // File extraction path

    TCHAR* szTableId = NULL;
    TCHAR* szColumnId = NULL;
    TCHAR* szRowId = NULL;

    if(args_left()==0)
    {
        result = INVALIDARG;
        goto done; // There are no arguments.
    }

    // Parse command line arguments
    while(arg_exists())
    {
        if(cmp_arg(_T("/?"))) // help
        {
            // Print usage text
            result = SUCCESS;
			print_usage();
            goto done;
        }
        else if(cmp_arg(_T("/f"))) // input file name
        {
            skip_arg();    
            szInput = get_arg();
            skip_arg();    
            if(szInput==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Input file name is missing in /f parameter.\n"));        
                goto done;
            }
        }
        else if(cmp_arg(_T("/fmd5"))) // md5 file or directory
        {
            skip_arg();    
            szInputMD5 = get_arg();
            skip_arg();    
            if(szInputMD5==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Input MD5 file name is missing in /fmd5 parameter.\n"));
                goto done;
            }
        }
        else if(cmp_arg(_T("/o"))) // output file or directory or "" (terminal)
        {
            skip_arg();    
            szOutput = get_arg();
            skip_arg();          
            if(szOutput==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Missing output file name in /o parameter.\n"));
                goto done;
            }
        }    
        else if(cmp_arg(_T("/sym"))) // symbol search dirs
        {
            skip_arg();    
            szSymSearchPath = get_arg();
            skip_arg();
            if(szSymSearchPath==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Missing symbol search path in /sym parameter.\n"));
                goto done;
            }
        }
        else if(cmp_arg(_T("/ext"))) // extract dir
        {
            skip_arg();    
            szExtractPath = get_arg();
            if(szExtractPath==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Missing file extraction path in /ext parameter.\n"));
                goto done;
            }
            skip_arg();
        }
        else if(cmp_arg(_T("/get"))) // get property
        {
            skip_arg();    
            szTableId = get_arg();
            skip_arg();
            szColumnId = get_arg();
            skip_arg();
            szRowId = get_arg();
            skip_arg();

            if(szTableId==NULL || szColumnId==NULL || szRowId==NULL)
            {
                result = INVALIDARG;
                _tprintf(_T("Missing table ID or column ID or row ID in /get parameter.\n"));
                goto done;
            }      
        }
        else // unknown arg
        {
            _tprintf(_T("Unexpected parameter: %s\n"), get_arg());
            goto done;
        }    
    }

    // Do the processing work
    result = process_report(szInput, szInputMD5, szOutput, szSymSearchPath, 
        szExtractPath, szTableId, szColumnId, szRowId); 

done:

    if(result==INVALIDARG)
    {
        print_usage();
    }

    return result;
}


// Processes a crash report file.
int process_report(LPTSTR szInput, LPTSTR szInputMD5, LPTSTR szOutput, 
                   LPTSTR szSymSearchPath, LPTSTR szExtractPath, LPTSTR szTableId,
                   LPTSTR szColumnId, LPTSTR szRowId)
{
    int result = UNEXPECTED; // Status
    CrpHandle hReport = 0; // Handle to the error report
    tstring sInDirName;
    tstring sInFileName;
    tstring sOutDirName;
    tstring sMD5DirName;
    tstring sMD5FileName;    
    tstring sExtactDirName;  
    BOOL bInputMD5FromDir = FALSE; // Did user specified file name for .MD5 file or directory name for search?
    BOOL bOutputToDir = FALSE; // Do we save resulting files to directory or save single resulting file?  
    DWORD dwFileAttrs = 0;
    TCHAR szMD5Buffer[64]=_T("");
    TCHAR* szMD5Hash = NULL;
    FILE* f = NULL;      

    // Validate input parameters
    if(szInput==NULL)
    {
        result = INVALIDARG;
        _tprintf(_T("Input file name is missing.\n"));
        goto done;
    }

    if(szTableId==NULL && szOutput==NULL && szExtractPath==NULL)
    {
        result = INVALIDARG;
        _tprintf(_T("Output file name or directory name is missing.\n"));
        goto done;
    }

    // Decide input dir and file name
    sInDirName = szInput;
    size_t pos = sInDirName.rfind('\\');
    if(pos<0) // There is no back slash in path
    {
        sInDirName = _T(""); 
        sInFileName = szInput;
    }
    else
    {
        sInFileName = sInDirName.substr(pos+1);
        sInDirName = sInDirName.substr(0, pos);    
    }

    if(szExtractPath!=NULL)
    {
        // Determine if user has specified a valid dir name for file extraction
        dwFileAttrs = GetFileAttributes(szExtractPath);
        if(dwFileAttrs==INVALID_FILE_ATTRIBUTES ||
            !(dwFileAttrs&FILE_ATTRIBUTE_DIRECTORY))
        {
            result = INVALIDARG;
            _tprintf(_T("Invalid directory name for file extraction.\n"));
            goto done;
        }
    }  

    if(szInputMD5!=NULL)
    {
        // Determine if user wants us to search for .MD5 files in a directory
        // or if he specifies the .MD5 file name.  
        dwFileAttrs = GetFileAttributes(szInputMD5);
        if(dwFileAttrs!=INVALID_FILE_ATTRIBUTES && 
            (dwFileAttrs&FILE_ATTRIBUTE_DIRECTORY))
            bInputMD5FromDir = TRUE;  

        // Append the last back slash to the MD5 dir name if needed
        if(bInputMD5FromDir)
        {
            sMD5DirName = szInputMD5;
            size_t pos = sMD5DirName.rfind('\\');
            if(pos<0) // There is no back slash in path
                sMD5DirName = _T(""); 
            else if(pos!=sMD5DirName.length()-1) // Append the back slash to dir name
                sMD5DirName = sMD5DirName.substr(0, pos+1);
        }
    }
    else
    {
        // Assume .md5 files are in the same dir as input file
        sMD5DirName = sInDirName;
    }

    if(szOutput!=NULL && _tcscmp(szOutput, _T(""))!=0) // If empty, direct output to terminal
    {
        // Determine if user wants us to save resulting file in directory using its respective 
        // file name or if he specifies the file name for the saved file
        dwFileAttrs = GetFileAttributes(szOutput);
        if(dwFileAttrs!=INVALID_FILE_ATTRIBUTES && 
            (dwFileAttrs&FILE_ATTRIBUTE_DIRECTORY))
            bOutputToDir = TRUE;  
    }  

    //_tprintf(_T("Processing file: %s\n"), sInFileName.c_str());

    // Decide MD5 file name  
    if(szInputMD5==NULL)
    {
        // If /md5 cmdline argument is omitted, search for md5 files in the same dir
        sMD5FileName = szInput;
        sMD5FileName += _T(".md5");
    }
    else
    {
        if(bInputMD5FromDir)
        {  
            // Look for .md5 files in the special directory
            sMD5FileName = sMD5DirName+sInFileName;
            sMD5FileName += _T(".md5");        
        }
        else
        {
            // Look for MF5 hash in the specified file
            sMD5FileName = szInputMD5;
        }
    }

    // Get MD5 hash from .md5 file
    _TFOPEN_S(f, sMD5FileName.c_str(), _T("rt"));
    if(f!=NULL)
    {
        szMD5Hash = _fgetts(szMD5Buffer, 64, f);   
        fclose(f);
        if(szTableId==NULL)
            _tprintf(_T("Found MD5 file %s; MD5=%s\n"), sMD5FileName.c_str(), szMD5Hash);
    }    
    else if(szTableId==NULL)
    {
        _tprintf(_T("Warning: 'MD5 file not detected; integrity check not performed.' while processing file '%s'\n"), sInFileName.c_str());
    }

    // Open the error report file  
    int res = crpOpenErrorReport(szInput, szMD5Hash, szSymSearchPath, 0, &hReport);
    if(res!=0)
    {
        result = UNEXPECTED;
        TCHAR buff[1024];
        crpGetLastErrorMsg(buff, 1024);
        _tprintf(_T("Error '%s' while processing file '%s'\n"), buff, sInFileName.c_str());      
        goto done;
    }
    else 
    {
        // Output results
        tstring sOutFileName;
        if(szOutput!=NULL && _tcscmp(szOutput, _T(""))!=0)
        {        
            if(bOutputToDir)
            {
                // Write output to directory
                sOutFileName = tstring(szOutput);
                if( sOutFileName[sOutFileName.length()-1]!='\\' )
                    sOutFileName += _T("\\"); 
                sOutFileName += sInFileName + _T(".txt");
            }
            else
            {
                // Write output to single file
                sOutFileName = szOutput;
            }              

            // Open resulting file
            _TFOPEN_S(f, sOutFileName.c_str(), _T("wt"));
            if(f==NULL)
            {
                result = UNEXPECTED;
                _tprintf(_T("Error: couldn't open output file '%s'.\n"), 
                    sOutFileName.c_str());      
                goto done;
            }
        }
        else if(szOutput!=NULL && _tcscmp(szOutput, _T(""))==0)
        {
            f=stdout; // Write output to terminal
        }

        if(szExtractPath!=NULL && szOutput!=NULL && f==NULL)
        {
            result = UNEXPECTED;
            _tprintf(_T("Error: couldn't open output file.\n")); 
            goto done;
        }

        if(szTableId!=NULL)
        {
            // Get single property
            tstring sProp;
            int get = get_prop(hReport, szTableId, szColumnId, sProp, _ttoi(szRowId));
            if(_tcscmp(szColumnId, CRP_META_ROW_COUNT)==0)
            {
                if(get<0)
                {
                    result = UNEXPECTED;
                    TCHAR szErr[1024];
                    crpGetLastErrorMsg(szErr, 1024);        
                    _tprintf(_T("%s\n"), szErr);
                    goto done;
                }
                else
                {
                    // Print row count in the specified table
                    _ftprintf(f, _T("%d\n"), get);
                }
            }
            else if(get!=0)
            {
                result = UNEXPECTED;
                TCHAR szErr[1024];
                crpGetLastErrorMsg(szErr, 1024);        
                _tprintf(_T("%s\n"), szErr);
                goto done;
            }
            else
            {
                _ftprintf(f, _T("%s\n"), sProp.c_str());
            }
        }
        else if(szOutput!=NULL)
        {      
            // Write error report properties to the resulting file
            result = output_document(hReport, f);
            if(result!=0)
                goto done;      
        }

        if(szExtractPath!=NULL)
        {
            // Extract files from error report
            result = extract_files(hReport, szExtractPath);
            if(result!=0)
                goto done;
        }
    }

    // Success.
    result = SUCCESS;

done:

    if(f!=NULL && f!=stdout)
        fclose(f);

    if(hReport!=0)
        crpCloseErrorReport(hReport);

    return result;
}

// Helper function thatr etrieves an error report property
int get_prop(CrpHandle hReport, LPCTSTR table_id, LPCTSTR column_id, tstring& str, int row_id)
{
    const int BUFF_SIZE = 1024;
    TCHAR buffer[BUFF_SIZE];  
    int result = crpGetProperty(hReport, table_id, column_id, row_id, buffer, BUFF_SIZE, NULL);
    if(result==0)
        str = buffer;
    return result;
}

int get_table_row_count(CrpHandle hReport, LPCTSTR table_id)
{
    return crpGetProperty(hReport, table_id, CRP_META_ROW_COUNT, 0, NULL, 0, NULL);
}

// Writes all error report properties to the file
int output_document(CrpHandle hReport, FILE* f)
{  
    int result = UNEXPECTED;
    COutputter doc;

    doc.Init(f);
    doc.BeginDocument(_T("Error Report"));

    doc.BeginSection(_T("Summary"));

    // Print CrashRpt version
    tstring sCrashRptVer;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_CRASHRPT_VERSION, sCrashRptVer);
    if(result==0)
        doc.PutRecord(_T("Generator version"), sCrashRptVer.c_str());

    // Print CrashGUID  
    tstring sCrashGUID;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_CRASH_GUID, sCrashGUID);
    if(result==0)
        doc.PutRecord(_T("Crash GUID"), sCrashGUID.c_str());

    // Print AppName
    tstring sAppName;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_APP_NAME, sAppName);
    if(result==0)
        doc.PutRecord(_T("Application name"), sAppName.c_str());

    // Print ImageName
    tstring sImageName;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_IMAGE_NAME, sImageName);
    if(result==0)
        doc.PutRecord(_T("Executable image"), sImageName.c_str());

    // Print AppVersion
    tstring sAppVersion;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_APP_VERSION, sAppVersion);
    if(result==0)
        doc.PutRecord(_T("Application version"), sAppVersion.c_str());

    // Print SystemTimeUTC
    tstring sSystemTimeUTC;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_SYSTEM_TIME_UTC, sSystemTimeUTC);
    if(result==0)
        doc.PutRecord(_T("Date created (UTC)"), sSystemTimeUTC.c_str());

    // Print OperatingSystem
    tstring sOperatingSystem;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_OPERATING_SYSTEM, sOperatingSystem);
    if(result==0)
        doc.PutRecord(_T("OS name (from user's registry)"), sOperatingSystem.c_str());

    tstring sOsVerMajor;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_OS_VER_MAJOR, sOsVerMajor);
    tstring sOsVerMinor;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_OS_VER_MINOR, sOsVerMinor);
    tstring sOsVerBuild;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_OS_VER_BUILD, sOsVerBuild);
    tstring sOsVerCSD;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_OS_VER_CSD, sOsVerCSD);

    tstring sOsVer;
    sOsVer += sOsVerMajor;
    sOsVer += _T(".");
    sOsVer += sOsVerMinor;
    sOsVer += _T(".");
    sOsVer += sOsVerBuild;
    sOsVer += _T(" ");
    sOsVer += sOsVerCSD; 

    doc.PutRecord(_T("OS version (from minidump)"), sOsVer.c_str());

    // Print OSIs64Bit
    tstring sOSIs64Bit;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_OS_IS_64BIT, sOSIs64Bit);
    if(result==0)
        doc.PutRecord(_T("OS is 64-bit"), sOSIs64Bit.c_str());

    // Print GeoLocation
    tstring sGeoLocation;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_GEO_LOCATION, sGeoLocation);
    if(result==0)
        doc.PutRecord(_T("Geographic location"), sGeoLocation.c_str());

    // Print SystemType
    tstring sSystemType;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_PRODUCT_TYPE, sSystemType);
    if(result==0)
        doc.PutRecord(_T("Product type"), sSystemType.c_str());

    // Print ProcessorArchitecture
    tstring sProcessorArchitecture;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_CPU_ARCHITECTURE, sProcessorArchitecture);
    if(result==0)
        doc.PutRecord(_T("CPU architecture"), sProcessorArchitecture.c_str());

    // Print NumberOfProcessors
    tstring sCPUCount;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_CPU_COUNT, sCPUCount);
    if(result==0)
        doc.PutRecord(_T("CPU count"), sCPUCount.c_str());

    // Print GUIResourceCount
    tstring sGUIResourceCount;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_GUI_RESOURCE_COUNT, sGUIResourceCount);
    if(result==0)
        doc.PutRecord(_T("GUI resource count"), sGUIResourceCount.c_str());

    // Print OpenHandleCount
    tstring sOpenHandleCount;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_OPEN_HANDLE_COUNT, sOpenHandleCount);
    if(result==0)
        doc.PutRecord(_T("Open handle count"), sOpenHandleCount.c_str());

    // Print MemoryUsageKbytes
    tstring sMemoryUsageKbytes;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_MEMORY_USAGE_KBYTES, sMemoryUsageKbytes);
    if(result==0)
        doc.PutRecord(_T("Memory usage (Kbytes)"), sMemoryUsageKbytes.c_str());

    int nExceptionType = 0;
    tstring sExceptionType;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_EXCEPTION_TYPE, sExceptionType);
    if(result==0)
    {
        nExceptionType = _ttoi(sExceptionType.c_str());
        doc.PutRecord(_T("Exception type"), sExceptionType.c_str());
    }

    tstring sExceptionAddress;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_EXCEPTION_ADDRESS, sExceptionAddress);
    if(result==0)
        doc.PutRecord(_T("Exception address"), sExceptionAddress.c_str());

    tstring sExceptionCode;
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_EXCPTRS_EXCEPTION_CODE, sExceptionCode);
    if(result==0)
        doc.PutRecord(_T("SEH exception code (from minidump)"), sExceptionCode.c_str());

    tstring sExceptionThreadRowID;  
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_EXCEPTION_THREAD_ROWID, sExceptionThreadRowID);
    int uExceptionThreadRowID = _ttoi(sExceptionThreadRowID.c_str());
    if(result==0)
    {
        tstring sExceptionThreadId;
        result = get_prop(hReport, CRP_TBL_MDMP_THREADS, CRP_COL_THREAD_ID, sExceptionThreadId, uExceptionThreadRowID);
        if(result==0)
            doc.PutRecord(_T("Exception thread ID"), sExceptionThreadId.c_str());
    }

    tstring sExceptionModuleRowID;  
    result = get_prop(hReport, CRP_TBL_MDMP_MISC, CRP_COL_EXCEPTION_MODULE_ROWID, sExceptionModuleRowID);
    int uExceptionModuleRowID = _ttoi(sExceptionModuleRowID.c_str());
    if(result==0)
    {
        tstring sExceptionModuleName;
        result = get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_NAME, sExceptionModuleName, uExceptionModuleRowID);
        if(result==0)
            doc.PutRecord(_T("Exception module name"), sExceptionModuleName.c_str());
    }

    // Print UserEmail
    tstring sUserEmail;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_USER_EMAIL, sUserEmail);
    if(result==0)
        doc.PutRecord(_T("User email"), sUserEmail.c_str());

    // Print ProblemDescription
    tstring sProblemDescription;
    result = get_prop(hReport, CRP_TBL_XMLDESC_MISC, CRP_COL_PROBLEM_DESCRIPTION, sProblemDescription);
    if(result==0)
        doc.PutRecord(_T("Problem description"), sProblemDescription.c_str());

    doc.EndSection();

    doc.BeginSection(_T("Application-defined properties"));

    int nPropCount = get_table_row_count(hReport, CRP_TBL_XMLDESC_CUSTOM_PROPS);
    if(nPropCount>0)
    {
        // Print custom property list  
        doc.PutTableCell(_T("#"), 2, false);
        doc.PutTableCell(_T("Name"), 16, false);
        doc.PutTableCell(_T("Value"), 32, true);

        int i;
        for(i=0; i<nPropCount; i++)
        { 
            TCHAR szBuffer[10];
            __STPRINTF_S(szBuffer, 10, _T("%d"), i+1);
            doc.PutTableCell(szBuffer, 2, false);
            tstring sPropName;
            get_prop(hReport, CRP_TBL_XMLDESC_CUSTOM_PROPS, CRP_COL_PROPERTY_NAME, sPropName, i);
            doc.PutTableCell(sPropName.c_str(), 16, false);
            tstring sPropValue;
            get_prop(hReport, CRP_TBL_XMLDESC_CUSTOM_PROPS, CRP_COL_PROPERTY_VALUE, sPropValue, i);
            doc.PutTableCell(sPropValue.c_str(), 32, true);      
        }  

        doc.EndSection();
    }

    doc.BeginSection(_T("File list"));

    // Print file list  
    doc.PutTableCell(_T("#"), 2, false);
    doc.PutTableCell(_T("Name"), 16, false);
    doc.PutTableCell(_T("Description"), 32, true);

    int nItemCount = get_table_row_count(hReport, CRP_TBL_XMLDESC_FILE_ITEMS);
    int i;
    for(i=0; i<nItemCount; i++)
    { 
        TCHAR szBuffer[10];
        __STPRINTF_S(szBuffer, 10, _T("%d"), i+1);
        doc.PutTableCell(szBuffer, 2, false);
        tstring sFileName;
        get_prop(hReport, CRP_TBL_XMLDESC_FILE_ITEMS, CRP_COL_FILE_ITEM_NAME, sFileName, i);
        doc.PutTableCell(sFileName.c_str(), 16, false);
        tstring sDesc;
        get_prop(hReport, CRP_TBL_XMLDESC_FILE_ITEMS, CRP_COL_FILE_ITEM_DESCRIPTION, sDesc, i);
        doc.PutTableCell(sDesc.c_str(), 32, true);      
    }  

    doc.EndSection();

    int nThreadCount = get_table_row_count(hReport, CRP_TBL_MDMP_THREADS);
    for(i=0; i<nThreadCount; i++)
    { 
        tstring sThreadId;
        result = get_prop(hReport, CRP_TBL_MDMP_THREADS, CRP_COL_THREAD_ID, sThreadId, i);
        if(result==0)
        {
            tstring str = _T("Stack trace for thread ");
            str += sThreadId;
            doc.BeginSection(str.c_str());

            doc.PutTableCell(_T("Frame"), 32, true);

            tstring sStackTableId;
            get_prop(hReport, CRP_TBL_MDMP_THREADS, CRP_COL_THREAD_STACK_TABLEID, sStackTableId, i);

            BOOL bMissingFrames=FALSE;
            int nFrameCount = get_table_row_count(hReport, sStackTableId.c_str());
            int j;
            for(j=0; j<nFrameCount; j++)
            {        
                tstring sModuleName;
                tstring sAddrPCOffset;
                tstring sSymbolName;            
                tstring sOffsInSymbol;
                tstring sSourceFile;
                tstring sSourceLine;

                tstring sModuleRowId;
                result = get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_MODULE_ROWID, sModuleRowId, j);
                if(result==0)
                {
                    int nModuleRowId = _ttoi(sModuleRowId.c_str());              
                    if(nModuleRowId==-1)
                    {            
                        if(!bMissingFrames)
                            doc.PutTableCell(_T("[Frames below may be incorrect and/or missing]"), 32, true);                                
                        bMissingFrames = TRUE;
                    }
                    get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_NAME, sModuleName, nModuleRowId);              
                }      

                get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_ADDR_PC_OFFSET, sAddrPCOffset, j);        
                get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_SYMBOL_NAME, sSymbolName, j);        
                get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_OFFSET_IN_SYMBOL, sOffsInSymbol, j);              
                get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_SOURCE_FILE, sSourceFile, j);              
                get_prop(hReport, sStackTableId.c_str(), CRP_COL_STACK_SOURCE_LINE, sSourceLine, j);              

                tstring str;
                str = sModuleName;
                if(!str.empty())
                    str += _T("!");

                if(sSymbolName.empty())
                    str += sAddrPCOffset;  
                else
                {
                    str += sSymbolName;
                    str += _T("+");
                    str += sOffsInSymbol;
                }

                if(!sSourceFile.empty())
                {
                    size_t pos = sSourceFile.rfind('\\');
                    if(pos>=0)
                        sSourceFile = sSourceFile.substr(pos+1);
                    str += _T(" [ ");
                    str += sSourceFile;
                    str += _T(": ");
                    str += sSourceLine;
                    str += _T(" ] ");
                } 

                doc.PutTableCell(str.c_str(), 32, true);                    
            }       

            doc.EndSection();
        }
    }

    // Print module list
    doc.BeginSection(_T("Module List"));

    doc.PutTableCell(_T("#"), 2, false);
    doc.PutTableCell(_T("Name"), 32, false);
    doc.PutTableCell(_T("SymLoadStatus"), 32, false);
    doc.PutTableCell(_T("LoadedPDBName"), 48, false);
    doc.PutTableCell(_T("LoadedImageName"), 48, true);

    // Get module count
    nItemCount = get_table_row_count(hReport, CRP_TBL_MDMP_MODULES);
    for(i=0; i<nItemCount; i++)
    {
        TCHAR szBuffer[10];
        __STPRINTF_S(szBuffer, 10, _T("%d"), i+1);
        doc.PutTableCell(szBuffer, 2, false);

        tstring sModuleName;
        result = get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_NAME, sModuleName, i);  
        doc.PutTableCell(sModuleName.c_str(), 32, false);      

        tstring sSymLoadStatus;
        result = get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_SYM_LOAD_STATUS, sSymLoadStatus, i);  
        doc.PutTableCell(sSymLoadStatus.c_str(), 32, false);      

        tstring sLoadedPDBName;
        result = get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_LOADED_PDB_NAME, sLoadedPDBName, i);  
        doc.PutTableCell(sLoadedPDBName.c_str(), 48, false);      

        tstring sLoadedImageName;
        result = get_prop(hReport, CRP_TBL_MDMP_MODULES, CRP_COL_MODULE_LOADED_IMAGE_NAME, sLoadedImageName, i);  
        doc.PutTableCell(sLoadedImageName.c_str(), 48, true);      
    }  
    doc.EndSection();

    doc.BeginSection(_T("Minidump Load Log"));
    nItemCount = get_table_row_count(hReport, CRP_TBL_MDMP_LOAD_LOG);
    for(i=0; i<nItemCount; i++)
    {
        TCHAR szBuffer[10];
        __STPRINTF_S(szBuffer, 10, _T("%d"), i+1);
        doc.PutTableCell(szBuffer, 2, false);

        tstring sEntry;
        result = get_prop(hReport, CRP_TBL_MDMP_LOAD_LOG, CRP_COL_LOAD_LOG_ENTRY, sEntry, i);  
        doc.PutTableCell(sEntry.c_str(), 64, true);          
    }
    doc.EndSection();

    doc.EndDocument();

    return SUCCESS;
}

int extract_files(CrpHandle hReport, LPCTSTR pszExtractPath)
{
    tstring sExtractPath = pszExtractPath;
    if(sExtractPath.at(sExtractPath.length()-1)!='\\')
        sExtractPath += _T("\\"); // Add the last slash if needed

    // Get count of files to extract.
    int nFileCount = get_table_row_count(hReport, CRP_TBL_XMLDESC_FILE_ITEMS);
    if(nFileCount<0)
    {
        return UNEXPECTED; // Error getting file count.
    }

    int i;
    for(i=0; i<nFileCount; i++)
    {
        tstring sFileName;
        int nResult = get_prop(hReport, CRP_TBL_XMLDESC_FILE_ITEMS, CRP_COL_FILE_ITEM_NAME, sFileName, i);
        if(nResult!=0)
        {
            return UNEXPECTED; // Error getting file name
        }

        tstring sFileSaveAs = sExtractPath+sFileName;    
        nResult = crpExtractFile(hReport, sFileName.c_str(), sFileSaveAs.c_str(), TRUE);
        if(nResult!=0)
        {
            return EXTRACTERR; // Error extracting file
        }
    }

    // Success.
    return SUCCESS;
}

