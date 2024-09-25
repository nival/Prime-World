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
 *  @file  HTTPProtocol.cpp: implementation of the HTTPProtocol class.
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
//
//////////////////////////////////////////////////////////////////////

#include "HTTPProtocol.h"
#include "ace/OS_NS_strings.h"

using namespace std;

HTTPProtocol::TabEl HTTPProtocol::RequestTab []=
{
    { "GET"    , HTTPRequest::REQ_GET    , & HTTPProtocol::ParseGET },
    { "HEAD"   , HTTPRequest::REQ_HEAD   , & HTTPProtocol::ParseGET },
    { "POST"   , HTTPRequest::REQ_POST   , & HTTPProtocol::ParsePOST},
    { "PUT"    , HTTPRequest::REQ_PUT    , NULL },
    { "DELETE" , HTTPRequest::REQ_DELETE , NULL },
    { "TRACE"  , HTTPRequest::REQ_TRACE  , NULL },
    { "OPTIONS", HTTPRequest::REQ_OPTIONS, NULL },
    { NULL , 0 , NULL }
};

HTTPProtocol::TabEl HTTPProtocol::HdrTab []=
{
    { "CONTENT-LENGTH"    , KEY_CONTENT_LENGTH   , & HTTPProtocol::ParseH_ContentLength },
    { "TRANSFER-ENCODING" , KEY_TRANSFER_ENCODING, & HTTPProtocol::ParseH_TransferEncoding},
    { "CONNECTION"        , KEY_CONNECTION       , & HTTPProtocol::ParseH_Connection},
    { NULL , 0 , NULL }
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HTTPProtocol::HTTPProtocol(PConnection * session, 
                           HTTPHandlerFactory & http_factory)
:	PConnectionProtocol (session),
	m_State     (ZERO_STATE),
	m_ErrState  (ZERO_STATE),
	m_NextState (ZERO_STATE),
	m_FlgSuccess(false),
  m_factory   (http_factory),
  m_pHandler  (0),
  m_Reader    (session),
  m_Writer    (session)
{
	;
}

HTTPProtocol::~HTTPProtocol()
{
  this->m_factory.destroy_handler (m_pHandler); 
}

//-------------------------------------------------------------------
//  This method is called only once to initialize state
//  and start the first I/O
//-------------------------------------------------------------------

void
HTTPProtocol::on_start ()
{
	if (m_State != ZERO_STATE)
    return;
	
  // Create HTTP Functional Handler

  
  m_pHandler = m_factory.create_handler (*this);
  
  if (!m_pHandler)
    return;

  if (!m_Writer.init ())
    return;

  // Start Parser - HTTPReader
  if (!m_Reader.init ())
    return;
    
  m_State = READ_REQUEST;   // Initial state 
}

//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------
void
HTTPProtocol::on_read_finished (ACE_Message_Block & mb,
                                size_t bytes_transferred,
                                int  error)
{
  this->m_Reader.on_read_finished (mb, 
                                   bytes_transferred,
                                   error);

  mb.release ();

  this->ServerAutomat ();
}

void
HTTPProtocol::on_write_finished (ACE_Message_Block & mb,
                                size_t bytes_transferred,
                                int  error)
{
  bool rc = this->m_Writer.on_write_finished (mb,
                                              bytes_transferred,
                                              error);

  if (!rc)
    SetSendFailed ();
  else
    m_State = m_NextState ;

  mb.release ();

  this->ServerAutomat ();
}

//-------------------------------------------------------------------
//  State Machine for HTTP Protocol
//-------------------------------------------------------------------

bool HTTPProtocol::ServerAutomat ()
{

	bool FlgAlive = false;

	do 
	{
        //  All StateMachine Handlers ReadXXX, SendXXX
        //  have to return the same codes:
        //  true  - continue StateMachine job
        //  false - StateMachine should return control 
        //          and wait for I/O Completion

		switch (m_State)
		{
        case READ_REQUEST   : FlgAlive = ReadRequest();      break;  
        case READ_HEADERS   : FlgAlive = ReadHeaders();      break;
        case READ_BODY      : FlgAlive = ReadBody ();        break;
        case READ_BODY_PART : FlgAlive = ReadBodyPart();     break;
        case READ_CHUNK_LEN : FlgAlive = ReadChunkLen();     break;
        case READ_CHUNK     : FlgAlive = ReadChunk();        break;
        case READ_CHUNK_TAIL: FlgAlive = ReadChunkTail();    break;
        case READ_FOOTER    : FlgAlive = ReadFooter();       break;
        case READ_OK        : FlgAlive = ReadOk ();          break;  
        case READ_FAILED    : FlgAlive = ReadFailed();       break;  
        case SEND_RESPONSE  : FlgAlive = SendResponse();     break; 	
        case SEND_HEADERS   : FlgAlive = SendHeaders();      break;
        case SEND_BODY      : FlgAlive = SendBody ();        break; 	
        case SEND_BODY_PART : FlgAlive = SendBodyPart();     break; 	
        case SEND_CHUNK     : FlgAlive = SendChunk();        break; 	
        case SEND_FOOTER    : FlgAlive = SendFooter();       break; 	
        case SEND_OK        : FlgAlive = SendOk ();          break;     
        case SEND_FAILED    : FlgAlive = SendFailed();       break; 

        case FIN_STATE      : FlgAlive = false ;	         break;    

        default             : ACE_ASSERT (0);
                              FlgAlive = false ;	         break;    

        }
    }
	while ( FlgAlive ) ;

	return ( m_State != FIN_STATE ) ;
}

//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------

HTTPProtocol::TabEl *
HTTPProtocol::FindVerb ( const char * pVerb, TabEl * pTab )
{
    if ( ! pVerb || ! pTab )
    {
        return NULL ;
    }

    for ( ; pTab->m_pKey != NULL ;  pTab ++ )
    {
        if ( ::strcmp ( pVerb, pTab->m_pKey ) == 0 )
        {
            return pTab ;
        }
    }

    return NULL;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
bool HTTPProtocol::ReadRequest ()
{
    HTTPReader::Status Rc = m_Reader.getLine ( m_Request.getRLine () );

    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    default:                    return SetReadFailed ();
    }

    ParseRequest ();

    m_Request.m_StrWk.erase ();

    if ( m_State == READ_FAILED )
    {
        return true;
    }

    if ( ! m_pHandler->onRequestReceived ( m_Request.getRLine ()) )
    {
        return SetReadFailed ();
    }

    m_State = READ_HEADERS;
    return true ;
}

void HTTPProtocol::ParseRequest ()
{
    m_Request.m_StrCmd.erase ();
    m_Request.m_StrURI.erase ();
    m_Request.m_Cmd = HTTPRequest::REQ_INVALID;

    if ( ! m_Request.m_RLine.size () )
    {
        SetReadFailed ();
        return;
    }

    //  Extract Command

    size_t Pos1   = 0;
    size_t Pos2   = m_Request.m_RLine.find_first_of ( " \t" );

    if ( Pos2 == HString::npos || Pos2 == 0)
    {
        SetReadFailed ();
        return;
    }

    m_Request.m_StrCmd.append ( m_Request.m_RLine, Pos1, Pos2-Pos1 );
    HTTPUtil::ToUpper ( m_Request.m_StrCmd );

    TabEl * pEl = FindVerb ( m_Request.m_StrCmd.c_str (),
                             RequestTab );
    if ( ! pEl )
    {
        SetReadFailed ();
        return ;
    }

    m_Request.m_Cmd = static_cast<HTTPRequest::ReqCode> (pEl->m_uVal) ;

    //  Extract URI

    Pos1 = m_Request.m_RLine.find_first_not_of ( " \t", Pos2 );

    if ( Pos1 == HString::npos )
    {
        SetReadFailed ();
        return;
    }

    Pos2 = m_Request.m_RLine.find_first_of ( " \t", Pos1 );

    if ( Pos2 == HString::npos )
    {
        SetReadFailed ();
        return;
    }

    m_Request.m_StrURI.append ( m_Request.m_RLine, Pos1, Pos2-Pos1 );

    // Extact HTTP version

    Pos1 = m_Request.m_RLine.find_first_not_of ( " \t", Pos2 );

    if ( Pos1 == HString::npos )
    {
        SetReadFailed ();
        return;
    }

    int n = ::sscanf ( m_Request.m_RLine.c_str() + Pos1 ,
                       "HTTP/%d.%d",
                       & m_Request.m_MajorVer,
                       & m_Request.m_MinorVer);

    if ( n != 2 )
    {
        SetReadFailed ();
        return;
    }

    switch ( m_Request.m_MajorVer )
    {
    case 0: SetReadFailed (); 
            return;

    case 1: if ( m_Request.m_MinorVer == 0 )
            {
                m_Request.SetDefault10 ();
                break;
            }

    default: m_Request.SetDefault11 ();
    }

    //  Call Command Handler

    if ( ! pEl->m_pFunc )  // == NULL )
    {
        SetReadFailed ();
        return ;
    }

    (this->* ( pEl->m_pFunc )) ( m_Request.m_StrCmd );

    return ;
}

bool HTTPProtocol::ParseGET (HString &  /*Str*/ )
{
    return true ;
}

bool HTTPProtocol::ParsePOST (HString & /*Str*/ )
{
    return true ;
}


    
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
bool HTTPProtocol::ReadHeaders ()
{
    HString StrHdr;

    HTTPReader::Status Rc = m_Reader.getLine ( StrHdr );
  
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  return SetReadOk ();
    default :                   return SetReadFailed ();
    }

    if ( StrHdr.size () == 0 )       // End of Headers
    {
        m_NextState = READ_BODY;     // Process the previous Header
        ParseHeader();               // and go to READ_BODY
        return true ;                
    }

    if ( StrHdr[0] == ' ' || StrHdr[0] =='\t' ) // add to previous Header
    {
        if ( ! HTTPUtil::addStringSafe ( m_Request.m_StrWk, StrHdr ) )
        {
            SetReadFailed ();
        }
        return true ;
    }

    if ( m_Request.m_StrWk.size () != 0 ) // not first Header 
    {
        m_NextState = READ_HEADERS;       // Process the previous Header
        ParseHeader ();                   // and stay in READ_HEADERS
    }                                     

    m_Request.m_StrWk = StrHdr ;          // Save as Previous Header
    return true;
}

