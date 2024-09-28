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
#include "Utility.h"
#include "CrashRpt.h"

class DeliveryTests : public CTestSuite
{
    BEGIN_TEST_MAP(DeliveryTests, "Error report delivery tests")        
        REGISTER_TEST(Test_HttpDelivery)
        REGISTER_TEST(Test_SmtpDelivery)
        REGISTER_TEST(Test_SmtpDelivery_proxy);
        REGISTER_TEST(Test_SMAPI_Delivery)
    END_TEST_MAP()

public:

    void SetUp();
    void TearDown();
	    
    void Test_HttpDelivery();
    void Test_SmtpDelivery();
    void Test_SmtpDelivery_proxy();
    void Test_SMAPI_Delivery();
};

REGISTER_TEST_SUITE( DeliveryTests );

void DeliveryTests::SetUp()
{
}

void DeliveryTests::TearDown()
{
}

void DeliveryTests::Test_HttpDelivery()
{ 
    CString sAppDataFolder;
    CString sExeFolder;
    CString sTmpFolder;

    // Create a temporary folder  
    Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
    sTmpFolder = sAppDataFolder+_T("\\CrashRpt");
    BOOL bCreate = Utility::CreateFolder(sTmpFolder);
    TEST_ASSERT(bCreate);

    // Install crash handler for the main thread

    CR_INSTALL_INFO info;
    memset(&info, 0, sizeof(CR_INSTALL_INFO));
    info.cb = sizeof(CR_INSTALL_INFO);
    info.pszAppVersion = _T("1.0.0"); // Specify app version, otherwise it will fail.
    info.dwFlags = CR_INST_NO_GUI;
    info.pszUrl = _T("localhost/crashrpt.php"); // Use HTTP address for delivery 
    info.uPriorities[CR_HTTP] = 0;
    info.uPriorities[CR_SMTP] = CR_NEGATIVE_PRIORITY;
    info.uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;  
    info.pszErrorReportSaveDir = sTmpFolder;
    int nInstResult = crInstall(&info);
    TEST_ASSERT(nInstResult==0);

    // Generate and send error report
    CR_EXCEPTION_INFO exc;
    memset(&exc, 0, sizeof(CR_EXCEPTION_INFO));
    exc.cb = sizeof(CR_EXCEPTION_INFO);
    int nResult2 = crGenerateErrorReport(&exc);
    TEST_ASSERT(nResult2==0);

    // Wait until CrashSender exits and check exit code
    WaitForSingleObject(exc.hSenderProcess, INFINITE);

    DWORD dwExitCode = 1;
    GetExitCodeProcess(exc.hSenderProcess, &dwExitCode);
    TEST_ASSERT(dwExitCode==0); // Exit code should be zero

    __TEST_CLEANUP__;  

    // Uninstall
    crUninstall();  

    // Delete tmp folder
    Utility::RecycleFile(sTmpFolder, TRUE);
}

void DeliveryTests::Test_SmtpDelivery()
{ 
    CString sAppDataFolder;
    CString sExeFolder;
    CString sTmpFolder;

    // Create a temporary folder  
    Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
    sTmpFolder = sAppDataFolder+_T("\\CrashRpt");
    BOOL bCreate = Utility::CreateFolder(sTmpFolder);
    TEST_ASSERT(bCreate);

    // Install crash handler for the main thread

    CR_INSTALL_INFO info;
    memset(&info, 0, sizeof(CR_INSTALL_INFO));
    info.cb = sizeof(CR_INSTALL_INFO);
    info.pszAppVersion = _T("1.0.0"); // Specify app version, otherwise it will fail.
    info.dwFlags = CR_INST_NO_GUI;
    info.pszEmailTo = _T("test@localhost");
    info.pszEmailSubject = _T("Crash Report Whooaaa!!!");
    info.pszEmailText = _T("And some text in the email body...");
    info.uPriorities[CR_HTTP] = CR_NEGATIVE_PRIORITY;
    info.uPriorities[CR_SMTP] = 0;
    info.uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;  
    info.pszErrorReportSaveDir = sTmpFolder;
    int nInstResult = crInstall(&info);
    TEST_ASSERT(nInstResult==0);

    // Generate and send error report
    CR_EXCEPTION_INFO exc;
    memset(&exc, 0, sizeof(CR_EXCEPTION_INFO));
    exc.cb = sizeof(CR_EXCEPTION_INFO);
    int nResult2 = crGenerateErrorReport(&exc);
    TEST_ASSERT(nResult2==0);

    // Wait until CrashSender exits and check exit code
    WaitForSingleObject(exc.hSenderProcess, INFINITE);

    DWORD dwExitCode = 1;
    GetExitCodeProcess(exc.hSenderProcess, &dwExitCode);
    TEST_ASSERT(dwExitCode==0); // Exit code should be zero

    __TEST_CLEANUP__;  

    // Uninstall
    crUninstall();  

    // Delete tmp folder
    Utility::RecycleFile(sTmpFolder, TRUE);
}

