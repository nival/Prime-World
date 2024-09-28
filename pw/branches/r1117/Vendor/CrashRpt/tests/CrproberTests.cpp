/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "Tests.h"
#include "CrashRpt.h"
#include "Utility.h"
#include "strconv.h"
#include "Shellapi.h"
#include "TestUtils.h"

class CrproberTests : public CTestSuite
{
    BEGIN_TEST_MAP(CrproberTests, "crprober.exe tests")
        REGISTER_TEST(Test_help)
		REGISTER_TEST(Test_output)
        REGISTER_TEST(Test_extract_file)
		REGISTER_TEST(Test_get)
    END_TEST_MAP()

public:

    void SetUp();
    void TearDown();

	void Test_help();
    void Test_output();
    void Test_extract_file();
	void Test_get();

    CString m_sTmpFolder;
    CString m_sErrorReportName;
    CString m_sMD5Hash;
};

REGISTER_TEST_SUITE( CrproberTests );

void CrproberTests::SetUp()
{
    CString sAppDataFolder;  

    // Create a temporary folder  
    Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
    m_sTmpFolder = sAppDataFolder+_T("\\CrashRpt 应用程序名称");
    BOOL bCreate = Utility::CreateFolder(m_sTmpFolder);
    TEST_ASSERT(bCreate);

    // Create error report ZIP
    BOOL bCreateReport = TestUtils::CreateErrorReport(m_sTmpFolder, m_sErrorReportName, m_sMD5Hash);
    TEST_ASSERT(bCreateReport);

    __TEST_CLEANUP__;


}

void CrproberTests::TearDown()
{
    // Delete tmp folder
    Utility::RecycleFile(m_sTmpFolder, TRUE);
}

void CrproberTests::Test_help()
{
	// This test runs 'crprober.exe /?' (help)
	// and checks the return code.

	int nRetCode=-1;
	CString sExeName;
	CString sParams;

#ifdef _DEBUG
    sExeName = Utility::GetModulePath(NULL)+_T("\\crproberd.exe");
#else
    sExeName = Utility::GetModulePath(NULL)+_T("\\crprober.exe");
#endif

	sParams = _T("/?");

	// Run - assume zero ret code
	nRetCode = TestUtils::RunProgram(sExeName, sParams);
	TEST_ASSERT(nRetCode==0);

	__TEST_CLEANUP__;
}

void CrproberTests::Test_output()
{ 
    // This test calls crprober.exe with /f, fmd5 and /o flags to
    // generate a text output file from error report ZIP archive

    CString sExeName;
    CString sParams;
    BOOL bExecute = FALSE;
    SHELLEXECUTEINFO sei;
    memset(&sei, 0, sizeof(SHELLEXECUTEINFO));
    DWORD dwExitCode = 1;
    DWORD dwFileAttrs = INVALID_FILE_ATTRIBUTES;

#ifdef _DEBUG
    sExeName = Utility::GetModulePath(NULL)+_T("\\crproberd.exe");
#else
    sExeName = Utility::GetModulePath(NULL)+_T("\\crprober.exe");
#endif

    sParams.Format(_T("/f \"%s\" /fmd5 \"%s\" /o \"%s\""), 
        m_sErrorReportName, 
        m_sErrorReportName+_T(".md5"),
        m_sTmpFolder+_T("\\out.txt"));

    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS|SEE_MASK_FLAG_NO_UI;
    sei.lpVerb = _T("open");
    sei.lpFile = sExeName;
    sei.lpParameters = sParams;
    sei.lpDirectory = m_sTmpFolder;

    bExecute = ShellExecuteEx(&sei);
    TEST_ASSERT(bExecute);

    // Wait until process exits
    WaitForSingleObject(sei.hProcess, 10000);

    // Check crprober.exe process exit code - it should equal to 0
    GetExitCodeProcess(sei.hProcess, &dwExitCode);
    TEST_ASSERT(dwExitCode==0);

    // Check that out.txt file exists
    dwFileAttrs = GetFileAttributes(m_sTmpFolder+_T("\\out.txt"));
    TEST_ASSERT(dwFileAttrs!=INVALID_FILE_ATTRIBUTES);

    __TEST_CLEANUP__;

    if(sei.hProcess)
    {
        CloseHandle(sei.hProcess);
        sei.hProcess = NULL;
    }

}

void CrproberTests::Test_extract_file()
{ 
    // This test calls crprober.exe with /ext flag to
    // extract all files from error report ZIP archive

    CString sExeName;
    CString sParams;
    BOOL bExecute = FALSE;
    SHELLEXECUTEINFO sei;
    memset(&sei, 0, sizeof(SHELLEXECUTEINFO));
    DWORD dwExitCode = 1;
    DWORD dwFileAttrs = INVALID_FILE_ATTRIBUTES;
    std::vector<CString> asFileList;
    UINT i;

    asFileList.push_back(_T("crashrpt.xml"));
    asFileList.push_back(_T("crashdump.dmp"));
    asFileList.push_back(_T("regkey.xml"));  

#ifdef _DEBUG
    sExeName = Utility::GetModulePath(NULL)+_T("\\crproberd.exe");
#else
    sExeName = Utility::GetModulePath(NULL)+_T("\\crprober.exe");
#endif

    sParams.Format(_T("/f \"%s\" /ext \"%s\""), m_sErrorReportName, m_sTmpFolder);

    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS|SEE_MASK_FLAG_NO_UI;
    sei.lpVerb = _T("open");
    sei.lpFile = sExeName;
    sei.lpParameters = sParams;
    sei.lpDirectory = m_sTmpFolder;

    bExecute = ShellExecuteEx(&sei);
    TEST_ASSERT(bExecute);

    // Wait until process exits
    WaitForSingleObject(sei.hProcess, 10000);

    // Check crprober.exe process exit code - it should equal to 0
    GetExitCodeProcess(sei.hProcess, &dwExitCode);
    TEST_ASSERT(dwExitCode==0);

    // Check that extracted files exist
    for(i=0; i<asFileList.size(); i++)
    {
        dwFileAttrs = GetFileAttributes(m_sTmpFolder+_T("\\")+asFileList[i]);
        TEST_ASSERT(dwFileAttrs!=INVALID_FILE_ATTRIBUTES);
    }

    __TEST_CLEANUP__;

    if(sei.hProcess)
    {
        CloseHandle(sei.hProcess);
        sei.hProcess = NULL;
    }  
}

void CrproberTests::Test_get()
{
	if(g_bRunningFromUNICODEFolder)
		return; // Skip this test for UNICODE case

	CString sExeName;
	std::wstring sOut;

#ifdef _DEBUG
    sExeName = Utility::GetModulePath(NULL)+_T("\\crproberd.exe");
#else
    sExeName = Utility::GetModulePath(NULL)+_T("\\crprober.exe");
#endif

	sExeName += _T(" /f \"");
	sExeName += m_sErrorReportName;
	sExeName += _T("\" /o \"\" /get XmlDescMisc AppName 0");

	sOut = TestUtils::exec(sExeName);
	TEST_ASSERT(sOut==L"My& app Name &");

	__TEST_CLEANUP__;
}