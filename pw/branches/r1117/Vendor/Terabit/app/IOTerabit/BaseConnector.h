/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Asynch_Connector3.h
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_BASECONNECTOR_H 
#define TPROACTOR_BASECONNECTOR_H 

#include "IOTerabit/IOTERABIT_Export.h"

#include "ace/pre.h"

#include "TProactor/Asynch_IO.h"
#include "TProactor/Monitor_T.h"

#include "ace/Synch_T.h"
#include "ace/INET_Addr.h"

namespace Terabit {


/**
 * @class BaseConnector
 *
 * @brief This class is an example of the Connector pattern.  This class
 * will establish new connections and create new HANDLER objects to handle
 * the new connections.
 *
 * Unlike the ACE_Connector, however, this class is designed to
 * be used asynchronously with the ACE Proactor framework.
 */


class IOTERABIT_Export BaseConnector : public TRB_Handler
{
public:
    typedef ACE_SYNCH_MUTEX            Mutex;
    typedef ACE_SYNCH_CONDITION        Condition;
    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;

    enum State
    {
        ST_INIT   = 0x0000,   // BEFORE OPEN
        ST_ACTIVE = 0x0001,   // OPERATIONAL
        ST_CANCEL = 0x0002,   // IN CANCEL
        ST_CLOSED = 0x0004    // CLOSED
    };

    /// A do nothing constructor.
    BaseConnector (void);

    /// Virtual destruction
    virtual ~BaseConnector (void);

    /**
    * This opens asynch connector
    */
    virtual int open (TRB_Proactor *proactor);

    /// This initiates a new asynchronous connect
    virtual int connect (const ACE_Addr &remote_sap,
                         const ACE_Addr &local_sap =
                               ACE_Addr::sap_any,
                         int reuse_addr = 1,
                         const void *act = 0);

    /**
    * Cancels all pending connects operations issued by this object.
    * and close the listen handle
    *
    * @note On Windows, the only one way to cancel all pending
    *  connect operations is to close listen handel. Windows call
    *  CancelIO cancels only operations initiated by the calling 
    *  thread, which is not helpfull.
    * @note On UNIX, it is safe to close listen handle only after
    *  cancellation. TProcator will take care about all pending
    *  connects .
    * So the portable solution is to do cancel-and-close, which is
    * actually done in current implementation.
    */
    virtual int cancel (void);

    /**
    * Waits for cancellations of all pending connects operations
    * issued by this object. This method must be called to ensure
    * that no more asychronous callbacks is expected and it is
    * safe to delete this object.
    */
    void wait (void);

    int get_pending_count (void) const;

    State get_state ();



private:

    /// This is called when an outstanding accept completes.
    virtual void handle_connect (const TRB_Asynch_Connect::Result &result);


    /**
    * This is the template method used to create new handler.
    * Subclasses must overwrite this method if a new handler creation
    * strategy is required.
    * @retval  -1  BaseConnector will close the connection, and
    *              the service will not be opened.
    * @retval  0   Service opening will proceeed.
    */
    virtual int on_connect_completed (const TRB_Asynch_Connect::Result& result) = 0;

private:

    /// Monitor to protect state
    mutable Monitor monitor_;

    /// state 
    State  state_;
    
    /// The number of pending asynchronous accepts
    int pending_count_;


    /// Asynch_Connect used to make life easier :-)
    TRB_Asynch_Connect asynch_connect_;

};

inline BaseConnector::State
BaseConnector::get_state ()
{
    Guard_Monitor guard (monitor_);
    return this->state_;
}

}  //namespace Terabit 


#include "ace/post.h"
#endif //TPROACTOR_BASECONNECTOR_H 
