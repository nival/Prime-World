// SQLRemotePerfChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <errno.h>
#include <stdio.h> 
#include <tchar.h>  
#include <vector> 
#include "mysql.h" 

struct ThreadInfo {
  DWORD dwThreadId;
  HANDLE hThread; 
};

struct SQLPerfLine
{
  double rMaxTime;
  double rMinTime;
  double rAveTime;
  DWORD  nLineNum;
  DWORD  nRepeatTimes;
  TCHAR const *cpRequest;
  DWORD  nReqSize;
  SQLPerfLine()
  {
    memset(this, 0, sizeof(*this));
  }
  SQLPerfLine(SQLPerfLine const &o)
  {
    memcpy(this, &o, sizeof(*this));
  }
};

typedef std::vector<SQLPerfLine> SQLPerfData;

DWORD WINAPI ThreadProc(LPVOID lpParam) 
{ 
  MYSQL *pConnection;    // pointer to connection handler
  SQLPerfData *pPerfData = (SQLPerfData *)lpParam;
  DWORD nI;
  
  pConnection = mysql_init(NULL);
  //do connect shits
  if(!mysql_real_connect(pConnection, "www.d-inter.ru", "base", "qwerty", "primalforces", 49558, NULL, CLIENT_COMPRESS))            
  {
    if(!mysql_real_connect(pConnection, "10.0.0.39", "root", "", "primalforces", 3306, NULL, CLIENT_COMPRESS))            
    {
      _ftprintf(stderr, _T("Failed to connect to database: Error: %s\n"), mysql_error(pConnection));
      return 0; 
    }
  }
  if(!mysql_set_character_set(pConnection, "utf8")) 
  {
    printf("New client character set: %s\n", mysql_character_set_name(pConnection));
  }

  for(SQLPerfData::iterator it = pPerfData->begin(); it != pPerfData->end(); it++)
  {
    int nError;
    int nSize;
    nSize = WideCharToMultiByte(CP_UTF8, 0, it->cpRequest, it->nReqSize / sizeof(TCHAR), NULL, 0, NULL, NULL);
    if(nSize <= 0)
    {
      nError = GetLastError();
      continue;
    }
    char *pUTF8 = (char *)malloc(nSize);
    WideCharToMultiByte(CP_UTF8, 0, it->cpRequest, it->nReqSize / sizeof(TCHAR), pUTF8, nSize, NULL, NULL);

    for(nI = 0; nI < it->nRepeatTimes; nI++)
    {
      //begin timing
      LARGE_INTEGER nStart;
      ::QueryPerformanceCounter(&nStart);
      nError = mysql_real_query(pConnection, pUTF8, nSize);
      if(nError != 0)
      {
        _ftprintf(stderr, _T("Error executing query: %d, with error: %d, error_no=%d , %S\n"), it->nLineNum, nError, mysql_errno(pConnection), mysql_error(pConnection));
        continue; 
      }
      //end timing
      LARGE_INTEGER nEnd;
      LARGE_INTEGER nCountsPerSecond;
      ::QueryPerformanceCounter(&nEnd);
      ::QueryPerformanceFrequency(&nCountsPerSecond);
      // timing is seconds
      double elapsed = (double)(nEnd.QuadPart - nStart.QuadPart) / nCountsPerSecond.QuadPart;
      it->rMinTime = (it->rMinTime > 0)? min(it->rMinTime, elapsed): elapsed;
      it->rMaxTime = max(it->rMaxTime, elapsed);
      it->rAveTime += elapsed;

      MYSQL_RES *pRes = mysql_store_result(pConnection);
      if(pRes != NULL)
      {
        mysql_free_result(pRes); 
      }
    }
    if(it->nRepeatTimes > 0)
    {
      it->rAveTime = it->rAveTime / (double)it->nRepeatTimes;
    }
    free(pUTF8);
  }
              
  mysql_close(pConnection);
  return 0; 
} 

static void DumpResults(SQLPerfData &perfData, DWORD nIdx)
{
  TCHAR fanme[100];
  _stprintf_s(fanme, 99, _T("PerfDmp%d.txt"), nIdx);
  FILE *fp;
  _tfopen_s(&fp, fanme, _T("w"));
  _ftprintf_s(fp, _T("%6s %10s %10s %10s\n"), _T("Num"), _T("MaxMs"), _T("MinMs"), _T("AveMs"));
  for(SQLPerfData::iterator it = perfData.begin(); it != perfData.end(); it++)
  {
    _ftprintf_s(fp, _T("%06d %10.5lf %10.5lf %10.5lf\n"), it->nLineNum, it->rMaxTime * 1000.0, it->rMinTime * 1000.0, it->rAveTime * 1000.0);
  }
  fclose(fp);
}

