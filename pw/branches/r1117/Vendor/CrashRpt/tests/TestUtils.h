/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"

namespace TestUtils
{

// A helper function that creates a error report for testing
BOOL CreateErrorReport(CString sTmpFolder, CString& sErrorReportName, CString& sMD5Hash);

// Returns the list of sections in an INI file.
int EnumINIFileSections(CString sFileName, std::vector<CString>& aSections);

// Returns the list of strings in the specified section in an INI file.
int EnumINIFileStrings(CString sFileName, CString sSectionName, std::vector<CString>& aStrings);

// Launches the EXE program and returns its return code. 
int RunProgram(CString sExeName, CString sParams);

// Launches the EXE program and grabs its stdout output.
std::wstring exec(LPCTSTR szCmd); 

// Trims the string
void wtrim(std::wstring& str, const wchar_t* szTrim=L" \t\r\n");
};

