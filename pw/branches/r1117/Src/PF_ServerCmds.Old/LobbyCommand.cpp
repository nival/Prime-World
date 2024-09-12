/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "../Server/src/TypeProxy.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <locale>
#include <stdlib.h>

#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LoggerStream.h"
#include "../System/SystemLog.h"
#include "../System/Basic.h"

#include "LobbyCommand.h"

REG_COMMAND_CPP(LobbyCommand);

LobbyCommand::LobbyCommand(): CommandFactory()
, m_requestCmd()
, m_replyCmd()
, m_nRequestSize(0)
, m_nReplySize(0)
, m_bRecievedFromClient(false)
, m_bRecievedFromServer(false)
, m_bReply(false)
, m_bExecutionSuccess(false)
, m_nCommandNumber(INVALID_COMMAND_NUMBER)
, m_nStatus(CS_NA)
{
  initCommonFields();
}

void LobbyCommand::initCommonFields()
{
  m_bRecievedFromClient = false;
  m_bRecievedFromServer = false;
  m_bReply = false;
  m_bExecutionSuccess = false;
  m_nCommandNumber = INVALID_COMMAND_NUMBER;
  m_nStatus = CS_NA;
}


void LobbyCommand::PrepareForSending()
{
  //serialize
  serialize();

  m_requestCmd.Seek(0, SEEKORIGIN_BEGIN);

  m_bRecievedFromClient = false;
  m_bRecievedFromServer = false;
  m_bReply              = false;
  m_bExecutionSuccess   = false; // Not yet executed
  m_nCommandNumber      = INVALID_COMMAND_NUMBER;

  //fill in command id if needed
  setCommandID();
  NI_VERIFY(getCommandID() != 0xFFFFFFFF, "Initialize type.", return;);
}

void LobbyCommand::serializeReply(void)
{
  MemoryStream &replyStream = GetReplyStream();
  UINT8        nFlagsByte = 0;
  unsigned int nCount = 0;

  //gather command flags into one byte
  if (m_bExecutionSuccess)
    nFlagsByte = nFlagsByte | (1 >> nCount);
  nCount++;
  if(m_bReply)
    nFlagsByte = nFlagsByte | (1 >> nCount);
  nCount++;
  if(m_bRecievedFromClient)
    nFlagsByte = nFlagsByte | (1 >> nCount);
  nCount++;
  if(m_bRecievedFromServer)
    nFlagsByte = nFlagsByte | (1 >> nCount);
  replyStream.Write(&nFlagsByte, sizeof(nFlagsByte));
}

void LobbyCommand::DeserializeReply(void)
{
  MemoryStream &replyStream = GetReplyStream();

  //preserve offset
  int nPosition = replyStream.GetPosition();
  replyStream.Seek(0, SEEKORIGIN_BEGIN);

  deserializeReply();

  replyStream.Seek(nPosition, SEEKORIGIN_BEGIN);
}

void LobbyCommand::deserializeReply(void)
{
  MemoryStream &replyStream = GetReplyStream();
  UINT8        nFlagsByte = 0;
  unsigned int nCount = 0;

  NI_ASSERT(getTotalReplySize() >= 1, "Strange command.");
  //do something only if at least one byte received
  if(replyStream.GetSize() >= 1)
  {
    replyStream.Read(&nFlagsByte, sizeof(nFlagsByte));
    m_bExecutionSuccess   = (nFlagsByte &  (1 >> (nCount++))) != 0;
    m_bReply              = (nFlagsByte &  (1 >> (nCount++))) != 0;
    m_bRecievedFromClient = (nFlagsByte &  (1 >> (nCount++))) != 0;
    m_bRecievedFromServer = (nFlagsByte &  (1 >> (nCount++))) != 0;
  }
}

#ifdef NI_PLATF_WIN
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

#ifdef NI_PLATF_LINUX
//utility functions
nstl::wstring LobbyCommand::Utf8ToUnc16(char const * cp)
{
  iconv_t cd;
  const char *charset = "UTF-8";
  cd = iconv_open("WCHAR_T", charset);
  if(cd == (iconv_t) -1)
  {
    if (errno == EINVAL)
      printf("conversion from '%s' to wchar_t not available", charset);
    else
      perror ("iconv_open");
    return nstl::wstring(L"");
  }
  size_t insize = strlen(cp);
  wchar_t *pBuff = new wchar_t[insize + 1];
  wchar_t *pBuff4iconv = pBuff;
  char    *pInBuff4Iconv = const_cast<char *>(cp);
  size_t outsize = insize * 2;
  size_t nconv = iconv(cd, &pInBuff4Iconv, &insize, (char **)&pBuff4iconv, &outsize);
  if (nconv == (size_t)-1)
  {
    perror ("conversion error");
  }
  nstl::wstring s(pBuff);
  delete pBuff;
  return s;
}

