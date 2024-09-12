// CensorLib.cpp : Defines the exported functions for the DLL application.
//
#include "Censor.h"
#include "windows.h"
#include <boost/functional/hash.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SEARCH_SPLITED 1

#ifndef SEARCH_REPEATED 
#define SEARCH_REPEATED 1
#endif

namespace CensorFilter
{

bool issep(wchar_t ch)
{
#if 0
  return !iswalnum(ch);
#else
  if (ch == L' ' || ch == L'.' || ch == L'*' || ch == L',' || ch == '!' || 
    ch == L'_' || ch == 10 || ch == '(' || ch == ')' || ch == '[' || ch == '?' ||
    ch == L']' || ch == 9 || ch == '<' || ch == '>' || ch == '{' || ch == '}' || 
    ch == ':' || ch == ';' || ch == L'-' || ch == L'\\' || ch == L'/')
    return true;

  return false;
#endif
}


void toLower( std::wstring& str )
{
  boost::algorithm::to_lower(str);
}

bool Censor::CheckInWhiteList( const std::wstring& word )
{
  if (whiteList.find(word) != whiteList.end())
    return true;

  return false;
}


bool Censor::CheckInWhiteList( const wchar_t* pWordStart,  wchar_t* const pWordEnd )
{
  std::wstring word(std::wstring(pWordStart, pWordEnd));
  boost::algorithm::to_lower(word);

  return CheckInWhiteList(word);
}

void Censor::FilterContext::ResetSplitedWord()
{
  pSplitedWordStart = 0;
  pSplitedWordEnd = 0;
  splitedWordKey.clear();
}

void Censor::FilterContext::BuildSplitedWord( wchar_t* pWordStart, int wordLength )
{
  //join single characters to key
  if (!pSplitedWordStart)
  {
    pSplitedWordStart = pWordStart;
    splitedWordKey.clear();
  }

  splitedWordKey += std::wstring(pWordStart, wordLength);
  pSplitedWordEnd = pWordStart + wordLength;
}

void Censor::FilterContext::FilterLastSplitedWord(Censor* pCensor)
{
  int keyLen = splitedWordKey.length();
  toLower(splitedWordKey);
  if ( pCensor->CheckInWhiteList(splitedWordKey) )
    return;

  if ( pSplitedWordStart && keyLen > 2)
  {
    //scan 
    wchar_t* pKeyStart = &splitedWordKey[0];
    wchar_t* pKeyEnd = pKeyStart + keyLen;
    int maskLen = keyLen < (int)pCensor->maxKeyLength ? keyLen : pCensor->maxKeyLength;
    while(maskLen >= 3)
    {
      wchar_t* pWS = pKeyStart;
      while(pKeyEnd - pWS >= maskLen)
      {
        key = std::wstring(pWS, maskLen);
        if (pCensor->FindInDicts(key))
        {
          wmemset(pSplitedWordStart, L'*', pSplitedWordEnd - pSplitedWordStart);
          maskLen = 0;
          key.clear();
          break;
        }
        else
          pWS++;
      }
      maskLen--;
    }
  }

  pSplitedWordStart = 0;
}

void Censor::Filter(wchar_t* text)
{
  FilterText(text, &ctx);
}

void Censor::FilterThreadSafe( wchar_t* text )
{
  FilterContext* localCtx = new FilterContext();
  FilterText(text, localCtx);
  delete localCtx;
}

void Censor::FilterText( wchar_t* text, FilterContext* pContext )
{
  pContext->Reset();

  wchar_t* pS = text;
  wchar_t* pWordStart = pS;

  while(*pS)
  {
    while(*pWordStart && issep(*pWordStart)) pWordStart++;
    if (!*pWordStart)
      break;

    if (pWordStart > pS)
      pS = pWordStart + 1;

    if ( !issep(*pS) && *pS )
      ++pS;

    int len = pS - pWordStart;
    if ( ( issep(*pS) || *pS == 0) && len > 0 ) 
    {
      if (len > 2)
      {
        pContext->FilterLastSplitedWord(this);

        pContext->key.clear();
        wchar_t* pWordEnd = pS;
        while( (issep(*pWordEnd) || *pWordEnd == 0) && pWordEnd > pWordStart ) pWordEnd--;
        int keyLen = pWordEnd-pWordStart+1;
        pContext->key = std::wstring(pWordStart, pWordEnd+1);
        toLower(pContext->key);
        if (!CheckInWhiteList(pContext->key))
        {
          if (FindInDicts(pContext->key))
          {
            if (maskWholeWord)
              keyLen = pS - pWordStart;

            wmemset(pWordStart, L'*', keyLen);
            pContext->key.clear();
          }
          else
          {
            //scan 
            std::wstring word = pContext->key;
            int lenToEnd = word.length();
            int maskLen = lenToEnd < (int)maxKeyLength ? lenToEnd : maxKeyLength+1;

            while(maskLen > 3)
            {
              wchar_t* pScanPos = &word[0];
              wchar_t* pScanEnd = pScanPos + lenToEnd;
              while(*pScanPos && issep(*pScanPos)) pScanPos++;

              while(pScanEnd - pScanPos > maskLen-2)
              {
                pContext->key = std::wstring(pScanPos, maskLen-1);
                if (FindInDicts(pContext->key))
                {
                  if (maskWholeWord)
                  {
                    wmemset(pWordStart, L'*', lenToEnd);
                    maskLen = 0;
                    break;
                  }
                  else
                  {
                    wmemset(pWordStart + (pScanPos - &word[0]), L'*', pContext->key.length());
                    wmemset(pScanPos, L'*', pContext->key.length());
                  }

                  pScanPos += maskLen;
                  pContext->key.clear();
                }
                else
                {
                  pScanPos++;
                  while(*pScanPos && issep(*pScanPos)) pScanPos++;
                }
              }
              maskLen--;
            }
          }
        }


        pWordStart = pS;
      }
      else
      {
#if SEARCH_SPLITED
        pContext->BuildSplitedWord(pWordStart, len);
        pWordStart += len;
      }
#else
      }
      pWordStart = pS;
#endif
    } 

  }
  pContext->FilterLastSplitedWord(this);
}


