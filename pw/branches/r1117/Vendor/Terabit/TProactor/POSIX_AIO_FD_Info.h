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
 *  @file    POSIX_AIO_FD_Info.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_FD_INFO_H 
#define TRB_POSIX_AIO_FD_INFO_H 

#include "TProactor/POSIX_Asynch_IO.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


//Forward declarations
class TRB_POSIX_AIO_Emulation_Provider;
class TRB_POSIX_AIO_FD_Info;
class TRB_POSIX_AIO_FD_Repository;
class TRB_POSIX_AIO_Config;

class TRB_POSIX_AIO_LINUX_NAIO_Provider;

/**
 *
 *
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_FD_Repository
{
public:
    friend class FD_Guard;

    typedef ACE_SYNCH_MUTEX            Mutex;
    typedef ACE_SYNCH_CONDITION        Condition;
    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;

    class FD_Guard : public Guard_Monitor
    {
    public:
        FD_Guard (TRB_POSIX_AIO_FD_Repository & rep,
                  ACE_HANDLE handle,
                  bool flgCreate = true);
        
        ~FD_Guard () {}

        TRB_POSIX_AIO_FD_Info * get_fd_info () const { return fd_info_;}
        
    private:
        TRB_POSIX_AIO_FD_Info  * fd_info_;
    };

    friend class FD_Guard;
    

    TRB_POSIX_AIO_FD_Repository (const TRB_POSIX_AIO_Config & config);
   

    virtual ~TRB_POSIX_AIO_FD_Repository ();

    int  open  (size_t num_files, size_t num_slots);
    void close ();

    size_t  size ()      const { return this->num_files_; }
    size_t  max_files () const { return this->num_files_; }
    size_t  num_slots () const { return this->num_slots_; }



private:
    const TRB_POSIX_AIO_Config & config_;
    size_t                   num_files_;
    size_t                   num_slots_;
    Monitor *                array_mon_;
    TRB_POSIX_AIO_FD_Info ** array_info_;
};


/**
 *
 *
 *
 */
class TPROACTOR_Export TRB_POSIX_AIO_FD_Info
{
public:

    typedef TRB_POSIX_AIO_FD_Repository::Mutex         Mutex;
    typedef TRB_POSIX_AIO_FD_Repository::Condition     Condition;
    typedef TRB_POSIX_AIO_FD_Repository::Monitor       Monitor;
    typedef TRB_POSIX_AIO_FD_Repository::Guard_Monitor Guard_Monitor;
    typedef TRB_POSIX_AIO_FD_Repository::Save_Guard    Save_Guard;

    typedef TRB_POSIX_AIO_FD_Repository::FD_Guard      FD_Guard;

    friend  class TRB_POSIX_AIO_Emulation_Provider;
    friend  class TRB_POSIX_AIO_LINUX_NAIO_Provider;

    enum
    {
        READ  = 0x0001,
        WRITE = 0x0002
    };

    enum
    {
        OPEN_READ     = 0x0001,
        OPEN_WRITE    = 0x0002,
        CANCEL        = 0x0004,  // CANCEL MUST CLEAR OPEN_READ/WRITE
        IN_CANCEL     = 0x0008,
        IN_EXEC_LIST  = 0x0010,
        IN_EXEC       = 0x0020,
        IN_DISP_LIST  = 0x0040,
        IN_DISPATCH   = 0x0080
    };


    TRB_POSIX_AIO_FD_Info (int fd = ACE_INVALID_HANDLE);
    virtual ~TRB_POSIX_AIO_FD_Info(void);

    ACE_HANDLE get_handle () const;

    int   open (int mask, FD_Guard & guard);


    // start read operation 
    // called with locked FD_Guard guard
    // If there were some completions, they will be placed 
    // into completed list
    // returns: 0   started, i.e queued nothing to do
    //          > 0 started, return value is interest to declare
    //          -1 unable to start
    int   start_read (TRB_POSIX_Asynch_Result * result,
                      FD_Guard & guard,
                      TRB_POSIX_Asynch_Result_Queue & completed_queue);

    // start write operation 
    // called with locked FD_Guard guard
    // If there were some completions, they will be placed 
    // into completed list
    // returns: 0   started, i.e queued nothing to do
    //          > 0 started, return value is interest to declare
    //          -1 unable to start
    int   start_write(TRB_POSIX_Asynch_Result * result,
                      FD_Guard & guard,
                      TRB_POSIX_Asynch_Result_Queue & completed_queue);

    // called with locked FD_Guard guard
    // canceled operations will be placed into completed list
    // returns: 1 - cancelled
    //          0 - already cancelled
    int   cancel (FD_Guard & guard,
                  TRB_POSIX_Asynch_Result_Queue & completed_queue);

    int   cancel_handler(FD_Guard &  guard,
                         TRB_Handler * handler,
                         TRB_POSIX_Asynch_Result_Queue & canceled_queue);


    // must be called with locked FD_Guard guard
    // completed operations will be placed into completed list
    // returns: 0   no interest  to declare
    //          > 0 return value is interest to declare
    int   execute (FD_Guard & guard,
                   TRB_POSIX_Asynch_Result_Queue & completed_queue);

