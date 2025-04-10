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

/* -*- C++ -*- */
// $Id:  $

#include "TProactor/POSIX_AIO_Config.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)


#include "TProactor/POSIX_AIO_Dispatcher.h"
#include "TProactor/POSIX_AIO_Processor.h"

#include "TProactor/POSIX_AIO_Select_Provider.h"
#include "TProactor/POSIX_AIO_Poll_Provider.h"
#include "TProactor/POSIX_AIO_Event_Poll_Provider.h"
#include "TProactor/POSIX_AIO_Dev_Poll_Provider.h"
#include "TProactor/POSIX_AIO_SUN_Port_Provider.h"
#include "TProactor/POSIX_AIO_Kqueue_Provider.h"

#include "TProactor/POSIX_AIO_STD_Provider.h"
#include "TProactor/POSIX_AIO_SUN_Provider.h"
#include "TProactor/POSIX_AIO_LINUX_NAIO_Provider.h"

#include "ace/Log_Msg.h"
#include "ace/ACE.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

TRB_POSIX_AIO_Config::TRB_POSIX_AIO_Config(size_t  max_num_aio,    
                                           int     processor_type, 
                                           int     provider_type,
                                           int     processor_op_mask)
: max_num_aio_       (max_num_aio)
, processor_type_    (processor_type)
, processor_op_mask_ (processor_op_mask)
, provider_type_     (provider_type)   
, provider_flags_    (0)
{
}

TRB_POSIX_AIO_Config::~TRB_POSIX_AIO_Config (void)
{
}

void
TRB_POSIX_AIO_Config::dump (void) const
{
    const ACE_TCHAR * str_tmp ;

    ACE_DEBUG ((LM_DEBUG, 
        ACE_LIB_TEXT ("Max. number aios : %u\n"),
        (unsigned int)this->max_num_aio_));

    switch (this->processor_type())
    {
    case PCT_NONE:      str_tmp = ACE_LIB_TEXT("DUMMY (not exist)"); break;
    case PCT_DEDICATED: str_tmp = ACE_LIB_TEXT("DEDICATED"); break;
    case PCT_SHARED:    str_tmp = ACE_LIB_TEXT("SHARED"); break;
    default:            str_tmp = ACE_LIB_TEXT("??????"); break;
    }

    ACE_DEBUG ((LM_DEBUG, 
        ACE_LIB_TEXT ("AIO Processor type  : %X %s\n"), 
        this->processor_type_,
        str_tmp));

    switch (this->provider_type ())
    {
    case PVT_NONE       :   str_tmp = ACE_LIB_TEXT("DUMMY (not exist)"); break;
    case PVT_POSIX_AIOCB:   str_tmp = ACE_LIB_TEXT("POSIX_AIOCB"); break;
    case PVT_POSIX_SIG  :   str_tmp = ACE_LIB_TEXT("POSIX_SIG  "); break;
    case PVT_POSIX_CB   :   str_tmp = ACE_LIB_TEXT("POSIX_CB   "); break;
    case PVT_SUN_AIO    :   str_tmp = ACE_LIB_TEXT("SUN_AIO    "); break;
    case PVT_LINUX_NAIO :   str_tmp = ACE_LIB_TEXT("LINUX_NAIO "); break;
    case PVT_SELECT     :   str_tmp = ACE_LIB_TEXT("SELECT     "); break;
    case PVT_POLL       :   str_tmp = ACE_LIB_TEXT("POLL       "); break;
    case PVT_EPOLL      :   str_tmp = ACE_LIB_TEXT("EPOLL      "); break;
    case PVT_DEVPOLL    :   str_tmp = ACE_LIB_TEXT("DEVPOLL    "); break;
    case PVT_SUNPORT    :   str_tmp = ACE_LIB_TEXT("SUNPORT    "); break;
    case PVT_KQUEUE     :   str_tmp = ACE_LIB_TEXT("KQUEUE     "); break;
    default             :   str_tmp = ACE_LIB_TEXT("??????");      break;
    }
    ACE_DEBUG ((LM_DEBUG, 
        ACE_LIB_TEXT ("AIO Provider type   : %X %s\n"), 
        this->provider_type_,
        str_tmp));

}

