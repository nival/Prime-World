// CensorTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "System/systemStdAfx.h"
//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"
#include <string>
#include <iostream>
#include <clocale>
#include <time.h>
#include <math.h>
#include <tchar.h>
#include <algorithm>
#include <System/sleep.h>


#define STATIC_DLL_LOAD

#ifdef STATIC_DLL_LOAD
#include "CensorDll.h"
#endif


#define NI_DUMP_LEAKS_TO_FILE
#define CHECK_MEMORY_LEAKS
#define MAX_LINES_COUNT 0

#define ASYNC_FILTER

int getNumStarsInLine( const nstl::wstring& line)
{
  return std::count(line.begin(), line.end(), '*');
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifndef STATIC_DLL_LOAD
  SetLastError(0);
  HMODULE hCensorLib = LoadLibrary(L"CensorDll.dll");
  if (!hCensorLib) 
  {
    std::cout << "could not load the dynamic library: " << GetLastError() << std::endl;
    return EXIT_FAILURE;
  }
#else
//  CensorFilter::LoadDictionary(L"..\\..\\..\\..\\Censor\\Dicts\\custom_whitelist.txt", true);
  /*CensorFilter::LoadDictionary(L"..\\Dicts\\Blocked_Chat_list.txt");
  CensorFilter::LoadDictionary(L"..\\Dicts\\Blocked_Chat_list_eng.txt");
  CensorFilter::LoadDictionary(L"..\\Dicts\\Blocked_Chat_list_TR.txt");
  CensorFilter::LoadDictionary(L"..\\Dicts\\Blocked_Chat_list_FR.txt");
  CensorFilter::LoadDictionary(L"..\\Dicts\\Blocked_Chat_list_DE.txt");
  CensorFilter::LoadDictionary(L"..\\Dicts\\WhiteList_RU.txt", true);
  CensorFilter::LoadDictionary(L"..\\Dicts\\WhiteList_eng.txt", true);
*/
#endif

  nstl::vector< nstl::wstring > messages;
  nstl::vector< nstl::wstring >* pMessages = &messages;

  TCHAR szBuffer[8192]= _T("");
  TCHAR* szLine = NULL;
  FILE* f = NULL;
  errno_t er = _wfopen_s(&f, L"..\\TestData\\org.txt", _T("r, ccs=UTF-8"));
  if (!f)
  {
    std::cout << "could not open file: " << "TestData\\org.txt" << "\nError: "<< er << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Reading test data file... Please wait." << std::endl;
  int i = 0;
  int startFrom = 0;
  while ( !feof(f) )
  {
    szLine = fgetws(szBuffer, 8192, f);
    if (startFrom > 0)
    {
      startFrom--;
      continue;
    }

    if (szBuffer == NULL || szLine == NULL)
      break;
    pMessages->push_back( szLine );

    i++;
    if (MAX_LINES_COUNT > 0 && i > MAX_LINES_COUNT)
      break;
  }

  fclose(f);

  er = _wfopen_s(&f, L"..\\TestData\\org_ref.txt", _T("w, ccs=UNICODE"));
  for(int i=0; i<pMessages->size();i++)
    fputws((*pMessages)[i].c_str(),f);
  fclose(f);
  std::cout << "Done!" << std::endl;
  
  //Нормальное отображение текста на русском
  std::setlocale( LC_ALL, "" );

  //Настраиваем boost::filesystem на кодировку utf8
  //std::locale utf8_locale(std::locale(), new boost::filesystem::detail::utf8_codecvt_facet() );
  //boost::filesystem::path::imbue(utf8_locale);

  //std::wcout.imbue(std::locale("rus_rus.866"));
//  std::wcout << "src: " << text[rand() % NUM_MESSAGES] << std::endl;

  
  typedef void (*FilterFunctionType)(wchar_t*);
  typedef int (*AsyncFilterFunctionType)(const wchar_t*);
  typedef int (*GetFilteredMessageType)(int&, wchar_t*, size_t);

  FilterFunctionType FilterText;
  AsyncFilterFunctionType FilterTextAsync;
  GetFilteredMessageType GetFilteredText;

#ifndef STATIC_DLL_LOAD
  FilterText = (FilterFunctionType)GetProcAddress(hCensorLib, "Filter");
  FilterTextAsync = (AsyncFilterFunctionType)GetProcAddress(hCensorLib, "FilterAsync");
  GetFilteredText = (GetFilteredMessageType)GetProcAddress(hCensorLib, "GetFilteredAsync");

  if (!FilterText || !FilterTextAsync)
  {
    std::cout << "could not find filter function: " << GetLastError() << std::endl;
    return EXIT_FAILURE;
  }
#else
  FilterText = &CensorFilter::Filter;
  FilterTextAsync = &CensorFilter::FilterAsync;
  GetFilteredText = &CensorFilter::GetFilteredAsync;
#endif

  std::cout << "Filter messages..." << std::endl;
  
  nstl::map< int, nstl::wstring > filteredAsyncResult;
  nstl::vector<int> messagesIds;
  
  clock_t begin, end;
  double time_spent;

  begin = clock();
  
  try
  {
  size_t msgsCount = pMessages->size();
  for(size_t i=0; i < msgsCount;i++)
  {
#ifndef ASYNC_FILTER
    FilterText(&(*pMessages)[i][0]);
   // std::cout << "\r" << (float)(i* 100.0f/msgsCount);
  }
#else
    messagesIds.push_back(FilterTextAsync((*pMessages)[i].c_str()));
  }


  nstl::wstring text;
  while( pMessages->size() > 0/*!= filteredAsyncResult.size() */)
  {
    int id = 0;
    wchar_t msg[8192];
    if ( GetFilteredText(id, msg, 8192) )
    {
      nstl::wstring res(msg);
      pMessages->pop_back();
      filteredAsyncResult.insert( nstl::make_pair(id, res) );
     // std::cout << "\r" << (float)(filteredAsyncResult.size() * 100.0f/msgsCount);
    }
    /*else
      nival::sleep(10);*/
  }
#endif
  }
  catch(...)
  {

  }
  
  end = clock();

#ifdef ASYNC_FILTER
  pMessages->clear();
  for( nstl::vector<int>::iterator it = messagesIds.begin(); it != messagesIds.end(); ++it)\
  {
    nstl::map< int, nstl::wstring >::iterator res = filteredAsyncResult.find(*it); 
    NI_ASSERT( res != filteredAsyncResult.end(), "bad async filter results" );
    pMessages->push_back(res->second);
  }
#endif

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  
  std::wcout << "Elapsed: " << time_spent <<" seconds\n " << pMessages->size() << " has been processed" <<  std::endl;
  std::wcout << "Started from line: " << startFrom << std::endl;
  

  nstl::set<nstl::wstring> uniq_messages;
  int nStarsNew = 0;

  er = _wfopen_s(&f, L"..\\TestData\\filtered.txt", _T("w, ccs=UNICODE"));
  for(int i=0; i<pMessages->size();i++)
  {
    fputws((*pMessages)[i].c_str(),f);
    uniq_messages.insert((*pMessages)[i]);
  }

  fclose(f);

  //

  for(nstl::set<nstl::wstring>::iterator it = uniq_messages.begin(); it != uniq_messages.end(); ++it)
    nStarsNew += getNumStarsInLine(*it);

  int nStarsOld = 0;
  uniq_messages.clear();
  i = 0;
  er = _wfopen_s(&f, L"..\\TestData\\filter_old.txt", _T("r, ccs=UNICODE"));
  while ( !feof(f) )
  {
    szLine = fgetws(szBuffer, 8192, f);
    if (startFrom > 0)
    {
      startFrom--;
      continue;
    }

    if (szBuffer == NULL || szLine == NULL)
      break;

    nstl::wstring str (szLine);
    uniq_messages.insert(str);
    
    i++;
    if (i == pMessages->size())
      break;

    if (MAX_LINES_COUNT > 0 && i > MAX_LINES_COUNT)
      break;
  }
  fclose(f);

  for(nstl::set<nstl::wstring>::iterator it = uniq_messages.begin(); it != uniq_messages.end(); ++it)
    nStarsOld += getNumStarsInLine(*it);

  std::wcout << "Hit to old filter: " << (float)nStarsNew/(float)nStarsOld*100.0f << std::endl;
  std::wcout << "old: " << nStarsOld << " new: " << nStarsNew << std::endl;
  
#ifndef STATIC_DLL_LOAD
  FreeLibrary(hCensorLib);
#endif  

	return 0;
}