//utility functions
nstl::string LobbyCommand::Unc16ToUtf8(wchar_t const * cp)
{
  iconv_t cd;
  const char *charset = "UTF-8";
  cd = iconv_open(charset, "WCHAR_T");
  if(cd == (iconv_t) -1)
  {
    if (errno == EINVAL)
      printf("conversion to '%s' from wchar_t not available", charset);
    else
      perror ("iconv_open");
    return nstl::string("");
  }
  size_t insize = wcslen(cp);
  char *pBuff = new char[(insize + 1) * 6]; //max utf8 symbol is 6 bytes long
  char *pBuff4iconv = pBuff;
  wchar_t *pInBuff4Iconv = const_cast<wchar_t *>(cp);
  size_t outsize = insize * 6;
  size_t nconv = iconv(cd, (char **)&pInBuff4Iconv, &insize, &pBuff4iconv, &outsize);
  if (nconv == (size_t)-1)
  {
    perror ("conversion error");
  }
  nstl::string s(pBuff);
  delete pBuff;

  return s;
}

#elif defined(NI_PLATF_WIN)
//utility functions
nstl::wstring LobbyCommand::Utf8ToUnc16(char const * cp)
{
  int nError;
  int nSize;
  nSize = MultiByteToWideChar(CP_UTF8, 0, cp, -1, NULL, 0);
  if(nSize <= 0)
  {
    nError = GetLastError();
    return nstl::wstring(L"");
  }
  wchar_t *pUTC = (wchar_t *)malloc(sizeof(wchar_t) * nSize);
  MultiByteToWideChar(CP_UTF8, 0, cp, -1, pUTC, nSize);
  nstl::wstring s(pUTC);
  free(pUTC);
  return s;
}

nstl::string LobbyCommand::Unc16ToUtf8(wchar_t const * cp)
{
  int nError;
  int nSize;
  nSize = WideCharToMultiByte(CP_UTF8, 0, cp, -1, NULL, 0, NULL, NULL);
  if(nSize <= 0)
  {
    nError = GetLastError();
    return nstl::string("");
  }
  char *pUTF8 = (char *)malloc(nSize);
  WideCharToMultiByte(CP_UTF8, 0, cp, -1, pUTF8, nSize, NULL, NULL);
  nstl::string s(pUTF8);
  free(pUTF8);
  return s;
}


#else
//utility functions
nstl::wstring LobbyCommand::Utf8ToUnc16(char const * cp)
{
  const std::locale& original_locale(std::locale::global(std::locale("en_US.UTF-8")));
  wchar_t *pBuff = new wchar_t[strlen(cp) + 1];
  mbstowcs(pBuff, cp, strlen(cp));
  nstl::wstring s(pBuff);
  delete pBuff;
  std::locale::global(original_locale);
  return s;
}

//utility functions
nstl::string LobbyCommand::Unc16ToUtf8(wchar_t const * cp)
{
  const std::locale& original_locale(std::locale::global(std::locale("en_US.UTF-8")));
  char *pBuff = new char[(wcslen(cp) + 1) * 6]; //max utf8 symbol is 6 bytes long
  wcstombs(pBuff, cp, wcslen(cp));
  nstl::string s(pBuff);
  delete pBuff;
  std::locale::global(original_locale);
  return s;
}
#endif

void LobbyCommand::WriteStringToStream(Stream &str, nstl::wstring const &s)
{
  unsigned int nLen = s.length();
  unsigned char caLen[5]; //4 bytes max of length
  unsigned int nLenghtLen = 1; //length of length
  unsigned int nI;

  while(nLen - (caLen[nLenghtLen - 1] = (nLen & 0x7F)) != 0)
  {
    caLen[nLenghtLen - 1] = caLen[nLenghtLen - 1] | 0x80;
    nLenghtLen += 1;
    nLen       &= nLen & ~0x7F;
    nLen        = nLen >> 7;
  }
  //write length
  for(nI = 0; nI < nLenghtLen; nI++)
  {
    str.Write(&caLen[nI], 1);
  }
  //write data
  str.Write(s.c_str(), nLen * sizeof(*s.begin()));
}
nstl::wstring LobbyCommand::ReadStringFromStream(Stream &str)
{
  unsigned char c;
  unsigned int  nStrLen = 0;
  unsigned int  nShift  = 0;
  //read length
  do
  {
    str.Read(&c, 1);
    nStrLen += (c & 0x7F) << nShift;
    nShift  += 7;
    NI_ASSERT(nShift < 32, "64 bit command field?");
  } while ((c & 0x80) != 0);

  nstl::wstring s;
  s.reserve(nStrLen);
  s.resize(nStrLen, L'x');
  nstl::wstring::iterator it = s.begin();
  str.Read(&(*it), nStrLen * sizeof(*s.begin()));
  s.resize(nStrLen);

  return s;
}


#ifdef NI_PLATF_WIN
#pragma warning(pop)
#endif


