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
// HTTPProtocol.h: interface for the HTTPProtocol class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _HTTPProtocol_H_
#define _HTTPProtocol_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HTTPHandler.h"
#include "PConnection.h"

class HTTPProtocol : public PConnectionProtocol
{
public:

    typedef bool ( HTTPProtocol :: * PtrMethod ) ( HString & Str );

    class TabEl
    {
    public :
        const char *   m_pKey ;
        unsigned long  m_uVal ;
        PtrMethod      m_pFunc;
    };
    
    static TabEl  RequestTab [];
    static TabEl  HdrTab[];


    enum State 
    {
      ZERO_STATE     = 0x0000, 
      READ_REQUEST   = 0x0001,
      READ_HEADERS   = 0x0002,
      READ_BODY	     = 0x0003,
		  READ_BODY_PART = 0x0004,
		  READ_CHUNK_LEN = 0x0005,
		  READ_CHUNK	   = 0x0006,
		  READ_CHUNK_TAIL= 0x0007,
		  READ_FOOTER    = 0x0008,
      READ_OK        = 0x000E,
      READ_FAILED    = 0x000F,
      SEND_RESPONSE  = 0x0011,
		  SEND_HEADERS   = 0x0012,
		  SEND_BODY	     = 0x0013,
		  SEND_BODY_PART = 0x0014,
		  SEND_CHUNK	   = 0x0015,
		  SEND_FOOTER    = 0x0016,
      SEND_OK        = 0x001E,
      SEND_FAILED    = 0x001F,
		  FIN_STATE	     = 0x00FF
    };

   
	HTTPProtocol(PConnection * session, HTTPHandlerFactory & http_factory);
	virtual ~HTTPProtocol();


  State  getState ()      const { return m_State;}
  State  getErrorState () const { return m_ErrState;}

  HTTPReader   & getReader   () { return m_Reader ;}
  HTTPWriter   & getWriter   () { return m_Writer ;}
  HTTPRequest  & getRequest  () { return m_Request;}
  HTTPResponse & getResponse () { return m_Response;}
    
	

protected:
    virtual void on_start ();

    virtual void on_read_finished (ACE_Message_Block & mb,
                                 size_t bytes_transferred,
                                 int  error);

    virtual void on_write_finished (ACE_Message_Block & mb,
                                 size_t bytes_transferred,
                                 int  error);

    bool   ServerAutomat () ;

  	bool   ReadRequest();
    void   ParseRequest ();
    void   SetDefault10 ();
    void   SetDefault11 ();

    bool   ParseGET ( HString & Str);
    bool   ParsePOST( HString & Str);

	  bool   ReadHeaders();
    void   ParseHeader ();
    bool   ParseProtocolHeader    ( HString & Key, HString & Val, int & KeyId );
    bool   ParseH_ContentLength   ( HString & Str);
    bool   ParseH_TransferEncoding( HString & Str);
    bool   ParseH_Connection      ( HString & Str);


	  bool  ReadBody();
    bool  ReadBodyPart();

    bool  ReadChunkLen ();
    bool  ReadChunk ();
    bool  ReadChunkTail();
    
  	bool  ReadFooter();

  	bool  ReadOk();
  	bool  ReadFailed();
	
	  bool  SendResponse();
	  bool  SendHeaders();
    bool  SendBody();
    bool  SendBodyPart();
    bool  SendChunk();
    bool  SendFooter();
  	bool  SendOk();
  	bool  SendFailed();

  	bool  SetReadOk ();
  	bool  SetSendOk ();
  	bool  SetReadFailed ();
  	bool  SetSendFailed ();
    
    

    TabEl *  FindVerb ( const char * pVerb, TabEl * pTab );

    State  m_State;
    State  m_ErrState;
    State  m_NextState;
    bool   m_FlgSuccess;

    HTTPHandlerFactory & m_factory;
    HTTPHandler * m_pHandler;

    HTTPReader    m_Reader;
    HTTPWriter    m_Writer;

    HTTPRequest   m_Request;
    HTTPResponse  m_Response;
};
	


#endif // !defined(_HTTPProtocol_H_)
//=====================End of File===========================================
