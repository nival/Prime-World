/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashDescReader.cpp
// Description: Crash description XML file reader.
// Authors: zexspectrum
// Date: 2010

#include "stdafx.h"
#include "CrashRpt.h"
#include "CrashDescReader.h"
#include "tinyxml.h"
#include "Utility.h"
#include "strconv.h"

CCrashDescReader::CCrashDescReader()
{
    m_bLoaded = false;
    m_dwExceptionType = 0;
    m_dwFPESubcode = 0;
    m_dwExceptionCode = 0;
    m_dwInvParamLine = 0;
}

CCrashDescReader::~CCrashDescReader()
{
}

int CCrashDescReader::Load(CString sFileName)
{
    TiXmlDocument doc;
    FILE* f = NULL;
    strconv_t strconv;

    if(m_bLoaded)
        return 1; // already loaded

    // Check that the file exists
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));
#endif

    if(f==NULL)
        return -1; // File can't be opened

    // Open XML document  
    bool bLoaded = doc.LoadFile(f);
    if(!bLoaded)
    {
        fclose(f);
        return -2; // XML is corrupted
    }

    TiXmlHandle hDoc(&doc);

    TiXmlHandle hRoot = hDoc.FirstChild("CrashRpt").ToElement();
    if(hRoot.ToElement()==NULL)
    {
        if(LoadXmlv10(hDoc)==0)
        {
            fclose(f);
            return 0;
        }  

        return -3; // Invalid XML structure
    }

    // Get generator version

    const char* szCrashRptVersion = hRoot.ToElement()->Attribute("version");
    if(szCrashRptVersion!=NULL)
    {
        m_dwGeneratorVersion = atoi(szCrashRptVersion);
    }

    // Get CrashGUID
    TiXmlHandle hCrashGUID = hRoot.ToElement()->FirstChild("CrashGUID");
    if(hCrashGUID.ToElement())
    {    
        TiXmlText* pTextElem = hCrashGUID.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sCrashGUID = strconv.utf82t(text);    
        }    
    }

    // Get AppName
    TiXmlHandle hAppName = hRoot.ToElement()->FirstChild("AppName");
    if(hAppName.ToElement())
    {    
        TiXmlText* pTextElem = hAppName.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sAppName = strconv.utf82t(text);        
        }
    }

    // Get AppVersion
    TiXmlHandle hAppVersion = hRoot.ToElement()->FirstChild("AppVersion");
    if(hAppVersion.ToElement())
    {    
        TiXmlText* pTextElem = hAppVersion.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sAppVersion = strconv.utf82t(text);    
        }
    }

    // Get ImageName
    TiXmlHandle hImageName = hRoot.ToElement()->FirstChild("ImageName");
    if(hImageName.ToElement())
    {    
        TiXmlText* pTextElem = hImageName.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sImageName = strconv.utf82t(text);        
        }
    }

    // Get OperatingSystem
    TiXmlHandle hOperatingSystem = hRoot.ToElement()->FirstChild("OperatingSystem");
    if(hOperatingSystem.ToElement())
    {    
        TiXmlText* pTextElem = hOperatingSystem.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sOperatingSystem = strconv.utf82t(text);        
        }
    }

    // Get GeoLocation
    TiXmlHandle hGeoLocation = hRoot.ToElement()->FirstChild("GeoLocation");
    if(hGeoLocation.ToElement())
    {    
        TiXmlText* pTextElem = hGeoLocation.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sGeoLocation = strconv.utf82t(text);        
        }
    }

    // Get OSIs64Bit
    m_bOSIs64Bit = FALSE;
    TiXmlHandle hOSIs64Bit = hRoot.ToElement()->FirstChild("OSIs64Bit");
    if(hOSIs64Bit.ToElement())
    {    
        TiXmlText* pTextElem = hOSIs64Bit.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_bOSIs64Bit = atoi(text);        
        }
    }

    // Get SystemTimeUTC
    TiXmlHandle hSystemTimeUTC = hRoot.ToElement()->FirstChild("SystemTimeUTC");
    if(hSystemTimeUTC.ToElement())
    {    
        TiXmlText* pTextElem = hSystemTimeUTC.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sSystemTimeUTC = strconv.utf82t(text);        
        }
    }

    // Get ExceptionType
    TiXmlHandle hExceptionType = hRoot.ToElement()->FirstChild("ExceptionType");
    if(hExceptionType.ToElement())
    {    
        TiXmlText* pTextElem = hExceptionType.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_dwExceptionType = atoi(text);        
        }
    }

    // Get UserEmail
    TiXmlHandle hUserEmail = hRoot.ToElement()->FirstChild("UserEmail");
    if(hUserEmail.ToElement())
    {    
        TiXmlText* pTextElem = hUserEmail.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sUserEmail = strconv.utf82t(text);    
        }
    }

    // Get ProblemDecription
    TiXmlHandle hProblemDescription = hRoot.ToElement()->FirstChild("ProblemDescription");
    if(hProblemDescription.ToElement())
    {
        TiXmlText* pTextElem = hProblemDescription.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sProblemDescription = strconv.utf82t(text);    
        }
    }

    // Get ExceptionCode (for SEH exceptions only)
    if(m_dwExceptionType==CR_SEH_EXCEPTION)
    {    
        TiXmlHandle hExceptionCode = hRoot.ToElement()->FirstChild("ExceptionCode");
        if(hExceptionCode.ToElement())
        {      
            TiXmlText* pTextElem = hExceptionCode.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_dwExceptionCode = atoi(text);    
            }
        }
    }

    // Get FPESubcode (for FPE exceptions only)
    if(m_dwExceptionType==CR_CPP_SIGFPE)
    {    
        TiXmlHandle hFPESubcode = hRoot.ToElement()->FirstChild("FPESubcode");
        if(hFPESubcode.ToElement())
        {      
            TiXmlText* pTextElem = hFPESubcode.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_dwFPESubcode = atoi(text);          
            }
        }
    }

    // Get InvParamExpression, InvParamFunction, InvParamFile, InvParamLine 
    // (for invalid parameter exceptions only)
    if(m_dwExceptionType==CR_CPP_INVALID_PARAMETER)
    {    
        TiXmlHandle hInvParamExpression = hRoot.ToElement()->FirstChild("InvParamExpression");
        if(hInvParamExpression.ToElement())
        {      
            TiXmlText* pTextElem = hInvParamExpression.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_sInvParamExpression = strconv.utf82t(text);          
            }
        }

        TiXmlHandle hInvParamFunction = hRoot.ToElement()->FirstChild("InvParamFunction");
        if(hInvParamFunction.ToElement())
        {      
            TiXmlText* pTextElem = hInvParamFunction.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_sInvParamFunction = strconv.utf82t(text);          
            }
        }

        TiXmlHandle hInvParamFile = hRoot.ToElement()->FirstChild("InvParamFile");
        if(hInvParamFile.ToElement())
        {      
            TiXmlText* pTextElem = hInvParamFile.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_sInvParamFile = strconv.utf82t(text);          
            }
        }

        TiXmlHandle hInvParamLine = hRoot.ToElement()->FirstChild("InvParamLine");
        if(hInvParamLine.ToElement())
        {      
            TiXmlText* pTextElem = hInvParamLine.FirstChild().Text();     
            if(pTextElem)
            {
                const char* text = pTextElem->Value();
                if(text)
                    m_dwInvParamLine = atoi(text);          
            }
        }
    }

    // Get GUI resource count
    TiXmlHandle hGUIResourceCount = hRoot.ToElement()->FirstChild("GUIResourceCount");
    if(hGUIResourceCount.ToElement())
    {      
        TiXmlText* pTextElem = hGUIResourceCount.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sGUIResourceCount = strconv.utf82t(text);          
        }
    }

    // Get open handle count
    TiXmlHandle hOpenHandleCount = hRoot.ToElement()->FirstChild("OpenHandleCount");
    if(hOpenHandleCount.ToElement())
    {      
        TiXmlText* pTextElem = hOpenHandleCount.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sOpenHandleCount = strconv.utf82t(text);          
        }
    }

    // Get memory usage in KB
    TiXmlHandle hMemoryUsageKbytes = hRoot.ToElement()->FirstChild("MemoryUsageKbytes");
    if(hMemoryUsageKbytes.ToElement())
    {      
        TiXmlText* pTextElem = hMemoryUsageKbytes.FirstChild().Text();     
        if(pTextElem)
        {
            const char* text = pTextElem->Value();
            if(text)
                m_sMemoryUsageKbytes = strconv.utf82t(text);          
        }
    }

    // Get file items list
    TiXmlHandle hFileList = hRoot.ToElement()->FirstChild("FileList");
    if(!hFileList.ToElement())
    {
        // This may work for reports generated by v1.2.1
        hFileList = hRoot.ToElement()->FirstChild("FileItems");
    }
    if(hFileList.ToElement())
    {
        TiXmlHandle hFileItem = hFileList.ToElement()->FirstChild("FileItem");
        while(hFileItem.ToElement())
        {
            const char* szFileName = hFileItem.ToElement()->Attribute("name");
            const char* szFileDescription = hFileItem.ToElement()->Attribute("description");

            CString sFileName, sFileDescription;
            if(szFileName!=NULL)
                sFileName = strconv.utf82t(szFileName);    
            if(szFileName!=NULL)
                sFileDescription = strconv.utf82t(szFileDescription);    

            m_aFileItems[sFileName]=sFileDescription;

            hFileItem = hFileItem.ToElement()->NextSibling();
        }
    }

    // Get custom property list
    TiXmlHandle hCustomProps = hRoot.ToElement()->FirstChild("CustomProps");
    if(hCustomProps.ToElement())
    {
        TiXmlHandle hProp = hCustomProps.ToElement()->FirstChild("Prop");
        while(hProp.ToElement())
        {
            const char* szName = hProp.ToElement()->Attribute("name");
            const char* szValue = hProp.ToElement()->Attribute("value");

            CString sName, sValue;
            if(szName!=NULL)
                sName = strconv.utf82t(szName);    
            if(szValue!=NULL)
                sValue = strconv.utf82t(szValue);    

            m_aCustomProps[sName]=sValue;

            hProp = hProp.ToElement()->NextSibling();
        }
    }

    fclose(f);

    // OK  
    m_bLoaded = true;
    return 0;
}

int CCrashDescReader::LoadXmlv10(TiXmlHandle hDoc)
{
    TiXmlHandle hRoot = hDoc.FirstChild("Exception").ToElement();
    if(hRoot.ToElement()==NULL)
    {
        return -3; // Invalid XML structure
    }

    // Set CrashRpt version to 1000

    m_dwGeneratorVersion = 1000;

    // Get ExceptionRecord element

    TiXmlHandle hExceptionRecord = hRoot.FirstChild("ExceptionRecord").ToElement();

    if(hExceptionRecord.ToElement()!=NULL)
    {
        const char* szImageName = hRoot.ToElement()->Attribute("ModuleName");
        if(szImageName!=NULL)
        {
            m_sImageName = szImageName;

            m_sAppName = Utility::GetBaseFileName(szImageName);
        }
    }  

    // OK
    m_bLoaded = true;
    return 0;
}
