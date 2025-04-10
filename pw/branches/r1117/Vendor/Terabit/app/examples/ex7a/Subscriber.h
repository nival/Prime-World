#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "TProactor/Double_List_T.h"
#include "IOTerabit/AsynchChannel.h"
#include "BufferFactory.h"


//#include "IOTerabit/Protocol.h"
//#include "IOTerabit/WrkThreadPool_T.h"

#include <map>

class Topics;
   
// *************************************************************
//  Subscriber
// *************************************************************

class Subscriber : public RefCount
{

public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    Subscriber(Topics *topics, 
               const ACE_TCHAR *topic_name);

    virtual ~Subscriber();

    LinkD_T <Subscriber> * get_link () const;


    void  send_message(ACE_Message_Block *mb);

    
private:
    /// link element
    
    ACE_Message_Queue<ACE_MT_SYNCH> msg_queue_;  
}; 




#endif  // SUBSCRIBER_H
