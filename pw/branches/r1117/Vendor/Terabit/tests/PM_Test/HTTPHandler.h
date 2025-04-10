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

#ifndef _HTTPHANDLER_H
#define _HTTPHANDLER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HTTPUtil.h"

class HTTPProtocol;  

enum
  {
    KEY_CONTENT_LENGTH    = 1,
    KEY_TRANSFER_ENCODING = 2,
    KEY_CONNECTION        = 3
  };


class HTTPMsg 
{
    friend class HTTPProtocol;

public:
    enum MsgType 
      {
        MSG_REQUEST  = 0x0001,
        MSG_RESPONSE = 0x0002
      };
 
    enum HdrFlag
      {
        FLG_CONTENT_LENGTH = 0x00000001,
        FLG_CHUNKED_BODY   = 0x00000002,
        FLG_KEEP_ALIVE     = 0x00000004
      };

    bool  isRequest () const { return m_Type == MSG_REQUEST;  }
    bool  isResponse() const { return m_Type == MSG_RESPONSE; }

    int   getMajorVer () const { return m_MajorVer;}
    int   getMinorVer () const { return m_MinorVer;}
    unsigned long getFlags() const { return m_Flags;}
    bool  isContentLength () const { return (m_Flags & FLG_CONTENT_LENGTH)!=0; }
    bool  isChunked ()       const { return (m_Flags & FLG_CHUNKED_BODY)!=0; }
    bool  isKeepAlive()      const { return (m_Flags & FLG_KEEP_ALIVE)!=0;}

    unsigned long getContentLength() const 
    {
        return isContentLength ()? m_ContentLength : (unsigned long) -1L;
    }
    unsigned long getBodyBytesTransferred() const { return m_BodyBytes;}

    HString & getRLine    ()  { return m_RLine;}
    HMap &    getHeaders  ()  { return m_Headers;} 
    HString & getPartBody ()  { return m_Body;}
    HString & getFooter   ()  { return m_Footer;}
    

    bool setContentLength (unsigned long Len);
    bool setChunked  (bool FlgSet);
    bool setKeepAlive(bool FlgSet);
    
protected :

    virtual ~HTTPMsg ()  {;}

    HTTPMsg (MsgType eType)
        : m_Type     (eType),
          m_MajorVer (0),
          m_MinorVer (0),
          m_Flags    (0),
          m_ContentLength (0),
          m_BodyBytes (0),
          m_Headers (),
          m_ItrWk   (m_Headers)
    {;}

    void  SetDefault10 ();
    void  SetDefault11 ();

    bool setContentLength_i (unsigned long Len);
    bool setChunked_i  (bool Flg);
    bool setKeepAlive_i(bool Flg);

    MsgType   m_Type;
    HString   m_RLine;    // Request/Response Line    
    int       m_MajorVer;
    int       m_MinorVer;

    HMap      m_Headers;  // Collection of Headers
    HMapItr   m_ItrWk;    // Working Iterator
    HString   m_StrWk;    // Working Buffer

    HString   m_Body;     // Current Part of Body
    HString   m_Footer;   // Footer Line ( if Chunked )
    

    unsigned long m_Flags;
    unsigned long m_ContentLength;  // ContentLength;
    unsigned long m_BodyBytes;      // Progress
    
};

class HTTPRequest : public HTTPMsg
{
    friend class HTTPProtocol;
public :

    enum  ReqCode 
    {
      REQ_INVALID = 0x0000,
      REQ_GET     = 0x0001,
      REQ_HEAD    = 0x0002,
      REQ_POST    = 0x0003,
      REQ_PUT     = 0x0004,
      REQ_DELETE  = 0x0005,
      REQ_TRACE   = 0x0006,
      REQ_OPTIONS = 0x0007
    };

    ReqCode          getRequestCode () const { return m_Cmd;}
    const HString &  getURI() const { return m_StrURI;}

protected: 

    HTTPRequest () 
        : HTTPMsg (MSG_REQUEST),
          m_Cmd   (REQ_INVALID) 
    {;}

    virtual ~HTTPRequest ()  {;}

    ReqCode  m_Cmd;
    HString  m_StrCmd;
    HString  m_StrURI;
};


class HTTPResponse : public HTTPMsg
{
    friend class HTTPProtocol;
protected: 
    HTTPResponse ()  
        : HTTPMsg (MSG_RESPONSE)
    {;}
    virtual ~HTTPResponse ()  {;}
};


class HTTPHandler  
{
    friend class HTTPProtocol;
public:

    virtual bool onRequestReceived(const HString & /*ReqLine*/){return true;}

    virtual bool onHeaderReceived(const HString & /*Key*/,
                                  const HString & /*Val*/,
                                  int  /*KeyId*/,
                                  bool /*FlgProcessed*/ ) {return true;}

    virtual bool onEndOfHeaders()  { return true;}

    virtual bool onBodyPartReceived(const HString & /*StrBody*/) {return true;}

    virtual bool onEndOfBody()  { return true;}
    virtual bool onFooterReceived(const HString & /*StrFooter*/) {return true;}

    virtual bool processRequest ()=0;
    virtual bool prepareNextBodyPart (HString & /*StrBody*/ ){ return true;}
    virtual bool prepareFooter(HString & /*StrFooter*/)  { return true;}

    virtual ~HTTPHandler(){;}

protected: 
	 HTTPHandler(HTTPProtocol  & Protocol);

	  HTTPProtocol &  m_Protocol;
    HTTPRequest  &  m_Request;
    HTTPResponse &  m_Response;
};

class HTTPHandlerFactory
{
public:
  virtual HTTPHandler * create_handler (HTTPProtocol & protocol) = 0;
  virtual void destroy_handler (HTTPHandler * handler) = 0;
};



#endif // !defined(_HTTPHANDLER_H_)
//=====================End of File===========================================