//------------------------------------------------------------------------
//  Process Header  
//  Returns
//  on success , m_State = m_NextState
//  on invalid Header , m_State=READ_FAILED
//------------------------------------------------------------------------

void HTTPProtocol::ParseHeader ( )
{
    size_t PosDlm = m_Request.m_StrWk.find (':');

    if (  PosDlm == HString::npos  || PosDlm == 0 )
    {
        SetReadFailed ();
        return ;
    }

    size_t  i1 = 0;
    size_t  i2 = PosDlm;

    if ( ! HTTPUtil::skipSpaces (m_Request.m_StrWk , i1 ,i2 ) )
    {
        SetReadFailed ();
        return ;
    }

    HString StrKey ( m_Request.m_StrWk , i1 , i2-i1 );

    HTTPUtil::ToUpper (StrKey);

    i1 = PosDlm+1;
    i2 = HString::npos ;
    
    if ( ! HTTPUtil::skipSpaces (m_Request.m_StrWk , i1 ,i2 ) )
    {
        SetReadFailed ();
        return;
    }

    HString  StrVal ( m_Request.m_StrWk , i1 , i2-i1);

    m_Request.m_Headers [ StrKey ] = StrVal ;
    //m_Request.m_Headers.set ( StrKey , StrVal) ;

    int  KeyId = -1;
    bool Rc    = ParseProtocolHeader ( StrKey , StrVal , KeyId);

    if ( m_State == READ_FAILED )
    {
        return;
    }

    if ( ! m_pHandler->onHeaderReceived ( StrKey,StrVal, KeyId, Rc ) )
    {
        SetReadFailed ();
        return;
    }

    m_State = m_NextState ;
    return;
}

