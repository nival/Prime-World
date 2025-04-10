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
 *  @file W_Test.cpp
 *
 *  W_Test.cpp
 *
 *  This program illustrates how the TRB_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"

#if defined (ACE_HAS_THREADS) && \
  ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS)))
  // This only works on Win32 platforms and on Unix platforms
  // supporting POSIX aio calls.

#include "ARWConnection.h"
#include "SSLConnection.h"
#include "HTTPProtocol.h"

static TestCfg cfg;


// *************************************************************
//
// *************************************************************
class DemoHandler : public HTTPHandler  
{
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

    virtual bool processRequest ();
    virtual bool prepareNextBodyPart (HString & StrBody ){ return true;}
    virtual bool prepareFooter(HString & /*StrFooter*/)  { return true;}

    DemoHandler(HTTPProtocol  & Protocol);
    virtual ~DemoHandler ();

};

DemoHandler::DemoHandler (HTTPProtocol  & Protocol)
:   HTTPHandler (Protocol)
{
    ACE_DEBUG (( LM_DEBUG, "DemoHandler::CTOR\n"));
}

DemoHandler::~DemoHandler()
{
    ACE_DEBUG (( LM_DEBUG, "DemoHandler::DTOR\n"));
}
  
bool DemoHandler::processRequest ()
{
    char Buf [1024];

    // Set Response Line
    m_Response.getRLine () = "HTTP/1.1 200 ok\r\n";

    //Set Some Headeres

    HMap &  MapO = m_Response.getHeaders ();

    MapO [ HString("Content-type")] = HString ("text/html") ;

    MapO [ HString("Date")] = HString ("Wed, 22 Oct 2003 12:00:00 GMT"); 

    // Prepare Body String

    HString & StrBody = m_Response.getPartBody();
    
    StrBody.erase ();

    StrBody.append ( "<HTML><BODY BGCOLOR=\"#ffffff\">\r\n"
                     "<H2> This is demo HHTP Server W_Test."
                     "</H2>"
                     "<H2> I am based on Proactor framework."
                     "</H2>"
                     "<H2> I can print input request data."
                     "</H2>" 
                    );

    StrBody.append ( "<P>=======REQUEST=========<P>" );

    StrBody.append ( m_Request.getRLine() ) ;

    sprintf ( Buf , "<P> Command Enum Value=%d MajVer=%d MinVer=%d" ,
                    m_Request.getRequestCode (),
                    m_Request.getMajorVer (),
                    m_Request.getMinorVer ()
                    );
    StrBody.append ( Buf );

    StrBody.append ( "<P> URI=" );
    StrBody.append ( m_Request.getURI () );

    StrBody.append ( "<P>=======HEADERS=========<P>" );

    HMapItr Itr1 ( m_Request.getHeaders() );
    HMapItr Itr2 ( m_Request.getHeaders() );
    
    for ( Itr1.begin(), Itr2.end(); Itr1 != Itr2 ; ++Itr1 )
    {
        StrBody.append ( Itr1.key() );
        StrBody.append ( "=");

        StrBody.append ( Itr1.value() );
        StrBody.append ( "<P>" );
    }

    StrBody.append ( "<P>=========BODY=========<P>" );
    
    StrBody.append ( m_Request.getPartBody () );
    StrBody.append ( "<P>" );

    StrBody.append ( "<br> <form action=\"/main.html\" method=post>" 
    "<input type=\"text\" name=\"FirstName\" value=\"\" size=30> First Name"
    "<p>"
    "<input type=\"text\" name=\"LastName\" value=\"\" size=30> Last Name"
    "<p>"
    "<input type=\"submit\" name=\"Submit\" suze=30>"
    "<p>" );


    StrBody.append ( "</BODY></HTML>\r\n" );
    StrBody.append ( "\r\n" );

    //Set More Headeres

    sprintf ( Buf , "%d" , StrBody.size () );
    MapO [ HString("Content-Length")] = HString ( Buf );
    
    return true;
}
// *************************************************************
//
// *************************************************************

class RecvFactory : 
  public PConnectionFactory,
  public HTTPHandlerFactory
{
public:


  virtual PConnection*  create_connection(PConnectionManager & /*manager*/)
    {
      PConnection * p = 0;
      ACE_NEW_RETURN (p, ARWConnection, 0);
      return p;
    }

  virtual void destroy_connection  (PConnection * connection) 
    {
      delete connection;
    }

  virtual PConnectionProtocol * create_protocol(PConnection * connection)
    {
       PConnectionProtocol * p = 0;
       ACE_NEW_RETURN (p, HTTPProtocol (connection, *this), 0);
       return p;
    }

  virtual void destroy_protocol (PConnectionProtocol * protocol) 
    { 
      delete protocol;
    }

  virtual HTTPHandler * create_handler (HTTPProtocol & protocol) 
    {
        return new DemoHandler (protocol);
    }

  virtual void destroy_handler (HTTPHandler * handler) 
    { 
      delete handler;
    }

};

