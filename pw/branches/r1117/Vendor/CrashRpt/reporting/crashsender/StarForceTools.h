#pragma once

namespace cr_starforce
{
  //bool IsStarforceCrash() { return true; }
  CString CreateReports( const CString& sfReportFilename, const CString& sUrl, const CString& sPrivacyPolicyURL );
};