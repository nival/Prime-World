/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/
// ============================================================================
/**
 *  @file HTTPHandler.cpp: implementation of the HTTPHandler class.
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
#include "HTTPProtocol.h"

using namespace std;

void HTTPMsg::SetDefault10 ()
{
  m_Flags=0;
  m_ContentLength = ( unsigned long) -1L;
  m_BodyBytes = 0;
}

void HTTPMsg::SetDefault11 ()
{
  m_Flags=0;
  m_Flags |= HTTPMsg::FLG_KEEP_ALIVE;
  m_ContentLength = ( unsigned long) -1L;
  m_BodyBytes = 0;
}

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------

bool HTTPMsg::setContentLength (unsigned long Len)
{
  return isResponse()? setContentLength_i(Len) : false;
}
bool HTTPMsg::setChunked(bool Flg)
{
  return isResponse()? setChunked_i(Flg) : false;
}
bool HTTPMsg::setKeepAlive(bool Flg)
{
  return isResponse()? setKeepAlive_i(Flg) : false;
}

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
bool HTTPMsg::setContentLength_i (unsigned long Len)
{
  m_Flags |= FLG_CONTENT_LENGTH ;
  m_ContentLength = Len;
  return true ;
}
bool HTTPMsg::setChunked_i(bool Flg)
{
  if ( Flg )    m_Flags |=  FLG_CHUNKED_BODY;
  else          m_Flags &= ~FLG_CHUNKED_BODY;

  return true ;
}
bool HTTPMsg::setKeepAlive_i(bool Flg)
{
  if ( Flg )    m_Flags |=  FLG_KEEP_ALIVE;
  else          m_Flags &= ~FLG_KEEP_ALIVE;

  return true ;
}

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
HTTPHandler::HTTPHandler (HTTPProtocol  & protocol)
: m_Protocol ( protocol ),
  m_Request  ( protocol.getRequest () ),
  m_Response ( protocol.getResponse() )
{
  ;
}

//=============================End of file===================================