class RecvFactorySSL : 
  public PConnectionFactory,
  public HTTPHandlerFactory
{
public:


  virtual PConnection*  create_connection(PConnectionManager & /*manager*/)
    {
      PConnection * p = 0;
      ACE_NEW_RETURN (p, SSLConnection, 0);
      return p;
    }

  virtual void destroy_connection  (PConnection * connection) 
    {
      delete connection;
    }

  virtual PConnectionProtocol * create_protocol(PConnection * connection)
    {
       PConnectionProtocol * p = 0;
       ACE_NEW_RETURN (p, HTTPProtocol (connection, *this), 0);
       return p;
    }

  virtual void destroy_protocol (PConnectionProtocol * protocol) 
    { 
      delete protocol;
    }

  virtual HTTPHandler * create_handler (HTTPProtocol & protocol) 
    {
        return new DemoHandler (protocol);
    }

  virtual void destroy_handler (HTTPHandler * handler) 
    { 
      delete handler;
    }

};
// *************************************************************
//   Configuration helpers
// *************************************************************

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("W_Test"));


  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

  //ACE_DEBUG ((LM_DEBUG,
  //            ACE_TEXT ("FD_SETSIZE=%d ACE_FDSETSIZE=%d\n"),
  //            FD_SETSIZE,
  //            ACE_FD_SETSIZE));

  ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


  ACE_SSL_Context *context = ACE_SSL_Context::instance ();
  // Note - the next two strings are naked on purpose... the arguments to
  // the ACE_SSL_Context methods are const char *, not ACE_TCHAR *.
  context->certificate ("dummy.pem", SSL_FILETYPE_PEM);
  context->private_key ("key.pem", SSL_FILETYPE_PEM);


  {
  int rc = 0;

  ProactorTask task1(cfg);

  RecvFactory    r_factory;
  RecvFactorySSL r_ssl_factory;

  PConnectionManager r_manager     (task1, r_factory,"R_Manager");
  PConnectionManager r_ssl_manager (task1, r_ssl_factory,"R_SSL_Manager");

  Acceptor  acceptor     (r_manager);
  Acceptor  acceptor_ssl (r_ssl_manager);

  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task1.start () == 0)
    {
      ACE_Time_Value timeout (cfg.timeout(), 0);
      r_manager.set_timeout (timeout);

      // Simplify, initial read with zero size
      if (acceptor.start (ACE_INET_Addr (cfg.listen_port())) == 0)
        rc = 1;

      if (acceptor_ssl.start (ACE_INET_Addr (cfg.listen_port()+1)) == 0)
        rc = 1;

      time_begin = ACE_OS::gettimeofday ();

      if (rc > 0)
        {
          task1.enable_event_loop();
          
          char c;
          cout << "Press any key to stop=>" << flush;
          cin.clear ();
          cin >> c;
        }
    }


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Cancel Acceptor    : PendingOP=%d Receivers=%d\n"),
              acceptor.get_pending_count(),  // number_pending_accepts
              r_manager.get_number_connections ()
            ));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Cancel Acceptor_SSL: PendingOP=%d Receivers=%d\n"),
              acceptor_ssl.get_pending_count (),  // number_pending_accepts
              r_ssl_manager.get_number_connections ()
            ));

  // Cancel all pending AIO on
  // Acceptors and all Receivers
  acceptor.cancel  ();
  acceptor_ssl.cancel  ();

  acceptor.wait ();
  acceptor_ssl.wait ();

  r_manager.cancel ();
  r_ssl_manager.cancel ();
   

  while (!r_manager.is_safe_to_delete ()    ||
         !r_ssl_manager.is_safe_to_delete ())
    {
        task1.wait_signal ();
    }

  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task1.stop ();
 
 
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Stop Acceptor    : PendingOP=%d Receivers=%d\n"),
              acceptor.get_pending_count (),  //number_pending_accepts
              r_manager.get_number_connections ()
            ));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Stop Acceptor_SSL: PendingOP=%d Receivers=%d\n"),
              acceptor_ssl.get_pending_count (),  //number_pending_accepts
              r_ssl_manager.get_number_connections ()
            ));


  //Print statistic
  r_manager.print_statistic ();
  r_ssl_manager.print_statistic ();
  
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
              cfg.threads(),
              cfg.blksize()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Connections: Max=%d R=%d \n"),
              cfg.connections (),
              r_manager.get_peak_connections()));


  float  fsec = (float)(time_run.msec()/1000);
  double fspeed = ((float) r_manager.get_total_snd()
                  +(float) r_manager.get_total_rcv()
                  );

  if ( fsec > 0.1 )
    fspeed /= fsec; 

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective run time = %f sec\n"),
              fsec));


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective bytes/sec = %f\n"),
              fspeed));

 }

  ACE_END_TEST;

  return 0;
}

#else /* ACE_WIN32 && !ACE_HAS_WINCE || ACE_HAS_AIO_CALLS */

int
main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("W_Test"));

  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("Threads or Asynchronous IO is unsupported.\n")
              ACE_TEXT ("W_Test will not be run.")));

  ACE_END_TEST;

  return 0;
}

#endif  /* ACE_WIN32 && !ACE_HAS_WINCE || ACE_HAS_AIO_CALLS */
