/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "TypeProxy.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ClientThread.h"
#include "../../System/basic.h"
#include "../../System/nlist.h"
#include "../../System/nstring.h"
#include "../../System/nvector.h"
using namespace nstl;
#include "../../System/StrProc.h"
#include "../../System/ScopedArray.h"
#include "ServerApp.h"
#include "ListenerThread.h"
#include "DatabaseThread.h"
#include "LCAuthenticateSimple.h"
#include "LCDisconnect.h"
#include "ServerLogic.h"
#include "SQLStream.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SQLStream::SQLFieldType getType(MYSQL_FIELD &field)
{
  if(IS_BLOB(field.flags))
  {
    return SQLStream::FT_BLOB;
  }

  if(field.type == MYSQL_TYPE_BIT && field.length == 1)
  {
    return SQLStream::FT_BOOL ;
  }
  if(IS_NUM_FIELD(&field))
  {
    if(UNSIGNED_FLAG & field.flags)
    {
      if(field.type == MYSQL_TYPE_TINY && field.length == 1)
        return SQLStream::FT_BYTE;
      if(field.type == MYSQL_TYPE_SHORT && field.length == 2)
        return SQLStream::FT_USHORT;
      if(field.type == MYSQL_TYPE_LONG  && field.length == 4)
        return SQLStream::FT_UINT32;
      if(field.type == MYSQL_TYPE_LONG  && field.length > 4)
        return SQLStream::FT_UINT64;
      if(field.type == MYSQL_TYPE_LONGLONG  && field.length > 4)
        return SQLStream::FT_UINT64;
    }
    else
    {
      if(field.type == MYSQL_TYPE_TINY && field.length == 1)
        return SQLStream::FT_CHAR;
      if(field.type == MYSQL_TYPE_SHORT && field.length == 2)
        return SQLStream::FT_SHORT;
      if(field.type == MYSQL_TYPE_LONG  && field.length == 4)
        return SQLStream::FT_INT32;
      if(field.type == MYSQL_TYPE_LONG  && field.length > 4)
        return SQLStream::FT_INT64;
      if(field.type == MYSQL_TYPE_LONGLONG  && field.length > 4)
        return SQLStream::FT_INT64;
    }
    if(field.type == MYSQL_TYPE_FLOAT && field.length >= 8)
      return SQLStream::FT_DOUBLE;
    if(field.type == MYSQL_TYPE_FLOAT && field.length >= 4)
      return SQLStream::FT_FLOAT;
    if(field.type == MYSQL_TYPE_DOUBLE && field.length >= 8)
      return SQLStream::FT_DOUBLE;
  }
  if(field.type == MYSQL_TYPE_STRING || field.type == MYSQL_TYPE_VAR_STRING)
  {
    return SQLStream::FT_WSTRING;
  }
  if(field.type == MYSQL_TYPE_VARCHAR)
  {
    if(field.length == 1)
      return SQLStream::FT_CHAR;
    return SQLStream::FT_WSTRING;
  }
  NI_ALWAYS_ASSERT("Learn to handle this type");
  return SQLStream::FT_NA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DatabaseThread::~DatabaseThread()
{
  WaitForGraciousTerminate();

  ServerLogic::Term();
  
  mysql_library_end();
}

DatabaseThread::DatabaseThread(Params &pars): m_pars(pars), m_pConnection(NULL), m_bWantExit(false)
{
  if(mysql_library_init(0, NULL, NULL))
  {
    fprintf(stderr, "Could not initialize MySQL library\n");
    exit(1);
  }
  ServerLogic::Init();
}


ClientThread * DatabaseThread::GetClientById(int nAccId)
{
  ClientThread *const pClientLast = ServerApp::Get()->m_recieveClients.last();
  for (ClientThread *pClient = ServerApp::Get()->m_recieveClients.first(); pClient != pClientLast;)
  {
    if(pClient->GetAccoundId() == nAccId)
    {
      return pClient;
    }
    //next
    pClient = ClientThread::Ring::next(pClient);
  }
  return NULL;
}

int  DatabaseThread::performDBRequest(wchar_t const *request, SQLStream *reply)
{
  nstl::string sUTF8 = LobbyCommand::Unc16ToUtf8(request);
  return performDBRequest(sUTF8.c_str(), sUTF8.length(), reply);
}

int  DatabaseThread::performDBRequest(char const *pUTF8Request, unsigned int nRequestSize, SQLStream *reply)
{
  if(nRequestSize == 0)
  {
    return -1;
  }
  int nError;
  int nResult = 0;

  //call DB
  nError = mysql_real_query(m_pConnection, pUTF8Request, nRequestSize);
  NI_SERVER_LOG_L5(("DB request send: %s\n", pUTF8Request));
  if(nError != 0)
  {
    fprintf(stderr, "Failed to execute: %s. Error: %s\n", pUTF8Request, mysql_error(m_pConnection));
  }

  do
  {
    if(reply != NULL) //we need DB reply
    {
      //make sure about stream we got
      NI_ASSERT(nResult > 0 || reply->GetPosition() == 0, "Strange stream");
      NI_ASSERT(nResult > 0 || reply->GetSize()     == 0, "Strange stream");

      MYSQL_RES *pRes = mysql_store_result(m_pConnection);
      if(pRes != NULL)  // there are rows
      {
        unsigned int nNumColumns      = mysql_num_fields(pRes);
        unsigned int nNumRows         = mysql_num_rows(pRes);
        MYSQL_FIELD *pFields          = mysql_fetch_fields(pRes);
        // retrieve rows, then call mysql_free_result(result)

        unsigned int  nRow, nCol;
        MYSQL_ROW     pRow;
        unsigned long *npLengths;
        
        nRow = 0;
        //row numbers mark
        reply->StoreSQLField(nNumRows);
        //column numbers mark
        reply->StoreSQLField(nNumColumns);
        while(NULL != (pRow = mysql_fetch_row(pRes))) //for each row
        {
          //get valid fields in result
          npLengths = mysql_fetch_lengths(pRes);
          for(nCol = 0; nCol < nNumColumns; nCol ++)
          {
            unsigned int nLen = npLengths[nCol];
            if(nLen == 0)
            {
              reply->StoreSQLField(SQLStream::FT_NULL_VALUE, (void *)NULL, 0);
            }                                     
            else
            {
              const char *pValue = pRow[nCol];

              reply->StoreSQLField(getType(pFields[nCol]), pValue, nLen);
              /*
              if(pFields[nCol].type == MYSQL_TYPE_TINY_BLOB || pFields[nCol].type == MYSQL_TYPE_MEDIUM_BLOB || 
                 pFields[nCol].type == MYSQL_TYPE_LONG_BLOB || pFields[nCol].type == MYSQL_TYPE_BLOB)
              {
                //simply write
                reply->Write(&nLen, sizeof(nLen));
                reply->Write(pValue, nLen);
              }
              else
              {
                nstl::wstring s = LobbyCommand::Utf8ToUnc16(pValue);
                //write
                int nStrLen = s.length() * sizeof(*s.begin());
                reply->Write(&nStrLen, sizeof(nStrLen));
                reply->Write(s.c_str(), nStrLen);
              } */
            }
          }
          nRow ++;
        }
        mysql_free_result(pRes);
      }
      else  // mysql_store_result() returned nothing; should it have?
      {
        if(mysql_field_count(m_pConnection) == 0)
        {
          // query does not return data (it was not a SELECT)
          int nNumRows = mysql_affected_rows(m_pConnection);
          NI_USE_PARAM(nNumRows);
        }
        else // mysql_store_result() should have returned data
        {
          fprintf(stderr, "Error: %s\n", mysql_error(m_pConnection));
        }
      }
    } //if(reply != NULL)
    nResult++;
  } while (0 == mysql_next_result(m_pConnection));

  //Prepare stream for further processing
  if(reply != NULL)
  {
    reply->Seek(0, SEEKORIGIN_BEGIN);
  }

  return nError;
}

void DatabaseThread::ThreadMain()
{
  m_pConnection = mysql_init(NULL);
  NI_VERIFY(m_pConnection != NULL, "Unable to init mySQL", return;);

  //create connection
  if(!mysql_real_connect(m_pConnection, m_pars.m_sDBServerAddr.c_str(), m_pars.m_sDBServerLogin.c_str(), m_pars.m_sDBServerPassw.c_str(), "primalforces", m_pars.m_nDBServerPort, NULL, CLIENT_COMPRESS | CLIENT_MULTI_STATEMENTS))
  {
    fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(m_pConnection));
    return;
  }

  if(!mysql_set_character_set(m_pConnection, "utf8"))
  {
    printf("New client character set: %s\n", mysql_character_set_name(m_pConnection));
  }

  ServerLogic::Get()->loadSQLLogic(m_pars.m_sSQLLogicPath.c_str());

  while(true)
  {
    //logic!
    ServerLogic::Get()->logicPerform();

    //now iterate with clients
    ClientThread *const pClientLast = ServerApp::Get()->m_recieveClients.last();
    for (ClientThread *pClient = ServerApp::Get()->m_recieveClients.first(); pClient != pClientLast;)
    {
      //skip disconnected client
      if(!pClient->IsConnected())
      {
        //next
        pClient = ClientThread::Ring::next(pClient);
        continue;
      }
      CommandHolder pHolder; 
      if((pHolder = pClient->GetNextCommand()) != NULL)
      {
        //send command to DB
        int nError;
        nError = performDBRequest(pHolder->serializeSQL(), &pHolder->GetSQLStream());

        bool bNeedSend = true;
        if(nError == 0) //zero means success
        {
          pHolder->SetExecutionSuccess();

          pHolder->deserializeSQL(pHolder->GetSQLStream());

          //perform some logic: Authentication is the first one
          bNeedSend = ServerLogic::Get()->onCommandRecieved(pClient, pHolder);
        }

        // and will add it for client
        if(bNeedSend)
        {
          pClient->Send(pHolder);
        }
      } //if(!r->m_recievedList.IsEmpty())

      //next
      pClient = ClientThread::Ring::next(pClient);
    } //end client cycle

    //do some logic requests
    if(m_bWantExit)
    {
      break;
    }
  } //end cycle eternal


  ServerLogic::Get()->logicKickAllClients();

  mysql_close(m_pConnection);
  m_pConnection = NULL;
}

void DatabaseThread::WaitForGraciousTerminate()
{
  m_bWantExit = true;
  while(m_pConnection != NULL)
  {
#ifdef NI_PLATF_LINUX
    sched_yield();
#else
    Sleep(1);
#endif
  }
}


/*   extracode

enum_field_types nType = pFields[nCol].type;

switch (nType)
{
case MYSQL_TYPE_DECIMAL:
case MYSQL_TYPE_TINY:
case MYSQL_TYPE_SHORT:
case MYSQL_TYPE_LONG:
{
int nRet;
convertValue(pValue, nType, nRet);
pHolder->GetReplyStream().Write(&nRet, sizeof(nRet));
break;
}
case MYSQL_TYPE_DOUBLE:
case MYSQL_TYPE_FLOAT:
{
int nRet;
convertValue(pValue, nType, nRet);
pHolder->GetReplyStream().Write(&nRet, sizeof(nRet));
break;
}
default:
{
NI_ALWAYS_ASSERT();
}
}
*/