//------------------------------------------------------------------
//  Return :
//   true  - Header processed
//   false - Header not processed, user can do it
//--------------------------------------------------------------------
bool HTTPProtocol::ParseProtocolHeader ( HString & Key, 
                                         HString & Val,
                                         int   &   KeyId)
{
    errno = 0 ;

    KeyId = -1 ;

    TabEl * pEl= FindVerb ( Key.c_str(), HdrTab );

    if ( ! pEl )
    {
        return false;  // not processed
    }

    KeyId = pEl->m_uVal ;

    if ( ! pEl->m_pFunc ) //  == NULL )
    {
        return false;  // not processed
    }

    return (this->* ( pEl->m_pFunc )) ( Val );
}

bool HTTPProtocol::ParseH_ContentLength (HString & Str)
{
    unsigned long Len = ::strtoul( Str.c_str (),
                                   (char**) NULL,
                                   10);

    m_Request.setContentLength_i(Len);

    if ( errno != 0 )
    {
        SetReadFailed ();
    }
    return true ;
}

bool HTTPProtocol::ParseH_TransferEncoding (HString & Str)
{
    if ( ACE_OS_String::strcasecmp ( Str.c_str () ,"chunked")  == 0 )
    {
        m_Request.setChunked_i(true);
    }

    return true ;
}