    LinkD_T <TRB_POSIX_AIO_FD_Info> * get_link_interest () const;
    LinkD_T <TRB_POSIX_AIO_FD_Info> * get_link_execute () const;


    bool  is_open_for_read  () const;
    bool  is_open_for_write () const;

    bool  is_canceled () const;

    bool  is_ready_for_read  () const;
    bool  is_ready_for_write () const;

    int   get_active_mask () const;
    int   get_ready_mask () const;


    int   get_interest() const;

    
private:
    // only for LINUX NAIO provider 
    // TODO: replace later
    TRB_POSIX_Asynch_Result_List& get_read_list ()
      {
        return this->read_op_list_;
      }

    TRB_POSIX_Asynch_Result_List& get_write_list ()
      {
        return this->write_op_list_;
      }

    void  update_ready_mask (int ready_mask);
    void  set_active_mask (int active_mask);
    
    int   cancel_list (TRB_POSIX_Asynch_Result_List & pending_list,
                       TRB_POSIX_Asynch_Result_Queue & completed_queue);

    bool  execute_read_list(FD_Guard & guard,
                            TRB_POSIX_Asynch_Result_Queue & completed_queue);

    bool  execute_write_list(FD_Guard & guard,
                             TRB_POSIX_Asynch_Result_Queue & completed_queue);




    /// Member variables

    ACE_HANDLE fd_;

    mutable LinkD_T <TRB_POSIX_AIO_FD_Info>  link_interest_;
    mutable LinkD_T <TRB_POSIX_AIO_FD_Info>  link_execute_;
    

    TRB_POSIX_Asynch_Result_List read_op_list_;
    TRB_POSIX_Asynch_Result_List write_op_list_;


    /// currently ready events
    int ready_mask_;

    /// currently active/pending events
    int active_mask_;

    /// open-cancel-dispatch flags
    int flags_;

    int num_waiters_;


};

//-------------------------------------------------------
//
//-------------------------------------------------------
class FD_Info_Exec_Link
{
public :
    LinkD_T <TRB_POSIX_AIO_FD_Info> *
        operator ()(const TRB_POSIX_AIO_FD_Info *  x)  const 
    {
        return  x->get_link_execute ();
    }
};


typedef 
Double_List_T <TRB_POSIX_AIO_FD_Info, FD_Info_Exec_Link>
FD_Info_Exec_List;

class FD_Info_Interest_Link
{
public :
    LinkD_T <TRB_POSIX_AIO_FD_Info> *
        operator ()(const TRB_POSIX_AIO_FD_Info *  x)  const 
    {
        return  x->get_link_interest ();
    }
};

typedef 
Double_List_T <TRB_POSIX_AIO_FD_Info, FD_Info_Interest_Link>
FD_Info_Interest_List;
//-------------------------------------------------------
//
//-------------------------------------------------------
inline ACE_HANDLE 
TRB_POSIX_AIO_FD_Info::get_handle () const
{
    return this->fd_;
}

inline LinkD_T <TRB_POSIX_AIO_FD_Info> *
TRB_POSIX_AIO_FD_Info::get_link_interest () const
{
    return & this->link_interest_;
}

inline LinkD_T <TRB_POSIX_AIO_FD_Info> *
TRB_POSIX_AIO_FD_Info::get_link_execute () const
{
    return & this->link_execute_;
}

inline int
TRB_POSIX_AIO_FD_Info::get_ready_mask () const
{
    return this->ready_mask_;
}

inline int
TRB_POSIX_AIO_FD_Info::get_active_mask () const
{
    return this->active_mask_;
}

inline void 
TRB_POSIX_AIO_FD_Info::update_ready_mask(int ready_mask)
{
    this->ready_mask_ |= ready_mask;
}

inline void 
TRB_POSIX_AIO_FD_Info::set_active_mask(int active_mask)
{
    this->active_mask_ = active_mask;
}


inline int  
TRB_POSIX_AIO_FD_Info::get_interest () const
{
    int  interest = 0;

    if (!read_op_list_.empty())
    {
        ACE_SET_BITS (interest, READ);
    }

    if (!write_op_list_.empty())
    {
        ACE_SET_BITS (interest, WRITE);
    }

    //  do not declare ready events
    interest &= ~this->ready_mask_;
    return interest;
}

inline bool  
TRB_POSIX_AIO_FD_Info::is_canceled () const
{
    return ACE_BIT_ENABLED(flags_, CANCEL);
}

inline bool  
TRB_POSIX_AIO_FD_Info::is_open_for_read () const
{
    return ACE_BIT_ENABLED(flags_, OPEN_READ);
}

inline bool  
TRB_POSIX_AIO_FD_Info::is_open_for_write () const
{
    return ACE_BIT_ENABLED(flags_, OPEN_WRITE);
}

inline bool  
TRB_POSIX_AIO_FD_Info::is_ready_for_read () const
{
    return ACE_BIT_ENABLED(ready_mask_, READ);
}

inline bool  
TRB_POSIX_AIO_FD_Info::is_ready_for_write () const
{
    return ACE_BIT_ENABLED(ready_mask_, WRITE);
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#endif //TRB_POSIX_AIO_FD_INFO_H 