bool Censor::RollUpString( const std::wstring& sourceStr, std::wstring& res )
{
  const wchar_t* pStr = sourceStr.c_str();
  wchar_t curChar;
  while( !issep(*pStr) && *pStr )
  {
    curChar = *pStr;
    res.push_back(curChar);
    pStr++;
    while( *pStr == curChar ) pStr++;
  }
  if (res.length() != sourceStr.length())
    return true;

  return false;
}

bool Censor::FindWordInDicts(const std::wstring& word)
{
  for( nstl::vector<TStringTable>::iterator dict = dicts.begin(); dict != dicts.end(); ++dict )
  {
    if (dict->find(word) != dict->end())
      return true;
  }

  return false;
}

bool Censor::FindInDicts( const std::wstring& key )
{
  if (key.empty()) return false;
  
  bool res = FindWordInDicts(key);

#ifdef SEARCH_REPEATED
  if (!res)
  {
    std::wstring resKey;
    if ( RollUpString(key, resKey) )
      return FindWordInDicts(resKey);
  }
#endif

  return res;
}

bool Censor::FindInDicts( const nstl::wstring& key )
{
  if (key.empty()) return false;

  std::wstring sKey(key.c_str());
  boost::algorithm::to_lower(sKey);

  return FindInDicts(sKey);
}

std::wstring trim(const std::wstring& str,
                 const std::wstring& whitespace = L" \t\n\r\0x13")
{
  const size_t strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::wstring::npos)
    return L""; // no content

  const size_t strEnd = str.find_last_not_of(whitespace);
  const size_t strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}
 
void Censor::AddDictionary( std::wstringstream& data, bool isWhiteList /*= false*/ )
{
  wchar_t word[8192];
  if (!isWhiteList)
    dicts.push_back(TStringTable());
  nstl::vector<TStringTable>::reference dict = isWhiteList ? whiteList : dicts.back();
  while( data.getline(word, 8192) )
  {
    AddWordToDict(word, dict, isWhiteList);
  }
}

int Censor::LoadDictionary( const wchar_t* fileName, bool isWhiteList /*= false*/ )
{
  TCHAR szBuffer[8192]= L"";
  TCHAR* szLine = NULL;
  FILE* f = NULL;
  errno_t er = _wfopen_s(&f, fileName, L"r, ccs=UTF-8");
  if (!f)
    return er;
 
  if (!isWhiteList)
    dicts.push_back(TStringTable());
  nstl::vector<TStringTable>::reference dict = isWhiteList ? whiteList : dicts.back();

  while ( !feof(f) )
  {
    szLine = fgetws(szBuffer, 8192, f);
    if (szBuffer == NULL || szLine == NULL)
      break;
    AddWordToDict(szLine, dict, isWhiteList);
  }
  
  fclose(f);

  return 0;
}

void Censor::AddWordToDict( const wchar_t* pWord, TStringTable& dict, bool isWhiteList )
{
  if (!pWord)
    return;

  std::wstring word = trim(pWord);
  if (word.empty())
    return;
  toLower(word);
  size_t length = word.length();
  
  if (!isWhiteList)
  {
    if (maxKeyLength < length)
     maxKeyLength = length;
  }
  dict.insert(word);
}

wchar_t NormailizeChar( wchar_t ch )
{
  if (ch == L'@' || ch == L'à')
    ch = L'a';
  else if (ch == L'ó')
    ch = L'y';
  else if (ch == L'è' || ch == L'1')
    ch = L'i';
  else if (ch == L'å' || ch == L'¸')
    ch = L'e';
  else if (ch == L'î')
    ch = L'o';
  else if (ch == L'ò')
    ch = L't';
  else if (ch == L'ì')
    ch = L'm';
  else if (ch == L'ð')
    ch = L'p';
  else if (ch == L'ï')
    ch = L'n';
  else if (ch == L'ä')
    ch = L'd';
  else if (ch == L'ê')
    ch = L'k';
  else if (ch == L'ñ')
    ch = L'c';
  else if (ch == L'4')
    ch = L'÷';
  else if (ch == L'õ')
    ch = L'x';
  else if (issep(ch) || ch == L'_' || ch == L'-')
    ch = 0;

  return ch;
}

}



