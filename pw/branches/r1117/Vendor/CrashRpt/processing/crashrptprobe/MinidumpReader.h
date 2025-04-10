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
#include "dbghelp.h"
#include <map>
#include <vector>

// Describes a loaded module
struct MdmpModule
{
    ULONG64 m_uBaseAddr;   // Base address
    ULONG64 m_uImageSize;  // Size of module
    CString m_sModuleName; // Module name  
    CString m_sImageName;  // The image name. The name may or may not contain a full path. 
    CString m_sLoadedImageName; // The full path and file name of the file from which symbols were loaded. 
    CString m_sLoadedPdbName;   // The full path and file name of the .pdb file.     
    BOOL m_bImageUnmatched;     // If TRUE than there wasn't matching binary found.
    BOOL m_bPdbUnmatched;       // If TRUE than there wasn't matching PDB file found.
    BOOL m_bNoSymbolInfo;       // If TRUE than no symbols were generated for this module.
    VS_FIXEDFILEINFO* m_pVersionInfo; // Version info for module.
};

// Describes a stack frame
struct MdmpStackFrame
{
    MdmpStackFrame()
    {
        m_nModuleRowID = -1;
        m_dw64OffsInSymbol = 0;
        m_nSrcLineNumber = -1;
    }

    DWORD64 m_dwAddrPCOffset; 
    int m_nModuleRowID;         // ROWID of the record in CPR_MDMP_MODULES table.
    CString m_sSymbolName;      // Name of symbol
    DWORD64 m_dw64OffsInSymbol; // Offset in symbol
    CString m_sSrcFileName;     // Name of source file
    int m_nSrcLineNumber;       // Line number in the source file
};

// Describes a thread
struct MdmpThread
{
    MdmpThread()
    {
        m_dwThreadId = 0;
        m_pThreadContext = NULL;
        m_bStackWalk = FALSE;
    }

    DWORD m_dwThreadId;        // Thread ID.
    CONTEXT* m_pThreadContext; // Thread context
    BOOL m_bStackWalk;         // Was stack trace retrieved for this thread?
    CString m_sStackTraceMD5;
    std::vector<MdmpStackFrame> m_StackTrace; // Stack trace for this thread.
};

// Describes a memory range
struct MdmpMemRange
{
    ULONG64 m_u64StartOfMemoryRange; // Starting address
    ULONG32 m_uDataSize;             // Size of data
    LPVOID m_pStartPtr;              // Pointer to the memrange data stored in minidump
};

// Minidump data
struct MdmpData
{   
    MdmpData()
    {
        m_hProcess = INVALID_HANDLE_VALUE;
        m_uProcessorArchitecture = 0;
        m_uchProductType = 0;
        m_ulVerMajor = 0;
        m_ulVerMinor = 0;
        m_ulVerBuild = 0;    
        m_uExceptionCode = 0;
        m_uExceptionAddress = 0;
        m_uExceptionThreadId = 0;
        m_pExceptionThreadContext = NULL;
    }

    HANDLE m_hProcess; // Process ID

    USHORT m_uProcessorArchitecture; // CPU architecture
    UCHAR  m_uchNumberOfProcessors;  // Number of processors
    UCHAR  m_uchProductType;         // Type of machine (workstation, server, ...)
    ULONG  m_ulVerMajor;             // OS major version number
    ULONG  m_ulVerMinor;             // OS minor version number
    ULONG  m_ulVerBuild;             // OS build number
    CString m_sCSDVer;               // The latest service pack installed

    ULONG32 m_uExceptionCode;        // Structured exception's code
    ULONG64 m_uExceptionAddress;     // Exception address
    ULONG32 m_uExceptionThreadId;    // Exceptions thread ID 
    CONTEXT* m_pExceptionThreadContext; // Thread context

    std::vector<MdmpThread> m_Threads;       // The list of threads.
    std::map<DWORD, size_t> m_ThreadIndex;   // <thread_id, thread_entry_index> pairs
    std::vector<MdmpModule> m_Modules;       // The list of loaded modules.
    std::map<DWORD64, size_t> m_ModuleIndex; // <base_addr, module_entry_index> pairs
    std::vector<MdmpMemRange> m_MemRanges;   // The list of memory ranges.  
    std::vector<CString> m_LoadLog; // Load log
};

// Class for opening minidumps
class CMiniDumpReader
{
public:

    /* Construction/destruction */
    CMiniDumpReader();
    ~CMiniDumpReader();

    /* Operations */

    // Opens a minidump (DMP) file
    int Open(CString sFileName, CString sSymSearchPath);

    // Retreives stack trace for specified thread ID
    int StackWalk(DWORD dwThreadId);  

    // Closes the opened minidump file
    void Close();

    BOOL CheckDbgHelpApiVersion();

    int GetModuleRowIdByBaseAddr(DWORD64 dwBaseAddr);
    int GetModuleRowIdByAddress(DWORD64 dwAddress);
    int GetThreadRowIdByThreadId(DWORD dwThreadId);

    MdmpData m_DumpData; // Minidump data

    BOOL m_bLoaded;               // Is minidump loaded?
    BOOL m_bReadSysInfoStream;    // Was system info stream read?
    BOOL m_bReadExceptionStream;  // Was exception stream read?
    BOOL m_bReadModuleListStream; // Was module list stream read?
    BOOL m_bReadMemoryListStream; // Was memory list stream read?
    BOOL m_bReadThreadListStream; // Was thread list stream read?  

private:

    /* Internally used member functions */

    // Helper function which extracts a UNICODE string from the minidump
    CString GetMinidumpString(LPVOID pStartAddr, RVA rva);

    // Reads MINIDUMP_SYSTEM_INFO stream
    int ReadSysInfoStream();

    // Reads MINIDUMP_EXCEPTION_STREAM stream
    int ReadExceptionStream();

    // Reads MINIDUMP_MODULE_LIST stream
    int ReadModuleListStream();

    // Reads MINIDUMP_MEMORY_LIST stream
    int ReadMemoryListStream();

    // Reads MINIDUMP_THREAD_LIST stream
    int ReadThreadListStream();

    /* Member variables */

    CString m_sFileName;    // Minidump file name.
    CString m_sSymSearchPath; // The list of symbol search dirs passed.
    HANDLE m_hFileMiniDump; // Handle to opened .DMP file
    HANDLE m_hFileMapping;  // Handle to memory mapping object
    LPVOID m_pMiniDumpStartPtr; // Pointer to the biginning of memory-mapped minidump  

};

