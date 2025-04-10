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
//=============================================================================
/**
 *
 *  @file    POSIX_AIO_Config.h
 *
 *  $Id: $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_CONFIG_H 
#define TRB_POSIX_AIO_CONFIG_H 

#include "ace/pre.h"
#include "TProactor/TPROACTOR_Export.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

//----------------------------------------------------------
#include "ace/Version.h"

#if (ACE_MAJOR_VERSION < 5)

#error unsupported version of ACE

#else  

#include "ace/os_include/sys/os_types.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/OS_NS_signal.h"

#if ((ACE_MAJOR_VERSION > 5) || (ACE_MINOR_VERSION > 4) || (ACE_BETA_VERSION > 6))
#include "ace/Countdown_Time.h"
#endif

#endif  // ((ACE_MAJOR_VERSION < 5) 


#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


#define ACE_AIO_MAX_SIZE     2048
#define ACE_AIO_DEFAULT_SIZE 1024
#define ACE_AIO_NO_LIMIT     (ACE_static_cast(size_t,-1))


//Forward declarations

class TRB_POSIX_AIO_Dispatcher;
class TRB_POSIX_AIO_Processor;
class TRB_POSIX_AIO_Provider;


/**
 * @class TRB_POSIX_AIO_Config
 *
 * @brief POSIX implementation .
 */

class TPROACTOR_Export TRB_POSIX_AIO_Config 
{

public:

    // AIO_Processor Types
    enum Processor_Type  
    {
        PCT_NONE      = 0,  // Processor not exist
        PCT_SHARED    = 1,  // handle events in user thread 
        PCT_DEDICATED = 2   // separate permanent thread for event handling
    };


    enum Provider_Class
    {
        PVC_NONE       = 0x0000,
        PVC_POSIX      = 0x0100,
        PVC_SUN_AIO    = 0x0200,
        PVC_LINUX_NAIO = 0x0300,
        PVC_EMULATION  = 0x0400,
        PVC_MASK       = 0xFF00
    };

    // AIO_Provider Types
    enum Provider_Type           
    {
        PVT_NONE        = (PVC_NONE),         // Provider not exist
        PVT_POSIX_AIOCB = (PVC_POSIX | 1),    // POSIX Standart AIO api
        PVT_POSIX_SIG   = (PVC_POSIX | 2),
        PVT_POSIX_CB    = (PVC_POSIX | 3),
        PVT_SUN_AIO     = (PVC_SUN_AIO),
        PVT_LINUX_NAIO  = (PVC_LINUX_NAIO),   // Linux libaio apo io_XXXXX
        PVT_SELECT      = (PVC_EMULATION | 1),  // 
        PVT_POLL        = (PVC_EMULATION | 2),
        PVT_EPOLL       = (PVC_EMULATION | 3),
        PVT_DEVPOLL     = (PVC_EMULATION | 4),
        PVT_SUNPORT     = (PVC_EMULATION | 5),
        PVT_KQUEUE      = (PVC_EMULATION | 6)
    };

    //enum Provider_Flags
    //{
    //    PVF_AIO_START_ANY_THREAD     = 0x0001, 
    //    // AIO can start in any thread, 
    //    // othewise on in leader thread

    //    PVF_AIO_START_INTERRUPT_WAIT = 0x0002 
    //    // Start AIO should interrupt waiter/leader 
    //    // to update wait state. For example,
    //    // re-issue aio_suspend() with new params.
    //};

    TRB_POSIX_AIO_Config (size_t  max_num_aio       = ACE_AIO_NO_LIMIT,
                          int     processor_type    = PCT_SHARED,
                          int     provider_type     = PVT_SELECT,
                          int     processor_op_mask = 0xFFFFFFFF);

    ~TRB_POSIX_AIO_Config (void);

 
    TRB_POSIX_AIO_Processor * create_processor 
           (TRB_POSIX_AIO_Dispatcher & dispatcher) const;

    TRB_POSIX_AIO_Provider * create_provider (void) const;

    void    dump (void) const;

    size_t  max_handles(void) const;
    size_t  max_num_aio (void) const;

    int     processor_type (void) const;
    int     processor_op_mask (void) const;
  
    int     provider_type (void) const;
    int     provider_class (void) const;
    int     provider_flags (void) const;

protected:

    size_t  max_num_aio_;

    int     processor_type_;
    int     processor_op_mask_;
  
    int     provider_type_;
    int     provider_flags_;
};

inline size_t
TRB_POSIX_AIO_Config::max_num_aio (void) const 
{ 
  return this->max_num_aio_;
}

inline int
TRB_POSIX_AIO_Config::processor_type (void) const 
{ 
    return this->processor_type_;
} 

inline int
TRB_POSIX_AIO_Config::processor_op_mask (void) const 
{
    return this->processor_op_mask_;
}

inline int
TRB_POSIX_AIO_Config::provider_type (void) const 
{
    return this->provider_type_;
}

inline int
TRB_POSIX_AIO_Config::provider_class (void) const 
{
    return (this->provider_type_ & PVC_MASK);
}

inline int
TRB_POSIX_AIO_Config::provider_flags (void) const 
{
  return this->provider_flags_;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS || ACE_HAS_AIO_EMULATION */

#include "ace/post.h"

#endif //TRB_POSIX_AIO_CONFIG_H 
