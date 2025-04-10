/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#pragma once
#include "stdafx.h"

extern BOOL g_bRunningFromUNICODEFolder; // Are we running from a UNICODE-named folder?

// What action to perform
enum eAction
{
    GET_NAMES, // Return test names
    RUN_TESTS  // Run tests
};

// Test suite class
class CTestSuite
{
public:

    // Constructor
    CTestSuite(CTestSuite* pParentSuite=NULL);

    // Allocates resources used by tests in this suite
    virtual void SetUp() = 0;  

    // Frees resources used by tests in this suite
    virtual void TearDown() = 0;

    // Returns suite name and description
    virtual void GetSuiteInfo(std::string& sName, std::string& sDescription) = 0;

    // Returns the list of tests in this suite or runs tests
    virtual void DoWithMyTests(eAction action, std::vector<std::string>& test_list) = 0;

    // Runs all or some tests from this test suite
    bool Run(std::set<std::string>& SuitesToRun);

    // Returns test list in this test suite 
    virtual std::vector<std::string> GetTestList(std::set<std::string>& SuitesToRun, bool bIncludeChildren = false);

    // Returns parent test suite
    CTestSuite* GetParentSuite();  

    // Sets parent suite
    void SetParentSuite(CTestSuite* pParent);

    // Returns count of child test suites
    UINT GetChildSuiteCount();  

    // Returns i-th child test suite
    CTestSuite* GetChildSuite(UINT i);  

    // Adds a child test suite
    void AddChildSuite(CTestSuite* pChildSuite);

    // Returns the list of errors
    std::vector<std::string> GetErrorList(bool bIncludeChildren = false);

    void ClearErrors();

    // Adds an error message to the list.
    void AddErrorMsg(const char* szFunction, const char* szAssertion, const char* szMsg, ...);

protected: 

    bool BeforeTest(const char* szFunction);
    void AfterTest(const char* szFunction);

private:

    CTestSuite* m_pParentSuite;   // Parent test suite
    std::vector<CTestSuite*> m_apChildSuites;     // The list of child test suites
    std::vector<std::string> m_asErrorMsg; // The list of error messages
    bool m_bSuiteSetUpFailed;
    bool m_bTestFailed;
};

#define BEGIN_TEST_MAP( TestSuite , Description)\
    virtual void GetSuiteInfo(std::string& sName, std::string& sDescription)\
{\
    sName = std::string( #TestSuite );\
    sDescription = std::string( Description );\
}\
    virtual void DoWithMyTests(eAction action, std::vector<std::string>& test_list)\
{

#define REGISTER_TEST( Test )\
    if(action==GET_NAMES)\
    test_list.push_back( #Test );\
else\
{\
    if(BeforeTest( #Test ))\
    Test();\
    AfterTest( #Test);\
}

#define END_TEST_MAP() }

class TopLevelTestSuite : public CTestSuite
{
public:

    BEGIN_TEST_MAP( TopLevelTestSuite, "All tests")
        UNREFERENCED_PARAMETER(test_list);
        UNREFERENCED_PARAMETER(action);
    END_TEST_MAP()

        TopLevelTestSuite()
        :CTestSuite(NULL)
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

class CTestRegistry
{
public: 

    static CTestRegistry* GetRegistry();

    CTestRegistry();

    CTestSuite* GetTopSuite();

private:

    CTestSuite* m_pTopSuite; // The top-level test suite.  
};

extern CTestSuite* g_pCurTestSuite;

#define TEST_ASSERT(expr)\
    if(!(expr)) { g_pCurTestSuite->AddErrorMsg(__FUNCTION__, #expr, NULL); \
    goto test_cleanup; }

#define TEST_ASSERT_MSG(expr, ...)\
	if(!(expr)) { g_pCurTestSuite->AddErrorMsg((__FUNCTION__), (#expr), __VA_ARGS__); \
    goto test_cleanup; }

#define __TEST_CLEANUP__ test_cleanup:

template <class T>
class CTestSuiteRegistrator
{
public:

    CTestSuiteRegistrator()
    {		
        CTestRegistry* pRegistry = CTestRegistry::GetRegistry();  
        CTestSuite* pTopSuite = pRegistry->GetTopSuite();
        CTestSuite* pSuite = new T();  
        pSuite->SetParentSuite(pTopSuite);
        pTopSuite->AddChildSuite(pSuite);
    }
};

#define REGISTER_TEST_SUITE( Suite ) CTestSuiteRegistrator<Suite> __reg_##Suite;

