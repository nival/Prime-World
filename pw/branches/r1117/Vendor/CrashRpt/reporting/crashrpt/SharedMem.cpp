/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "SharedMem.h"

CSharedMem::CSharedMem()  
{
	// Set internal variables to their default state
    m_uSize = 0;
    m_hFileMapping = NULL;  

	// Determine memory granularity (needed for file mapping).
    SYSTEM_INFO si;  
    GetSystemInfo(&si);
    m_dwAllocGranularity = si.dwAllocationGranularity;  
}

CSharedMem::~CSharedMem()
{
	// Clean up
    Destroy();
}


BOOL CSharedMem::Init(LPCTSTR szName, BOOL bOpenExisting, ULONG64 uSize)
{
	// If already initialised, do nothing
    if(m_hFileMapping!=NULL)
        return FALSE;

	// Either open existing file mapping or create new one
    if(!bOpenExisting)
    {	
        ULARGE_INTEGER i;
        i.QuadPart = uSize;
        m_hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, i.HighPart, i.LowPart, szName);
    }
    else
    {    
        m_hFileMapping = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE, FALSE, szName);
    }

	// Save name and size of the file mapping
    m_sName = szName;
    m_uSize = uSize; 

	// Check file mapping is valid
    if(m_hFileMapping==NULL)
    {
		// Failure
        m_uSize = 0;  
        return FALSE;
    }

	// Done
    return TRUE;
}

BOOL CSharedMem::IsInitialized()
{
	return m_hFileMapping!=NULL;
}

BOOL CSharedMem::Destroy()
{
	// Release all views of the file mapping
    std::map<LPBYTE, LPBYTE>::iterator it;
    for(it=m_aViewStartPtrs.begin(); it!=m_aViewStartPtrs.end(); it++)
    {
        UnmapViewOfFile(it ->second);    
    }
    m_aViewStartPtrs.clear();

	// Destroy file mapping
    if(m_hFileMapping!=NULL)
    {
        CloseHandle(m_hFileMapping);    
    }

    m_hFileMapping = NULL;	
    m_uSize = 0;  

    return TRUE;
}

CString CSharedMem::GetName()
{
	// Return file mapping name
    return m_sName;
}

ULONG64 CSharedMem::GetSize()
{
	// Return file mapping size
    return m_uSize;
}

LPBYTE CSharedMem::CreateView(DWORD dwOffset, DWORD dwLength)
{
	// Create view with specified offset from the beginning of the file mapping
	// and return pointer to the view
    DWORD dwBaseOffs = dwOffset-dwOffset%m_dwAllocGranularity;
    DWORD dwDiff = dwOffset-dwBaseOffs;
    LPBYTE pPtr = NULL;

    pPtr = (LPBYTE)MapViewOfFile(m_hFileMapping, FILE_MAP_READ|FILE_MAP_WRITE, 0, dwBaseOffs, dwLength + dwDiff);
    m_aViewStartPtrs[pPtr + dwDiff] = pPtr;

    return (pPtr+dwDiff);
}

void CSharedMem::DestroyView(LPBYTE pViewPtr)
{
	// Release the view having specified starting pointer
    std::map<LPBYTE, LPBYTE>::iterator it = m_aViewStartPtrs.find(pViewPtr);
    if(it!=m_aViewStartPtrs.end())
    {
        UnmapViewOfFile(it ->second);
        m_aViewStartPtrs.erase(it);
    }
}


