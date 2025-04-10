/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
** = AUTHOR
**   Alexander Libman <libman@terabit.com.au>
**
**
**
**********************************************************************/

#ifndef TERABIT_IOTHREADPOOL_H
#define TERABIT_IOTHREADPOOL_H

#include "IOTerabit/IOTERABIT_Export.h"

#include "IOTerabit/BaseThreadPool.h"
#include "TProactor/Proactor.h"
#include <vector>

namespace Terabit {

/**
 * @class IOThreadPool
 * IOThreadPool plays role for Proactor threads pool
 *
 * IOThreadPool is ACE_Task resposible for:
 * 1. Creation and deletion of Proactor thread pool
 * 2. Running Proactor event loop
 *
 */


class IOTERABIT_Export IOThreadPool : public BaseThreadPool
{
public:

    // Proactor Type (UNIX only, Win32 ignored)
    enum ProactorType
    { 
        PT_DEFAULT = 0, 
        PT_AIOCB,
        PT_SIG,
        PT_CB,
        PT_SUN,
        PT_SELECT,
        PT_POLL,
        PT_DEVPOLL,
        PT_EPOLL,
        PT_LINUX_NAIO,
        PT_SUNPORT,
        PT_KQUEUE,
        PT_DUMMY
    };

    IOThreadPool (const ACE_TCHAR *name,
                  ProactorType  proactor_type = PT_DEFAULT,
                  int           leader_type = 0,     // shared
                  int           num_proactors = 1,   //
                  size_t        max_op = 0,
                  int           proactor_sig_num = 0);


    virtual ~IOThreadPool();


    TRB_Proactor * get_proactor (u_int idx = 0);

protected:
    virtual int enable_event_loop (void);
    virtual int disable_event_loop (void);
    virtual int run_event_loop (u_int thr_num);

    int create_proactors  (int num_proactors);
    int destroy_proactors ();

private:
    TRB_Proactor * create_proactor (int idx); 


    typedef std::vector<TRB_Proactor *> ProactorVector;
    ProactorVector proactor_vect_;

    ProactorType  proactor_type_;
    int           leader_type_;       // POSIX leader type:  0-shared, 1-dedicated
    size_t        max_op_;            // for old compatibility
    int           proactor_sig_num_;  // for old compatibility
    long          num_processors_;    // number of processors;
};

}  //namespace Terabit 



#endif  // TERABIT_IOTHREADPOOL_H

