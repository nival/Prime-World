/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   @file IOThreadPool.cpp 
**  
**  
**   @author Alexander Libman <libman@terabit.com.au>
**
**
**********************************************************************/

#include "IOTerabit/IOThreadPool.h"
#include "ace/Signal.h"
#include "ace/OS_NS_unistd.h"

#if defined (ACE_WIN32) 

#  include "TProactor/WIN32_Proactor.h"

#else  /* defined (ACE_WIN32) */

#  include "TProactor/POSIX_Proactor.h"
#  include "TProactor/POSIX_CB_Proactor.h"
#  include "TProactor/SUN_Proactor.h"

#endif /* defined (ACE_WIN32) */

namespace Terabit {


// *****************************************************************
//
// *****************************************************************

IOThreadPool::IOThreadPool (const ACE_TCHAR *name,
                            ProactorType     proactor_type,
                            int              leader_type,  
                            int              num_proactors,  
                            size_t           max_op,
                            int              proactor_sig_num)
: BaseThreadPool    (name)
, proactor_vect_    ()
, proactor_type_    (proactor_type)
, leader_type_      (leader_type)     //  0  - shared, 1 - dedicated    
, max_op_           (max_op)          
, proactor_sig_num_ (proactor_sig_num)
, num_processors_   (ACE_OS::num_processors ())
{
    this->create_proactors (num_proactors);
}

IOThreadPool::~IOThreadPool (void)
{
    this->stop ();
    this->destroy_proactors ();
}

TRB_Proactor *
IOThreadPool::get_proactor(u_int idx)
{
    size_t count = proactor_vect_.size();

    if (count == 0)
        return 0;

    idx = idx % count;

    return proactor_vect_.at(idx);
}

int
IOThreadPool::run_event_loop(u_int thr_num)
{
  TRB_Proactor * proactor = get_proactor (thr_num);

  if (proactor == 0)
    return -1;

  proactor->proactor_run_event_loop ();
  
  return 0;
}

int
IOThreadPool::enable_event_loop(void)
{
  ProactorVector::iterator itr1 = proactor_vect_.begin();
  ProactorVector::iterator itr2 = proactor_vect_.end ();
  
  for (int i=0; itr1 != itr2; ++i, ++itr1)
  {
      TRB_Proactor * proactor = *itr1;

      int rc = proactor->proactor_reset_event_loop ();
      ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("(%t) %s Proactor=%d : reset_event_loop rc=%d\n"),
                    this->get_name (), i, rc ));
  }

  return 0;
}

int
IOThreadPool::disable_event_loop(void)
{
  ProactorVector::iterator itr1 = proactor_vect_.begin();
  ProactorVector::iterator itr2 = proactor_vect_.end ();
  
  for (int i=0; itr1 != itr2; ++i, ++itr1)
  {
      TRB_Proactor * proactor = *itr1;

      int rc = proactor->proactor_end_event_loop ();
      ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("(%t) %s Proactor=%d : end_event_loop rc=%d\n"),
                    this->get_name (), i, rc ));
  }

  return 0;
}


int
IOThreadPool::create_proactors(int num_proactors)
{
    ACE_ASSERT (this->proactor_vect_.empty ());

    if (num_proactors > this->num_processors_)
    {
        num_proactors = this->num_processors_;
    }
    if (num_proactors <= 0)
    {
        num_proactors = 1;
    }

    int rc = 0;
    {
        Guard_Monitor guard (this->get_monitor());    

        for (int i=0; i < num_proactors; ++i)
        {
            TRB_Proactor * proactor = create_proactor(i);
            if (!proactor)
            {
                rc = -1;
                break;
            }
            proactor_vect_.push_back (proactor);
        }
    }
    if (rc < 0)
    {
        ACE_ERROR((LM_ERROR,
            ACE_TEXT ("(%t) %s IOThreadPool::create_proactors failed\n"),
            this->get_name ()));

        this->destroy_proactors ();
    }

    return rc;
}

