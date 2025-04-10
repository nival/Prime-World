/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: strconv.h
// Description: String conversion class
// Author: zexspectrum
// Date: 2009-2010

#ifndef _STRCONV_H
#define _STRCONV_H

#include "Prefastdef.h"
#include <vector>

class strconv_t
{
public:
    strconv_t(){}
    ~strconv_t()
    {
        unsigned i;
        for(i=0; i<m_ConvertedStrings.size(); i++)
        {
            delete [] m_ConvertedStrings[i];
        }
    }

    LPCWSTR a2w(__in_opt LPCSTR lpsz)
    {
        if(lpsz==NULL)
            return NULL;

        int count = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpsz, -1, NULL, 0);
        if(count==0)
            return NULL;

        void* pBuffer = (void*) new wchar_t[count];
        int result = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpsz, -1, (LPWSTR)pBuffer, count);
        if(result==0)
        {
            delete [] pBuffer;
            return NULL;
        }    

        m_ConvertedStrings.push_back(pBuffer);
        return (LPCWSTR)pBuffer;
    }

    LPCSTR w2a(__in_opt LPCWSTR lpsz)
    { 
        if(lpsz==NULL)
            return NULL;

        int count = WideCharToMultiByte(CP_ACP, 0, lpsz, -1, NULL, 0, NULL, NULL);
        if(count==0)
            return NULL;

        void* pBuffer = (void*) new char[count];
        int result = WideCharToMultiByte(CP_ACP, 0, lpsz, -1, (LPSTR)pBuffer, count, NULL, NULL);
        if(result==0)
        {
            delete [] pBuffer;
            return NULL;
        }    

        m_ConvertedStrings.push_back(pBuffer);
        return (LPCSTR)pBuffer;
    }

    // Converts UNICODE little endian string to UNICODE big endian 
    LPCWSTR w2w_be(__in_opt LPCWSTR lpsz, UINT cch)
    {
        if(lpsz==NULL)
            return NULL;

        WCHAR* pBuffer = new WCHAR[cch+1];    
        UINT i;
        for(i=0; i<cch; i++)
        {
            // Swap bytes
            pBuffer[i] = (WCHAR)MAKEWORD((lpsz[i]>>8), (lpsz[i]&0xFF));
        }

        pBuffer[cch] = 0; // Zero terminator

        m_ConvertedStrings.push_back((void*)pBuffer);
        return (LPCWSTR)pBuffer;
    }

    LPCSTR a2utf8(__in_opt LPCSTR lpsz)
    {
        if(lpsz==NULL)
            return NULL;

        // 1. Convert input ANSI string to widechar using 
        // MultiByteToWideChar(CP_ACP, ...) function (CP_ACP 
        // is current Windows system Ansi code page)

        // Calculate required buffer size
        int count = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpsz, -1, NULL, 0);
        if(count==0)
            return NULL;

        // Convert ANSI->UNICODE
        wchar_t* pBuffer = new wchar_t[count];
        int result = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpsz, -1, (LPWSTR)pBuffer, count);
        if(result==0)
        {
            delete [] pBuffer;
            return NULL;
        }  

        // 2. Convert output widechar string from previous call to 
        // UTF-8 using WideCharToMultiByte(CP_UTF8, ...)  function

        LPCSTR pszResult = (LPCSTR)w2utf8(pBuffer);
        delete [] pBuffer;
        return pszResult;
    }

    LPCSTR w2utf8(__in_opt LPCWSTR lpsz)
    {
        if(lpsz==NULL)
            return NULL;

        // Calculate required buffer size
        int count = WideCharToMultiByte(CP_UTF8, 0, lpsz, -1, NULL, 0, NULL, NULL);
        if(count==0)
        {      
            return NULL;
        }

        // Convert UNICODE->UTF8
        LPSTR pBuffer = new char[count];
        int result = WideCharToMultiByte(CP_UTF8, 0, lpsz, -1, (LPSTR)pBuffer, count, NULL, NULL);    
        if(result==0)
        {      
            delete [] pBuffer;
            return NULL;
        }    

        m_ConvertedStrings.push_back(pBuffer);
        return (LPCSTR)pBuffer;
    }

    LPCWSTR utf82w(__in_opt LPCSTR lpsz)
    {
        if(lpsz==NULL)
            return NULL;

        // Calculate required buffer size
        int count = MultiByteToWideChar(CP_UTF8, 0, lpsz, -1, NULL, 0);
        if(count==0)
        {      
            return NULL;
        }

        // Convert UNICODE->UTF8
        LPWSTR pBuffer = new wchar_t[count];
        int result = MultiByteToWideChar(CP_UTF8, 0, lpsz, -1, (LPWSTR)pBuffer, count);    
        if(result==0)
        {      
            delete [] pBuffer;
            return NULL;
        }    

        m_ConvertedStrings.push_back(pBuffer);
        return (LPCWSTR)pBuffer;
    }

    LPCWSTR utf82w(__in_opt LPCSTR pStr, UINT cch)
    {
        if(pStr==NULL)
            return NULL;

        // Calculate required buffer size
        int count = MultiByteToWideChar(CP_UTF8, 0, pStr, cch, NULL, 0);
        if(count==0)
        {      
            return NULL;
        }

        // Convert UNICODE->UTF8
        LPWSTR pBuffer = new wchar_t[count+1];
        int result = MultiByteToWideChar(CP_UTF8, 0, pStr, cch, (LPWSTR)pBuffer, count);    
        if(result==0)
        {      
            delete [] pBuffer;
            return NULL;
        }    

        // Zero-terminate
        pBuffer[count]=0;

        m_ConvertedStrings.push_back(pBuffer);
        return (LPCWSTR)pBuffer;
    }

    LPCSTR utf82a(__in_opt LPCSTR lpsz)
    {
        return w2a(utf82w(lpsz));
    }

    LPCTSTR utf82t(__in_opt LPCSTR lpsz)
    {
#ifdef UNICODE    
        return utf82w(lpsz);
#else
        return utf82a(lpsz);
#endif
    }

    LPCSTR t2a(__in_opt LPCTSTR lpsz)
    {
#ifdef UNICODE    
        return w2a(lpsz);
#else
        return lpsz;
#endif
    }

    LPCWSTR t2w(__in_opt LPCTSTR lpsz)
    {
#ifdef UNICODE    
        return lpsz;
#else
        return a2w(lpsz);
#endif
    }

    LPCTSTR a2t(__in_opt LPCSTR lpsz)
    {
#ifdef UNICODE    
        return a2w(lpsz);
#else
        return lpsz;
#endif
    }

    LPCTSTR w2t(__in_opt LPCWSTR lpsz)
    {
#ifdef UNICODE    
        return lpsz;
#else
        return w2a(lpsz);
#endif
    }

    LPCSTR t2utf8(__in_opt LPCTSTR lpsz)
    {
#ifdef UNICODE    
        return w2utf8(lpsz);
#else
        return a2utf8(lpsz);
#endif
    }

private:
    std::vector<void*> m_ConvertedStrings;  
};

#endif  //_STRCONV_H