bool HTTPProtocol::ParseH_Connection (HString & Str)
{
    if ( ACE_OS_String::strcasecmp ( Str.c_str (), "close")  == 0 )
    {
        m_Request.setKeepAlive_i ( false);
        return true;
    }

    if ( ACE_OS_String::strcasecmp ( Str.c_str (),"keep-alive") == 0 
       ||ACE_OS_String::strcasecmp ( Str.c_str (),"keepalive")  == 0
       ||ACE_OS_String::strcasecmp ( Str.c_str (),"persistent") == 0
       )
    {
        m_Request.setKeepAlive_i ( true );
        return true;
    }
 
    return false;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadBody ()
{
    if ( ! m_pHandler->onEndOfHeaders ())
    {
        return SetReadFailed ();
    }

    if ( m_Request.isChunked () )
    {
        m_State = READ_CHUNK_LEN ;
        return true;
    }    

    if ( m_Request.isContentLength() )
    {
        m_State = READ_BODY_PART;
        return true;
    }


    switch ( m_Request.m_Cmd )
    {
    case HTTPRequest::REQ_GET:  
    case HTTPRequest::REQ_HEAD:  
    case HTTPRequest::REQ_TRACE:  
    case HTTPRequest::REQ_DELETE:  
    case HTTPRequest::REQ_OPTIONS:  
        m_State = READ_OK;
        return true;
    default:
        break;
    }

    if ( m_Request.isKeepAlive () )
    {
        SetReadFailed (); // Need Content Length
        return true;
    }
    
    m_State = READ_BODY_PART;
    return true;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadBodyPart ()
{
    size_t nBytesNeed = m_Request.getContentLength()
                      - m_Request.getBodyBytesTransferred ();

    if ( nBytesNeed == 0 )
    {
        if ( ! m_pHandler->onEndOfBody () )
        {
            return SetReadFailed ();
        }

        return SetReadOk ();
    }

    HString &  StrBody = m_Request.getPartBody ();

    HTTPReader::Status Rc = m_Reader.getChunk (StrBody , nBytesNeed );
    
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  break;
    default :                   return SetReadFailed ();
    }

    size_t nBytesRead = StrBody.size ();

    m_Request.m_BodyBytes += nBytesRead;

    if ( nBytesRead > 0 )
    {
        if ( ! m_pHandler->onBodyPartReceived ( StrBody ) )
        {
            return SetReadFailed ();
        }

    }


//    if (  m_Request.m_BodyBytes == m_Request.getContentLength () 
//       || nBytesRead == 0 
//       )
//    {
//        if ( ! m_pHandler->onEndOfBody () )
//        {
//            return SetReadFailed ();
//        }
//
//        return SetReadOk ();
//    }


    return true ;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadChunkLen()
{
    HTTPReader::Status Rc = m_Reader.getLine ( m_Request.m_StrWk);
  
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  return SetReadFailed ();
    default :                   return SetReadFailed ();
    }

    errno=0;

    if ( m_Request.m_StrWk.size () == 0)
    {
        return SetReadFailed ();
    }

    m_Request.m_BodyBytes = 0;
    m_Request.m_ContentLength= ::strtoul( m_Request.m_StrWk.c_str (),
                                           (char**) NULL,
                                           16);

    if ( errno != 0 )
    {
        return SetReadFailed ();
    }

    if ( m_Request.m_ContentLength == 0 )
    {
        if ( ! m_pHandler->onEndOfBody () )
        {
            return SetReadFailed ();
        }

        m_State= READ_FOOTER;
        return true ;
    }

    m_State = READ_CHUNK;
    return true ;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadChunk ()
{
    size_t nBytesNeed = m_Request.getContentLength () ;

    if ( nBytesNeed == 0 )
    {
        m_State = READ_CHUNK_TAIL;
        return true ;
    }

    HString & StrBody = m_Request.getPartBody ();

    HTTPReader::Status Rc = m_Reader.getChunk ( StrBody , nBytesNeed );
    
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  break;
    default :                   return SetReadFailed ();
    }

    size_t nBytesRead = StrBody.size ();

    m_Request.m_BodyBytes += nBytesRead;
    m_Request.m_ContentLength -= nBytesRead;

    if ( m_Request.m_ContentLength == 0 )
    {
        m_State = READ_CHUNK_TAIL;
        return true ;
    }

    if ( nBytesRead == 0 )
    {
        return SetReadFailed();
    }

    if ( ! m_pHandler->onBodyPartReceived ( StrBody ) )
    {
        return SetReadFailed ();
    }

    return true ;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadChunkTail ()
{
    HTTPReader::Status Rc = m_Reader.getLine ( m_Request.m_StrWk);
  
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  return SetReadFailed ();
    default :                   return SetReadFailed ();
    }

    m_State= READ_CHUNK_LEN ;
    return true;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
bool HTTPProtocol::ReadFooter()
{
    HTTPReader::Status Rc = m_Reader.getLine ( m_Request.getFooter() );
  
    switch ( Rc )
    {
    case HTTPReader::READ_MORE: return false;
    case HTTPReader::READ_OK:   break;
    case HTTPReader::READ_EOF:  return SetReadFailed ();
    default :                   return SetReadFailed ();
    }

    if ( ! m_pHandler->onFooterReceived (m_Request.getFooter() ) )
    {
        return SetReadFailed ();
    }

    return SetReadOk ();
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadOk ()
{
    if ( ! m_pHandler->processRequest () )
    {
        return SetReadFailed ();
    }

    m_State = SEND_RESPONSE ;
    return true ;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::ReadFailed ()
{
    m_FlgSuccess = false ;
    m_State = FIN_STATE;
    return true;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

bool HTTPProtocol::SendResponse ()
{
    m_Response.m_ItrWk.begin ();

    m_NextState = SEND_HEADERS ;

    switch (m_Writer.write (m_Response.m_RLine ))
      {
      case HTTPWriter::WRITE_WAIT:
        return false;

      case HTTPWriter::WRITE_ERR:
        return this->SetSendFailed();

      default:
        break;
      }

    return true;
}

bool HTTPProtocol::SendHeaders()
{
    m_Response.m_StrWk.erase ();

    if ( m_Response.m_ItrWk.isValid () )
    {
        m_Response.m_StrWk.append ( m_Response.m_ItrWk.key () );
        m_Response.m_StrWk.append ( ": ");

        m_Response.m_StrWk.append ( m_Response.m_ItrWk.value() );
        m_Response.m_ItrWk++;

        m_NextState = SEND_HEADERS ;
    }
    else
    {
        m_NextState = SEND_BODY ;
    }

    m_Response.m_StrWk.append ( "\r\n" );

    switch (m_Writer.write ( m_Response.m_StrWk ))
     {
      case HTTPWriter::WRITE_WAIT:
        return false;

      case HTTPWriter::WRITE_ERR:
        return this->SetSendFailed();

      default:
        break;
      }

    return true;

}

bool HTTPProtocol::SendBody()
{
    if ( m_Response.isChunked () )
    {
        m_State = SEND_CHUNK;
        return true ;
    }

    m_State = SEND_BODY_PART;
   return true ;
}

bool HTTPProtocol::SendChunk ()
{
   m_Response.m_StrWk.erase ();

   HString & StrBody =  m_Response.getPartBody();

   if ( ! m_pHandler->prepareNextBodyPart ( StrBody ) )
   {
       return SetSendFailed();
   }

   char Buf [128] ;

   size_t Len = StrBody.size();

   if ( Len == 0 )
   {
        m_State = SEND_FOOTER ;
        return true;
   }

   Len = sprintf ( Buf, "%X\r\n", Len );


   m_Response.m_StrWk.append ( Buf, Len );

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, StrBody ) )
   {
       return SetSendFailed();
   }

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, "\r\n" , 2 ) )
   {
       return SetSendFailed();
   }

   StrBody.erase ();
   m_NextState = m_State;

   switch (m_Writer.write ( m_Response.m_StrWk ))
     {
      case HTTPWriter::WRITE_WAIT:
        return false;

      case HTTPWriter::WRITE_ERR:
        return this->SetSendFailed();

      default:
        break;
      }

    return true;

}

bool HTTPProtocol::SendBodyPart ()
{
   m_Response.m_StrWk.erase ();

   HString & StrBody =  m_Response.getPartBody();

   if ( ! m_pHandler->prepareNextBodyPart ( StrBody ) )
   {
       return SetSendFailed();
   }

   size_t Len = StrBody.size();

   if ( Len == 0 )
   {
        m_State = SEND_OK;
        return true;
   }

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, StrBody ) )
   {
       return SetSendFailed();
   }

   StrBody.erase ();
   m_NextState = m_State;

   switch (m_Writer.write ( m_Response.m_StrWk ))
     {
      case HTTPWriter::WRITE_WAIT:
        return false;

      case HTTPWriter::WRITE_ERR:
        return this->SetSendFailed();

      default:
        break;
      }

    return true;

}