TRB_Proactor *
IOThreadPool::create_proactor(int idx)
{
    const ACE_TCHAR * str_type = ACE_TEXT(" DEFAULT");


#if defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)

    TRB_WIN32_Proactor * proactor_impl = 0;

    str_type = ACE_TEXT("WIN32");

    ACE_NEW_RETURN (proactor_impl,
                    TRB_WIN32_Proactor (this->num_processors_),
                    0);



#elif defined (ACE_HAS_AIO_CALLS) || defined (ACE_HAS_AIO_EMULATION)

    ProactorType ptype = this->proactor_type_;

    if (idx > 0 && ptype == PT_SUN) 
    {
        // aiowait() allows only single SUN_Proactor
        ptype = PT_POLL;
    }

    TRB_POSIX_Proactor * proactor_impl = 0;

    switch (ptype)
    {
    case PT_AIOCB:
        str_type = ACE_TEXT("AIOCB");
        ACE_NEW_RETURN (proactor_impl,
            TRB_POSIX_AIOCB_Proactor (this->max_op_,
                                      this->proactor_sig_num_,
                                      this->leader_type_),
            0);
        break;

    case PT_SIG:
        str_type = ACE_TEXT("SIG");
        ACE_NEW_RETURN (proactor_impl,
            TRB_POSIX_SIG_Proactor (this->max_op_,
                                    this->proactor_sig_num_,
                                    this->leader_type_),
            0);
        break;

    case PT_SUN:
        str_type = ACE_TEXT("SUN");
        ACE_NEW_RETURN (proactor_impl,
            TRB_SUN_Proactor (this->max_op_,
                              this->proactor_sig_num_,
                              this->leader_type_),
            0);
        break;

    case PT_CB:
        str_type = ACE_TEXT("CB-SGI");
        ACE_NEW_RETURN (proactor_impl,
            TRB_POSIX_CB_Proactor (this->max_op_,
                                   this->proactor_sig_num_,
                                   this->leader_type_),
            0);
        break;

    case PT_SELECT:
        str_type = ACE_TEXT("SELECT");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Select_Proactor (this->max_op_,
                                 this->proactor_sig_num_,
                                 this->leader_type_),
            0);
        break;

    case PT_POLL:
        str_type = ACE_TEXT("POLL");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Poll_Proactor (this->max_op_,
                               this->proactor_sig_num_,
                               this->leader_type_),
            0);
        break;


    case PT_EPOLL:
        str_type = ACE_TEXT("EPOLL");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Event_Poll_Proactor (this->max_op_,
                                     this->proactor_sig_num_,
                                     this->leader_type_),
            0);
        break;
    case PT_DEVPOLL:
        str_type = ACE_TEXT("DEVPOLL");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Dev_Poll_Proactor (this->max_op_,
                                   this->proactor_sig_num_,
                                   this->leader_type_),
            0);
        break;


    case PT_LINUX_NAIO:
        str_type = ACE_TEXT("LINUX_NAIO");
        ACE_NEW_RETURN (proactor_impl,
            TRB_LINUX_Proactor (this->max_op_,
                                this->proactor_sig_num_,
                                this->leader_type_),
            0);
        break;

    case PT_SUNPORT:
        str_type = ACE_TEXT("SUNPORT");
        ACE_NEW_RETURN (proactor_impl,
            TRB_SUN_Port_Proactor (this->max_op_,
                                   this->proactor_sig_num_,
                                   this->leader_type_),
            0);
        break;

    case PT_KQUEUE:
        str_type = ACE_TEXT("KQUEUE");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Kqueue_Proactor (this->max_op_,
                                 this->proactor_sig_num_,
                                 this->leader_type_),
            0);
        break;

    case PT_DUMMY:
        str_type = ACE_TEXT("DUMMY");
        ACE_NEW_RETURN (proactor_impl,
            TRB_Dummy_Proactor (),
            0);
    default:
        break;
    }

#endif // (ACE_WIN32) && !defined (ACE_HAS_WINCE)

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT("(%t) %s Created Proactor=%d Type=%s\n"),
        this->get_name (),
        idx,
        str_type));

    // always delete implementation  1 , not  !(proactor_impl == 0)

    TRB_Proactor * proactor = 0;
    ACE_NEW_RETURN (proactor,
        TRB_Proactor (proactor_impl, 1 ), 
        0);

    return proactor;
}

int
IOThreadPool::destroy_proactors (void)
{
    Guard_Monitor guard (this->get_monitor());

    ProactorVector::iterator itr1 = proactor_vect_.begin();
    ProactorVector::iterator itr2 = proactor_vect_.end ();

    for (int i=0; itr1 != itr2; ++i, ++itr1)
    {
        TRB_Proactor * proactor = *itr1;

        delete proactor;

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) %s Deleted Proactor=%d\n"),
            this->get_name (),
            i));

        *itr1=0;
    }
    proactor_vect_.clear ();

    return 0;
}

}  //namespace Terabit 


