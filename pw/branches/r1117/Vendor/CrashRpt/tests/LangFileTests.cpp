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
#include "TestUtils.h"
#define MIN(a,b) (a<=b?a:b)

class LangFileTests : public CTestSuite
{
    BEGIN_TEST_MAP(LangFileTests, "CrashRpt language file tests")
        REGISTER_TEST(Test_lang_file_versions);    
		REGISTER_TEST(Test_lang_file_strings);    
    END_TEST_MAP()

public:

    void SetUp();
    void TearDown();

    void Test_lang_file_versions();
	void Test_lang_file_strings();

private:

	std::vector<CString> m_asLangAbbr; // The list of lang file abbreviations

};


REGISTER_TEST_SUITE( LangFileTests );

void LangFileTests::SetUp()
{
    m_asLangAbbr.push_back(_T("DE"));
    m_asLangAbbr.push_back(_T("EN"));
    m_asLangAbbr.push_back(_T("ES"));
    m_asLangAbbr.push_back(_T("FR"));
    m_asLangAbbr.push_back(_T("HI"));
    m_asLangAbbr.push_back(_T("IT"));
    m_asLangAbbr.push_back(_T("PT"));
    m_asLangAbbr.push_back(_T("RU"));
    m_asLangAbbr.push_back(_T("ZH-CN"));

}

void LangFileTests::TearDown()
{
}

void LangFileTests::Test_lang_file_versions()
{ 
    // This test ensures that CrashRptVersion field of all CrashRpt language files
    // equals to CRASHRPT_VER constant value

    if(g_bRunningFromUNICODEFolder)
        return; // Skip this test if running from another process
	    
    const int BUFF_SIZE = 1024;
    TCHAR szBuffer[BUFF_SIZE]=_T("");

    UINT i;
    for(i=0; i<m_asLangAbbr.size(); i++)
    {
        CString sExePath = Utility::GetModulePath(NULL);
        CString sFileName;
#ifndef WIN64
        sFileName.Format(_T("%s\\..\\lang_files\\crashrpt_lang_%s.ini"), 
            sExePath.GetBuffer(0), m_asLangAbbr[i].GetBuffer(0));
#else
        sFileName.Format(_T("%s\\..\\..\\lang_files\\crashrpt_lang_%s.ini"), 
            sExePath.GetBuffer(0), m_asLangAbbr[i].GetBuffer(0));
#endif //!WIN64

        GetPrivateProfileString(_T("Settings"), _T("CrashRptVersion"), _T(""), szBuffer, BUFF_SIZE, sFileName);

        int nActualVer = _ttoi(szBuffer);

        TEST_ASSERT(nActualVer==CRASHRPT_VER);
    }

    __TEST_CLEANUP__;


}

void LangFileTests::Test_lang_file_strings()
{ 
    // This test ensures that all lang files have the same count of
	// sections and the same count of strings in each section.

    if(g_bRunningFromUNICODEFolder)
        return; // Skip this test if running from another process
	
	strconv_t strconv;
	CString sExePath = Utility::GetModulePath(NULL);

	// Use EN lang file as template for comparison
    CString sTemplateFileName;
#ifndef WIN64
    sTemplateFileName.Format(_T("%s\\..\\lang_files\\crashrpt_lang_EN.ini"), 
            sExePath.GetBuffer(0));
#else
    sTemplateFileName.Format(_T("%s\\..\\..\\lang_files\\crashrpt_lang_EN.ini"), 
            sExePath.GetBuffer(0));
#endif //!WIN64
	
    UINT i;
    for(i=0; i<m_asLangAbbr.size(); i++)
    {
		if(m_asLangAbbr[i]==_T("EN"))
			continue; // Skip EN file
    
		// Format i-th file name
        CString sFileName;
#ifndef WIN64
        sFileName.Format(_T("%s\\..\\lang_files\\crashrpt_lang_%s.ini"), 
            sExePath.GetBuffer(0), m_asLangAbbr[i].GetBuffer(0));
#else
        sFileName.Format(_T("%s\\..\\..\\lang_files\\crashrpt_lang_%s.ini"), 
            sExePath.GetBuffer(0), m_asLangAbbr[i].GetBuffer(0));
#endif //!WIN64

		// Get count of sections in EN file
		std::vector<CString> asTemplateSections;
		int nTemplateSectionCount = TestUtils::EnumINIFileSections(sTemplateFileName, asTemplateSections);

		// Get count of sections in i-th file
		std::vector<CString> asSections;
		int nSectionCount = TestUtils::EnumINIFileSections(sFileName, asSections);

		// Ensure section count is the same
		TEST_ASSERT_MSG(nTemplateSectionCount==nSectionCount, "Count of INI sections is different in lang files EN and %s", strconv.t2a(m_asLangAbbr[i]));

		// Now compare strings in each section

		int nSection = 0;
		for(nSection = 0; nSection<nTemplateSectionCount; nSection++)
		{
			// Get count of strings in n-th section in EN file
			std::vector<CString> asTemplateStrings;
			int nTemplateStringCount = TestUtils::EnumINIFileStrings(sTemplateFileName, asTemplateSections[nSection], asTemplateStrings);

			// Get count of strings in n-th section in i-th file
			std::vector<CString> asStrings;
			int nStringCount = TestUtils::EnumINIFileStrings(sFileName, asTemplateSections[nSection], asStrings);
						
			// Compare string names
			size_t nStr;
			for(nStr=0; nStr<MIN(asTemplateStrings.size(), asStrings.size()); nStr++)
			{
				// Ensure string names are the same
				TEST_ASSERT_MSG(asTemplateStrings[nStr]==asStrings[nStr], "Names of INI strings #%d in section %s are different in lang files EN and %s : %s and %s", 
					nStr, strconv.t2a(asTemplateSections[nSection]), strconv.t2a(m_asLangAbbr[i]), strconv.t2a(asTemplateStrings[nStr]), strconv.t2a(asStrings[nStr]));
			}

			// Ensure string count is the same
			TEST_ASSERT_MSG(nTemplateStringCount==nStringCount, "Count of INI strings in section %s is different in lang files EN and %s", strconv.t2a(asTemplateSections[nSection]), strconv.t2a(m_asLangAbbr[i]));

		}
    }

    __TEST_CLEANUP__;


}