void DeliveryTests::Test_SmtpDelivery_proxy()
{ 
    CString sAppDataFolder;
    CString sExeFolder;
    CString sTmpFolder;

    // Create a temporary folder  
    Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
    sTmpFolder = sAppDataFolder+_T("\\CrashRpt");
    BOOL bCreate = Utility::CreateFolder(sTmpFolder);
    TEST_ASSERT(bCreate);

    // Install crash handler for the main thread

    CR_INSTALL_INFO info;
    memset(&info, 0, sizeof(CR_INSTALL_INFO));
    info.cb = sizeof(CR_INSTALL_INFO);
    info.pszAppVersion = _T("1.0.0"); // Specify app version, otherwise it will fail.
    info.dwFlags = CR_INST_NO_GUI;
    info.pszEmailTo = _T("test@localhost");
    info.pszSmtpProxy = _T("127.0.0.1:25");
    info.pszEmailSubject = _T("Crash Report Whooaaa!!!");
    info.pszEmailText = _T("And some text in the email body...");
    info.uPriorities[CR_HTTP] = CR_NEGATIVE_PRIORITY;
    info.uPriorities[CR_SMTP] = 0;
    info.uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;  
    info.pszErrorReportSaveDir = sTmpFolder;
    int nInstResult = crInstall(&info);
    TEST_ASSERT(nInstResult==0);

    // Generate and send error report
    CR_EXCEPTION_INFO exc;
    memset(&exc, 0, sizeof(CR_EXCEPTION_INFO));
    exc.cb = sizeof(CR_EXCEPTION_INFO);
    int nResult2 = crGenerateErrorReport(&exc);
    TEST_ASSERT(nResult2==0);

    // Wait until CrashSender exits and check exit code
    WaitForSingleObject(exc.hSenderProcess, INFINITE);

    DWORD dwExitCode = 1;
    GetExitCodeProcess(exc.hSenderProcess, &dwExitCode);
    TEST_ASSERT(dwExitCode==0); // Exit code should be zero

    __TEST_CLEANUP__;  

    // Uninstall
    crUninstall();  

    // Delete tmp folder
    Utility::RecycleFile(sTmpFolder, TRUE);
}


// This test tries to send report in silent mode over SMAPI.
// Since SMAPI is not available in silent mode, test passes when delivery fails.
void DeliveryTests::Test_SMAPI_Delivery()
{ 
    CString sAppDataFolder;
    CString sExeFolder;
    CString sTmpFolder;

    // Create a temporary folder  
    Utility::GetSpecialFolder(CSIDL_APPDATA, sAppDataFolder);
    sTmpFolder = sAppDataFolder+_T("\\CrashRpt");
    BOOL bCreate = Utility::CreateFolder(sTmpFolder);
    TEST_ASSERT(bCreate);

    // Install crash handler for the main thread

    CR_INSTALL_INFO info;
    memset(&info, 0, sizeof(CR_INSTALL_INFO));
    info.cb = sizeof(CR_INSTALL_INFO);
    info.pszAppVersion = _T("1.0.0"); // Specify app version, otherwise it will fail.
    info.dwFlags = CR_INST_NO_GUI;
    info.pszEmailTo = _T("test@gmail.com");
    info.pszEmailSubject = _T("Crash Report Whooaaa!!!");
    info.pszEmailText = _T("And some text in the email body...");
    info.uPriorities[CR_HTTP] = CR_NEGATIVE_PRIORITY;
    info.uPriorities[CR_SMTP] = CR_NEGATIVE_PRIORITY;
    info.uPriorities[CR_SMAPI] = 0;  
    info.pszErrorReportSaveDir = sTmpFolder;
    int nInstResult = crInstall(&info);
    TEST_ASSERT(nInstResult==0);

    // Generate and send error report
    CR_EXCEPTION_INFO exc;
    memset(&exc, 0, sizeof(CR_EXCEPTION_INFO));
    exc.cb = sizeof(CR_EXCEPTION_INFO);
    int nResult2 = crGenerateErrorReport(&exc);
    TEST_ASSERT(nResult2==0);

    // Wait until CrashSender exits and check exit code
    WaitForSingleObject(exc.hSenderProcess, INFINITE);

    DWORD dwExitCode = 1;
    GetExitCodeProcess(exc.hSenderProcess, &dwExitCode);
    // Since SMAPI is not available in silent mode, test passes when delivery fails.
    TEST_ASSERT(dwExitCode!=0); // Exit code should be non-zero

    __TEST_CLEANUP__;  

    // Uninstall
    crUninstall();  

    // Delete tmp folder
    Utility::RecycleFile(sTmpFolder, TRUE);
}