bool HTTPProtocol::SendFooter ()
{
   m_Response.m_StrWk.erase ();

   HString & StrFooter = m_Response.getFooter();
   
   if ( ! m_pHandler->prepareNextBodyPart ( StrFooter ) )
   {
       return SetSendFailed();
   }

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, "0\r\n", 3 ) )
   {
       return SetSendFailed();
   }

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, StrFooter ) )
   {
       return SetSendFailed();
   }

   if ( ! HTTPUtil::addStringSafe ( m_Response.m_StrWk, "\r\n" , 2 ) )
   {
       return SetSendFailed();
   }

   StrFooter.erase ();
   m_NextState = SEND_OK;
   
   switch (m_Writer.write ( m_Response.m_StrWk ))
     {
      case HTTPWriter::WRITE_WAIT:
        return false;

      case HTTPWriter::WRITE_ERR:
        return this->SetSendFailed();

      default:
        break;
      }

    return true;

}

bool HTTPProtocol::SendOk()
{
    m_FlgSuccess = true ;
    m_State = FIN_STATE ;
    return true;
}

bool HTTPProtocol::SendFailed()
{
    m_FlgSuccess = false ;
    m_State = FIN_STATE ;
    return true;
}

bool HTTPProtocol::SetSendOk ()
{
    m_State = SEND_OK ;
    return true ;
}

bool HTTPProtocol::SetReadOk ( )
{
    m_State  = READ_OK;
    return true ;
}
bool HTTPProtocol::SetSendFailed ()
{
    if ( m_ErrState == ZERO_STATE )
    {
        m_ErrState = m_State ;
    }

    m_State    = SEND_FAILED ;
    return true ;
}

bool HTTPProtocol::SetReadFailed ( )
{
    if ( m_ErrState == ZERO_STATE )
    {
        m_ErrState = m_State ;
    }
    m_State  = READ_FAILED ;
    return true ;
}

//====================================================================================