int _tmain(int argc, _TCHAR* argv[])
{
  int        nI;
  BYTE      *pFileBuff;
  int        nNumThreads = 1; 

  if(argc >= 3)
  {
    _stscanf_s(argv[2], _T("%d"), &nNumThreads);
  }

  ThreadInfo  *threadInfo = new ThreadInfo[nNumThreads];
  SQLPerfData *dataFile  = new SQLPerfData[nNumThreads];

  if(argc < 2)
  {
    _tprintf_s(_T("Usage: SQLRemotePerfChecker.exe <filename with requests> <number of clients to simulate>\n\
  Request file format is:\n\
    1. Each line is new request\n\
    2. Line format <times to repeat> <request>. Example: 20 show databases;\n\
    3. File encoding: Windows little endian Unicode with BOM.\n\
  As a result you will get report file for each client.\n"));
    return 0;
  }

  //read file
  HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if(hFile == INVALID_HANDLE_VALUE)
  {
    _tprintf_s(_T("Could not open file %s\n"), argv[1]);
    return 0;
  }
  DWORD  nSize;
  nSize = GetFileSize(hFile, NULL);
  pFileBuff = (BYTE *)GlobalAlloc(GPTR, nSize + 10);
  DWORD nActuallyRead;
  ReadFile(hFile, pFileBuff, nSize, &nActuallyRead, NULL);
  CloseHandle(hFile);

  //parse file
  TCHAR *pCurr = (TCHAR *)(pFileBuff + 2); //skip BOM
  DWORD nCounter = 0; 
  while(*pCurr != _T('\0'))
  {
    SQLPerfLine  sqlLine;
    sqlLine.nLineNum = nCounter;
    _stscanf_s(pCurr, _T("%d"), &sqlLine.nRepeatTimes);
    //skip to request
    while(*pCurr != _T('\0') && (*pCurr != _T(' ') && *pCurr != _T('\t'))) {pCurr++;}
    while(*pCurr != _T('\0') && (*pCurr == _T(' ') || *pCurr == _T('\t'))) {pCurr++;}
    sqlLine.cpRequest = pCurr;
    if(_tcsstr(pCurr, _T("\n")) != NULL)
    {
      sqlLine.nReqSize  = sizeof(TCHAR) * (_tcsstr(pCurr, _T("\n")) - pCurr - 1);
    }
    else
    {
      sqlLine.nReqSize  = sizeof(TCHAR) * _tcsclen(pCurr);
    }

    dataFile[0].push_back(sqlLine);
    //skip to next
    pCurr += sqlLine.nReqSize / sizeof(TCHAR);
    while(*pCurr != _T('\0') && (*pCurr == _T('\r') || *pCurr == _T('\n'))) {pCurr++;}
    nCounter++;
  }

  //propagate
  for(nI = 1; nI < nNumThreads; nI++ )
  {
    dataFile[nI] = dataFile[0];
  }

  if (mysql_library_init(0, NULL, NULL)) 
  {
      _ftprintf(stderr, _T("Could not initialize MySQL library\n"));
      exit(1);
  }
  for(nI = 0; nI < nNumThreads; nI++ )
  {
    threadInfo[nI].hThread = CreateThread(NULL, 0, ThreadProc, &dataFile[nI], 0, &threadInfo[nI].dwThreadId); 
  }

  
  for(nI = 0; nI < nNumThreads; nI++)
  {
    WaitForSingleObject(threadInfo[nI].hThread, INFINITE);
  }

  for(nI = 0; nI < nNumThreads; nI++)
  {
    CloseHandle(threadInfo[nI].hThread);
  }

  //dump
  SQLPerfData merge;
  merge = dataFile[0];
  for(nI = 1; nI < nNumThreads; nI++)
  {
    for(SQLPerfData::iterator itSrc = dataFile[nI].begin(), itDst = merge.begin(); itSrc != dataFile[nI].end(); itSrc++, itDst++)
    {
      itDst->rMinTime = min(itDst->rMinTime, itSrc->rMinTime);
      itDst->rMaxTime = max(itDst->rMaxTime, itSrc->rMaxTime);
      itDst->rAveTime += itSrc->rAveTime;
    }
  }
  for(SQLPerfData::iterator itDst = merge.begin(); nNumThreads > 0 && itDst != merge.end(); itDst++)
  {
    itDst->rAveTime = itDst->rAveTime / nNumThreads;
  }

  DumpResults(merge, 0);

  mysql_library_end();

  delete threadInfo;
  //delete dataFile;
  GlobalFree(pFileBuff);

	return 0;
}

