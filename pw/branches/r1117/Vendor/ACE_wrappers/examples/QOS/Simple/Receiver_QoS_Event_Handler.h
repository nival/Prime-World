/* -*- C++ -*- */
// $Id: Receiver_QoS_Event_Handler.h 80826 2008-03-04 14:51:23Z wotte $

// ============================================================================
//
// = LIBRARY
//    ACE_wrappers/examples/QOS
//
// = FILENAME
//    Receiver_QoS_Event_Handler.h
//
// = AUTHOR
//    Vishal Kachroo <vishal@cs.wustl.edu>
//
// ============================================================================

#ifndef RECEIVER_QOS_EVENT_HANDLER_H
#define RECEIVER_QOS_EVENT_HANDLER_H

#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/Event_Handler.h"
#include "ace/QoS/QoS_Session.h"
#include "ace/QoS/SOCK_Dgram_Mcast_QoS.h"

ACE_RCSID(Receiver_QoS_Event_Handler, Receiver_QoS_Event_Handler, "$Id: Receiver_QoS_Event_Handler.h 80826 2008-03-04 14:51:23Z wotte $")

  class Receiver_QoS_Event_Handler : public ACE_Event_Handler
  {
  public:
    // = Initialization and Termination methods.
    Receiver_QoS_Event_Handler (void);
    // Constructor.

    Receiver_QoS_Event_Handler (const ACE_SOCK_Dgram_Mcast_QoS &dgram_mcast_qos,
                                ACE_QoS_Session *qos_session);
    // Constructor.

    ~Receiver_QoS_Event_Handler (void);
    // Destructor.

    virtual ACE_HANDLE get_handle (void) const;
    // Override this to return the handle of the Dgram_Mcast
    // that we are using.

    virtual int handle_input (ACE_HANDLE fd);
    // Handles a READ event.

    virtual int handle_qos (ACE_HANDLE fd);
    // Handles a QoS event.

  private:
    ACE_SOCK_Dgram_Mcast_QoS dgram_mcast_qos_;
    ACE_QoS_Session *qos_session_;
    ACE_INET_Addr remote_addr_;
  };

#endif  /* RECEIVER_QOS_EVENT_HANDLER_H */



