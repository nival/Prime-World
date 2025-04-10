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
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef ACE_TESTS_CFG_H
#define ACE_TESTS_CFG_H
//----------------------------------------------------------
#include "ace/Version.h"

#if (ACE_MAJOR_VERSION < 5)

#error unsupported version of ACE

#elif (ACE_MAJOR_VERSION == 5) 

#if ((ACE_MINOR_VERSION == 4) && (ACE_BETA_VERSION > 6))
#   define NEED_COUNTDOWN_TIME 1
#elif (ACE_MINOR_VERSION > 4)
#   define NEED_COUNTDOWN_TIME 1
#endif

#else  // ACE 6.x.y

#   define NEED_COUNTDOWN_TIME 1

#endif  // ((ACE_MAJOR_VERSION))

#ifdef NEED_COUNTDOWN_TIME
#include "ace/Countdown_Time.h"
#endif
//----------------------------------------------------------
#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "ace/Log_Msg.h"
#include "TProactor/Sock_Addr.h"


// helper functions
int 
disable_signal (int sigmin, int sigmax);

int
do_delay (u_long millisec);

// Proactor Type (UNIX only, Win32 ignored)
enum ProactorType
  { 
    DEFAULT = 0, 
    AIOCB,
    SIG,
    CB,
    SUN,
    SELECT,
    POLL,
    DEVPOLL,
    EPOLL,
    LINUX_NAIO,
    SUNPORT,
    KQUEUE,
    DUMMY
  }; 

const  size_t MIN_TIME     = 0;         // min 0 sec
const  size_t MAX_TIME     = 3600;      // max 1 hour
const  u_int  MAX_BLK      = 1024*128;  // 128K
const  u_int  MIN_BLK      = 1;         //
const  u_int  MAX_WIN      = 1024*512;  // 512K
const  u_int  MIN_WIN      = 0;         //
const  size_t MIN_DELAY    = 0;         // min 0
const  size_t MAX_DELAY    = 1000*1000; // 1000 seconds (in milliseconds)
const  u_int  MAX_CONNECTIONS = 10*1000;      //

const  u_int  MAX_THREADS  = 100;          //
const  u_int  MIN_THREADS  = 1;            //

const  u_int  MAX_DEMULTIPLEXORS = 100;    //
const  u_int  MIN_DEMULTIPLEXORS = 1;      //


class LogLocker
{
public:
  LogLocker () { ACE_LOG_MSG->acquire (); }
  virtual ~LogLocker () { ACE_LOG_MSG->release (); }
};

class TestCfg
{
  
public:

  TestCfg  (void);
  virtual ~TestCfg (void);


  int          init ();
  int          parse_args (int argc, ACE_TCHAR *argv[]);
  int          print_usage(int argc, ACE_TCHAR *argv[]);

  void         set_blksize (u_int blksize);
  int          set_proactor_type (const ACE_TCHAR *ptype);
  int          set_proactor_type (ProactorType type);

  int          set_log_level     (int level);
  int          set_num_threads   (u_int threads);
  int          set_num_demultiplexors (u_int demultiplexors);
  int          set_timeout       (u_long timeout);



  const ACE_TString & filename()      const { return filename_;}
  u_int        threads ()             const { return threads_            ;}
  u_int        demultiplexors ()      const { return demultiplexors_     ;}
  ProactorType proactor_type ()       const { return proactor_type_      ;}
  size_t       max_aio_operations ()  const { return max_aio_operations_ ;}
  int          sig_num ()             const { return sig_num_            ;}
  int          leader_type ()         const { return leader_type_        ;}  
  int          start_aio_type ()      const { return start_aio_type_     ;}
  int          both ()                const { return both_               ;}
  const ACE_TCHAR * connect_host ()   const { return connect_host_       ;}
  u_short      connect_port ()        const { return connect_port_       ;}
  u_short      listen_port ()         const { return listen_port_        ;}
  u_int        connections ()         const { return connections_        ;}
  int          loglevel ()            const { return loglevel_           ;} 
  u_int        seconds ()             const { return seconds_            ;}  
  u_long       delay ()               const { return delay_              ;}    
  u_long       timeout ()             const { return timeout_            ;}
  size_t       xfer_limit ()          const { return xfer_limit_         ;}  
  u_int        blksize ()             const { return blksize_            ;}
  u_int        s_blksize ()           const { return s_blksize_          ;}
  u_int        r_blksize ()           const { return r_blksize_          ;}
  u_int        w_size ()              const { return w_size_             ;}  

  void         get_addresses (TRB_Sock_Addr& listenAddr,
                              TRB_Sock_Addr& connectAddr);
                              
  void         get_listen_address (TRB_Sock_Addr& listenAddr);
                                   
  void         get_connect_address (TRB_Sock_Addr& connectAddr);
                                   
  void         get_binding_address (TRB_Sock_Addr& addr, int index);                                   
                                  
protected:

  // Thread Pool Size
  u_int threads_;

  // Number of Proactors
  u_int demultiplexors_;

  ProactorType proactor_type_;

  // POSIX : > 0 max number aio operations  proactor,
  size_t max_aio_operations_;

  // POSIX : signal to interrupt (0- PIPE Strategy,
  //                              sig_num - SIGNAL Strategy)
  int  sig_num_;

  // POSIX : leader type :  0-shared / 1-dedicated
  int  leader_type_;  

  // POSIX : start aio type :  1 - any thread , 0- only leader
  int  start_aio_type_;

  // both:  0 run client or server 
  //          sessions = 0 server
  //          sessions != 0 client
  //     != 0 run client and server
  int both_;

  // Host that we're connecting to.
  const ACE_TCHAR * connect_host_;
  
  // Port that we're connecting to.
  u_short connect_port_;

  // Port that we're receiving connections on.
  u_short listen_port_;
  
  // Clients sessions
  u_int connections_;

  // Log options
  int   loglevel_; // 0 full , 1 medium, 2 only errors

  // seconds to run - 0 means prompt a message to stop
  u_int seconds_;  // default time to run - 2 seconds

  // delay - emulate long callback
  u_long delay_;    

  // timeout per operation (evictor pattern)
  u_long timeout_;


  // Number of bytes for Sender to send. 
  size_t xfer_limit_;  

  u_int  blksize_;
  u_int  s_blksize_;
  u_int  r_blksize_;
  u_int  w_size_;

  ACE_TString filename_;

};

#endif // ACE_TESTS_CFG_H
