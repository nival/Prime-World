// 

// ============================================================================
/**
 *  @file Cfg.cpp
 *
 *  Cfg.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"
#include "Cfg.h"
#include "ace/Signal.h"

TestCfg::TestCfg (void)
{
  this->init ();
}


TestCfg::~TestCfg (void)
{
}

void 
TestCfg::set_blksize (u_int blksize)
{
  if (blksize < MIN_BLK)
      blksize = MIN_BLK;

  if (blksize > MAX_BLK)
      blksize = MAX_BLK;

  this->blksize_   = blksize;
  this->s_blksize_ = this->blksize_;          // send block size
  this->r_blksize_ = this->s_blksize_*2;      // recv block size

  if (this->r_blksize_ < BUFSIZ)
    this->r_blksize_ = BUFSIZ;
}

int
TestCfg::init(void)
{
  threads_            = 1;
  demultiplexors_     = 1;

  proactor_type_      = Terabit::IOThreadPool::PT_SELECT;
  
  max_aio_operations_ = 0;

  sig_num_            = 0;  // use pipe
  leader_type_        = 0;  // S=0  shared     D=1  dedicated
  start_aio_type_     = 1;  // A=1  any thread L=0  only leader thread

  both_               = 1;  // both
  connect_host_       = ACE_LOCALHOST;
  connect_port_       = ACE_DEFAULT_SERVER_PORT;
  listen_port_        = ACE_DEFAULT_SERVER_PORT;
  connections_        = 20;

  loglevel_           = 2;  // 0 full, 1 medium, 2 only errors 
  seconds_            = 3;  
  delay_              = 0;  // no delay    
  timeout_            = 0;  // no timeout

  xfer_limit_         = 0;  // unlimited
  blksize_            = 1024;
  s_blksize_          = 1024;
  r_blksize_          = 1024;
  w_size_             = 0;

  
  this->set_blksize(1024);

  return 0;
}


int
TestCfg::parse_args (int argc, ACE_TCHAR *argv[])
{
    ACE_Get_Opt get_opt (argc, argv, ACE_TEXT ("j:f:m:r:x:d:k:l:a:g:i:t:o:n:p:w:h:s:v:ub"));
    int c;

    while ((c = get_opt ()) != EOF)
    {
        switch (c)
        {
        case 'j':  // demultiplexors
            this->set_num_demultiplexors ( ACE_OS::atoi (get_opt.opt_arg ()));
            break;

        case 'f':
            this->filename_ = get_opt.opt_arg ();
            break;

        case 'x':  // xfer limit
            this->xfer_limit_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;
      
        case 'k':   // blksize
            this->set_blksize (ACE_OS::atoi (get_opt.opt_arg ()));
            break;

        case 'w':         // win size
            this->w_size_ = ACE_OS::atoi (get_opt.opt_arg ());
            if (this->w_size_ <= MIN_WIN)
            this->w_size_ = MIN_WIN;
            if (this->w_size_ > MAX_WIN)
            this->w_size_ = MAX_WIN;
            break;

        case 'd':         // delay
            this->delay_ = ACE_OS::atoi (get_opt.opt_arg ());
            if (this->delay_ > MAX_DELAY)
            this->delay_ = MAX_DELAY;
            break;

        case 'm':         // timeout
            this->timeout_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 'g':   // signal to interrupt
            this->sig_num_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 'l':   // leader type
            if (::toupper (*get_opt.opt_arg ()) == 'D')  // dedicated
                this->leader_type_ = 1; // dedicated
            else
                this->leader_type_ = 0; // shared 
            break;

        case 'a':   // start aio type
            if (::toupper (*get_opt.opt_arg ()) == 'L')  //  start aio
                this->start_aio_type_ = 0;                 //  only in leader
            else
                this->start_aio_type_ = 1;                 //  any thread
            break;

        case 'i':  // time to run
            this->seconds_ = ACE_OS::atoi (get_opt.opt_arg ());
            if (this->seconds_ <= MIN_TIME)
                this->seconds_ = MIN_TIME;
            if (this->seconds_ > MAX_TIME)
                this->seconds_ = MAX_TIME;
            break;

        case 'b':  // both client and server
            this->both_ = 1;
            break;

        case 'v':  // log level
            this->loglevel_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 'h':         // host to connect
            this->connect_host_ = get_opt.opt_arg ();
            break;
        case 'p':         // port to connect
            this->connect_port_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 'r':         // port to listen
            this->listen_port_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 'n':         // thread pool size
            this->set_num_threads (ACE_OS::atoi (get_opt.opt_arg ()));
            break;

        case 's':     // number of connections_
            this->connections_ = ACE_OS::atoi (get_opt.opt_arg ());
            if (connections_ > MAX_CONNECTIONS)
                connections_ = MAX_CONNECTIONS;
            break;

        case 'o':     // max number of aio for proactor
            this->max_aio_operations_ = ACE_OS::atoi (get_opt.opt_arg ());
            break;

        case 't':    //  Proactor Type
            if (set_proactor_type (get_opt.opt_arg ()) < 0)
                return print_usage (argc, argv);
            break;

        case 'u':
        default:
            return print_usage (argc, argv);
        } // switch
    } // while

  return 0;
}

int 
TestCfg::set_log_level (int level)
{
    this->loglevel_ = level;
    return 0;
}

int
TestCfg::set_num_demultiplexors (u_int demultiplexors)
{
    if (demultiplexors > MAX_DEMULTIPLEXORS)  
        demultiplexors = MAX_DEMULTIPLEXORS;

    if (demultiplexors < MIN_DEMULTIPLEXORS)  
        demultiplexors = MIN_DEMULTIPLEXORS;          

    this->demultiplexors_ = demultiplexors;
    return 0;
}
int
TestCfg::set_num_threads (u_int threads)
{
    if (threads > MAX_THREADS)  threads = MAX_THREADS;
    if (threads < MIN_THREADS)  threads = MIN_THREADS;          
    this->threads_ = threads;
    return 0;
}

int 
TestCfg::set_timeout (u_long timeout)
{
    this->timeout_ = timeout;
    return 0;
}

int
TestCfg::set_proactor_type (ProactorType ptype)
{
    this->proactor_type_ = ptype;
    return 0;
}

int
TestCfg::set_proactor_type (const ACE_TCHAR *ptype)
{
  this->proactor_type_ = Terabit::IOThreadPool::PT_DEFAULT;

  if (!ptype)
    return -1;
  

  switch (::toupper (*ptype))
    {
    case 'D':  this->proactor_type_ = Terabit::IOThreadPool::PT_DEFAULT; break;
    case 'A':  this->proactor_type_ = Terabit::IOThreadPool::PT_AIOCB;   break;
    case 'I':  this->proactor_type_ = Terabit::IOThreadPool::PT_SIG;     break;
    case 'E':  this->proactor_type_ = Terabit::IOThreadPool::PT_SELECT;  break;
    case 'P':  this->proactor_type_ = Terabit::IOThreadPool::PT_POLL;    break;
    //case 'R':  this->proactor_type_ = Terabit::IOThreadPool::PT_LINUXRT; break;
    case 'L':  this->proactor_type_ = Terabit::IOThreadPool::PT_LINUX_NAIO;   break;
    case 'S':  this->proactor_type_ = Terabit::IOThreadPool::PT_SUN;     break;
    case 'V':  this->proactor_type_ = Terabit::IOThreadPool::PT_DEVPOLL; break;
    case 'O':  this->proactor_type_ = Terabit::IOThreadPool::PT_EPOLL;   break;
    case 'C':  this->proactor_type_ = Terabit::IOThreadPool::PT_CB;      break;
    case 'K':  this->proactor_type_ = Terabit::IOThreadPool::PT_SUNPORT; break;
    case 'Q':  this->proactor_type_ = Terabit::IOThreadPool::PT_KQUEUE;  break;
    case 'Y':  this->proactor_type_ = Terabit::IOThreadPool::PT_DUMMY;   break;
    default:   return -1;
    }
  return 0;
}
void 
TestCfg::get_addresses (TRB_Sock_Addr& listenAddr,
                        TRB_Sock_Addr& connectAddr)
{
    u_short listenPort  = this->listen_port ();
    u_short connectPort = this->connect_port ();
    const char* host    = this->connect_host ();


#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    if (listenPort == 0xFFFF)
    {
        ACE_UNIX_Addr tmp (host);
        listenAddr = tmp;
        ACE_OS::unlink (host);
    }
    else
#endif
    {
        ACE_INET_Addr tmp (listenPort);
        listenAddr = tmp;
    }

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    if (connectPort == 0xFFFF)
    {
        ACE_UNIX_Addr tmp (host);
        connectAddr = tmp;
    }
    else
#endif
    {
        ACE_INET_Addr tmp (connectPort, host);
        connectAddr = tmp;
    }
}

int
TestCfg::print_usage (int /* argc */, ACE_TCHAR *argv[])
{
  ACE_ERROR
    ((LM_ERROR,
      ACE_TEXT ("\nusage: %s")
      ACE_TEXT ("\n-h host to connect (default ACE_LOCALHOST)")
      ACE_TEXT ("\n-p port to connect (default ACE_DEFAULT_SERVER_PORT)")
      ACE_TEXT ("\n-r port to listen  (default ACE_DEFAULT_SERVER_PORT)")
      ACE_TEXT ("\n-n number threads in thread pool")
      ACE_TEXT ("\n-j number demultiplexors in thread pool")
      ACE_TEXT ("\n-s number of sender's instances")
      ACE_TEXT ("\n-b run client and server at the same time")
      ACE_TEXT ("\n-k data block size to send/receive")
      ACE_TEXT ("\n-w flow control window size")
      ACE_TEXT ("\n-x session limit transfer count")
      ACE_TEXT ("\n-i time to run in seconds (0 means prompt to stop)")
      ACE_TEXT ("\n-d delay for long callback in milliseconds(0 means no delay)")
      ACE_TEXT ("\n-m timeout per operation in seconds (0 means no timeout)")
      ACE_TEXT ("\n-v log level")
      ACE_TEXT ("\n    0 - log all messages")
      ACE_TEXT ("\n    1 - log all short messages")
      ACE_TEXT ("\n    2 - log only errors and unusual cases")
      ACE_TEXT ("\n-u show this message")
      ACE_TEXT ("\n ****** the following parameters are valid     ******")
      ACE_TEXT ("\n ****** only for POSIX Proactor tests          ******")
      ACE_TEXT ("\n ****** and ignored for Win32 and TP_Reactor   ******")
      ACE_TEXT ("\n-o max number of started aio operations")
      ACE_TEXT ("\n-t Proactor type")
      ACE_TEXT ("\n    A POSIX AIOCB - aiosuspend()")
      ACE_TEXT ("\n    I POSIX SIG - sigwaitinfo()")
      ACE_TEXT ("\n    C POSIX CALLBACK - SGI style aio callbacks")
      ACE_TEXT ("\n    S SUN - Sun aiowait()")
      ACE_TEXT ("\n    E SELECT - select()")
      ACE_TEXT ("\n    P POLL - poll()")
      ACE_TEXT ("\n    V DEVPOLL - Sun /dev/poll")
      ACE_TEXT ("\n    K SUNPORT - Sun port_get()")
      ACE_TEXT ("\n    O EPOLL - Linux epoll_wait()")
      ACE_TEXT ("\n    L LINUX NAIO  - Linux - io_getevents()")
      ACE_TEXT ("\n    D default")
      ACE_TEXT ("\n-g signal number for SIGNAL interrupt strategy")
      ACE_TEXT ("\n   0 means use PIPE interrrupt strategy (default)")
      ACE_TEXT ("\n-l leader type ")
      ACE_TEXT ("\n   D - dedicated")
      ACE_TEXT ("\n   S - shared (default)")
      ACE_TEXT ("\n-a start aio is performed in:")
      ACE_TEXT ("\n   L - leader thread only")
      ACE_TEXT ("\n   A - any thread (default)")
      ACE_TEXT ("\n"),
      argv[0]
   ));
  return -1;
}


//-----------------------------------------------------
//  Emulate long callback - do delay
//-----------------------------------------------------
int
do_delay (u_long millisec)
{
  int rc = 0;


#if defined _WIN32

	::Sleep (millisec);

#else // _WIN32

  timeval  tv;

  //do 
  {
       tv.tv_sec  = millisec/1000;
       tv.tv_usec = (millisec%1000)*1000;

       rc = ::select (0,0,0,0,&tv);
    }
  //while (rc < 0 && ACE_OS::last_error() == EINTR);

#endif // _WIN32

  return rc;
}

//=======================================================================