size_t
TRB_POSIX_AIO_Config::max_handles (void) const 
{ 
    // take user defined limitation
    //size_t max_num_files = this->max_handles_;

    size_t max_num_files = 0;
    
    // if user number is not defined, take system max files
    if ((int) max_num_files <= 0)
        max_num_files = ACE_static_cast(size_t, ACE::max_handles ());

    // if still not defined take hard-coded value 
    if ((int) max_num_files <= 0)
        max_num_files = ACE_AIO_DEFAULT_SIZE;
    
    return max_num_files;
}

TRB_POSIX_AIO_Processor  *
TRB_POSIX_AIO_Config::create_processor 
    (TRB_POSIX_AIO_Dispatcher & dispatcher) const
{
    TRB_POSIX_AIO_Processor * processor = 0;

    switch (this->processor_type ())
    {
    case PCT_NONE:    
        break;
    case PCT_DEDICATED: 
        ACE_NEW_RETURN 
            (processor,
            TRB_POSIX_AIO_Dedicated_Processor (dispatcher,
                                               *this),
            0);
        break;

    case PCT_SHARED: 
        ACE_NEW_RETURN 
            (processor,
            TRB_POSIX_AIO_Processor (dispatcher,
                                     *this),
            0);
    default:            
        break;
    }
    return processor;
}

TRB_POSIX_AIO_Provider *
TRB_POSIX_AIO_Config::create_provider (void) const
{
    TRB_POSIX_AIO_Provider * provider = 0;
    switch (this->provider_type())
    {
#if defined (ACE_HAS_AIO_CALLS) 

    case TRB_POSIX_AIO_Config::PVT_POSIX_AIOCB:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_AIOCB_Provider (*this),
                        0);
        break;

    case TRB_POSIX_AIO_Config::PVT_POSIX_CB:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_CB_Provider (*this),
                        0);
        break;

#if defined(sun)
    case TRB_POSIX_AIO_Config::PVT_SUN_AIO:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_SUN_Provider (*this),
                        0);
        break;
#endif // (sun)        

#if defined(linux) && defined(ACE_HAS_LINUX_LIBAIO) 
    case TRB_POSIX_AIO_Config::PVT_LINUX_NAIO:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_LINUX_NAIO_Provider (*this),
                        0);
        break;
#endif // (linux)

#endif // (ACE_HAS_AIO_CALLS) 

    case TRB_POSIX_AIO_Config::PVT_SELECT:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Select_Provider (*this),
                        0);
        break;

    case TRB_POSIX_AIO_Config::PVT_POLL:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Poll_Provider (*this),
                        0);
        break;

#if defined(linux) && defined(ACE_HAS_LINUX_EPOLL) 
    case TRB_POSIX_AIO_Config::PVT_EPOLL:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Event_Poll_Provider (*this),
                        0);
        break;
#endif

#if defined(sun) && defined(ACE_HAS_DEV_POLL)
    case TRB_POSIX_AIO_Config::PVT_DEVPOLL:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Dev_Poll_Provider (*this),
                        0);
        break;
#endif

#if defined(sun) && defined(ACE_HAS_SUN_COMPLETION_PORTS)
    case TRB_POSIX_AIO_Config::PVT_SUNPORT:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_SUN_Port_Provider (*this),
                        0);
        break;
#endif

//#if (defined(__FreeBSD__) || defined(__APPLE__)) && defined(ACE_HAS_KQUEUE)
#if defined(ACE_HAS_KQUEUE)
    case TRB_POSIX_AIO_Config::PVT_KQUEUE:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Kqueue_Provider (*this),
                        0);
        break;
#endif

    default:
        ACE_NEW_RETURN (provider,
                        TRB_POSIX_AIO_Select_Provider (*this),
                        0);
        break;
    }
  return provider;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
