//
//  Uncomment the following line
//  to use svc.conf.xml instead of svc.conf
//
//#define ACE_HAS_XML_SVC_CONF

#if defined (_WIN32)

#  include "config-win32.h"

#elif defined (linux)

// uncomment the following line 
// if you want to include LINUX_Provider
// Linux NAIO (io_getevents/io_submit)
// must be kernel 2.6 

//#  define ACE_HAS_LINUX_LIBAIO


// uncomment the following line 
// if you want to include Event_Poll_Strategy
// Linux epoll interface
// must be kernel 2.6 

#  define ACE_HAS_LINUX_EPOLL

#  include "config-linux.h"

#elif defined (sun)

// uncomment the following line 
// if you want to include SUN_Port_Strategy
// SUN completion port are supported by SunOS 5.10
 
//#define ACE_HAS_SUN_COMPLETION_PORTS

#define ACE_HAS_DEV_POLL

#  include "config-sunos5.8.h"

#elif defined (__xlC__) || defined (__IBMCPP__)

//
// uncomment the following line if you
// don't want to use AIX native AIO
#  define ACE_HAS_AIO_EMULATION

#  include "config-aix5.x.h" 

#endif